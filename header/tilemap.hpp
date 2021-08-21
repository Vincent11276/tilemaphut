#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_TILE_COUNT 256


class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    std::vector<std::vector<int>> cells;

    sf::Vector2f cellSize;

public:
    TileMap(sf::Vector2f p_mapSize, sf::Vector2f p_cellSize);

    void load(sf::Texture &p_tileSet, sf::Vector2f cellSize, bool append=true);

    void appendTile(sf::Texture &p_tile);

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
    sf::VertexArray     tileVertices;
    sf::RenderTexture   tileSet;
    uint32_t            tileCount;

    void setTileSet(int id, sf::Vector2i p_coords);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
};
