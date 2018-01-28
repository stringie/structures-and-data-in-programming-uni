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
    string decompressBits(string s);
    string decompressBytes(string s);
    void getTextFromFile(string path);
    string findPathToLeaf(char leaf, BinTreePosition<pair<char, int>> pos, string path);
    int getSmallestTreeIndex(vector<tree> trees);
    vector<pair<char, string>> constructAlphabet();
    void convertOutputToByteFormat();
};

HTree::HTree() {}

// контруктор приемащ път към информацията за компресиране
HTree::HTree(string path) : pathToFile(path) {
    this->getTextFromFile(path);
    this->getCharFrequency();
    this->constructHuffmanTree();
    this->compress();
}

HTree::~HTree() {}

// запазва дървото в in-order формат
void HTree::save(string path) {
    ofstream file(path);
    BinTreePosition<pair<char, int>> pos(this->huffman);
    this->saveHuffmanTree(pos, file);
}

// зарежда дърво от in-order формат
void HTree::load(string path) {
    this->getTextFromFile(path);
    const char* file = this->inputFile.c_str();
    this->huffman = this->getHuffmanTreeFromFile(file);
    this->compress();
}

// връща оригиналния низ
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
    // броя на нулите за формата на последното число
    int zerosExtraInfo = 0;
    for (int i = 0; i < compressedFile.size(); i++) {
        byte.push_back(compressedFile.at(i));
        bitCounter++;
        if (bitCounter == 8 || i == compressedFile.size()-1){
            bitCounter = 0;
            auto sit = byte.begin();
            zerosExtraInfo = 0;
            while (*sit == '0'){
                zerosExtraInfo++;
                sit++;
            }
            compressedFileInByteFormat.append(to_string(bitset<8>(byte).to_ulong()) + " ");
            byte = "";
        }
    }

    // Този форма изисква допълнителна информация за боря нули които са отрязани
    // при конвертиване на последния 8-битов израз към десетично число.
    // Записва се по формат 'zN' където N е броя на нулите
    compressedFileInByteFormat.append("z" + to_string(zerosExtraInfo));
}

void HTree::getTextFromFile(string path){
    string text;
    ifstream file(path);
    
    char c;
    while (c = file.get()){
        if (file.eof()){
            file.close();
            break;
        }
        text.push_back(c);
    }

    this->inputFile = text;
}

// конструира честотната таблица
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
    // създават се първоначалните дървета
    vector<tree> trees;
    for (auto p : this->frequencies){
        tree t(p);
        trees.push_back(t);
    }
    
    // цикъл който редуцира броя на дърветата до едно хъфманово дърво
    while (trees.size() != 1)
    {
        // взима се най малкото
        int indexF = this->getSmallestTreeIndex(trees);
        tree fMin = trees.at(indexF);

        // изтрива се най малкото
        auto it = trees.begin();
        advance(it, indexF);
        it = trees.erase(it);

        // взима се второто най малко
        int indexS = this->getSmallestTreeIndex(trees);
        tree sMin = trees.at(indexS);

        // изтрива се второто най малко
        it = trees.begin();
        advance(it, indexS);
        it = trees.erase(it);

        // изчислява се корена на новото дърво
        int fCount = fMin.root().second;
        int sCount = sMin.root().second;
        int mergedTreeCount = fCount + sCount;

        // създава се едно цяло дърво от двете най малки
        tree mergedTree(make_pair('*', mergedTreeCount), fMin, sMin);
        trees.push_back(mergedTree);   
    }

    tree huff = trees.front();
    this->huffman = huff;
}

// обхожда се дървото за да се намери пътя до листото в 0 или 1
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
        if (pathCode.empty())
            pathCode = "0";
        alphabet.push_back(make_pair(leaf.first, pathCode));
    }

    return alphabet;
}

void HTree::compress(){
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

// превръща примерно 01110110 към изречение чрез дървото
string HTree::decompressBits(string s){
    string str;
    auto sit = s.begin();
    while (sit != s.end())
    {
        BinTreePosition<pair<char, int>> pos(this->huffman);
        if (pos.get().first != '*')
            sit++;
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

// превърща примерно 23 104 към битове и ги подава на decompressBits
string HTree::decompressBytes(string s){
    string bits = "";
    auto sit = s.begin();
    while(sit != s.end()){
        int number = 0;
        while (*sit != ' '){
            number *= 10;
            number += *sit - '0';
            sit++;
        }

        sit++;
        if((*sit) == 'z'){
            int zerosFix = (*(++sit)) - '0';
            while (zerosFix != 0){
                bits.push_back('0');
                zerosFix--;
            }
            sit++;
        }

        string n = bitset<8>(number).to_string();
        if (sit == s.end()){
            auto it = n.begin();
            while(*it != '1' && it != n.end()){
                it = n.erase(it);
            }
        }
        bits.append(n);
    }

    return this->decompressBits(bits);
}

// публична функция която избира подходящия формат за възстановяване на информация
string HTree::decompress(string s){
    if(s.find(' ') == string::npos)
        return this->decompressBits(s);

    return decompressBytes(s);
}

// запазване на дървото
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
    treeText++; // пропуска отварящата скоба
    if ((*treeText) == ')'){
        treeText++;
        tree nullTree;
        return nullTree;
    }
    tree left = this->getHuffmanTreeFromFile(treeText);
    treeText++; // пропуска квадратна скоба
    char root = *treeText; // взима корена
    treeText++; // пропуска корена
    treeText++; // пропуска запетая
    int count = 0; // взима броя
    char c = *treeText;
    while (c >= '0' && c <= '9'){
        count *= 10;
        count += c - '0';
        treeText++;
        c = *treeText;
    }
    treeText++; // пропуска затваряща квадратна скоба
    tree right = this->getHuffmanTreeFromFile(treeText);
    treeText++; // пропуска затваряща скоба

    tree huffman(make_pair(root, count), left, right);
    return huffman;
}