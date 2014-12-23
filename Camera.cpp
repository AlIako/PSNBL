#include "Camera.h"
#include <cmath>

Camera::Camera()
{
    m_cible=NULL;
    m_sensibility=0.1;
}

void Camera::updateTime(double fonction_temps)
{
    ft=fonction_temps;
}
void Camera::look()
{
    if(m_cible!=NULL)
    {
        m_position=m_cible->getPos()+Vector3D(0,0,1);

        double m_distance=1;
        m_target.X=m_position.X-m_distance*sin((90-m_beta)*M_PI/180)*cos(m_alpha*M_PI/180);
        m_target.Y=m_position.Y-m_distance*sin((90-m_beta)*M_PI/180)*sin(m_alpha*M_PI/180);
        m_target.Z=m_position.Z-m_distance*sin(m_beta*M_PI/180);
        m_direction=Vector3D(-cos(m_alpha*M_PI/180),-sin(m_alpha*M_PI/180),0);

        m_cible->setDir(m_direction);
        m_cible->setRot(Vector3D(0,0,(90-m_beta)));
        //m_target=m_position;
        //m_target.X+=5;
    }


    gluLookAt(m_position.X,m_position.Y,m_position.Z,
    m_target.X,m_target.Y,m_target.Z,
    0,0,1);
}
void Camera::setCible(Object *cible)
{
    m_cible=cible;
}
Vector3D Camera::getPos()
{
    return m_position;
}
Vector3D Camera::getDir()
{
    return m_direction;
}
Object* Camera::getCible()
{
    return m_cible;
}
void Camera::setPos(Vector3D position)
{
    m_position=position;
}

void Camera::onMouseMotion(const SDL_MouseMotionEvent & event)
{
    m_alpha -= event.xrel*m_sensibility;
    m_beta += event.yrel*m_sensibility;

    if (m_beta > 89)
        m_beta = 89;
    else if (m_beta < -89)
        m_beta = -89;

    if(m_alpha>=360)
        m_alpha=0;
    else if(m_alpha<=-360)
        m_alpha=0;
}


