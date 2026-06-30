#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using coord = sf::Vector2i;

namespace BinTree {

    class Node {
        coord value;

        bool defined = false;
        size_t _size = 0;

        std::vector<Node> children;
    public:
        Node() {}

        size_t size() const {
            return _size;
        }

        void clear() {
            defined = false;
            _size = 0;
            children.clear();
        }

        void insert(const coord& inValue){
            _size ++;

            if (!defined) {
                value = inValue;
                defined = true;
                return;
            }

            int child_idx;
            if (inValue.x > value.x) {
                child_idx = 2;
            } else {
                child_idx = 0;
            }
            if (inValue.y > value.y) {
                child_idx += 1;
            }

            if (children.empty()) {
                children.resize(4, Node());
            }

            children[child_idx].insert(inValue);

        }

        bool contains(const coord& inValue) const {
            if (!defined) {
                return false;
            }
            if (inValue == value) {
                return true;
            }
            for (const auto& child : children) {
                if (child.contains(inValue)) {
                    return true;
                }
            }
            return false;
        }

        void remove(const coord& inValue) {
            if (this->contains(inValue)) {
                _size --;
            } else {
                return;
            }
            if (inValue == value) {
                if (children.empty()) {
                    defined = false;
                    return;
                } else {
                    // Find a replacement value from the children
                    for (Node& child : children) {
                        if (child.defined) {
                            value = child.value;
                            child.remove(child.value);
                            return;
                        }
                    }
                    defined = false; // If all children are empty, just mark as undefined
                    return;
                }
            }
            for (auto& child : children) {
                child.remove(inValue);
            }
        }

        coord get(unsigned int index) const {
            if (index >= _size) {
                throw std::out_of_range("Index out of range");
            }
            if (index == 0) {
                return value;
            }
            index --;
            for (const Node& child : children) {
                if (index < child.size()) {
                    return child.get(index);
                }
                index -= child.size();
            }
            throw std::out_of_range("Index out of range");
        }
    };
}