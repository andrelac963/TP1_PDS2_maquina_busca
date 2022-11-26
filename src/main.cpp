#include <iostream>
#include <string>
#include "indexing.hpp"

using namespace std;

int main()
{
  string search, option;
  indexing index;

  do
  {
    cout << "O que deseja buscar?\n ";
    cin >> search;

    index.recovery(search);

    do
    {
      cout << "\nDeseja fazer outra pesquisa? (s/n)" << endl;
      cin >> option;

      if (option != "s" && option != "n")
      {
        cout << "Opção inválida!" << endl;
      }

    } while (option != "s" && option != "n");

    if (option == "s")
    {
      cout << "\n--------------------------------------------\n"
           << endl;
    }

  } while (option == "s");

  return 0;
}