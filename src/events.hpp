#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "configuration.hpp"
#include "game.hpp"
#include "render.hpp"

void processEvents(sf::Window & window, Game & game, Render & render, uint32_t & max_framerate, bool & running);