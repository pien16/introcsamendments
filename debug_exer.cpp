/*
 * Created by   : Eduardo Lira
 * Date         : 12 August 2020
 * Description  : 
 *      This program find the number of matching words from  2 inputted sentences. The input must not have any puntuation.
 ---------------------------
 *	EXAMPLE: input1 = "This is a test", input2 = "This test is cool". 
 *		output """
 *		[CONSOLE] Common word found : this
		[CONSOLE] Common word found : is
		[CONSOLE] Common word found : test
		There are 3 words in common between the 2 inputted strings.
			"""
-----------------------------
 *      First the program will change both input string to lower case. 
 *      Then it will append a space character (this is needed to ensure we do not go out of bounds when making a vector of words)
 *      We then make a vector<string> where every entry is a word. This is done by looking for a ' ' character.
 *      We then remove any duplicate words from either string. (We simplified matching words to 1 per string.)
 *      We then look for the number of matching strings in the 2 vectors. It will print each occurence as it finds it.
 * 
 * Task         : 
 *      Your task, should you choose to accept it, is to debug this program. While debugging the program, be sure to use the hypothesis-testing techniques outlined in the zyBook.
 *      As a submission, we expect a short report showing your hypothesis testing and troubleshooting processes while finding all the bugs in this program. 
 *      
*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isSpace(char a) {return a == 32;} 

void appendSpace(string &str) {
    string space = " ";
    str = str + space;
}

//if it is a capital in the ASCII table, add 32 to char to get the lower case value.
void removeCapitals(string &str) {
    for (int i = 0; i < str.size(); i++) {
        if (str.at(i) > 64 && str.at(i) < 91) {
            str.at(i) = str.at(i) + 32;
        }
    }
}

//This will remove duplicate words.
void removeDuplicates(vector<string> &vec1) { 
    for (int i = 0; i < vec1.size(); i++) {
        for (int j = i + 1; j < vec1.size(); j++) {
            if (vec1.at(i) == vec1.at(j)) {
                vec1.erase(vec1.begin() + i);
                i = 0;
                //This simply removes the element at index i.
            }
        }
    }
}

vector <string> delimitString (string &sentence){
    vector<string> delimitedSentence;
    string word;
    bool pastSpace;
    for (int i = 0; i < sentence.size(); i++) {
        if (isSpace(sentence.at(i))) { 
            if(!pastSpace){
            delimitedSentence.push_back(word);
            word.erase();
            pastSpace = true;
            }
        } else{
            word.push_back(sentence.at(i));
            pastSpace = false;
        }
    }
    return delimitedSentence;
}

//will count the number of words the 2 strings have in common.
unsigned int wordsInCommon(const vector<string> &vec1, const vector<string> &vec2) {
    unsigned int matches = 0;
    for (int i = 0; i < vec1.size() ; i++) {
        for (int j = 0; j < vec2.size(); j++) {
            if ((vec1.at(i) == vec2.at(j))) {
                cout << "[CONSOLE] Common word found : " << vec1.at(i) << endl;
                matches++; 
                break;
            }
        }
    }
    return matches;
}


int main() {

    string firstSentence, secondSentence;
    cout << "Please type the first sentence. Do not use any punctuation.\n";
    getline(cin, firstSentence);
    cout << "Please type the second sentence. Do not use any punctuation.\n\a";
    getline(cin, secondSentence);

    //Remove capitalization of words
    removeCapitals(firstSentence);
    removeCapitals(secondSentence);

    //Append a space to ensure that delimeter gets last letter
    appendSpace(firstSentence);
    appendSpace(secondSentence);

    //Now we need to delimit the strings to a vector of strings, one word per vector entry.
    vector <string> entryOne, entryTwo;
    entryOne = delimitString(firstSentence);
    entryTwo = delimitString(secondSentence);

    //Remove duplicate words from the input strings.
    removeDuplicates(entryOne);
    removeDuplicates(entryTwo);

    //Now we can try to find the number of matches;
    unsigned int matches = wordsInCommon(entryOne, entryTwo);
    cout << "There are " << matches << " words in common between the 2 inputted strings." << endl;

    return 0;
}
