// libraries
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <regex>
using namespace std;

void fileCleaner(string &str, map<string, int>&);


int main(){
  map<string,int> word_count;
  string read_csv, read_stopwords; // string var for reading csv file and reading stopwords file
  ofstream cleaned_words; // creates write object for cleaned words file
  ifstream file_csv, stop_words; // creates read object for csv file and stopwords file


  cleaned_words.open("/Users/ahmedalnoor/Documents/TechScholars/TechScholars-Group-1/src/cleaned_words.txt");
  file_csv.open("/Users/ahmedalnoor/Documents/TechScholars/TechScholars-Group-1/src/jobs.csv"); // take in csv file
  stop_words.open("/Users/ahmedalnoor/Documents/TechScholars/TechScholars-Group-1/src/stopwords_en_minus_c_r.txt"); // take in csv file


  while(getline(file_csv,read_csv)){ // print lines from csv files
    fileCleaner(read_csv, word_count);

  }

  for (const auto& x : word_count) {
    cout << x.first << ": " << x.second << "\n";
   }


  while(getline(file_csv,read_stopwords)){ // print lines from csv files
  }

  return 0;

}

// Function that changes all characters to upper case (to avoid checking for it) and removes all symbols
void fileCleaner(string &str, map<string, int>& words) {

  //1. Looping through and changing each individual character to upper case.
  for (int x = 0; x < str.length(); x++) {
    str[x] = toupper(str[x]);
  }

  //2. Using regular expressions (C++11) to remove all symbols and non-letters.
  regex reg{"([a-zA-Z]+)"}; //This regex will search for all upper case letters and omit all symbols.
  smatch match; // This will store the result of the regex.
  sregex_iterator currentMatch{ str.begin(), str.end(), reg }; //This iterator helps to find all instances of the regex, instead of just one.
  sregex_iterator lastMatch;
  while (currentMatch != lastMatch) {
    match = *currentMatch;
    cout << match.str() << endl;
    ++words[match.str()];
    currentMatch++;
  }

}
