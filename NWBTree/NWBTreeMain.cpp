// File: NWBTree/SmartNWBTreeMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.

#include "Utilities.hpp" // promptIntBetween.
#include "NTree.hpp"
#include "NWBTreeToStreamVis.hpp"
#include "NWBTreeInsertVis.hpp"
#include "NWBTreeRemVis.hpp"
#include "NTreeIsEmptyVis.hpp"
#include "NWBTreeContainsVis.hpp"
#include "NWBTreeHeightVis.hpp"
#include "NWBTreeNumNodesVis.hpp"
#include "NWBTreeNumValuesVis.hpp"
#include "NWBTreeMinVis.hpp"
#include "NWBTreeMaxVis.hpp"

using namespace std;

int main() {
    char response;
    NTree<int> nwTree;
    int order = promptIntGE("Enter order of Nguyen-Wong B-tree: ", 2);
    int key, position, num;
    do {
        cout << "\n(c)lear      (i)nsert    (r)emove  i(s)Empty  co(n)tains  (h)eight"
             << "\nnum(V)alues  n(u)mNodes  (m)in     ma(x)      (w)rite     (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'C':
            // clear(nwTree);  // to do
            break;
        case 'I':
            cout << "Insert what integer key? ";
            cin >> key;
            insert(nwTree, order, key);
            break;
        case 'R':
            cout << "Remove what integer key? ";
            cin >> key;
            remove(nwTree, order, key);
            break;
        case 'S':
            if (isEmpty(nwTree)) {
                cout << "\nThe tree is empty." << endl;
            } else {
                cout << "\nThe tree is not empty." << endl;
            }
            break;
        case 'N':
            cout << "Search for what integer value? ";
            cin >> key;
            position = contains(key, nwTree);
            if (position == -1) {
                cout << "\nThe tree does not contain " << key << "." << endl;
            } else {
                cout << "\nThe tree contains " << key << " at position " << position << "." << endl;
            }
            break;
        case 'H':
            cout << "\nThe height of the tree is " << height(nwTree) << "." << endl;
            break;
        case 'V':
            num = numValues(nwTree);
            if (num == 0) {
                cout << "\nThere are no values in the tree." << endl;
            } else if (num == 1) {
                cout << "\nThere is 1 value in the tree." << endl;
            } else {
                cout << "\nThere are " << num << " values in the tree." << endl;
            }
            break;
        case 'U':
            num = numNodes(nwTree);
            if (num == 0) {
                cout << "\nThere are no nodes in the tree." << endl;
            } else if (num == 1) {
                cout << "\nThere is 1 node in the tree." << endl;
            } else {
                cout << "\nThere are " << num << " nodes in the tree." << endl;
            }
            break;
        case 'M':
            if (isEmpty(nwTree)) {
                cout << "\nThe tree is empty." << endl;
            } else {
                cout << "\nThe minimum value is " << min(nwTree) << "." << endl;
            }
            break;
        case 'X':
            if (isEmpty(nwTree)) {
                cout << "\nThe tree is empty." << endl;
            } else {
                cout << "\nThe maximum value is " << max(nwTree) << "." << endl;
            }
            break;
        case 'W':
            cout << endl;
            toNWStream(cout, nwTree);
            cout << endl;
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
    return EXIT_SUCCESS;
}
