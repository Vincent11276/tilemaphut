#include "tilemaphut.hpp"


TileMap::TileMap(sf::Vector2f p_mapSize, sf::Vector2f p_cellSize)
    : cellSize(p_cellSize) 
{ 
    this->mapdata.resize(p_mapSize.y, std::vector<int>(p_mapSize.x, -1));

    this->tileVertices.resize(p_mapSize.x * p_mapSize.y * 4);
    this->tileVertices.setPrimitiveType(sf::Quads);

    if (!tileSet.create(cellSize.x * MAX_TILE_COUNT, cellSize.y))
    {
        std::cerr << "Unable to create the render-texture" << std::endl;
    }
    this->tileSet.clear(sf::Color::Transparent);
}

void TileMap::loadFromTexture(sf::Texture &p_tileSet, bool append)
{
    if (!append)
    {
        this->tileCount = 0;
        this->tileSet.clear();
    }

    for (uint32_t y = 0; y < p_tileSet.getSize().y / this->cellSize.y; y++)
    {
        for (uint32_t x = 0; x < p_tileSet.getSize().x / this->cellSize.x; x++)
        {
            sf::IntRect rect(x, y, this->cellSize.x, this->cellSize.y);
            
            sf::Sprite tile(p_tileSet, rect);

            tile.setPosition(this->tileCount++ * this->cellSize.x, 0);

            this->tileSet.draw(tile);
        }
    }
    this->tileSet.display();
}

void TileMap::loadFromDirectory(const std::string &path, bool append)
{
    // sort files in alphabetical order for correct mapping of tile id
    std::vector<std::filesystem::path> fileNames;

    std::copy(std::filesystem::directory_iterator(path), 
        std::filesystem::directory_iterator(), std::back_inserter(fileNames));

    std::sort(fileNames.begin(), fileNames.end());

    // load every path
    for (const std::string &path : fileNames) 
    {
        sf::Texture tile;

        if (!tile.loadFromFile(path))
        {
            std::cerr << "Unable to load tile texture from the path " << path << std::endl;
        }
        else this->loadFromTexture(tile);
    }
}

void TileMap::mapCellsFrom(std::vector<std::vector<int>> &p_cells)
{
    for (int y = 0; y < this->getMapSize().y; y++)
    {
        for (int x = 0; x < this->getMapSize().x; x++)
        {
            setCell(p_cells[y][x], sf::Vector2i(x, y));
        }
    }
}

void TileMap::clear()
{
    mapdata.clear();
}

sf::Vector2i TileMap::getMapSize()
{
    if (this->mapdata.size() > 0)
    {
        return sf::Vector2i(this->mapdata[0].size(), this->mapdata.size());
    }
    else return {0, 0};
}

// [TO-DO]: dynamic size

// void TileMap::resizeMap(sf::Vector2i p_size)
// {
//     for (auto &row: cells)
//     {
//         row.resize(p_size.x, -1);
//     }
//     this->cells.resize(p_size.y, std::vector<int>(p_size.x, -1));
// }

void TileMap::setCell(int id, sf::Vector2i p_coords)
{
    if (this->isInBounds(p_coords) && id < tileCount)
    {
        std::cout << id << std::endl;

        this->mapdata[p_coords.y][p_coords.x] = id;

        this->setTileVertices(id, p_coords);
    }
}

int TileMap::getCell(sf::Vector2i p_coords)
{
    if (this->isInBounds(p_coords))
    {
        return this->mapdata[p_coords.y][p_coords.x];
    }
    return -1;
}

void TileMap::remove(sf::Vector2i p_coords)
{
   this->setCell(-1, p_coords);
}

std::vector<sf::Vector2i> TileMap::getUsedCells(int id)
{
    std::vector<sf::Vector2i> usedCells;

    for (int32_t column = 0; column < this->mapdata.size(); column++)
    {
        for (int32_t row = 0; row < this->mapdata.size(); row++)
        {
            if (this->mapdata[column][row] == id)
            {
                usedCells.push_back(sf::Vector2i(row, column));
            }
        }
    }
    return usedCells;
}

std::vector<sf::Vector2i> TileMap::getUsedCells()
{
    std::vector<sf::Vector2i> usedCells;

    for (int32_t column = 0; column < this->mapdata.size(); column++)
    {
        for (int32_t row = 0; row < this->mapdata.size(); row++)
        {
            if (this->mapdata[column][row] != -1)
            {
                usedCells.push_back(sf::Vector2i(row, column));
            }
        }
    }
    return usedCells;
}

sf::Vector2i TileMap::getUsedRect()
{
    sf::Vector2i usedRect;

    for (uint32_t column = 0; column < this->mapdata.size(); column++)
    {
        for (uint32_t row = usedRect.x; row < this->mapdata.size(); row++)
        {
            if (this->mapdata[column][row] != -1 && usedRect.x < row)
            {
                usedRect = sf::Vector2i(row, column);
            }
        }
    }
    return usedRect;
}

sf::Vector2f TileMap::worldToMap(sf::Vector2f p_coords)
{
    return sf::Vector2f(p_coords.x * cellSize.x, p_coords.y * cellSize.y);
}

sf::Vector2i TileMap::mapToWorld(sf::Vector2f p_coords)
{
    return sf::Vector2i(p_coords.x / cellSize.x, p_coords.y / cellSize.y);
}

bool TileMap::isInBounds(sf::Vector2i p_coords)
{
    sf::Vector2i mapSize = getMapSize();

    return (p_coords.x >= 0) && (p_coords.x < mapSize.x) &&
        (p_coords.y >= 0) && (p_coords.y < mapSize.y);
}

void TileMap::setTileVertices(int id, sf::Vector2i p_coords)
{
    // get a pointer to the current tile's quad
    sf::Vertex* quad = &tileVertices[(p_coords.x + p_coords.y * getMapSize().x) * 4];

    // define its 4 corners
    quad[0].position = sf::Vector2f(p_coords.x * this->cellSize.x, p_coords.y * this->cellSize.y);
    quad[1].position = sf::Vector2f((p_coords.x + 1) * this->cellSize.x, p_coords.y * this->cellSize.y);
    quad[2].position = sf::Vector2f((p_coords.x + 1) * this->cellSize.x, (p_coords.y + 1) * this->cellSize.y);
    quad[3].position = sf::Vector2f(p_coords.x * this->cellSize.x, (p_coords.y + 1) * this->cellSize.y);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f((id - 1) * this->cellSize.x, 0);
    quad[1].texCoords = sf::Vector2f((id - 1) * this->cellSize.x + this->cellSize.x, 0);
    quad[2].texCoords = sf::Vector2f((id - 1) * this->cellSize.x + this->cellSize.x, this->cellSize.y);
    quad[3].texCoords = sf::Vector2f((id - 1) * this->cellSize.x, this->cellSize.y);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();

    states.texture = &this->tileSet.getTexture();

    target.draw(this->tileVertices, states);
}