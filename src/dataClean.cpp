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
  map<string,int> word_map;
  map<string,int> cleaned_word_maps;
  string read_csv, read_stopwords; // string var for reading csv file and reading stopwords file
  ofstream cleaned_words; // creates write object for cleaned words file
  ifstream file_csv, stop_words; // creates read object for csv file and stopwords file


  cleaned_words.open("/Users/ahmedalnoor/Documents/TechScholars/TechScholars-Group-1/src/cleaned_words.txt");
  file_csv.open("/Users/ahmedalnoor/Documents/TechScholars/TechScholars-Group-1/src/jobs.csv"); // take in csv file
  stop_words.open("/Users/ahmedalnoor/Documents/TechScholars/TechScholars-Group-1/src/stopwords_en_minus_c_r.txt"); // take in csv file



  while(getline(file_csv,read_csv)) { // print lines from csv files
      fileCleaner(read_csv, word_map);
  }

  //* Creating a duplicate of the original map of words.
  cleaned_word_maps.insert(word_map.begin(), word_map.end());

  // cleaned_word_maps.erase("ZOOM");
  //
  // for (const auto& x: cleaned_word_maps){
  //   cout << x.first << ": " << x.second << "\n";
  // }



  // for (const auto& x : word_map){
  //   cout << x.first << ": " << x.second << "\n";
  // }

  while(getline(stop_words,read_stopwords)){ // print lines from csv files
    for(int i = 0; i < read_stopwords.length(); i++) {
      read_stopwords[i] = toupper(read_stopwords[i]);
    }

    auto isFound = word_map.find(read_stopwords);
    if(isFound != word_map.end()){
      cout << " found ";
    }
    // if((word_map.count( read_stopwords)) == 1){
    //   cleaned_word_maps.erase(read_stopwords);
    // }

    // cout << read_stopwords << endl;
    // map<string,int>::iterator it;
    // it = word_map.find(read_stopwords);
    // if (it != word_map.end()) {
    //   cleaned_word_maps.erase (it);
    // }
    // if (cleaned_word_maps.find(read_stopwords) == cleaned_word_maps.end()) {
    //   cleaned_word_maps.erase(read_stopwords);
    // }
  }

  cout << cleaned_word_maps.size()<< endl;
  cout << word_map.size() << endl;

  // for (const auto& x: cleaned_word_maps){
  //   cout << x.first << ": " << x.second << "\n";
  // }

  // for (const auto& x : word_map){
  //   cout << x.first << ": " << x.second << "\n";
  // }


  file_csv.close();
  stop_words.close();
  return 0;

}

// Function that changes all characters to upper case (to avoid checking for it) and removes all symbols
void fileCleaner(string &str, map<string, int>& words) {

  //1. Looping through and changing each individual character to upper case.
  for (int x = 0; x < str.length(); x++) {
    str[x] = toupper(str[x]);
  }

  //2. Using regular expressions (C++11) to remove all symbols and non-letters.
  regex reg{"([A-Z]+)"}; //This regex will search for all upper case letters and omit all symbols.
  smatch match; // This will store the result of the regex.
  sregex_iterator currentMatch{ str.begin(), str.end(), reg }; //This iterator helps to find all instances of the regex, instead of just one.
  sregex_iterator lastMatch;
  while (currentMatch != lastMatch) {
    match = *currentMatch;
    ++words[match.str()];
    currentMatch++;
  }

}
