#include "indexing.hpp"

indexing::indexing()
{
}

indexing::~indexing()
{
}

set<string> indexing::read_directory(const string &name)
{
  DIR *dirp = opendir(name.c_str());
  if (dirp == NULL)
  {
    return set<string>();
  }

  struct dirent *dp;
  set<string> files;

  while ((dp = readdir(dirp)) != NULL)
  {
    if (dp->d_name[0] != '.')
      files.insert(dp->d_name);
  }
  closedir(dirp);

  return files;
}

void indexing::read_files(const string &name)
{
  set<string> files = read_directory(name);
  fstream file;
  string word, filename;

  for (auto it = files.begin(); it != files.end(); it++)
  {
    filename = *it;
    file.open(name + filename);
    while (file >> word)
    {
      this->insert(word, filename);
    }
    file.close();
  }
}

void indexing::insert(string word, string filename)
{
  string normalized_word = this->normalize(word);
  if (normalized_word != "")
  {
    this->index[normalized_word].insert(filename);
  }
}

map<string, set<string>> indexing::get_index()
{
  return this->index;
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

bool conditional_sort(pair<string, int> &a, pair<string, int> &b)
{
  return a.second > b.second;
}

vector<pair<string, int>> indexing::recovery(vector<string> query)
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

  vector<pair<string, int>> ordered_files;

  for (auto it = relevant_files.begin(); it != relevant_files.end(); it++)
  {
    ordered_files.push_back(make_pair(it->first, it->second));
  }

  sort(ordered_files.begin(), ordered_files.end(), conditional_sort);

  return ordered_files;
}

void indexing::print_ordered_files(vector<string> query)
{
  vector<pair<string, int>> ordered_files = this->recovery(query);

  if (ordered_files.size() == 0)
  {
    cout << "\nNenhum arquivo encontrado!" << endl;
  }
  else
  {
    cout << "\nArquivos encontrados:" << endl;
    for (int i = 0; i < ordered_files.size(); i++)
    {
      cout << ordered_files[i].first << " - " << ordered_files[i].second << " ocorrências" << endl;
    }
  }
}