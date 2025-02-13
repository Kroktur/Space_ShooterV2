#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "KT_Array.h"
int main() {
    KT::Array<int,3> test;
   
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

  
    sf::CircleShape circle(100);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(350, 250);  // Centr� environ

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("test.wav")) {
        std::cerr << "Erreur : Impossible de charger test.wav\n";
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();  // Joue le son

    sf::Music music;

    // Chargement de la musique � partir d'un fichier
    if (!music.openFromFile("path/to/your/music.ogg")) {
        std::cerr << "Erreur lors du chargement de la musique" << std::endl;
    }

    // D�marrer la musique
    music.play();

    // Attendre la fin de la musique
    while (music.getStatus() == sf::Music::Playing) {
        // Vous pouvez aussi mettre un petit d�lai si vous ne voulez pas bloquer le programme
        // Par exemple : sf::sleep(sf::seconds(0.1f));
    }

    std::cout << "La musique a �t� jou�e avec succ�s!" << std::endl;
  
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);  // Fond noir
        window.draw(circle);             // Dessiner le cercle
        window.display();                // Afficher le rendu
    }

    return 0;
}
