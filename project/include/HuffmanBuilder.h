#pragma once

#include "HuffmanTree.h"

namespace huffman {

    class HuffmanBuilder {
    public:
        void update(uint8_t seq, unsigned long count = 1);
        HuffmanTree build() const;
        unsigned long getCount(uint8_t seq) const noexcept;
        unsigned long getMaxCount() const noexcept;

    private:
        std::unordered_map<uint8_t, unsigned long> data;
    };
}