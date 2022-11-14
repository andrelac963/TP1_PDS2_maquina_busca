#include <iostream>
#include <string>

int main()
{
  std::string s;

  std::cout << "Insira as palavras que você deseja pesquisar: " << std::endl;

  std::cin >> s;

  std::cout << "A palavra que você digitou foi: " << s << std::endl;

  return 0;
}