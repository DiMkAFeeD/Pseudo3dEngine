#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include <map.h>
#include <player.h>

namespace Main {
	inline sf::RenderWindow window(sf::VideoMode({ 800, 600 }), L"Окно");
	inline sf::View view;
	inline sf::Clock clock;

	inline Map::Map map("scene.json");
	inline Player::Player player(sf::Vector2f(90, 60));

	inline sf::VertexArray bg;

	void init();
	void Event();
	void Update();
	void Render();
	void Draw();
}