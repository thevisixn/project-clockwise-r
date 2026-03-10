#pragma once
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <vector>

#include "BeatmapStructs.h"

namespace godot {

class SongSelectController : public Control {
  GDCLASS(SongSelectController, Control)
  std::vector<SongGroup> songList;

private:
  int currentSelectionIndex = -1;

  int currentSongIndex = -1;
  int currentDifficultyIndex = 0;

  Vector2 itemSize = Vector2(100, 800);

  int gridHSeparation = 20;
  int gridVSeparation = 20;
  Label *titleLabel = nullptr;
  Label *artistLabel = nullptr;
  Label *difficultyLabel = nullptr;
  Label *levelLabel = nullptr;

  Button *navMainMenuBtn = nullptr;
  Button *navSettingsBtn = nullptr;
  Button *navPlayBtn = nullptr;
  Button *navShopBtn = nullptr;
  Button *navCreditBtn = nullptr;
  Button *navExitBtn = nullptr;

  String mainMenuScenePath = "res://resource-media/assets/scenes/MainMenu.tscn";

  Label *scoreLabel = nullptr;
  Label *gradeLabel = nullptr;
  TextureRect *infoBackgroundRect = nullptr;

  TextureRect *textBackgroundRect = nullptr;

  Button *backButton = nullptr;

  GridContainer *gridContainer = nullptr;
  Ref<PackedScene> beatmapItemScene;

  String gameScenePath = "res://resource-media/assets/scenes/play.tscn  ";
  void update_info_panel();
  void populate_grid();

  void scan_maps_recursive(String folderPath);

  void process_map_file(String folderPath, String fileName);

  Button *btnOpenModUI = nullptr;      // ปุ่มที่กดแล้ว Panel เด้งขึ้นมา
  Button *btnCloseModUI = nullptr;     // ปุ่มปิด Panel (กากบาท)
  Control *modPanel = nullptr;         // ตัวหน้าต่าง Panel สี่เหลี่ยม
  Button *btnToggleAutoplay = nullptr; // ปุ่มเปิด/ปิด Autoplay
  Button *btnToggleHPMode = nullptr;   // ปุ่มเปิด/ปิด HP Mode
public:
  void _on_back_button_pressed();

  void set_back_button(Button *btn) { backButton = btn; }
  Button *get_back_button() const { return backButton; }

  void set_main_menu_scene_path(String path) { mainMenuScenePath = path; }
  String get_main_menu_scene_path() const { return mainMenuScenePath; }

  void _ready() override;

  void _on_item_clicked(int index);

  void set_title_label(Label *l) { titleLabel = l; }
  Label *get_title_label() const { return titleLabel; }

  void set_artist_label(Label *l) { artistLabel = l; }
  Label *get_artist_label() const { return artistLabel; }

  void set_difficulty_label(Label *l) { difficultyLabel = l; }
  Label *get_difficulty_label() const { return difficultyLabel; }

  void set_level_label(Label *l) { levelLabel = l; }
  Label *get_level_label() const { return levelLabel; }

  void set_score_label(Label *l) { scoreLabel = l; }
  Label *get_score_label() const { return scoreLabel; }

  void set_grade_label(Label *l) { gradeLabel = l; }
  Label *get_grade_label() const { return gradeLabel; }

  void set_info_bg_rect(TextureRect *t) { infoBackgroundRect = t; }
  TextureRect *get_info_bg_rect() const { return infoBackgroundRect; }

  void set_game_scene_path(String p) { gameScenePath = p; }
  String get_game_scene_path() const { return gameScenePath; }

  void set_grid_container(GridContainer *g) { gridContainer = g; }
  GridContainer *get_grid_container() const { return gridContainer; }

  void set_beatmap_item_scene(Ref<PackedScene> scene) {
    beatmapItemScene = scene;
  }
  Ref<PackedScene> get_beatmap_item_scene() const { return beatmapItemScene; }

  void set_item_size(Vector2 size) { itemSize = size; }
  Vector2 get_item_size() const { return itemSize; }

  void set_grid_separation_h(int val) { gridHSeparation = val; }
  int get_grid_separation_h() const { return gridHSeparation; }

  void set_grid_separation_v(int val) { gridVSeparation = val; }
  int get_grid_separation_v() const { return gridVSeparation; }

  void _unhandled_input(const Ref<InputEvent> &event) override;

  void set_text_bg_rect(TextureRect *t) { textBackgroundRect = t; }
  TextureRect *get_text_bg_rect() const { return textBackgroundRect; }

  // 🔥 [เพิ่ม] Setter/Getter สำหรับ Mod UI
  void set_btn_open_mod(Button *b) { btnOpenModUI = b; }
  Button *get_btn_open_mod() const { return btnOpenModUI; }

  void set_btn_close_mod(Button *b) { btnCloseModUI = b; }
  Button *get_btn_close_mod() const { return btnCloseModUI; }

  void set_mod_panel(Control *c) { modPanel = c; }
  Control *get_mod_panel() const { return modPanel; }

  void set_btn_toggle_autoplay(Button *b) { btnToggleAutoplay = b; }
  Button *get_btn_toggle_autoplay() const { return btnToggleAutoplay; }

  void set_btn_toggle_hpmode(Button *b) { btnToggleHPMode = b; }
  Button *get_btn_toggle_hpmode() const { return btnToggleHPMode; }

  // 🔥 [เพิ่ม] ฟังก์ชันรับ Event การกดปุ่ม
  void _on_btn_open_mod_pressed();
  void _on_btn_close_mod_pressed();
  void _on_btn_toggle_autoplay_pressed();
  void _on_btn_toggle_hpmode_pressed();

  // 🔥 [เพิ่ม] ฟังก์ชันอัปเดตหน้าตาปุ่ม (เปลี่ยนสี/ข้อความ)
  void update_mod_button_visuals();

protected:
  static void _bind_methods();
};

} // namespace godot
