#include "puzzle.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
   list<string> ls;
   ls.push_front("Karol");
   ls.push_front("sai");
   ls.push_front("do_bbb");
   ls.push_front("se_e_pa_tombar");
   ls.push_front("tombe");
   matrix m(30, 30, ls);
   createPuzzle(30, 30, ls, "gabarito.txt", m);
   solvePuzzle(ls, "gabarito.txt", "resolvido.txt", m);
   return 0;
}
