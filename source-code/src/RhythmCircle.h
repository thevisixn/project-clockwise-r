#pragma once

#include "BeatmapStructs.h"
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/line2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <vector>

namespace godot {

class RhythmCircle : public Node2D {
  GDCLASS(RhythmCircle, Node2D)

private:
  double baseRadius = 476.0;
  double laneGap = 133.0;
  int totalLanes = 2;
  double visibleWindow = 1.5;
  int currentCombo = 0;

  double volSingle = 0.0;
  double volHold = 0.0;
  double volReverse = 0.0;
  double volOverclock = 0.0;
  double volOverheat = 0.0;

  std::vector<NoteData> notes;
  double currentBPM;
  double baseSpeed;
  double startBPM = 120.0;

  double fadeSpeed = 2.0;
  std::vector<CircleEvent> events;

  Sprite2D *judgementLine = nullptr;
  std::vector<Sprite2D *> noteSprites;
  std::vector<Line2D *> noteTails;
  std::vector<Sprite2D *> noteCaps;
  std::vector<Line2D *> trackLines;
  Ref<PackedScene> hitEffectScene;

  Ref<Texture2D> texSingle;
  Ref<Texture2D> texReverse;
  Ref<Texture2D> texOverclock;
  Ref<Texture2D> texOverheat;
  Ref<Texture2D> texLine;
  Ref<Texture2D> texAnomaly;
  Ref<Texture2D> texHoldTail;
  Ref<Texture2D> texHoldCap;
  Ref<Texture2D> texCenterCap;
  Sprite2D *centerCapSprite = nullptr;

  double hitWindowPerfect = 0.05;
  double hitWindowGood = 0.1;
  double hitWindowMiss = 0.15;

  double userAudioOffset = 0.0;
  std::vector<AudioStreamPlayer *> sfxPool;
  int poolSize = 32;

  AudioStreamPlayer *get_free_sfx_player();
  Ref<AudioStream> sfxSingle;
  Ref<AudioStream> sfxHold;
  Ref<AudioStream> sfxReverse;
  Ref<AudioStream> sfxOverclock;
  Ref<AudioStream> sfxOverheat;

  double currentAlpha = 1.0;
  double targetAlpha = 1.0;
  bool isActive = true;

protected:
  static void _bind_methods();

public:
  RhythmCircle();
  ~RhythmCircle();

  void _ready() override;
  void _draw() override;
  void update_state(double audioTime, double delta);
  void add_note(NoteData note);
  void set_bpm(double bpm);
  void set_start_bpm(double bpm) {
    startBPM = bpm;
    currentBPM = bpm;
    baseSpeed = bpm / 240.0;
  }

  double calculate_angle_at_time(double targetTime);
  Vector2 get_position_on_circle(double angleRad, double laneIndex);

  void set_base_radius(double value);
  double get_base_radius() const;

  void set_lane_gap(double value);
  double get_lane_gap() const;

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

  void set_tex_hold_cap(const Ref<Texture2D> &p_tex) { texHoldCap = p_tex; }
  Ref<Texture2D> get_tex_hold_cap() const { return texHoldCap; }


  void set_tex_center_cap(const Ref<Texture2D> &p_texture) {
    texCenterCap = p_texture;
  }
  Ref<Texture2D> get_tex_center_cap() const { return texCenterCap; }

  void set_hit_effect_scene(const Ref<PackedScene> &p_scene) {
    hitEffectScene = p_scene;
  }
  Ref<PackedScene> get_hit_effect_scene() const { return hitEffectScene; }

  void process_input(int laneIndex, double currentAudioTime);

  void on_note_hit(int noteIndex, HitResult result);

  void set_user_audio_offset(double value) { userAudioOffset = value; }
  double get_user_audio_offset() const { return userAudioOffset; }

  void set_sfx_single(const Ref<AudioStream> &p_stream) {
    sfxSingle = p_stream;
  }
  void set_sfx_hold(const Ref<AudioStream> &p_stream) { sfxHold = p_stream; }
  void set_sfx_reverse(const Ref<AudioStream> &p_stream) {
    sfxReverse = p_stream;
  }
  void set_sfx_overclock(const Ref<AudioStream> &p_stream) {
    sfxOverclock = p_stream;
  }
  void set_sfx_overheat(const Ref<AudioStream> &p_stream) {
    sfxOverheat = p_stream;
  }
  void process_release(int laneIndex, double audioTime);

  void set_visible_window(double p_value) { visibleWindow = p_value; }
  double get_visible_window() const { return visibleWindow; }

  void spawn_hit_effect(Vector2 pos, Color color);

  void set_vol_single(double v) { volSingle = v; }
  void set_vol_hold(double v) { volHold = v; }
  void set_vol_reverse(double v) { volReverse = v; }
  void set_vol_overclock(double v) { volOverclock = v; }
  void set_vol_overheat(double v) { volOverheat = v; }



  void set_fade_speed(double val) { fadeSpeed = val; }
  double get_fade_speed() const { return fadeSpeed; }

  double get_closest_hittable_distance(double currentAudioTime);

  void clear_simultaneous_anomaly(double hitTime);

  void force_hit_anomaly(double targetTime);

  int get_notes_count() const { return notes.size(); }


  void set_active_state(bool active);


  void add_event(CircleEvent evt);


  void process_events(double currentAudioTime);


  bool is_circle_active() const { return isActive; }
};

}
