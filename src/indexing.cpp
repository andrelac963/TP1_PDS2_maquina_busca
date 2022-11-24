#include "indexing.hpp"

indexing::indexing()
{
  fstream file;
  string word, filename;
  int i = 1;

  do
  {
    filename = "d" + to_string(i) + ".txt";
    cout << filename << endl;
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

void indexing::insert(string word, string file)
{
  string normalized_word = this->normalize(word);
  this->index[normalized_word].insert(file);
}

string indexing::normalize(string word)
{
  string normalized_word = "", aux = "";

  for (int i = 0; i < word.length(); i++)
  {
    aux = tolower(word[i]);

    if (isalpha(aux[0]))
    {
      normalized_word += aux[0];
    }
  }

  return normalized_word;
}

void indexing::print()
{
  for (auto it = this->index.begin(); it != this->index.end(); it++)
  {
    cout << it->first << ": ";
    for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      cout << *it2 << " ";
    }
    cout << endl;
  }
}