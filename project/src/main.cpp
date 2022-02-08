#include "HuffmanArchiver.h"

#include <iostream>
#include <stdexcept>

namespace {

    enum Mode {
        CompressingMode,
        DecompressingMode
    };

    void compressingMode(std::ifstream &in, std::ofstream &out) {
        huffman::HuffmanArchiver archiver(in, out);
        archiver.compress();
        std::cout << archiver.getSizeOfData() << std::endl
                  << archiver.getSizeOfCodedData() << std::endl
                  << archiver.getSizeOfHeader() << std::endl;
    }

    void decompressingMode(std::ifstream &in, std::ofstream &out) {
        huffman::HuffmanArchiver archiver(in, out);
        archiver.decompress();
        std::cout << archiver.getSizeOfCodedData() << std::endl
                  << archiver.getSizeOfData() << std::endl
                  << archiver.getSizeOfHeader() << std::endl;
    }

}

int main(int argc, char *argv[]) {
    char mode = -1;
    std::ofstream out;
    std::ifstream in;
    for (int i = 1; i < argc; i++) {
        std::string command(argv[i]);
        if (command == "-c")
            mode = CompressingMode;
        else if (command == "-u")
            mode = DecompressingMode;
        else if ((command == "-f" || command == "--file") && ++i < argc)
            in.open(std::string(argv[i]), std::ios::binary);
        else if ((command == "-o" || command == "--output") && ++i < argc)
            out.open(std::string(argv[i]), std::ios::binary);
    }
    try {
        switch (mode) {
            case CompressingMode:
                compressingMode(in, out);
                break;
            case DecompressingMode:
                decompressingMode(in, out);
                break;
            default:
                std::cout << "Invalid mode argument\n";
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        in.close();
        out.close();
    }
    in.close();
    out.close();
    return 0;
}