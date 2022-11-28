#include "../ext/googletest/googletest/include/gtest/gtest.h"
#include "../include/indexing.hpp"

TEST(IndexingTest, construtor){
  map<string, set<string>> index;
  indexing indexador;
  ASSERT_EQ(index, indexador.index);
}

TEST(IndexingTest, RecoveryTest) {
  indexing index;
  vector<string> files = {"../data/1.txt", "../data/2.txt", "../data/3.txt"};
  index.recovery(files);
  CHECK(index[1] == "1.txt");
  CHECK(index[2] == "2.txt");
  check(index[3] == "3.txt");
}

TEST(IndexingTest, InsertTest) {
  indexing index;
  index.insert("1.txt", "1");
  CHECK(index[1] == "1.txt");
}

TEST(IndexingTest, NormalizeTest) {
  indexing index;
  CHECK(index.normalize("WORD") == "word");
  CHECK(index.normalize("wórD") == "word");
  CHECK(index.normalize("WórD.") == "word");
}

  









