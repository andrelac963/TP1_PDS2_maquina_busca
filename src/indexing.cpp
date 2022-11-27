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

void indexing::recovery(vector<string> query)
{
  set<string> normalized_query;
  string aux;

  for (int i = 0; i < query.size(); i++)
  {
    aux = this->normalize(query[i]);
    if (aux != "")
    {
      normalized_query.insert(aux);
    }
  }

  map<string, int> relevant_files;

  for (auto it = this->index.begin(); it != this->index.end(); it++)
  {
    if (normalized_query.find(it->first) != normalized_query.end())
    {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
      {
        relevant_files[*it2]++;
      }
    }
  }

  if (relevant_files.size() == 0)
  {
    cout << "\nNenhum documento encontrado!" << endl;
  }
  else
  {
    set<pair<int, string>> ordered_files;

    for (auto it = relevant_files.begin(); it != relevant_files.end(); it++)
    {
      ordered_files.insert(make_pair(it->second, it->first));
    }

    cout << "\nDocumentos encontrados:" << endl;

    for (auto it = ordered_files.rbegin(); it != ordered_files.rend(); it++)
    {
      cout << it->second << " - " << it->first << " ocorrências" << endl;
    }
  }
}