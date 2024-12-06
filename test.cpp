#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <string>
#include <iostream>
#include <functional>
#include "File.hpp"
#include "FileAVL.hpp"
#include "FileTrie.hpp"

using namespace std;


int main()
{
  FileTrie fileTrie;

  File* file1 = new File("avl.txt");
  File* file2 = new File("avltree.txt");
  File* file3 = new File("avltree2.txt");
  File* file4 = new File("avltree3.txt");
  File* file5 = new File("avltree4.jpg");

  fileTrie.addFile(file1);
  fileTrie.addFile(file2);
  fileTrie.addFile(file3);
  fileTrie.addFile(file4);
  fileTrie.addFile(file5);

  std::unordered_set<File*> res = fileTrie.getFilesWithPrefix("av");

  for (auto it = res.begin(); it != res.end(); ++it)
  {
    cout << **it << endl;
  }
  delete file1;
  delete file2;
  delete file3;
  delete file4;
  delete file5;

  return 0;
}