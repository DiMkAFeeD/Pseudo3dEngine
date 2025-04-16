#pragma once

#include <SFML/Graphics.hpp>

#include <math.h>

#include <map.h>

namespace Camera {
	class Camera {
	public:
		Camera(sf::Angle fov, int rays, float lenght, float stepRay);

		void UpdateInfo(sf::Vector2f position, sf::Angle rotation);

		void DrawMinimapView(sf::RenderWindow& window);
		void DrawCameraView(sf::RenderWindow& window);

		void updateNumRays(const int& numRays) { this->numRays = numRays; }

		void Render(const sf::Vector2u& windowSize, const Map::Map& map);
	private:
		void castRayDefault(const sf::Angle& direction, int iRay, const sf::Vector2u& windowSize, const Map::Map& map);
		void castRaySectionMethod(const sf::Angle& direction, int iRay, const sf::Vector2u& windowSize, const Map::Map& map);

		void drawLine(const float& lenght, const Map::Map::Wall& wall ,const int& iRay, const sf::Vector2u& windowSize);

		sf::Vector2f position;
		sf::Angle rotation;

		sf::Angle FOV = sf::degrees(45);
		int numRays;
		float rayLenght;
		float rayStep;

		sf::VertexArray minimapView;
		sf::VertexArray cameraView;
	};
}