/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProgettoProvaAudioProcessor::ProgettoProvaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ProgettoProvaAudioProcessor::~ProgettoProvaAudioProcessor()
{
}

//==============================================================================
const String ProgettoProvaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProgettoProvaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProgettoProvaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProgettoProvaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProgettoProvaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProgettoProvaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ProgettoProvaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProgettoProvaAudioProcessor::setCurrentProgram (int index)
{
}

const String ProgettoProvaAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProgettoProvaAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ProgettoProvaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	double w[3] = { 0.6025, 0.2930, 0.1145 };	// par 4.2.2 valid for major chords, major keys and minor keys
	double u[3] = { 0.6011, 0.2121, 0.1868 };	// valid for minor chords

	generate_spiral();
	generate_keys(w[0], w[1], w[2], u[0], u[1], u[2], 1, 0);
}

void ProgettoProvaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProgettoProvaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ProgettoProvaAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	StringArray midiOutputList = MidiOutput::getDevices();
	int portIndex = midiOutputList.indexOf("loopMIDI Port 2");
	int portIndexTracks = midiOutputList.indexOf("loopMIDI Port 1");

	MidiOutput* midiOutput;
	MidiOutput* midiOutTracks;
 

	if (portIndex != -1) {
		midiOutput = MidiOutput::openDevice(portIndex);	//WINDOWS
		midiOutTracks = MidiOutput::openDevice(portIndexTracks);
	}
	else
		midiOutput = MidiOutput::openDevice(0);	//OSX

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;
	MidiMessage m_old = MidiMessage();
	int time_old = 0;

	

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	AudioPlayHead* phead = getPlayHead();
	MidiBuffer midiBuf;
	double old_time = 0.0;
	int midiCount = 0;
	double beatPerSecond = 0;
	double bpsOld = 0;
	double oldMeasure = 0.0;
	double alfa = 0.04;
	double zeta = 0.3;
	

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		AudioPlayHead::CurrentPositionInfo playposinfo;
		phead->getCurrentPosition(playposinfo);		
		//midiDesc = var(playposinfo.timeInSeconds).toString();
		if (count == 0) {
			trackPlayed = true;
		}


		

		switch (m.getChannel()) {
		case 1:
			if (m.isNoteOn())
			{
				uint8 velocity = m.getVelocity();
				if (btnState1) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				processedMidi.addEvent(m, time);
			}
			break;
		case 2:
			
			if (m.isNoteOn())
				{

				if (!bypassState) {
					midiNoteVal = labelNote(m.getMidiNoteName(m.getNoteNumber(), true, false, 4), CE[0], CE[1], CE[2]); //m.getMidiNoteName(m.getNoteNumber(), true, false, 4);

					if (playposinfo.timeInSeconds - old_time > 0.05) {
						++countMeasures;
						actualTime = playposinfo.timeInSeconds;

						if (countMeasures == 2) {
							c[0] = computeCE(playedNotes, noteTimes, countMeasures - 1, 0);
							c[1] = computeCE(playedNotes, noteTimes, countMeasures - 1, 1);
							c[2] = computeCE(playedNotes, noteTimes, countMeasures - 1, 2);

							CE_prev[0] = CE[0];
							CE_prev[1] = CE[1];
							CE_prev[2] = CE[2];

							CE[0] = alfa * c[0] + (1 - alfa) * CE_prev[0];
							CE[1] = alfa * c[1] + (1 - alfa) * CE_prev[1];
							CE[2] = alfa * c[2] + (1 - alfa) * CE_prev[2];

							harmTension_prev = harmTension;
							harmTension = getDistance(CE, CE_prev);

							if (selectedKey != 0 && selectedKey != 1) {
								if (btnState2) {
									actualKey[0] = T2[0][selectedKey];
									actualKey[1] = T2[1][selectedKey];
									actualKey[2] = T2[2][selectedKey];
									selectedTon = spiralArray[selectedKey + 4] + "m";
								}
								else {
									actualKey[0] = T1[0][selectedKey];
									actualKey[1] = T1[1][selectedKey];
									actualKey[2] = T1[2][selectedKey];
									selectedTon = spiralArray[selectedKey + 4];
								}
								tensileStrain = getDistance(actualKey, CE);
							}
							else {
								tensileStrain = 0.0;
								selectedTon = "not selected";
							}

							keyFinal = findKey(CE[0], CE[1], CE[2]);

							playedNotes.clearQuick();
							noteTimes.clearQuick();
							countMeasures = 0;

						}
						
						old_time = playposinfo.timeInSeconds;
						playedNotes.add(midiNoteVal);
						noteTimes.add(playposinfo.timeInSeconds);
					}
					// to handle chords 
					else {
						cloudDiameter_prev = cloudDiameter;
						cloudDiameter = getMaxDistance(playedNotes, old_time, noteTimes);

						playedNotes.add(midiNoteVal);
						noteTimes.add(playposinfo.timeInSeconds);
					}
				} else {
					tensileStrain = 0.0;
					cloudDiameter = 0.0;
					harmTension = 0.0;
				}

				processedMidi.addEvent(m, time);
			}
			break;
		case 3:
			if (m.isNoteOn())
			{
				if (btnState3) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}

				processedMidi.addEvent(m, time);
			}
			break;
		case 4:
			if (m.isNoteOn())
			{
				if (btnState4) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				processedMidi.addEvent(m, time);
			}
			break;
		case 5:
			if (m.isNoteOn())
			{
				

				if (btnState5) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				else {
					/*String midiNoteVal = m.getMidiNoteName(m.getNoteNumber(), true, false, 4);

					if (playposinfo.timeInSeconds != old_time) {
						old_time = playposinfo.timeInSeconds;
						playedNotes.clearQuick();
						playedNotes.add(midiNoteVal);
					}
					else {
						playedNotes.add(midiNoteVal);
						harmTension = getMaxDistance(playedNotes);
					}*/
				}
				processedMidi.addEvent(m, time);
			}
			break;
		case 6:
			if (m.isNoteOn())
			{
				
				if (btnState6) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				else {
					/*String midiNoteVal = m.getMidiNoteName(m.getNoteNumber(), true, false, 4);

					if (playposinfo.timeInSeconds != old_time) {
						old_time = playposinfo.timeInSeconds;
						playedNotes.clearQuick();
						playedNotes.add(midiNoteVal);
					}
					else {
						playedNotes.add(midiNoteVal);
						harmTension = getMaxDistance(playedNotes);
					}*/
				}
				processedMidi.addEvent(m, time);
			}
			break;
		case 7:
			if (m.isNoteOn())
			{
				
				
				if (btnState7) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				else {
					/*String midiNoteVal = m.getMidiNoteName(m.getNoteNumber(), true, false, 4);

					if (playposinfo.timeInSeconds != old_time) {
						old_time = playposinfo.timeInSeconds;
						playedNotes.clearQuick();
						playedNotes.add(midiNoteVal);
					}
					else {
						playedNotes.add(midiNoteVal);
						harmTension = getMaxDistance(playedNotes);
					}*/
				}
				processedMidi.addEvent(m, time);
			}
			break;
		case 8:
			if (m.isNoteOn())
			{
				
				

				if (btnState8) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				else {
					/*String midiNoteVal = m.getMidiNoteName(m.getNoteNumber(), true, false, 4);

					if (playposinfo.timeInSeconds != old_time) {
						old_time = playposinfo.timeInSeconds;
						playedNotes.clearQuick();
						playedNotes.add(midiNoteVal);
					}
					else {
						playedNotes.add(midiNoteVal);
						harmTension = getMaxDistance(playedNotes);
					}*/
				}
				processedMidi.addEvent(m, time);
			}
			break;
		case 10:
			if (m.isNoteOn())
			{
				if (btnState10) {
					uint8 newVel = 0;
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
				}
				else {
					midiCount++;
					beatPerSecond = (double(midiCount) / (playposinfo.timeInSeconds/60.0)+bpsOld)/2.0;
					bpsOld = beatPerSecond;
					
				}
				
				processedMidi.addEvent(m, time);
			}
			break;
	
		default:
			
			processedMidi.addEvent(m, time);
			break;
		}
		valueToSend = int(zeta*(100.0 + 6*cloudDiameter + 150*harmTension) + (1-zeta)*(100.0 + 6*cloudDiameter_prev  + 150*harmTension_prev));
		if (valueToSend > 127)
			valueToSend = 127;

		auto messageDimmer = MidiMessage::controllerEvent(8, 0, uint8(valueToSend));
		controllerNumber = messageDimmer.getDescription();
		addMessageToBuffer(messageDimmer, midiBuf);

		position = playposinfo.ppqPositionOfLastBarStart;
		/*if (position != oldMeasure) {
			countMeasure++;
			oldMeasure = position;
			if (countMeasure == 6) {
				auto messagePattern = MidiMessage::controllerEvent(8, rand() % 21 + 1, uint8(valueToSend));
				controllerNumber = messagePattern.getDescription();
				addMessageToBuffer(messagePattern, midiBuf);
				countMeasure = 0;
			} 
		}*/

		if (playposinfo.isPlaying)
			playing = true;
		else
			playing = false;

		if(count < 1)
			count++;

	}
	
	//midiMessages.swapWith(processedMidi);
	midiOutTracks->sendBlockOfMessagesNow(processedMidi);
	midiOutput->sendBlockOfMessagesNow(midiBuf);
}

Array<double> ProgettoProvaAudioProcessor::generate_maj_triad(int index, double w1, double w2, double w3) {
	Array<double> C_M = Array<double>();
	C_M.add(w1 * spiral[0][index] + w2 * spiral[0][index + 1] + w3 * spiral[0][index + 4]);
	C_M.add(w1 * spiral[1][index] + w2 * spiral[1][index + 1] + w3 * spiral[1][index + 4]);
	C_M.add(w1 * spiral[2][index] + w2 * spiral[2][index + 1] + w3 * spiral[2][index + 4]);
	return C_M;
}

Array<double> ProgettoProvaAudioProcessor::generate_min_triad(int index, double w1, double w2, double w3) {
	Array<double> C_m = Array<double>();
	C_m.add(w1 * spiral[0][index] + w2 * spiral[0][index+1] + w3 * spiral[0][index-3]);
	C_m.add(w1 * spiral[1][index] + w2 * spiral[1][index + 1] + w3 * spiral[1][index - 3]);
	C_m.add(w1 * spiral[2][index] + w2 * spiral[2][index + 1] + w3 * spiral[2][index - 3]);
	return C_m;
}

void ProgettoProvaAudioProcessor::generate_spiral() {
	double h = sqrt(2.0 / 15.0);
	double r = 1.0;
	for (int k = 0; k < spiralArray.size(); k++) {
		double k_f = double(k-15.0);
		spiral[0][k] = r*sin(k_f * M_PI_2);
		if (abs(spiral[0][k]) < pow(10, -8))
			spiral[0][k] = 0;

		spiral[1][k] = r*cos(k_f * M_PI_2);
		if (abs(spiral[1][k]) < pow(10, -8))
			spiral[1][k] = 0;

		spiral[2][k] = k_f * h;
		if (abs(spiral[2][k]) < pow(10, -8))
			spiral[2][k] = 0;
	}
}

void ProgettoProvaAudioProcessor::generate_keys(double w11, double w12, double w13, double u11, double u12, double u13, double alpha, double beta) {
	int T_index = 0;
	// up to 29 elements to make it 26
	for (int k = 4; k < 29 ; ++k) {
		Array<double> CM_tonic = generate_maj_triad(k, w11, w12, w13);
		Array<double> CM_dom = generate_maj_triad(k + 1, w11, w12, w13);
		Array<double> CM_subdom = generate_maj_triad(k - 1, w11, w12, w13);

		Array<double> Cm_tonic = generate_min_triad(k, u11, u12, u13);
		Array<double> Cm_dom = generate_min_triad(k + 1, u11, u12, u13);
		Array<double> Cm_subdom = generate_min_triad(k - 1, u11, u12, u13);

		T1[0][T_index] = w11 * CM_tonic[0] + w12 * CM_dom[0] + w13 * CM_subdom[0];
		if (abs(T1[0][T_index]) < pow(10, -8))
			T1[0][T_index] = 0.0;

		T1[1][T_index] = w11 * CM_tonic[1] + w12 * CM_dom[1] + w13 * CM_subdom[1];
		if (abs(T1[1][T_index]) < pow(10, -8))
			T1[1][T_index] = 0.0;

		T1[2][T_index] = w11 * CM_tonic[2] + w12 * CM_dom[2] + w13 * CM_subdom[2];
		if (abs(T1[2][T_index]) < pow(10, -8))
			T1[2][T_index] = 0.0;

		T2[0][T_index] = w11 * Cm_tonic[0] + w12 * (alpha * CM_dom[0] + (1 - alpha) * Cm_dom[0]) + w13 * (beta * CM_subdom[0] + (1 - beta) * Cm_subdom[0]);
		if (abs(T2[0][T_index]) < pow(10, -8))
			T2[0][T_index] = 0.0;

		T2[1][T_index] = w11 * Cm_tonic[1] + w12 * (alpha * CM_dom[1] + (1 - alpha) * Cm_dom[1]) + w13 * (beta * CM_subdom[1] + (1 - beta) * Cm_subdom[1]);
		if (abs(T2[1][T_index]) < pow(10, -8))
			T2[1][T_index] = 0.0;

		T2[2][T_index] = w11 * Cm_tonic[2] + w12 * (alpha * CM_dom[2] + (1 - alpha) * Cm_dom[2]) + w13 * (beta * CM_subdom[2] + (1 - beta) * Cm_subdom[2]);
		if (abs(T2[2][T_index]) < pow(10, -8))
			T2[2][T_index] = 0.0;

		++T_index;
	}
}

int ProgettoProvaAudioProcessor::getMinimumDistance(int idx1, int idx2, int idx3, double CEx, double CEy, double CEz) {
	double h = sqrt(2.0 / 15.0);
	double k1 = double(idx1);
	double k2 = double(idx2);
	double k3 = double(idx3);
	double notes[] = { spiral[0][idx1], spiral[1][idx1], spiral[2][idx1], k1, spiral[0][idx2], spiral[1][idx2], spiral[2][idx2], k2, spiral[0][idx3] , spiral[1][idx3], spiral[2][idx3], k3};

	double minDistance = sqrt(pow(CEx - notes[0], 2.0) + pow(CEy - notes[1], 2.0) + pow(CEz - notes[2], 2.0));
	int minIdx = idx1;
	for (int i = 0; i < 9; i=i+4) {
		double dist = sqrt(pow(CEx - notes[i], 2.0) + pow(CEy - notes[i+1], 2.0) + pow(CEz - notes[i+2], 2.0));
		if (dist < minDistance) {
			minIdx = int(notes[i + 3]);
			minDistance = dist;
		}
	}
	return minIdx;
}

String ProgettoProvaAudioProcessor::findKey(double cex, double cey, double cez) {
	double init[3] = { T1[0][0], T1[1][0], T1[2][0] };
	double ce[3] = { cex, cey, cez };
	double minDist = getDistance(ce, init);
	int minIndex = 0;
	bool isMajor = true;

	for (int i = 0; i < 25; ++i) {
		double coordsM[3] = { T1[0][i], T1[1][i], T1[2][i] };
		double coordsm[3] = { T2[0][i], T2[1][i], T2[2][i] };
		double distMaj = getDistance(ce, coordsM);
		if (distMaj < minDist) {
			minDist = distMaj;
			minIndex = i;
			isMajor = true;
		}
		double distMin = getDistance(ce, coordsm);
		if (distMin < minDist) {
			minDist = distMin;
			minIndex = i;
			isMajor = false;
		}
	}
	String note = spiralArray[minIndex + 4];
	String key = String();
	indexKey = minIndex;
	if (isMajor == false) {
		key = note + "m";
	}
	else {
		key = note;
	}
	return key;
}


String ProgettoProvaAudioProcessor::labelNote(String note, double CE_x, double CE_y, double CE_z) {
	int index = spiralArray.indexOf(note);
	if (index + 12 > spiralArray.size()) {
		// -12 -12 
		// calculate minimum distance
		int minIndex = getMinimumDistance(index, index-12, index-24, CE_x, CE_y, CE_z);
		String spelledNote = spiralArray[minIndex];
		return spelledNote;
	}
	else {
		// +12 -12
		// calculate minimum distance
		int minIndex = getMinimumDistance(index, index-12, index+12, CE_x, CE_y, CE_z);
		String spelledNote = spiralArray[minIndex];
		return spelledNote;
	}
}

double ProgettoProvaAudioProcessor::computeCE(StringArray notes, Array<double> timestamps, int b_a, int spNoteIndex) {
	double c_tot;
	Array<double> ntot = Array<double>(); // vettore che tiene conto del numero di note per ogni chunck
	double nj = 1.0;
	int bin = 0;

	for (int i = 1; i < timestamps.size()+1; ++i) {
		if (i >= timestamps.size())
			ntot.add(nj);
		else {
			if (timestamps[i] - timestamps[i-1] < 0.05) {
				nj += 1.0;
			}
			else {
				ntot.add(nj);
				nj = 1.0;
			}
		}
	}
	
	c_tot = 0;
	for (int i = 0; i <= b_a; ++i) {
		if (i != 0) 
			bin = bin + ntot[i - 1];
		for (int j = 0; j < ntot[i]; ++j) {
			if (i == 0) {
				c_tot = c_tot + spiral[spNoteIndex][spiralArray.indexOf(notes[j])] / ntot[i];
				}
			else {
				c_tot = c_tot + spiral[spNoteIndex][spiralArray.indexOf(notes[j + bin])] / ntot[i];
			}
		}
	}
	c_tot = c_tot / (double(b_a)+1.0);
	if (abs(c_tot) < pow(10, -8))
		c_tot = 0;
	return c_tot;
}

/*double* ProgettoProvaAudioProcessor::computePosition(int indexNote) {
	double *point = (double *) malloc(sizeof(double)*3);
	double h = sqrt(2.0 / 15.0);
	double k_f = double(indexNote);
	point[0] = sin(k_f * M_PI_2);
	if (point[0] < pow(10, -8))
		point[0] = 0;

	point[1] = cos(k_f * M_PI_2);
	if (point[1] < pow(10, -8))
		point[1] = 0;

	point[2] = k_f * h;
	if (point[2] < pow(10, -8))
		point[2] = 0;

	return point;
}*/

double ProgettoProvaAudioProcessor::getDistancefromC1(String note) {
	/* calcuate distance of the from C4 (supposed as the key)*/
	int k = 0;
	double x0 = 0, y0 = 1, z0 = 0, x, y, z;
	double h = sqrt(2.0/15.0);
	k = spiralArray.indexOf(note);
	double k_f = double(k);
	x = sin(k_f * M_PI_2);
	y = cos(k_f * M_PI_2);
	z = k_f * h;
	double dist = sqrt(pow(x-x0, 2.0) + pow(y - y0, 2.0) + pow(z - z0, 2.0));
	return dist;
}

double ProgettoProvaAudioProcessor::getMaxDistance(StringArray notes, double refTime, Array<double> timeNotes) {
	double maxDistance = 0.0;
	for (int i = 0; i < notes.size() - 1; i++) {
		for (int j = 0; j < notes.size() - 1; j++) {
			if (refTime - timeNotes[i] < 0.05 && refTime - timeNotes[j] < 0.05) {
				double x1, y1, z1, x2, y2, z2;

				x1 = spiral[0][spiralArray.indexOf(notes[i])];
				y1 = spiral[1][spiralArray.indexOf(notes[i])];
				z1 = spiral[2][spiralArray.indexOf(notes[i])];

				x2 = spiral[0][spiralArray.indexOf(notes[j])];
				y2 = spiral[1][spiralArray.indexOf(notes[j])];
				z2 = spiral[2][spiralArray.indexOf(notes[j])];

				double dist = sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0) + pow(z2 - z1, 2.0));

				if (dist > maxDistance)
					maxDistance = dist;
			}
		}
	}
	return maxDistance;
}

double ProgettoProvaAudioProcessor::getDistance(double* p1, double* p2) {
	double dist = sqrt(pow(p1[0] - p2[0], 2.0) + pow(p1[1] - p2[1], 2.0) + pow(p1[2] - p2[2], 2.0));
	return dist;
}

void ProgettoProvaAudioProcessor::addMessageToBuffer(const MidiMessage& message, MidiBuffer& buffer)
{
	auto timestamp = message.getTimeStamp();
	auto sampleNumber = (int)(timestamp * 48000);
	buffer.addEvent(message, sampleNumber);
}

void ProgettoProvaAudioProcessor::sendMessage()
{
	btnClick = true;
}

//==============================================================================
bool ProgettoProvaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ProgettoProvaAudioProcessor::createEditor()
{
    return new ProgettoProvaAudioProcessorEditor (*this);
}


//==============================================================================
void ProgettoProvaAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ProgettoProvaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProgettoProvaAudioProcessor();
}
