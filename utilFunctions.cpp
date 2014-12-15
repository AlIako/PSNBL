#include "utilFunctions.h"


//fonction a ne PAS utiliser dans un parametre
//chaque char* attribué a cette fonction DOIT etre delete
char* stringtochar(std::string lestring)
{
    size_t size = lestring.size()+1;
    char * bufferpseudo = new char[ size ];
    // copier la chaîne
    strncpy( bufferpseudo, lestring.c_str(), size );
    return bufferpseudo;
}
