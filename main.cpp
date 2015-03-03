#include "Game.h"

/*
//template
template <typename T>
T myMax(T left, T right)
{
    return (left > right) ? left : right;
}
double bigger = myMax<double> (3.45,2.34);*/

int main ( int argc, char** argv )
{

    cerr<<"Start main"<<endl;
    srand (time(NULL));

    vector<int> test;

    test.clear();

    //test.erase(test.begin());

    for(unsigned int i=0;i<test.size();i++)
    {
        cerr<<"t:"<<test[i]<<endl;
    }

    //
    Game game;

    game.play();

    return 0;
}
