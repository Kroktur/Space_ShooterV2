#include "SceneManager.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

//TODO
#include <conio.h>
#include <GameObject.h>
#include <iostream>
int main(int argc, char** argv) {
    SceneManager a(argv[0], 1920, 1080, "const std::string & title"/*,sf::Style::Fullscreen*/);
    a.AddScene(new Game(a.getWindow(), 240, a.geTextureCash()));
    a.Exe();
}

//#include <SFML/Graphics.hpp>  // Si tu utilises la partie graphique de SFML
//#include <SFML/Window.hpp>    // Pour utiliser sf::Event
//
//        // Création de la fenêtre SFML
//    sf::RenderWindow window(sf::VideoMode(900, 900),"test");
//
//        // Création d'un cercle rouge
//        sf::CircleShape shape(50);
//        window.setView(shape);
//        shape.setFillColor(sf::Color::Red);
//        shape.setPosition(sf::Vector2f(375, 275));  // Position initiale au centre
//
//        // Vitesse de déplacement
//        float speed = 5.0f;
//
//        // Boucle principale
//        while (window.isOpen()) {
//            sf::Event event;
//            while (window.pollEvent(event)) {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//            }
//
//            // Gestion des touches pour le déplacement
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//                shape.move(0, -speed);  // Haut
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//                shape.move(0, speed);   // Bas
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//                shape.move(-speed, 0);  // Gauche
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//                shape.move(speed, 0);   // Droite
//
//            // Affichage
//            window.clear(sf::Color::Black);
//            window.draw(shape);
//            window.display();
//        }
//
//        return 0;
//
//
//}
//
//
//
//
//#include <SFML/Graphics.hpp>
//#include <vector>
//
//int main() {
//    // Créer une fenêtre SFML
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Map Example");
//
//    // Taille de la carte (largeur et hauteur de la carte en tiles)
//    const int mapWidth = 1600;
//    const int mapHeight = 1600;
//
//    // Taille de chaque "tile" (rectangle représentant une portion de la carte)
//    const int tileSize = 50;
//
//    // Créer une grille de rectangles (représentant la carte)
//    std::vector<sf::RectangleShape> tiles;
//    for (int i = 0; i < mapWidth / tileSize; ++i) {
//        for (int j = 0; j < mapHeight / tileSize; ++j) {
//            // Créer un rectangle représentant une tuile de la carte
//            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
//            tile.setPosition(i * tileSize, j * tileSize);
//
//            // Colorier les tuiles alternativement
//            if ((i + j) % 2 == 0)
//                tile.setFillColor(sf::Color(200, 200, 200));  // Gris clair
//            else
//                tile.setFillColor(sf::Color(100, 100, 100));  // Gris foncé
//
//            // Ajouter la tuile à la liste
//            tiles.push_back(tile);
//        }
//    }
//
//    // Créer un joueur (un cercle)
//    sf::CircleShape player(20);  // Rayon de 20 pixels
//    player.setFillColor(sf::Color::Green);
//    player.setPosition(800, 600);  // Placer le joueur initialement au centre de la fenêtre
//
//    // Créer la vue (elle commence centrée sur le joueur)
//    sf::View view(sf::FloatRect(0, 0, 800, 600));
//    window.setView(view);
//
//    // Vitesse de déplacement du joueur
//    float playerSpeed = 200.f;
//
//    sf::Clock clock;  // Pour mesurer le temps écoulé entre les frames (utile pour les mouvements indépendants du FPS)
//
//    while (window.isOpen()) {
//        sf::Time deltaTime = clock.restart();  // Temps écoulé entre chaque frame
//
//        // Gestion des événements
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Déplacer le joueur avec les touches directionnelles
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//            player.move(-playerSpeed * deltaTime.asSeconds(), 0);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//            player.move(playerSpeed * deltaTime.asSeconds(), 0);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//            player.move(0, -playerSpeed * deltaTime.asSeconds());
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//            player.move(0, playerSpeed * deltaTime.asSeconds());
//        }
//
//        // Déplacer la vue pour centrer sur le joueur
//        view.setCenter(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
//
//        // Appliquer la vue à la fenêtre
//        window.setView(view);
//
//        // Effacer la fenêtre avec une couleur de fond
//        window.clear(sf::Color::White);
//
//        // Dessiner la carte (les tuiles de la carte)
//        for (auto& tile : tiles) {
//            window.draw(tile);
//        }
//
//        // Dessiner le joueur (en avant-plan)
//        window.draw(player);
//
//        // Afficher le contenu de la fenêtre
//        window.display();
//    }
//
//    return 0;
//}
