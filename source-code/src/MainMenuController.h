#pragma once
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

namespace godot {

class MainMenuController : public Control {
  GDCLASS(MainMenuController, Control)

private:

  Button *playButton = nullptr;
  Button *shopButton = nullptr;
  Button *settingsButton = nullptr;
  Button *creditButton = nullptr;
  Button *exitButton = nullptr;

  TextureRect *gameIconRect = nullptr;


  String songSelectScenePath =
      "res://resource-media/assets/scenes/SongSelect.tscn";

public:
  MainMenuController();
  ~MainMenuController();

  void _ready() override;


  void _on_play_pressed();
  void _on_shop_pressed();
  void _on_settings_pressed();
  void _on_credit_pressed();
  void _on_exit_pressed();


  void set_play_button(Button *btn) { playButton = btn; }
  Button *get_play_button() const { return playButton; }

  void set_shop_button(Button *btn) { shopButton = btn; }
  Button *get_shop_button() const { return shopButton; }

  void set_settings_button(Button *btn) { settingsButton = btn; }
  Button *get_settings_button() const { return settingsButton; }

  void set_credit_button(Button *btn) { creditButton = btn; }
  Button *get_credit_button() const { return creditButton; }

  void set_exit_button(Button *btn) { exitButton = btn; }
  Button *get_exit_button() const { return exitButton; }

  void set_game_icon(TextureRect *node) { gameIconRect = node; }
  TextureRect *get_game_icon() const { return gameIconRect; }

  void set_song_select_path(String path) { songSelectScenePath = path; }
  String get_song_select_path() const { return songSelectScenePath; }

protected:
  static void _bind_methods();
};

}
