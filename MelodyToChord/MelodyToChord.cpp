#include "pch.h"
#include "framework.h"
#include "MIDIClock.h"
#include "MIDIIO.h"
#include "Chords.h"
#include "ChordRecommend.h"
#include "MelodyToChord.h"
#include <string>
#include <iostream>
#include <map>
#include <thread>

MelodyToChord::MelodyToChord() {
	std::cout << "create!" << std::endl;
}

MelodyToChord::~MelodyToChord() {
	std::cout << "delete!" << std::endl;
}

int MelodyPrint(std::multimap<int, int>& melodyAndTime) {
	multimap <int, int> ::iterator iter;
	for (iter = melodyAndTime.begin(); iter != melodyAndTime.end(); iter++) {
		return iter->first;
	}
}

int MelodyPrintOne(std::multimap<int, int>& melodyAndTime) {
	if (melodyAndTime.empty() == false) {
		multimap <int, int> ::iterator iter;
		--iter;
		return iter->first;
	} else {
		return -1;
	
	}

}

bool enterExit(map<string, int> &recommendedResult, bool exitroop) {
	cout << "thread" << endl;
	if (recommendedResult.empty() != true) {
		char ch;
		cin.get(ch);
		if (ch == '\n') exitroop = true;
		return exitroop;
	}

}

map<string, int> MelodyToChord::ChordRecommendClock(std::multimap<int, int>& melodyAndTime, ChordRecommend& chords, bool stop) {
	if (stop == true && melodyAndTime.size() > 0) {
		multimap<int, int> melodyAndTimeCopy = melodyAndTime;
		int cl = clock();
		cout << "clock when press enter : " << cl << endl;

		multimap <int, int> ::iterator iter;
		multimap <int, int> ::iterator tmp1;
		multimap <int, int> ::iterator tmp2;
		multimap <int, int> ::iterator max = melodyAndTime.begin();

		vector<vector<multimap <int, int> ::iterator>> melodyOnePhrase;

		for (iter = melodyAndTime.begin(); iter != melodyAndTime.end(); iter++) {
			chords.SaveNoteset(iter->first);

			tmp1 = iter;

			tmp2 = ++tmp1;
			if (tmp2 == melodyAndTime.end()) {
				tmp2 = iter;
			}

			if (max->second < tmp2->second) {
				max = tmp2;
				cout << "max iter : " << max->first << " / " << max->second << endl;
			}
		}
		chords.AddictionalPoint(max);

		melodyAndTimeCopy.clear();
		return chords.Recommend();


	}

}

int MelodyToChord::Setting() {

	/* MIDI入力デバイス(No.0)の名前を調べる */
	lRet = MIDIIn_GetDeviceName(0, szDeviceName, 32);
	if (lRet == 0) {
		printf("利用できるMIDI入力デバイスはありません。\n");
		return 0;
	}
	/* MIDI入力デバイスを開く */
	pMIDIIn = MIDIIn_Open(szDeviceName);
	if (pMIDIIn == NULL) {
		//printf("MIDI入力デバイス「%s」を開けません。\n", szDeviceName);
		std::cout << "MIDI入力デバイス " << *szDeviceName << " を開けません。" << std::endl;
		return 0;
	}
	//printf("MIDI入力デバイス「%s」を開きました。\n", szDeviceName);
	std::cout << "MIDI入力デバイス " << *szDeviceName << " を開きました。" << std::endl;
	/* MIDI出力デバイス(No.0)の名前を調べる */
	lRet = MIDIOut_GetDeviceName(0, szDeviceName, 32);
	if (lRet == 0) {
		MIDIIn_Close(pMIDIIn);
		printf("利用できるMIDI出力デバイスはありません。\n");
		return 0;
	}
	/* MIDI出力デバイスを開く */
	pMIDIOut = MIDIOut_Open(szDeviceName);
	if (pMIDIOut == NULL) {
		MIDIIn_Close(pMIDIIn);
		//printf("MIDI出力デバイス「%s」を開けません。\n", szDeviceName);
		std::cout << "MIDI出力デバイス " << *szDeviceName << " を開けません。" << std::endl;
		return 0;
	}
	//printf("MIDI出力デバイス「%s」を開きました。\n", szDeviceName);
	std::cout << "MIDI出力デバイス " << *szDeviceName << " を開きました。" << std::endl;

}

map<string,int> MelodyToChord::main() {
	std::cout << "main on" << std::endl;
	std::vector<int> melodyArray;
	static std::multimap<int, int> melodyAndTime;
	std::map <string, int> recommendedResult;
	bool exitroop = false;
	/* 10秒 = 10000 */
	/* 1秒 = 1000 */
	/* 2秒 = 2000 */

	ChordRecommend chords;
	const int bpm = 120;
	const int onePhraseSec = (bpm * 1000) / 120;

	int startTime = 0;
	int endTime = 0;
	bool stop = false;

	while (clock() < 20000) { //20秒
		//std::cout << "clock" << std::endl;
		/* MIDI入力デバイスからメッセージを取得する */
		lRet = MIDIIn_GetMIDIMessage(pMIDIIn, byMessage, 256);
		/* MIDIメッセージを取得した場合 */
		if (lRet > 0) {
			std::cout << "clock2" << std::endl;
			/* MIDI出力デバイスからメッセージを送出する */
			MIDIOut_PutMIDIMessage(pMIDIOut, byMessage, lRet);
			int melodyNum = int(byMessage[1]); //入力されたメロディを整数値に変換
			if (int(byMessage[0]) != 128) { // byMessage[0]=128は入力が終了したときに出る。よって、入力開始時のメロディだけ受け取る
				std::cout << "clock3" << std::endl;
				//cout << melodyNum << "の入力開始時間は " << clock() << " です" << endl;
				startTime = clock();
			}

			if (int(byMessage[0]) == 128) {
				//cout << melodyNum << "の入力終了時間は " << clock() << " です" << endl;
				endTime = clock();

				int inputTime = endTime - startTime;

				melodyAndTime.insert(pair<int, int>(melodyNum, inputTime));

				cout << melodyAndTime.size() << endl;
				stop = true;
				
				//MelodyPrintOne(melodyAndTime);
				multimap <int, int> ::iterator iter;
				iter = melodyAndTime.end();
				--iter; // end()は最後の次のイテレータを返すので最後を指し示すためには-1をしなければならない
				//cout << melodyNum << "は " <<  iter->second<< " 間押されました" << endl;
				if (melodyAndTime.empty() != true)
					recommendedResult = ChordRecommendClock(melodyAndTime, chords, stop);
				melodyAndTime.clear();
				stop = false;
				startTime = 0;
				endTime = 0;
			}

		}
		/* MIDIメッセージを取得しなかった場合 */
		else {
			//Sleep(1);
		}
		
	}


	cout << "----------input time end-------------" << endl;


	/* MIDI入力デバイスを閉じる */
	MIDIIn_Close(pMIDIIn);
	/* MIDI出力デバイスを閉じる */
	MIDIOut_Close(pMIDIOut);
	return recommendedResult;

}