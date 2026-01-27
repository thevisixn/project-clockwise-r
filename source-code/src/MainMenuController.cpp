#include "MainMenuController.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

MainMenuController::MainMenuController() {}
MainMenuController::~MainMenuController() {}

void MainMenuController::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_play_button", "btn"), &MainMenuController::set_play_button);
    ClassDB::bind_method(D_METHOD("get_play_button"), &MainMenuController::get_play_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_play_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_play_button", "get_play_button");


    ClassDB::bind_method(D_METHOD("set_shop_button", "btn"), &MainMenuController::set_shop_button);
    ClassDB::bind_method(D_METHOD("get_shop_button"), &MainMenuController::get_shop_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_shop_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_shop_button", "get_shop_button");


    ClassDB::bind_method(D_METHOD("set_settings_button", "btn"), &MainMenuController::set_settings_button);
    ClassDB::bind_method(D_METHOD("get_settings_button"), &MainMenuController::get_settings_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_settings_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_settings_button", "get_settings_button");


    ClassDB::bind_method(D_METHOD("set_credit_button", "btn"), &MainMenuController::set_credit_button);
    ClassDB::bind_method(D_METHOD("get_credit_button"), &MainMenuController::get_credit_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_credit_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_credit_button", "get_credit_button");


    ClassDB::bind_method(D_METHOD("set_exit_button", "btn"), &MainMenuController::set_exit_button);
    ClassDB::bind_method(D_METHOD("get_exit_button"), &MainMenuController::get_exit_button);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_exit_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_exit_button", "get_exit_button");


    ClassDB::bind_method(D_METHOD("set_game_icon", "node"), &MainMenuController::set_game_icon);
    ClassDB::bind_method(D_METHOD("get_game_icon"), &MainMenuController::get_game_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_game_icon", PROPERTY_HINT_NODE_TYPE, "TextureRect"), "set_game_icon", "get_game_icon");


    ClassDB::bind_method(D_METHOD("set_song_select_path", "path"), &MainMenuController::set_song_select_path);
    ClassDB::bind_method(D_METHOD("get_song_select_path"), &MainMenuController::get_song_select_path);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "next_scene_path", PROPERTY_HINT_FILE, "*.tscn"), "set_song_select_path", "get_song_select_path");


    ClassDB::bind_method(D_METHOD("_on_play_pressed"), &MainMenuController::_on_play_pressed);
    ClassDB::bind_method(D_METHOD("_on_shop_pressed"), &MainMenuController::_on_shop_pressed);
    ClassDB::bind_method(D_METHOD("_on_settings_pressed"), &MainMenuController::_on_settings_pressed);
    ClassDB::bind_method(D_METHOD("_on_credit_pressed"), &MainMenuController::_on_credit_pressed);
    ClassDB::bind_method(D_METHOD("_on_exit_pressed"), &MainMenuController::_on_exit_pressed);
}

void MainMenuController::_ready() {

    if (playButton) playButton->connect("pressed", Callable(this, "_on_play_pressed"));
    if (shopButton) shopButton->connect("pressed", Callable(this, "_on_shop_pressed"));
    if (settingsButton) settingsButton->connect("pressed", Callable(this, "_on_settings_pressed"));
    if (creditButton) creditButton->connect("pressed", Callable(this, "_on_credit_pressed"));
    if (exitButton) exitButton->connect("pressed", Callable(this, "_on_exit_pressed"));
}

void MainMenuController::_on_play_pressed() {
    UtilityFunctions::print("Play Button Pressed! Changing Scene...");
    if (songSelectScenePath.is_empty()) {
        UtilityFunctions::print("❌ Error: Song Select Scene Path is empty!");
        return;
    }
    get_tree()->change_scene_to_file(songSelectScenePath);
}

void MainMenuController::_on_shop_pressed() {
    UtilityFunctions::print("Shop - Coming Soon!");
}

void MainMenuController::_on_settings_pressed() {
    UtilityFunctions::print("Settings - Coming Soon!");
}

void MainMenuController::_on_credit_pressed() {
    UtilityFunctions::print("Credit - Created by You!");
}

void MainMenuController::_on_exit_pressed() {
    UtilityFunctions::print("Exiting Game...");
    get_tree()->quit();
}
