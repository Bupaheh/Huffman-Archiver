#include "Reader.h"

#include <stdexcept>

namespace huffman {

    Reader::Reader(std::istream &in): in(in) {
        if (in.fail())
            throw std::ios_base::failure("Unable to open file");
    }

    bool Reader::readBit() {
        if (index < 0)
            updateBuffer();
        bool result = (buffer >> index) & 1;
        index--;
        return result;
    }

    uint8_t Reader::readByte() {
        int prevIndex = index;
        uint8_t res = buffer << (bufferSize - index - 1);
        int sizeOfRes = index + 1;
        updateBuffer();
        res = res + (buffer >> sizeOfRes);
        index = prevIndex;
        return res;
    }

    std::vector<bool> Reader::read(std::size_t n) {
        std::vector<bool> result;
        result.reserve(n);
        for (int i = 0; i < n; i++)
            result.push_back(readBit());
        return result;
    }

    void Reader::updateBuffer() {
        in.read((char *) &buffer, sizeof(buffer));
        if (in.fail()) {
            in.clear();
            throw std::ios_base::failure("End of file");
        }
        nmOfBytesRead++;
        index = bufferSize - 1;
    }

    std::size_t Reader::getNmOfBytesRead() const noexcept {
        return nmOfBytesRead;
    }

    void Reader::seek(int value, std::ios_base::seekdir way) {
        in.seekg(value, way);
    }
}