#include <iostream>
#include <string>
#include "indexing.hpp"

int main()
{
  string pesquisa;
  indexing teste;
 
  cout << "O que deseja buscar?\n ";
  cin >> pesquisa;

  teste.recovery(pesquisa);

  return 0;
}