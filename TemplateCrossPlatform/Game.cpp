#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	const char* shroomFileName;
	const char* fireballFileName;
    const char* mangoPodFileName;
    const char* batteryFileName;
    const char* backgFileName;

	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	shroomFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/mushroom.png";
	fireballFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/fireball.bmp";
    mangoPodFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/mangopod.png";
    batteryFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/USBStick.png";
    backgFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/background.png";


	#else
	shroomFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/mushroom.png";
	fireballFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/fireball.bmp";
    mangoPodFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/mangopod.png";
    batteryFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/USBStick.png";
    backgFileName = "/Users/jasonrocha/Documents/CSE165Labs/TemplateCrossPlatform/background.png";


	#endif

    mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    explosion = new AnimatedRect(fireballFileName, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);
    mangoPod = new TexRect(mangoPodFileName, -0.4, 0.25, 0.25, 0.25);
    battery = new TexRect(batteryFileName, 0.1, 0.0, 1.25, 1.25);
    hitBox = new Rect(-0.4, -0.8, 0.25, 0.1);
    backg = new AnimatedRect(backgFileName, 1, 2, 200, true, true, -2, 1, 4, 2);
    
    up = false;
    left = true;
    projectileVisible = true;
    mushroomVisible = true;
    theta = 0;
    deg = 0;
    hit = false;
    gravity = true;
    
    setRate(1);
    start();
}

void Game::action(){
    float mx = 0.5;
    float my = 0;
    float jy = -0.0009;
   


    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    
//    if (left)
//        mx -= 0.0005;
//    else
//        mx += 0.0005;
//
//    if (mx < -1.6f){
//        left = false;
//    }
//    if (mx > 1.6 - mushroom->getW()){
//        left = true;
//    }
    
    
//    mushroom->setX(mx - mushroom->getW()/2);
//    mushroom->setY(my + mushroom->getH()/2);
//    
//    theta += 0.001;
//    deg += 0.1;
    
    switch (podstate) {
        case jump: {
            float ypos = mangoPod->getY();
            if(hangTime > 0){
                
                ypos += 0.001;
                mangoPod->setY(ypos);
                hangTime = hangTime - 1;
            }
            else{
                
                podstate = down;

            }
            break;
            
            
            
        }
            
        case down: {
            
            
            mangoPod->setY(jy + mangoPod->getY());
            
            if(mangoPod->contains(-0.4, -0.775)){
                std::cout << "stop";
                podstate = dead;
            }
            
            break;
            
            
        }
            
        case dead: {
            
//            float yposi = mangoPod->getY();
//            if(yposi == -0.5){
//                yposi = -0.5;
//                std::cout << "stopped";
//                mangoPod->setY(yposi);
//            }
            mangoPod->setY(-0.5);
            
            
            break;
            
            
        }
            
        default:
            break;
    }
    
    
    
    
    
    
//    mangoPod->setY(jy + mangoPod->getY());
//    
//    
//        if(bounceUp){
//        
//            float ypos = mangoPod->getY();
//            ypos += 0.001;
//            mangoPod->setY(ypos);
//            bounceUp = false;
//        
//        }


//    if (!hit && up){
//        float ypos = projectile->getY();
//        ypos +=0.005;
//        projectile->setY(ypos);
//
//        if (mushroom->contains(0, ypos-0.005)){
//            up = false;
//            hit = true;
//            projectileVisible = false;
//            mushroomVisible = false;
//            explosion->setX(mushroom->getX());
//            explosion->setY(mushroom->getY());
//            explosion->playOnce();
//        }
//    }
    
//    if (hit){
//        explosion->setY(explosion->getY()-0.0001);
//    }
}

void Game::draw() const {
    
//    if (projectileVisible){
//        projectile->draw();
//    }
//    if (mushroomVisible){
//        mushroom->draw(0.0);
//    }
    //explosion->draw(0.1);
    backg->draw(0.1);
    
    mangoPod->draw(1.0);
    
    battery->draw(1.0);
    
    hitBox->draw();
    
//    static double someYOffset = 0.0;
//    someYOffset += 0.1;
//    if(someYOffset > 1000.0){
//        backg->draw(0.1);
//        someYOffset -= 1000.0;
//
//    }
//    glTranslatef(someYOffset, 0.0f, 0.0f);
    
    
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
        //up = true;
        //bounceUp = true;
        hangTime = 250;
        podstate = jump;
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
}

Game::~Game(){
    stop();
    delete mushroom;
    delete explosion;
    delete projectile;
    delete mangoPod;
    delete battery;
    delete backg;
}
