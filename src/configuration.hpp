#pragma once
#include <SFML/Graphics.hpp>

namespace conf
{
//Window configuration
sf::Vector2u const window_size = {1600, 800};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);

constexpr uint32_t max_allowed_framerate=200;
constexpr float zoom_sensitivity = 1.1f; // Mouse wheel sensitivity for zooming
constexpr float move_sensitivity = 15.0f; // Keyboard sensitivity for moving the view
constexpr float initial_zoom = 10;
// Grid configuration
sf::Vector2f const cell_size { 1.0f, 1.0f };
constexpr float cell_in_ratio = 0.8f;
}
