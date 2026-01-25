cmake_minimum_required(VERSION 3.20)
project(ChronoR VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options($<$<CONFIG:Debug>:/MDd> $<$<CONFIG:Release>:/MD>)
endif()

add_compile_definitions(JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
                        JUCE_STANDALONE_APPLICATION=0
                        JUCE_DONT_DEFINE_WINDOWS_HANDLE=1
                        JUCE_CHECK_MEMORY_LEAKS=0
                        _CRT_SECURE_NO_WARNINGS)

add_subdirectory(../thirdparty/JUCE third_party/JUCE)

add_subdirectory(../thirdparty/godot-cpp third_party/godot-cpp)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE godot::cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_audio_formats
    juce::juce_dsp
    juce::juce_audio_devices
    juce::juce_audio_utils
)
