// File: DictionaryHash/HashMain.cpp

#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE.

#include "DictionaryHash.hpp"
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
    string functionName;
    char response;
    cout << "Hash function type--Knuth or Bernstein (k or b): ";
    cin >> response;
    if (toupper(response) == 'K') {
        hashFunction = knuthHash;
        functionName = "Knuth";
    } else if (toupper(response) == 'B') {
        hashFunction = bernsteinHash;
        functionName = "Bernstein";
    } else {
        cerr << "Illegal hash type.";
        return EXIT_FAILURE;
    }
    tableSize = promptIntGE("Size of hash table ", 1);
    DictionaryHash<CAMetricsStr, int> hashDict(tableSize, hashFunction);
    cout << "Interactive or file input (i or f): ";
    cin >> response;
    if (toupper(response) == 'I') {
        do {
            cout << "\n(c)lear  (i)nsert  (r)emove  co(n)tains  (w)rite  (q)uit: ";
            cin >> response;
            switch (toupper(response)) {
            case 'C':
                hashDict.clear();
                break;
            case 'I':
                cout << "Insert what string key? ";
                cin >> key;
                cout << "Insert what integer value? ";
                cin >> value;
                hashDict.insert(key, value);
                break;
            case 'R':
                cout << "Remove what integer key? ";
                cin >> key;
                if (hashDict.remove(key, value)) {
                    cout << "\nKey " << key << " removed with a value of " << value << "." << endl;
                } else {
                    cout << "\nKey " << key << " is not in the dictionary." << endl;
                }
                break;
            case 'N':
                cout << "Search for what integer key? ";
                cin >> key;
                if (hashDict.contains(key, value)) {
                    cout << "\nThe value for key " << key << " is " << value << "." << endl;
                } else {
                    cout << "\nKey " << key << " is not in the dictionary." << endl;
                }
                break;
            case 'W':
                cout << endl << hashDict << endl;
                break;
            case 'Q':
                break;
            default:
                cout << "\nIllegal command." << endl;
                break;
            }
        } while (toupper(response) != 'Q');
    } else if (toupper(response) == 'F') {
        numLoaded = promptIntGE("Number of keys to load ", 1);
        cout << "Load from what file--";
        promptFileOpen(inFile);
        if (!inFile) {
            return EXIT_FAILURE;
        }
        cout << "\nDisplay loaded keys? (y or n): ";
        cin >> response;
        cout << endl;
        for (int i = 1; i <= numLoaded; i++) {
            inFile >> key >> value;
            if (!inFile) {
                cerr << "Error reading hash load file." << endl;
                return EXIT_FAILURE;
            }
            hashDict.insert(key, value);
            if (toupper(response) == 'Y') {
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
        cout << endl;
        if (toupper(response) == 'Y') {
            cout << endl;
            cout << hashDict;
        }
        inFile.seekg(0, ios::beg);
        cout << "\nDisplay tested keys? (y or n): ";
        cin >> response;
        cout << endl;
        numFound = compFound = numMissing = compMissing = 0;
        inFile.seekg(0, ios::beg);
        for (int i = 0; i < 2 * numLoaded; i++) {
            inFile >> key >> value;
            if (!inFile) {
                cerr << "Error reading hash file." << endl;
                return EXIT_FAILURE;
            }
            CAMetricsStr::clearCompareCount();
            if (hashDict.contains(key, value)) {
                numFound++;
                compFound += CAMetricsStr::getCompareCount();
                if (toupper(response) == 'Y') {
                    cout << "Found:     <" << key << ", " << value << ">" << endl;
                }
            } else {
                numMissing++;
                compMissing += CAMetricsStr::getCompareCount();
                if (toupper(response) == 'Y') {
                    cout << "Not found: " << key << endl;
                }
            }
        }
        inFile.close();
        cout << endl;
        cout << "Hash type: " << functionName << endl;
        cout << "Hash table size: " << tableSize << endl;
        cout << "Number loaded: " << numLoaded << endl;
        cout << "Load factor alpha: " << numLoaded << "/" << tableSize << " == " << (numLoaded * 1.0) / (tableSize) << endl;
        cout << "Number tested: " << 2 * numLoaded << endl;
        cout << "Number found: " << numFound << endl;
        cout << "Number of found comparisons: " << compFound << endl;
        cout << "Found comparisons per query: " << (compFound * 1.0) / (numLoaded * 1.0) << endl;
        cout << "Number missing: " << numMissing << endl;
        cout << "Number of missing comparisons: " << compMissing << endl;
        cout << "Missing comparisons per query: " << (compMissing * 1.0) / (numLoaded * 1.0) << endl;
    } else {
        cerr << "Illegal response: " << response << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
