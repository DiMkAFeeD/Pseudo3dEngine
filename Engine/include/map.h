#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <limits>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace pfe {
	class Map {
	public:
		class Wall {
		public:
			Wall(sf::Vector2f p, sf::Vector2f p1, sf::Color c, float th, float bh)
				: pos0(p), pos1(p1), color(c), topHeight(th), bottomHeight(bh){};
			sf::Vector2f pos0;
			sf::Vector2f pos1;
			sf::Color color;
			float topHeight, bottomHeight;
		};

		Map(std::string map);

		void AddWall(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Color& color, float bh, float th);

		void Draw(sf::RenderWindow& window);

		std::vector<std::pair<sf::Vector2f, Map::Map::Wall>> getRayIntersection(const sf::Vector2f& start, const sf::Vector2f& direction, float maxDist) const;
		
		void loadFromFile(const std::string& filePath);
		void saveToFile(const std::string& filePath);

	private:
			
		std::vector<Wall> walls;
		sf::VertexArray wallsInMap;
		std::vector<sf::RectangleShape> mapWalls;
	};
}