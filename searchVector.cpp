// PROGRAM: searchVector.cpp
// PURPOSE: Searches a given vector and finds position of a user-specified value. If value is found,
// the program will save the position to a file, or display the result on-screen.
// Kyle Eng

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cstddef>
using namespace std;

string vectToStr(vector<string> vect);
string searchVector(string vecStr, string searchVal);
void writeResult(string option, string fileName, string result);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "One argument expected. Vector should be given in the form of a comma-delimited string." << endl;
    return 1;
  }
  string vectStr = argv[1];
  //cout << "vector string is " << vectStr << endl;
  
  cout << "Enter value to search in the vector:" << endl;
  string searchVal;
  getline(cin, searchVal);
  
  string result = searchVector(vectStr, searchVal);
  
  cout << "Enter one of the listed numbers (e.g. '1' or '2') to execute the option:" << endl;
  cout << "1.) Overwrite a file 2.) Save to a new file 3.) Display on-screen" << endl;
  string option;
  getline(cin, option);
  
  string fileName;
  if ( (option == "1") || (option == "2") ) {
    cout << "Enter file name:" << endl;
    getline(cin, fileName);
  }
  writeResult(option, fileName, result);
  return 0;
}

string vectToStr(vector<string> vect) {
  stringstream sStream;
  for (int i = 0; i < vect.size(); i++) {
    if (i != 0)
      sStream << ",";
    sStream << vect[i];
  }
  string str = sStream.str();
  return str;
}

// Gets position of search value in vector. If value not found, it is prepended to vector.
string searchVector(string vecStr, string searchVal) {
  vector<string> vect;
  
  string str = vecStr;
  str.push_back('\0');
  // saving user string to vector
  for (int i = 0, j = 0; i < str.size(); i++) {
    if( (str.at(i) == ',') || (str.at(i) == '\0') ){
      vect.push_back(str.substr(j,i-j));
      j = i+1;
    }
  }
  
  string result;
  ptrdiff_t valPos = find(vect.begin(), vect.end(), searchVal) - vect.begin();
  //cout << "pos is " << to_string(valPos) << endl;
  if (valPos >= vect.size()) {
    // value not found
    // value is prepended to vector
    vect.insert(vect.begin(), searchVal);
    result = vectToStr(vect);
    return result;
  } else {
    result = "Position of " + searchVal + " in vector is " + to_string(valPos);
    return result;
  }
}

// Saves result to a file, or displays it on-screen
void writeResult(string option, string fileName, string result) {
  if (option == "1") {
    // overwriting file
    ofstream fout;
    fout.open(fileName, ios::out | ios::trunc);
    if (fout.good()) {
      fout << result << endl;
      cout << "Result successfully saved" << endl;
    } else {
      cout << "Error in overwriting file" << fileName << endl;
    }
    fout.close();
  } else if (option == "2") {
    // saving to new file
    ofstream fout;
    fout.open(fileName, ios::out);
    if (fout.good()) {
      fout << result << endl;
      cout << "Result successfully saved" << endl;
    } else {
      cout << "Error in saving result to file" << fileName << endl;
    }
    fout.close();
  } else {
    cout << "Result is: " << result << endl;
  }
}