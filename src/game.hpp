#pragma once
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "SearchTree.hpp"

using coord = sf::Vector2i;

struct Game {

    BinTree::Node alive {}; // Initial alive cells
    BinTree::Node computed {};

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
            if (alive.contains(neighbor)) {
                count++;
            }
        }
        return count;
    }

    void addCell(const coord& cell) {
        addCell(cell, alive);
    }

    void addCell(const coord& cell, BinTree::Node& inAlive) {
        if (!inAlive.contains(cell)) {
            inAlive.insert(cell);
        }
    }

    void buildComputed(const BinTree::Node& inAlive, BinTree::Node& inComputed){
        inComputed.clear();
        
        unsigned int alive_size = inAlive.size();
        for (unsigned int i = 0; i < alive_size; i++) {
            coord cell = inAlive.get(i);

            inComputed.insert(cell);
            // neighbors might also change
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (!inComputed.contains(coord{cell.x + x, cell.y + y})) {
                        inComputed.insert(coord{cell.x + x, cell.y + y});
                    }
                }
            }
        }
    }

    void killCell(const coord& cell) {
        if (alive.contains(cell)) {
            alive.remove(cell);
        }
    }

    void step() {
        BinTree::Node computed;
        buildComputed(alive, computed);
        BinTree::Node newAlive = {};

        // std::cout << "Alive cells: " << alive.size() << std::endl;
        // std::cout << "Computed cells: " << computed.size() << std::endl;
        // for (const coord& cell: alive){
        //     std::cout << "Alive cell: (" << cell.x << ", " << cell.y << ")" << std::endl;
        // }
        // for (const coord& cell: computed){
        //     std::cout << "Computed cell: (" << cell.x << ", " << cell.y << ")" << std::endl;
        // }

        unsigned int computed_size = computed.size();
        for (unsigned int i = 0; i < computed_size; i++) {
            coord cell = computed.get(i);

            std::vector<coord> neighbors = getNeighbors(cell);

            int count = countNeighbors(neighbors);

            if (alive.contains(cell)) {
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