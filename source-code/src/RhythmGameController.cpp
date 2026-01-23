#include "RhythmGameController.h"
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/font_variation.hpp>
#include <godot_cpp/classes/tween.hpp> 
#include <godot_cpp/classes/property_tweener.hpp>
#include "GameGlobal.h"

using namespace godot;

void RhythmGameController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_on_hit_judgement", "result", "combo"), &RhythmGameController::_on_hit_judgement);
    
    ClassDB::bind_method(D_METHOD("set_accuracy_label", "label"), &RhythmGameController::set_accuracy_label);
    ClassDB::bind_method(D_METHOD("get_accuracy_label"), &RhythmGameController::get_accuracy_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "accuracy_label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_accuracy_label", "get_accuracy_label");

    ClassDB::bind_method(D_METHOD("set_title_label", "label"), &RhythmGameController::set_title_label);
    ClassDB::bind_method(D_METHOD("get_title_label"), &RhythmGameController::get_title_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "title_label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_title_label", "get_title_label");

    ClassDB::bind_method(D_METHOD("set_difficulty_label", "label"), &RhythmGameController::set_difficulty_label);
    ClassDB::bind_method(D_METHOD("get_difficulty_label"), &RhythmGameController::get_difficulty_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "difficulty_label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_difficulty_label", "get_difficulty_label");
        
    ClassDB::bind_method(D_METHOD("set_rating_label", "label"), &RhythmGameController::set_rating_label);
    ClassDB::bind_method(D_METHOD("get_rating_label"), &RhythmGameController::get_rating_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "rating_label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_rating_label", "get_rating_label");

    ClassDB::bind_method(D_METHOD("set_grade_label", "label"), &RhythmGameController::set_grade_label);
    ClassDB::bind_method(D_METHOD("get_grade_label"), &RhythmGameController::get_grade_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "grade_label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_grade_label", "get_grade_label");

    ClassDB::bind_method(D_METHOD("set_score_label", "label"), &RhythmGameController::set_score_label);
    ClassDB::bind_method(D_METHOD("get_score_label"), &RhythmGameController::get_score_label);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "score_label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_score_label", "get_score_label");
    

    ADD_GROUP("Result SFX Levels (dB)", "sfx_");

    ClassDB::bind_method(D_METHOD("set_result_master_volume_db", "volume_db"), &RhythmGameController::set_result_master_volume_db);
    ClassDB::bind_method(D_METHOD("get_result_master_volume_db"), &RhythmGameController::get_result_master_volume_db);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sfx_result_master_volume_db", PROPERTY_HINT_RANGE, "-80,24,0.1,suffix:dB"), "set_result_master_volume_db", "get_result_master_volume_db");

    ClassDB::bind_method(D_METHOD("set_sfx_all_tuned_volume_db", "volume_db"), &RhythmGameController::set_sfx_all_tuned_volume_db);
    ClassDB::bind_method(D_METHOD("get_sfx_all_tuned_volume_db"), &RhythmGameController::get_sfx_all_tuned_volume_db);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sfx_all_tuned_offset_db", PROPERTY_HINT_RANGE, "-80,24,0.1,suffix:dB"), "set_sfx_all_tuned_volume_db", "get_sfx_all_tuned_volume_db");

    ClassDB::bind_method(D_METHOD("set_sfx_full_adjusted_volume_db", "volume_db"), &RhythmGameController::set_sfx_full_adjusted_volume_db);
    ClassDB::bind_method(D_METHOD("get_sfx_full_adjusted_volume_db"), &RhythmGameController::get_sfx_full_adjusted_volume_db);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sfx_full_adjusted_offset_db", PROPERTY_HINT_RANGE, "-80,24,0.1,suffix:dB"), "set_sfx_full_adjusted_volume_db", "get_sfx_full_adjusted_volume_db");

    ClassDB::bind_method(D_METHOD("set_sfx_tuning_finish_volume_db", "volume_db"), &RhythmGameController::set_sfx_tuning_finish_volume_db);
    ClassDB::bind_method(D_METHOD("get_sfx_tuning_finish_volume_db"), &RhythmGameController::get_sfx_tuning_finish_volume_db);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "sfx_tuning_finish_offset_db", PROPERTY_HINT_RANGE, "-80,24,0.1,suffix:dB"), "set_sfx_tuning_finish_volume_db", "get_sfx_tuning_finish_volume_db");

    ClassDB::bind_method(D_METHOD("set_tex_single", "texture"), &RhythmGameController::set_tex_single);
    ClassDB::bind_method(D_METHOD("get_tex_single"), &RhythmGameController::get_tex_single);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_single", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_single", "get_tex_single");

    ClassDB::bind_method(D_METHOD("set_tex_reverse", "texture"), &RhythmGameController::set_tex_reverse);
    ClassDB::bind_method(D_METHOD("get_tex_reverse"), &RhythmGameController::get_tex_reverse);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_reverse", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_reverse", "get_tex_reverse");

    ClassDB::bind_method(D_METHOD("set_tex_overclock", "texture"), &RhythmGameController::set_tex_overclock);
    ClassDB::bind_method(D_METHOD("get_tex_overclock"), &RhythmGameController::get_tex_overclock);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_overclock", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_overclock", "get_tex_overclock");

    ClassDB::bind_method(D_METHOD("set_tex_overheat", "texture"), &RhythmGameController::set_tex_overheat);
    ClassDB::bind_method(D_METHOD("get_tex_overheat"), &RhythmGameController::get_tex_overheat);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_overheat", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_overheat", "get_tex_overheat");

    ClassDB::bind_method(D_METHOD("set_tex_line", "texture"), &RhythmGameController::set_tex_line);
    ClassDB::bind_method(D_METHOD("get_tex_line"), &RhythmGameController::get_tex_line);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_line", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_line", "get_tex_line");

    ClassDB::bind_method(D_METHOD("set_tex_anomaly", "texture"), &RhythmGameController::set_tex_anomaly);
    ClassDB::bind_method(D_METHOD("get_tex_anomaly"), &RhythmGameController::get_tex_anomaly);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_anomaly", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_anomaly", "get_tex_anomaly");

    ClassDB::bind_method(D_METHOD("set_tex_hold_tail", "texture"), &RhythmGameController::set_tex_hold_tail);
    ClassDB::bind_method(D_METHOD("get_tex_hold_tail"), &RhythmGameController::get_tex_hold_tail);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_hold_tail", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_hold_tail", "get_tex_hold_tail");

    ClassDB::bind_method(D_METHOD("set_user_audio_offset", "offset"), &RhythmGameController::set_user_audio_offset);
    ClassDB::bind_method(D_METHOD("get_user_audio_offset"), &RhythmGameController::get_user_audio_offset);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "user_audio_offset"), "set_user_audio_offset", "get_user_audio_offset");

ClassDB::bind_method(D_METHOD("set_sfx_single", "stream"), &RhythmGameController::set_sfx_single);
    ClassDB::bind_method(D_METHOD("get_sfx_single"), &RhythmGameController::get_sfx_single);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_single", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_single", "get_sfx_single");

    ClassDB::bind_method(D_METHOD("set_sfx_hold", "stream"), &RhythmGameController::set_sfx_hold);
    ClassDB::bind_method(D_METHOD("get_sfx_hold"), &RhythmGameController::get_sfx_hold);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_hold", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_hold", "get_sfx_hold");

    ClassDB::bind_method(D_METHOD("set_sfx_reverse", "stream"), &RhythmGameController::set_sfx_reverse);
    ClassDB::bind_method(D_METHOD("get_sfx_reverse"), &RhythmGameController::get_sfx_reverse);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_reverse", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_reverse", "get_sfx_reverse");

    ClassDB::bind_method(D_METHOD("set_sfx_overclock", "stream"), &RhythmGameController::set_sfx_overclock);
    ClassDB::bind_method(D_METHOD("get_sfx_overclock"), &RhythmGameController::get_sfx_overclock);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_overclock", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_overclock", "get_sfx_overclock");

    ClassDB::bind_method(D_METHOD("set_sfx_overheat", "stream"), &RhythmGameController::set_sfx_overheat);
    ClassDB::bind_method(D_METHOD("get_sfx_overheat"), &RhythmGameController::get_sfx_overheat);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_overheat", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_overheat", "get_sfx_overheat");

    ClassDB::bind_method(D_METHOD("set_visible_window", "value"), &RhythmGameController::set_visible_window);
    ClassDB::bind_method(D_METHOD("get_visible_window"), &RhythmGameController::get_visible_window);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "visible_window"), "set_visible_window", "get_visible_window");
    
    ClassDB::bind_method(D_METHOD("set_hit_effect_scene", "scene"), &RhythmGameController::set_hit_effect_scene);
    ClassDB::bind_method(D_METHOD("get_hit_effect_scene"), &RhythmGameController::get_hit_effect_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hit_effect_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_hit_effect_scene", "get_hit_effect_scene");

    ClassDB::bind_method(D_METHOD("set_vol_music", "db"), &RhythmGameController::set_vol_music);
    ClassDB::bind_method(D_METHOD("get_vol_music"), &RhythmGameController::get_vol_music);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "vol_music_db"), "set_vol_music", "get_vol_music");

    ClassDB::bind_method(D_METHOD("set_vol_single", "db"), &RhythmGameController::set_vol_single);
    ClassDB::bind_method(D_METHOD("get_vol_single"), &RhythmGameController::get_vol_single);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "vol_sfx_single_db"), "set_vol_single", "get_vol_single");

    ClassDB::bind_method(D_METHOD("set_vol_hold", "db"), &RhythmGameController::set_vol_hold);
    ClassDB::bind_method(D_METHOD("get_vol_hold"), &RhythmGameController::get_vol_hold);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "vol_sfx_hold_db"), "set_vol_hold", "get_vol_hold");

    ClassDB::bind_method(D_METHOD("set_vol_reverse", "db"), &RhythmGameController::set_vol_reverse);
    ClassDB::bind_method(D_METHOD("get_vol_reverse"), &RhythmGameController::get_vol_reverse);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "vol_sfx_reverse_db"), "set_vol_reverse", "get_vol_reverse");

    ClassDB::bind_method(D_METHOD("set_vol_overclock", "db"), &RhythmGameController::set_vol_overclock);
    ClassDB::bind_method(D_METHOD("get_vol_overclock"), &RhythmGameController::get_vol_overclock);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "vol_sfx_overclock_db"), "set_vol_overclock", "get_vol_overclock");

    ClassDB::bind_method(D_METHOD("set_vol_overheat", "db"), &RhythmGameController::set_vol_overheat);
    ClassDB::bind_method(D_METHOD("get_vol_overheat"), &RhythmGameController::get_vol_overheat);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "vol_sfx_overheat_db"), "set_vol_overheat", "get_vol_overheat");

    ClassDB::bind_method(D_METHOD("set_tex_background", "texture"), &RhythmGameController::set_tex_background);
    ClassDB::bind_method(D_METHOD("get_tex_background"), &RhythmGameController::get_tex_background);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_background", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_background", "get_tex_background");

ClassDB::bind_method(D_METHOD("set_sfx_all_tuned", "stream"), &RhythmGameController::set_sfx_all_tuned);
    ClassDB::bind_method(D_METHOD("get_sfx_all_tuned"), &RhythmGameController::get_sfx_all_tuned);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_all_tuned", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_all_tuned", "get_sfx_all_tuned");

    ClassDB::bind_method(D_METHOD("set_sfx_full_adjusted", "stream"), &RhythmGameController::set_sfx_full_adjusted);
    ClassDB::bind_method(D_METHOD("get_sfx_full_adjusted"), &RhythmGameController::get_sfx_full_adjusted);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_full_adjusted", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_full_adjusted", "get_sfx_full_adjusted");

    ClassDB::bind_method(D_METHOD("set_sfx_tuning_finish", "stream"), &RhythmGameController::set_sfx_tuning_finish);
    ClassDB::bind_method(D_METHOD("get_sfx_tuning_finish"), &RhythmGameController::get_sfx_tuning_finish);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sfx_tuning_finish", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_sfx_tuning_finish", "get_sfx_tuning_finish");
}

RhythmGameController::RhythmGameController()
{
}

RhythmGameController::~RhythmGameController()
{
}

void RhythmGameController::set_vol_music(double val) { 
    volMusic = val; 
}

void RhythmGameController::set_vol_single(double val) { volSingle = val; for(auto* c : circles) c->set_vol_single(val); }
void RhythmGameController::set_vol_hold(double val) { volHold = val; for(auto* c : circles) c->set_vol_hold(val); }
void RhythmGameController::set_vol_reverse(double val) { volReverse = val; for(auto* c : circles) c->set_vol_reverse(val); }
void RhythmGameController::set_vol_overclock(double val) { volOverclock = val; for(auto* c : circles) c->set_vol_overclock(val); }
void RhythmGameController::set_vol_overheat(double val) { volOverheat = val; for(auto* c : circles) c->set_vol_overheat(val); }


void RhythmGameController::_ready()
{
    if (texBackground.is_valid()) {
        CanvasLayer* bgLayer = memnew(CanvasLayer);
        bgLayer->set_layer(-100);
        add_child(bgLayer);

        Sprite2D* bg = memnew(Sprite2D);
        bg->set_texture(texBackground);
        
        bg->set_modulate(Color(0.3, 0.3, 0.3)); 

        Size2 texSize = texBackground->get_size();
        Size2 screenSize = get_viewport_rect().size;
        
        double scaleX = screenSize.x / texSize.x;
        double scaleY = screenSize.y / texSize.y;
        double finalScale = MAX(scaleX, scaleY);
        
        bg->set_scale(Vector2(finalScale * 1.05, finalScale * 1.05));
        
        bg->set_position(screenSize / 2.0);
        
        bgLayer->add_child(bg);
    }

    audioEngine = memnew(JuceAudioEngine);
    add_child(audioEngine);
    uiLayer = memnew(CanvasLayer);
    uiLayer->set_layer(10);
    add_child(uiLayer);

    progressBar = memnew(ProgressBar);
    
    progressBar->set_anchors_and_offsets_preset(Control::PRESET_TOP_WIDE); 
    
    progressBar->set_offset(Side::SIDE_BOTTOM, 10); 
    
    progressBar->set_custom_minimum_size(Vector2(0, 0));
    progressBar->set_show_percentage(false); 
    
    Ref<StyleBoxFlat> bgStyle = memnew(StyleBoxFlat);
    bgStyle->set_bg_color(Color(0, 0, 0, 0.5)); 
    bgStyle->set_content_margin_all(0);
    progressBar->add_theme_stylebox_override("background", bgStyle);
    
    Ref<StyleBoxFlat> fillStyle = memnew(StyleBoxFlat);
    fillStyle->set_bg_color(Color(1.0, 1.0, 1.0));
    fillStyle->set_content_margin_all(0);
    progressBar->add_theme_stylebox_override("fill", fillStyle);

    uiLayer->add_child(progressBar);

    
    Size2 screenSize = get_viewport_rect().size;
    double centerX = screenSize.x / 2.0;
    double topY = 40.0;

    Ref<Font> comboFont = ResourceLoader::get_singleton()->load("res://resource-media/fonts/Quicksand.ttf");

    comboLabel = memnew(Label);
    comboLabel->set_text(""); 
    comboLabel->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_CENTER);
    comboLabel->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
    
    comboLabel->add_theme_font_size_override("font_size", 80);
    comboLabel->add_theme_color_override("font_outline_color", Color(0,0,0,0));
    comboLabel->add_theme_constant_override("outline_size", 0);
    
    if (comboFont.is_valid()) {
        Ref<FontVariation> adjustedFont = memnew(FontVariation);
        adjustedFont->set_base_font(comboFont);
        
        adjustedFont->set_variation_embolden(0.8);
        
        if (comboLabel) {
            comboLabel->add_theme_font_override("font", adjustedFont);
        }
    }

    comboLabel->set_modulate(Color(1, 1, 1, 0)); 
    
    double numberW = 400.0;
    comboLabel->set_position(Vector2(centerX - (numberW/2), topY)); 
    comboLabel->set_size(Vector2(numberW, 100));
    comboLabel->set_pivot_offset(Vector2(numberW/2, 50));

    uiLayer->add_child(comboLabel);


    comboTextLabel = memnew(Label);
    comboTextLabel->set_text("COMBO"); 
    comboTextLabel->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_CENTER);
    comboTextLabel->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);

    comboTextLabel->add_theme_font_size_override("font_size", 32);
    comboTextLabel->add_theme_color_override("font_outline_color", Color(0,0,0,0));
    comboTextLabel->add_theme_constant_override("outline_size", 0);
    if (comboFont.is_valid()) {
        Ref<FontVariation> adjustedFont = memnew(FontVariation);
        adjustedFont->set_base_font(comboFont);
        
        adjustedFont->set_variation_embolden(0.8);

        if (comboTextLabel) {
            comboTextLabel->add_theme_font_override("font", adjustedFont);
        }
    }
    comboTextLabel->set_modulate(Color(1, 1, 1, 0)); 


    double textY = topY + 120.0;
    comboTextLabel->set_position(Vector2(centerX - (numberW/2), textY));
    comboTextLabel->set_size(Vector2(numberW, 50));
    comboTextLabel->set_pivot_offset(Vector2(numberW/2, 25));

    uiLayer->add_child(comboTextLabel);
    
    resultAnim = memnew(AnimatedSprite2D);
    resultAnim->set_position(screenSize / 2.0);
    resultAnim->set_visible(false);
    uiLayer->add_child(resultAnim);
    
    
    Ref<SpriteFrames> frames = ResourceLoader::get_singleton()->load("res://resource-media/assets/gameplay/result-animation/animated/result_animations.tres");

    if (frames.is_valid()) {
        resultAnim->set_sprite_frames(frames);
    } else {
        UtilityFunctions::print("Error: Could not load result_animations.tres!");
    }
    isGameEnded = false;
    isAllPerfect = true;
    isFullCombo = true;
    
    std::vector<Vector2> circlePositions = {
        Vector2(-693, 0),
        Vector2(693, 0)
    };
    double maxNoteTime = 0.0;
    for (const auto &pos : circlePositions)
    {
        RhythmCircle *c = memnew(RhythmCircle);
        c->set_position(pos);

        c->set_tex_single(texSingle);
        c->set_tex_reverse(texReverse);
        c->set_tex_overclock(texOverclock);
        c->set_tex_overheat(texOverheat);
        c->set_tex_anomaly(texAnomaly);
        c->set_tex_line(texLine);
        c->set_tex_hold_tail(texHoldTail);
        c->set_sfx_single(sfxSingle);
        c->set_sfx_hold(sfxHold);
        c->set_sfx_reverse(sfxReverse);
        c->set_sfx_overclock(sfxOverclock);
        c->set_sfx_overheat(sfxOverheat);
        c->set_visible_window(visibleWindow);
        c->connect("on_hit_judgement", Callable(this, "_on_hit_judgement"));
        c->set_hit_effect_scene(hitEffectScene);

        c->set_vol_single(volSingle);
        c->set_vol_hold(volHold);
        c->set_vol_reverse(volReverse);
        c->set_vol_overclock(volOverclock);
        c->set_vol_overheat(volOverheat);

        add_child(c);
        circles.push_back(c);
        
    }

    isAllPerfect = true;
    isFullCombo = true;
    String mapToLoad = "";
    if (!GameGlobal::selectedMapPath.empty()) {
        mapToLoad = String(GameGlobal::selectedMapPath.c_str());
    }
    
    if (mapToLoad == "") {
        mapToLoad = "res://resource-media/map/Template-ChronoR-BeatMap-hui.csv"; 
    }

    load_beatmap_from_csv(mapToLoad);
    String fullPath = ProjectSettings::get_singleton()->globalize_path("res://resource-media/sound/music/demo-sample/hui_.wav");
    audioEngine->play_audio(fullPath);
}

void RhythmGameController::_process(double delta)
{
    if (audioEngine && audioEngine->is_playing())
    {
        double rawTime = audioEngine->get_audio_time();
        if (songDuration > 0.1) {
            double progress = (rawTime / songDuration) * 100.0;
            progressBar->set_value(progress);
        }
        double adjustedTime = rawTime - userAudioOffset;

        for (auto *c : circles) {
            c->update_state(adjustedTime, delta);
        }
    if (!isGameEnded && songDuration > 0 && rawTime >= songDuration) {
        isGameEnded = true;
        
        Color themeColor = Color(1, 1, 1);
        String text = "TUNING FINISH";
        
        if (isAllPerfect) {
            text = "ALL TUNED";
            themeColor = Color(1, 0.9, 0.2);
        } else if (isFullCombo) {
            text = "FULL ADJUSTED";
            themeColor = Color(0.2, 0.8, 1.0);
        }
            play_result_animation(text, themeColor);
        }
    }
    if (comboTextLabel) {
        if (comboLabel) {
            Color cText = comboTextLabel->get_modulate();
            cText.a = comboLabel->get_modulate().a;
            comboTextLabel->set_modulate(cText);
        }
    }   
}

double RhythmGameController::beat_to_time(double beat, double startBpm, double offset, const std::vector<TimingPoint> &timings)
{
    double currentTime = offset;
    double currentBeat = 0.0;
    double currentBpm = startBpm;

    for (const auto &tp : timings)
    {
        if (beat < tp.beat)
            break;

        double beatDiff = tp.beat - currentBeat;
        currentTime += beatDiff * (60.0 / currentBpm);

        currentBeat = tp.beat;
        currentBpm = tp.newBpm;
    }

    double remainingBeats = beat - currentBeat;
    currentTime += remainingBeats * (60.0 / currentBpm);

    return currentTime;
}

void RhythmGameController::load_beatmap_from_csv(String path)
{
    if (circles.size() < 2) return;

    Ref<FileAccess> file = FileAccess::open(path, FileAccess::READ);
    if (file.is_null()) {
        UtilityFunctions::print("ERROR: Cannot open CSV: ", path);
        return;
    }

    BeatmapData map;
    map.startBpm = 120.0;
    map.offset = 0.0;
    bool isNoteSection = false;
    while (file->get_position() < file->get_length()) {
        PackedStringArray row = file->get_csv_line();
        
        if (row[0] == "Note Data" || row[0] == "Beat") {
            isNoteSection = true;
            continue;
        }

        if (row.size() >= 2) {
            String key = row[0];
            String val = row[1];
            if (key == "Title") map.title = val;
            else if (key == "Artist") map.artist = val;
            else if (key == "BPM") map.startBpm = val.to_float();
            else if (key == "Offset") map.offset = val.to_float();
            else if (key == "Difficulty")  map.difficulty = val;
            else if (key == "Level")  map.level = val;
            else if (key == "Mapper")  map.mapper = val;
            else if (key == "Illustrator")  map.illustrator = val;
            else if (key == "Description")  map.description = val;
        }

        if (row.size() >= 5) {
            if (row[3] == "anomaly") {
                TimingPoint tp;
                tp.beat = row[0].to_float();
                tp.newBpm = row[4].to_float();
                
                if (row.size() >= 6) tp.numerator = row[5].to_int();
                else tp.numerator = 4;

                if (row.size() >= 7) tp.denominator = row[6].to_int();
                else tp.denominator = 4;

                map.timingPoints.push_back(tp);
            }
        }
    }

    mapTitle = map.title;
    mapArtist = map.artist;
    mapBPM = map.startBpm;
    mapOffset = map.offset;
    
    mapDifficulty = map.difficulty;
    mapLevel = map.level;
    mapMapper = map.mapper;
    mapIllustrator = map.illustrator;
    mapDescription = map.description;

    if (titleLabel) {
        titleLabel->set_text(mapTitle);
    }

    if (difficultyLabel) {
        difficultyLabel->set_text(mapDifficulty + " " + mapLevel);
    }

    std::sort(map.timingPoints.begin(), map.timingPoints.end(), [](const TimingPoint& a, const TimingPoint& b) {
        return a.beat < b.beat;
    });

    file->seek(0); 

    RhythmCircle *leftCircle = circles[0];
    RhythmCircle *rightCircle = circles[1];
    leftCircle->set_start_bpm(map.startBpm);
    rightCircle->set_start_bpm(map.startBpm);

    std::vector<NoteData> tempLeftNotes;
    std::vector<NoteData> tempRightNotes;

    double calculatedMaxTime = 0.0;
    isNoteSection = false;
    while (!file->eof_reached()) {
        PackedStringArray row = file->get_csv_line();

        if (!isNoteSection) {
            if (row[0] == "Beat" && row[1] == "Lane") {
                isNoteSection = true;
            }
            continue;
        }
        if (row.size() < 4) continue; 
        
        if (!row[0].is_valid_float()) continue;

        double beat = row[0].to_float();
        int lane = row[1].to_int();
        int circleId = row[2].to_int();
        String typeStr = row[3].strip_edges();
        
        double param = (row.size() >= 5) ? row[4].to_float() : 0.0;
        double param2 = (row.size() >= 6) ? row[5].to_float() : 0.0;
        double param3 = (row.size() >= 7) ? row[6].to_float() : 0.0;

        double time = beat_to_time(beat, map.startBpm, map.offset, map.timingPoints);
        double endTime = time;
        
        if (typeStr == "hold") {
            if (param <= 0) param = 1.0; 
            endTime = beat_to_time(beat + param, map.startBpm, map.offset, map.timingPoints);
        }

        double thisNoteFinish = (typeStr == "hold") ? endTime : time;
        if (thisNoteFinish > calculatedMaxTime) {
            calculatedMaxTime = thisNoteFinish;
        }

        NoteType type = NOTE_SINGLE;
        if (typeStr == "hold") type = NOTE_HOLD;
        else if (typeStr == "reverse") type = NOTE_REVERSE;
        else if (typeStr == "overclock") type = NOTE_OVERCLOCK;
        else if (typeStr == "overheat") type = NOTE_OVERHEAT;
        else if (typeStr == "anomaly") type = NOTE_ANORMALY;

        NoteData newNote = {time, lane, type, param, param2, param3, endTime};

        if (type == NOTE_ANORMALY) {
            tempLeftNotes.push_back(newNote);
            tempRightNotes.push_back(newNote);
        } 
        else {
            if (circleId == 0) tempLeftNotes.push_back(newNote);
            else if (circleId == 1) tempRightNotes.push_back(newNote);
        }
    }
    
    file->close();
    
    auto sortRule = [](const NoteData &a, const NoteData &b) {
        if (Math::is_equal_approx(a.time, b.time)) return a.type == NOTE_ANORMALY;
        return a.time < b.time;
    };
    std::sort(tempLeftNotes.begin(), tempLeftNotes.end(), sortRule);
    std::sort(tempRightNotes.begin(), tempRightNotes.end(), sortRule);

    for (const auto &n : tempLeftNotes) leftCircle->add_note(n);
    for (const auto &n : tempRightNotes) rightCircle->add_note(n);
    totalNotesInMap = circles[0]->get_notes_count() + circles[1]->get_notes_count(); 
    
    totalNotesInMap = 0;
    for(auto* c : circles) {
        if(c) totalNotesInMap += c->get_notes_count();
    }

    maxRawScore = totalNotesInMap * 2;
    currentRawScore = 0;
    currentScore = 0;
    currentAccuracy = 100.0;
    hasMissed = false;
    
    if (ratingLabel) ratingLabel->set_text("0.00");
    if (gradeLabel) gradeLabel->set_text("?");
    if (calculatedMaxTime > 0) {
        songDuration = calculatedMaxTime + 0.2;
    } else {
        songDuration = 120.0;
    }

    UtilityFunctions::print("Map Loaded. Max Beat Time: ", calculatedMaxTime, "s | Song Duration: ", songDuration, "s");
}

void RhythmGameController::_unhandled_input(const Ref<InputEvent> &event) {
    
    if (!audioEngine || !audioEngine->is_playing()) return;

    Ref<InputEventKey> keyEvent = event;

    if (keyEvent.is_valid() && !keyEvent->is_echo()) {
        Key key = keyEvent->get_keycode();
        
        if (key == KEY_ESCAPE && keyEvent->is_pressed()) {
            get_tree()->quit();
            return;
        }

        if (key == KEY_QUOTELEFT && keyEvent->is_pressed()) {
            get_tree()->reload_current_scene();
            return;
        }

        double currentTime = audioEngine->get_audio_time();
        double adjustedTime = currentTime - userAudioOffset;

        if (keyEvent->is_pressed()) {
            
            RhythmCircle* targetCircle = nullptr;
            double globalMinDist = 999999.0;

            for (auto* c : circles) {
                double dist = c->get_closest_hittable_distance(adjustedTime);
                
                if (dist != -1.0 && dist < globalMinDist) {
                    globalMinDist = dist;
                    targetCircle = c;
                }
            }

            if (targetCircle) {
                targetCircle->process_input(-1, adjustedTime);

                for (auto* c : circles) {
                    if (c != targetCircle) { 
                         c->force_hit_anomaly(adjustedTime); 
                    }
                }
            }
        } 
        else {
            for (auto* c : circles) c->process_release(-1, adjustedTime);
        }
    }
}

void RhythmGameController::set_visible_window(double p_value) {
    visibleWindow = p_value;
    for (RhythmCircle* c : circles) {
        if (c) c->set_visible_window(visibleWindow);
    }
}

void RhythmGameController::_on_hit_judgement(String result, int combo) {
    int previousCombo = globalCombo;

    if (comboTween.is_valid()) comboTween->kill();

    bool isComboBreak = (result == "MISS" && previousCombo > 0);
    
    if (isComboBreak) {
        comboTween = create_tween();
        comboTween->set_parallel(true);
    }
    const int RAW_PERFECT = 2;
    const int RAW_GOOD = 1;
    const int RAW_MISS = 0;
    int hitRaw = 0;

    if (result == "MISS") {
        isAllPerfect = false;
        isFullCombo = false;
        hasMissed = true;
        globalCombo = 0;
        hitRaw = RAW_MISS;
    } 
    else {
        if (result == "GOOD") {
            isAllPerfect = false;
            hitRaw = RAW_GOOD;
        } else {
            hitRaw = RAW_PERFECT;
        }
        globalCombo++;
    }
    
    currentRawScore += hitRaw;
    totalNotesProcessed++;
    
    int currentMax = totalNotesProcessed * 2;
    currentAccuracy = (currentMax > 0) ? ((double)currentRawScore / currentMax) * 100.0 : 100.0;

    if (scoreLabel) scoreLabel->set_text(String::num_int64(currentScore).pad_zeros(7));
    if (accuracyLabel) accuracyLabel->set_text(String::num(currentAccuracy, 2) + "%");

    String currentGrade = calculate_grade(currentScore, currentAccuracy, isFullCombo, isAllPerfect);
    
    double levelVal = mapLevel.is_valid_float() ? mapLevel.to_float() : 1.0;
    double currentRating = calculate_rating(currentScore, currentAccuracy, levelVal);

    if (maxRawScore > 0) {
        currentScore = (int)(((double)currentRawScore / maxRawScore) * 1000000.0);
    }

    if (gradeLabel) {
        gradeLabel->set_text(currentGrade);
        
        if (currentGrade == "PS") gradeLabel->set_modulate(Color(0, 1, 1));
        else if (currentGrade == "AS") gradeLabel->set_modulate(Color(1, 0.8, 0));
        else if (currentGrade.begins_with("S")) gradeLabel->set_modulate(Color(1, 1, 0));
        else gradeLabel->set_modulate(Color(1, 1, 1));
    }

    if (ratingLabel) {
        ratingLabel->set_text(String::num(currentRating, 2));
    }
    
    Color targetColor;
    if (result == "MISS") {
        targetColor = Color(1, 0.2, 0.2, 1);
    } else {
        if (isAllPerfect) targetColor = Color(1, 0.9, 0.2, 1);
        else if (isFullCombo) targetColor = Color(0.2, 0.8, 1.0, 1);
        else targetColor = Color(1, 1, 1, 1);
    }

    if (comboLabel) {
        if (result == "MISS") {
            if (previousCombo > 0) {
                comboLabel->set_modulate(targetColor);
                comboLabel->set_scale(Vector2(1.0, 1.0));
                comboTween->tween_property(comboLabel, "modulate:a", 0.0, 0.5);
            } 
            else {
                Color c = targetColor; c.a = 0.0;
                comboLabel->set_modulate(c);
            }
        } 
        else {
            comboLabel->set_text(String::num_int64(globalCombo));
            comboLabel->set_visible(true);
            comboLabel->set_modulate(targetColor);
            comboLabel->set_scale(Vector2(1.0, 1.0));
        }
    }

    if (comboTextLabel) {
        if (result == "MISS") {
            if (previousCombo > 0) {
                comboTextLabel->set_modulate(targetColor);
                comboTextLabel->set_scale(Vector2(1.0, 1.0));
                comboTween->tween_property(comboTextLabel, "modulate:a", 0.0, 0.5);
            } else {
                Color c = targetColor; c.a = 0.0;
                comboTextLabel->set_modulate(c);
            }
        } 
        else {
            comboTextLabel->set_visible(true);
            comboTextLabel->set_modulate(targetColor);
            comboTextLabel->set_scale(Vector2(1.0, 1.0));
        }
    }
}
void RhythmGameController::play_result_animation(String text, Color themeColor) {
    if (!resultAnim) return;

    Size2 screenSize = get_viewport_rect().size;
    
    float targetScale = (screenSize.x * 0.7) / 1920.0;
    
    resultAnim->set_scale(Vector2(targetScale, targetScale));
    resultAnim->set_position(screenSize / 2.0);

    resultAnim->set_visible(true);
    resultAnim->set_modulate(themeColor);

    String animName = "tuning_finish";
    if (text == "ALL TUNED") animName = "all_tuned";
    else if (text == "FULL ADJUSTED") animName = "full_adjusted";

    resultAnim->stop();
    resultAnim->play(animName);
    resultAnim->set_visible(true);
    resultAnim->set_modulate(themeColor);

    Ref<AudioStream> targetSound;
    float finalVolumeDb = resultMasterVolumeDb;

    if (text == "ALL TUNED") {
        resultAnim->play("all_tuned");
        targetSound = sfxAllTuned;
        finalVolumeDb += sfxAllTunedVolumeDb;
    } 
    else if (text == "FULL ADJUSTED") {
        resultAnim->play("full_adjusted");
        targetSound = sfxFullAdjusted;
        finalVolumeDb += sfxFullAdjustedVolumeDb;
    } 
    else {
        resultAnim->play("tuning_finish");
        targetSound = sfxTuningFinish;
        finalVolumeDb += sfxTuningFinishVolumeDb;
    }

    
    Size2 currentScreenSize = get_viewport_rect().size;

    Ref<SpriteFrames> frames = resultAnim->get_sprite_frames();
    
    if (frames.is_valid() && frames->has_animation(animName)) {
        
        Ref<Texture2D> firstFrameTex = frames->get_frame_texture(animName, 0);
        
        if (firstFrameTex.is_valid()) {
            Size2 srcSize = firstFrameTex->get_size();
            
            if (srcSize.x > 0) {
                float targetWidth = currentScreenSize.x * 0.7;
                float scaleFactor = targetWidth / srcSize.x;
                
                resultAnim->set_scale(Vector2(scaleFactor, scaleFactor));
            }
        }
    }
    
    resultAnim->set_position(currentScreenSize / 2.0);

    if (targetSound.is_valid()) {
        AudioStreamPlayer* sfxPlayer = memnew(AudioStreamPlayer);
        sfxPlayer->set_stream(targetSound);
        
        sfxPlayer->set_volume_db(finalVolumeDb);
        
        add_child(sfxPlayer);
        sfxPlayer->play();
        sfxPlayer->connect("finished", Callable(sfxPlayer, "queue_free"));
    }
}

void RhythmGameController::reset_game_state() {
    currentScore = 0;
    currentAccuracy = 100.0;
    totalNotesProcessed = 0;
    maxPossibleScore = 0;
    globalCombo = 0;
    
    isAllPerfect = true;
    isFullCombo = true;

    if (accuracyLabel) accuracyLabel->set_text("100.00%");
}



double RhythmGameController::calculate_rating(int score, double accuracy, double level) {
    
    double factor = 0.0;
    
    if (score >= 1000000) factor = 5.0;
    else if (score >= 990000) factor = 4.8 + ((score - 990000) / 10000.0) * 0.2;
    else if (score >= 950000) factor = 4.0 + ((score - 950000) / 40000.0) * 0.8;
    else if (score >= 900000) factor = 3.0 + ((score - 900000) / 50000.0) * 1.0;
    else factor = ((double)score / 900000.0) * 3.0;

    return level * factor;
}

String RhythmGameController::calculate_grade(int score, double accuracy, bool fc, bool ap) {
    if (ap || score == 1000000) return "PS";

    if (fc) return "AS";

    if (score >= 990000) return "S+";
    if (score >= 970000) return "S";
    if (score >= 950000) return "A+";
    if (score >= 900000) return "A";
    if (score >= 850000) return "B+";
    if (score >= 800000) return "B";
    if (score >= 700000) return "C+";
    if (score >= 600000) return "C";
    if (score >= 500000) return "D";
    
    return "F";
}