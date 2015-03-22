#include "Video.h"

Video* Video::m_instance = new Video();


Video* Video::getInstance()
{
    return m_instance;
}



Video::Video()
{

}



void Video::ini()
{
    m_hd=false;
    m_largeur=800;
    m_hauteur=600;
    m_fullscreen=false;
    m_fov=90;

    m_largeur=Config::getInstance()->width;
    m_hauteur=Config::getInstance()->height;
    m_fullscreen=Config::getInstance()->fullscreen;



    m_fov=Config::getInstance()->fov;
    if(Config::getInstance()->width>1500)
        m_fov=90;





    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("BHO 0.12",NULL);

    if(m_fullscreen)
        SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL | SDL_FULLSCREEN);
    else SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL);

    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);//antialia

    SDL_Init(SDL_INIT_VIDEO);

	//glViewport(0,0,m_largeur,m_hauteur);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(m_fov,(double)m_hauteur/m_largeur,0.01,1000);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

  	glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur

    //SDL_ShowCursor(SDL_DISABLE);//no cursor
    //SDL_WM_GrabInput(SDL_GRAB_ON);

    //resolutions available


    m_resolutions.clear();
    SDL_Rect** modes;
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    for (unsigned int i=0; modes[i]; ++i)
        m_resolutions.push_back(Vector3D(modes[i]->w,modes[i]->h,0));

    //fog
    fog.enable();

    //fade
    fade.ini();






    const unsigned char* glver = glGetString(GL_VERSION);
    std::cerr <<"Opengl Version: "<< glver<<std::endl;


    //glew
    glewInit();
    //shaders
    programID = LoadShaders( "../data/shaders/vertexShader.vsh", "../shaders/fragmentShader.fsh" );
    programIDRed = LoadShaders( "../data/shaders/vertexShaderRed.vsh", "../shaders/fragmentShaderRed.fsh" );
    programIDBlur = LoadShaders( "../data/shaders/vertexShaderBlur.vsh", "../shaders/fragmentShaderBlur.fsh" );
    programIDWave = LoadShaders( "../data/shaders/vertexShaderWave.vsh", "../shaders/fragmentShaderWave.fsh" );
    programIDText = LoadShaders( "../data/shaders/vertexShaderText.vsh", "../shaders/fragmentShaderText.fsh" );
}

void Video::incrFOV(int i)
{
    m_fov+=i;
    stringstream ss;
    ss << "fov:"<<m_fov;
    Tracer::getInstance()->trace("video",ss.str());
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(m_fov,(double)m_hauteur/m_largeur,0.01,1000);
}


//shaders
GLuint Video::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void Video::update(double functionTime)
{
    fog.update(functionTime);
    fade.update(functionTime);
}

void Video::matrixProjection()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(m_fov,(double)m_hauteur/m_largeur,0.01,1000);

    /*glMatrixMode(GL_PROJECTION );
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();*/
}

void Video::matrixOrtho2D()
{
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,1,0,1);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

	/*glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,1,1,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();*/
}
void Video::beforeDraw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}

void Video::afterDraw()
{
    glFlush();
    SDL_GL_SwapBuffers();
}



string Video::getStrHD()
{
    if(m_hd)
        return "hq";
    return "lq";
}

Vector3D Video::nextResolution(int width, int height)
{
    int cur=0;
    //find which we have
    for(unsigned int i=0;i<m_resolutions.size();i++)
    {
        if(m_resolutions[i].X==width && m_resolutions[i].Y==height)
            cur=i;
    }
    //return next one
    cur--;
    if(cur<0)
        cur=(int)m_resolutions.size()-1;

    return Vector3D(m_resolutions[cur].X,m_resolutions[cur].Y,0);
}
Vector3D Video::previousResolution(int width, int height)
{
    int cur=0;
    //find which we have
    for(unsigned int i=0;i<m_resolutions.size();i++)
    {
        if(m_resolutions[i].X==width && m_resolutions[i].Y==height)
            cur=i;
    }
    //return previous one
    cur++;
    if(cur>=(int)m_resolutions.size())
        cur=0;


    return Vector3D(m_resolutions[cur].X,m_resolutions[cur].Y,0);
}



void Video::close()
{
    SDL_Quit();
}

Video::~Video()
{

}

