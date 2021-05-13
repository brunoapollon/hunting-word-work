#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;

struct mPair {
   bool marked;
   char letter;
};

class matrix {
   mPair *data;
   int ncols, nrows; 
   list<string> words;
public:
   void reset();
   matrix(int, int,list<string>&);
   void atribuir(mPair* mat);
   mPair& cell(int, int);
   void save(string); 
   ~matrix();
};