#include "Rope.h"
#define DISTANCE_MAX 40




Rope::Rope()
{
    m_block=true;

    m_hooked=false;
    m_physical=true;
    m_gravity=false;

    m_type="rope";
    linkedTo=NULL;

    m_speed=0.05;

    m_life=100;
}


void Rope::update(double functionTime)
{
    ft=functionTime;
    if(!m_hooked)
    {
        m_end=m_position;
        m_distance=distance2V(m_start,m_end);

        //collide
        if(m_collided)
        {
            damageCollided();
            if(collidedWithHookable())
            {
                //cerr<<"update hook"<<endl;
                m_hooked=true;
                m_velocity=Vector3D(0,0,0);
                m_physical=false;
                m_block=false;
                m_smallBoost=false;
                m_end=m_position;

                if(linkedTo!=NULL)
                    m_start=linkedTo->getPos();

                //cerr<<"distance: "<<m_distance<<endl;
            }
            else
            {
                m_life=0;
                unlink();
            }
        }
        //too far: kill
        if(m_distance>DISTANCE_MAX)
        {
            m_life=0;
            unlink();
        }
    }
    else
    {
        if(linkedTo==NULL)//if player isnt attached to rope anymore
        {
            //pulling up
            m_distance-=ft/2;
            if(m_distance<=0.1)
                m_distance=0.1;
            //and kill
            //if((m_end-simulLinked.getPos()).length()<=1)
            if(m_distance<=0.5)
                m_life=0;

            //simulate physics
            simulLinked.applyGravity();
            simulLinked.applyPhysics();

            if ((m_end-simulLinked.getPos()).length() > m_distance )
                simulLinked.setVel(simulLinked.getVel()+(m_end-simulLinked.getPos()).normalize()*ft/40);
        }
    }



    //update start pos
    if(linkedTo!=NULL)
        m_start=linkedTo->getPos();
    else//if player isnt attached to rope anymore
        m_start=simulLinked.getPos();
}

void Rope::setNowDistance()
{
    if(linkedTo!=NULL)
        m_distance=(m_end-linkedTo->getPos()).length();
}

void Rope::pullMe(Object* o)
{
    //pull your player
    double distToOutside=(m_end-o->getPos()).length()-m_distance;
    //distToOutside=(m_end-o->getPos()).length()-(m_distance-2);

    m_smallBoost=true;
    Vector3D dirToEnd=(m_end-o->getPos()).normalize();
    if (distToOutside>0)// we're past the end of our rope -> pull the avatar back in
    {
        Vector3D oldVel=o->getVel();
        double velNorm=oldVel.length();
        Vector3D newVel=o->getVel()+dirToEnd*ft/40*2;
        Vector3D newPos=o->getPos()+dirToEnd*distToOutside;

        //trouver la tangeante la plus proche de la vitesse
        //tangeante= intersetion du plan des tangeante avec plan de vitesse
        //plan = ax + by + cz = 0


        Vector3D rope=dirToEnd;
        Vector3D vit=o->getVel().normalize();
        Vector3D playerPos=o->getPos();
        //trouver plan de vitesse/rope
        /*(rope.x-vit.x)*(x-playerPos.x) + (rope.y-vit.y)*(y-playerPos.y) + (rope.z-vit.z)*(z-playerPos.z) = 0
        (rope.x-vit.x)*x + (rope.y-vit.y)*y + (rope.z-vit.z)*z
        +(rope.x-vit.x)*playerPos.x + (rope.y-vit.y)*playerPos.y + (rope.z-vit.z)*playerPos.z=0

        double a1=rope.X-vit.X;
        double b1=rope.Y-vit.Y;
        double c1=rope.Z-vit.Z;
        double d1=-((rope.X-vit.X)*playerPos.X + (rope.Y-vit.Y)*playerPos.Y + (rope.Z-vit.Z)*playerPos.Z);
        */
        /*
        (rope.Y*vit.Z-rope.Z*vit.Y)*(x-playerPos.X)+(rope.Z*vit.X-rope.X*vit.Z)(y-playerPos.Y)+(rope.X*vit.Y-rope.Y*vit.X)(z-playerPos.Z)=0
        */


        double a1=(rope.Y*vit.Z-rope.Z*vit.Y);
        double b1=(rope.Z*vit.X-rope.X*vit.Z);
        double c1=(rope.X*vit.Y-rope.Y*vit.X);
        double d1=-(a1*playerPos.X + b1*playerPos.Y + c1*playerPos.Z);



        //trouver plan des tangeantes

        /*
        (rope.y*vit.z-rope.z*vitesse.y)(x-playerPos.x)  +
         (rope.z*vitesse.x-rope.x*vitesse.z)(y-playerPos.y)  +
          (rope.x*vitesse.y-rope.y*vitesse.x)(z-playerPos.z)=0
        */
        double a2=rope.X;
        double b2=rope.Y;
        double c2=rope.Z;
        //double d2=-(a2*playerPos.X + b2*playerPos.Y + c2*playerPos.Z);


        //trouver intersection
        /*
        P1: a1x + b1y + c1z + d1 = 0
        P2: a2x + b2y + c2z + d2 = 0

        y = (-c1z -a1x -d1) / b1
        z = ((b2/b1)*(a1x+d1) -a2x -d2)/(c2 - c1*b2/b1)
        */
        Vector3D inter=Vector3D(0,0,0);
        /*inter.X=vit.X;
        inter.Z = ((b2/b1)*(a1*inter.X+d1) -a2*inter.X -d2)/(c2 - c1*b2/b1);
        inter.Y = (-c1*inter.Z -a1*inter.X -d1) / b1;*/

        inter.X=b1*c2 - c1*b2;
        inter.Y =a2*c1 - c2*a1;
        inter.Z = a1*b2 - b1*a2;

        inter=inter.normalize();

        //choisir celui le plus proche de vitesse
        Vector3D interInverse=-1*inter;

        if((inter-vit).length()<(interInverse-vit).length())
            newVel=inter;
        else newVel=interInverse;



        //Tracer::getInstance()->trace("rope","tan:"+newVel.toString(),300,0);
        std::stringstream ss;
        ss << "a1: "<< a1 <<", b1: " << b1 << ", c1: " << c1 << ", d1: " << d1;
        //Tracer::getInstance()->trace("rope",ss.str(),100,0);

        /*std::stringstream ss2;
        ss2 << "a2: "<< a2 <<", b2: " << b2 << ", c2: " << c2 << ", d2: " << d2;
        Tracer::getInstance()->trace("rope",ss2.str(),1000,1);*/







        newVel/=3.0;

        //apply
        o->setVel(newVel.normalize()*velNorm);
        //o->setVel((o->getVel()+newVel.normalize()*velNorm).normalize()*velNorm);

        if(m_smallBoost)//dont teleport back at first, we want the player to have a small boost
        {
            Vector3D savePos=o->getPos();

            double oldDis=(o->getPos()-m_end).length();
            //o->setPos(o->getPos()+rope*distToOutside/200.0);//move progressively to center, not instantly
            o->setPos(o->getPos()+rope*distToOutside);

            stringstream ss;
            ss <<"dist: "<<oldDis<<"->"<<(o->getPos()-m_end).length();

            Tracer::getInstance()->trace("rope",ss.str(),100,1);

            if(!Collision::getInstance()->testCollision(o))
            {
                setPos(newPos);
                m_start=newPos;
            }
            else
            {
                //Tracer::getInstance()->trace("rope","setpos denied.");
                o->setPos(savePos);
            }
        }
    }
    else m_smallBoost=true;//player back in->small boost finished

    //o->setVel(o->getVel()+ft*dirToEnd/100.0);
}
void Rope::pullUp()
{
    //cerr<<"pull up rope: "<< m_distance << endl;
    m_distance-=ft/10.0;
    if(m_distance<1)
        m_distance=1;
}
void Rope::pullDown()
{

}


void Rope::unlink()
{
    /*if(linkedTo!=NULL)
        simulLinked=*linkedTo;*/

    linkedTo=NULL;
}

void Rope::ini()
{
    m_type="rope";
    if(GTexture::getInstance()!=NULL)
    {
        GTexture::getInstance()->addTexture("../data/textures/rope.jpg");
        m_texture=GTexture::getInstance()->getTexture("../data/textures/rope.jpg");
    }

    m_size=Vector3D(0.05,0.05,0.05);
}


void Rope::ini(Vector3D start, Vector3D dir)
{
    ini();

    m_position=start;
    m_start=start;
    m_direction=dir;


    m_velocity=m_direction;

}

void Rope::draw()
{
    if(linkedTo!=NULL)
    {
        glEnable(GL_CULL_FACE);

        const Vector3D m_taille=m_size;
        const double mosaic=0.5;

        glColor3ub(255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();

        double distance=distance2V(m_start,m_end);
        //double distance=2;

        glPushMatrix();

        glBegin(GL_QUADS);
        glNormal3d(0.0,1.0,0.0);
        glTexCoord2d(0,distance/mosaic);                                 glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(0,0);                                                      glVertex3d(m_start.X+m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,0);                                                           glVertex3d(m_start.X-m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,distance/mosaic);                                                                        glVertex3d(m_end.X-m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);

        glNormal3d(1.0,0.0,0.0);
        glTexCoord2d(0,distance/mosaic);                                          glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(0,0);             glVertex3d(m_start.X+m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,0);                                         glVertex3d(m_start.X+m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,distance/mosaic);                                                                     glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);

        glNormal3d(0.0,-1.0,0.0);
        glTexCoord2d(0,distance/mosaic);                                      glVertex3d(m_end.X-m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(0,0);                                                                  glVertex3d(m_start.X-m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,0);                              glVertex3d(m_start.X+m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,distance/mosaic);    glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);

        glNormal3d(-1.0,0.0,0.0);
        glTexCoord2d(0,distance/mosaic);                                    glVertex3d(m_end.X-m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(0,0);                                                                 glVertex3d(m_start.X-m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,0);                                  glVertex3d(m_start.X-m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,distance/mosaic);    glVertex3d(m_end.X-m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);



        glNormal3d(0.0,0.0,1.0);
        glTexCoord2d(0,1);    glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(0,0);    glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(1,0);    glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);
        glTexCoord2d(1,1);    glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);



        glNormal3d(0.0,0.0,-1.0);
        glTexCoord2d(0,1);    glVertex3d(m_start.X+m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,1);    glVertex3d(m_start.X+m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(1,0);    glVertex3d(m_start.X-m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
        glTexCoord2d(0,0);    glVertex3d(m_start.X-m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);

        glEnd();

        glPopMatrix();

        glDisable(GL_CULL_FACE);
    }
}


void Rope::damageCollided()
{
    //Effects::getInstance()->addExplosion(m_position);

    for(unsigned int i=0;i<m_colliding.size();i++)
    {
        if(m_colliding[i]->getType()=="boss")
        {
            m_colliding[i]->loseLife(10);
        }
    }
}

