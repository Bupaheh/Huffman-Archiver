#include "doctest.h"
#include "HuffmanBuilder.h"

TEST_CASE("HuffmanBuilder tests") {

    huffman::HuffmanBuilder builder;
    for (int i = 1; i <= std::numeric_limits<uint8_t>::max(); i++)
        builder.update(i, 2 * i);

    SUBCASE("getCount() test") {
        for (int i = 0; i <= std::numeric_limits<uint8_t>::max(); i++)
            CHECK_EQ(builder.getCount(i), 2 * i);
    }

    SUBCASE("getMaxCount() test") {
        CHECK_EQ(builder.getMaxCount(), std::numeric_limits<uint8_t>::max() * 2);
    }

    SUBCASE("getMaxCount() test with empty builder") {
        huffman::HuffmanBuilder testBuilder;
        CHECK_EQ(testBuilder.getMaxCount(), 0);
    }

    SUBCASE("build() with empty builder") {
        CHECK_NOTHROW(huffman::HuffmanBuilder().build());
    }

}