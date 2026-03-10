#include "NavbarController.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
using namespace godot;

NavbarController::NavbarController() {}
NavbarController::~NavbarController() {}

void NavbarController::_bind_methods() {
    ADD_SIGNAL(MethodInfo("play_action_requested"));

    ClassDB::bind_method(D_METHOD("set_main_menu_btn", "btn"), &NavbarController::set_main_menu_btn);
    ClassDB::bind_method(D_METHOD("get_main_menu_btn"), &NavbarController::get_main_menu_btn);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_main_menu_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_main_menu_btn", "get_main_menu_btn");

    ClassDB::bind_method(D_METHOD("set_settings_btn", "btn"), &NavbarController::set_settings_btn);
    ClassDB::bind_method(D_METHOD("get_settings_btn"), &NavbarController::get_settings_btn);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_settings_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_settings_btn", "get_settings_btn");

    ClassDB::bind_method(D_METHOD("set_play_btn", "btn"), &NavbarController::set_play_btn);
    ClassDB::bind_method(D_METHOD("get_play_btn"), &NavbarController::get_play_btn);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_play_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_play_btn", "get_play_btn");

    ClassDB::bind_method(D_METHOD("set_shop_btn", "btn"), &NavbarController::set_shop_btn);
    ClassDB::bind_method(D_METHOD("get_shop_btn"), &NavbarController::get_shop_btn);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_shop_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_shop_btn", "get_shop_btn");

    ClassDB::bind_method(D_METHOD("set_credit_btn", "btn"), &NavbarController::set_credit_btn);
    ClassDB::bind_method(D_METHOD("get_credit_btn"), &NavbarController::get_credit_btn);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_credit_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_credit_btn", "get_credit_btn");

    ClassDB::bind_method(D_METHOD("set_exit_btn", "btn"), &NavbarController::set_exit_btn);
    ClassDB::bind_method(D_METHOD("get_exit_btn"), &NavbarController::get_exit_btn);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_exit_btn", PROPERTY_HINT_NODE_TYPE, "Button"), "set_exit_btn", "get_exit_btn");

    ClassDB::bind_method(D_METHOD("set_main_menu_path", "path"), &NavbarController::set_main_menu_path);
    ClassDB::bind_method(D_METHOD("get_main_menu_path"), &NavbarController::get_main_menu_path);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "main_menu_path", PROPERTY_HINT_FILE, "*.tscn"), "set_main_menu_path", "get_main_menu_path");

    ClassDB::bind_method(D_METHOD("_on_main_menu_pressed"), &NavbarController::_on_main_menu_pressed);
    ClassDB::bind_method(D_METHOD("_on_settings_pressed"), &NavbarController::_on_settings_pressed);
    ClassDB::bind_method(D_METHOD("_on_play_pressed"), &NavbarController::_on_play_pressed);
    ClassDB::bind_method(D_METHOD("_on_shop_pressed"), &NavbarController::_on_shop_pressed);
    ClassDB::bind_method(D_METHOD("_on_credit_pressed"), &NavbarController::_on_credit_pressed);
    ClassDB::bind_method(D_METHOD("_on_exit_pressed"), &NavbarController::_on_exit_pressed);
}

void NavbarController::_ready() {
    if (Engine::get_singleton()->is_editor_hint()) {
        return;
    }
    if (mainMenuBtn) mainMenuBtn->connect("pressed", Callable(this, "_on_main_menu_pressed"));
    if (settingsBtn) settingsBtn->connect("pressed", Callable(this, "_on_settings_pressed"));
    if (playBtn) playBtn->connect("pressed", Callable(this, "_on_play_pressed"));
    if (shopBtn) shopBtn->connect("pressed", Callable(this, "_on_shop_pressed"));
    if (creditBtn) creditBtn->connect("pressed", Callable(this, "_on_credit_pressed"));
    if (exitBtn) exitBtn->connect("pressed", Callable(this, "_on_exit_pressed"));
}

void NavbarController::_on_main_menu_pressed() {
    if (!mainMenuPath.is_empty()) get_tree()->change_scene_to_file(mainMenuPath);
}

void NavbarController::_on_settings_pressed() {
    UtilityFunctions::print("Nav: Go to Settings");

}

void NavbarController::_on_play_pressed() {

    emit_signal("play_action_requested");
}

void NavbarController::_on_shop_pressed() {
    UtilityFunctions::print("Nav: Go to Shop");

}

void NavbarController::_on_credit_pressed() {
    UtilityFunctions::print("Nav: Show Credit");
}

void NavbarController::_on_exit_pressed() {
    get_tree()->quit();
}
