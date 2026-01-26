#include "SongSelectController.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "BeatmapItem.h"
#include "GameGlobal.h"

using namespace godot;

std::string GameGlobal::selectedMapPath = "";
std::string GameGlobal::selectedAudioPath = "";

void SongSelectController::_bind_methods() {

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
}

void SongSelectController::_ready() {
  scan_maps_recursive("res://resource-media/map/");
  populate_grid();

  if (!mapList.empty()) {
    _on_item_clicked(0);
  }
}

void SongSelectController::scan_maps_in_folder(String folderPath) {
  Ref<DirAccess> dir = DirAccess::open(folderPath);
  if (dir.is_valid()) {
    dir->list_dir_begin();
    String fileName = dir->get_next();

    while (fileName != "") {
      if (!dir->current_is_dir() && fileName.ends_with(".csv")) {
        String fullPath = folderPath + "/" + fileName;

        Ref<FileAccess> file = FileAccess::open(fullPath, FileAccess::READ);
        if (file.is_valid()) {
          MapMetadata meta;
          meta.csvPath = fullPath;
          meta.title = "Unknown";
          meta.artist = "Unknown";

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
          mapList.push_back(meta);
        }
      }
      fileName = dir->get_next();
    }
  }
}

void SongSelectController::populate_grid() {
  if (!gridContainer || !beatmapItemScene.is_valid()) {
    UtilityFunctions::print("Error: Grid or Scene not set!");
    return;
  }

  gridContainer->add_theme_constant_override("h_separation", gridHSeparation);
  gridContainer->add_theme_constant_override("v_separation", gridVSeparation);

  TypedArray<Node> children = gridContainer->get_children();
  for (int i = 0; i < children.size(); i++) {
    Node *n = Object::cast_to<Node>(children[i]);
    if (n)
      n->queue_free();
  }

  for (int i = 0; i < mapList.size(); i++) {
    Node *node = beatmapItemScene->instantiate();
    BeatmapItem *item = Object::cast_to<BeatmapItem>(node);

    if (item) {
      item->set_custom_minimum_size(itemSize);
      gridContainer->add_child(item);

      Ref<Texture2D> coverTex;
      if (mapList[i].coverPath != "") {
        coverTex = ResourceLoader::get_singleton()->load(mapList[i].coverPath);
      }

      String diffText = mapList[i].difficulty + " " + mapList[i].level;
      item->setup_data(i, mapList[i].title, mapList[i].artist, diffText,
                       coverTex);

      item->connect("item_clicked", Callable(this, "_on_item_clicked"));
    }
  }
}

void SongSelectController::_on_item_clicked(int index) {
  if (index < 0 || index >= mapList.size())
    return;

  if (currentSelectionIndex == index) {
    String godotStr = mapList[index].csvPath;
    GameGlobal::selectedMapPath = godotStr.utf8().get_data();

    String audioGodotStr = mapList[index].audioPath;
    GameGlobal::selectedAudioPath = audioGodotStr.utf8().get_data();

    get_tree()->change_scene_to_file(gameScenePath);
  } else {
    currentSelectionIndex = index;
    update_info_panel();

    TypedArray<Node> children = gridContainer->get_children();
    for (int i = 0; i < children.size(); i++) {
      BeatmapItem *item = Object::cast_to<BeatmapItem>(children[i]);
      if (item) {
        item->set_selected(i == currentSelectionIndex);
      }
    }
  }
}

void SongSelectController::update_info_panel() {
  if (currentSelectionIndex < 0)
    return;
  MapMetadata &meta = mapList[currentSelectionIndex];

  if (titleLabel)
    titleLabel->set_text(meta.title);
  if (artistLabel)
    artistLabel->set_text(meta.artist);

  if (difficultyLabel) {
    String combinedText = meta.difficulty + " " + meta.level;
    difficultyLabel->set_text(combinedText);
  }
  if (levelLabel)
    levelLabel->set_text(meta.level);


  if (scoreLabel) {

    scoreLabel->set_text(String::num_int64(meta.bestScore).pad_zeros(7));
  }



  if (gradeLabel) {
    gradeLabel->set_text(meta.grade);
  }


  if (infoBackgroundRect) {
    if (!meta.coverPath.is_empty()) {
      Ref<Texture2D> tex =
          ResourceLoader::get_singleton()->load(meta.coverPath);
      infoBackgroundRect->set_texture(tex);
    } else {

      infoBackgroundRect->set_texture(Ref<Texture2D>());
    }
  }
}

void SongSelectController::scan_maps_recursive(String p_path) {
  UtilityFunctions::print("🚀 START SCANNING AT: ", p_path);

  Ref<DirAccess> dir = DirAccess::open(p_path);
  if (dir.is_null()) {

    UtilityFunctions::print("❌ Error opening directory: ", p_path);
    return;
  }

  dir->list_dir_begin();
  String file_name = dir->get_next();

  while (file_name != "") {
    if (dir->current_is_dir()) {
      if (file_name != "." && file_name != "..") {
        scan_maps_recursive(p_path + "/" + file_name);
      }
    } else {
      if (file_name.ends_with(".csv")) {
        process_map_file(p_path + "/" + file_name);
      }
    }
    file_name = dir->get_next();
  }
}

void SongSelectController::process_map_file(String fullPath) {
  Ref<FileAccess> file = FileAccess::open(fullPath, FileAccess::READ);
  if (file.is_valid()) {
    MapMetadata meta;
    meta.csvPath = fullPath;
    meta.title = "Unknown";
    meta.artist = "Unknown";


    meta.bestScore = 0;
    meta.grade = "-";
    String folderPath = fullPath.get_base_dir();

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
    if (meta.coverPath.is_empty() || meta.audioPath.is_empty()) {
      Ref<DirAccess> dir = DirAccess::open(folderPath);
      if (dir.is_valid()) {
        dir->list_dir_begin();
        String fileName = dir->get_next();
        while (fileName != "") {
          if (!dir->current_is_dir()) {
            String ext = fileName.get_extension().to_lower();
            if (meta.coverPath.is_empty() &&
                (ext == "png" || ext == "jpg" || ext == "jpeg")) {
              meta.coverPath = folderPath + "/" + fileName;
            }
            if (meta.audioPath.is_empty() &&
                (ext == "mp3" || ext == "ogg" || ext == "wav")) {
              meta.audioPath = folderPath + "/" + fileName;
            }
          }
          fileName = dir->get_next();
        }
      }
    }

    if (meta.coverPath != "") {
      UtilityFunctions::print("✅ Found Map: ", meta.title,
                              " | Cover: ", meta.coverPath);
    } else {
      UtilityFunctions::print("⚠️ Found Map: ", meta.title,
                              " | No Cover Found!");
    }

    if (meta.audioPath != "") {
      UtilityFunctions::print("   🎵 Audio Found: ", meta.audioPath);
    } else {
      UtilityFunctions::print("   ❌ No Audio Found for: ", meta.title);
    }

    mapList.push_back(meta);

    if (meta.coverPath != "") {
      UtilityFunctions::print("✅ Found Map: ", meta.title,
                              " | Cover: ", meta.coverPath);
    } else {
      UtilityFunctions::print("⚠️ Found Map: ", meta.title,
                              " | No Cover Found!");
    }
  }
}
