#ifndef _INDEXING_H_
#define _INDEXING_H_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class indexing
{
private:
  map<string, set<string>> index;

  void insert(string, string);

public:
  indexing();
  ~indexing();

  string normalize(string);
  void print();
};

#endif