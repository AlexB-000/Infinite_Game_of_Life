#pragma once
#include <SFML/Graphics.hpp>

#include "configuration.hpp"
#include "game.hpp"

struct Render {
    Game& game;

    float scale = conf::initial_zoom;
    sf::Vector2f shift {0, 0};

    Render(Game& game) : game(game) {}

    void render(sf::RenderWindow& window) {
        sf::RectangleShape shape{conf::cell_size};

        for (const coord& cell : game.alive) {
            sf::Vector2f position{
                cell.x * conf::cell_size.x * scale + shift.x,
                cell.y * conf::cell_size.y * scale + shift.y
            };
            shape.setPosition(position);

            shape.setScale({scale, scale});
            shape.setFillColor({128, 128, 128});
            window.draw(shape);

            shape.setScale({scale*conf::cell_in_ratio, scale*conf::cell_in_ratio});
            
            shape.setPosition(position + conf::cell_size * scale * (1-conf::cell_in_ratio) / 2.0f);

            shape.setFillColor({200, 200, 200});
            window.draw(shape);
        }
    }
};