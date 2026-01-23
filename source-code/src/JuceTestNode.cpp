#include "JuceTestNode.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void JuceTestNode::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("play_test_sound", "file_path"), &JuceTestNode::play_test_sound);
}

JuceTestNode::JuceTestNode() {
    
    formatManager.registerBasicFormats();

    
    auto setupResult = deviceManager.initialise(0, 2, nullptr, true);
    if (setupResult.isNotEmpty()) {
        UtilityFunctions::print("JUCE Error: " + String(setupResult.toRawUTF8()));
    }

    
    sourcePlayer.setSource(&transportSource);

    
    deviceManager.addAudioCallback(&sourcePlayer);
    
    UtilityFunctions::print("JUCE Audio System Initialized!");
}

JuceTestNode::~JuceTestNode() {
    
    transportSource.setSource(nullptr);
    deviceManager.removeAudioCallback(&sourcePlayer);
    deviceManager.closeAudioDevice();
}

void JuceTestNode::play_test_sound(String filePath) {
    
    juce::File file(filePath.utf8().get_data());

    if (!file.existsAsFile()) {
        UtilityFunctions::print("Error: File not found -> " + filePath);
        return;
    }

    
    auto* reader = formatManager.createReaderFor(file);

    if (reader != nullptr) {
        
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        
        
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        
        
        readerSource = std::move(newSource);

        
        transportSource.start();
        UtilityFunctions::print("Playing: " + filePath);
    } else {
        UtilityFunctions::print("Error: JUCE cannot read this format!");
    }
}