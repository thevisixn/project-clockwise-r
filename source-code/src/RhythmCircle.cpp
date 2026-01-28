#include "RhythmCircle.h"
#include "BeatmapStructs.h"
#include <algorithm>
#include <cmath>
#include <godot_cpp/classes/gradient.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void RhythmCircle::_bind_methods() {

  ClassDB::bind_method(D_METHOD("set_tex_single", "texture"),
                       &RhythmCircle::set_tex_single);
  ClassDB::bind_method(D_METHOD("get_tex_single"),
                       &RhythmCircle::get_tex_single);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_single",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_single", "get_tex_single");

  ClassDB::bind_method(D_METHOD("set_tex_reverse", "texture"),
                       &RhythmCircle::set_tex_reverse);
  ClassDB::bind_method(D_METHOD("get_tex_reverse"),
                       &RhythmCircle::get_tex_reverse);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_reverse",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_reverse", "get_tex_reverse");

  ClassDB::bind_method(D_METHOD("set_tex_overclock", "texture"),
                       &RhythmCircle::set_tex_overclock);
  ClassDB::bind_method(D_METHOD("get_tex_overclock"),
                       &RhythmCircle::get_tex_overclock);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_overclock",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_overclock", "get_tex_overclock");

  ClassDB::bind_method(D_METHOD("set_tex_overheat", "texture"),
                       &RhythmCircle::set_tex_overheat);
  ClassDB::bind_method(D_METHOD("get_tex_overheat"),
                       &RhythmCircle::get_tex_overheat);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_overheat",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_overheat", "get_tex_overheat");

  ClassDB::bind_method(D_METHOD("set_tex_line", "texture"),
                       &RhythmCircle::set_tex_line);
  ClassDB::bind_method(D_METHOD("get_tex_line"), &RhythmCircle::get_tex_line);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_line",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_line", "get_tex_line");

  ClassDB::bind_method(D_METHOD("set_tex_anomaly", "texture"),
                       &RhythmCircle::set_tex_anomaly);
  ClassDB::bind_method(D_METHOD("get_tex_anomaly"),
                       &RhythmCircle::get_tex_anomaly);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_anomaly",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_anomaly", "get_tex_anomaly");

  ClassDB::bind_method(D_METHOD("set_tex_hold_tail", "texture"),
                       &RhythmCircle::set_tex_hold_tail);
  ClassDB::bind_method(D_METHOD("get_tex_hold_tail"),
                       &RhythmCircle::get_tex_hold_tail);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_hold_tail",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_hold_tail", "get_tex_hold_tail");

  ClassDB::bind_method(D_METHOD("set_base_radius", "radius"),
                       &RhythmCircle::set_base_radius);
  ClassDB::bind_method(D_METHOD("get_base_radius"),
                       &RhythmCircle::get_base_radius);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "base_radius"), "set_base_radius",
               "get_base_radius");

  ClassDB::bind_method(D_METHOD("set_lane_gap", "gap"),
                       &RhythmCircle::set_lane_gap);
  ClassDB::bind_method(D_METHOD("get_lane_gap"), &RhythmCircle::get_lane_gap);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lane_gap"), "set_lane_gap",
               "get_lane_gap");

  ClassDB::bind_method(D_METHOD("set_visible_window", "value"),
                       &RhythmCircle::set_visible_window);
  ClassDB::bind_method(D_METHOD("get_visible_window"),
                       &RhythmCircle::get_visible_window);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "visible_window"),
               "set_visible_window", "get_visible_window");

  ClassDB::bind_method(D_METHOD("set_tex_hold_cap", "texture"),
                       &RhythmCircle::set_tex_hold_cap);
  ClassDB::bind_method(D_METHOD("get_tex_hold_cap"),
                       &RhythmCircle::get_tex_hold_cap);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_hold_cap",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_hold_cap", "get_tex_hold_cap");

  ClassDB::bind_method(D_METHOD("set_hit_effect_scene", "scene"),
                       &RhythmCircle::set_hit_effect_scene);
  ClassDB::bind_method(D_METHOD("get_hit_effect_scene"),
                       &RhythmCircle::get_hit_effect_scene);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hit_effect_scene",
                            PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"),
               "set_hit_effect_scene", "get_hit_effect_scene");

  ClassDB::bind_method(D_METHOD("set_tex_center_cap", "texture"),
                       &RhythmCircle::set_tex_center_cap);
  ClassDB::bind_method(D_METHOD("get_tex_center_cap"),
                       &RhythmCircle::get_tex_center_cap);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_center_cap",
                            PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"),
               "set_tex_center_cap", "get_tex_center_cap");

  ClassDB::bind_method(D_METHOD("set_fade_speed", "val"),
                       &RhythmCircle::set_fade_speed);
  ClassDB::bind_method(D_METHOD("get_fade_speed"),
                       &RhythmCircle::get_fade_speed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_speed"), "set_fade_speed",
               "get_fade_speed");

  ADD_SIGNAL(MethodInfo("on_hit_judgement",
                        PropertyInfo(Variant::STRING, "result"),
                        PropertyInfo(Variant::INT, "combo")));
}

RhythmCircle::RhythmCircle() {}
RhythmCircle::~RhythmCircle() {}

void RhythmCircle::_ready() {
  judgementLine = memnew(Sprite2D);
  if (texLine.is_valid()) {
    judgementLine->set_texture(texLine);

    Vector2 s = texLine->get_size();
    judgementLine->set_offset(Vector2(0, -s.y / 2));
  }
  judgementLine->set_z_index(10);
  add_child(judgementLine);

  for (int i = 0; i < poolSize; i++) {
    AudioStreamPlayer *p = memnew(AudioStreamPlayer);
    p->set_max_polyphony(1);
    p->set_bus("Master");
    add_child(p);
    sfxPool.push_back(p);
  }

  centerCapSprite = memnew(Sprite2D);

  if (texCenterCap.is_valid()) {
    centerCapSprite->set_texture(texCenterCap);


    centerCapSprite->set_centered(true);


    centerCapSprite->set_offset(Vector2(0, 0));
  }


  centerCapSprite->set_position(Vector2(0, 0));


  centerCapSprite->set_z_index(11);


  add_child(centerCapSprite);

  for (int i = 0; i < totalLanes; i++) {
    Line2D *line = memnew(Line2D);

    double r = baseRadius - (i * laneGap);
    int segments = 128;

    for (int j = 0; j <= segments; j++) {
      double angle = (Math_PI * 2 * j) / segments;
      Vector2 p(Math::sin(angle) * r, -Math::cos(angle) * r);
      line->add_point(p);
    }

    line->set_width(2.0);
    line->set_default_color(Color(1, 1, 1, 0.25));
    line->set_texture_mode(Line2D::LINE_TEXTURE_NONE);

    line->set_z_index(-50);

    add_child(line);
    trackLines.push_back(line);
  }
}

AudioStreamPlayer *RhythmCircle::get_free_sfx_player() {
  for (auto *p : sfxPool) {
    if (!p->is_playing())
      return p;
  }
  return sfxPool[0];
}

bool compare_notes(const NoteData &a, const NoteData &b) {
  return a.time < b.time;
}

void RhythmCircle::set_base_radius(double value) {
  baseRadius = value;
  queue_redraw();
}
double RhythmCircle::get_base_radius() const { return baseRadius; }

void RhythmCircle::set_lane_gap(double value) {
  laneGap = value;
  queue_redraw();
}
double RhythmCircle::get_lane_gap() const { return laneGap; }

void RhythmCircle::_draw() {

  for (size_t i = 0; i < notes.size(); ++i) {
    if (notes[i].isHit && notes[i].finalResult != RESULT_MISS) {

      if (i < noteSprites.size() && noteSprites[i]->is_visible()) {

        Sprite2D *s = noteSprites[i];

        Color strokeColor = Color(1, 1, 1);
        if (notes[i].finalResult == RESULT_PERFECT) {
          strokeColor = Color(1, 0.9, 0.2);
        } else {
          strokeColor = Color(0.2, 0.8, 1.0);
        }

        strokeColor.a = s->get_modulate().a;

        double currentRadius = 32.0;

        if (s->get_texture().is_valid()) {
          double scaleWidth = s->get_texture()->get_width();
          currentRadius = scaleWidth * s->get_scale().x;
        }

        draw_arc(s->get_position(), currentRadius, 0, Math_PI * 2, 64,
                 strokeColor, 6.0);
      }
    }
  }
}

void RhythmCircle::add_note(NoteData note) {
  notes.push_back(note);

  Sprite2D *s = memnew(Sprite2D);

  switch (note.type) {
  case NOTE_SINGLE:
  case NOTE_HOLD:
    if (texSingle.is_valid())
      s->set_texture(texSingle);
    s->set_modulate(Color(1, 1, 1));
    s->set_z_index(-1);
    break;

  case NOTE_REVERSE:
    if (texReverse.is_valid())
      s->set_texture(texReverse);
    s->set_modulate(Color(0.6, 0.0, 0.8));
    s->set_z_index(-2);
    break;

  case NOTE_OVERCLOCK:
    if (texOverclock.is_valid())
      s->set_texture(texOverclock);
    else if (texSingle.is_valid())
      s->set_texture(texSingle);

    s->set_modulate(Color(0.0, 1.0, 0.0));
    s->set_z_index(-2);
    break;

  case NOTE_OVERHEAT:
    if (texOverheat.is_valid())
      s->set_texture(texOverheat);
    else if (texSingle.is_valid())
      s->set_texture(texSingle);

    s->set_modulate(Color(1.0, 0.0, 0.0));
    s->set_z_index(-2);
    break;
  case NOTE_ANORMALY:
    if (texAnomaly.is_valid())
      s->set_texture(texAnomaly);
    else if (texSingle.is_valid())
      s->set_texture(texSingle);

    s->set_modulate(Color(1.0, 1.0, 0.0));
    s->set_z_index(-1);
    break;
  default:
    break;
  case NOTE_CMD_HIDE:
    break;
  case NOTE_CMD_SHOW:
    break;
  }

  add_child(s);
  noteSprites.push_back(s);
  move_child(s, 0);

  Line2D *l = memnew(Line2D);
  l->set_visible(false);
  l->set_width(40.0);
  l->set_texture_mode(Line2D::LINE_TEXTURE_TILE);

  if (texHoldTail.is_valid()) {
    l->set_texture(texHoldTail);
  }

  l->set_z_index(-3);

  Ref<Gradient> grad;
  grad.instantiate();

  grad->set_color(0, Color(1, 1, 1, 1));
  grad->set_color(1, Color(1, 1, 1, 1));

  l->set_gradient(grad);

  add_child(l);
  noteTails.push_back(l);

  Sprite2D *cap = memnew(Sprite2D);

  if (note.type == NOTE_HOLD) {
    if (texHoldCap.is_valid())
      cap->set_texture(texHoldCap);
    else if (texSingle.is_valid())
      cap->set_texture(texSingle);

    cap->set_z_index(-2);
    cap->set_visible(false);
  } else {
    cap->set_visible(false);
  }

  add_child(cap);
  noteCaps.push_back(cap);
}

double RhythmCircle::calculate_angle_at_time(double targetTime) {
  double accumulatedAngle = 0.0;
  double lastTime = 0.0;

  double localBPM = startBPM;
  double localNum = 4.0;
  double localDen = 4.0;

  double barLength = localNum * (4.0 / localDen);
  double localSpeed = localBPM / (60.0 * barLength);

  double currentDir = 1.0;

  for (const auto &note : notes) {
    if (note.time > targetTime)
      break;

    double dt = note.time - lastTime;
    accumulatedAngle += dt * localSpeed * currentDir * (2.0 * Math_PI);
    lastTime = note.time;

    if (note.type == NOTE_REVERSE) {
      double stopDurationSec = (note.param / localBPM) * 60.0;
      if (targetTime < note.time + stopDurationSec)
        return accumulatedAngle;
      lastTime += stopDurationSec;
      currentDir *= -1.0;
    } else if (note.type == NOTE_OVERCLOCK || note.type == NOTE_OVERHEAT) {
      localSpeed *= note.param;
    } else if (note.type == NOTE_ANORMALY) {
      localBPM = note.param;

      if (note.param2 > 0.0)
        localNum = note.param2;
      if (note.param3 > 0.0)
        localDen = note.param3;

      barLength = localNum * (4.0 / localDen);
      localSpeed = localBPM / (60.0 * barLength);
    }
  }

  double remainingTime = targetTime - lastTime;
  if (remainingTime > 0) {
    accumulatedAngle +=
        remainingTime * localSpeed * currentDir * (2.0 * Math_PI);
  }

  return accumulatedAngle;
}

Vector2 RhythmCircle::get_position_on_circle(double angleRad,
                                             double laneIndex) {
  double r = baseRadius - (laneIndex * laneGap);

  return Vector2(Math::sin(angleRad) * r, -Math::cos(angleRad) * r);
}

double RhythmCircle::get_closest_hittable_distance(double currentAudioTime) {
  double minDiff = 999999.0;
  bool found = false;

  for (const auto &note : notes) {
    if (note.isHit)
      continue;

    double timeDiff = note.time - currentAudioTime;

    double hitWindow = 0.15;

    if (std::abs(timeDiff) <= hitWindow) {
      if (std::abs(timeDiff) < minDiff) {
        minDiff = std::abs(timeDiff);
        found = true;
      }
    }
  }

  return found ? minDiff : -1.0;
}

void RhythmCircle::clear_simultaneous_anomaly(double hitTime) {
  for (auto &note : notes) {
    if (!note.isHit && note.type == NOTE_ANORMALY) {
      if (std::abs(note.time - hitTime) < 0.001) {
        note.isHit = true;
      }
    }
  }
}

void RhythmCircle::force_hit_anomaly(double targetTime) {
  for (int i = 0; i < notes.size(); ++i) {
    if (!notes[i].isHit && notes[i].type == NOTE_ANORMALY) {
      if (Math::abs(notes[i].time - targetTime) <= 0.2) {

        notes[i].finalResult = RESULT_PERFECT;

        on_note_hit(i, RESULT_PERFECT);

        double angle = calculate_angle_at_time(notes[i].time);
        Vector2 hitPos = get_position_on_circle(angle, 0.5);
        spawn_hit_effect(hitPos, Color(1, 0.9, 0.2));
      }
    }
  }
}

void RhythmCircle::process_input(int inputLane, double currentAudioTime) {
  int bestNoteIndex = -1;
  double minDiff = 999999.0;

  for (size_t i = 0; i < notes.size(); ++i) {
    if (notes[i].isHit)
      continue;

    bool checkLane = (inputLane != -1);
    bool isSpecial =
        (notes[i].type == NOTE_REVERSE || notes[i].type == NOTE_OVERCLOCK ||
         notes[i].type == NOTE_OVERHEAT || notes[i].type == NOTE_ANORMALY);

    if (checkLane && !isSpecial && notes[i].lane != inputLane)
      continue;

    double diff = Math::abs(currentAudioTime - notes[i].time);

    if (diff <= hitWindowMiss && diff < minDiff) {
      minDiff = diff;
      bestNoteIndex = i;
    }
  }

  if (bestNoteIndex != -1) {
    HitResult result = RESULT_MISS;
    double diff = notes[bestNoteIndex].time - currentAudioTime;
    String resultName = "MISS";

    if (std::abs(diff) <= hitWindowPerfect) {
      result = RESULT_PERFECT;
      resultName = "PERFECT";
      currentCombo++;
    } else if (std::abs(diff) <= hitWindowGood) {
      result = RESULT_GOOD;
      resultName = "GOOD";
      currentCombo++;
    } else {
      result = RESULT_MISS;
      resultName = "MISS";
      currentCombo = 0;
    }

    emit_signal("on_hit_judgement", resultName, currentCombo);
    notes[bestNoteIndex].finalResult = result;

    if (result != RESULT_MISS) {
      double angle = calculate_angle_at_time(notes[bestNoteIndex].time);
      double visualLane = (double)notes[bestNoteIndex].lane;
      if (notes[bestNoteIndex].type == NOTE_REVERSE ||
          notes[bestNoteIndex].type == NOTE_OVERCLOCK ||
          notes[bestNoteIndex].type == NOTE_OVERHEAT ||
          notes[bestNoteIndex].type == NOTE_ANORMALY)
        visualLane = 0.5;

      Vector2 hitPos = get_position_on_circle(angle, visualLane);
      Color effectColor = (result == RESULT_PERFECT) ? Color(1, 0.9, 0.2)
                                                     : Color(0.2, 0.8, 1.0);
      spawn_hit_effect(hitPos, effectColor);
    }

    on_note_hit(bestNoteIndex, result);

    if (notes[bestNoteIndex].type == NOTE_ANORMALY) {
      clear_simultaneous_anomaly(notes[bestNoteIndex].time);
    }
  }
}

void RhythmCircle::on_note_hit(int index, HitResult result) {
  if (index >= notes.size())
    return;

  if (sfxSingle.is_valid()) {
    AudioStreamPlayer *p = get_free_sfx_player();
    p->set_stream(sfxSingle);
    p->set_volume_db(volSingle);
    p->play();
  }

  Ref<AudioStream> specialSFX;
  double targetVolume = 0.0;

  switch (notes[index].type) {
  case NOTE_REVERSE:
    specialSFX = sfxReverse;
    targetVolume = volReverse;
    break;
  case NOTE_ANORMALY:
    specialSFX = sfxReverse;
    targetVolume = volReverse;
    break;
  case NOTE_OVERCLOCK:
    specialSFX = sfxOverclock;
    targetVolume = volOverclock;
    break;
  case NOTE_OVERHEAT:
    specialSFX = sfxOverheat;
    targetVolume = volOverheat;
    break;
  case NOTE_HOLD:
    specialSFX = sfxHold;
    targetVolume = volHold;
    break;
  default:
    break;
  case NOTE_CMD_HIDE:
    break;
  case NOTE_CMD_SHOW:
    break;
  }

  if (specialSFX.is_valid()) {
    AudioStreamPlayer *p = get_free_sfx_player();
    p->set_stream(specialSFX);
    p->set_volume_db(targetVolume);
    p->play();

    if (notes[index].type == NOTE_HOLD) {
      notes[index].activeHoldPlayer = p;
    }
  }
  if (notes[index].type == NOTE_HOLD) {
    notes[index].isHit = true;
    notes[index].isHolding = true;

    UtilityFunctions::print("HOLD START!");
    return;
  }
  notes[index].isHit = true;

  if (index < noteSprites.size()) {

    Color c = noteSprites[index]->get_modulate();
    c.a = 1.0;
    noteSprites[index]->set_modulate(c);

    noteSprites[index]->set_z_index(9);
    noteSprites[index]->set_visible(true);
    UtilityFunctions::print(result == RESULT_PERFECT ? "PERFECT!" : "GOOD!");
  }
}


void RhythmCircle::add_event(CircleEvent evt) {
  events.push_back(evt);
  // เรียงลำดับตามเวลาเพื่อให้ Process ง่าย
  std::sort(events.begin(), events.end(),
            [](const CircleEvent &a, const CircleEvent &b) {
              return a.time < b.time;
            });
}


void RhythmCircle::process_events(double currentAudioTime) {
  for (auto &evt : events) {
    if (!evt.isProcessed && currentAudioTime >= evt.time) {
      evt.isProcessed = true;


      if (evt.type == NOTE_CMD_SHOW) {
        set_active_state(true);
      } else if (evt.type == NOTE_CMD_HIDE) {
        set_active_state(false);
      }
    }
  }
}

void RhythmCircle::update_state(double audioTime, double delta) {
  process_events(audioTime);

  double lineAngle = calculate_angle_at_time(audioTime);
  if (judgementLine) {
    judgementLine->set_rotation(lineAngle);
  }


  currentAlpha = Math::lerp(currentAlpha, targetAlpha, delta * fadeSpeed);


  Color c = get_modulate();
  c.a = currentAlpha;
  set_modulate(c);


  if (centerCapSprite) {
    Color capColor = centerCapSprite->get_modulate();
    capColor.a = currentAlpha; // ให้จางตามตัวแม่
    centerCapSprite->set_modulate(capColor);


    if (currentAlpha < 0.01) {
      centerCapSprite->set_visible(false);
    } else {
      centerCapSprite->set_visible(true);
    }
  }

  // ตัดการทำงานถ้ามองไม่เห็น (Performance Optimization)
  if (currentAlpha < 0.01) {
    if (is_visible())
      set_visible(false);
    return;
  } else {
    if (!is_visible())
      set_visible(true);
  }

  bool isAnyAnimationPlaying = false;

  for (size_t i = 0; i < notes.size(); ++i) {
    double timeDiff = notes[i].time - audioTime;

    if (timeDiff > visibleWindow) {
      if (i < noteSprites.size())
        noteSprites[i]->set_visible(false);
      if (i < noteTails.size())
        noteTails[i]->set_visible(false);
      if (i < noteCaps.size())
        noteCaps[i]->set_visible(false);
      continue;
    }

    if (timeDiff < -0.5 && !notes[i].isHolding) {
      if (i < noteSprites.size())
        noteSprites[i]->set_visible(false);
      if (i < noteTails.size())
        noteTails[i]->set_visible(false);
      if (i < noteCaps.size())
        noteCaps[i]->set_visible(false);
      continue;
    }

    if (!notes[i].isHit) {
      if (audioTime > notes[i].time + hitWindowMiss) {
        notes[i].isHit = true;
        notes[i].finalResult = RESULT_MISS;

        currentCombo = 0;
        emit_signal("on_hit_judgement", "MISS", 0);
      }
    }

    double ratio = 1.0 - (timeDiff / visibleWindow);
    ratio = std::clamp(ratio, 0.0, 1.0);

    if (i < noteTails.size()) {
      Line2D *tail = noteTails[i];
      Sprite2D *cap = noteCaps[i];

      bool shouldShow = (notes[i].type == NOTE_HOLD) && (!notes[i].isProcessed);

      if (shouldShow) {
        double tailStartTime = std::max(notes[i].time, audioTime);
        double visibleEdge = audioTime + visibleWindow;
        double tailEndTime = std::min(notes[i].endTime, visibleEdge);

        bool isTailClipped = (notes[i].endTime > visibleEdge);

        if (isTailClipped || notes[i].endTime < audioTime) {
          cap->set_visible(false);
        } else {
          cap->set_visible(true);

          double endAngle = calculate_angle_at_time(notes[i].endTime);
          double visualLane = (double)notes[i].lane;
          if (notes[i].type == NOTE_REVERSE ||
              notes[i].type == NOTE_OVERCLOCK || notes[i].type == NOTE_OVERHEAT)
            visualLane = 0.5;

          cap->set_position(get_position_on_circle(endAngle, visualLane));
          cap->set_rotation(endAngle);

          double capTargetSize = 64.0;
          double capTexSize = 64.0;
          if (cap->get_texture().is_valid())
            capTexSize = cap->get_texture()->get_width();
          double capBaseScale = capTargetSize / capTexSize;

          double capScale = 1.0;
          Color capColor = Color(1, 1, 1, 1);

          if (notes[i].isHolding) {
            capColor = Color(1, 1, 0, 1);
            capScale *= (1.2 + 0.1 * Math::sin(audioTime * 20.0));
          } else {
            double endRatio =
                1.0 - ((notes[i].endTime - audioTime) / visibleWindow);
            endRatio = std::clamp(endRatio, 0.0, 1.0);
            capColor.a = 0.7 * endRatio;
          }

          cap->set_scale(
              Vector2(capScale * capBaseScale, capScale * capBaseScale));
          cap->set_modulate(capColor);
          cap->set_z_index(-2);
        }

        if (tailStartTime >= tailEndTime) {
          tail->set_visible(false);
        } else {

          double rawStartAngle = calculate_angle_at_time(tailStartTime);
          double rawEndAngle = calculate_angle_at_time(tailEndTime);

          double currentLaneRadius = baseRadius - (notes[i].lane * laneGap);
          if (notes[i].type == NOTE_REVERSE ||
              notes[i].type == NOTE_OVERCLOCK ||
              notes[i].type == NOTE_OVERHEAT) {
            currentLaneRadius = baseRadius - (0.5 * laneGap);
          }

          double headOffsetAngle = 0.0;
          if (i < noteSprites.size() &&
              noteSprites[i]->get_texture().is_valid()) {
            Sprite2D *s = noteSprites[i];
            double rPx =
                (s->get_texture()->get_width() / 2.0) * s->get_scale().x;
            headOffsetAngle = (rPx * 0.8) / currentLaneRadius;
          }

          double capOffsetAngle = 0.0;
          if (!isTailClipped && cap->get_texture().is_valid()) {
            double rPx =
                (cap->get_texture()->get_width() / 2.0) * cap->get_scale().x;
            capOffsetAngle = (rPx * 0.8) / currentLaneRadius;
          }

          double angleDiff = rawEndAngle - rawStartAngle;

          if (Math::abs(angleDiff) <= (headOffsetAngle + capOffsetAngle)) {
            tail->set_visible(false);
          } else {
            tail->set_visible(true);
            tail->clear_points();

            double adjustedStartAngle = rawStartAngle;
            double adjustedEndAngle = rawEndAngle;

            if (angleDiff > 0) {
              adjustedStartAngle += headOffsetAngle;
              adjustedEndAngle -= capOffsetAngle;
            } else {
              adjustedStartAngle -= headOffsetAngle;
              adjustedEndAngle += capOffsetAngle;
            }

            int segments = 24;
            double adjAngleDiff = adjustedEndAngle - adjustedStartAngle;

            for (int j = 0; j <= segments; j++) {
              double t = (double)j / segments;
              double currentA = adjustedStartAngle + (adjAngleDiff * t);
              Vector2 pointPos =
                  get_position_on_circle(currentA, notes[i].lane);
              tail->add_point(pointPos);
            }

            Color baseColor = Color(1, 1, 1);
            double baseAlpha = 0.7;

            if (notes[i].isHolding) {
              baseColor = Color(1, 1, 0);
              baseAlpha = 0.9 + (0.1 * Math::sin(audioTime * 15.0));
            } else {
              baseAlpha = 0.7 * ratio;
            }
            baseColor.a = baseAlpha;

            Ref<Gradient> grad = tail->get_gradient();
            if (grad.is_valid()) {
              grad->set_color(0, baseColor);
              Color tailColor = baseColor;
              if (isTailClipped)
                tailColor.a = 0.0;
              else
                tailColor.a = baseAlpha;
              grad->set_color(1, tailColor);
            }
          }
        }
      }
    }
    if (i < noteSprites.size()) {
      Sprite2D *s = noteSprites[i];

      double targetTime = notes[i].time;

      if (notes[i].type == NOTE_HOLD && notes[i].isProcessed &&
          notes[i].finalResult != RESULT_MISS) {
        targetTime = notes[i].endTime;
      }

      double noteAngle = calculate_angle_at_time(targetTime);

      double visualLane = (double)notes[i].lane;
      if (notes[i].type == NOTE_REVERSE || notes[i].type == NOTE_OVERCLOCK ||
          notes[i].type == NOTE_OVERHEAT) {
        visualLane = 0.5;
      }
      s->set_position(get_position_on_circle(noteAngle, visualLane));
      s->set_rotation(noteAngle);

      if (notes[i].isHolding) {
        s->set_visible(false);

        if (audioTime >= notes[i].endTime) {
          notes[i].isHolding = false;
          notes[i].isProcessed = true;

          if (notes[i].activeHoldPlayer) {
            AudioStreamPlayer *p =
                Object::cast_to<AudioStreamPlayer>(notes[i].activeHoldPlayer);
            if (p)
              p->stop();
            notes[i].activeHoldPlayer = nullptr;
          }

          notes[i].finalResult = RESULT_PERFECT;

          double endAngle = calculate_angle_at_time(notes[i].endTime);

          s->set_position(get_position_on_circle(endAngle, visualLane));
          s->set_rotation(endAngle);

          s->set_visible(true);
          s->set_modulate(Color(1, 1, 1, 1));
          s->set_scale(Vector2(1, 1));
          s->set_z_index(20);

          if (i < noteCaps.size())
            noteCaps[i]->set_visible(false);
          if (i < noteTails.size())
            noteTails[i]->set_visible(false);

          emit_signal("on_hit_judgement", "PERFECT", currentCombo);
          spawn_hit_effect(s->get_position(), Color(1, 0.9, 0.2));
        } else {
          continue;
        }
      }

      double targetSize = 64.0;

      if (notes[i].type == NOTE_REVERSE || notes[i].type == NOTE_OVERCLOCK ||
          notes[i].type == NOTE_OVERHEAT) {
        targetSize = 31.0;
      }

      double textureSize = 64.0;
      if (s->get_texture().is_valid()) {
        textureSize = s->get_texture()->get_width();
      }

      double baseScale = targetSize / textureSize;

      Color targetColor = Color(1, 1, 1, 1);
      Vector2 targetScale = Vector2(1, 1);
      double distScale = 0.6 + (0.4 * ratio);

      if (notes[i].isHit) {

        if (notes[i].finalResult == RESULT_MISS) {
          s->set_visible(true);
          s->set_z_index(5);

          double timeSinceMiss = audioTime - (notes[i].time + hitWindowMiss);
          if (timeSinceMiss < 0)
            timeSinceMiss = 0;

          double dropDistance = 0.5 * 800.0 * (timeSinceMiss * timeSinceMiss);
          Vector2 currentPos = s->get_position();
          currentPos.y += dropDistance;
          s->set_position(currentPos);

          s->set_rotation(s->get_rotation() + (timeSinceMiss * 5.0));

          Color missColor = Color(0.6, 0.2, 0.2, 1.0);

          double fadeSpeed = 2.0;
          double alpha = 1.0 - (timeSinceMiss * fadeSpeed);
          missColor.a = std::clamp(alpha, 0.0, 1.0);
          targetColor = missColor;

          double shrink = 1.0 - (timeSinceMiss * 0.5);
          if (shrink < 0)
            shrink = 0;
          targetScale = Vector2(baseScale * shrink, baseScale * shrink);

          if (alpha <= 0)
            s->set_visible(false);
        } else {
          isAnyAnimationPlaying = true;
          s->set_z_index(9);

          double fadeDuration = 0.25;
          double currentAlpha = s->get_modulate().a - (delta / fadeDuration);

          if (currentAlpha > 0)
            s->set_visible(true);
          else
            s->set_visible(false);

          targetColor = Color(1, 1, 1);
          if (notes[i].finalResult == RESULT_PERFECT)
            targetColor = Color(1, 0.9, 0.2);
          else if (notes[i].finalResult == RESULT_GOOD)
            targetColor = Color(0.2, 0.8, 1.0);

          targetColor.a = currentAlpha;

          if (currentAlpha > 0.8) {
            targetColor.r = 1.0;
            targetColor.g = 1.0;
            targetColor.b = 1.0;
          }

          double progress = 1.0 - currentAlpha;
          double expansionAmount = 0.5;
          double newScale = 1.0 + (progress * expansionAmount);

          targetScale = Vector2(newScale * baseScale, newScale * baseScale);
        }
        s->set_modulate(targetColor);
        s->set_scale(targetScale);
      } else {
        if (notes[i].type == NOTE_REVERSE)
          targetColor = Color(1.0, 0.0, 1.0);
        else if (notes[i].type == NOTE_OVERCLOCK)
          targetColor = Color(0, 1.0, 0);
        else if (notes[i].type == NOTE_OVERHEAT)
          targetColor = Color(1.0, 0, 0);

        else if (notes[i].type == NOTE_ANORMALY)
          targetColor = Color(1.0, 1.0, 0.0);
        else
          targetColor = Color(1, 1, 1);

        double alpha = ratio;
        targetColor.a = std::clamp(alpha, 0.0, 1.0);

        targetScale = Vector2(distScale * baseScale, distScale * baseScale);

        if (notes[i].type == NOTE_OVERCLOCK || notes[i].type == NOTE_OVERHEAT) {
          double pulse = 1.0 + (0.15 * Math::sin(audioTime * 12.0));
          targetScale *= pulse;
        }

        s->set_modulate(targetColor);
        s->set_scale(targetScale);

        s->set_z_index(-10 + (int)(ratio * 9));

        if (!notes[i].isHit && targetColor.a <= 0.01)
          s->set_visible(false);
        else if (!notes[i].isHit)
          s->set_visible(true);
      }
    }
  }
  if (isAnyAnimationPlaying) {
    queue_redraw();
  }
}

void RhythmCircle::set_bpm(double bpm) {
  startBPM = bpm;
  currentBPM = bpm;
  baseSpeed = bpm / 240.0;

  UtilityFunctions::print("Set BPM: ", currentBPM,
                          " -> Base Speed: ", baseSpeed, " RPS");
}

void RhythmCircle::process_release(int laneIndex, double audioTime) {
  for (size_t i = 0; i < notes.size(); i++) {
    bool isCorrectLane = (laneIndex == -1) || (notes[i].lane == laneIndex);
    if (notes[i].isHolding && isCorrectLane) {
      double releaseThreshold = notes[i].endTime - hitWindowGood;

      if (notes[i].endTime - notes[i].time < hitWindowGood) {
        releaseThreshold = notes[i].time;
      }
      notes[i].isHolding = false;
      if (audioTime < releaseThreshold) {
        notes[i].isHit = true;
        notes[i].finalResult = RESULT_MISS;
        currentCombo = 0;
        emit_signal("on_hit_judgement", "MISS", 0);
        if (i < noteSprites.size()) {
          noteSprites[i]->set_visible(true);
          double currentAngle = calculate_angle_at_time(audioTime);
          double visualLane = (double)notes[i].lane;
          if (notes[i].type == NOTE_REVERSE ||
              notes[i].type == NOTE_OVERCLOCK || notes[i].type == NOTE_OVERHEAT)
            visualLane = 0.5;
          noteSprites[i]->set_position(
              get_position_on_circle(currentAngle, visualLane));
          noteSprites[i]->set_rotation(currentAngle);
        }
        if (i < noteSprites.size())
          noteSprites[i]->set_visible(false);
        if (i < noteCaps.size())
          noteCaps[i]->set_visible(false);
        if (notes[i].activeHoldPlayer) {
          AudioStreamPlayer *p =
              Object::cast_to<AudioStreamPlayer>(notes[i].activeHoldPlayer);
          if (p)
            p->stop();
          notes[i].activeHoldPlayer = nullptr;
        }
        UtilityFunctions::print("HOLD FAILED!");
      } else {
        notes[i].isProcessed = true;
        notes[i].finalResult = RESULT_PERFECT;

        currentCombo++;
        emit_signal("on_hit_judgement", "PERFECT", currentCombo);

        if (i < noteSprites.size()) {
          Sprite2D *s = noteSprites[i];

          double endAngle = calculate_angle_at_time(notes[i].endTime);
          double visualLane = (double)notes[i].lane;
          if (notes[i].type == NOTE_REVERSE ||
              notes[i].type == NOTE_OVERCLOCK || notes[i].type == NOTE_OVERHEAT)
            visualLane = 0.5;

          Vector2 endPos = get_position_on_circle(endAngle, visualLane);

          s->set_position(endPos);
          s->set_rotation(endAngle);

          s->set_visible(true);
          s->set_modulate(Color(1, 1, 1, 1));
          s->set_scale(Vector2(1, 1));
          s->set_z_index(20);

          notes[i].isHit = true;
        }

        if (i < noteCaps.size())
          noteCaps[i]->set_visible(false);
        if (i < noteTails.size())
          noteTails[i]->set_visible(false);

        double endAngle = calculate_angle_at_time(notes[i].endTime);
        double visualLane = (double)notes[i].lane;
        if (notes[i].type == NOTE_REVERSE || notes[i].type == NOTE_OVERCLOCK ||
            notes[i].type == NOTE_OVERHEAT)
          visualLane = 0.5;
        Vector2 hitPos = get_position_on_circle(endAngle, visualLane);
        spawn_hit_effect(hitPos, Color(1, 0.9, 0.2));
        if (notes[i].activeHoldPlayer) {
          AudioStreamPlayer *p =
              Object::cast_to<AudioStreamPlayer>(notes[i].activeHoldPlayer);
          if (p)
            p->stop();
          notes[i].activeHoldPlayer = nullptr;
        }
        UtilityFunctions::print("HOLD COMPLETE!");
      }
    }
  }
}

void RhythmCircle::spawn_hit_effect(Vector2 pos, Color color) {
  if (!hitEffectScene.is_valid())
    return;

  Node *node = hitEffectScene->instantiate();
  Node2D *effect = Object::cast_to<Node2D>(node);

  if (effect) {
    add_child(effect);
    effect->set_position(pos);
    effect->set_z_index(10);
    effect->set_modulate(color);
  }
}


void RhythmCircle::set_active_state(bool active) {
  isActive = active;
  targetAlpha = active ? 1.0 : 0.0;
}
