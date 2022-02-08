#include "Writer.h"

namespace huffman {

    Writer::Writer(std::ostream &out) : out(out) {}

    char Writer::flush() {
        char res = (bufferSize - size) % bufferSize;
        if (size != 0)
            print();
        return res;
    }

    void Writer::write(bool value) {
        buffer = buffer + (value << (bufferSize - size - 1));
        size++;
        if (size == 8)
            print();
    }

    void Writer::writeByte(uint8_t value) {
        uint8_t res = buffer + (value >> size);
        out.write((char *) &res, sizeof(uint8_t));
        nmOfBytesWritten++;
        buffer = value << (bufferSize - size);
    }

    void Writer::write(const std::vector<bool> &value) {
        for (bool i : value)
            write(i);
    }

    void Writer::print() {
        out.write((char *) &buffer, sizeof(buffer));
        size = 0;
        buffer = 0;
        nmOfBytesWritten++;
    }

    std::size_t Writer::getNmOfBytesWritten() const noexcept {
        if (size != 0)
            return nmOfBytesWritten + 1;
        else
            return nmOfBytesWritten;
    }

    void Writer::seek(int value, std::ios_base::seekdir way) {
        out.seekp(value, way);
    }


}
