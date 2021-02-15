// Changed this back to only the libraries needed instead of <bits/stdc++>
// It turns out that actually includes all other known header files in compilation
// If the focus is efficiency, then it's better to only include the headers we need.
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <regex>

// This namespace allows us to forget about "std::"
using namespace std;

//Function Declarations
bool sortByValue(const pair<string, int>&, const pair<string, int>&);
void filterWords(map<string, int>&);
void fileCleaner(string& str, map<string, int>&);
void sortAndPrint(map<string, int>); // Called algorithm before

int main() {
    ifstream file_csv; // Our input file stream object for jobs.csv file
    map<string, int> word_map; // our map that will store the words
    string read_csv;           // string that will store jobs.csv strings line by line
    file_csv.open("jobs.csv");

    while (getline(file_csv, read_csv)) { fileCleaner(read_csv, word_map); }
    filterWords(word_map);
    sortAndPrint(word_map);

    return 0;
}

// sort values based on value
bool sortByValue(const pair<string, int>& firstValue, const pair<string, int>& secondValue) {
    return (firstValue.second > secondValue.second);
}

void filterWords(map<string, int>& word_map) {
    ifstream relWords;
    string read;
    // open filter
    relWords.open("blacklist.txt");
    while (getline(relWords, read)) {
        auto isFound = word_map.find(read);
        if (isFound != word_map.end()) word_map.erase(read);
    }
    relWords.close();
}


void fileCleaner(string& str, map<string, int>& words) {

    //1. Looping through and changing each individual character to upper case.
    for (int x{ 0 }; x < str.length(); x++) { str[x] = toupper(str[x]); }

    //2. Using regular expressions (C++11) to remove all symbols and non-letters.
    regex reg{ "([A-Z]+)" };                                     //This regex will search for all upper case letters and omit all symbols.
    smatch match;                                                // This will store the result of the regex.
    sregex_iterator currentMatch{ str.begin(), str.end(), reg }; //This iterator helps to find all instances of the regex, instead of just one.
    sregex_iterator lastMatch;
    while (currentMatch != lastMatch) {
        match = *currentMatch;
        // appendto.append(match.str() + ' ');
        ++words[match.str()];
        currentMatch++;
    }
}

void sortAndPrint(map<string, int> wordSort) {

    // vector pair map, alternative to multimap. Takes values and sorts them
    vector<pair<string, int>> vectorIndex;

    map<string, int>::iterator iterateWords;

    for (iterateWords = wordSort.begin(); iterateWords != wordSort.end(); iterateWords++) {
        vectorIndex.push_back(make_pair(iterateWords->first, iterateWords->second));
    }

    // sort sortAndPrint boolean func
    sort(vectorIndex.begin(), vectorIndex.end(), sortByValue);

    // output file
    ofstream outfile;

    // using ios_base::out write to file (will erase previous data, use ::app instead to preserve data)
    outfile.open("output_file.csv", ios_base::out);

    // output sorted file into csv file
    for (int i{ 0 }; i < vectorIndex.size(); i++) {
      if(vectorIndex[i].second <=3){
        continue;
      }
      else{
        outfile << vectorIndex[i].first << "," << vectorIndex[i].second << endl;
      }
    }




    outfile.close();
}
