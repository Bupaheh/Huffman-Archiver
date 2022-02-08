#include "doctest.h"
#include "Writer.h"

#include <string>
#include <sstream>
#include <vector>

TEST_CASE("Writer tests") {

    std::stringstream out;
    huffman::Writer writer(out);

    SUBCASE("writeByte() test") {
        std::vector<uint8_t> data = {253, 141, 0};
        for (uint8_t x : data)
            writer.writeByte(x);
        std::string res = out.str();
        for (int i = 0; i < data.size(); i++)
            CHECK_EQ(uint8_t (res[i]), data[i]);
    }

    SUBCASE("write(const std::vector<bool> &) test") {
        std::vector<bool> data {1, 0, 0, 1, 0, 0, 1, 0,
                                1, 1, 1, 1, 0, 0, 0, 1};
        writer.write(data);
        std::string res = out.str();
        CHECK_EQ(uint8_t (res[0]), 146);
        CHECK_EQ(uint8_t (res[1]), 241);
    }

    SUBCASE("getNmOfBytesWritten() test") {
        std::vector<bool> data {1, 0, 0, 1, 0, 0, 1, 0,
                                1, 0, 1};
        CHECK_EQ(writer.getNmOfBytesWritten(), 0);
        writer.write(data);
        CHECK_EQ(writer.getNmOfBytesWritten(), 2);
    }

    SUBCASE("flush() test") {
        std::vector<bool> data {1, 0, 0, 1, 0, 0, 1, 0,
                                1, 0, 1};
        writer.write(data);
        std::string res = out.str();
        CHECK_EQ(res.size(), 1);
        CHECK_EQ(uint8_t (res[0]), 146);
        writer.flush();
        res = out.str();
        CHECK_EQ(res.size(), 2);
        CHECK_EQ(uint8_t (res[1]), 160);
    }

    SUBCASE("write(bool) test") {
        writer.write(1);
        writer.write(1);
        writer.flush();
        std::string res = out.str();
        CHECK_EQ(uint8_t (res[0]), 192);
    }

}
