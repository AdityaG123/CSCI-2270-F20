#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

struct wordRecord {
  string word;
  int count;
};

void arrayDouble(wordRecord * &inArray, int &N){
  wordRecord* temp = new wordRecord[2 * N];
  for (int i = 0; i < N; i++) {
    temp[i] = inArray[i];
  }
  delete [] inArray;
  inArray = temp;
  N = 2 * N;
}

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]) {
  ifstream ignwords(ignoreWordFileName);
  if (ignwords.fail()) {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
  string temp;
  
  for (int i = 0; i < 50; i++) {
    getline(ignwords, temp);
    ignoreWords[i] = temp;
  }
}

bool isIgnoreWord(string word, string ignoreWords[]) {
  for (int i = 0; i < 50; i++) {
    if (word == ignoreWords[i]) {
      return true;
    }
  }
  return false;
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length) {
  int total = 0;
  for (int i = 0; i < length; i++) {
    total = total + distinctWords[i].count;
  }
  return total;
}

void sortArray(wordRecord distinctWords[], int length) {
  wordRecord temp;
  int i, j;
  for (i = 0; i < length; i++) {
    for (j = 0; j < length; j++) {
      if (distinctWords[i].count > distinctWords[j].count) {
        temp = distinctWords[j];
        distinctWords[j] = distinctWords[i];
        distinctWords[i] = temp;
      }
    }
  }
  for(i = 0; i < length; i++){
    for(j = i + 1; j < length; j++){
      if(distinctWords[i].count == distinctWords[j].count){
        if(distinctWords[i].word > distinctWords[j].word){
          temp = distinctWords[i];
          distinctWords[i] = distinctWords[j];
          distinctWords[j] = temp;
        }
      }
    }
  }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords) {
  for (int i = N; i < N + 10; i++) {
    cout << fixed << setprecision(5) << round(100000 * ((float) distinctWords[i].count/totalNumWords)) / 100000 << " - " << distinctWords[i].word << endl;
  }
}

int main(int argc, char const *argv[]) {
  int length = 100;
  int noncommon = 1;
  int arrDouble = 0;
  string ignoreWords[50];
  
  getIgnoreWords(argv[3],ignoreWords);
  wordRecord *distinctWords;
  distinctWords = new wordRecord[length];
  int index = stof(argv[1]);
  ifstream mdick(argv[2]);
  string temp;
  
  while(mdick.good()) {
    bool added = false;
    mdick >> temp;
    if (!isIgnoreWord(temp, ignoreWords)) {
      for (int i = 0; i < noncommon; ++i) {
        if (temp == distinctWords[i].word && !added) {
          distinctWords[i].count++;
          added = true;
        } 
        else if (i == noncommon -1 && !added) {
          distinctWords[i].word = temp;
          distinctWords[i].count = 1;
          added = true;
          noncommon++;
        }
      }
      if (noncommon == length) {
        arrayDouble(distinctWords, length);
        arrDouble++;
      }
    }
  }
  
  int totalWords = getTotalNumberNonIgnoreWords(distinctWords, noncommon);
  cout << "Array doubled: " << arrDouble << endl << "Distinct non-common words: " << noncommon - 1 << endl << "Total non-common words: " << totalWords - 1 << endl;
  sortArray(distinctWords, length);
  cout << "Probability of next 10 words from rank " << stof(argv[1]) << endl;
  cout << "---------------------------------------" << endl;
  printTenFromN(distinctWords, stof(argv[1]), totalWords);

  return 0;
}