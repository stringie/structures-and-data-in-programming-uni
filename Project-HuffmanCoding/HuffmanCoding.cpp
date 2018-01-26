#include "fstream"
#include "iostream"
#include "vector"
#include "bintree.cpp"
using namespace std;

using tree = BinTree<pair<char, int>>;

string getTextFromFile(string path){
    string text;
    ifstream file(path);
    
    char c;
    while (c = file.get()){
        if (file.eof())
            break;
        text.push_back(c);
    }

    return text;
}

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

tree constructHuffmanTree(vector<pair<char, int>> frequencies){
    //create initial huffman tree(s)
    vector<tree> trees;
    for (auto p : frequencies){
        tree t(p);
        trees.push_back(t);
    }
    
    // reduce to single tree
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

string findPathToLeaf(char leaf, BinTreePosition<pair<char, int>> pos, string path){
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

vector <pair<char,string>> constructAlphabet(tree huffman, string leafs){
    vector<pair<char, string>> alphabet;
    for (auto leaf : leafs){
        BinTreePosition<pair<char, int>> pos(huffman);
        string pathCode = findPathToLeaf(leaf, pos, "");
        alphabet.push_back(make_pair(leaf, pathCode));
    }

    return alphabet;
}

string compress(tree huffman, string text, vector<pair<char, int>> frequencies){
    string leafs;
    for (auto p : frequencies){
        char c = p.first;
        leafs.push_back(c);
    }

    vector<pair<char, string>> alphabet = constructAlphabet(huffman, leafs);

    string compressed;
    for (auto c : text){
        for (auto p : alphabet){
            if (c == p.first){
                compressed.append(p.second);
                break;
            }
        }
    }

    return compressed;
}

string decompress(string s, tree huffman){
    string str;
    auto sit = s.begin();
    while (sit != s.end())
    {
        BinTreePosition<pair<char, int>> pos(huffman);
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
void saveHuffmanTree(BinTreePosition<pair<char,int>> pos, ofstream& os){
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

tree getHuffmanTreeFromFile(const char*& treeText){
    treeText++; // skip opening bracket
    if ((*treeText) == ')'){
        treeText++;
        tree nullTree;
        return nullTree;
    }
    tree left = getHuffmanTreeFromFile(treeText);
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
    tree right = getHuffmanTreeFromFile(treeText);
    treeText++;

    tree huffman(make_pair(root, count), left, right);
    return huffman;
}


int main(){
    string text = getTextFromFile("input.txt");
    vector<pair<char, int>> frequencies = getCharFrequency(text);
    tree huffman = constructHuffmanTree(frequencies);
    ofstream file("tree.txt");
    BinTreePosition<pair<char, int>> pos(huffman);
    saveHuffmanTree(pos, file);
    file.close();
    string txt = getTextFromFile("tree.txt");
    const char* treeText = txt.c_str();
    tree restoredHuffman = getHuffmanTreeFromFile(treeText);

    // string compressed = compress(huffman, text, frequencies);
    // string decompressed = decompress(compressed ,huffman);


    // string inputPath;
    // string outputPath;

    // cin.ignore();
    // cin.ignore();
    // cin.ignore();
    
    // cin >> inputPath;

    // cin.ignore();
    // cin.ignore();
    // cin.ignore();

    // cin >> outputPath;

    // string text = getTextFromFile(inputPath);
    // ofstream file(outputPath);
    // if (mode == 'c') {
    //     vector<pair<char, int>> frequencies = getCharFrequency(text);
    //     tree huffman = constructHuffmanTree(frequencies);
    //     ofstream treeStream("tree.txt");
    //     huffman.printDOTPair(treeStream);
    //     string compressed = compress(huffman, text, frequencies);

    //     file << compressed; 
    // } else {
    //     tree huffman = getHuffmanTreeFromFile("tree.txt");
    //     string decompressed = decompress(text, huffman);
    //     file << decompressed;
    // }
}