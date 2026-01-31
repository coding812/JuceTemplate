cmake_minimum_required(VERSION 3.22)

project(MY_PLUGIN VERSION 0.0.1)



# 1. Include JUCE
set(JUCE_BUILD_EXTRAS ON CACHE INTERNAL "")  # This forces JUCE to include the Host
add_subdirectory(JUCE)

# 2. Create the Plugin target
juce_add_plugin(MyNewPlugin
    COMPANY_NAME "Steve's Plugins"
    BUNDLE_ID "com.stevesplugins.mynewplugin"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    # This enables VST3 and Standalone formats
    FORMATS VST3 Standalone 
    PRODUCT_NAME "MyNewPlugin")
    
target_compile_definitions(MyNewPlugin PRIVATE 
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# 3. Add your source files
target_sources(MyNewPlugin PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

# 4. Link JUCE modules
target_link_libraries(MyNewPlugin PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_events
    juce::juce_core)

# 5. Professional Defaults (Optional but recommended)
# This copies the VST3 to your system's VST3 folder automatically after building
set_target_properties(MyNewPlugin PROPERTIES 
    JUCE_VST3_CATEGORY "Fx" 
    JUCE_COPY_PLUGIN_AFTER_BUILD TRUE)