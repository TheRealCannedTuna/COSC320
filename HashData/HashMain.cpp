// File: Hash/HashMain.cpp

#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE.
#include "HashData.hpp" // insert, contains.
#include "HashFunctions.hpp" // CAMetricsStr
#include "Utilities.hpp" // promptIntGE, promptFileOpen.

int main() {
    ifstream inFile;
    CAMetricsStr key;
    int value;
    HashFunction hashFunction;
    int tableSize, numLoaded;
    int numFound, compFound;
    int numMissing, compMissing;
    string functionName, response;
    cout << "Hash function type--Knuth or Bernstein (k or b): ";
    cin >> response;
    if ((response[0] == 'k') || (response[0] == 'K')) {
        hashFunction = knuthHash;
        functionName = "Knuth";
    }
    else if ((response[0] == 'b') || (response[0] == 'B')) {
        hashFunction = bernsteinHash;
        functionName = "Bernstein";
    }
    else {
        cerr << "Illegal hash type.";
        return EXIT_FAILURE;
    }
    tableSize = promptIntGE("Size of hash table ", 1);
    HashTable hashTable(tableSize, hashFunction);
    numLoaded = promptIntGE("Number of keys to load ", 1);
    cout << "Load from what file--";
    promptFileOpen(inFile);
    if (!inFile) {
        return EXIT_FAILURE;
    }
    cout << "\nDisplay loaded keys? (y or n): ";
    cin >> response;
    for (int i = 1; i <= numLoaded; i++) {
        inFile >> key >> value;
        if (!inFile) {
            cerr << "Error reading hash load file." << endl;
            return EXIT_FAILURE;
        }
        hashTable.insert(key);
        if ((response [0] == 'y') || (response [0] == 'Y')) {
            cout.width(18);
            cout.setf(ios::left, ios::adjustfield);
            cout << key;
            if (i % 6 == 0) {
                cout << endl;
            }
        }
    }
    cout << "\nDump hash table? (y or n): ";
    cin >> response;
    if ((response [0] == 'y') || (response [0] == 'Y')) {
        cout << endl;
        cout << hashTable;
    }
    inFile.seekg(0, ios::beg);
    cout << "\nDisplay tested keys? (y or n): ";
    cin >> response;
    numFound = compFound = numMissing = compMissing = 0;
    inFile.seekg(0, ios::beg);
    for (int i = 0; i < 2 * numLoaded; i++) {
        inFile >> key >> value;
        if (!inFile) {
            cerr << "Error reading hash file." << endl;
            return EXIT_FAILURE;
        }
        CAMetricsStr::clearCompareCount();
        if (hashTable.contains(key)) {
            numFound ++;
            compFound += CAMetricsStr::getCompareCount();
            if ((response [0] == 'y') || (response [0] == 'Y')) {
                cout << "Found:     " << key << endl;
            }
        }
        else {
            numMissing ++;
            compMissing += CAMetricsStr::getCompareCount();
            if ((response [0] == 'y') || (response [0] == 'Y')) {
                cout << "Not found: " << key << endl;
            }
        }
    }
    inFile.close();
    cout << endl;
    cout << "Hash type: " << functionName << endl;
    cout << "Hash table size: " << tableSize << endl;
    cout << "Number loaded: " << numLoaded << endl;
    cout << "Number tested: " << 2 * numLoaded << endl;
    cout << "Number found: " << numFound << endl;
    cout << "Number of found comparisons: " << compFound << endl;
    cout << "Found comparisons per query: " << compFound <<"/" << numLoaded << " == " << (compFound * 1.0)/(numLoaded * 1.0) << endl;
    cout << "Number missing: " << numMissing << endl;
    cout << "Number of missing comparisons: " << compMissing << endl;
    cout << "Missing comparisons per query: " << compMissing <<"/" << numLoaded << " == " << (compMissing * 1.0)/(numLoaded * 1.0) << endl;
    cout << "Load factor alpha: " << numLoaded << "/" << tableSize << " == " << (numLoaded * 1.0)/(tableSize) << endl;
    return EXIT_SUCCESS;
}
