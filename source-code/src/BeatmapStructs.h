#pragma once
#include "godot_cpp/classes/node.hpp"
#include <godot_cpp/variant/string.hpp>
#include <vector>
#include <algorithm>

using namespace godot;

enum NoteType {
  NOTE_SINGLE,
  NOTE_HOLD,
  NOTE_REVERSE,
  NOTE_OVERCLOCK,
  NOTE_OVERHEAT,
  NOTE_ANORMALY,
  NOTE_CMD_SHOW,
  NOTE_CMD_HIDE
};

enum EventType {
  EVENT_CIRCLE_SHOW,
  EVENT_CIRCLE_HIDE
};


struct CircleEvent {
  double time;
  int circleId;
  NoteType type;
  bool isProcessed = false;
};

enum HitResult { RESULT_NONE, RESULT_MISS, RESULT_GOOD, RESULT_PERFECT };

struct MapMetadata {
  String title;
  String artist;
  String difficulty;
  String level;
  String coverPath;
  String audioPath;
  String csvPath;

  int bestScore = 0;
  String grade = "-";
};

struct NoteData {
  double time;
  int lane;
  NoteType type;
  double param;
  double param2;
  double param3;

  double endTime = 0.0;
  bool isHolding = false;

  bool isHit = false;
  bool isProcessed = false;
  HitResult finalResult = RESULT_NONE;

  Node *activeHoldPlayer = nullptr;
};

struct TimingPoint {
  double beat;
  double newBpm;
  int numerator = 4;
  int denominator = 4;
};

struct BeatmapData {
  String title;
  String artist;
  double startBpm;
  double offset;
  String difficulty;
  String level;
  String mapper;
  String illustrator;
  String description;

  std::vector<TimingPoint> timingPoints;

  std::vector<NoteData> leftCircleNotes;
  std::vector<NoteData> rightCircleNotes;
};


inline String get_difficulty_class(String diffName, int level) {
    String d = diffName.to_lower();

    if (d.contains("spacos")) return "Spacos";
    if (d.contains("chronos")) return "Chronos";
    if (d.contains("insane")) return "Insane";
    if (d.contains("hard")) return "Hard";
    if (d.contains("easy")) return "Easy";


    if (level >= 17) return "Insane";
    if (level >= 9) return "Hard";
    return "Easy";
}


inline Color get_difficulty_color(String diffClass) {
    if (diffClass == "Easy") return Color(0.2, 0.8, 0.2, 1.0);
    if (diffClass == "Hard") return Color(1.0, 0.6, 0.0, 1.0);
    if (diffClass == "Insane") return Color(1.0, 0.2, 0.2, 1.0);
    if (diffClass == "Chronos") return Color(0.1, 0.1, 0.1, 1.0);
    if (diffClass == "Spacos") return Color(0.5, 0.5, 0.5, 1.0);

    return Color(1, 1, 1, 1);
}


struct SongGroup {
    String title;
    String artist;
    String coverPath;
    String audioPath;


    std::vector<MapMetadata> difficulties;


    void sort_difficulties() {
        std::sort(difficulties.begin(), difficulties.end(), [](const MapMetadata& a, const MapMetadata& b) {
            int lvA = a.level.to_int();
            int lvB = b.level.to_int();
            return lvA < lvB;
        });
    }
};
