#include "iostream"
#include "htree.cpp"
#include "fstream"
using namespace std;

int main(){

    HTree huffman("input.txt");
    string compressed = huffman.getCompressedText();
    ofstream compressedOutput("output.txt");

    compressedOutput << compressed;    
}