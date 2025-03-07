#include "SceneManager.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

//TODO
#include <conio.h>
#include <GameObject.h>
#include <iostream>
int main(int argc, char** argv) {
    SceneManager a(argv[0], 1920, 1080, "const std::string & title"/*,sf::Style::Fullscreen*/);
    a.AddScene(new Game(a.getWindow(),240,a.geTextureCash()));
    a.Exe();

}




