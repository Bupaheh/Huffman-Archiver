#pragma once

#include <fstream>
#include <cstdint>
#include <vector>

namespace huffman {

    class Writer {
    public:
        explicit Writer(std::ostream &out);

        void write(bool value);
        void writeByte(uint8_t value);
        void write(const std::vector<bool> &value);
        char flush();
        std::size_t getNmOfBytesWritten() const noexcept;
        void seek(int value, std::ios_base::seekdir way = std::ios_base::beg);

    private:
        void print();

        static const std::size_t bufferSize = std::numeric_limits<uint8_t>::digits;
        uint8_t buffer = 0;
        int size = 0;
        std::size_t nmOfBytesWritten = 0;
        std::ostream &out;
    };
}