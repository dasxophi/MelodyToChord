#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;


typedef vector<int> noteset;
typedef vector<noteset> chord;
typedef vector<chord> recommendset;

class Chords {
private:
	noteset _C{ 0,12,24,36,48,60,72,84,96,108,120 }; // Cの音が出る全ての場合をvectorでまとめた
	noteset _Db{ 1,13,25,37,49,61,73,85,97,109,121 };
	noteset _D{ 2,14,26,38,50,62,74,86,98,110,122 };
	noteset _Eb{ 3,15,27,39,51,63,75,87,99,111,123 };
	noteset _E{ 4,16,28,40,52,64,76,88,100,112,124 };
	noteset _F{ 5,17,29,41,53,65,77,89,101,113,125 };
	noteset _Gb{ 6,18,30,42,54,66,78,90,102,114,126 };
	noteset _G{ 7,19,31,43,55,67,79,91,103,115,127 };
	noteset _Ab{ 8,20,32,44,56,68,80,92,104,116,128 };
	noteset _A{ 9,21,33,45,57,69,81,93,105,117,129 };
	noteset _Bb{ 10,22,34,46,58,70,82,94,106,118,130 };
	noteset _B{ 11,23,35,47,59,71,83,95,107,119,131 };

protected:
	vector<vector<string>> set;
	vector<string> savenoteset;

public:
	vector<string> C{ "[C]", "C","E","G" }; // 最初の要素はコードネーム
	vector<string> Dm{ "[Dm]" ,"D","F","A" };
	vector<string> Em{ "[Em]", "E","G","B" };
	vector<string> F{ "[F]", "F","A","C" };
	vector<string> G{ "[G]", "G","B","D" };
	vector<string> Am{ "[Am]" ,"A","C","E" };
	vector<string> Bdim{ "[Bdim]", "B","D","F" };
	vector<string> CM7{ "[CM7]", "C","E","G","B" };
	vector<string> Dm7{ "[Dm7]", "D","F","A","C" };
	vector<string> Em7{ "[Em7]", "E","G","B","D" };
	vector<string> FM7{ "[FM7]", "F","A","C","E" };
	vector<string> G7{ "[G7]", "G","B","D","F" };
	vector<string> Am7{ "[Am7]", "A","C","E","G" };
	vector<string> Bm7b5{ "[Bm7b5]", "B","D","F","A" };
	vector<string> Cm{ "[Cm]", "C","Db","G" };
	vector<string> D{ "[D]", "D","Gb","A" };
	vector<string> E{ "[E]", "E","Ab","B" };
	vector<string> Fm{ "[Fm]", "F","Ab","C" };
	vector<string> Gm{ "[Gm]", "G","Bb","D" };

	std::vector<vector<string>> AllchordList
	{ C, Dm, Em, F, G, Am, Bdim,
	  CM7, Dm7, Em7, FM7, G7, Am7, Bm7b5,
	  Cm, D, E, Fm, Gm
	};

	map<vector<string>, int> ChordAndCount;

	void SaveNoteset(int num) { //savenotesetに判定された音を入れる
		savenoteset.push_back(ReturnNoteset(num));
		std::cout << "入力されたノート数 : " << savenoteset.size() << std::endl;
	}

	void printNoteset() {
		for (auto n : savenoteset) {
			std::cout << "[" << n << "]" << std::endl;
		}
	}

	string ReturnNoteset(int note) { //受け取った整数値がどんな音なのかを判定
		if (std::find(_C.begin(), _C.end(), note) != _C.end()) {
			std::cout << "this is C note" << std::endl;
			return "C";
		}
		else if (std::find(_Db.begin(), _Db.end(), note) != _Db.end()) {
			std::cout << "this is Db(C#) note" << std::endl;
			return "Db";
		}
		else if (std::find(_D.begin(), _D.end(), note) != _D.end()) {
			std::cout << "this is D note" << std::endl;
			return "D";
		}
		else if (std::find(_Eb.begin(), _Eb.end(), note) != _Eb.end()) {
			std::cout << "this is Eb(D#) note" << std::endl;
			return "Eb";
		}
		else if (std::find(_E.begin(), _E.end(), note) != _E.end()) {
			std::cout << "this is E note" << std::endl;
			return "E";
		}
		else if (std::find(_F.begin(), _F.end(), note) != _F.end()) {
			std::cout << "this is F note" << std::endl;
			return "F";
		}
		else if (std::find(_Gb.begin(), _Gb.end(), note) != _Gb.end()) {
			std::cout << "this is Gb(F#) note" << std::endl;
			return "Gb";
		}
		else if (std::find(_G.begin(), _G.end(), note) != _G.end()) {
			std::cout << "this is G note" << std::endl;
			return "G";
		}
		else if (std::find(_Ab.begin(), _Ab.end(), note) != _Ab.end()) {
			std::cout << "this is Ab(G#) note" << std::endl;
			return "Ab";
		}
		else if (std::find(_A.begin(), _A.end(), note) != _A.end()) {
			std::cout << "this is A note" << std::endl;
			return "A";
		}
		else if (std::find(_Bb.begin(), _Bb.end(), note) != _Bb.end()) {
			std::cout << "this is Bb(A#) note" << std::endl;
			return "Bb";
		}
		else if (std::find(_B.begin(), _B.end(), note) != _B.end()) {
			std::cout << "this is B note" << std::endl;
			return "B";
		}
	}

	~Chords() {
		"desturctor on";
	}
};

