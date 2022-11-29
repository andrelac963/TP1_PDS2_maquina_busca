#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../include/indexing.hpp"

TEST_CASE("Testa Indexing::Indexing()")
{
  indexing test;
  CHECK(test.get_index().size() == 0);
}

TEST_CASE("Testa Indexing::read_directory()")
{
  indexing test;
  set<string> files = test.read_directory("./tests");
  CHECK(files.size() == 3);
  CHECK(files.find("test.cpp") != files.end());
  CHECK(files.find("doctest.h") != files.end());
  CHECK(files.find("documentos_test") != files.end());
}

TEST_CASE("Testa Indexing::read_directory() com diretório inexistente")
{
  indexing test;
  set<string> files = test.read_directory("./tests/nao_existe");
  CHECK(files.size() == 0);
}

TEST_CASE("Testa Indexing::read_files()")
{
  indexing test;
  test.read_files("./tests/documentos_test/");
  CHECK(test.get_index().size() == 3);
}

TEST_CASE("Testa Indexing::read_files() com diretório inexistente")
{
  indexing test;
  test.read_files("./tests/nao_existe/");
  CHECK(test.get_index().size() == 0);
}

TEST_CASE("Testa Indexing::Insert()")
{
  indexing test;
  test.insert("teste", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() com acentos")
{
  indexing test;
  test.insert("áéíóú", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() com acentos e letras maiúsculas")
{
  indexing test;
  test.insert("ÁÉÍÓÚ", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() com acentos e letras maiúsculas e minúsculas")
{
  indexing test;
  test.insert("áÉíÓú", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() com acentos e letras maiúsculas e minúsculas e caracteres especiais")
{
  indexing test;
  test.insert("áÉíÓú!@#$%¨&*()_+{}[];:.,<>?/|\\", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() com acentos e letras maiúsculas e minúsculas e caracteres especiais e números")
{
  indexing test;
  test.insert("áÉíÓú!@#$%¨&*()_+{}[];:.,<>?/|\\1234567890", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() com acentos e letras maiúsculas e minúsculas e caracteres especiais e números e espaços")
{
  indexing test;
  test.insert("áÉíÓú!@#$%¨&*()_+{}[];:.,<>?/|\\1234567890 ", "teste.txt");
  CHECK(test.get_index().size() == 1);
}

TEST_CASE("Testa Indexing::Insert() somente caracteres especiais")
{
  indexing test;
  test.insert("!@#$%¨&*()_+{}[];:.,<>?/|\\", "teste.txt");
  CHECK(test.get_index().size() == 0);
}

TEST_CASE("Testa Indexing::Insert() somente números")
{
  indexing test;
  test.insert("1234567890", "teste.txt");
  CHECK(test.get_index().size() == 0);
}

TEST_CASE("Testa Indexing::Insert() somente espaços")
{
  indexing test;
  test.insert(" ", "teste.txt");
  CHECK(test.get_index().size() == 0);
}

TEST_CASE("Testa Indexing::Normalize() com acentos")
{
  indexing test;
  string normalized_word = test.normalize("áéíóú");
  CHECK(normalized_word == "aeiou");
}

TEST_CASE("Testa Indexing::Normalize() com acentos e letras maiúsculas")
{
  indexing test;
  string normalized_word = test.normalize("ÁÉÍÓÚ");
  CHECK(normalized_word == "aeiou");
}

TEST_CASE("Testa Indexing::Normalize() com acentos e letras maiúsculas e minúsculas")
{
  indexing test;
  string normalized_word = test.normalize("áÉíÓú");
  CHECK(normalized_word == "aeiou");
}

TEST_CASE("Testa Indexing::Normalize() com acentos e letras maiúsculas e minúsculas e caracteres especiais")
{
  indexing test;
  string normalized_word = test.normalize("áÉíÓú!@#$%¨&*()_+{}[];:.,<>?/|\\");
  CHECK(normalized_word == "aeiou");
}

TEST_CASE("Testa Indexing::Normalize() com acentos e letras maiúsculas e minúsculas e caracteres especiais e números")
{
  indexing test;
  string normalized_word = test.normalize("áÉíÓú!@#$%¨&*()_+{}[];:.,<>?/|\\1234567890");
  CHECK(normalized_word == "aeiou");
}

TEST_CASE("Testa Indexing::Normalize() com acentos e letras maiúsculas e minúsculas e caracteres especiais e números e espaços")
{
  indexing test;
  string normalized_word = test.normalize("áÉíÓú!@#$%¨&*()_+{}[];:.,<>?/|\\1234567890 ");
  CHECK(normalized_word == "aeiou");
}

TEST_CASE("Testa Indexing::Normalize() somente caracteres especiais")
{
  indexing test;
  string normalized_word = test.normalize("!@#$%¨&*()_+{}[];:.,<>?/|\\");
  CHECK(normalized_word == "");
}

TEST_CASE("Testa Indexing::Normalize() somente números")
{
  indexing test;
  string normalized_word = test.normalize("1234567890");
  CHECK(normalized_word == "");
}

TEST_CASE("Testa Indexing::Normalize() somente espaços")
{
  indexing test;
  string normalized_word = test.normalize(" ");
  CHECK(normalized_word == "");
}

TEST_CASE("Testa Indexing::Recovery()")
{
  indexing test;
  vector<string> input_recovery = {"teste", "testando"};
  test.insert("teste", "teste.txt");
  test.insert("teste", "teste2.txt");
  test.insert("teste", "teste3.txt");
  test.insert("testando", "teste.txt");
  test.insert("testando", "teste3.txt");
  vector<pair<string, int>> result_recovery = test.recovery(input_recovery);
  CHECK(result_recovery.size() == 3);
  CHECK(result_recovery[0].first == "teste.txt");
  CHECK(result_recovery[0].second == 2);
  CHECK(result_recovery[1].first == "teste3.txt");
  CHECK(result_recovery[1].second == 2);
  CHECK(result_recovery[2].first == "teste2.txt");
  CHECK(result_recovery[2].second == 1);
}

