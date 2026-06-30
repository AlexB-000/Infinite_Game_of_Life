#include <SFML/Graphics.hpp>

#include "configuration.hpp"
#include "events.hpp"
#include "game.hpp"
#include "render.hpp"

int main(){
    uint32_t max_framerate = 100;

    auto window = sf::RenderWindow{sf::VideoMode({conf::window_size.x, conf::window_size.y}), "Game of Life", sf::Style::Titlebar};
    window.setFramerateLimit(max_framerate);

    Game game;
    Render render(game);

    bool running = false;

    while (window.isOpen())
    {
        processEvents(window, game, render, max_framerate, running);
        
        if (running) game.step();

        // rendering
        window.clear();

        render.render(window);

        window.display();
    }
}