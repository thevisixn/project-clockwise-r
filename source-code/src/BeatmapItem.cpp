#include "BeatmapItem.h"

using namespace godot;

void BeatmapItem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("setup_data", "index", "title", "cover"), &BeatmapItem::setup_data);
    ClassDB::bind_method(D_METHOD("set_selected", "selected"), &BeatmapItem::set_selected);
    ClassDB::bind_method(D_METHOD("_on_button_pressed"), &BeatmapItem::_on_button_pressed);

    ADD_SIGNAL(MethodInfo("item_clicked", PropertyInfo(Variant::INT, "index")));

    ClassDB::bind_method(D_METHOD("set_cover_node", "node"), &BeatmapItem::set_cover_node);
    ClassDB::bind_method(D_METHOD("get_cover_node"), &BeatmapItem::get_cover_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_cover", PROPERTY_HINT_NODE_TYPE, "TextureRect"), "set_cover_node", "get_cover_node");

    ClassDB::bind_method(D_METHOD("set_title_node", "node"), &BeatmapItem::set_title_node);
    ClassDB::bind_method(D_METHOD("get_title_node"), &BeatmapItem::get_title_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_title", PROPERTY_HINT_NODE_TYPE, "Label"), "set_title_node", "get_title_node");

    ClassDB::bind_method(D_METHOD("set_button_node", "node"), &BeatmapItem::set_button_node);
    ClassDB::bind_method(D_METHOD("get_button_node"), &BeatmapItem::get_button_node);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ui_button", PROPERTY_HINT_NODE_TYPE, "Button"), "set_button_node", "get_button_node");
}

BeatmapItem::BeatmapItem() {}
BeatmapItem::~BeatmapItem() {}

void BeatmapItem::_ready() {
    if (clickButton) {
        clickButton->connect("pressed", Callable(this, "_on_button_pressed"));
    }
}

void BeatmapItem::setup_data(int p_index, String p_title, Ref<Texture2D> p_cover) {
    index = p_index;
    if (titleLabel) titleLabel->set_text(p_title);
    if (coverImage && p_cover.is_valid()) coverImage->set_texture(p_cover);
}

void BeatmapItem::set_selected(bool selected) {
    if (clickButton) {
        clickButton->set_modulate(selected ? Color(1, 1, 0, 1) : Color(1, 1, 1, 0));
    }
}

void BeatmapItem::_on_button_pressed() {
    emit_signal("item_clicked", index);
}