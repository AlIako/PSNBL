#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED
#include <SDL.h>
#include <GL/glew.h>
#include "Video.h"
#include "Online.h"
#include "Map.h"
#include "Camera.h"
#include "GTime.h"
#include "Interface.h"
#include "SpellRope.h"
#include "Chat.h"
#include "Interaction.h"

using namespace std;

class Editor
{
    public:
    Editor();

    void ini(string path);
    void iniInterf();
    void draw(bool toPick=false);
    void play(string path);
    void updateTimes();

    void handleTracer();
    void moveObj(Vector3D key);
    string choseFile(string what,string c, bool fullname, string type1, string type2="", string type3="");
    int entrerNombre(int erg);
    string entrerString(string *m);
    Vector3D modifVector(Vector3D *v, string nom, double pas);
    Vector3D modifVector(Vector3D v, string nom, double pas);


    void processHits(GLint hits, GLuint buffer[]);
    void pick(double x, double y);

    void menuObj();


    void close();
    ~Editor();

    private:
    string m_path;

    bool playLoop;
    bool fadingToLeave;

    Video* m_video;
    Camera m_camera;
    Chat m_chat;

    std::vector<Object*>* m_objects;
    int objSelected;

    GTime since_last_frame;
    double ft;//function time

    vector<Button> interf_editor;
    vector<Button> buttons;
    bool touchebouton;
    bool justgrab;
    bool grabCursor;
    Interaction interaction;

    int m_fps;
    GTime m_fpsTime;
    double yboutonstexture;

    Vector3D posCur;
    Object* curObj;
    bool showCur;
};


#endif // EDITOR_H_INCLUDED
