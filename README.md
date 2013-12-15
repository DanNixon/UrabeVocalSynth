UrabeVocalSynth
===============

A waveform and Japanese voice MIDI synthesiser

NOTE: This project is still in development.

Features
--------

*	Single hand kana entry keypad
*	512 space kana buffer
*	Ability to use predefined kana buffer
*	Highly configurable waveform synth

Requirements
------------

1.  Arduino Mega
2.  [GinSing Arduino shield](http://ginsingsound.com/) or [BabbleBot IC](http://babblebot.net/) and GinSing library
3.  MIDI input device
4.  Graphic LCD
5.  Arduino [MIDI library](http://playground.arduino.cc/Main/MIDILibrary)
6.  [u8glib](https://code.google.com/p/u8glib/) library

Waveform Synth Options
----------------------

Much of this is based on the GinSing reference.

*	Waveform
	*	Sets the synth waveform
	*	Possible options: Sine, Triangle, Square, Sawtooth, Ramp, Noise
*	Frequency Distortion
	*	Sets distortion to the DCO waveform
	*	Range from 0 to 1000, MIDI controllable
*	Overflow
	*	Enables or disables integer overflow of the wave table pointer in the Babblebot IC
	*	Disabling gives accurate frequency but produced audio artifacts
	*	Enabling gives a quantized frequency but no artifacts
*	Duty Cycle
	*	Sets duty cycle for square waveform mode
	*	Range from -1000 to 1000, where -1000 is fully negative and 1000 is fully positive
*	Envelope
	*	Attack Duration
		*	Time taken to reach attack volume after DCO is triggered
		*	Possible values: 2, 8, 16, 24, 38, 56, 68, 80, 100, 125, 500, 800, 1000, 2800, 5600, 11200 ms
		*	MIDI Controllable
	*	Attack Volume
		*	Preset volume for attack envelope stage
		*	Range from 0 to 1000, MIDI controllable
	*	Decay Duration
		*	Time taken to reach decay volume after attack stage
		*	Possible values: 2, 6, 10, 15, 23, 34, 40, 48, 59, 145, 292, 455, 575, 1500, 2785, 4873 ms
		*	MIDI Controllable
	*	Decay Volume
		*	Preset volume for decay envelope stage
		*	MIDI Controllable
	*	Release Duration
		*	Time taken to reach release volume after DCO is released
		*	Possible values: 2, 6, 10, 15, 23, 34, 40, 48, 59, 145, 292, 455, 575, 1500, 2785, 4873 ms
		*	MIDI Controllable
	*	Release Volume
		*	Preset volume for release envelope stage
		*	MIDI Controllable