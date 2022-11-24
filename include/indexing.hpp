#ifndef _INDEXING_H_
#define _INDEXING_H_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class indexing
{
private:
  map<string, set<string>> index;

  void insert(string, string);
  string normalize(string);

public:
  indexing();
  ~indexing();

  void recovery(string);
};

#endif