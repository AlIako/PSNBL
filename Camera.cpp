#include "Camera.h"
#include <cmath>

Camera::Camera()
{
    m_cible=NULL;
    m_sensibility=0.1;

    m_mode="play";

    m_distToCible=7;

    m_target=Vector3D(0,0,0);
    m_position=Vector3D(0,0,0);
    m_direction=Vector3D(1,1,1);

    ft=0;
    m_beta=0;

    m_alpha=270;
}

void Camera::updateTime(double fonction_temps)
{
    ft=fonction_temps;
}
void Camera::look()
{
    if(m_mode=="play")
    {
        if(m_cible!=NULL)
        {
            m_position=m_cible->getPos()+Vector3D(0,0,1)+Vector3D(0,0,1);

            double m_distance=1;
            m_target.X=m_position.X-m_distance*sin((90-m_beta)*M_PI/180)*cos(m_alpha*M_PI/180);
            m_target.Y=m_position.Y-m_distance*sin((90-m_beta)*M_PI/180)*sin(m_alpha*M_PI/180);
            m_target.Z=m_position.Z-m_distance*sin(m_beta*M_PI/180);
            m_direction=Vector3D(-cos(m_alpha*M_PI/180),-sin(m_alpha*M_PI/180),0);
            m_cible->setDir(m_direction);
            m_cible->setRot(Vector3D(0,0,(90-m_beta)));
        }


        gluLookAt(m_position.X,m_position.Y,m_position.Z,
        m_target.X,m_target.Y,m_target.Z,
        0,0,1);
    }
    else if(m_mode.find("spectate")!=string::npos || m_mode.find("editor")!=string::npos)
    {
        if(m_cible!=NULL)
        {
            m_position=m_cible->getPos()+Vector3D(0,0,1);

            m_target.X=m_position.X-m_distToCible*sin((90-m_beta)*M_PI/180)*cos(m_alpha*M_PI/180);
            m_target.Y=m_position.Y-m_distToCible*sin((90-m_beta)*M_PI/180)*sin(m_alpha*M_PI/180);
            m_target.Z=m_position.Z-m_distToCible*sin(m_beta*M_PI/180);
            m_direction=Vector3D(-cos(m_alpha*M_PI/180),-sin(m_alpha*M_PI/180),0);
        }
        m_direction=(m_target-m_position).normalize();
        gluLookAt(m_position.X-m_direction.X*m_distToCible,m_position.Y-m_direction.Y*m_distToCible,m_position.Z-m_direction.Z*m_distToCible,
        m_position.X,m_position.Y,m_position.Z,
        0,0,1);
    }
    else
    {
        gluLookAt(5,2,1,
        1,2,0,
        0,0,1);
    }
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


void Camera::zoom(double z)
{
    m_distToCible-=z;
    if(m_distToCible<abs(z))
        m_distToCible=0.1;
}

