#include "SongSelectController.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "BeatmapItem.h"
#include "GameGlobal.h"
#include "godot_cpp/classes/input_event_key.hpp"

using namespace godot;

std::string GameGlobal::selectedMapPath = "";
std::string GameGlobal::selectedAudioPath = "";
bool GameGlobal::modAutoplay = false;
bool GameGlobal::modHPMode = false;
std::string GameGlobal::lastTitle = "";
std::string GameGlobal::lastArtist = "";
std::string GameGlobal::lastDifficulty = "";
int GameGlobal::lastScore = 0;
int GameGlobal::lastPerfect = 0;
int GameGlobal::lastGood = 0;
int GameGlobal::lastMiss = 0;
int GameGlobal::lastMaxCombo = 0;
std::string GameGlobal::lastGrade = "";
std::string GameGlobal::lastTuningStatus = "";

void SongSelectController::_bind_methods() {

  ClassDB::bind_method(D_METHOD("set_back_button", "btn"),
                       &SongSelectController::set_back_button);
  ClassDB::bind_method(D_METHOD("get_back_button"),
                       &SongSelectController::get_back_button);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_back_btn",
                            PROPERTY_HINT_NODE_TYPE, "Button"),
               "set_back_button", "get_back_button");

  ClassDB::bind_method(D_METHOD("_on_back_button_pressed"),
                       &SongSelectController::_on_back_button_pressed);

  ClassDB::bind_method(D_METHOD("set_grid_separation_h", "val"),
                       &SongSelectController::set_grid_separation_h);
  ClassDB::bind_method(D_METHOD("get_grid_separation_h"),
                       &SongSelectController::get_grid_separation_h);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "grid_separation_h"),
               "set_grid_separation_h", "get_grid_separation_h");

  ClassDB::bind_method(D_METHOD("set_grid_separation_v", "val"),
                       &SongSelectController::set_grid_separation_v);
  ClassDB::bind_method(D_METHOD("get_grid_separation_v"),
                       &SongSelectController::get_grid_separation_v);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "grid_separation_v"),
               "set_grid_separation_v", "get_grid_separation_v");

  ClassDB::bind_method(D_METHOD("set_grid_container", "node"),
                       &SongSelectController::set_grid_container);
  ClassDB::bind_method(D_METHOD("get_grid_container"),
                       &SongSelectController::get_grid_container);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_grid", PROPERTY_HINT_NODE_TYPE,
                            "GridContainer"),
               "set_grid_container", "get_grid_container");

  ClassDB::bind_method(D_METHOD("set_beatmap_item_scene", "scene"),
                       &SongSelectController::set_beatmap_item_scene);
  ClassDB::bind_method(D_METHOD("get_beatmap_item_scene"),
                       &SongSelectController::get_beatmap_item_scene);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "beatmap_item_scene",
                            PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"),
               "set_beatmap_item_scene", "get_beatmap_item_scene");

  ClassDB::bind_method(D_METHOD("_on_item_clicked", "index"),
                       &SongSelectController::_on_item_clicked);

  ClassDB::bind_method(D_METHOD("set_title_label", "label"),
                       &SongSelectController::set_title_label);
  ClassDB::bind_method(D_METHOD("get_title_label"),
                       &SongSelectController::get_title_label);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_title",
                            PROPERTY_HINT_NODE_TYPE, "Label"),
               "set_title_label", "get_title_label");

  ClassDB::bind_method(D_METHOD("set_artist_label", "label"),
                       &SongSelectController::set_artist_label);
  ClassDB::bind_method(D_METHOD("get_artist_label"),
                       &SongSelectController::get_artist_label);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_artist",
                            PROPERTY_HINT_NODE_TYPE, "Label"),
               "set_artist_label", "get_artist_label");

  ClassDB::bind_method(D_METHOD("set_difficulty_label", "label"),
                       &SongSelectController::set_difficulty_label);
  ClassDB::bind_method(D_METHOD("get_difficulty_label"),
                       &SongSelectController::get_difficulty_label);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_difficulty",
                            PROPERTY_HINT_NODE_TYPE, "Label"),
               "set_difficulty_label", "get_difficulty_label");

  ClassDB::bind_method(D_METHOD("set_level_label", "label"),
                       &SongSelectController::set_level_label);
  ClassDB::bind_method(D_METHOD("get_level_label"),
                       &SongSelectController::get_level_label);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_level",
                            PROPERTY_HINT_NODE_TYPE, "Label"),
               "set_level_label", "get_level_label");

  ClassDB::bind_method(D_METHOD("set_game_scene_path", "path"),
                       &SongSelectController::set_game_scene_path);
  ClassDB::bind_method(D_METHOD("get_game_scene_path"),
                       &SongSelectController::get_game_scene_path);
  ADD_PROPERTY(PropertyInfo(Variant::STRING, "game_scene_path",
                            PROPERTY_HINT_FILE, "*.tscn"),
               "set_game_scene_path", "get_game_scene_path");

  ClassDB::bind_method(D_METHOD("set_score_label", "label"),
                       &SongSelectController::set_score_label);
  ClassDB::bind_method(D_METHOD("get_score_label"),
                       &SongSelectController::get_score_label);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_score",
                            PROPERTY_HINT_NODE_TYPE, "Label"),
               "set_score_label", "get_score_label");

  ClassDB::bind_method(D_METHOD("set_grade_label", "node"),
                       &SongSelectController::set_grade_label);
  ClassDB::bind_method(D_METHOD("get_grade_label"),
                       &SongSelectController::get_grade_label);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_grade",
                            PROPERTY_HINT_NODE_TYPE, "Label"),
               "set_grade_label", "get_grade_label");

  ClassDB::bind_method(D_METHOD("set_info_bg_rect", "node"),
                       &SongSelectController::set_info_bg_rect);
  ClassDB::bind_method(D_METHOD("get_info_bg_rect"),
                       &SongSelectController::get_info_bg_rect);

  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_info_bg",
                            PROPERTY_HINT_NODE_TYPE, "TextureRect"),
               "set_info_bg_rect", "get_info_bg_rect");
  ClassDB::bind_method(D_METHOD("set_text_bg_rect", "rect"),
                       &SongSelectController::set_text_bg_rect);
  ClassDB::bind_method(D_METHOD("get_text_bg_rect"),
                       &SongSelectController::get_text_bg_rect);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_text_bg",
                            PROPERTY_HINT_NODE_TYPE, "TextureRect"),
               "set_text_bg_rect", "get_text_bg_rect");
  // 🔥 [เพิ่ม] Bind Property สำหรับ UI Mod
  ClassDB::bind_method(D_METHOD("set_btn_open_mod", "btn"),
                       &SongSelectController::set_btn_open_mod);
  ClassDB::bind_method(D_METHOD("get_btn_open_mod"),
                       &SongSelectController::get_btn_open_mod);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_btn_open_mod",
                            PROPERTY_HINT_NODE_TYPE, "Button"),
               "set_btn_open_mod", "get_btn_open_mod");

  ClassDB::bind_method(D_METHOD("set_btn_close_mod", "btn"),
                       &SongSelectController::set_btn_close_mod);
  ClassDB::bind_method(D_METHOD("get_btn_close_mod"),
                       &SongSelectController::get_btn_close_mod);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_btn_close_mod",
                            PROPERTY_HINT_NODE_TYPE, "Button"),
               "set_btn_close_mod", "get_btn_close_mod");

  ClassDB::bind_method(D_METHOD("set_mod_panel", "ctrl"),
                       &SongSelectController::set_mod_panel);
  ClassDB::bind_method(D_METHOD("get_mod_panel"),
                       &SongSelectController::get_mod_panel);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_mod_panel",
                            PROPERTY_HINT_NODE_TYPE, "Control"),
               "set_mod_panel", "get_mod_panel");

  ClassDB::bind_method(D_METHOD("set_btn_toggle_autoplay", "btn"),
                       &SongSelectController::set_btn_toggle_autoplay);
  ClassDB::bind_method(D_METHOD("get_btn_toggle_autoplay"),
                       &SongSelectController::get_btn_toggle_autoplay);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_btn_toggle_autoplay",
                            PROPERTY_HINT_NODE_TYPE, "Button"),
               "set_btn_toggle_autoplay", "get_btn_toggle_autoplay");

  ClassDB::bind_method(D_METHOD("set_btn_toggle_hpmode", "btn"),
                       &SongSelectController::set_btn_toggle_hpmode);
  ClassDB::bind_method(D_METHOD("get_btn_toggle_hpmode"),
                       &SongSelectController::get_btn_toggle_hpmode);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_btn_toggle_hpmode",
                            PROPERTY_HINT_NODE_TYPE, "Button"),
               "set_btn_toggle_hpmode", "get_btn_toggle_hpmode");

  // 🔥 [เพิ่ม] Bind ฟังก์ชันกดปุ่ม
  ClassDB::bind_method(D_METHOD("_on_btn_open_mod_pressed"),
                       &SongSelectController::_on_btn_open_mod_pressed);
  ClassDB::bind_method(D_METHOD("_on_btn_close_mod_pressed"),
                       &SongSelectController::_on_btn_close_mod_pressed);
  ClassDB::bind_method(D_METHOD("_on_btn_toggle_autoplay_pressed"),
                       &SongSelectController::_on_btn_toggle_autoplay_pressed);
  ClassDB::bind_method(D_METHOD("_on_btn_toggle_hpmode_pressed"),
                       &SongSelectController::_on_btn_toggle_hpmode_pressed);
}

void SongSelectController::_ready() {
  if (Engine::get_singleton()->is_editor_hint()) {
        return;
    }
  scan_maps_recursive("res://resource-media/map");
  populate_grid();

  if (!songList.empty()) {
    _on_item_clicked(0);
  }
  // 🔥 [เพิ่ม] Connect สัญญาณปุ่ม Mod
  if (btnOpenModUI)
    btnOpenModUI->connect("pressed",
                          Callable(this, "_on_btn_open_mod_pressed"));
  if (btnCloseModUI)
    btnCloseModUI->connect("pressed",
                           Callable(this, "_on_btn_close_mod_pressed"));
  if (btnToggleAutoplay)
    btnToggleAutoplay->connect(
        "pressed", Callable(this, "_on_btn_toggle_autoplay_pressed"));
  if (btnToggleHPMode)
    btnToggleHPMode->connect("pressed",
                             Callable(this, "_on_btn_toggle_hpmode_pressed"));

  // ซ่อนหน้าต่าง Mod ไว้ก่อนตอนเริ่มเกม และอัปเดตสีปุ่ม
  if (modPanel)
    modPanel->set_visible(false);
  update_mod_button_visuals();
}

void SongSelectController::_unhandled_input(const Ref<InputEvent> &event) {
  if (songList.empty() || currentSongIndex < 0 || currentSongIndex >= songList.size())
    return;

  Ref<InputEventKey> k = event;
  if (k.is_valid() && k->is_pressed() && !k->is_echo()) {

    SongGroup &song = songList[currentSongIndex];
    int maxDiff = song.difficulties.size() - 1;
    bool diffChanged = false;

    // 🌟 ระบบเลื่อนเปลี่ยนระดับความยาก (Q / E หรือ ลูกศรซ้าย / ขวา)
    if (k->get_keycode() == KEY_Q || k->get_keycode() == KEY_LEFT || k->get_keycode() == KEY_A) {
      if (currentDifficultyIndex > 0) {
        currentDifficultyIndex--;
        diffChanged = true;
      }
    } else if (k->get_keycode() == KEY_E || k->get_keycode() == KEY_RIGHT || k->get_keycode() == KEY_D) {
      if (currentDifficultyIndex < maxDiff) {
        currentDifficultyIndex++;
        diffChanged = true;
      }
    }

    if (diffChanged) {
      update_info_panel();
      MapMetadata &meta = song.difficulties[currentDifficultyIndex];
      GameGlobal::selectedMapPath = meta.csvPath.utf8().get_data();
      GameGlobal::selectedAudioPath = meta.audioPath.utf8().get_data();
      UtilityFunctions::print("Difficulty Changed: ", meta.difficulty);
      return; // จบการทำงานแค่นี้ ไม่ต้องเช็คปุ่มอื่นต่อ
    }

    // 🌟 ระบบเลื่อนเปลี่ยนเพลง (W / S หรือ ลูกศรขึ้น / ลง)
    if (k->get_keycode() == KEY_W || k->get_keycode() == KEY_UP) {
      int newIndex = currentSongIndex - 1;
      if (newIndex >= 0) {
          _on_item_clicked(newIndex); // โยนไปให้ฟังก์ชันคลิกจัดการ UI ต่อเลย
      }
    } else if (k->get_keycode() == KEY_S || k->get_keycode() == KEY_DOWN) {
      int newIndex = currentSongIndex + 1;
      if (newIndex < songList.size()) {
          _on_item_clicked(newIndex);
      }
    }

    // 🌟 ระบบกด Enter เพื่อเข้าเล่นเพลง
    if (k->get_keycode() == KEY_ENTER || k->get_keycode() == KEY_KP_ENTER) {
        _on_item_clicked(currentSongIndex); // เสมือนการกดดับเบิ้ลคลิก
    }
  }
}

void SongSelectController::populate_grid() {
  // 1. ป้องกัน Error ถ้าลืมใส่ Grid หรือ Scene ไว้ในหน้า Editor
  if (!gridContainer || !beatmapItemScene.is_valid()) {
    UtilityFunctions::print("❌ Error: Grid Container or Beatmap Item Scene is missing!");
    return;
  }

  // 2. ตั้งค่าระยะห่าง (Separation) ของ Grid
  gridContainer->add_theme_constant_override("h_separation", gridHSeparation);
  gridContainer->add_theme_constant_override("v_separation", gridVSeparation);

  // 3. ถอนการติดตั้ง Node ลูกของเก่าให้สะอาดสะอ้าน (แก้บั๊ก UI ซ้อนกัน)
  TypedArray<Node> children = gridContainer->get_children();
  for (int i = 0; i < children.size(); i++) {
    Node *n = Object::cast_to<Node>(children[i]);
    if (n) {
      gridContainer->remove_child(n); // เอาออกจาก UI ก่อนลบเสมอ
      n->queue_free();                // ลบข้อมูลทิ้ง
    }
  }

  // 4. วนลูปสร้าง Item เพลงใหม่เข้า Grid
  for (int i = 0; i < songList.size(); i++) {
    Node *node = beatmapItemScene->instantiate();
    BeatmapItem *item = Object::cast_to<BeatmapItem>(node);

    if (item) {
      // บังคับขนาดขั้นต่ำ ป้องกัน UI ถูกบีบจนเบี้ยว
      item->set_custom_minimum_size(itemSize);
      
      // ดึงและโหลดรูปปกเพลงอย่างปลอดภัย
      Ref<Texture2D> coverTex;
      if (!songList[i].coverPath.is_empty()) {
        coverTex = ResourceLoader::get_singleton()->load(songList[i].coverPath);
      }

      // หาช่วงเลเวลความยาก (เช่น Lv. 1 หรือ Lv. 1 - 5)
      String diffText = "Lv. ?";
      if (!songList[i].difficulties.empty()) {
        String minLv = songList[i].difficulties.front().level;
        String maxLv = songList[i].difficulties.back().level;
        diffText = (minLv == maxLv) ? ("Lv. " + minLv) : ("Lv. " + minLv + " - " + maxLv);
      }

      // ใส่ข้อมูลเข้า UI ของแต่ละเพลง
      item->setup_data(i, songList[i].title, songList[i].artist, diffText, coverTex);
      
      // ไฮไลท์เพลงที่กำลังเลือกอยู่ทันที
      item->set_selected(i == currentSongIndex); 
      
      // เชื่อมต่อการคลิก (เช็คก่อนว่ายังไม่ได้เชื่อม เพื่อกันบั๊กคลิกแล้วเบิ้ล)
      if (!item->is_connected("item_clicked", Callable(this, "_on_item_clicked"))) {
        item->connect("item_clicked", Callable(this, "_on_item_clicked"));
      }

      // นำเข้า GridContainer เพื่อแสดงบนหน้าจอ
      gridContainer->add_child(item);
    }
  }
  
  UtilityFunctions::print("✅ Loaded ", songList.size(), " songs into the grid.");
}

void SongSelectController::_on_item_clicked(int index) {
  if (index < 0 || index >= songList.size())
    return;

  // 🎯 กรณีที่ 1: ดับเบิ้ลคลิกที่เพลงเดิม (เพื่อเข้าเล่น)
  if (currentSongIndex == index) {
    if (songList[index].difficulties.empty()) {
      UtilityFunctions::print("❌ Error: No difficulties found for this song!");
      return; // ดักแครชถ้าเพลงพัง
    }

    UtilityFunctions::print("▶ Starting Game: ", songList[index].title);
    MapMetadata &meta = songList[index].difficulties[currentDifficultyIndex];

    GameGlobal::selectedMapPath = meta.csvPath.utf8().get_data();
    GameGlobal::selectedAudioPath = meta.audioPath.utf8().get_data();

    if (gameScenePath.is_empty()) {
      UtilityFunctions::print("❌ Error: Game Scene Path is empty!");
    } else {
      get_tree()->change_scene_to_file(gameScenePath);
    }
    return;
  }

  // 🎯 กรณีที่ 2: คลิกเลือกเพลงใหม่ครั้งแรก
  currentSongIndex = index;
  currentDifficultyIndex = 0; // รีเซ็ตความยากกลับเป็นอันแรกเสมอเมื่อเปลี่ยนเพลง
  
  // อัปเดตข้อมูลแผงด้านซ้าย
  update_info_panel();

  // เซ็ต Path ให้ Global เผื่อผู้เล่นกดปุ่ม Play สีเขียวด้านบน
  if (!songList[index].difficulties.empty()) {
    MapMetadata &meta = songList[index].difficulties[0];
    GameGlobal::selectedMapPath = meta.csvPath.utf8().get_data();
    GameGlobal::selectedAudioPath = meta.audioPath.utf8().get_data();
  }

  // 🌟 อัปเดต UI กรอบไฮไลท์ให้ตรงกับเพลงที่เลือก
  if (gridContainer) {
    TypedArray<Node> children = gridContainer->get_children();
    for (int i = 0; i < children.size(); i++) {
      BeatmapItem *item = Object::cast_to<BeatmapItem>(children[i]);
      if (item) {
        item->set_selected(i == currentSongIndex);
      }
    }
  }
}
void SongSelectController::update_info_panel() {
  if (currentSongIndex < 0 || currentSongIndex >= songList.size())
    return;

  SongGroup &group = songList[currentSongIndex];
  if (group.difficulties.empty())
    return;

  MapMetadata &meta = group.difficulties[currentDifficultyIndex];

  if (titleLabel)
    titleLabel->set_text(meta.title);
  if (artistLabel)
    artistLabel->set_text(meta.artist);

  String diffClass = get_difficulty_class(meta.difficulty, meta.level.to_int());
  Color themeColor = get_difficulty_color(diffClass);

  if (difficultyLabel) {
    String text = meta.difficulty + " " + meta.level;

    if (group.difficulties.size() > 1) {
      text = "< " + text + " >";
    }

    difficultyLabel->set_text(text);

    difficultyLabel->set_modulate(Color(1, 1, 1, 1));
  }

  if (levelLabel) {
    levelLabel->set_text(diffClass);

    levelLabel->set_modulate(Color(1, 1, 1, 1));
  }

  if (scoreLabel)
    scoreLabel->set_text(String::num_int64(meta.bestScore).pad_zeros(7));
  if (gradeLabel)
    gradeLabel->set_text(meta.grade);

  if (infoBackgroundRect) {
    if (!group.coverPath.is_empty()) {
      Ref<Texture2D> tex =
          ResourceLoader::get_singleton()->load(group.coverPath);
      infoBackgroundRect->set_texture(tex);
    }

    infoBackgroundRect->set_modulate(Color(1, 1, 1, 1));
  }
  if (textBackgroundRect) {

    textBackgroundRect->set_self_modulate(themeColor);
  }
}

void SongSelectController::scan_maps_recursive(String folderPath) {
  UtilityFunctions::print("🚀 START SCANNING AT: ", folderPath);

  Ref<DirAccess> dir = DirAccess::open(folderPath);
  if (dir.is_null()) {
    UtilityFunctions::print("Error opening folder: ", folderPath);
    return;
  }

  dir->list_dir_begin();
  String fileName = dir->get_next();

  while (fileName != "") {
    if (dir->current_is_dir()) {
      if (fileName != "." && fileName != "..") {

        scan_maps_recursive(folderPath + "/" + fileName);
      }
    } else {

      if (fileName.get_extension().to_lower() == "csv") {
        process_map_file(folderPath, fileName);
      }
    }
    fileName = dir->get_next();
  }
}

void SongSelectController::process_map_file(String folderPath,
                                            String fileName) {
  String fullPath = folderPath + "/" + fileName;
  Ref<FileAccess> file = FileAccess::open(fullPath, FileAccess::READ);

  if (file.is_null())
    return;
  MapMetadata meta;
  meta.csvPath = fullPath;
  meta.title = "Unknown";
  meta.artist = "Unknown";

  meta.bestScore = 0;
  meta.grade = "-";

  while (!file->eof_reached()) {
    PackedStringArray row = file->get_csv_line();
    if (row.size() < 2)
      continue;
    if (row[0] == "Note Data")
      break;

    if (row[0] == "Title")
      meta.title = row[1];
    else if (row[0] == "Artist")
      meta.artist = row[1];
    else if (row[0] == "Difficulty")
      meta.difficulty = row[1];
    else if (row[0] == "Level")
      meta.level = row[1];
  }
  file->close();
  if (meta.title.is_empty())
    return;
  Ref<DirAccess> dir = DirAccess::open(folderPath);
  if (dir.is_valid()) {
    dir->list_dir_begin();
    String fName = dir->get_next();

    // ลบบรรทัด String csvBaseName = ... ทิ้งไปได้เลยครับ

    while (fName != "") {
      if (!dir->current_is_dir()) {
        String ext = fName.get_extension().to_lower();

        // 🔥 [แก้ไข] เอาเงื่อนไข (fileBaseName == csvBaseName) ออกไป
        // ให้มันหยิบไฟล์รูปใดๆ ก็ตามที่เจอในโฟลเดอร์นี้มาใช้เลย
        if (meta.coverPath.is_empty() &&
            (ext == "png" || ext == "jpg" || ext == "jpeg")) {
          meta.coverPath = folderPath + "/" + fName;
        }

        // 🔥 [แก้ไข] เอาเงื่อนไข (fileBaseName == csvBaseName) ออกไป
        if (meta.audioPath.is_empty() &&
            (ext == "mp3" || ext == "ogg" || ext == "wav")) {
          meta.audioPath = folderPath + "/" + fName;
        }
      }
      fName = dir->get_next();
    }
  }
  bool groupFound = false;
  for (auto &group : songList) {
    if (group.title == meta.title && group.artist == meta.artist) {
      group.difficulties.push_back(meta);
      group.sort_difficulties();
      groupFound = true;
      break;
    }
  }

  if (!groupFound) {
    SongGroup newGroup;
    newGroup.title = meta.title;
    newGroup.artist = meta.artist;
    newGroup.coverPath = meta.coverPath;
    newGroup.audioPath = meta.audioPath;
    newGroup.difficulties.push_back(meta);
    songList.push_back(newGroup);
  }

  UtilityFunctions::print("Processed Map: ", meta.title, " [", meta.difficulty,
                          "]");
}

void SongSelectController::_on_back_button_pressed() {

  if (mainMenuScenePath.is_empty()) {
    UtilityFunctions::print("❌ Error: Main Menu Path is empty!");
    return;
  }
  get_tree()->change_scene_to_file(mainMenuScenePath);
}

void SongSelectController::_on_btn_open_mod_pressed() {
  if (modPanel) {
    modPanel->set_visible(true); // เปิดหน้าต่าง
    update_mod_button_visuals(); // อัปเดตสีปุ่มให้ตรงกับสถานะปัจจุบัน
  }
}

void SongSelectController::_on_btn_close_mod_pressed() {
  if (modPanel) {
    modPanel->set_visible(false); // ปิดหน้าต่าง
  }
}

void SongSelectController::_on_btn_toggle_autoplay_pressed() {
  // สลับค่า true/false ใน GameGlobal
  GameGlobal::modAutoplay = !GameGlobal::modAutoplay;
  update_mod_button_visuals();
}

void SongSelectController::_on_btn_toggle_hpmode_pressed() {
  // สลับค่า true/false ใน GameGlobal
  GameGlobal::modHPMode = !GameGlobal::modHPMode;
  update_mod_button_visuals();
}

// ฟังก์ชันสำหรับเปลี่ยนสี/เปลี่ยนข้อความปุ่มเมื่อเปิดปิด
void SongSelectController::update_mod_button_visuals() {
  if (btnToggleAutoplay) {
    if (GameGlobal::modAutoplay) {
      btnToggleAutoplay->set_text("Autoplay : ON");
      btnToggleAutoplay->set_self_modulate(Color(0.2, 1.0, 0.2)); // สีเขียว
    } else {
      btnToggleAutoplay->set_text("Autoplay : OFF");
      btnToggleAutoplay->set_self_modulate(Color(1, 1, 1)); // สีขาวปกติ
    }
  }

  if (btnToggleHPMode) {
    if (GameGlobal::modHPMode) {
      btnToggleHPMode->set_text("HP Mode : ON");
      btnToggleHPMode->set_self_modulate(Color(1.0, 0.2, 0.2)); // สีแดง (เลือด)
    } else {
      btnToggleHPMode->set_text("HP Mode : OFF");
      btnToggleHPMode->set_self_modulate(Color(1, 1, 1)); // สีขาวปกติ
    }
  }
}
