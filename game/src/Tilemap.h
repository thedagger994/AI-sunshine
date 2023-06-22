#pragma once
#include "TileCoord.h"
#include "raylib.h"
#include "Tilemap2.h"
#include "imgui.h"
#include <vector>
#include <queue>
#include <limits>
#define MAP_WIDTH 32
#define MAP_HEIGHT 24

struct Node
{
	TileCoord position;
	int distance;

	bool operator<(const Node& other) const
	{
		return distance > other.distance;
	}
};

enum class Tile
{
	Floor = 0,
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
		tileColors[(int)Tile::Floor] = WHITE;
		tileColors[(int)Tile::Wall] = GRAY;
	}

	void GenerateFromImage(Image image, int waterThreshold, int mountainThreshold)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				float u = x / (float)MAP_WIDTH;
				float v = y / (float)MAP_HEIGHT;
				tiles[x][y] = (Tile)(rand() % (int)Tile::Count);
				Color color = GetImageColor(image, u*image.width, v*image.height);

				Tile tile = Tile::Count;
				if (color.r > waterThreshold) tile = Tile::Count;
				if (color.r > mountainThreshold) tile = Tile::Wall;
				tiles[x][y] = tile;
			}
		}
	}

	void Randomize()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{

				tiles[x][y] = (Tile)(rand() % (int)Tile::Count);
			}
		}
	}

	void RandomizeArea(int randChance = 50)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				tiles[x][y] = (Tile::Floor);

				if ((rand() % 101) < randChance)
				{
					tiles[x][y] = (Tile::Wall);
				}
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


	bool ContainsTile(TileCoord tilePosition)
	{
		return tilePosition.x >= 0 && tilePosition.x < MAP_WIDTH &&
			tilePosition.y >= 0 && tilePosition.y < MAP_HEIGHT;
	}

	bool IsTraversableAt(TileCoord tilePosition)
	{
		if (ContainsTile(tilePosition))
		{
			Tile tile = tiles[tilePosition.x][tilePosition.y];
			// Implement your own logic to determine if the tile is traversable

			return tile != Tile::Wall;
		}
		return false;
	}

	std::vector<TileCoord> GetTraversableTilesAdjacentTo(TileCoord tilePos)
	{
		std::vector<TileCoord> adjacentTiles;
		// Implement the logic to find and add adjacent traversable tiles

		// Example implementation: assuming 8-directional movement
		int x = tilePos.x;
		int y = tilePos.y;

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (dx == 0 && dy == 0)
					continue; // Skip the current tile

				TileCoord adjacentTile = { x + dx, y + dy };

				if (ContainsTile(adjacentTile) && IsTraversableAt(adjacentTile))
					adjacentTiles.push_back(adjacentTile);
			}
		}

		return adjacentTiles;
	}

	int GetCostForTile(Tile tile)
	{
	    // Define the cost for each tile type
	    switch (tile)
	    {
	        case Tile::Floor:
	            return 1;  // Cost for a floor tile
	        case Tile::Wall:
	            return -1; // Cost for a wall tile
	        default:
	            return 0;  // Default cost for unknown tile types
	    }
	}
	
	std::vector<TileCoord> Dijkstra(TileCoord start, TileCoord goal)
	{
		std::priority_queue<Node> pq;
		std::vector<int> distance(MAP_WIDTH * MAP_HEIGHT, std::numeric_limits<int>::max());
		std::vector<TileCoord> previous(MAP_WIDTH * MAP_HEIGHT, { -1, -1 });
		std::vector<TileCoord> path;

		pq.push({ start, 0 });
		distance[start.y * MAP_WIDTH + start.x] = 0;

		Node current = pq.top();
		while (!pq.empty())
		{
			pq.pop();

			if (current.position == goal)
				break;

			std::vector<TileCoord> adjacentTiles = GetTraversableTilesAdjacentTo(current.position);

			for (const auto& tile : adjacentTiles)
			{
				int cost = GetCostForTile(tiles[tile.x][tile.y]);
				int newDistance = current.distance + cost;

				if (newDistance < distance[tile.y * MAP_WIDTH + tile.x])
				{
					distance[tile.y * MAP_WIDTH + tile.x] = newDistance;
					previous[tile.y * MAP_WIDTH + tile.x] = current.position;
					pq.push({ tile, newDistance });
				}
			}
		}
		if (current.position == goal)
		// Reconstruct path from goal to start
		TileCoord current = goal;
		while (current != start)
		{
			path.push_back(current);
			current = previous[current.y * MAP_WIDTH + current.x];
		}

		path.push_back(start);
		std::reverse(path.begin(), path.end());

		return path;
	}
};
