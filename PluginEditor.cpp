/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProgettoProvaAudioProcessorEditor::ProgettoProvaAudioProcessorEditor (ProgettoProvaAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	startTimer(200);

	trackButton2.setButtonText("minor");
	bypassButton.setButtonText("BYPASS");


	

	addAndMakeVisible(textLabel);
	textLabel.setFont(textFont);
	textLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(styleMenu);

	addAndMakeVisible(&trackButton2);
	addAndMakeVisible(&bypassButton);

	styleMenu.addItem("none", 1);
	styleMenu.addItem("C", 11);
	styleMenu.addItem("C#", 18);
	styleMenu.addItem("Db", 6);
	styleMenu.addItem("D", 13);
	styleMenu.addItem("D#", 20);
	styleMenu.addItem("Eb", 8);
	styleMenu.addItem("E", 15);
	styleMenu.addItem("F", 10);
	styleMenu.addItem("F#", 17);
	styleMenu.addItem("Gb", 5);
	styleMenu.addItem("G", 12);
	styleMenu.addItem("G#", 19);
	styleMenu.addItem("Ab", 7);
	styleMenu.addItem("A", 14);
	styleMenu.addItem("A#", 21);
	styleMenu.addItem("Bb", 9);
	styleMenu.addItem("B", 16);

	styleMenu.onChange = [this] { styleMenuChanged(); };

	trackButton2.setToggleState(false, true);
	trackButton2.setClickingTogglesState(true);
	trackButton2.onClick = [this] { updateToggleState(&trackButton2);   };

	bypassButton.setToggleState(false, true);
	bypassButton.setClickingTogglesState(true);
	bypassButton.onClick = [this] { updateToggleState(&bypassButton);   };
	
	addAndMakeVisible(midiMessagesBox);
	midiMessagesBox.setMultiLine(true);
	midiMessagesBox.setReturnKeyStartsNewLine(true);
	midiMessagesBox.setReadOnly(true);
	midiMessagesBox.setScrollbarsShown(true);
	midiMessagesBox.setCaretVisible(false);
	midiMessagesBox.setPopupMenuEnabled(true);
	midiMessagesBox.setColour(TextEditor::backgroundColourId, Colour(0x32ffffff));
	midiMessagesBox.setColour(TextEditor::outlineColourId, Colour(0x1c000000));
	midiMessagesBox.setColour(TextEditor::shadowColourId, Colour(0x16000000));
	setSize(400, 600);
}

ProgettoProvaAudioProcessorEditor::~ProgettoProvaAudioProcessorEditor()
{
}

void ProgettoProvaAudioProcessorEditor::timerCallback()  {
	String valueMidi = String(processor.harmTension, 3);
	String valueCloudDiameter = String(processor.cloudDiameter, 3);
	String MidiController = String(processor.valueToSend);
	String noteToPlay = processor.midiNoteVal;
	String ce0 = String(processor.CE[0]);
	String ce1 = String(processor.CE[1]);
	String ce2 = String(processor.CE[2]);
	String ce_prev0 = String(processor.CE_prev[0]);
	String ce_prev1 = String(processor.CE_prev[1]);
	String ce_prev2 = String(processor.CE_prev[2]);
	String tempo = String(processor.actualTime);
	String misura = String(processor.countMeasures);
	String selectedTonality = processor.selectedTon;
	String tStrain = String(processor.tensileStrain, 3);
	String tonality = processor.keyFinal;
	String kx = String(processor.T1[0][processor.indexKey]);
	String ky = String(processor.T1[1][processor.indexKey]);
	String kz = String(processor.T1[2][processor.indexKey]);
	String kxm = String(processor.T2[0][processor.indexKey]);
	String kym = String(processor.T2[1][processor.indexKey]);
	String kzm = String(processor.T2[2][processor.indexKey]);
	String indexTon = String(processor.indexKey+4);
	/*String testx = String(processor.testP[0]);
	String testy = String(processor.testP[1]);
	String testz = String(processor.testP[2]);*/
	StringArray notePlay = processor.playedNotes;
	Array<double> noteTime = processor.noteTimes;
	StringArray noteTimeStrings = StringArray();
	

	if (processor.trackPlayed)
	{ 
		start = Time::currentTimeMillis();
		processor.trackPlayed = false;
	}

	if (true)
		{
		/*String kx = String(processor.T1[0][0]);
		String ky = String(processor.T1[1][0]);
		String kz = String(processor.T1[2][0]);
		String kxm = String(processor.T2[0][0]);
		String kym = String(processor.T2[1][0]);
		String kzm = String(processor.T2[2][0]);
		String spiralx = String(processor.spiral[0][0]);
		String spiraly = String(processor.spiral[1][0]);
		String spiralz = String(processor.spiral[2][0]);
		String indexTon = String(0 + 4);

		if (counter < 25) {

			kx = String(processor.T1[0][counter]);
			 ky = String(processor.T1[1][counter]);
			 kz = String(processor.T1[2][counter]);
			 kxm = String(processor.T2[0][counter]);
			 kym = String(processor.T2[1][counter]);
			 kzm = String(processor.T2[2][counter]);
			 indexTon = String(counter + 4);
			 spiralx = String(processor.spiral[0][counter]);
			 spiraly = String(processor.spiral[1][counter]);
			 spiralz = String(processor.spiral[2][counter]);

		}*/
		
			for (int i = 0; i < noteTime.size(); ++i) {
				noteTimeStrings.add(String(noteTime[i]));
			}
			now = Time::currentTimeMillis();
			if (processor.playing)
				//logMessage("MIDI ver 2 note: " + noteToPlay + " with CE: [" + ce0 + ", " + ce1 + ", " + ce2 + "] at " + tempo + " with CE_prev: [" + ce_prev0 + ", " + ce_prev1 + ", " + ce_prev2 + ", cloud momentum: " + valueMidi + " cloud diameter: " + valueCloudDiameter + " the key is " + tonality + "("+indexTon+")  at coords: [" + kx + ", " + ky + ", " + kz + "] or minor at coords: [ " + kxm + ", " + kym + ", " + kzm + "] with misura " + misura + " Played notes are " + notePlay.joinIntoString(", ")+ " at times "+ noteTimeStrings.joinIntoString(", ")+ " \n");
				logMessage("MIDI note: " + noteToPlay + " at " + tempo + "\n cloud momentum: " + valueMidi + "\n cloud diameter: " + valueCloudDiameter + "\n tensile strain: " + tStrain + "\n key: " + selectedTonality + "\n the key is " + tonality + "\n controller value: " + MidiController + "\n");
				//logMessage("At " + tempo + " tone " + indexTon + " coords: [" + kx + ", " + ky + ", " + kz + "] or minor at coords: [ " + kxm + ", " + kym + ", " + kzm + "] spiral is [" + spiralx + ", " + spiraly + ", " + spiralz + "] \n");
			if (counter < 25) {
				counter++;
			}
				/*if (now - start <= (min * trackTimer * 1000 + 500) && now - start >= min * trackTimer * 1000 - 500) {
				activated++;
				if (activated == 1)
				{
					switch (min) {
					case 1:
						trackButton2.setToggleState(false, false);
						updateToggleState(&trackButton2);
						logMessage("Track  2 activated");
						break;
					case 2:
						trackButton10.setToggleState(false, false);
						updateToggleState(&trackButton10);
						logMessage("Track  10 activated");
						break;
					case 3:
						trackButton4.setToggleState(false, false);
						updateToggleState(&trackButton4);
						logMessage("Track  4 activated");
						break;
					case 4:
						trackButton5.setToggleState(false, false);
						updateToggleState(&trackButton5);
						logMessage("Track  5 activated");
						break;
					case 5:
						trackButton6.setToggleState(false, false);
						updateToggleState(&trackButton6);
						logMessage("Track  6 activated");
						break;
					case 6:
						trackButton7.setToggleState(false, false);
						updateToggleState(&trackButton7);
						logMessage("Track  7 activated");
						break;
					case 7:
						trackButton8.setToggleState(false, false);
						updateToggleState(&trackButton8);
						logMessage("Track  8 activated");
						break;
					case 8:
						trackButton9.setToggleState(false, false);
						updateToggleState(&trackButton9);
						logMessage("Track  9 activated");
						break;
					case 9:
						trackButton10.setToggleState(false, false);
						updateToggleState(&trackButton10);
						logMessage("Track  10 activated");
						break;
					case 10:
						trackButton11.setToggleState(false, false);
						updateToggleState(&trackButton11);
						logMessage("Track  11 activated");
						break;
					case 11:
						trackButton12.setToggleState(false, false);
						updateToggleState(&trackButton12);
						logMessage("Track  12 activated");
						break;
					case 12:
						trackButton13.setToggleState(false, false);
						updateToggleState(&trackButton13);
						logMessage("Track  13 activated");
						break;
					case 13:
						trackButton14.setToggleState(false, false);
						updateToggleState(&trackButton14);
						logMessage("Track  14 activated");
						break;
					case 14:
						trackButton15.setToggleState(false, false);
						updateToggleState(&trackButton15);
						logMessage("Track  15 activated");
						break;
					case 15:
						trackButton16.setToggleState(false, false);
						updateToggleState(&trackButton16);
						logMessage("Track  16 activated");
						break;
					}
					if (min < 16)
						min++;
				}

			}
			if (now - start > ((min - 1) * trackTimer * 1000 + 500))
				activated = 0;*/
	}

}

//==============================================================================

void ProgettoProvaAudioProcessorEditor::buttonClicked(Button* button) 
{
	processor.sendMessage();
}

void ProgettoProvaAudioProcessorEditor::updateToggleState(Button* button)
{
	auto state = button->getToggleState();
	auto name = button->getButtonText();
	if (name == "BYPASS") {
		processor.bypassState = state;
	}
	else {
		processor.btnState2 = state;
	}
}

void ProgettoProvaAudioProcessorEditor::styleMenuChanged()
{
	processor.selectedKey = styleMenu.getSelectedId();
}


void ProgettoProvaAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("MIDI tension mapper",0,0, getWidth(),30, Justification::centred, 1);
	
	
}

void ProgettoProvaAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	

	auto halfHeight = getHeight() / 2;
	auto halfWidth = getWidth() / 2;

	styleMenu.setBounds(getLocalBounds().withHeight(halfHeight / 6).withWidth(halfWidth / 2).withX(0).withY(halfHeight - halfHeight / 6).reduced(10));
	trackButton2.setBounds(getLocalBounds().withHeight(halfHeight / 6).withWidth(halfWidth / 2).withX(halfWidth/2).withY(halfHeight - halfHeight / 6).reduced(10));
	bypassButton.setBounds(getLocalBounds().withHeight(halfHeight / 6).withWidth(halfWidth / 2).withX(2*halfWidth - halfWidth/2).withY(2*halfHeight-halfHeight/6).reduced(10));
	midiMessagesBox.setBounds(getLocalBounds().withHeight(halfHeight).withWidth(halfWidth).withX(0).withY(halfHeight).reduced(10));
	textLabel.setBounds(getLocalBounds().withHeight(styleMenu.getHeight()+10).withWidth(styleMenu.getWidth()).withX(0).withY(styleMenu.getY()-styleMenu.getHeight()-10).reduced(10));
}

void ProgettoProvaAudioProcessorEditor::logMessage(const String& m)
{
	midiMessagesBox.moveCaretToEnd();
	midiMessagesBox.insertTextAtCaret(m + newLine);
}
