#pragma once

#include <SFML/Graphics.hpp>

#include <math.h>

#include <camera.h>

namespace pfe {
	class Player {
	public:
		Player(sf::Vector2f pos);

		void setPosition(const sf::Vector2f& newPos) { position = newPos; }

		void Movement(sf::RenderWindow& window);
		void CameraRender(const sf::Vector2u& windowSize, const pfe::Map& map);
		void Draw(sf::RenderWindow& window);
		void DrawCameraView(sf::RenderWindow& window);

		void UpdateNumRaysCamera(const int& num) { camera.updateNumRays(num); }
	private:
		pfe::Camera camera;

		float speed = 10;
		float sensity = .7f;

		sf::Vector2f position;
		sf::Angle rotation;

		sf::CircleShape playerShape;
		sf::VertexArray dirLine;

		sf::Vector2i lastMousePos;
	};
}