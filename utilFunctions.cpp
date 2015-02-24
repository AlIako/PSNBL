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

int myIntRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

double myDoubleRand(double min, double max)
{
    return (double) (min + ((float) rand() / RAND_MAX * (max - min + 1.000)));
}


std::string nameNoEnd(char* c, int size)
{
    std::string s="";
    for(int i=0;i<size;i++)
        if(c[i]!='\0')
            s+=c[i];
        else break;
    return s;
}
