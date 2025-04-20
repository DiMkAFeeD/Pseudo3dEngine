#include <main.h>

using namespace Main;
int main() {
    std::setlocale(LC_ALL, "RU");

    init();

    sf::RenderTexture renderTexture({ window.getSize()});

    while (window.isOpen()) {
        Event();

        ImGui::SFML::Update(window, Main::clock.restart());

        switch (Main::page) {
        case Page::menu:
            ImGui::Begin("Menu");
            ImGui::SetWindowSize("Μενώ", ImVec2(250, 100));

            if (ImGui::Button("Editor", ImVec2(225, 50))) {
                page =Page::view;
            }

            if (ImGui::Button("Exit", ImVec2(250, 50))) {
                window.close();
            }

            ImGui::End();
            break;
        case Main::Page::view:
            Update();
            Render();

            window.clear();
            renderTexture.clear(sf::Color::White);
            renderTexture.setView(view);  
            Main::Draw(); 
            renderTexture.display(); 
    
            ImGui::Begin("View Preview");
            ImGui::Image(renderTexture.getTexture());
            ImGui::End();
            break;
        default:
            break;
        }

        if (Main::page != Main::Page::view) {
            Main::window.clear();
            ImGui::SFML::Render(Main::window);
            Main::window.display();
        }

        ImGui::EndFrame();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

void Main::init() {
    view = sf::View(sf::FloatRect({ 0,0 }, { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) }));
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

    ImGui::CreateContext();
    ImGui::SFML::Init(window);
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

        ImGui::SFML::ProcessEvent(Main::window, event.value());
    }
}

void Main::Update()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
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
