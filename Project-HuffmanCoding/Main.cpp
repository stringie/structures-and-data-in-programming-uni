#include "iostream"
#include "vector"
#include "bintree.cpp"
using namespace std;

using tree = BinTree<pair<char, int>>;

vector<pair<char,int>> getCharFrequency(string s){
    vector<pair<char,int>> frequency;
    auto sit = s.begin();
    while (sit != s.end()){
        bool present = false;
        auto fit = frequency.begin();
        while (!present && fit != frequency.end()){
            if ((*fit).first == (*sit)){
                present = true;
                (*fit).second++;
            }

            fit++;
        }

        if (!present){
            auto p = make_pair((*sit), 1);
            frequency.push_back(p);
        }
        sit++;
    }

    return frequency;
}

int getSmallestTreeIndex(vector<tree> trees){
    int index = 0;
    auto it = trees.begin();

    int currentIndex = 0;
    int currentMin = INT32_MAX;
    while (it != trees.end()){
        int freq = (*it).root().second;
       
        if (freq <= currentMin){
            currentMin = freq;
            index = currentIndex;
        }

        currentIndex++;
        it++;
    }

    return index;
}

tree constructHuffmanTree(vector<tree> trees){
    while (trees.size() != 1)
    {
        // get smallest tree
        int indexF = getSmallestTreeIndex(trees);
        tree fMin = trees.at(indexF);

        // erase smallest tree
        auto it = trees.begin();
        advance(it, indexF);
        it = trees.erase(it);

        // get second smallest tree
        int indexS = getSmallestTreeIndex(trees);
        tree sMin = trees.at(indexS);

        // erase second smallest tree
        it = trees.begin();
        advance(it, indexS);
        it = trees.erase(it);

        // add counts for the new root
        int fCount = fMin.root().second;
        int sCount = sMin.root().second;
        int mergedTreeCount = fCount + sCount;

        // create new tree and push
        tree mergedTree(make_pair('*', mergedTreeCount), fMin, sMin);
        trees.push_back(mergedTree);   
    }

    tree huffman = trees.front();
    return huffman;
}

// vector <pair<char,string>> constructAlphabet(tree huffman){

// }

int main(){
    string test = "ABRACADABRA";
    vector<pair<char, int>> charFrequency = getCharFrequency(test);

    for (auto p : charFrequency){
        cout << "char: " << p.first << " count: " << p.second << endl;
    }

    vector<tree> trees;
    for (auto p : charFrequency){
        tree t(p);
        trees.push_back(t);
    }

    tree huffman = constructHuffmanTree(trees);
    huffman.printDOTPair();
    // vector<pair<char, string>> alphabet = constructAlphabet(huffman);
}