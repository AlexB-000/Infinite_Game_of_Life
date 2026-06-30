#pragma once
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

using coord = sf::Vector2i;

struct Game {

    std::vector<coord> alive {}; // Initial alive cells
    std::vector<coord> computed {};

    Game(){}

    std::vector<coord> getNeighbors(const coord& cell) {
        std::vector<coord> result;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (x == 0 && y == 0) continue; // Skip the cell itself
                result.push_back({cell.x + x, cell.y + y});
            }
        }
        return result;
    }

    int countNeighbors(const std::vector<coord>& neighbors) {
        int count = 0;
        for (const coord& neighbor : neighbors) {
            if (std::find(alive.begin(), alive.end(), neighbor) != alive.end()) {
                count++;
            }
        }
        return count;
    }

    void addCell(const coord& cell) {
        addCell(cell, alive);
    }

    void addCell(const coord& cell, std::vector<coord>& inAlive) {
        if (std::find(inAlive.begin(), inAlive.end(), cell) == inAlive.end()) {
            inAlive.push_back(cell);
        }
    }

    void buildComputed(const std::vector<coord>& inAlive, std::vector<coord>& inComputed){
        for (const coord& cell : inAlive) {
            inComputed.emplace_back(cell);
            // neighbors might also change
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (std::find(inComputed.begin(), inComputed.end(), coord{cell.x + x, cell.y + y}) == inComputed.end()) {
                        inComputed.push_back(coord{cell.x + x, cell.y + y});
                    }
                }
            }
        }
    }

    void step() {
        std::vector<coord> computed;
        buildComputed(alive, computed);
        std::vector<coord> newAlive = {};

        // std::cout << "Alive cells: " << alive.size() << std::endl;
        // std::cout << "Computed cells: " << computed.size() << std::endl;
        // for (const coord& cell: alive){
        //     std::cout << "Alive cell: (" << cell.x << ", " << cell.y << ")" << std::endl;
        // }
        // for (const coord& cell: computed){
        //     std::cout << "Computed cell: (" << cell.x << ", " << cell.y << ")" << std::endl;
        // }

        for (const coord& cell : computed) {
            std::vector<coord> neighbors = getNeighbors(cell);

            int count = countNeighbors(neighbors);

            if (std::find(alive.begin(), alive.end(), cell) != alive.end()) {
                // Cell is alive
                if (count == 2 || count == 3) {
                    addCell(cell, newAlive);
                }
            } else {
                // Cell is dead
                if (count == 3) {
                    addCell(cell, newAlive);
                }
            }
        }
        alive = newAlive;
    }
};