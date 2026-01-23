cmake_minimum_required(VERSION 3.20)
project(ChronoR VERSION 1.0.0 LANGUAGES CXX)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    
    add_compile_options($<$<CONFIG:Debug>:/MDd> $<$<CONFIG:Release>:/MD>)
endif()

add_subdirectory(../thridparty/JUCE third_party/JUCE)


add_compile_definitions(JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1 JUCE_STANDALONE_APPLICATION=0 JUCE_DONT_DEFINE_WINDOWS_HANDLE=1)

add_subdirectory(../thridparty/godot-cpp third_party/godot-cpp)


file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/register_types.cpp)

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


set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../chrono-r/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../chrono-r/bin"
)


target_compile_definitions(${PROJECT_NAME} PRIVATE
    
    JUCE_CHECK_MEMORY_LEAKS=0 
    
    JUCE_WEB_BROWSER=0 
    JUCE_USE_CURL=0
    _CRT_SECURE_NO_WARNINGS
)