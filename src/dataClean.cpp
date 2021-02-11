// libraries
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <regex>
using namespace std;

void fileCleaner(string& str, map<string, int>&);

int main() {

    map<string, int> word_map;
    map<string, int> cleaned_words_map;
    string read_csv, read_stopwords; // string var for reading csv file and reading stopwords file
    ofstream cleaned_words;          // creates write object for cleaned words file
    ifstream file_csv, stop_words;   // creates read object for csv file and stopwords file

    // Opening all the necessary files
    file_csv.open("jobs.csv");
    stop_words.open("stopwords_en_minus_c_r.txt");
    cleaned_words.open("cleaned_words.csv");

    // Reading the jobs.csv file line-by-line and calling a function that removes all garbage symbols and numbers.
    // This fileCleaner function stores the filtered/cleaned words into word_map, the map of words.
    while (getline(file_csv, read_csv)) fileCleaner(read_csv, word_map);

    // Creating a duplicate of the original map of words.
    cleaned_words_map.insert(word_map.begin(), word_map.end());

    // Gathering the unnecessary stop words to filter them out
    while (getline(stop_words, read_stopwords)) {
        // Changing all characters to upper case
        for (int i = 0; i < read_stopwords.length(); i++) {
            read_stopwords[i] = toupper(read_stopwords[i]);
        }

        // Removing the stop words from the duplicate of our word_map (cleaned_words_map),
        // if it exists in our original word_map.
        auto isFound = word_map.find(read_stopwords);
        if (isFound != word_map.end()) {
            cleaned_words_map.erase(read_stopwords); // The stop word is removed here with the erase method.
        }
    }

    // Printing out the fully filtered/cleaned words to a new csv file in csv format (Seperating by ','(commas)).
    for (const auto x : cleaned_words_map) {
        cleaned_words << x.first << "," << x.second << endl;
    }

    //These can be removed later. There here just to confirm that stop words have been removed.
    //If the stop words were succesfully removed, then the map of cleaned words should have a smaller size.
    cout << cleaned_words_map.size() << endl;
    cout << word_map.size() << endl;

    // Closing all the files that were used in this program
    file_csv.close();
    stop_words.close();
    cleaned_words.close();
    return 0;
}

// Function that changes all characters to upper case (to avoid checking for it) and removes all symbols
void fileCleaner(string& str, map<string, int>& words) {

    //1. Looping through and changing each individual character to upper case.
    for (int x = 0; x < str.length(); x++) {
        str[x] = toupper(str[x]);
    }

    //2. Using regular expressions (C++11) to remove all symbols and non-letters.
    regex reg{ "([A-Z]+)" };                                     //This regex will search for all upper case letters and omit all symbols.
    smatch match;                                                // This will store the result of the regex.
    sregex_iterator currentMatch{ str.begin(), str.end(), reg }; //This iterator helps to find all instances of the regex, instead of just one.
    sregex_iterator lastMatch;
    while (currentMatch != lastMatch) {
        match = *currentMatch;
        ++words[match.str()];
        currentMatch++;
    }
}