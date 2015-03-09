#include "SpellJump.h"



SpellJump::SpellJump()
{
    m_name="jump";
    m_required="nothing";
    m_cooldown=100;

    m_position.Y+=0.1;
}



