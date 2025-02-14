#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "KT_Array.h"
#include "SceneManager.h"
#include "Game.h"
#include <filesystem>
#include "TextureCache.h"
int main(int argc, char** argv) {
    std::cout << argv[0] << std::endl;
    std::filesystem::path execFilePath(argv[0]);
    auto filepath = execFilePath.parent_path().parent_path().parent_path().parent_path().parent_path() / "Re" / "galaxie3.png";
    std::cout << filepath.string();
    SceneManager a( 800, 800, "const std::string & title");
    a.AddScene(new Game(a.getWindow(),60,new TextureCache(/*argv[0]*/)));
    a.Exe();
    KT::Array<int,3> test;
   
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
 
  
    sf::CircleShape circle(100);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(350, 250);  // Centré environ

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("test.wav")) {
        std::cerr << "Erreur : Impossible de charger test.wav\n";
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();  // Joue le son

    sf::Music music;

    // Chargement de la musique à partir d'un fichier
    if (!music.openFromFile("path/to/your/music.ogg")) {
        std::cerr << "Erreur lors du chargement de la musique" << std::endl;
    }

    // Démarrer la musique
    music.play();

    // Attendre la fin de la musique
    while (music.getStatus() == sf::Music::Playing) {
        // Vous pouvez aussi mettre un petit délai si vous ne voulez pas bloquer le programme
        // Par exemple : sf::sleep(sf::seconds(0.1f));
    }

    std::cout << "La musique a été jouée avec succès!" << std::endl;
  
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
    std::cout << "je test ma super mega branche qui tue" << std::endl;
    return 0;
}
