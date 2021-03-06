#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Vector3D.h"
#include "Object.h"

class Camera
{
    public:
    Camera();

    void setCible(Object *cible) { m_cible=cible; }
    void setPos(Vector3D position) { m_position=position; }
    Vector3D getPos() { return m_position; }
    Vector3D getDir() { return m_direction; }
    Vector3D getTarget() { return m_target; }
    Object* getCible() { return m_cible; }

    void look();
    void onMouseMotion(const SDL_MouseMotionEvent & event);

    void updateTime(double fonction_temps);
    void zoom(double z);

    double getAlpha() { return m_alpha; }
    double getBeta() { return m_beta; }
    void setMode(std::string m){m_mode=m;}
    std::string getMode() {return m_mode;}
    void setDist(double d){m_distToCible=d;}

    private:
    Vector3D m_position;
    Vector3D m_target;
    Vector3D m_direction;
    Object *m_cible;

    double ft;
    double m_alpha;
    double m_beta;
    double m_sensibility;
    std::string m_mode;

    double m_distToCible;
};


#endif // CAMERA_H_INCLUDED
