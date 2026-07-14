# harmonic-tension-vst3

Plugin audio VST3 scritto in C++ sul framework JUCE che ascolta il MIDI in ingresso in tempo reale
e trasforma l'analisi armonica in un segnale di controllo live per l'illuminazione del palco,
anziche' per il suono. Implementa lo Spiral Array Model di Elaine Chew, una rappresentazione
geometrica dell'armonia tonale, per derivare dalla sequenza di note suonate e dalla loro tempistica
delle metriche di tensione utilizzabili per pilotare luci di scena in tempo reale.

## Come funziona

Dalla sequenza di note MIDI e dai relativi timestamp, il plugin calcola il centro di effetto
(center of effect) delle note suonate sulla spirale armonica, e da li' deriva tre metriche:
tensione armonica (harmonic tension), diametro della nuvola (cloud diameter) e tensile strain.
La tonalita' corrente viene stimata trovando il punto piu' vicino sulla spirale al centro di
effetto calcolato. Questi valori numerici, aggiornati in tempo reale a ogni blocco audio, sono
pensati per essere mappati su variazioni di luminosita' e pattern delle luci di scena da un sistema
di illuminazione esterno.

L'idea e' stata dimostrata dal vivo, mappando i valori di tensione derivati sull'illuminazione del
palco, all'evento di musica elettronica Festivalle nella Valle dei Templi, agosto 2019.

## Stato del progetto

La classe processore si chiama ancora `ProgettoProvaAudioProcessor` nel codice sorgente
(`PluginProcessor.h`), residuo del nome dato dallo scaffolding di progetto generato automaticamente
da JUCE ("test project" in italiano). Questo segnala che il plugin e' rimasto un prototipo
funzionante, dimostrato dal vivo, piuttosto che una release rifinita e ripulita per la
distribuzione. La logica di calcolo (generazione della spirale, calcolo delle distanze, ricerca
della tonalita' piu' vicina) e' interamente contenuta in `PluginProcessor.cpp/.h`; `PluginEditor.cpp/.h`
gestisce l'interfaccia del plugin.

## Documentazione

Il PDF incluso nel repository ("Implementation of a VST3 plugin based on the geometrical modelling
of Tonal Harmony with the Spiral Array model within the Juce framework for intelligent lighting
engineering purposes") documenta il modello geometrico sottostante e il caso d'uso
dell'illuminazione intelligente in modo piu' approfondito di quanto facciano i commenti nel codice,
ed e' il riferimento da consultare per capire la teoria prima di leggere l'implementazione.

## Stack tecnico

C++ sul framework JUCE, targeting VST3. Il codice e' quello generato dallo scaffolding standard di
un progetto audio plugin JUCE, con la logica del modello Spiral Array aggiunta sopra.
