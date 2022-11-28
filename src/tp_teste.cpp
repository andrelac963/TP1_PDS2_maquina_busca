#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"

#include "indexing.hpp"

TEST_CASE("indexing::indexing()")
{
  indexing index;
  CHECK(index.index.size() == 0);
}

TEST_CASE("indexing::insert(word, filename)")
{
  indexing index;
  index.insert("word", "filename");
  CHECK(index.index.size() == 1);
  CHECK(index.index["word"].size() == 1);
  CHECK(index.index["word"].count("filename") == 1);
}

TEST_CASE("indexing::normalize(word)"){
  indexing index;
  
}









