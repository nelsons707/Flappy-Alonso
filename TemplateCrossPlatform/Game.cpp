#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string> 
using namespace std; 

#include "Game.h"

bool birdHasCollided = false;
bool resetGame = false; 

int attemptCount = 0;
int numOfFlaps = 0;
int highScore = 0;

void print(const char *text, int x, int y, int length)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}


Game::Game() {

	

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
	battery1 = new TexRect(batteryFileName, 0.1, 1.5, 1.25, 1.25);
	battery2 = new TexRect(batteryFileName, 1.0, -0.5, 1.25, 1.25);
	battery3 = new TexRect(batteryFileName, 1.0, 1.2, 1.25, 1.5);
	battery4 = new TexRect(batteryFileName, 1.9, 0.4, 1.25, 1.75);
	battery5 = new TexRect(batteryFileName, 1.9, 1.9, 1.25, 1.25);
	battery6 = new TexRect(batteryFileName, 2.7, -0.3, 1.25, 1.25);
	battery7 = new TexRect(batteryFileName, 2.7, 1.2, 1.25, 1.25);
	battery8 = new TexRect(batteryFileName, 3.7, 0.4, 1.25, 1.75);
	battery9 = new TexRect(batteryFileName, 3.7, 1.9, 1.25, 1.25);

	hitBox = new Rect(-0.4, -0.8, 0.25, 0.1);

	backg = new TexRect(backgFileName, -2, 1, 4, 2);
	backg1 = new TexRect(backgFileName, 2, 1, 4, 2);
	backg2 = new TexRect(backgFileName, 6, 1, 4, 2);

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

void Game::action() {

	if (resetGame = true) {
		birdHasCollided = false;
		resetGame = false;
		draw();							//not sure if this is the correct way of calling this
		numOfFlaps = 0;
		attemptCount++;
	}

	if (birdHasCollided == true) {

		//Pause game until user presses space again
		if (podstate == jump)
			resetGame = true;

	}

	else {

	
		float mx = 0.5;
		float my = 0;
		float jy = -0.0009;




		if (theta >= 2 * M_PI) theta = 0;
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
			if (hangTime > 0) {

				ypos += 0.001;
				mangoPod->setY(ypos);
				hangTime = hangTime - 1;
			}
			else {

				podstate = down;

			}
			break;



		}

		case down: {


			mangoPod->setY(jy + mangoPod->getY());

			if (mangoPod->contains(-0.4, -0.775)) {
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
			backg->setX(-2);
			backg1->setX(-6);
			backg2->setX(-6);

			break;


		}

		default:
			break;
		}



		if (podstate != dead) {

			if (battery->getX() <= -2.5) {
				battery->setX(1.8);
			}
			if (battery1->getX() <= -2.5) {
				battery1->setX(1.8);
			}
			if (battery2->getX() <= -2.5) {
				battery2->setX(1.8);
			}
			if (battery3->getX() <= -2.5) {
				battery3->setX(1.8);
			}
			if (battery4->getX() <= -2.5) {
				battery4->setX(1.8);
			}
			if (battery5->getX() <= -2.5) {
				battery5->setX(1.8);
			}
			if (battery6->getX() <= -2.5) {
				battery6->setX(1.8);
			}
			if (battery7->getX() <= -2.5) {
				battery7->setX(1.8);
			}
			if (battery8->getX() <= -2.5) {
				battery8->setX(1.8);
			}
			if (battery9->getX() <= -2.5) {
				battery9->setX(1.8);
			}

			battery->setX(-0.001 + battery->getX());
			battery1->setX(-0.001 + battery1->getX());
			battery2->setX(-0.001 + battery2->getX());
			battery3->setX(-0.001 + battery3->getX());
			battery4->setX(-0.001 + battery4->getX());
			battery5->setX(-0.001 + battery5->getX());
			battery6->setX(-0.001 + battery6->getX());
			battery7->setX(-0.001 + battery7->getX());
			battery8->setX(-0.001 + battery8->getX());
			battery9->setX(-0.001 + battery9->getX());

		}
		else {
			podstate = dead;
		}



		if (backg->getX() <= -6) {
			backg->setX(6);
		}
		if (backg1->getX() <= -6) {
			backg1->setX(6);
		}
		if (backg2->getX() <= -6) {
			backg2->setX(6);
		}

		backg->setX(backg->getX() - .001);
		backg1->setX(backg1->getX() - .001);
		backg2->setX(backg2->getX() - .001);



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
		backg1->draw(0.1);
		backg2->draw(0.1);

		mangoPod->draw(1.0);

		battery->draw(1.0);
		battery1->draw(1.0);
		battery2->draw(1.0);
		battery3->draw(1.0);
		battery4->draw(1.0);
		battery5->draw(1.0);
		battery6->draw(1.0);
		battery7->draw(1.0);
		battery8->draw(1.0);
		battery9->draw(1.0);

		hitBox->draw();

		string score = "Attempt: "; 
		string attempt = to_string(attemptCount);
		string currentScore = to_string(numOfFlaps);
		string highestScore = to_string(highScore);
		score.append(attempt);
		score.append("Score: ");
		score.append(currentScore);
		score.append(" High Score: ");
		score.append(highestScore);

		print(score.data(), 0, 0, 100); 



		//    static double someYOffset = 0.0;
		//    someYOffset += 0.1;
		//    if(someYOffset > 1000.0){
		//        backg->draw(0.1);
		//        someYOffset -= 1000.0;
		//
		//    }
		//    glTranslatef(someYOffset, 0.0f, 0.0f);


	}
	

void Game::handleKeyDown(unsigned char key, float x, float y) {
	if (key == ' ') {
		//up = true;
		//bounceUp = true;
		hangTime = 250;
		podstate = jump;
		numOfFlaps++;
		if (numOfFlaps > highScore)
			highScore = numOfFlaps;
	}
	else if (key == 'p') {
		stop();
	}
	else if (key == 'r') {
		start();
	}
}

Game::~Game() {
	stop();
	delete mushroom;
	delete explosion;
	delete projectile;
	delete mangoPod;
	delete battery;
	delete battery1;
	delete battery2;
	delete battery3;
	delete battery4;
	delete battery5;
	delete battery6;
	delete battery7;
	delete battery8;
	delete battery9;
	delete backg;
	delete backg1;
	delete backg2;
}

