#pragma once
#include "TileCoord.h"
#include "raylib.h"
#define MAP_WIDTH 32
#define MAP_HEIGHT 24

enum class Tile
{
	Floor = 0,
	Grass,
	Water,
	Restricted,
	Wall,
	Count
};

class Tilemap
{
public:
	float tilesizeX = 32;
	float tilesizeY = 32;
	Color tileColors[(int)Tile::Count];

	Tile tiles[MAP_WIDTH][MAP_HEIGHT];
	
	Vector2 GetScreenPositionOfTile(TileCoord coordinate)
	{
		return { coordinate.x * tilesizeX, coordinate.y * tilesizeY };
	}

	Tilemap()
	{
		tileColors[(int)Tile::Restricted] = RED;
		tileColors[(int)Tile::Grass] = GREEN;
		tileColors[(int)Tile::Water] = BLUE;
		tileColors[(int)Tile::Floor] = WHITE;
		tileColors[(int)Tile::Wall] = GRAY;
	}

	void Randomize()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				tiles[x][y] = (Tile)(rand() % (int)Tile::Water);
			}
		}
	}

	void PerlinNoise()
	{

	}

	void RandomizeArea()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				tiles[x][y] = (Tile::Water);
			}
		}
	}
	
	void Draw()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				Tile tileType = tiles[x][y];
				Color tileColor = tileColors[(int)tileType];
				DrawRectangle(x * tilesizeX, y * tilesizeY, tilesizeX, tilesizeY, tileColor);
			}
		}
	}
};
