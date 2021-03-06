#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
    TexRect* mushroom;
    Rect* projectile;
    
    TexRect* mangoPod;
    TexRect* battery;
    TexRect* battery1;
    TexRect* battery2;
    TexRect* battery3;
    TexRect* battery4;
    TexRect* battery5;
    TexRect* battery6;
    TexRect* battery7;
    TexRect* battery8;
    TexRect* battery9;
    Rect* hitBox;
    TexRect* backg;
    TexRect* backg1;
    TexRect* backg2;
    
    bool projectileVisible;
    bool mushroomVisible;
    bool up;
    bool left;
    bool hit;
    float theta;
    float deg;
    bool bounceUp;
    bool gravity;
    
    enum state{jump, down, dead};
    state podstate = down;
    
    int hangTime;
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    
    void action();

    ~Game();

};

#endif 
