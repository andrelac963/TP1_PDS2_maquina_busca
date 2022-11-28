#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "indexing.hpp"

TEST_CASE("Testa Indexing::Indexing()")
{
  indexing test;
  CHECK(test.get_index().size() == 0);
}

TEST_CASE("Testa Indexing::read_directory()")
{
  indexing test;
  set<string> files = test.read_directory("./tests");
  CHECK(files.size() == 2);
  CHECK(files.find("test.cpp") != files.end());
  CHECK(files.find("doctest.h") != files.end());
}

TEST_CASE("Testa Indexing::Insert()")
{
  indexing test;
  test.insert("teste", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Normalize()")
{
  indexing test;
  string normalized_word = test.normalize("TèStÉ");
  CHECK(normalized_word == "teste");
}