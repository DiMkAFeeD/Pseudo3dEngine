#include <map.h>

using json = nlohmann::json;

pfe::Map::Map(std::string filename) {
	wallsInMap.setPrimitiveType(sf::PrimitiveType::Lines);

	loadFromFile(filename);
}

void pfe::Map::AddWall(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Color& color, float th, float bh)
{
	walls.push_back(Wall(p0, p1, color, th, bh));
}

void pfe::Map::Draw(sf::RenderWindow& window)
{
	window.draw(wallsInMap);
}

std::vector<std::pair<sf::Vector2f, pfe::Map::Wall>> pfe::Map::getRayIntersection(
	const sf::Vector2f& start,
	const sf::Vector2f& direction,
	float maxDist
) const {
	std::vector<std::pair<sf::Vector2f, Wall>> intersections;

	for (const auto& wall : walls) {
		const sf::Vector2f& p1 = wall.pos0;
		const sf::Vector2f& p2 = wall.pos1;

		sf::Vector2f s1 = direction;
		sf::Vector2f s2 = p2 - p1;

		float denom = (-s2.x * s1.y + s1.x * s2.y);
		if (std::abs(denom) < 0.00001f)
			continue;

		float s = (-s1.y * (start.x - p1.x) + s1.x * (start.y - p1.y)) / denom;
		float t = (s2.x * (start.y - p1.y) - s2.y * (start.x - p1.x)) / denom;

		if (s >= 0 && s <= 1 && t >= 0) {
			sf::Vector2f intersection = start + t * s1;
			float dist = std::hypot(intersection.x - start.x, intersection.y - start.y);
			if (dist <= maxDist) {
				intersections.emplace_back(intersection, wall);
			}
		}
	}

	std::sort(intersections.begin(), intersections.end(),
		[&start](const auto& a, const auto& b) {
			float distA = std::hypot(a.first.x - start.x, a.first.y - start.y);
			float distB = std::hypot(b.first.x - start.x, b.first.y - start.y);
			return distA > distB;
		});

	return intersections;
}


void pfe::Map::loadFromFile(const std::string& filePath)
{
	std::ifstream in(filePath);
	if (!in.is_open()) {
		std::cerr << "Failed to open map file: " << filePath << "\n";
		return;
	}

	json j;
	in >> j;

	if (j.contains("walls") && j["walls"].is_array()) {
		for (const auto& wall : j["walls"]) {
			sf::Vector2f pos0(
				wall["pos0"]["x"].get<float>(),
				wall["pos0"]["y"].get<float>()
			);
			sf::Vector2f pos1(
				wall["pos1"]["x"].get<float>(),
				wall["pos1"]["y"].get<float>()
			);
			sf::Color color(
				wall["color"]["red"].get<int>(),
				wall["color"]["green"].get<int>(),
				wall["color"]["blue"].get<int>()
			);
			float topHeight = wall["topHeight"].get<float>();
			float bottomHeight = wall["bottomHeight"].get<float>();

			sf::Vertex v;
			v.color = color;
			v.position = pos0;
			wallsInMap.append(v);
			v.position = pos1;
			wallsInMap.append(v);

			AddWall(pos0, pos1, color, topHeight, bottomHeight);
		}
	}
}

void pfe::Map::saveToFile(const std::string& filePath)
{
	std::ofstream out(filePath);
	if (!out.is_open()) {
		std::cerr << "Failed to open map file for writing: " << filePath << "\n";
		return;
	}

	json j;
	j["walls"] = json::array();

	for (const auto& wall : walls) {
		json wallJson;
		wallJson["pos0"]["x"] = wall.pos0.x;
		wallJson["pos0"]["y"] = wall.pos0.y;
		wallJson["pos1"]["x"] = wall.pos1.x;
		wallJson["pos1"]["y"] = wall.pos1.y;

		wallJson["color"]["red"] = wall.color.r;
		wallJson["color"]["green"] = wall.color.g;
		wallJson["color"]["blue"] = wall.color.b;

		wallJson["topHeight"] = wall.topHeight;
		wallJson["bottomHeight"] = wall.bottomHeight;

		j["walls"].push_back(wallJson);
	}

	out << std::setw(4) << j << std::endl;
}
