#include "TextManager.h"

TextManager* TextManager::m_instance = new TextManager();


TextManager* TextManager::getInstance()
{
    return m_instance;
}


TextManager::TextManager()
{

}


void TextManager::ini()
{
    m_font.init("../data/fonts/arial.TTF", 16);
}
