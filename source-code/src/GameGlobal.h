#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>
#include <string>
namespace godot {

class GameGlobal {
public:
    static std::string selectedMapPath;
};


}