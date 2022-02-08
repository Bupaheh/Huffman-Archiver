#pragma once

#include <fstream>
#include <cstdint>
#include <vector>
#include <limits>

namespace huffman {

    class Reader {
    public:
        explicit Reader(std::istream &in);

        bool readBit();
        uint8_t readByte();
        std::vector<bool> read(std::size_t n);
        std::size_t getNmOfBytesRead() const noexcept;
        void seek(int value, std::ios_base::seekdir way = std::ios_base::beg);

    private:
        void updateBuffer();

        static const std::size_t bufferSize = std::numeric_limits<uint8_t>::digits;
        uint8_t buffer = 0;
        int index = -1;
        std::size_t nmOfBytesRead = 0;
        std::istream &in;
    };
}