/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include <cmath>

//==============================================================================
/**
*/
class ProgettoProvaAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	ProgettoProvaAudioProcessor();
	~ProgettoProvaAudioProcessor();

	int selectedKey = 0;
	bool btnState1 = false;
	bool btnState2 = false;
	bool btnState3 = false;
	bool btnState4 = false;
	bool btnState5 = false;
	bool btnState6 = false;
	bool btnState7 = false;
	bool btnState8 = false;
	bool btnState9 = false;
	bool btnState10 = false;
	bool btnState11 = false;
	bool btnState12 = false;
	bool btnState13 = false;
	bool btnState14 = false;
	bool btnState15 = false;
	bool btnState16 = false;

	String midiDesc = String();
	String midiNoteVal = String();
	int valueToSend = 100;
	double harmTension_prev = 0.0;
	double harmTension = 0.0;
	double cloudDiameter_prev = 0.0;
	double cloudDiameter = 0.0;
	double tensileStrain = 0.0;
	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;


	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;
	bool trackPlayed = false;
	double position;
	String controllerNumber; 
	bool playing = false;
	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	void sendMessage();
	void addMessageToBuffer(const MidiMessage& message, MidiBuffer& buffer);
	StringArray spiralArray = {
		"Fbb", "Cbb", "Gbb", "Dbb", "Abb", "Ebb", "Bbb", "Fb", "Cb", "Gb", "Db", "Ab", "Eb", "Bb", "F", "C", "G", "D", "A", "E", "B", "F#", "C#", "G#", "D#", "A#", "E#", "B#", "F##", "C##", "G##", "D##", "A##", "E##", "B##"};
	StringArray playedNotes = StringArray();
	double spiral[3][35];
	Array<double> noteTimes = Array<double>();
	double CE[3] = { 0, 1.0, 0 };
	double actualTime = 0.0;
	int countMeasures = 0;
	double c[3] = { 0, 0, 0 };
	double CE_prev[3] = { 0, 1.0, 0 }; //{ -1, 0, 5.477225575 };
	double T1[3][25];	// based on the number of pitches in the spiral array, the number of keys is 35 - 7 (minor major triads) - 2 (for keys)
	double T2[3][25];	// the keys will span from Abb to F##
	String keyFinal = String();
	double actualKey[3] = { 0, 0, 0 };
	int indexKey = 0;
	double testP[3] = { 0, 0 ,0 };
	String selectedTon = "not selected";
	bool bypassState = false;
	

private:
	//==============================================================================
	bool btnClick = false;
	double totTension = 0.0;
	double ProgettoProvaAudioProcessor::getDistancefromC1(String note);
	void ProgettoProvaAudioProcessor::generate_spiral();
	String ProgettoProvaAudioProcessor::findKey(double cex, double cey, double cez);
	double ProgettoProvaAudioProcessor::getDistance(double* p1, double* p2);
	double ProgettoProvaAudioProcessor::getMaxDistance(StringArray notes, double refTime, Array<double> timeNotes);
	double ProgettoProvaAudioProcessor::computeCE(StringArray notes, Array<double> timestamps, int b_a, int var);
	//double* ProgettoProvaAudioProcessor::computePosition(int indexNote);
	void ProgettoProvaAudioProcessor::generate_keys(double w11, double w12, double w13, double u11, double u12, double u13, double alpha, double beta);
	Array<double> ProgettoProvaAudioProcessor::generate_maj_triad(int index, double w1, double w2, double w3);
	Array<double> ProgettoProvaAudioProcessor::generate_min_triad(int index, double w1, double w2, double w3);
	String ProgettoProvaAudioProcessor::labelNote(String note, double CE_x, double CE_y, double CE_z);
	int ProgettoProvaAudioProcessor::getMinimumDistance(int idx1, int idx2, int idx3, double CEx, double CEy, double CEz);
	int count = 0;
	
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProgettoProvaAudioProcessor)
};
