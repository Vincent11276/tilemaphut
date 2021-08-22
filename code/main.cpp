#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iterator>
using namespace std;

#include "tilemap.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(608, 384), "tilemaphut - demo");

    // Load the background image

    sf::Texture backgroundTxt;
    if (!backgroundTxt.loadFromFile("../Assets/craftpix-net-198222-free-industrial-zone-tileset-pixel-art/2 Background/Background.png"))
    {
        return (-1);
    }
    sf::Sprite backgroundSpr(backgroundTxt);
    backgroundSpr.setScale(1.2, 1.2);

    // Initialize our tile map data

    std::vector<std::vector<int>> middleGround
    {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {04, 06, -1, -1, 04, 71, 05, 36, 71, 06, -1, -1, -1, -1, 04, 04, 04, 04, 04},
        {22, 24, -1, -1, 22, 23, 23, 23, 23, 24, 62, 62, 62, 62, 22, 23, 23, 23, 23},
        {-1, -1, -1, -1, -1, -1, -1, 70, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {04, 05, 36, 36, 06, -1, -1, 74, 75, 75, 75, 75, 75, 75, 76, -1, -1, 04, 05},
        {13, 14, 14, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 14},
        {13, 14, 14, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 14},
        {13, 14, 14, 14, 16, 32, 32, 32, 32, 2, 32, 32, 32, 32, 33, -1, -1, 13, 14}
    };

    TileMap tilemap(sf::Vector2f(19, 12), sf::Vector2f(32, 32));
    tilemap.loadFromDirectory("../Assets/craftpix-net-198222-free-industrial-zone-tileset-pixel-art/1 Tiles");
    tilemap.mapCellsFrom(middleGround);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }
        window.clear(sf::Color(97, 22, 86));

        window.draw(backgroundSpr);

        window.draw(tilemap);

        window.display();
    }


    return EXIT_SUCCESS;
}