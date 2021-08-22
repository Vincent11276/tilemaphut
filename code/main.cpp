#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iterator>
using namespace std;

#include "tilemap.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "tilemaphut - demo");

    TileMap tilemap(sf::Vector2f(25, 25), sf::Vector2f(32, 32));

    tilemap.loadFromDirectory("/home/vitalityedge42/Documents/GitHub/tilemaphut/Assets/craftpix-net-198222-free-industrial-zone-tileset-pixel-art/1 Tiles");

    tilemap.setCell(2, sf::Vector2i(5, 5));

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

        window.draw(tilemap);

        window.display();
    }


    return EXIT_SUCCESS;
}