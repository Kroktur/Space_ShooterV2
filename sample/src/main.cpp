#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "KT_Array.h"
#include "SceneManager.h"
#include "Game.h"
#include <filesystem>
#include "TextureCache.h"
#include "RandomNumber.h"
int main(int argc, char** argv) {
    std::cout << argv[0] << std::endl;
    std::filesystem::path execFilePath(argv[0]);
    auto filepath = execFilePath.parent_path().parent_path().parent_path().parent_path().parent_path() / "Re" / "galaxie3.png";
    std::cout << filepath.string();
    SceneManager a(argv[0], 800, 800, "const std::string & title");
    a.AddScene(new Game(a.getWindow(),60,a.geTextureCash()));
    a.Exe();
    std::cout << UseRandomNumber().getRandomNumber(0,43);
    std::cout << UseRandomNumber().getRandomNumber(0, 43);
    std::cout << UseRandomNumber().getRandomNumber(0, 43);
    std::cout << UseRandomNumber().getRandomNumber(0, 43);
}
