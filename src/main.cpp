#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <regex>

using namespace std;



// global variables
string appendto; // stream string buffer; use to append data after cleaning the file
vector<std::string> filter {}; // vector, dynamic array

// boolean func - checking if string is inside array
bool in_array(const std::string &value, const std::vector<std::string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

// sort values based on value
bool sortValue(const pair<string, int> &firstValue, const pair<string, int> &secondValue){
    return (firstValue.second > secondValue.second);
}

void filterWords(){
  ifstream relWords;
  string read;
  // open filter
  relWords.open("blacklist.txt");
  while(getline(relWords,read)){
    // iterate through file and append to dynamic array
    filter.push_back(read);
  }
}

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
    appendto.append(match.str() + ' ');
    ++words[match.str()];
    currentMatch++;
  }

}

void algorithm(map<string, int> wordSort){

  // vector pair map, alternative to multimap. Takes values and sorts them
	vector<pair<string, int>> vectorIndex;


	map<string, int> :: iterator iterateWords;

	for (iterateWords=wordSort.begin(); iterateWords!=wordSort.end(); iterateWords++)
	{
		vectorIndex.push_back(make_pair(iterateWords->first, iterateWords->second));
	}

  // sort algorithm boolean func
	sort(vectorIndex.begin(), vectorIndex.end(), sortValue);

	// output file
	ofstream outfile;

  // using ios_base::out write to file (will erase previous data, use ::app instead to preserve data)
	outfile.open("output_file.csv", ios_base::out);

  // output sorted file into csv file
	for (int i = 0; i < vectorIndex.size(); i++)
	{
		outfile << vectorIndex[i].first << "," << vectorIndex[i].second << endl;
	}

}

void frequency(string str)
{
    map<string, int> wordFrequency;

    string word = "";

    for (int i = 0; i < str.size(); i++) {
        // delim ' '
        if (str[i] == ' ') {
            if (wordFrequency.find(word) == wordFrequency.end()) {
              // checks if word is in filter, if so does not include
              if (in_array(word, filter)){
              }else{
                // if not in filter then make it a map pair
                wordFrequency.insert(make_pair(word, 1));
              }
                word = "";
            }
            else {
                // add to word
                wordFrequency[word]++;
                word = "";
            }
        }
        else{
          word += str[i];
        }
    }
    if (wordFrequency.find(word) == wordFrequency.end()){
        wordFrequency.insert(make_pair(word, 1));
    }
    else{
        wordFrequency[word]++;
    }
    for (auto& it : wordFrequency){}

    // previously defined alogirthm func in action
		algorithm(wordFrequency);


}

int main()
{
  // filtering out the words
  filterWords();
  ifstream file_csv;
  map<string, int> word_map; // map
  string read_csv; // read
  file_csv.open("jobs.csv");

  while(getline(file_csv,read_csv)){
    // information placed inside appendto string
      fileCleaner(read_csv, word_map);
    }
  // iterator; go through the data inside appendto string
  frequency(appendto);

    return 0;
}
