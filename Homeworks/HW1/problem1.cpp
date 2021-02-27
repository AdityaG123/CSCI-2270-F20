#include <iostream>
#include <fstream>
using namespace std;



int addToArrayAsc(float sortedArray[], int numElements, float newValue) {
  int i, j;
  float temp;
  i = 0;
  j = 0;
  string output = "";
  sortedArray[numElements] = newValue;

  for (i = 0; i <= numElements; i++) {
    for (j = 0; j <= numElements; j++) {
      if (sortedArray[j] > sortedArray[i]) {
        temp = sortedArray[i];
        sortedArray[i] = sortedArray[j];
        sortedArray[j] = temp;
      }
    }
  }

  for (i = 0; i < numElements + 1; i++) {
    if (i == 0) {
      cout << sortedArray[i];
    } 
    else {
      cout << "," << sortedArray[i];
    }
  }
  cout << endl;
  return numElements + 1;
}

int main(int argc, char const *argv[]) {
  float array[100];
  int i = 0;
  ifstream ifile(argv[1]);
  string tempString;
  
  if(ifile.is_open()){
      while (!ifile.eof()) {
          getline(ifile, tempString);
          addToArrayAsc(array, i, stof(tempString));
          i++;
      }
  }
  
  else{
      std::cout << "Failed to open the file." << std::endl;
  }
 
  return 0;
}