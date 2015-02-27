#include "Crosshair.h"

Crosshair::Crosshair()
{
}

void Crosshair::ini()
{

}

void Crosshair::draw()
{

    Video::getInstance()->matrixOrtho2D();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    double sq=0.002;
    glColor4ub(155,155,155,255);
    glBegin(GL_QUADS);
        glTexCoord2d(1,0);    glVertex2d(0.5-sq,0.5-sq);
        glTexCoord2d(1,1);    glVertex2d(0.5-sq,0.5+sq);
        glTexCoord2d(0,1);    glVertex2d(0.5+sq,0.5+sq);
        glTexCoord2d(0,0);    glVertex2d(0.5+sq,0.5-sq);
    glEnd();



    glEnable(GL_TEXTURE_2D);

    Video::getInstance()->matrixProjection();
}


void Crosshair::update(double functionTime)
{
}
