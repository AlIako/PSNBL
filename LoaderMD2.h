#ifndef LOADERMD2_H_INCLUDED
#define LOADERMD2_H_INCLUDED
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <dirent.h>
#include "GTexture.h"
#include <string>
#include "sdlglutils.h"

// vector
typedef float vec3_t[3];/* Table of precalculated normals */


// md2 header
typedef struct
{
  int ident;
  int version;

  int skinwidth;
  int skinheight;

  int framesize;

  int num_skins;
  int num_vertices;
  int num_st;
  int num_tris;
  int num_glcmds;
  int num_frames;

  int offset_skins;
  int offset_st;
  int offset_tris;
  int offset_frames;
  int offset_glcmds;
  int offset_end;
} md2_header_t;
// texture name
typedef struct
{
  char name[64];
} md2_skin_t;
// texture coords
typedef struct
{
  short s;
  short t;
} md2_texCoord_t;
//triangle info
typedef struct
{
  unsigned short vertex[3];
  unsigned short st[3];
} md2_triangle_t;
// compressed vertex
typedef struct
{
  unsigned char v[3];
  unsigned char normalIndex;
} md2_vertex_t;
// model frame
typedef struct
{
  vec3_t scale;
  vec3_t translate;
  char name[16];
  md2_vertex_t *verts;
} md2_frame_t;
//gl command packet
typedef struct
{
  float s;
  float t;
  int index;
} md2_glcmd_t;

class md2_model_t
{
    public:
    md2_model_t();
    void getTexture(const char *filename);
    int ReadMD2Model (const char *filename);
    void FreeModel();
    void RenderFrame (int n);
    void RenderFrameItp (int n, float interp);
    void RenderFrameWithGLCmds (int n);
    void RenderFrameItpWithGLCmds (int n, float interp);
    void Animate (int start, int end, int *frame, float *interp);
    void init (const char *filename);
    void shutdownApp ();
    void reshape (int w, int h);
    void display (int n, int interp);
    void setTexture(Texture* t);
    Texture* getTexture();

    void setAfficherRendu(bool r);

    string repertoire;

    int cur_frame;
    md2_header_t header;
    bool text;

    private:
    bool afficher;
    md2_skin_t *skins;
    md2_texCoord_t *texcoords;
    md2_triangle_t *triangles;
    md2_frame_t *frames;
    int *glcmds;
    GLuint tex_id;
    Texture *m_texture;
};

#endif // HDF_H_INCLUDED
