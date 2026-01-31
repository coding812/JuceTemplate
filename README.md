# JUCE CMake Starter Template

## How to Clone
To get this repo with the JUCE dependency included, run:
```bash
git clone --recursive https://github.com/coding812/JuceTemplate
```
==================

Your complete, one-stop guide to creating a functional JUCE audio plugin. This contains the folder structure, the CMakeLists.txt, and the four essential C++ files to get a compiling plugin.

* * *

🏗️ Phase 1: Folder Structure
-----------------------------

Create this layout manually or via terminal:
```
MyNewPlugin/
├── JUCE/ (Git Submodule)
├── Source/
│   ├── PluginProcessor.h
│   ├── PluginProcessor.cpp
│   ├── PluginEditor.h
│   └── PluginEditor.cpp
└── CMakeLists.txt
```

**Quick Setup Commands:**

```bash
mkdir MyNewPlugin && cd MyNewPlugin
```

```bash
git init
```

```bash
git submodule add https://github.com/juce-framework/JUCE.git
```

```bash
mkdir Source
```



* * *

📄 Phase 2: The Files
---------------------

### 1. CMakeLists.txt (The Project Brain)

```cmake
    cmake_minimum_required(VERSION 3.22)
    project(MY_PLUGIN VERSION 0.0.1)
    set(JUCE_BUILD_EXTRAS ON CACHE INTERNAL "") # Enables AudioPluginHost
    add_subdirectory(JUCE)

    juce_add_plugin(MyNewPlugin
        COMPANY_NAME "Steve's Plugins"
        BUNDLE_ID "com.stevesplugins.mynewplugin"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        FORMATS VST3 Standalone 
        PRODUCT_NAME "MyNewPlugin")

    target_sources(MyNewPlugin PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp)

    target_link_libraries(MyNewPlugin PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_gui_basics
        juce::juce_graphics
        juce::juce_events
        juce::juce_core)

    target_compile_definitions(MyNewPlugin PRIVATE JUCE_VST3_CAN_REPLACE_VST2=0)

    set_target_properties(MyNewPlugin PROPERTIES 
        JUCE_VST3_CATEGORY "Fx" 
        JUCE_COPY_PLUGIN_AFTER_BUILD TRUE)
```

### 2. Source/PluginProcessor.h (Audio Header)

```c++
#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class MyPluginProcessor : public juce::AudioProcessor {
public:
    MyPluginProcessor();
    ~MyPluginProcessor() override;

    void prepareToPlay (double, int) override {}
    void releaseResources() override {}
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "MyNewPlugin"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPluginProcessor)
};
```

### 3. Source/PluginProcessor.cpp (Audio Logic)

```c++
#include "PluginProcessor.h"
#include "PluginEditor.h"

MyPluginProcessor::MyPluginProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)) {}

MyPluginProcessor::~MyPluginProcessor() {}

void MyPluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Audio bypass logic
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel) {
        auto* channelData = buffer.getWritePointer (channel);
        // Add DSP here
    }
}

juce::AudioProcessorEditor* MyPluginProcessor::createEditor() { return new MyPluginEditor (*this); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new MyPluginProcessor(); }
```

### 4. Source/PluginEditor.h (UI Header)

```c++
#pragma once
#include "PluginProcessor.h"

class MyPluginEditor : public juce::AudioProcessorEditor {
public:
    MyPluginEditor (MyPluginProcessor&);
    ~MyPluginEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    MyPluginProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPluginEditor)
};
```

### 5. Source/PluginEditor.cpp (UI Logic)

```c++
#include "PluginProcessor.h"
#include "PluginEditor.h"

MyPluginEditor::MyPluginEditor (MyPluginProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p) {
    setSize (400, 300);
}

MyPluginEditor::~MyPluginEditor() {}

void MyPluginEditor::paint (juce::Graphics& g) {
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("Steve's Plugin Loaded!", getLocalBounds(), juce::Justification::centred, 1);
}

void MyPluginEditor::resized() {}
```

* * *

✅ Phase 3: Build Checklist
--------------------------

* [ ] **Delete Cache:**
  
  * Press `Ctrl+Shift+P`
  * Type `CMake: Delete Cache and Reconfigure`

* [ ] **Target Selection:**
  
  * Press `Ctrl+Shift+P`
  * Type `CMake: Set Build Target`
  * Select `MyNewPlugin_VST3`

* [ ] **Compile:** Press `F7`

* [ ] **Scan Path:** Point AudioPluginHost to:
  
      build/MyNewPlugin_artefacts/Debug/VST3/
  
  

* * *

💻 Phase 4: VS Code Workflow
----------------------------

* [ ] **Open Folder:** Open the root `MyNewPlugin` folder in VS Code.

* [ ] **Select Kit:** In the bottom status bar, select your compiler (ensure it is an x64 version).

* [ ] **Set Launch Target:**
  
  * In the status bar, click the "Select a target to launch" icon (looks like a small play button).
  * Select `AudioPluginHost`.

* [ ] **Launch Debugger:** Press `F5` to run with debugging.

* * *

🎹 Phase 5: Testing in AudioPluginHost
--------------------------------------

* [ ] **Open AudioPluginHost:** It should launch automatically if configured correctly.

* [ ] **Scan for Plugin:**
  
  * Go to `Options` → `Edit list of available plug-ins` → `Options` → `Scan for new or updated VST3 plug-ins`
  * Point it to the `build/MyNewPlugin_artefacts/Debug/VST3/` folder

* [ ] **Load Plugin:** Right-click the canvas, add your plugin, and connect the yellow audio pins.

* [ ] **Verify:** You should see "Steve's Plugin Loaded!" in the plugin window.

* * *

🐞 Phase 6: Debugging Tips
--------------------------

* [ ] **Set Breakpoint:** Open `PluginProcessor.cpp` and click the margin next to a line number in `processBlock`.

* [ ] **Debug Mode:** Ensure the status bar says `[Debug]`.

* [ ] **Always on Top (Optional):** If the AudioPluginHost window keeps hiding, modify `JUCE/extras/AudioPluginHost/Source/UI/MainHostWindow.cpp` and add `setAlwaysOnTop(true);` in the constructor.

* * *

🛑 Common Error Fixes
---------------------

| Error                     | Fix                                                                         |
| ------------------------- | --------------------------------------------------------------------------- |
| `LNK1104` (In Use)        | Close the AudioPluginHost before building.                                  |
| Missing Target            | `Ctrl+Shift+P` → `CMake: Delete Cache and Reconfigure`.                     |
| Failed to Load            | Ensure you are scanning the `..._artefacts/Debug/VST3` folder specifically. |
| "Could not create plugin" | Check that all 4 source files are present and have no syntax errors.        |

* * *

**Happy JUCE coding! 🎵**
