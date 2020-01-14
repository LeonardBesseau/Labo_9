/* ---------------------------
Laboratoire : 09
Fichier : main.cpp
Auteur(s) : Besseau Zwick Austburger
Date :  07.01.2020

But : Le but de ce laboratoire est d'établir les bases d'un correcteur orthographique.
Nous nous intéressons particulièrement à la lecture d'un fichier contenant la liste des mots du dictionnaire,
et à la recherche dans cette liste d'un mot donné ou d'un vector<string> de mots provenant d'un fichier.
Le progrmme affiche alors si le ou les mots ne sont pas présent dans le dictionnaire.

Remarque(s) :

Compilateur : g++ 7.4.0

--------------------------- */
#include <iostream>
#include "recherche.h"
#include "lecture.h"
#include "utils.h"

using namespace std;

/**
 * Order a list alphabetically (by inverting or ordering it if needed)
 * @param list a vector of string containing a list of word
 */
void formatListAlphabetically(vector<string> &list);


// Test dictionaries
const vector<string> NATO_WITH_MAJ{"Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India",
                                   "Juliet", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
                                   "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "Xray", "Yankee", "Zulu"};

const vector<string> NATO_WITHOUT_MAJ{"alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel", "india",
                                      "juliet", "kilo", "lima", "mike", "november", "oscar", "papa", "quebec", "romeo",
                                      "sierra", "tango", "uniform", "victor", "whiskey", "xray", "yankee", "zulu"};

const vector<string> OTAN{"Zulu", "Yankee", "Xray", "Whiskey", "Victor", "Uniform", "Tango", "Sierra", "Romeo",
                          "Quebec", "Papa", "Oscar", "November", "Mike", "Lima", "Kilo", "Juliet", "India", "Hotel",
                          "Golf", "Foxtrot", "Echo", "Delta", "Charlie", "Bravo", "Alpha"};

const vector<string> NATO_SHUFFLED{"kilo", "golf", "november", "charlie", "alpha", "sierra", "delta", "uniform",
                                   "yankee", "tango", "echo", "lima", "xray", "victor", "bravo", "romeo", "zulu",
                                   "hotel", "mike", "juliet", "quebec", "foxtrot", "india", "oscar", "papa",
                                   "whiskey"};

// Current directory
const string PWD = "C:\\Users\\gaeta\\Documents\\HEIGVD\\INF1\\Labo_9";


void formatListAlphabetically(std::vector<std::string> &list) {
    switch (checkIfSorted(list)) {
        case 1:
            inverseList(list);
            break;
        case 2:
            mergeSort(list);
            break;
        default:
            break;
    }
}

/**
 * Test function for reading a file from disk and creating of vector of string from its contents
 */
void testReadingFile() {
    vector<string> test = readFileByLine(PWD + "nato.txt");
    bool error = false;
    // Check if word read from file are the same as the test dictionary
    if (NATO_WITHOUT_MAJ.size() == test.size()) {
        for (size_t i = 0; i < NATO_WITH_MAJ.size(); ++i) {
            if (test.at(i) != NATO_WITH_MAJ.at(i)) {
                cout << "Error readingFile Test at index "
                     << i
                     << " element "
                     << test.at(i)
                     << " != "
                     << NATO_WITH_MAJ.at(i)
                     << endl;
                error = true;
            }
        }
    } else {
        error = true;
    }
    cout << (!error ? "Reading from file OK " : "Error Reading from file") << endl;
}

/**
 * Test function for inverting the order of the element in a vector of string
 */
void testInversion() {
    vector<string> v1 = NATO_WITH_MAJ;
    vector<string> v2 = OTAN;

    inverseList(v1);
    inverseList(v2);

    bool error = false;

    for (size_t i = 0; i < NATO_WITH_MAJ.size(); ++i) {
        if (v1.at(i) != OTAN.at(i)) {
            cout << "Error Inversion Test at index " << i << " element " << v1.at(i) << " != " << OTAN.at(i) << endl;
            error = true;
        }
        if (v2.at(i) != NATO_WITH_MAJ.at(i)) {
            cout << "Error Inversion Test at index " << i << " element " << v2.at(i) << " != " << NATO_WITH_MAJ.at(i)
                 << endl;
            error = true;
        }
    }
    cout << (!error ? "Inversion OK " : "Error") << endl;
}

/**
 * Test function for sorting a vector of string using bubbleSort and mergeSort
 */
void testSort() {
    vector<string> test = NATO_SHUFFLED;

    bubbleSort(test);

    bool error = false;
    for (size_t i = 0; i < NATO_WITHOUT_MAJ.size(); ++i) {
        if (test.at(i) != NATO_WITHOUT_MAJ.at(i)) {
            cout << "Error BubbleSort Test at index " << i << " element " << test.at(i) << " != " << NATO_WITH_MAJ.at(i)
                 << endl;
            error = true;
        }
    }
    cout << (!error ? "BubbleSort OK " : "Error") << endl;

    test = NATO_SHUFFLED;
    mergeSort(test);

    error = false;
    for (size_t i = 0; i < NATO_WITHOUT_MAJ.size(); ++i) {
        if (test.at(i) != NATO_WITHOUT_MAJ.at(i)) {
            cout << "Error MergeSort Test at index " << i << " element " << test.at(i) << " != " << NATO_WITH_MAJ.at(i)
                 << endl;
            error = true;
        }
    }
    cout << (!error ? "MergeSort OK " : "Error") << endl;
}

/**
 * Test function for finding a string in a vector of string linearly (with and without iterators)
 */
void testLinear() {
    const vector<string> wordTest{"alpha", "al", "a", "alpa", "kilo", "rover", "zuluR"};
    const size_t NOT_FOUND = size_t(-1);
    const vector<size_t> WORD_TEST_INDEX_ORDERED{0, NOT_FOUND, NOT_FOUND, NOT_FOUND, 10, NOT_FOUND, NOT_FOUND};
    const vector<size_t> WORD_TEST_INDEX_UNORDERED{4, NOT_FOUND, NOT_FOUND, NOT_FOUND, 0, NOT_FOUND, NOT_FOUND};

    bool error = false;

    for (size_t i = 0; i < wordTest.size(); ++i) {
        if (rechercheLineaire(NATO_SHUFFLED, wordTest.at(i)) != WORD_TEST_INDEX_UNORDERED.at(i)) {
            cout << "Error linear unordered Test at index " << i << endl;
            error = true;
        }
        if (rechercheLineaire(NATO_WITHOUT_MAJ, wordTest.at(i)) != WORD_TEST_INDEX_ORDERED.at(i)) {
            cout << "Error linear ordered Test at index " << i << endl;
            error = true;
        }
    }
    bool test = NATO_SHUFFLED.begin() + 4 == rechercheLineaire(NATO_SHUFFLED.cbegin(), NATO_SHUFFLED.cend(), "alpha");
    bool test1 = NATO_SHUFFLED.end() == rechercheLineaire(NATO_SHUFFLED.begin(), NATO_SHUFFLED.end(), "al");
    if (!test || !test1) {
        cout << "Error linear unordered Test" << endl;
    }

    cout << (!error ? "LinearSort OK " : "Error") << endl;
}

/**
 * Test function for finding a string in a vector of string using binary search (iteratively and recursively)
 */
void testDichotomique() {
    const vector<string> wordTest{"alpha", "al", "a", "alpa", "kilo", "rover", "zuluR"};
    const size_t NOT_FOUND = size_t(-1);
    const vector<size_t> WORD_TEST_INDEX_ORDERED{0, NOT_FOUND, NOT_FOUND, NOT_FOUND, 10, NOT_FOUND, NOT_FOUND};
    const vector<bool> WORD_TEST_RECURSIVE{true, false, false, false, true, false, false};


    bool error = false;

    for (size_t i = 0; i < wordTest.size(); ++i) {

        if (rechercheDichotomique(NATO_WITHOUT_MAJ, wordTest.at(i)) != WORD_TEST_INDEX_ORDERED.at(i)) {
            cout << "Error dichotomique Test at index " << i << endl;
            error = true;
        }
        if (rechercheDichotomiqueRecursive(NATO_WITHOUT_MAJ, wordTest.at(i)) != WORD_TEST_RECURSIVE.at(i)) {
            cout << "Error dichotomique recursive Test at index " << i << endl;
            error = true;
        }
    }
    bool validIteratorSearch = NATO_WITHOUT_MAJ.begin() ==
                               rechercheDichotomique(NATO_WITHOUT_MAJ.cbegin(), NATO_WITHOUT_MAJ.cend(), "alpha");
    bool validIteratorSearchB = NATO_WITHOUT_MAJ.begin() + 4 ==
                                rechercheDichotomique(NATO_WITHOUT_MAJ.cbegin(), NATO_WITHOUT_MAJ.cend(), "echo");
    bool invalidIteratorSearchLower = NATO_WITHOUT_MAJ.end() ==
                                      rechercheDichotomique(NATO_WITHOUT_MAJ.begin(), NATO_WITHOUT_MAJ.end(), "al");
    bool invalidIteratorSearchUpper = NATO_WITHOUT_MAJ.end() ==
                                      rechercheDichotomique(NATO_WITHOUT_MAJ.begin(), NATO_WITHOUT_MAJ.end(), "zulur");
    bool test2 = rechercheDichotomiqueRecursive(NATO_WITHOUT_MAJ.cbegin(), NATO_WITHOUT_MAJ.cend(), "alpha");
    bool test3 = !rechercheDichotomiqueRecursive(NATO_WITHOUT_MAJ.begin(), NATO_WITHOUT_MAJ.end(), "al");
    bool test4 = !rechercheDichotomiqueRecursive(NATO_WITHOUT_MAJ.begin(), NATO_WITHOUT_MAJ.end(), "zuluR");
    bool test5 = !rechercheDichotomiqueRecursive(NATO_WITHOUT_MAJ.begin(), NATO_WITHOUT_MAJ.end(), "zula");
    bool test6 = !rechercheDichotomiqueRecursive(NATO_WITHOUT_MAJ.begin(), NATO_WITHOUT_MAJ.end(), "");
    if (!validIteratorSearch || !invalidIteratorSearchLower || !invalidIteratorSearchUpper || !validIteratorSearchB) {
        cout << "Error dichotomique Test" << endl;
    }
    if (!test2 || !test3 || !test4 || !test5 || !test6) {
        cout << "Error dichotomique recursive Test" << endl;
    }

    cout << (!error ? "dichotomique OK " : "Error") << endl;
}

/**
 * Find if a word is present in a file
 * @param path a string containing the path to the file
 * @param word a string containing the word to find
 * @return true if the word is present, false otherwise
 */
bool findWord(const string &path, const string &word) {
    vector<string> dictionary = readFileByLine(path);
    formatListAlphabetically(dictionary);
    cout << "dictionnary size " << dictionary.size() << endl;
    return rechercheDichotomique(dictionary, word) != size_t(-1);
}

int main() {
    string test1 = "\"You will excuse this mask,\" continued our strange visitor. \"The ";
    string test = normaliseString(test1);
    vector<string> testVect;
    testVect.push_back(test);
    cout << testVect.at(0);
    vector<vector<string>> blabla = readWordByLine(testVect);
    cout << "[";
    for (auto bla : blabla) {
        for (auto bl : bla) {
            cout << bl << "|";
        }
    }
    cout << "]";
    string a;
/*
    const string PATH = PWD + "dictionary.txt";
    const string WORD = "knapsacked";
    cout << "word " << (findWord(PATH, WORD) ? "found" : "not found") << endl;
    */
    return 0;
}
