#include "App.h"
#include "Game.h"


int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv, 1280, 800, "Flappy Juul");
    

    app->run();
}
