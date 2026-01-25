#pragma once
#include <godot_cpp/variant/string.hpp>
#include <vector>
#include "godot_cpp/classes/node.hpp"
using namespace godot;

enum NoteType {
    NOTE_SINGLE,
    NOTE_HOLD,
    NOTE_REVERSE,
    NOTE_OVERCLOCK,
    NOTE_OVERHEAT,
    NOTE_ANORMALY
};

enum HitResult {
    RESULT_NONE,
    RESULT_MISS,
    RESULT_GOOD,
    RESULT_PERFECT
};

struct MapMetadata {
    String title;
    String artist;
    String difficulty;
    String level;
    String coverPath;
    String audioPath;
    String csvPath;
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

    Node* activeHoldPlayer = nullptr;
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
