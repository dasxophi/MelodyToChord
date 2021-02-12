#pragma once
#include "Chords.h"
using namespace std;


class ChordRecommend : public Chords {

private:
	string longMelody;

public:
	void AddictionalPoint(multimap <int, int> ::iterator max) {
		longMelody = ReturnNoteset(max->first); // 加算点
	}
	map<string, int> Recommend() {
		int count = 0;

		for (string noteset : savenoteset) {
			for (auto chordname : AllchordList) {

				if (std::find(chordname.begin(), chordname.end(), noteset) != chordname.end()) {
					if (std::find(set.begin(), set.end(), chordname) == set.end()) { // setの中に推薦するコードが存在していない場合
						set.push_back(chordname); //　コードを推薦リストに追加　　　　　　　　　　　　　　　　　　　　
						ChordAndCount.insert(pair<vector<string>, int>(chordname, 1));
						//cout << chordname.at(0) << "が推薦されました" << endl;


					}
					else if (std::find(set.begin(), set.end(), chordname) != set.end()) { // setの中に推薦するコードが存在してる場合　
						count++;
						ChordAndCount[chordname] = ChordAndCount[chordname] + count;// 存在しているコードの推薦回数を一つ増やす
						//cout << chordname.at(0) << "が推薦されました" << endl;
						count = 0;
					}

				}
				//longMelodyについてはコード推薦をもう一度行う(longMelodyはコードを決定するときに特に重要なので)
				if (std::find(chordname.begin(), chordname.end(), longMelody) != chordname.end()) {
					if (std::find(set.begin(), set.end(), chordname) == set.end()) { // setの中に推薦するコードが存在していない場合
						set.push_back(chordname); //　コードを推薦リストに追加　　　　　　　　　　　　　　　　　　　　
						ChordAndCount.insert(pair<vector<string>, int>(chordname, 1));
						//cout << chordname.at(0) << "が推薦されました" << endl;


					}
					else if (std::find(set.begin(), set.end(), chordname) != set.end()) { // setの中に推薦するコードが存在してる場合　
						count++;
						//ChordAndCount[chordname] = ChordAndCount[chordname] + count;// 存在しているコードの推薦回数を一つ増やす
						//cout << chordname.at(0) << "が推薦されました" << endl;
						count = 0;
					}
				}

			}
		}
		map < vector<string>, int> ::iterator iter;
		map<string, int>  result;
		
		for (iter = ChordAndCount.begin(); iter != ChordAndCount.end(); iter++) {
			cout << iter->first.at(0) << " " << iter->second << "point  " << endl;
			result.insert(pair<string,int>(iter->first.at(0), iter->second));
			//String^ csString = msclr::interop::marshal_as<String^>(iter->first.at(0));
			//result->Add(csString, iter->second);
		}
		//Dictionary<String^, int>^ result2 = marshal_as<Dictionary<String^, int>^>(result);
		return result;
		savenoteset.clear();
		ChordAndCount.clear();
		
	}


};