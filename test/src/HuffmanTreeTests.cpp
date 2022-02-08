#include "doctest.h"
#include "HuffmanBuilder.h"
#include "HuffmanTree.h"

TEST_CASE("HuffmanTree tests") {

    SUBCASE("code() and decode() test") {
        huffman::HuffmanBuilder builder;
        for (int i = 1; i <= std::numeric_limits<uint8_t>::max(); i++)
            builder.update(i, 2 * i);
        huffman::HuffmanTree tree = builder.build();
        for (int i = 1; i <= std::numeric_limits<uint8_t>::max(); i++) {
            CHECK(tree.containsCode(tree.code(i)));
            CHECK_EQ(tree.decode(tree.code(i)), i);
        }
        CHECK_THROWS(tree.code(0));
        CHECK_FALSE(tree.containsCode(std::vector<bool>(0)));
        CHECK_THROWS(tree.decode(std::vector<bool>(0)));
    }

    SUBCASE("test code correctness") {
        std::vector<std::pair<int, int>> data { std::make_pair(5, 4), std::make_pair(15, 4),
                                                std::make_pair(20, 3), std::make_pair(45, 2),
                                                std::make_pair(100, 1) };
        huffman::HuffmanBuilder builder;
        for (int i = 0; i < data.size(); i++)
            builder.update(i, data[i].first);
        huffman::HuffmanTree tree = builder.build();
        for (int i = 0; i < data.size(); i++)
            CHECK_EQ(tree.code(i).size(), data[i].second);
    }

    SUBCASE("single sequence test") {
        huffman::HuffmanBuilder builder;
        builder.update(1, 100);
        huffman::HuffmanTree tree = builder.build();
        CHECK_EQ(tree.code(1).size(), 1);
    }

}