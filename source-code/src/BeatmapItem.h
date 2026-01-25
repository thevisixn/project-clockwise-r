#pragma once
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>
#include <godot_cpp/classes/texture2d.hpp>

namespace godot {

class BeatmapItem : public Control {
    GDCLASS(BeatmapItem, Control)

private:
    int index = -1;

    TextureRect* coverImage = nullptr;
    Label* titleLabel = nullptr;
    Button* clickButton = nullptr;

    Label* artistLabel = nullptr;
    Label* difficultyLabel = nullptr;
    Color normalColor = Color(1, 1, 1, 0);
    Color selectedColor = Color(1, 1, 1, 0.2);

public:
    BeatmapItem();
    ~BeatmapItem();

    void _ready() override;

    void set_selected(bool selected);

    void _on_button_pressed();

    void set_cover_node(TextureRect* node) { coverImage = node; }
    TextureRect* get_cover_node() const { return coverImage; }

    void set_title_node(Label* node) { titleLabel = node; }
    Label* get_title_node() const { return titleLabel; }

    void set_button_node(Button* node) { clickButton = node; }
    Button* get_button_node() const { return clickButton; }

    void setup_data(int p_index, String p_title, String p_artist, String p_difficulty, Ref<Texture2D> p_cover);


    void set_artist_node(Label* node) { artistLabel = node; }
    Label* get_artist_node() const { return artistLabel; }

    void set_difficulty_node(Label* node) { difficultyLabel = node; }
    Label* get_difficulty_node() const { return difficultyLabel; }
protected:
    static void _bind_methods();
};

}
