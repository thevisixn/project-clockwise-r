#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>
#include <string>
namespace godot {

class GameGlobal {
public:
  static std::string selectedMapPath;

  static std::string selectedAudioPath;

  static bool modAutoplay;
  static bool modHPMode;

  static std::string lastTitle;
  static std::string lastArtist;
  static std::string lastDifficulty;
  static int lastScore;
  static int lastPerfect;
  static int lastGood;
  static int lastMiss;
  static int lastMaxCombo;
  static std::string lastGrade;
  static std::string lastTuningStatus;  
};

} // namespace godot
