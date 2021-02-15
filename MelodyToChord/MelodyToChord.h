#pragma once
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <vector>
#include <thread>
#include <string>
#include <functional>
#include <map>
#include "pch.h"
#include "framework.h"
#include "MIDIClock.h"
#include "MIDIIO.h"
#include "Chords.h"
#include "ChordRecommend.h"


class MelodyToChord {
private:
	MIDIIn* pMIDIIn;
	MIDIOut* pMIDIOut;
	wchar_t szDeviceName[32];
	unsigned char byMessage[256];
	long lRet;
	bool exitflag = false;
public:
	MelodyToChord();
	~MelodyToChord();
	int Setting();
	int MelodyPrint(std::multimap<int, int>& melodyAndTime);
	int MelodyPrintOne(std::multimap<int, int>& melodyAndTime);
	map<string, int>  main();
	map<string, int>  ChordRecommendClock(multimap<int, int>& melodyAndTime, ChordRecommend& chords, bool stop);
	void exitFlag();
};


