#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3D.h"
#include "Object.h"

class Camera
{
    public:
    Camera();

    void setCible(Object *cible);
    void setPos(Vector3D position);
    Vector3D getPos();
    Vector3D getDir();
    Object* getCible();

    void look();
    void onMouseMotion(const SDL_MouseMotionEvent & event);

    void updateTime(double fonction_temps);

    private:
    Vector3D m_position;
    Vector3D m_target;
    Vector3D m_direction;
    Object *m_cible;

    double ft;
    double m_alpha;
    double m_beta;
    double m_sensibility;
};


#endif // CAMERA_H_INCLUDED
