#include "HuffmanArchiver.h"

namespace huffman {

    HuffmanArchiver::HuffmanArchiver(std::istream &in, std::ostream &out): in(in), out(out) {}

    std::size_t HuffmanArchiver::bitsNeeded(long value) noexcept {
        int res = 0;
        while (value > 0) {
            res++;
            value /= 2;
        }
        return res;
    }

    std::vector<bool> HuffmanArchiver::intToSequence(unsigned long value, std::size_t size) {
        std::vector<bool> res(size);
        for (int i = 0; i < size; i++) {
            res[i] = value % 2;
            value /= 2;
        }
        return res;
    }

    unsigned long HuffmanArchiver::sequenceToInt(const std::vector<bool> &sequence) noexcept {
        unsigned long res = 0, prev = 1;
        for (bool i : sequence) {
            res += i * prev;
            prev *= 2;
        }
        return res;
    }

    void HuffmanArchiver::compress() {
        HuffmanBuilder builder;
        Reader reader(in);
        Writer writer(out);

        fillFrequency(builder, reader);
        sizeOfData = reader.getNmOfBytesRead();

        std::size_t sizeOfTableElement = (bitsNeeded(builder.getMaxCount()) + bitsInByte - 1) / bitsInByte;
        writer.seek(sizeOfHeaderSizeInfo);
        writeFrequency(builder, writer, sizeOfTableElement);
        sizeOfHeader = sizeOfHeaderSizeInfo + writer.getNmOfBytesWritten();

        huffman::HuffmanTree tree = builder.build();
        reader.seek(0);
        std::size_t offsetBits = codeData(tree, reader, writer);

        sizeOfCodedData = writer.getNmOfBytesWritten() - sizeOfHeader + sizeOfHeaderSizeInfo;
        writer.seek(0);
        fillHeader(writer, sizeOfCodedData, offsetBits, sizeOfTableElement);
    }

    void HuffmanArchiver::fillFrequency(huffman::HuffmanBuilder &builder, Reader &reader) noexcept {
        try {
            while (true)
                builder.update(reader.readByte());
        } catch (std::ios_base::failure &e) {}
    }

    void HuffmanArchiver::writeFrequency(HuffmanBuilder &builder, Writer &writer, std::size_t sizeOfTableElement) {
        for (int i = 0; i <= std::numeric_limits<uint8_t>::max(); i++) {
            unsigned long count = builder.getCount(i);
            writer.write(intToSequence(count, sizeOfTableElement * bitsInByte));
        }
    }

    std::size_t HuffmanArchiver::codeData(HuffmanTree &tree, Reader &reader, Writer &writer) {
        try {
            while (true) {
                uint8_t sequence = reader.readByte();
                try {
                    writer.write(tree.code(sequence));
                } catch (std::out_of_range &e) {
                    throw std::invalid_argument("Illegal state of HuffmanTree");
                }
            }
        } catch (std::ios_base::failure &e) {}
        return writer.flush();
    }

    void HuffmanArchiver::fillHeader(Writer &writer, std::size_t sizeOfCodedData, std::size_t offsetBits, std::size_t sizeOfTableElement) {
        writer.write(intToSequence(sizeOfCodedData, sizeOfFirstHeaderBlock * bitsInByte));
        writer.write(intToSequence(offsetBits, sizeOfSecondHeaderBlock * bitsInByte));
        writer.write(intToSequence(sizeOfTableElement, sizeOfThirdHeaderBlock * bitsInByte));
    }

    void HuffmanArchiver::decompress() {
        HuffmanBuilder builder;
        Reader reader(in);
        Writer writer(out);

        std::size_t offsetBits, sizeOfTableElement;
        extractHeaderData(reader, sizeOfCodedData, offsetBits, sizeOfTableElement);

        extractFrequency(reader, builder, sizeOfTableElement);
        sizeOfHeader = reader.getNmOfBytesRead();

        HuffmanTree tree = builder.build();
        decodeData(reader, writer, tree, sizeOfCodedData * bitsInByte - offsetBits);
        sizeOfData = writer.getNmOfBytesWritten();
    }

    void HuffmanArchiver::extractHeaderData(Reader &reader, size_t &sizeOfCodedData, size_t &offsetBits,
                                            size_t &sizeOfTableElement) {
        sizeOfCodedData = sequenceToInt(reader.read(bitsInByte * sizeOfFirstHeaderBlock));
        offsetBits = sequenceToInt(reader.read(bitsInByte * sizeOfSecondHeaderBlock));
        sizeOfTableElement = sequenceToInt(reader.read(bitsInByte * sizeOfThirdHeaderBlock));
    }

    void HuffmanArchiver::extractFrequency(Reader &reader, HuffmanBuilder &builder, std::size_t sizeOfTableElement) {
        try {
            for (int i = 0; i <= std::numeric_limits<uint8_t>::max(); i++) {
                unsigned long count = sequenceToInt(reader.read(sizeOfTableElement * bitsInByte));
                builder.update(i, count);
            }
        } catch (std::ios_base::failure &e) {
            throw std::invalid_argument("Corrupted file");
        }
    }

    void HuffmanArchiver::decodeData(Reader &reader, Writer &writer, HuffmanTree &tree, unsigned long nmOfBitsToRead) {
        std::vector<bool> now;
        for (unsigned long i = 0; i < nmOfBitsToRead; i++) {
            try {
                now.push_back(reader.readBit());
            } catch (std::ios_base::failure &e) {
                throw std::invalid_argument("Corrupted file");
            }
            if (tree.containsCode(now)) {
                uint8_t data = tree.decode(now);
                writer.writeByte(data);
                now.clear();
            }
        }
    }

}