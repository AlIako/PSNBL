#ifndef UTILFUNCTIONS_H_INCLUDED
#define UTILFUNCTIONS_H_INCLUDED
#include <string>
#include <SDL/SDL.h>


/*
std::ostringstream oss;
oss << "PSNBLAL " << AutoVersion::MAJOR;
oss.str();
*/


char* stringtochar(std::string lestring);
int myIntRand(int min, int max);
double myDoubleRand(double min, double max);
std::string nameNoEnd(char* c, int size);
char* endNoName(std::string s);

#endif // UTILFUNCTIONS_H_INCLUDED
