cmake_minimum_required(VERSION 3.20)
project(ChronoR VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    add_compile_options($<$<CONFIG:Debug>:/MDd> $<$<CONFIG:Release>:/MD>)
endif()

add_subdirectory(../thridparty/JUCE third_party/JUCE)

add_compile_definitions(JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
                        JUCE_STANDALONE_APPLICATION=0
                        JUCE_DONT_DEFINE_WINDOWS_HANDLE=1)

add_subdirectory(../thridparty/godot-cpp third_party/godot-cpp)

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

# เช็คว่าถ้าไม่ใช่ Visual Studio (คือใช้ Ninja) ให้เติม /Debug เข้าไปเอง
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set(FINAL_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../chrono-r/bin")
else()
    # ถ้าใช้ Ninja/NMake ให้เติม Debug ต่อท้าย
    set(FINAL_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../chrono-r/bin/Debug")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${FINAL_OUTPUT_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "${FINAL_OUTPUT_PATH}"
)


target_compile_definitions(${PROJECT_NAME} PRIVATE

    JUCE_CHECK_MEMORY_LEAKS=0

    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    _CRT_SECURE_NO_WARNINGS
)
