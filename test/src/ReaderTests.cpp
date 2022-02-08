#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Reader.h"
#include "Writer.h"

#include <string>
#include <sstream>
#include <vector>

TEST_CASE("Reader tests") {

    std::stringstream in;
    huffman::Writer writer(in);
    huffman::Reader reader(in);
    std::vector <bool> data {1, 0, 1, 1, 1, 0, 0, 0,
                             0, 0, 0, 0, 1, 1, 0, 0};
    writer.write(data);

    SUBCASE("readBit() test") {
        for (bool x : data)
            CHECK_EQ(reader.readBit(), x);
    }

    SUBCASE("readByte() test") {
        uint8_t t1 = reader.readByte();
        uint8_t t2 = reader.readByte();
        CHECK_EQ(t1, 184);
        CHECK_EQ(t2, 12);
    }

    SUBCASE("read() test") {
        std::vector <bool> res = reader.read(10);
        for (int i = 0; i < res.size(); i++)
            CHECK_EQ(res[i], data[i]);
    }

    SUBCASE("getNmOfBytesRead() test") {
        reader.readByte();
        CHECK_EQ(reader.getNmOfBytesRead(), 1);
        reader.readBit();
        CHECK_EQ(reader.getNmOfBytesRead(), 2);
    }

    SUBCASE("throws exception after the end of the file") {
        CHECK_THROWS_AS(reader.read(17), std::ios_base::failure);
    }

}
