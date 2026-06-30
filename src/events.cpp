#include "events.hpp"

void processEvents(sf::Window &window, Game &game, Render &render, uint32_t &max_framerate, bool &running)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    window.close();

                else if (keyPressed->code == sf::Keyboard::Key::Space)
                    running = !running;

                else if (keyPressed->code == sf::Keyboard::Key::C){                    
                    // clear the grid (set all cells to dead)
                    game.alive.clear();
                    game.computed.clear();
                }
            }
        }
        else if (const auto &mouseWheelScroll = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            // get the local mouse position (relative to the window)
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            sf::Vector2f worldPosition = {
                (localPosition.x - render.shift.x) / render.scale,
                (localPosition.y - render.shift.y) / render.scale};

            // Zoom in or out
            render.scale *= pow(conf::zoom_sensitivity, mouseWheelScroll->delta);

            // Adjust the camera shift based on the mouse position
            render.shift = sf::Vector2f(localPosition) - worldPosition * render.scale;
        }
    }

    // Move events
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
        {
            // if shift is pressed, increase the speed of the program
            max_framerate += 5;
            if (max_framerate > conf::max_allowed_framerate)
                max_framerate = conf::max_allowed_framerate;
            window.setFramerateLimit(max_framerate);
            std::cout << "max fps : " << max_framerate << std::endl;
        }
        else
            render.shift.y += conf::move_sensitivity; // move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
        {
            // if shift is pressed, decrease the speed of the program
            if (max_framerate < 6)
                max_framerate = 6;
            max_framerate -= 5;
            window.setFramerateLimit(max_framerate);
            std::cout << "max fps : " << max_framerate << std::endl;
        }
        else
            render.shift.y -= conf::move_sensitivity; // move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        render.shift.x += conf::move_sensitivity; // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        render.shift.x -= conf::move_sensitivity; // move right

    //MARK: mouse events
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        // get the local mouse position (relative to the window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        // ignore if the mouse is outside the window
        if (localPosition.x < 0 || localPosition.y < 0)
            return;
        if (localPosition.x > conf::window_size.x || localPosition.y > conf::window_size.y)
            return;

        sf::Vector2f real_pos = {
            (localPosition.x - render.shift.x) / conf::cell_size.x / render.scale,
            (localPosition.y - render.shift.y) / conf::cell_size.y / render.scale
        };
        coord pos;
        if (real_pos.x < 0) pos.x = real_pos.x - 1.0f;
        else pos.x = real_pos.x;
        if (real_pos.y < 0) pos.y = real_pos.y - 1.0f;
        else pos.y = real_pos.y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            // if the cell is dead, make it alive
            game.addCell(pos);
        }
        else {
            // if the cell is alive, make it dead
            game.killCell(pos);
        }
    }
}