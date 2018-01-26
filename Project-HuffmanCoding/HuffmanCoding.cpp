#include "iostream"
#include "htree.cpp"
#include "fstream"
#include "bitset"
using namespace std;

int main(){

    // ЗАДАЧАТА: 
    // Да се напише програма, която въвежда съдържанието на текстов файл, построява честотна 
    // таблица и дървото на Хъфман и извежда в друг текстов файл двоичната последователност, 
    // която кодира оригиналния низ. Да се поддържат режим на работа,в който вместо извеждане
    // на двоичната последователност, да се изведе поредица от числа от 0 до 255, получени от
    // разбиване на блокове от по 8 бита. Да се пресметне степента на компресия (отношението 
    // на броя на битовете на компресираната и декомпресираната последователност — считаме, че
    // всеки символ се кодира с един байт). По дървото на Хъфман да се възстанови оригиналният низ.

    // Създаденото дърво на Хъфман (не честотната таблица) да може да се извежда и въвежда в подходящ формат. 
    // Дървото на Хъфман да се пази в изходния текстов файл или в отделен файл.
    // ИЗПЪЛНЕНИЕ: 

    
    // зареждаме дърво на хъфман с текст от файл
    HTree huffman("input.txt");
    string compressed = huffman.getCompressedText(); // компресирания низ
    string compressedInBytes = huffman.getCompressedTextInByteFormat(); // същия низ в битов формат
    
    ofstream compressedOutput("output.txt"); 
    compressedOutput << compressed; // извеждаме компресирания низ
    compressedOutput.close();
    
    ofstream compressedOutputInBytes("outputInBytesFormat.txt");
    compressedOutputInBytes << compressedInBytes; // извеждаме битовия формат
    compressedOutputInBytes.close();

    cout << "Original file size: " << huffman.getText().size()*8 << endl; // показваме разликата в размера (ефективността на компресията)
    cout << "Compressed file size: " << compressed.size() << endl;

    // показваме възможност за възстановяване на низа по дървото (декомпресия)
    cout << "Decompressed file contents: " << huffman.decompress(compressed) << endl << endl; 

    // показваме възможност да запазим дървото в удобен и смислен формат (in-order)
    huffman.save("tree.txt");

    // създаваме ново дърво за да покажем възможност за възстановяване дърво от файл
    HTree testLoad;
    testLoad.load("tree.txt");
    cout << "Loaded tree decompression test: " << testLoad.decompress(compressed) << endl;
}