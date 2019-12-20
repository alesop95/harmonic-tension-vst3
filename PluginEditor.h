/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ProgettoProvaAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener, public Timer
{
public:
    ProgettoProvaAudioProcessorEditor (ProgettoProvaAudioProcessor&);
    ~ProgettoProvaAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void logMessage(const String& m);
	void timerCallback() override;

private:
	void buttonClicked(Button* button) override;
	void updateToggleState(Button* button);
	void styleMenuChanged();
	int64 start = 0;
	int64 now = 0;
	int64 trackTimer = 10;
	int activated = 0;
	int64 min = 1;
	int counter = 0;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProgettoProvaAudioProcessor& processor;

	Label textLabel{ {}, "Key" };
	Font textFont{ 18.0f };

	ComboBox styleMenu;

	TextButton midiButton;
	TextButton bypassButton;
	TextButton trackButton1;
	TextButton trackButton2;
	TextButton trackButton3;
	TextButton trackButton4;
	TextButton trackButton5;
	TextButton trackButton6;
	TextButton trackButton7;
	TextButton trackButton8;
	TextButton trackButton9;
	TextButton trackButton10;
	TextButton trackButton11;
	TextButton trackButton12;
	TextButton trackButton13;
	TextButton trackButton14;
	TextButton trackButton15;
	TextButton trackButton16;

	TextEditor midiMessagesBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgettoProvaAudioProcessorEditor)
};
