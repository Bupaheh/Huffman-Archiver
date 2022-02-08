#pragma once

#include "Reader.h"
#include "Writer.h"
#include "HuffmanBuilder.h"

namespace huffman {

    class HuffmanArchiver {
    public:
        HuffmanArchiver(std::istream &in, std::ostream &out);

        std::size_t getSizeOfHeader() const noexcept { return sizeOfHeader; }
        std::size_t getSizeOfData() const noexcept { return sizeOfData; }
        std::size_t getSizeOfCodedData() const noexcept { return sizeOfCodedData; }

        void compress();
        void decompress();

    private:
        static std::size_t bitsNeeded(long value) noexcept;
        static std::vector<bool> intToSequence(unsigned long value, std::size_t size);
        static unsigned long sequenceToInt(const std::vector<bool> &sequence) noexcept;

        static void fillFrequency(huffman::HuffmanBuilder &builder, Reader &reader) noexcept;
        static void writeFrequency(huffman::HuffmanBuilder &builder, Writer &writer, std::size_t sizeOfTableElement);
        static std::size_t codeData(huffman::HuffmanTree &tree, Reader &reader, Writer &writer);
        static void fillHeader(Writer &writer, std::size_t sizeOfCodedData, std::size_t offsetBits, std::size_t sizeOfTableElement);

        static void extractHeaderData(Reader &reader, size_t &sizeOfCodedData,
                                      size_t &offsetBits, size_t &sizeOfTableElement);
        static void extractFrequency(Reader &reader, HuffmanBuilder &builder, std::size_t sizeOfTableElement);
        static void decodeData(Reader &reader, Writer &writer, HuffmanTree &tree, unsigned long nmOfBitsToRead);

        static const std::size_t bitsInByte = std::numeric_limits<unsigned char>::digits;
        static const std::size_t sizeOfHeaderSizeInfo = 6;
        static const std::size_t sizeOfFirstHeaderBlock = 4;
        static const std::size_t sizeOfSecondHeaderBlock = 1;
        static const std::size_t sizeOfThirdHeaderBlock = 1;

        std::size_t sizeOfHeader = -1;
        std::size_t sizeOfData = -1;
        std::size_t sizeOfCodedData = -1;
        std::istream &in;
        std::ostream &out;
    };
}
