#include "JuceAudioEngine.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void JuceAudioEngine::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play_audio", "file_path"), &JuceAudioEngine::play_audio);
    ClassDB::bind_method(D_METHOD("get_audio_time"), &JuceAudioEngine::get_audio_time);
    ClassDB::bind_method(D_METHOD("get_audio_length"), &JuceAudioEngine::get_audio_length);
    ClassDB::bind_method(D_METHOD("is_playing"), &JuceAudioEngine::is_playing);
    ClassDB::bind_method(D_METHOD("stop"), &JuceAudioEngine::stop);
}

JuceAudioEngine::JuceAudioEngine() {
    formatManager.registerBasicFormats();

    auto setupResult = deviceManager.initialise(0, 2, nullptr, true);
    if (setupResult.isNotEmpty()) {
        UtilityFunctions::print("JUCE Error: " + String(setupResult.toRawUTF8()));
    }

    sourcePlayer.setSource(&transportSource);

    deviceManager.addAudioCallback(&sourcePlayer);

    UtilityFunctions::print("JUCE Audio System Initialized!");
}

JuceAudioEngine::~JuceAudioEngine() {
    transportSource.setSource(nullptr);
    deviceManager.removeAudioCallback(&sourcePlayer);
    deviceManager.closeAudioDevice();
}

void JuceAudioEngine::play_audio(String filePath) {
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
double JuceAudioEngine::get_audio_time() {
    if (transportSource.isPlaying()) {
        return transportSource.getCurrentPosition();
    }
    return 0.0;
}
double JuceAudioEngine::get_audio_length(){
    if (transportSource.getLengthInSeconds() > 0) {
        return transportSource.getLengthInSeconds();
    }
    return 0.0;
}

bool JuceAudioEngine::is_playing() {
    return transportSource.isPlaying();
}

void JuceAudioEngine::stop() {
    transportSource.stop();
    transportSource.setPosition(0.0); // (Optional) รีเซ็ตเวลากลับไปเริ่มใหม่
}
