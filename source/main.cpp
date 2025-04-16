#include "main.h"

int main()
{
    std::setlocale(LC_ALL, "RU");

    std::cout << "начало инициализации\n";
    Main::init();
    std::cout << "инициализация прошла\n";

    while (Main::window.isOpen()) {
        std::cout << "начало евентов";
        Main::Event();
        std::cout << "конец евентов\nначало апдейта\n";
        Main::Update();
        std::cout << "конец апдейта\nначало рендера\n";
        Main::Render();
        std::cout << "конец рендера\nначало отрисовки\n";
        Main::Draw();
        std::cout << "конец отрисовки\n";
    }

	return 0;
}

void Main::init() {
	view = sf::View(sf::FloatRect({ 0,0 }, { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
    bg.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    sf::Vertex v;
    v.color = sf::Color::White;
    v.position = sf::Vector2f(0, 0);
    bg.append(v);
    v.position = sf::Vector2f(window.getSize().x, 0);
    bg.append(v);
    v.color = sf::Color(20, 20, 20);
    v.position = sf::Vector2f(0, window.getSize().y / 2);
    bg.append(v);
    v.position = sf::Vector2f(window.getSize().x, window.getSize().y / 2);
    bg.append(v);
    v.color = sf::Color::Red;
    v.position = sf::Vector2f(0, window.getSize().y);
    bg.append(v);
    v.position = sf::Vector2f(window.getSize().x, window.getSize().y);
    bg.append(v);

    player.UpdateNumRaysCamera(window.getSize().x);
}

void Main::Event()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            sf::FloatRect viewSize({ 0, 0 }, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
            view = sf::View(viewSize);

            player.UpdateNumRaysCamera(resized->size.x);

            bg[1].position.x = resized->size.x;
            bg[2].position.y = resized->size.y / 2;
            bg[3].position = sf::Vector2f(resized->size.x, resized->size.y / 2);
            bg[4].position.y = resized->size.y;
            bg[5].position = sf::Vector2f(resized->size);
        }
    }
}

void Main::Update()
{
    config::deltaTime = clock.restart().asSeconds();
    player.Movement(window);
}

void Main::Render()
{
    player.CameraRender(window.getSize(), map);
}

void Main::Draw()
{
    window.clear(sf::Color::White);
    window.setView(view);

    window.draw(bg);

    player.DrawCameraView(window);

    map.Draw(window);
    player.Draw(window);

    window.display();
}
