#include "tilemap.hpp"


Tilemap::TileMap(sf::Vector2f p_mapSize, sf::Vector2f p_cellSize)
    : cellSize(p_cellSize) 
{ 
    cells.resize(p_mapSize.y, std::vector<int>(p_mapSize.x, -1));
}

sf::Vector2i Tilemap::getMapSize()
{
    if (this->cells.size() > 0)
    {
        return sf::Vector2i(this->cells[0].size(), this->cells.size());
    }
    else return {0, 0};
}

void Tilemap::esizeMap(sf::Vector2i p_size)
{
    for (auto &row: cells)
    {
        row.resize(p_size.x, -1);
    }
    this->cells.resize(p_size.y, std::vector<int>(p_size.x, -1));
}

void Tilemap::clear()
{
    cells.clear();
}

void Tilemap::setCell(int id, sf::Vector2i p_coords)
{
    if (this->isInBounds(p_coords))
    {
        this->cells[p_coords.y][p_coords.x] = id;
    }
}

int Tilemap::getCell(sf::Vector2i p_coords)
{
    if (this->isInBounds(p_coords))
    {
        return this->cells[p_coords.y][p_coords.x];
    }
}
void Tilemap::remove(sf::Vector2i p_coords)
{
    setCell(-1, p_coords);
}

std::vector<sf::Vector2i> Tilemap::getUsedCells(int id)
{
    std::vector<sf::Vector2i> usedCells;

    for (int32_t column = 0; column < this->cells.size(); column++)
    {
        for (int32_t row = 0; row < this->cells.size(); row++)
        {
            if (this->cells[column][row] == id)
            {
                usedCells.push_back(sf::Vector2i(row, column));
            }
        }
    }
    return usedCells;
}

std::vector<sf::Vector2i> Tilemap::getUsedCells()
{
    std::vector<sf::Vector2i> usedCells;

    for (int32_t column = 0; column < this->cells.size(); column++)
    {
        for (int32_t row = 0; row < this->cells.size(); row++)
        {
            if (this->cells[column][row] != -1)
            {
                usedCells.push_back(sf::Vector2i(row, column));
            }
        }
    }
    return usedCells;
}

sf::Vector2i Tilemap::getUsedRect()
{
    sf::Vector2i usedRect;

    for (uint32_t column = 0; column < this->cells.size(); column++)
    {
        for (uint32_t row = usedRect.x; row < this->cells.size(); row++)
        {
            if (this->cells[column][row] != -1 && usedRect.x < row)
            {
                usedRect = sf::Vector2i(row, column);
            }
        }
    }
    return usedRect;
}

sf::Vector2f Tilemap::worldToMap(sf::Vector2f p_coords)
{
    return sf::Vector2f(p_coords.x * cellSize.x, p_coords.y * cellSize.y);
}

sf::Vector2i Tilemap::mapToWorld(sf::Vector2f p_coords)
{
    return sf::Vector2i(p_coords.x / cellSize.x, p_coords.y / cellSize.y);
}

bool Tilemap::isInBounds(sf::Vector2i p_coords)
{
    sf::Vector2i mapSize = getMapSize();

    return (p_coords.x > mapSize.x) && (p_coords.x < mapSize.x) &&
        (p_coords.y > mapSize.y) && (p_coords.y < mapSize.y);
}

virtual void Tilemap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}