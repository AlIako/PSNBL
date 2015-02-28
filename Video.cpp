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
    m_largeur=800;
    m_hauteur=600;
    m_fullscreen=false;
    m_fov=90;

    std::ifstream file("config.ini", std::ios::in);

    if(file)
    {
        std::string befor_read="",read_name="",read_name_before="";
        std::string cur_read="";
        int cur_int=0;

        while(!file.eof())
        {
            read_name=cur_read.substr(0,cur_read.size()-1);//enleve le ":"

            if(read_name_before=="resolution")
            {
                file >> cur_int;
                m_largeur=cur_int;
                file >> cur_int;
                m_hauteur=cur_int;

                std::cerr<<"resolution: "<<m_largeur<<" "<< m_hauteur<<std::endl;
            }
            else if(read_name=="fullscreen")
            {
                file >> cur_int;
                if(cur_int)
                    m_fullscreen=true;
                else m_fullscreen=false;
            }
            else if(read_name=="fov")
            {
                file >> cur_int;
                m_fov=cur_int;
            }

            file >> cur_read;
            befor_read=cur_read;
            read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"

        }

        std::cerr<<std::endl;
        file.close();
    }
    else
        std::cerr << "can't open file (config settings)" << std::endl;




    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("BHO 0.12",NULL);

    if(m_fullscreen)
        SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL | SDL_FULLSCREEN);
    else SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL);

    SDL_Init(SDL_INIT_VIDEO);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(m_fov,(double)m_hauteur/m_largeur,0.01,1000);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

  	glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur

    SDL_ShowCursor(SDL_DISABLE);//no cursor
    SDL_WM_GrabInput(SDL_GRAB_ON);


    fog.enable();



    /*const unsigned char* glver = glGetString(GL_VERSION);
    std::cerr <<"Opengl Version: "<< glver<<std::endl;


    //glew
    //glewInit();
    //shaders
    programID = LoadShaders( "../shaders/vertexShader.vsh", "../shaders/fragmentShader.fsh" );
    programIDRed = LoadShaders( "../shaders/vertexShaderRed.vsh", "../shaders/fragmentShaderRed.fsh" );
    programIDBlur = LoadShaders( "../shaders/vertexShaderBlur.vsh", "../shaders/fragmentShaderBlur.fsh" );*/
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
}

void Video::matrixProjection()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(m_fov,(double)m_hauteur/m_largeur,0.01,1000);
}

void Video::matrixOrtho2D()
{
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,1,0,1);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
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









void Video::close()
{
    SDL_Quit();
}

Video::~Video()
{

}

