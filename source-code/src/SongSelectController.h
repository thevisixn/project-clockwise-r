#pragma once
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <vector>
#include "BeatmapItem.h"


namespace godot {

struct MapMetadata {
    String title;
    String artist;
    String difficulty;
    String level;
    String coverPath;
    String csvPath;
};

class SongSelectController : public Control {
    GDCLASS(SongSelectController, Control)

private:
    std::vector<MapMetadata> mapList;
    int currentSelectionIndex = -1;

    Label* titleLabel = nullptr;
    Label* artistLabel = nullptr;
    Label* difficultyLabel = nullptr;
    Label* levelLabel = nullptr;
    
    GridContainer* gridContainer = nullptr;
    Ref<PackedScene> beatmapItemScene;

    String gameScenePath = "res://resource-media/assets/scenes.tscn"; 

    void scan_maps_in_folder(String folderPath);
    void update_info_panel();
    void populate_grid();

    void scan_maps_recursive(String folderPath);

    void process_map_file(String filePath);

public:
    void _ready() override;
    
    void _on_item_clicked(int index);

    void set_title_label(Label* l) { titleLabel = l; }
    Label* get_title_label() const { return titleLabel; }

    void set_artist_label(Label* l) { artistLabel = l; }
    Label* get_artist_label() const { return artistLabel; }
    
    void set_difficulty_label(Label* l) { difficultyLabel = l; }
    Label* get_difficulty_label() const { return difficultyLabel; }

    void set_level_label(Label* l) { levelLabel = l; }
    Label* get_level_label() const { return levelLabel; }

    void set_game_scene_path(String p) { gameScenePath = p; }
    String get_game_scene_path() const { return gameScenePath; }

    void set_grid_container(GridContainer* g) { gridContainer = g; }
    GridContainer* get_grid_container() const { return gridContainer; }

    void set_beatmap_item_scene(Ref<PackedScene> scene) { beatmapItemScene = scene; }
    Ref<PackedScene> get_beatmap_item_scene() const { return beatmapItemScene; }

protected:
    static void _bind_methods();
};

}