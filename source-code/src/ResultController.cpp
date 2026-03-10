#include "ResultController.h"
#include "GameGlobal.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

void ResultController::_bind_methods() {
  ClassDB::bind_method(D_METHOD("_on_retry_pressed"),
                       &ResultController::_on_retry_pressed);
  ClassDB::bind_method(D_METHOD("_on_back_pressed"),
                       &ResultController::_on_back_pressed);
}

void ResultController::_ready() {
  if (Engine::get_singleton()->is_editor_hint()) {
      return; 
  }
lblTitle = get_node<Label>("Title");
  lblArtist = get_node<Label>("Artist");
  lblDiff = get_node<Label>("Difficulty");
  lblScore = get_node<Label>("ScoreValue");
  lblPerfect = get_node<Label>("PerfectCount");
  lblGood = get_node<Label>("GoodCount");
  lblMiss = get_node<Label>("MissCount");
  lblGrade = get_node<Label>("GradeLarge");
  lblStatus = get_node<Label>("TuningStatus");
  btnRetry = get_node<Button>("BtnRetry");
  btnBack = get_node<Button>("BtnBack");

  // 🔥 [แก้ไขจุดที่ 2] ต้องเช็คว่าดึง Node สำเร็จ (ไม่เป็น nullptr) ก่อนสั่งเซ็ตค่าเสมอ
  if (lblTitle) lblTitle->set_text(String(GameGlobal::lastTitle.c_str()));
  if (lblArtist) lblArtist->set_text(String(GameGlobal::lastArtist.c_str()));
  if (lblDiff) lblDiff->set_text(String(GameGlobal::lastDifficulty.c_str()));
  
  if (lblScore) lblScore->set_text(String::num_int64(GameGlobal::lastScore).pad_zeros(7));
  if (lblPerfect) lblPerfect->set_text(String::num_int64(GameGlobal::lastPerfect));
  if (lblGood) lblGood->set_text(String::num_int64(GameGlobal::lastGood));
  if (lblMiss) lblMiss->set_text(String::num_int64(GameGlobal::lastMiss));
  
  if (lblGrade) {
      lblGrade->set_text(String(GameGlobal::lastGrade.c_str()));
      String currentGradeStr = String(GameGlobal::lastGrade.c_str());
      if (currentGradeStr == "PS") lblGrade->set_self_modulate(Color(1, 0.8, 0));
      else if (currentGradeStr.contains("S")) lblGrade->set_self_modulate(Color(1, 0.5, 1));
  }
  
  if (lblStatus) lblStatus->set_text(String(GameGlobal::lastTuningStatus.c_str()));

  // Connect ปุ่ม (ต้องเช็คก่อนเช่นกัน)
  if (btnRetry) btnRetry->connect("pressed", Callable(this, "_on_retry_pressed"));
  if (btnBack) btnBack->connect("pressed", Callable(this, "_on_back_pressed"));
}

void ResultController::_on_retry_pressed() {
  // โหลดหน้าเดิมซ้ำ โดยใช้ Path ที่อยู่ใน Global
  get_tree()->change_scene_to_file("res://resource-media/assets/scenes/play.tscn");
}

void ResultController::_on_back_pressed() {
  get_tree()->change_scene_to_file("res://resource-media/assets/scenes/song_selection.tscn");
}
