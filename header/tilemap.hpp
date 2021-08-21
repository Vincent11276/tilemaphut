#pragma once

#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    std::vector<std::vector<int>> cells;

    sf::Vector2f cellSize;

public:
    TileMap(sf::Vector2f p_mapSize, sf::Vector2f p_cellSize);

    void clear();

    void remove(sf::Vector2i p_coords);
    
    void setCell(int id, sf::Vector2i p_coords);
    
    int getCell(sf::Vector2i p_coords);

    void resizeMap(sf::Vector2i p_size);

    sf::Vector2i getMapSize();

    std::vector<sf::Vector2i> getUsedCells(int id);

    std::vector<sf::Vector2i> getUsedCells();

    sf::Vector2i getUsedRect();

    sf::Vector2f worldToMap(sf::Vector2f p_coords);

    sf::Vector2i mapToWorld(sf::Vector2f p_coords);

    bool isInBounds(sf::Vector2i p_coords);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
};
