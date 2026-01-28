#pragma once

#include "JuceAudioEngine.h"
#include "RhythmCircle.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/interval_tweener.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/method_tweener.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <vector>

namespace godot {

class RhythmGameController : public Node2D {
  GDCLASS(RhythmGameController, Node2D)

private:
  JuceAudioEngine *audioEngine = nullptr;
  std::vector<RhythmCircle *> circles;

  CanvasLayer *uiLayer = nullptr;
  ProgressBar *progressBar = nullptr;
  Label *comboLabel = nullptr;
  Label *comboTextLabel = nullptr;
  Label *scoreLabel = nullptr;
  Ref<Tween> comboTween;
  double songDuration = 1.0;
  int globalCombo = 0;

  bool isAllPerfect = true;
  bool isFullCombo = true;

  AnimatedSprite2D *resultAnim = nullptr;

  Ref<AudioStream> sfxAllTuned;
  Ref<AudioStream> sfxFullAdjusted;
  Ref<AudioStream> sfxTuningFinish;
  float resultMasterVolumeDb = 0.0f;
  float sfxAllTunedVolumeDb = 0.0f;
  float sfxFullAdjustedVolumeDb = 0.0f;
  float sfxTuningFinishVolumeDb = 0.0f;
  bool isGameEnded = false;

  double volMusic = 0.0;

  double volSingle = 0.0;
  double volHold = 0.0;
  double volReverse = 0.0;
  double volOverclock = 0.0;
  double volOverheat = 0.0;

  Ref<Texture2D> texSingle;
  Ref<Texture2D> texReverse;
  Ref<Texture2D> texOverclock;
  Ref<Texture2D> texOverheat;
  Ref<Texture2D> texAnomaly;
  Ref<Texture2D> texLine;
  Ref<Texture2D> texHoldTail;
  Ref<Texture2D> texBackground;
  Ref<PackedScene> hitEffectScene;

  Ref<Texture2D> texCenterCap;

  double beat_to_time(double beat, double startBpm, double offset,
                      const std::vector<TimingPoint> &timings);
  double userAudioOffset = 0.0;
  double visibleWindow = 1.5;
  Ref<AudioStream> sfxSingle;
  Ref<AudioStream> sfxHold;
  Ref<AudioStream> sfxReverse;
  Ref<AudioStream> sfxOverclock;
  Ref<AudioStream> sfxOverheat;

  String mapTitle;
  String mapArtist;
  double mapBPM = 120.0;
  double mapOffset = 0.0;
  String mapDifficulty;
  String mapLevel;
  String mapMapper;
  String mapIllustrator;
  String mapDescription;

  int currentScore = 0;
  double currentAccuracy = 100.0;
  int totalNotesInMap = 0;
  int maxRawScore = 0;
  int currentRawScore = 0;

  bool hasMissed = false;

  Label *ratingLabel = nullptr;
  Label *gradeLabel = nullptr;

  int totalNotesProcessed = 0;
  int maxPossibleScore = 0;

  Label *accuracyLabel = nullptr;
  Label *titleLabel = nullptr;
  Label *difficultyLabel = nullptr;


  Vector2 leftCirclePosDefault = Vector2(-693, 0);
  Vector2 rightCirclePosDefault = Vector2(693, 0);
  Vector2 centerPos = Vector2(0, 0);


  bool isLeftActive = true;
  bool isRightActive = true;


  double circleFadeSpeed = 2.0;

protected:
  static void _bind_methods();

public:
  RhythmGameController();
  ~RhythmGameController();

  void _ready() override;
  void _process(double delta) override;
  void _unhandled_input(const Ref<InputEvent> &event) override;

  void load_beatmap_from_csv(String path);

  void set_tex_single(const Ref<Texture2D> &p_tex) { texSingle = p_tex; }
  Ref<Texture2D> get_tex_single() const { return texSingle; }

  void set_tex_reverse(const Ref<Texture2D> &p_tex) { texReverse = p_tex; }
  Ref<Texture2D> get_tex_reverse() const { return texReverse; }

  void set_tex_overclock(const Ref<Texture2D> &p_tex) { texOverclock = p_tex; }
  Ref<Texture2D> get_tex_overclock() const { return texOverclock; }

  void set_tex_overheat(const Ref<Texture2D> &p_tex) { texOverheat = p_tex; }
  Ref<Texture2D> get_tex_overheat() const { return texOverheat; }

  void set_tex_line(const Ref<Texture2D> &p_tex) { texLine = p_tex; }
  Ref<Texture2D> get_tex_line() const { return texLine; }

  void set_tex_anomaly(const Ref<Texture2D> &p_tex) { texAnomaly = p_tex; }
  Ref<Texture2D> get_tex_anomaly() const { return texAnomaly; }

  void set_tex_hold_tail(const Ref<Texture2D> &p_tex) { texHoldTail = p_tex; }
  Ref<Texture2D> get_tex_hold_tail() const { return texHoldTail; }


  void set_tex_center_cap(const Ref<Texture2D> &p_tex) { texCenterCap = p_tex; }
  Ref<Texture2D> get_tex_center_cap() const { return texCenterCap; }

  void set_user_audio_offset(double value) { userAudioOffset = value; }
  double get_user_audio_offset() const { return userAudioOffset; }

  void set_sfx_single(const Ref<AudioStream> &p_stream) {
    sfxSingle = p_stream;
  }
  Ref<AudioStream> get_sfx_single() const { return sfxSingle; }

  void set_sfx_hold(const Ref<AudioStream> &p_stream) { sfxHold = p_stream; }
  Ref<AudioStream> get_sfx_hold() const { return sfxHold; }

  void set_sfx_reverse(const Ref<AudioStream> &p_stream) {
    sfxReverse = p_stream;
  }
  Ref<AudioStream> get_sfx_reverse() const { return sfxReverse; }

  void set_sfx_overclock(const Ref<AudioStream> &p_stream) {
    sfxOverclock = p_stream;
  }
  Ref<AudioStream> get_sfx_overclock() const { return sfxOverclock; }

  void set_sfx_overheat(const Ref<AudioStream> &p_stream) {
    sfxOverheat = p_stream;
  }
  Ref<AudioStream> get_sfx_overheat() const { return sfxOverheat; }

  void set_visible_window(double p_value);
  double get_visible_window() const { return visibleWindow; }

  void set_hit_effect_scene(const Ref<PackedScene> &p_scene) {
    hitEffectScene = p_scene;
  }
  Ref<PackedScene> get_hit_effect_scene() const { return hitEffectScene; }

  void set_tex_background(const Ref<Texture2D> &p_tex) {
    texBackground = p_tex;
  }
  Ref<Texture2D> get_tex_background() const { return texBackground; }



  void set_circle_fade_speed(double val);
  double get_circle_fade_speed() const { return circleFadeSpeed; }

  void set_vol_music(double val);
  double get_vol_music() const { return volMusic; }

  void set_vol_single(double val);
  double get_vol_single() const { return volSingle; }

  void set_vol_hold(double val);
  double get_vol_hold() const { return volHold; }

  void set_vol_reverse(double val);
  double get_vol_reverse() const { return volReverse; }

  void set_vol_overclock(double val);
  double get_vol_overclock() const { return volOverclock; }

  void set_vol_overheat(double val);
  double get_vol_overheat() const { return volOverheat; }

  void _on_hit_judgement(String result, int combo);

  void set_sfx_all_tuned(const Ref<AudioStream> &p_stream) {
    sfxAllTuned = p_stream;
  }
  Ref<AudioStream> get_sfx_all_tuned() const { return sfxAllTuned; }

  void set_sfx_full_adjusted(const Ref<AudioStream> &p_stream) {
    sfxFullAdjusted = p_stream;
  }
  Ref<AudioStream> get_sfx_full_adjusted() const { return sfxFullAdjusted; }

  void set_sfx_tuning_finish(const Ref<AudioStream> &p_stream) {
    sfxTuningFinish = p_stream;
  }
  Ref<AudioStream> get_sfx_tuning_finish() const { return sfxTuningFinish; }

  void set_result_master_volume_db(float p_volume) {
    resultMasterVolumeDb = p_volume;
  }
  float get_result_master_volume_db() const { return resultMasterVolumeDb; }

  void set_sfx_all_tuned_volume_db(float p_volume) {
    sfxAllTunedVolumeDb = p_volume;
  }
  float get_sfx_all_tuned_volume_db() const { return sfxAllTunedVolumeDb; }

  void set_sfx_full_adjusted_volume_db(float p_volume) {
    sfxFullAdjustedVolumeDb = p_volume;
  }
  float get_sfx_full_adjusted_volume_db() const {
    return sfxFullAdjustedVolumeDb;
  }

  void set_sfx_tuning_finish_volume_db(float p_volume) {
    sfxTuningFinishVolumeDb = p_volume;
  }
  float get_sfx_tuning_finish_volume_db() const {
    return sfxTuningFinishVolumeDb;
  }

  void play_result_animation(String text, Color themeColor);

  void set_accuracy_label(Label *p_label) { accuracyLabel = p_label; }
  Label *get_accuracy_label() const { return accuracyLabel; }

  void set_rating_label(Label *p_label) { ratingLabel = p_label; }
  Label *get_rating_label() const { return ratingLabel; }

  void set_grade_label(Label *p_label) { gradeLabel = p_label; }
  Label *get_grade_label() const { return gradeLabel; }

  void reset_game_state();

  String calculate_grade(int score, double accuracy, bool isFullCombo,
                         bool isAllPerfect);
  double calculate_rating(int score, double accuracy, double mapLevel);

  void set_score_label(Label *p_label) { scoreLabel = p_label; }
  Label *get_score_label() const { return scoreLabel; }

  void set_title_label(Label *p_label) { titleLabel = p_label; }
  Label *get_title_label() const { return titleLabel; }

  void set_difficulty_label(Label *p_label) { difficultyLabel = p_label; }
  Label *get_difficulty_label() const { return difficultyLabel; }
};

}
