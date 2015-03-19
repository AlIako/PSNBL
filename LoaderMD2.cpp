#include "LoaderMD2.h"

vec3_t anorms_table[162] = {
{ -0.525731f,  0.000000f,  0.850651f },
{ -0.442863f,  0.238856f,  0.864188f },
{ -0.295242f,  0.000000f,  0.955423f },
{ -0.309017f,  0.500000f,  0.809017f },
{ -0.162460f,  0.262866f,  0.951056f },
{  0.000000f,  0.000000f,  1.000000f },
{  0.000000f,  0.850651f,  0.525731f },
{ -0.147621f,  0.716567f,  0.681718f },
{  0.147621f,  0.716567f,  0.681718f },
{  0.000000f,  0.525731f,  0.850651f },
{  0.309017f,  0.500000f,  0.809017f },
{  0.525731f,  0.000000f,  0.850651f },
{  0.295242f,  0.000000f,  0.955423f },
{  0.442863f,  0.238856f,  0.864188f },
{  0.162460f,  0.262866f,  0.951056f },
{ -0.681718f,  0.147621f,  0.716567f },
{ -0.809017f,  0.309017f,  0.500000f },
{ -0.587785f,  0.425325f,  0.688191f },
{ -0.850651f,  0.525731f,  0.000000f },
{ -0.864188f,  0.442863f,  0.238856f },
{ -0.716567f,  0.681718f,  0.147621f },
{ -0.688191f,  0.587785f,  0.425325f },
{ -0.500000f,  0.809017f,  0.309017f },
{ -0.238856f,  0.864188f,  0.442863f },
{ -0.425325f,  0.688191f,  0.587785f },
{ -0.716567f,  0.681718f, -0.147621f },
{ -0.500000f,  0.809017f, -0.309017f },
{ -0.525731f,  0.850651f,  0.000000f },
{  0.000000f,  0.850651f, -0.525731f },
{ -0.238856f,  0.864188f, -0.442863f },
{  0.000000f,  0.955423f, -0.295242f },
{ -0.262866f,  0.951056f, -0.162460f },
{  0.000000f,  1.000000f,  0.000000f },
{  0.000000f,  0.955423f,  0.295242f },
{ -0.262866f,  0.951056f,  0.162460f },
{  0.238856f,  0.864188f,  0.442863f },
{  0.262866f,  0.951056f,  0.162460f },
{  0.500000f,  0.809017f,  0.309017f },
{  0.238856f,  0.864188f, -0.442863f },
{  0.262866f,  0.951056f, -0.162460f },
{  0.500000f,  0.809017f, -0.309017f },
{  0.850651f,  0.525731f,  0.000000f },
{  0.716567f,  0.681718f,  0.147621f },
{  0.716567f,  0.681718f, -0.147621f },
{  0.525731f,  0.850651f,  0.000000f },
{  0.425325f,  0.688191f,  0.587785f },
{  0.864188f,  0.442863f,  0.238856f },
{  0.688191f,  0.587785f,  0.425325f },
{  0.809017f,  0.309017f,  0.500000f },
{  0.681718f,  0.147621f,  0.716567f },
{  0.587785f,  0.425325f,  0.688191f },
{  0.955423f,  0.295242f,  0.000000f },
{  1.000000f,  0.000000f,  0.000000f },
{  0.951056f,  0.162460f,  0.262866f },
{  0.850651f, -0.525731f,  0.000000f },
{  0.955423f, -0.295242f,  0.000000f },
{  0.864188f, -0.442863f,  0.238856f },
{  0.951056f, -0.162460f,  0.262866f },
{  0.809017f, -0.309017f,  0.500000f },
{  0.681718f, -0.147621f,  0.716567f },
{  0.850651f,  0.000000f,  0.525731f },
{  0.864188f,  0.442863f, -0.238856f },
{  0.809017f,  0.309017f, -0.500000f },
{  0.951056f,  0.162460f, -0.262866f },
{  0.525731f,  0.000000f, -0.850651f },
{  0.681718f,  0.147621f, -0.716567f },
{  0.681718f, -0.147621f, -0.716567f },
{  0.850651f,  0.000000f, -0.525731f },
{  0.809017f, -0.309017f, -0.500000f },
{  0.864188f, -0.442863f, -0.238856f },
{  0.951056f, -0.162460f, -0.262866f },
{  0.147621f,  0.716567f, -0.681718f },
{  0.309017f,  0.500000f, -0.809017f },
{  0.425325f,  0.688191f, -0.587785f },
{  0.442863f,  0.238856f, -0.864188f },
{  0.587785f,  0.425325f, -0.688191f },
{  0.688191f,  0.587785f, -0.425325f },
{ -0.147621f,  0.716567f, -0.681718f },
{ -0.309017f,  0.500000f, -0.809017f },
{  0.000000f,  0.525731f, -0.850651f },
{ -0.525731f,  0.000000f, -0.850651f },
{ -0.442863f,  0.238856f, -0.864188f },
{ -0.295242f,  0.000000f, -0.955423f },
{ -0.162460f,  0.262866f, -0.951056f },
{  0.000000f,  0.000000f, -1.000000f },
{  0.295242f,  0.000000f, -0.955423f },
{  0.162460f,  0.262866f, -0.951056f },
{ -0.442863f, -0.238856f, -0.864188f },
{ -0.309017f, -0.500000f, -0.809017f },
{ -0.162460f, -0.262866f, -0.951056f },
{  0.000000f, -0.850651f, -0.525731f },
{ -0.147621f, -0.716567f, -0.681718f },
{  0.147621f, -0.716567f, -0.681718f },
{  0.000000f, -0.525731f, -0.850651f },
{  0.309017f, -0.500000f, -0.809017f },
{  0.442863f, -0.238856f, -0.864188f },
{  0.162460f, -0.262866f, -0.951056f },
{  0.238856f, -0.864188f, -0.442863f },
{  0.500000f, -0.809017f, -0.309017f },
{  0.425325f, -0.688191f, -0.587785f },
{  0.716567f, -0.681718f, -0.147621f },
{  0.688191f, -0.587785f, -0.425325f },
{  0.587785f, -0.425325f, -0.688191f },
{  0.000000f, -0.955423f, -0.295242f },
{  0.000000f, -1.000000f,  0.000000f },
{  0.262866f, -0.951056f, -0.162460f },
{  0.000000f, -0.850651f,  0.525731f },
{  0.000000f, -0.955423f,  0.295242f },
{  0.238856f, -0.864188f,  0.442863f },
{  0.262866f, -0.951056f,  0.162460f },
{  0.500000f, -0.809017f,  0.309017f },
{  0.716567f, -0.681718f,  0.147621f },
{  0.525731f, -0.850651f,  0.000000f },
{ -0.238856f, -0.864188f, -0.442863f },
{ -0.500000f, -0.809017f, -0.309017f },
{ -0.262866f, -0.951056f, -0.162460f },
{ -0.850651f, -0.525731f,  0.000000f },
{ -0.716567f, -0.681718f, -0.147621f },
{ -0.716567f, -0.681718f,  0.147621f },
{ -0.525731f, -0.850651f,  0.000000f },
{ -0.500000f, -0.809017f,  0.309017f },
{ -0.238856f, -0.864188f,  0.442863f },
{ -0.262866f, -0.951056f,  0.162460f },
{ -0.864188f, -0.442863f,  0.238856f },
{ -0.809017f, -0.309017f,  0.500000f },
{ -0.688191f, -0.587785f,  0.425325f },
{ -0.681718f, -0.147621f,  0.716567f },
{ -0.442863f, -0.238856f,  0.864188f },
{ -0.587785f, -0.425325f,  0.688191f },
{ -0.309017f, -0.500000f,  0.809017f },
{ -0.147621f, -0.716567f,  0.681718f },
{ -0.425325f, -0.688191f,  0.587785f },
{ -0.162460f, -0.262866f,  0.951056f },
{  0.442863f, -0.238856f,  0.864188f },
{  0.162460f, -0.262866f,  0.951056f },
{  0.309017f, -0.500000f,  0.809017f },
{  0.147621f, -0.716567f,  0.681718f },
{  0.000000f, -0.525731f,  0.850651f },
{  0.425325f, -0.688191f,  0.587785f },
{  0.587785f, -0.425325f,  0.688191f },
{  0.688191f, -0.587785f,  0.425325f },
{ -0.955423f,  0.295242f,  0.000000f },
{ -0.951056f,  0.162460f,  0.262866f },
{ -1.000000f,  0.000000f,  0.000000f },
{ -0.850651f,  0.000000f,  0.525731f },
{ -0.955423f, -0.295242f,  0.000000f },
{ -0.951056f, -0.162460f,  0.262866f },
{ -0.864188f,  0.442863f, -0.238856f },
{ -0.951056f,  0.162460f, -0.262866f },
{ -0.809017f,  0.309017f, -0.500000f },
{ -0.864188f, -0.442863f, -0.238856f },
{ -0.951056f, -0.162460f, -0.262866f },
{ -0.809017f, -0.309017f, -0.500000f },
{ -0.681718f,  0.147621f, -0.716567f },
{ -0.681718f, -0.147621f, -0.716567f },
{ -0.850651f,  0.000000f, -0.525731f },
{ -0.688191f,  0.587785f, -0.425325f },
{ -0.587785f,  0.425325f, -0.688191f },
{ -0.425325f,  0.688191f, -0.587785f },
{ -0.425325f, -0.688191f, -0.587785f },
{ -0.587785f, -0.425325f, -0.688191f },
{ -0.688191f, -0.587785f, -0.425325f }
};
md2_model_t::md2_model_t()
{
    repertoire="";
    tex_id=0;
    m_texture=NULL;
    afficher=true;
    text=true;
}

void md2_model_t::getTexture(const char *filename)
{
    std::string name=filename;
    name=name.substr(0,name.size()-4);//enleve le .md2 du nom
    std::string chaineALire="";
    std::string reper="data/models/md2/";

    DIR *dir;
    //MAP PERSO
    struct dirent *lecture;

    char* tempchemin=stringtochar(reper);
    dir = opendir(tempchemin);
    delete tempchemin;
    tempchemin=NULL;

    while ((lecture = readdir(dir)))
    {
        chaineALire=strdup(lecture->d_name);
        if(reper+chaineALire==name+".tga" ||
           reper+chaineALire==name+".JPEG"||
           reper+chaineALire==name+".PNG" ||
           reper+chaineALire==name+".png" ||
           reper+chaineALire==name+".JPG" ||
           reper+chaineALire==name+".pcx" ||
           reper+chaineALire==name+".bmp" ||
           reper+chaineALire==name+".jpg")
        {
            cerr << "texture " << reper+chaineALire << endl;

            char* tempS=stringtochar(reper+chaineALire);
            tex_id=loadTexture(tempS);
            delete tempS;

            GTexture::getInstance()->addTexture(reper+chaineALire);
            m_texture=GTexture::getInstance()->getTexture(reper+chaineALire);
            cerr << "TEXTURE LOAD MD2" << endl;
        }
    }

}
int md2_model_t::ReadMD2Model(const char *filename)
{
    cerr << "MD2 " << filename << "..." << endl;
    //tex_id=loadTexture("data/models/md2/lili.tga");
    getTexture(filename);
    repertoire=filename;
    FILE *fp;
    fp = fopen (filename, "rb");
    if (!fp)
    {
        cerr<< "error: couldn't open "<< filename<<endl;
        return 0;
    }

    // read header
    fread (&header, 1, sizeof (md2_header_t), fp);

    if ((header.ident != 844121161) ||
    (header.version != 8))
    {
        // error!
        cerr<< "error: bad version! "<< endl;
        fclose (fp);
        return 0;
    }

    // memory allocation
    skins = (md2_skin_t *)malloc (sizeof (md2_skin_t) * header.num_skins);
    texcoords = (md2_texCoord_t *)malloc (sizeof (md2_texCoord_t) * header.num_st);
    triangles = (md2_triangle_t *)malloc (sizeof (md2_triangle_t) * header.num_tris);
    frames = (md2_frame_t *)malloc (sizeof(md2_frame_t) * header.num_frames);
    glcmds = (int *)malloc (sizeof (int) * header.num_glcmds);

    // read model data
    fseek (fp, header.offset_skins, SEEK_SET);
    fread (skins, sizeof (md2_skin_t), header.num_skins, fp);

    fseek (fp, header.offset_st, SEEK_SET);
    fread (texcoords, sizeof (md2_texCoord_t), header.num_st, fp);

    fseek (fp, header.offset_tris, SEEK_SET);
    fread (triangles, sizeof (md2_triangle_t), header.num_tris, fp);

    fseek (fp, header.offset_glcmds, SEEK_SET);
    fread (glcmds, sizeof (int), header.num_glcmds, fp);

    // read frames
    fseek (fp, header.offset_frames, SEEK_SET);
    for (int i = 0; i < header.num_frames; ++i)
    {
        // memory allocation for vertices of this frame
        frames[i].verts = (md2_vertex_t *)
        malloc (sizeof (md2_vertex_t) * header.num_vertices);

        // read frame data
        fread (frames[i].scale, sizeof (vec3_t), 1, fp);
        fread (frames[i].translate, sizeof (vec3_t), 1, fp);
        fread (frames[i].name, sizeof (char), 16, fp);
        fread (frames[i].verts, sizeof (md2_vertex_t), header.num_vertices, fp);
    }

    fclose (fp);
    return 1;
}

void md2_model_t::FreeModel()
{
    if (skins)
    {
        free (skins);
        skins = NULL;
    }
    if (texcoords)
    {
        free (texcoords);
        texcoords = NULL;
    }
    if (triangles)
    {
        free (triangles);
        triangles = NULL;
    }
    if (glcmds)
    {
        free (glcmds);
        glcmds = NULL;
    }
    if (frames)
    {
        for (int i = 0; i < header.num_frames; ++i)
        {
            free (frames[i].verts);
            frames[i].verts = NULL;
        }
        free (frames);
        frames = NULL;
    }
}

void md2_model_t::RenderFrame(int n)
{
    GLfloat s, t;
    vec3_t v;
    md2_frame_t *pframe;
    md2_vertex_t *pvert;
    // check if n is in a valid range
    if ((n < 0) || (n > header.num_frames - 1))
    return;

    // enable model's texture
    glBindTexture (GL_TEXTURE_2D, tex_id);
    // draw the model
    glBegin (GL_TRIANGLES);
    // draw each triangle
    for (int i=0;i<header.num_tris; ++i)
    {
        // draw each vertex
        for (int j=0;j<3;++j)
        {
            pframe = &frames[n];
            pvert = &pframe->verts[triangles[i].vertex[j]];
            // compute texture coordinates
            s = (GLfloat)texcoords[triangles[i].st[j]].s / header.skinwidth;
            t = (GLfloat)texcoords[triangles[i].st[j]].t / header.skinheight;
            // pass texture coordinates to OpenGL
            glTexCoord2f (s, t);

            // normal vector
            glNormal3fv (anorms_table[pvert->normalIndex]);
            // calculate vertex real position
            v[0] = (pframe->scale[0] * pvert->v[0]) + pframe->translate[0];
            v[1] = (pframe->scale[1] * pvert->v[1]) + pframe->translate[1];
            v[2] = (pframe->scale[2] * pvert->v[2]) + pframe->translate[2];

            glVertex3fv (v);
        }
    }
    glEnd();
}
void md2_model_t::RenderFrameItp(int n, float interp)
{
    GLfloat s, t;
    vec3_t v_curr, v_next, v, norm;
    float *n_curr, *n_next;
    md2_frame_t *pframe1, *pframe2;
    md2_vertex_t *pvert1, *pvert2;
    //check if n is in a valid range
    if ((n < 0) || (n > header.num_frames))
    return;

    // enable model's texture
    glBindTexture (GL_TEXTURE_2D, tex_id);
    // draw the model
    glBegin (GL_TRIANGLES);
    // draw each triangle
    for (int i=0;i<header.num_tris; ++i)
    {
        // draw each vertex
        for (int j = 0; j < 3; ++j)
        {
            pframe1 = &frames[n];
            pframe2 = &frames[n + 1];
            pvert1 = &pframe1->verts[triangles[i].vertex[j]];
            pvert2 = &pframe2->verts[triangles[i].vertex[j]];
            // compute texture coordinates
            s = (GLfloat)texcoords[triangles[i].st[j]].s / header.skinwidth;
            t = (GLfloat)texcoords[triangles[i].st[j]].t / header.skinheight;
            // pass texture coordinates to OpenGL
            glTexCoord2f (s, t);
            // interpolate normals
            n_curr = anorms_table[pvert1->normalIndex];
            n_next = anorms_table[pvert2->normalIndex];
            norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
            norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
            norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);
            glNormal3fv (norm);
            // interpolate vertices
            v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
            v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
            v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];
            v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
            v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
            v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];
            v[0] = v_curr[0] + interp * (v_next[0] - v_curr[0]);
            v[1] = v_curr[1] + interp * (v_next[1] - v_curr[1]);
            v[2] = v_curr[2] + interp * (v_next[2] - v_curr[2]);
            glVertex3fv (v);
        }
    }
    glEnd();
}

void md2_model_t::RenderFrameWithGLCmds(int n)
{
    int i, *pglcmds;
    vec3_t v;
    md2_frame_t *pframe;
    md2_vertex_t *pvert;
    md2_glcmd_t *packet;

    // check if n is in a valid range
    if ((n < 0) || (n > header.num_frames - 1))
        return;

    // enable model's texture
    glBindTexture (GL_TEXTURE_2D, tex_id);

    // pglcmds points at the start of the command list
    pglcmds = glcmds;

    // draw the model
    while ((i = *(pglcmds++)) != 0)
    {
        if (i < 0)
        {
            glBegin (GL_TRIANGLE_FAN);
            i = -i;
        }
        else
            glBegin (GL_TRIANGLE_STRIP);

        // draw each vertex of this group
        for (; i > 0; --i, pglcmds += 3)
        {
            packet = (md2_glcmd_t *)pglcmds;
            pframe = &frames[n];
            pvert = &pframe->verts[packet->index];
            // pass texture coordinates to OpenGL
            glTexCoord2f (packet->s, packet->t);
            // normal vector
            glNormal3fv (anorms_table[pvert->normalIndex]);
            // calculate vertex real position
            v[0] = (pframe->scale[0] * pvert->v[0]) + pframe->translate[0];
            v[1] = (pframe->scale[1] * pvert->v[1]) + pframe->translate[1];
            v[2] = (pframe->scale[2] * pvert->v[2]) + pframe->translate[2];
            glVertex3fv (v);
        }
        glEnd();
    }
}

void md2_model_t::RenderFrameItpWithGLCmds(int n, float interp)
{
    int i, *pglcmds;
    vec3_t v_curr, v_next, v, norm;
    float *n_curr, *n_next;
    md2_frame_t *pframe1, *pframe2;
    md2_vertex_t *pvert1, *pvert2;
    md2_glcmd_t *packet;
    // check if n is in a valid range
    if ((n < 0) || (n > header.num_frames - 1))
        return;

    // enable model's texture
    //tex_id=loadTexture("data/models/md2/lili.tga");
    //glBindTexture (GL_TEXTURE_2D, tex_id);
    if(m_texture!=NULL && text&&0)
    {
        //cerr << "BIND TEXTURE MD2" << endl;
        m_texture->bind();
    }
    // pglcmds points at the start of the command list
    pglcmds = glcmds;
    // draw the model
    while ((i = *(pglcmds++)) != 0)
    {
        if (i < 0)
        {
            glBegin (GL_TRIANGLE_FAN);
            i = -i;
        }
        else
            glBegin (GL_TRIANGLE_STRIP);

        // draw each vertex of this group
        for (; i > 0; --i, pglcmds += 3)
        {
            packet = (md2_glcmd_t *)pglcmds;
            pframe1 = &frames[n];
            pframe2 = &frames[n + 1];
            pvert1 = &pframe1->verts[packet->index];
            pvert2 = &pframe2->verts[packet->index];
            // pass texture coordinates to OpenGL
            glTexCoord2f (packet->s, 1-packet->t);
            // interpolate normals
            n_curr = anorms_table[pvert1->normalIndex];
            n_next = anorms_table[pvert2->normalIndex];
            norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
            norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
            norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);
            glNormal3fv (norm);
            // interpolate vertices
            v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
            v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
            v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];
            v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
            v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
            v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];
            v[0] = v_curr[0] + interp * (v_next[0] - v_curr[0]);
            v[1] = v_curr[1] + interp * (v_next[1] - v_curr[1]);
            v[2] = v_curr[2] + interp * (v_next[2] - v_curr[2]);
            glVertex3fv (v);
        }
        glEnd ();
    }
}


void md2_model_t::init(const char *filename)
{
    GLfloat lightpos[] = { 5.0f, 10.0f, 0.0f, 1.0f };
    // init OpenGL
    glClearColor (0.5f, 0.5f, 0.5f, 1.0f);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    // init OpenGL light
    glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
    // load model file
    //mdl = (md2_model_t *)malloc (sizeof (md2_model_t));
    if ( !ReadMD2Model (filename))
        exit(-1);
}

void md2_model_t::shutdownApp()
{
    FreeModel();
}

void md2_model_t::reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (45.0, (GLfloat)w/(GLfloat)h, 0.01, 1000.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void md2_model_t::display(int n, int interp)
{
    // draw model
    // RenderFrame (n, md2file);
    // RenderFrameWithGLCmds (n, md2file);
    // RenderFrameItp (n, interp, md2file);
    if(afficher)
    {
        glScalef(0.25,0.25,0.25);
        RenderFrameItpWithGLCmds (n, interp);
    }
}

void md2_model_t::setTexture(Texture* t)
{
    m_texture=t;
}

Texture* md2_model_t::getTexture()
{
    return m_texture;
}

void md2_model_t::setAfficherRendu(bool r)
{
    afficher=r;
}


