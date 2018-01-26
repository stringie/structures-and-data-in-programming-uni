#include "bintree.cpp"
#include "vector"
#include "fstream"
#include "bitset"
using namespace std;

using tree = BinTree<pair<char, int>>;

class HTree{

private:
    tree huffman;
    string pathToTreeSave;
    string pathToFile;
    string inputFile;
    string compressedFile;
    string compressedFileInByteFormat;
    vector<pair<char, int>> frequencies;

public:
    HTree();
    HTree(string path);
    void save(string path);
    void load(string path);
    string getText();
    string getCompressedText();
    string getCompressedTextInByteFormat();
    string decompress(string s);
    ~HTree();

private:
    void getCharFrequency();
    void constructHuffmanTree();
    void compress();
    void saveHuffmanTree(BinTreePosition<pair<char, int>> pos, ofstream& ofs);
    tree getHuffmanTreeFromFile(const char*& treeText);
    string getTextFromFile(string path);
    string findPathToLeaf(char leaf, BinTreePosition<pair<char, int>> pos, string path);
    int getSmallestTreeIndex(vector<tree> trees);
    vector<pair<char, string>> constructAlphabet();
    void convertOutputToByteFormat();
};

HTree::HTree() {}

// constructor that take path to file for compression, constructs tree and compresses
HTree::HTree(string path) : pathToFile(path) {
    this->inputFile = this->getTextFromFile(path);
    this->getCharFrequency();
    this->constructHuffmanTree();
    this->compress();
}

HTree::~HTree() {}

// saves huffman tree to file in in-order format
void HTree::save(string path) {
    ofstream file(path);
    BinTreePosition<pair<char, int>> pos(this->huffman);
    this->saveHuffmanTree(pos, file);
}

// loads in-order format huffman tree from file
void HTree::load(string path) {
    const char * file = this->getTextFromFile(path).c_str();
    this->huffman = this->getHuffmanTreeFromFile(file);
    this->compress();
}

// returns original uncompressed file
string HTree::getText() {
    return inputFile;
}

string HTree::getCompressedText() {
    return compressedFile;
}

string HTree::getCompressedTextInByteFormat(){
    this->convertOutputToByteFormat();
    return compressedFileInByteFormat;
}

void HTree::convertOutputToByteFormat(){
    int bitCounter = 0;
    string byte = "";
    for (int i = 0; i < compressedFile.size(); i++) {
        if (bitCounter == 8 || i == compressedFile.size() - 1){
            bitCounter = 0;
            compressedFileInByteFormat.append(to_string(bitset<8>(byte).to_ulong()) + " ");
            byte = "";
        }
        byte.push_back(compressedFile.at(i));
        bitCounter++;
    }
}

string HTree::getTextFromFile(string path){
    string text;
    ifstream file(path);
    
    char c;
    while (c = file.get()){
        if (file.eof())
            break;
        text.push_back(c);
    }

    file.close();
    return text;
}

// constructs the frequency table
void HTree::getCharFrequency(){
    vector<pair<char,int>> frequency;
    auto sit = this->inputFile.begin();
    while (sit != this->inputFile.end()){
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

    this->frequencies = frequency;
}

int HTree::getSmallestTreeIndex(vector<tree> trees){
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

void HTree::constructHuffmanTree(){
    //create initial huffman tree(s)
    vector<tree> trees;
    for (auto p : this->frequencies){
        tree t(p);
        trees.push_back(t);
    }
    
    // reduce to single tree
    while (trees.size() != 1)
    {
        // get smallest tree
        int indexF = this->getSmallestTreeIndex(trees);
        tree fMin = trees.at(indexF);

        // erase smallest tree
        auto it = trees.begin();
        advance(it, indexF);
        it = trees.erase(it);

        // get second smallest tree
        int indexS = this->getSmallestTreeIndex(trees);
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

    tree huff = trees.front();
    this->huffman = huff;
}

string HTree::findPathToLeaf(char leaf, BinTreePosition<pair<char, int>> pos, string path){
    if (pos.valid() && pos.get().first == leaf){
        return path;
    }else if (pos.valid() && pos.get().first == '*'){
        path.push_back('0');
        string left = findPathToLeaf(leaf, pos.left(), path);
        path.pop_back();
        path.push_back('1');
        string right = findPathToLeaf(leaf, pos.right(), path);

        return left + right;
    } else if (pos.valid()){
        return "";
    }
}

vector<pair<char, string>> HTree::constructAlphabet(){
    vector<pair<char, string>> alphabet;
    for (auto leaf : this->frequencies){
        BinTreePosition<pair<char, int>> pos(this->huffman);
        string pathCode = this->findPathToLeaf(leaf.first, pos, "");
        alphabet.push_back(make_pair(leaf.first, pathCode));
    }

    return alphabet;
}

void HTree::compress(){
    string leafs;
    for (auto p : this->frequencies){
        char c = p.first;
        leafs.push_back(c);
    }

    vector<pair<char, string>> alphabet = this->constructAlphabet();

    string compressed;
    for (auto c : this->inputFile){
        for (auto p : alphabet){
            if (c == p.first){
                compressed.append(p.second);
                break;
            }
        }
    }

    this->compressedFile = compressed;
}

string HTree::decompress(string s){
    string str;
    auto sit = s.begin();
    while (sit != s.end())
    {
        BinTreePosition<pair<char, int>> pos(this->huffman);
        while (pos.get().first == '*'){
            char bit = (*sit);
            if (bit == '0'){
                pos = pos.left();
            } else {
                pos = pos.right();
            }
            sit++;
        }

        str.push_back(pos.get().first);
    }

    return str;
}

//save a tree into a file with in-order traversal
void HTree::saveHuffmanTree(BinTreePosition<pair<char,int>> pos, ofstream& os){
    if (!pos.valid()){
        os << "()";
    }else{
        os << '(';
        saveHuffmanTree(pos.left(), os);
        os << '[' << (*pos).first << ',' << (*pos).second << ']';
        saveHuffmanTree(pos.right(), os);
        os << ')';
    }
}

tree HTree::getHuffmanTreeFromFile(const char*& treeText){
    treeText++; // skip opening bracket
    if ((*treeText) == ')'){
        treeText++;
        tree nullTree;
        return nullTree;
    }
    tree left = this->getHuffmanTreeFromFile(treeText);
    treeText++; // skip opening square bracket
    char root = *treeText; // get node char
    treeText++; // skip node char
    treeText++; // skip comma
    int count = 0; // retrieve node char count
    char c = *treeText;
    while (c >= '0' && c <= '9'){
        count *= 10;
        count += c - '0';
        treeText++;
        c = *treeText;
    }
    treeText++; // skip closing square bracket
    tree right = this->getHuffmanTreeFromFile(treeText);
    treeText++;

    tree huffman(make_pair(root, count), left, right);
    return huffman;
}