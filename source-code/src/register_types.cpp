#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include "JuceAudioEngine.h"
#include "RhythmGameController.h"
#include "JuceTestNode.h"
#include "RhythmCircle.h"
#include "SongSelectController.h"
#include "BeatmapItem.h"
#include "MainMenuController.h"
#include "NavbarController.h"

using namespace godot;

void initialize_chronor_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<JuceTestNode>();
    ClassDB::register_class<JuceAudioEngine>();
    ClassDB::register_class<RhythmGameController>();
    ClassDB::register_class<RhythmCircle>();
    ClassDB::register_class<SongSelectController>();
    ClassDB::register_class<BeatmapItem>();
    ClassDB::register_class<MainMenuController>();
    ClassDB::register_class<NavbarController>();
}

void uninitialize_chronor_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT chronor_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_chronor_module);
        init_obj.register_terminator(uninitialize_chronor_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
