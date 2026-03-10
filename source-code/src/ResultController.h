#pragma once
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {
class ResultController : public Control {
    GDCLASS(ResultController, Control)

private:
    Label *lblTitle = nullptr;
    Label *lblArtist = nullptr;
    Label *lblDiff = nullptr;
    Label *lblScore = nullptr;
    Label *lblPerfect = nullptr;
    Label *lblGood = nullptr;
    Label *lblMiss = nullptr;
    Label *lblGrade = nullptr;
    Label *lblStatus = nullptr;
    Button *btnRetry = nullptr;
    Button *btnBack = nullptr;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _on_retry_pressed();
    void _on_back_pressed();
};
}
