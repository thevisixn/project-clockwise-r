#pragma once
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

namespace godot {

class NavbarController : public Control {
    GDCLASS(NavbarController, Control)

private:

    Button* mainMenuBtn = nullptr;
    Button* settingsBtn = nullptr;
    Button* playBtn = nullptr;
    Button* shopBtn = nullptr;
    Button* creditBtn = nullptr;
    Button* exitBtn = nullptr;


    String mainMenuPath = "res://resource-media/assets/scenes/main_menu.tscn";
    String settingsPath = "res://resource-media/assets/scenes/Settings.tscn";
    String shopPath = "res://resource-media/assets/scenes/Shop.tscn";

public:
    NavbarController();
    ~NavbarController();

    void _ready() override;


    void _on_main_menu_pressed();
    void _on_settings_pressed();
    void _on_play_pressed();
    void _on_shop_pressed();
    void _on_credit_pressed();
    void _on_exit_pressed();


    void set_main_menu_btn(Button* btn) { mainMenuBtn = btn; }
    Button* get_main_menu_btn() const { return mainMenuBtn; }

    void set_settings_btn(Button* btn) { settingsBtn = btn; }
    Button* get_settings_btn() const { return settingsBtn; }

    void set_play_btn(Button* btn) { playBtn = btn; }
    Button* get_play_btn() const { return playBtn; }

    void set_shop_btn(Button* btn) { shopBtn = btn; }
    Button* get_shop_btn() const { return shopBtn; }

    void set_credit_btn(Button* btn) { creditBtn = btn; }
    Button* get_credit_btn() const { return creditBtn; }

    void set_exit_btn(Button* btn) { exitBtn = btn; }
    Button* get_exit_btn() const { return exitBtn; }


    void set_main_menu_path(String path) { mainMenuPath = path; }
    String get_main_menu_path() const { return mainMenuPath; }

protected:
    static void _bind_methods();
};

}
