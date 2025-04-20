#include <player.h>

pfe::Player::Player(sf::Vector2f pos) 
	: position(pos), playerShape(sf::CircleShape(3)), dirLine(sf::VertexArray(sf::PrimitiveType::Lines, 2)), 
	camera(Camera::Camera(sf::degrees(90), 1000, 200, 2))
{
	playerShape.setFillColor(sf::Color::Red);
	dirLine[0].color = sf::Color::Blue;
	dirLine[1].color = sf::Color::Blue;
}

void pfe::Player::Movement(sf::RenderWindow& window)
{
	if (!window.hasFocus()) return;

	lastMousePos = sf::Mouse::getPosition();
	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
	rotation -= sf::degrees(sf::Mouse::getPosition().x - lastMousePos.x) * sensity;

	sf::Vector2f direction(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		direction.x += cos(rotation.asRadians());
		direction.y += sin(rotation.asRadians());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		direction.x -= cos(rotation.asRadians());
		direction.y -= sin(rotation.asRadians());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		sf::Angle r = sf::degrees(90);
		r += rotation;
		direction.x += cos(r.asRadians());
		direction.y += sin(r.asRadians());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		sf::Angle r = sf::degrees(90);	
		r += rotation;
		direction.x -= cos(r.asRadians());
		direction.y -= sin(r.asRadians());
	}

	position += direction * speed;

	dirLine[0].position = position + sf::Vector2f(playerShape.getRadius() / 2, playerShape.getRadius() / 2);
	float dirLenght = 15;
	dirLine[1].position = position + sf::Vector2f(cos(rotation.asRadians()) * dirLenght, sin(rotation.asRadians()) * dirLenght) + sf::Vector2f(playerShape.getRadius() / 2, playerShape.getRadius() / 2);
	playerShape.setPosition(position - sf::Vector2f(playerShape.getRadius() / 2, playerShape.getRadius() / 2));

	camera.UpdateInfo(dirLine[0].position, rotation);
}

void pfe::Player::CameraRender(const sf::Vector2u& windowSize, const pfe::Map& map)
{
	camera.Render(windowSize, map);
}

void pfe::Player::Draw(sf::RenderWindow& window)
{
	window.draw(playerShape);
	camera.DrawMinimapView(window);
	window.draw(dirLine);
}

void pfe::Player::DrawCameraView(sf::RenderWindow& window)
{
	camera.DrawCameraView(window);
}
