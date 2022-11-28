#include "indexing.hpp"

using namespace std;

int main()
{

  string option, word, aux;
  indexing search;
  search.read_files();

  do
  {
    vector<string> query;

    cout << "O que deseja buscar?\n ";
    getline(cin, word);

    for (int i = 0; i <= word.length(); i++)
    {
      if (word[i] == ' ' || i == word.length())
      {
        query.push_back(aux);
        aux = "";
      }
      else
      {
        aux += word[i];
      }
    }

    search.recovery(query);

    do
    {
      cout << "\n\nDeseja fazer outra pesquisa? (s/n)" << endl;
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

    cin.ignore();

  } while (option == "s");

  return 0;
}