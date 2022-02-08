#include "doctest.h"
#include "HuffmanArchiver.h"

#include <string>
#include <sstream>
#include <random>

std::string compress(const std::string &data) {
    std::stringstream in(data);
    std::stringstream out(std::string(6, '*'));
    huffman::HuffmanArchiver archiver(in, out);
    archiver.compress();
    std::string codedData = out.str();
    CHECK_EQ(archiver.getSizeOfData(), data.size());
    CHECK_EQ(archiver.getSizeOfCodedData(), codedData.size() - archiver.getSizeOfHeader());
    return codedData;
}

std::string decompress(const std::string &codedData) {
    std::stringstream in(codedData);
    std::stringstream out;
    huffman::HuffmanArchiver archiver(in, out);
    archiver.decompress();
    std::string data = out.str();
    CHECK_EQ(archiver.getSizeOfData(), data.size());
    CHECK_EQ(archiver.getSizeOfCodedData(), codedData.size() - archiver.getSizeOfHeader());
    return data;
}

TEST_CASE("HuffmanArchiver tests") {

    SUBCASE("short file case") {
        std::string data = "something";
        std::string codedString = compress(data);
        std::string decompressedData = decompress(codedString);
        CHECK_EQ(decompressedData, data);
    }

    SUBCASE("empty file case") {
        std::string data;
        std::string codedString = compress(data);
        std::string decompressedData = decompress(codedString);
        CHECK_EQ(decompressedData, data);
    }

    SUBCASE("single character file case") {
        std::string data(100, '1');
        std::string codedString = compress(data);
        std::string decompressedData = decompress(codedString);
        CHECK_EQ(decompressedData, data);
    }

    SUBCASE("large file case") {
        std::size_t sizeOfFile = 300000;
        std::stringstream stringBuilder;
        std::mt19937 mt(1);
        std::uniform_int_distribution<char> dist(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
        for (int i = 0; i < sizeOfFile; i++)
            stringBuilder << dist(mt);
        std::string data = stringBuilder.str();
        std::string codedString = compress(data);
        std::string decompressedData = decompress(codedString);
        CHECK_EQ(decompressedData, data);
    }

    SUBCASE("corrupted file case") {
        std::string s = "corrupted data";
        CHECK_THROWS(decompress(s));
    }

}