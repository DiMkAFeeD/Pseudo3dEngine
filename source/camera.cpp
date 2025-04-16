#include <camera.h>

Camera::Camera::Camera(sf::Angle fov, int rays, float lenght, float stepRay) : FOV(fov), numRays(rays), rayLenght(lenght), rayStep(stepRay){
	cameraView.setPrimitiveType(sf::PrimitiveType::Lines);
	minimapView.setPrimitiveType(sf::PrimitiveType::Lines);
}
void Camera::Camera::UpdateInfo(sf::Vector2f position, sf::Angle rotation)
{
	this->position = position; this->rotation = rotation;
}

void Camera::Camera::DrawMinimapView(sf::RenderWindow& window)
{
	if(minimapView.getVertexCount() > 0) window.draw(minimapView);
}

void Camera::Camera::DrawCameraView(sf::RenderWindow& window)
{
	if (cameraView.getVertexCount() > 0) window.draw(cameraView);
}

void Camera::Camera::Render(const sf::Vector2u& windowSize, const Map::Map& map)
{
	minimapView.clear();
	cameraView.clear();

	sf::Angle startAngle = rotation - FOV/ 2;
	sf::Angle rotateStep = FOV / static_cast<float>(numRays);

	for (int i = 0; i < numRays; i++) {
		//castRayDefault(startAngle + rotateStep * i, i, windowSize, map);
		castRaySectionMethod(startAngle + rotateStep * i, i, windowSize, map);
	}
}

void Camera::Camera::castRayDefault(const sf::Angle& direction, int iRay, const sf::Vector2u& windowSize, const Map::Map& map)
{
	sf::Vector2f startRay = position;
	sf::Vector2f endRay = startRay;
	float lenght = 0;
	std::optional<Map::Map::Wall> wall;

	for (lenght; lenght < rayLenght; lenght += rayStep) {
		endRay = startRay + sf::Vector2f(cos(direction.asRadians()) * lenght, sin(direction.asRadians()) * lenght);
		//wall = map.getWallFromPoint(endRay);
		if (wall) {
			drawLine(lenght, wall.value(), iRay, windowSize);

			break;
		}
	}
	sf::Vertex startRayPoint, endRayPoint;
	startRayPoint.color = sf::Color::Red;
	endRayPoint.color = sf::Color::Yellow;

	startRayPoint.position = startRay;
	endRayPoint.position = endRay;

	minimapView.append(startRayPoint);
	minimapView.append(endRayPoint);
}

void Camera::Camera::castRaySectionMethod(const sf::Angle& direction, int iRay, const sf::Vector2u& windowSize, const Map::Map& map)
{
	sf::Vector2f dir(std::cos(direction.asRadians()), std::sin(direction.asRadians()));
	auto intersection = map.getRayIntersection(position, dir, rayLenght);

	sf::Vector2f endRay = position + dir * rayLenght;

	if (!intersection.empty()) {
		endRay = intersection[intersection.size()-1].first;
		for (auto& i : intersection) {
			float lenght = std::hypot(i.first.x - position.x, i.first.y - position.y);
			drawLine(lenght, i.second, iRay, windowSize);
		}
	}

	// Миникарта
	sf::Vertex startRayPoint, endRayPoint;
	startRayPoint.color = sf::Color::Cyan;
	endRayPoint.color = sf::Color::Magenta;

	startRayPoint.position = position;
	endRayPoint.position = endRay;

	minimapView.append(startRayPoint);
	minimapView.append(endRayPoint);
}


void Camera::Camera::drawLine(const float& lenght, const Map::Map::Wall& wall, const int& iRay, const sf::Vector2u& windowSize)
{
	float xWall = static_cast<float>(iRay) * windowSize.x / static_cast<float>(numRays);

	sf::Vertex topWallPoint, bottomWallPoint;

	float wallHeight = (windowSize.y / (lenght + 1.0f));

	topWallPoint.position = sf::Vector2f(xWall, windowSize.y / 2 - wallHeight * wall.topHeight);
	bottomWallPoint.position = sf::Vector2f(xWall, windowSize.y / 2 + wallHeight * wall.bottomHeight);

	float stpGray = 255 - (200 / rayLenght) * lenght;
	sf::Color gray(stpGray, stpGray, stpGray);

	topWallPoint.color = wall.color * gray;
	bottomWallPoint.color = wall.color * gray;

	cameraView.append(topWallPoint);
	cameraView.append(bottomWallPoint);
}
