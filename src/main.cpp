#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

int main()
{
    // * create window
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 4;

    sf::RenderWindow *window = new sf::RenderWindow(
        sf::VideoMode({640u, 480u}),
        "first!!",
        sf::State::Windowed,
        settings);

    // * start clock
    sf::Clock clock;

    while (window->isOpen())
    {
        window->setFramerateLimit(60u); // * limiting to 60fps

        // * clock!!
        float deltaTime = clock.restart().asSeconds();
        float fps = 1.0f / deltaTime;
        std::cout << "delta time : " << deltaTime << "\nframe rate : " << fps << "\n";

        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }
            if (event->is<sf::Event::Resized>())
            {
                // * udpating view
                sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window->getSize())));
                window->setView(view);
            }
            else if (auto *key = event->getIf<sf::Event::KeyPressed>()) // KeyReleased {}
                if (auto *press = event->getIf<sf::Event::MouseButtonPressed>())
                {
                }
            if (auto *mouse = event->getIf<sf::Event::MouseMoved>())
            {
            }
        }

        // * drawing a background colour
        window->clear(sf::Color(100, 120, 140)); // * colour window buffer

        // * drawing

        window->display();
    }

    delete window;
    return 0;
}