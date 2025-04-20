#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include <map.h>
#include <player.h>

#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>

namespace Main {
	inline sf::RenderWindow window(sf::VideoMode({ 800, 600 }), L"Окно");
	inline sf::View view;
	inline sf::Clock clock;

	inline pfe::Map map("scene.json");
	inline pfe::Player player(sf::Vector2f(90, 60));

	inline sf::VertexArray bg;

	enum class Page {
		menu, editor, selectFile, view
	};
	inline Page page = Page::menu;

	void init();
	void Event();
	void Update();
	void Render();
	void Draw();
}