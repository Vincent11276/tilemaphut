/*
MIT License

Copyright (c) 2021 Vincent

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iterator>
using namespace std;

#include "tilemaphut.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(608, 384), "tilemaphut - demo");
    window.setVerticalSyncEnabled(true);

    // Load the background image

    sf::Texture backgroundTxt;
    if (!backgroundTxt.loadFromFile("../Assets/craftpix-net-198222-free-industrial-zone-tileset-pixel-art/2 Background/Background.png"))
    {
        return (-1);
    }
    sf::Sprite background(backgroundTxt);
    background.setScale(1.2, 1.2);

    // Initialize our tile map data
    std::vector<std::vector<int>> tiledata
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
        {13, 14, 14, 14, 16, 32, 32, 32, 32, 02, 32, 32, 32, 32, 33, -1, -1, 13, 14}
    };

    TileMap tilemap(sf::Vector2f(19, 12), sf::Vector2f(32, 32));
    tilemap.loadFromDirectory("../Assets/craftpix-net-198222-free-industrial-zone-tileset-pixel-art/1 Tiles");
    tilemap.mapCellsFrom(tiledata);

    sf::Clock clock;

    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();

        int fps = 1 / delta;

        std::cout << fps << std::endl;

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

        window.draw(background);

        window.draw(tilemap);

        window.display();
    }


    return EXIT_SUCCESS;
}