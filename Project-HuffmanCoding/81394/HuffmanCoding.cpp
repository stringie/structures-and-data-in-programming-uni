#include "iostream"
#include "htree.cpp"
#include "fstream"
#include "bitset"
#include "cmd.hpp"
using namespace std;


void configure_parser(cli::Parser& parser) {
    parser.set_optional<string>("i", "input", "input_file.txt", "Input filepath.");
    parser.set_optional<string>("o", "output", "output_file.txt", "Output filepath.");
    parser.set_optional<bool>("l", "load-tree", false, "Load tree.");
    parser.set_optional<bool>("s", "save-tree", false, "Save tree.");
    parser.set_optional<bool>("c", "compress", false, "Compress a file.");
    parser.set_optional<bool>("d", "decompress", false, "Decompress a file.");
    parser.set_optional<bool>("b", "byte-format", false, "Use byte format for the output.");
    parser.set_optional<bool>("e", "compression-efficiency", false, "Output compression efficiency.");
}

int main(int argcount, char** args){

    cli::Parser parser(argcount, args);
    configure_parser(parser);
    parser.run_and_exit_if_error();

    string input = parser.get<string>("i");
    string output = parser.get<string>("o");
    bool compress = parser.get<bool>("c");
    bool decompress = parser.get<bool>("d");
    bool save = parser.get<bool>("s");
    bool load = parser.get<bool>("l");
    bool format = parser.get<bool>("b");
    bool efficiency = parser.get<bool>("e");

    string treePath = "tree.txt";

    if (compress){
        if (load){
            HTree huffman;
            huffman.load(treePath);
            string compressed;
            if (format){
                compressed = huffman.getCompressedTextInByteFormat();
            }else{
                compressed = huffman.getCompressedText();
            }
            ofstream file(output);
            file << compressed;
            file.close();

            if (efficiency){
                cout << "Original file size: " << huffman.getText().size()*8 << endl; // показваме разликата в размера (ефективността на компресията)
                cout << "Compressed file size: " << compressed.size() << endl;
            }
        }else{
            HTree huffman(input);
            string compressed;
            if (format){
                compressed = huffman.getCompressedTextInByteFormat();
            }else{
                compressed = huffman.getCompressedText();
            }
            ofstream file(output);
            file << compressed;
            file.close();

            if (efficiency){
                cout << "Original file size: " << huffman.getText().size()*8 << endl; // показваме разликата в размера (ефективността на компресията)
                cout << "Compressed file size: " << compressed.size() << endl;
            }

            if (save){
                huffman.save(treePath);
            }
        }
    } else if (decompress){
        if (load){
            HTree huffman;
            huffman.load(treePath);
            string decompressed = huffman.decompress(input);
            ofstream file(output);
            file << decompressed;
            file.close();
        }
    }
}