#ifndef _INDEXING_H_
#define _INDEXING_H_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

class indexing
{
private:
  map<string, set<string>> index;

public:
  indexing();
  ~indexing();

  set<string> read_directory(const string &);
  void read_files(const string &);

  void insert(string, string);
  map<string, set<string>> get_index();

  string normalize(string);

  void recovery(vector<string>);
};

#endif