#include "SongSelectController.h"
#include "GameGlobal.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>



using namespace godot;

std::string GameGlobal::selectedMapPath = "";

void SongSelectController::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_grid_container", "node"), &SongSelectController::set_grid_container);
    ClassDB::bind_method(D_METHOD("get_grid_container"), &SongSelectController::get_grid_container);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_grid", PROPERTY_HINT_NODE_TYPE, "GridContainer"), "set_grid_container", "get_grid_container");

    ClassDB::bind_method(D_METHOD("set_beatmap_item_scene", "scene"), &SongSelectController::set_beatmap_item_scene);
    ClassDB::bind_method(D_METHOD("get_beatmap_item_scene"), &SongSelectController::get_beatmap_item_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "beatmap_item_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_beatmap_item_scene", "get_beatmap_item_scene");
    
    ClassDB::bind_method(D_METHOD("_on_item_clicked", "index"), &SongSelectController::_on_item_clicked);

    ClassDB::bind_method(D_METHOD("set_title_label", "label"), &SongSelectController::set_title_label);
    ClassDB::bind_method(D_METHOD("get_title_label"), &SongSelectController::get_title_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_title", PROPERTY_HINT_NODE_TYPE, "Label"), "set_title_label", "get_title_label");

    ClassDB::bind_method(D_METHOD("set_artist_label", "label"), &SongSelectController::set_artist_label);
    ClassDB::bind_method(D_METHOD("get_artist_label"), &SongSelectController::get_artist_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_artist", PROPERTY_HINT_NODE_TYPE, "Label"), "set_artist_label", "get_artist_label");

    ClassDB::bind_method(D_METHOD("set_difficulty_label", "label"), &SongSelectController::set_difficulty_label);
    ClassDB::bind_method(D_METHOD("get_difficulty_label"), &SongSelectController::get_difficulty_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_difficulty", PROPERTY_HINT_NODE_TYPE, "Label"), "set_difficulty_label", "get_difficulty_label");
    
    ClassDB::bind_method(D_METHOD("set_level_label", "label"), &SongSelectController::set_level_label);
    ClassDB::bind_method(D_METHOD("get_level_label"), &SongSelectController::get_level_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_level", PROPERTY_HINT_NODE_TYPE, "Label"), "set_level_label", "get_level_label");

    ClassDB::bind_method(D_METHOD("set_game_scene_path", "path"), &SongSelectController::set_game_scene_path);
    ClassDB::bind_method(D_METHOD("get_game_scene_path"), &SongSelectController::get_game_scene_path);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "game_scene_path", PROPERTY_HINT_FILE, "*.tscn"), "set_game_scene_path", "get_game_scene_path");
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
                        if (row.size() < 2) continue;
                        if (row[0] == "Note Data") break;

                        if (row[0] == "Title") meta.title = row[1];
                        else if (row[0] == "Artist") meta.artist = row[1];
                        else if (row[0] == "Difficulty") meta.difficulty = row[1];
                        else if (row[0] == "Level") meta.level = row[1];
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

    TypedArray<Node> children = gridContainer->get_children();
    for (int i = 0; i < children.size(); i++) {
        Node* n = Object::cast_to<Node>(children[i]);
        if (n) n->queue_free();
    }

    for (int i = 0; i < mapList.size(); i++) {
        Node* node = beatmapItemScene->instantiate();
        BeatmapItem* item = Object::cast_to<BeatmapItem>(node);
        
        if (item) {
            gridContainer->add_child(item);
            
            Ref<Texture2D> coverTex;
            if (mapList[i].coverPath != "") {
                 coverTex = ResourceLoader::get_singleton()->load(mapList[i].coverPath);
            }
            
            item->setup_data(i, mapList[i].title, coverTex);
            
            item->connect("item_clicked", Callable(this, "_on_item_clicked"));
        }
    }
}

void SongSelectController::_on_item_clicked(int index) {
    if (index < 0 || index >= mapList.size()) return;

    if (currentSelectionIndex == index) {
        
        String godotStr = mapList[index].csvPath;
        GameGlobal::selectedMapPath = godotStr.utf8().get_data();

        get_tree()->change_scene_to_file(gameScenePath);
    } 
    else {
        currentSelectionIndex = index;
        update_info_panel();
        
        TypedArray<Node> children = gridContainer->get_children();
        for (int i = 0; i < children.size(); i++) {
            BeatmapItem* item = Object::cast_to<BeatmapItem>(children[i]);
            if (item) {
                item->set_selected(i == currentSelectionIndex);
            }
        }
    }
}

void SongSelectController::update_info_panel() {
    if (currentSelectionIndex < 0) return;
    MapMetadata& meta = mapList[currentSelectionIndex];

    if (titleLabel) titleLabel->set_text(meta.title);
    if (artistLabel) artistLabel->set_text(meta.artist);
    if (difficultyLabel) difficultyLabel->set_text(meta.difficulty);
    if (levelLabel) levelLabel->set_text(meta.level);
    
}

void SongSelectController::scan_maps_recursive(String p_path) {
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
        
        String folderPath = fullPath.get_base_dir();

        while (!file->eof_reached()) {
            PackedStringArray row = file->get_csv_line();
            if (row.size() < 2) continue;
            if (row[0] == "Note Data") break; 

            if (row[0] == "Title") meta.title = row[1];
            else if (row[0] == "Artist") meta.artist = row[1];
            else if (row[0] == "Difficulty") meta.difficulty = row[1];
            else if (row[0] == "Level") meta.level = row[1];
            else if (row[0] == "Cover") {
                String imageFile = row[1];
                meta.coverPath = folderPath + "/" + imageFile;
            }
        }
        mapList.push_back(meta);
        
        UtilityFunctions::print("✅ Found Map: ", meta.title, " at ", fullPath);
    }
}