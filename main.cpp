#include <SFML/Graphics.hpp>
using namespace std;


class TileMap
{
public:
    pass
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Chess Game - Beta");

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

        window.display();
    }


    return EXIT_SUCCESS;
}