cmake_minimum_required(VERSION 3.19)
project(archiver)

set(CMAKE_CXX_STANDARD 20)
include_directories(project/include/)
include_directories(test/include/)

add_executable(archiver project/src/main.cpp project/src/Writer.cpp project/include/Writer.h project/src/Reader.cpp project/include/Reader.h project/src/HuffmanBuilder.cpp project/include/HuffmanBuilder.h project/src/HuffmanTree.cpp project/include/HuffmanTree.h project/src/HuffmanArchiver.cpp project/include/HuffmanArchiver.h)
add_executable(tests project/src/Writer.cpp project/include/Writer.h project/src/Reader.cpp project/include/Reader.h project/src/HuffmanBuilder.cpp project/include/HuffmanBuilder.h project/src/HuffmanTree.cpp project/include/HuffmanTree.h project/src/HuffmanArchiver.cpp project/include/HuffmanArchiver.h test/include/doctest.h test/src/ReaderTests.cpp test/src/WriterTests.cpp test/src/HuffmanBuilderTests.cpp test/src/HuffmanTreeTests.cpp test/src/HuffmanArchiverTests.cpp)
