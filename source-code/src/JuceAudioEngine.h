#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
namespace godot {

class JuceAudioEngine : public Node {
    GDCLASS(JuceAudioEngine, Node)

private:
    juce::AudioDeviceManager deviceManager;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::AudioSourcePlayer sourcePlayer;
protected:
    static void _bind_methods();

public:
    JuceAudioEngine();
    ~JuceAudioEngine();
    void play_audio(String filePath);
    double get_audio_time();
    double get_audio_length();
    bool is_playing();

    void stop();
};

}
