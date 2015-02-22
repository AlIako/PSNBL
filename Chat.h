#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include "Texte.h"
#include <vector>
#include "GTime.h"
#include "GSounds.h"

struct message
{
    std::string msg;
    GTime apparu;
    int user;
    Texte* text;
    int id;
};
class Chat
{
    public:
    Chat();
    void activate(int largeur, int hauteur, const char* t);
    void addMessage();
    void newMessage(string m, int iduser);
    void openTextBox(int iduser, double x);
    void openNeedString(string m="",double x=0.55);
    void redrawAll();
    void closeTextBox();
    void recieveMessage(const char* t, int id, int iduser);
    void checkKeyboard();
    void update();
    void draw();
    bool boxOpened();
    bool active();
    bool possedeId(int id,int iduser);
    bool vide(string s);
    void enterUp();
    void closeChat();
    void setSide(int side);
    void soundMsg();

    std::vector<message> msgToSend;
    message nextMessage;

    Gsounds* gsounds;
    GTime lastson;

    private:
    int m_side;
    bool up;
    std::vector<message> m_messages;
    int lastId;
    freetype::font_data m_font;
    int m_largeur;
    int m_hauteur;
    bool m_active;
    bool m_writing;
    int m_timeStay;//time a msg stay without disapearing
    SDL_Event event;
    Texte* barre;
    unsigned int curseur;
    GTime barreA;
    bool ons;
    int curuser;
};

#endif // CHAT_H_INCLUDED
