#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

int main()
{
    // * create window
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 4;

    sf::RenderWindow *window = new sf::RenderWindow(
        sf::VideoMode({800, 800}),
        "perlin",
        sf::State::Windowed,
        settings);

    // * start clock
    sf::Clock clock;

    // * random
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Random number engine
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    // * shader
    sf::Shader shader;

    if (!shader.loadFromFile("src/shader.frag", sf::Shader::Type::Fragment))
    {
        return -1;
    }

    sf::RectangleShape rect(sf::Vector2f(800, 800));

    while (window->isOpen())
    {
        window->setFramerateLimit(60u); // * limiting to 60fps

        // * clock!!
        float deltaTime = clock.restart().asSeconds();
        float fps = 1.0f / deltaTime;

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
            else if (auto *key = event->getIf<sf::Event::KeyPressed>())
            {
            }
            if (auto *press = event->getIf<sf::Event::MouseButtonPressed>())
            {
            }
            if (auto *mouse = event->getIf<sf::Event::MouseMoved>())
            {
            }
        }

        // * setting uniforms in shader
        shader.setUniform("time", clock.getElapsedTime().asSeconds());
        shader.setUniform("resolution", sf::Vector2f(window->getSize()));

        // * drawing a background colour
        // window->clear(sf::Color(100, 120, 140)); // * colour window buffer

        // * drawing
        window->clear();
        window->draw(rect, &shader);

        window->display();
    }

    delete window;
    return 0;
}