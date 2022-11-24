#include "indexing.hpp"

indexing::indexing()
{
  fstream file;
  string word, filename;
  int i = 1;

  do
  {
    filename = "d" + to_string(i) + ".txt";

    file.open("./documentos/" + filename);

    while (file >> word)
    {
      this->insert(word, filename);
    }

    file.close();

    i++;
  } while (i <= 3);
}

indexing::~indexing()
{
}

void indexing::insert(string word, string filename)
{
  string normalized_word = this->normalize(word);
  this->index[normalized_word].insert(filename);
}

string indexing::normalize(string word)
{
  string normalized_word = "", aux;

  string comAcentos = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
  string semAcentos = "AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc";

  for (int i = 0; i < word.length(); i++)
  {
    aux = tolower(word[i]);

    for (int j = 0; j < comAcentos.length(); j += 2)
    {
      if (word[i] << word[i + 1] == comAcentos[j] << comAcentos[j + 1])
      {
        aux = semAcentos[j / 2];
        aux = tolower(aux[0]);
        break;
      }
    }

    if (isalpha(aux[0]))
    {
      normalized_word += aux;
    }
  }

  return normalized_word;
}

void indexing::recovery(string query)
{
  string normalized_query = this->normalize(query);

  if (this->index.find(normalized_query) != this->index.end())
  {
    cout << "Palavra encontrada!" << endl;
    cout << "Arquivos que contém a palavra: " << normalized_query << endl;

    for (auto it = this->index[normalized_query].begin(); it != this->index[normalized_query].end(); it++)
    {
      cout << *it << endl;
    }
  }
  else
  {
    cout << "Palavra não encontrada!" << endl;
  }
}