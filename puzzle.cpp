#include <list>
#include <string>
#include "puzzle.h"

using namespace std;
char direcaoPalavra(){
   char direcao[] = {'d','e','c','b'};
   return direcao[rand() % 4];
}
char letraAleatoria(){
   char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
   int let = rand() % 26;
   return letras[let];
}
bool rangeMat(int col, int row, int quantCar, int ncols, int nrows, char dir){
   bool retorno;
   switch (dir){
   case 'c':
      retorno = ((row - quantCar) >= 0);
      break;
   case 'b':
      retorno = ((row + quantCar) < nrows);
      break;
   case 'e':
      retorno = ((col - quantCar) >= 0);
      break;
   case 'd':
      retorno = ((col + quantCar) < ncols);
      break;
   default:
      break;
   }
   return retorno;
}
int contaCaracteres(string pal){
   int cont = 0;
   for (int i = 0; i < 1000; i++){ 
      if (pal[i]){
         cont++;
      }
      else{
         break;
      }
   }
   return cont;
}
bool celulaMarcada(mPair matriz[], int col, int row, int ncols){
   return matriz[ncols * row + col].marked;
}
bool celulasLivres(mPair mat[], int col, int row, int ncols, char dir, int cont){
   bool retorno;
   switch (dir){
   case 'c':
      for (int i = row; cont > 0; i--, cont--){
         if (mat[ncols * i + col].marked == 1)
         {
            retorno = true;
            break;
         }
         else
         {
            retorno = false;
         }
      }
   break;
   case 'b':
      for (int i = row; cont > 0; i++, cont--){
         if (mat[ncols * i + col].marked == 1)
         {
            retorno = true;
            break;
         }
         else
         {
            retorno = false;
         }
      }
   break;
   case 'e':
      for (int i = col; cont > 0; i--, cont--){
         if (mat[ncols * row + i].marked == 1)
         {
            retorno = true;
            break;
         }
         else
         {
            retorno = false;
         }
      }
   break;
   case 'd':
      for (int i = col; cont > 0; i++, cont--){
         if (mat[ncols * row + i].marked == 1)
         {
            retorno = true;
            break;
         }
         else
         {
            retorno = false;
         }
         
      }
   break;
   default:
      retorno = true;
      break;
   }
   return retorno;
}
void createPuzzle(int ncols, int nrows, list<string> &words, string matrixFile, matrix& m) {
   list<string> ls = words;
   list<string>::iterator i;
   string word;
   char direcao;
   int cont = 0, col, row, cont2 = 0, tentativas = 0;
   mPair *mat = new mPair[ncols * nrows];
   for (int i = 0; i < nrows; i++){
      for (int j = 0; j < ncols; j++){
         mat[ncols * j + i].letter = letraAleatoria();
         mat[ncols * j + i].marked = 0;
      }
   }
   for (i =  words.begin(); i != words.end(); ++i){
      word = ls.front();
      ls.pop_front();
      cont = contaCaracteres(word);
      while (1 != 2){ 
         col = rand() % ncols; 
         row = rand() % nrows; 
         direcao = direcaoPalavra();
         tentativas++;
         if (!rangeMat(col, row, (cont - 1), ncols, nrows, direcao)){
            continue;
         }
         if (celulaMarcada(mat, col, row, ncols))
         {
            continue;
         }
         if (celulasLivres(mat, col, row, ncols, direcao, cont))
         {
            continue;
         }
         if (tentativas > (ncols * nrows) / 2)
         {
            break;
         }
         
         if (direcao == 'd'){
            for (int i = col; cont > 0; i++, cont--){
               mat[ncols * row + i].letter = word[cont2];
               mat[ncols * row + i].marked = 1;
               cont2++;
            }
            cont2 = 0;
         }
         else if (direcao == 'e'){
            for (int i = col; cont > 0; i--, cont--){
               mat[ncols * row + i].letter = word[cont2];
               mat[ncols * row + i].marked = 1;
               cont2++;
            }
            cont2 = 0;
         }
         else if(direcao == 'c'){
            for (int i = row; cont > 0; i--, cont--){
               mat[ncols * i + col].letter = word[cont2];
               mat[ncols * i + col].marked = 1;
               cont2++;
            }
            cont2 = 0;
         }
         else{
            for (int i = row; cont > 0; i++, cont--){
               mat[ncols * i + col].letter = word[cont2];
               mat[ncols * i + col].marked = 1;
               cont2++;
            }
            cont2 = 0;
         }
         break;
      }
      cont = 0;
   }
   m.atribuir(mat);
   m.save(matrixFile.c_str());
}
bool palavraEncontrada(mPair mat[], int tamanhoPal, char dir, int col, int row, string palavra, int tamanhoMat){
   int cont = 0, posicaoLetra = 0, tamanhoPalAux = tamanhoPal;
   bool retorno = false;
   switch (dir){
   case 'c':
      for (int i = row; tamanhoPalAux > 0; i--, tamanhoPalAux--)
      {
         if (mat[tamanhoMat * i + col].letter == palavra[posicaoLetra])
         {
            cont++;
         }
         posicaoLetra++;
      }
      if (cont == tamanhoPal)
      {
         retorno = true;
      }
   break;
   case 'b':
     for (int i = row; tamanhoPalAux > 0; i++, tamanhoPalAux--)
      {
         if (mat[tamanhoMat * i + col].letter == palavra[posicaoLetra])
         {
            cont++;
         }
         posicaoLetra++;
      }
      if (cont == tamanhoPal)
      {
         retorno = true;
      }
   break;
   case 'e':
      for (int i = col; tamanhoPalAux > 0; i--, tamanhoPalAux--)
      {
         if (mat[tamanhoMat * row + i].letter == palavra[posicaoLetra])
         {
            cont++;
         }
         posicaoLetra++;
      }
      if (cont == tamanhoPal)
      {
         retorno = true;
      }
   break;
   case 'd':
      for (int i = col; tamanhoPalAux > 0; i++, tamanhoPalAux--)
      {
         if (mat[tamanhoMat * row + i].letter == palavra[posicaoLetra])
         {
            cont++;
         }
         posicaoLetra++;
      }
      if (cont == tamanhoPal)
      {
         retorno = true;
      }
   break;
   default:
      retorno = false;
      break;
   }
   return retorno;
}
void solvePuzzle(list<string> &words, string inputFileMatrix,string outputFileMatrix, matrix& m) 
{
   list<string> ls = words;
   list<string>::iterator i;
   string arquivo, word, tamanhoSt, letra;
   int cont = 0, tamanhoMat, posicaoLet = 0, tamanhoPal, col = 0, row = 0;
   ifstream stream(inputFileMatrix.c_str());
   stream >> tamanhoSt;
   tamanhoMat = stoi(tamanhoSt);
   mPair *mat = new mPair[tamanhoMat * tamanhoMat];
   char letras[tamanhoMat * tamanhoMat];
   for (int i = 0; i < tamanhoMat; i++)
      {
         for (int j = 0; j < tamanhoMat; j++)
         {
           stream >> letra;
           stream >> letra;
           stream >> letra;
           letras[tamanhoMat * j + i] = letra[0];
           stream >> letra;
         }
      }
   
   for (int i = 0; i < tamanhoMat; i++)
   {
      for (int j = 0; j < tamanhoMat; j++, posicaoLet++)
      {
         mat[tamanhoMat * i + j].letter = letras[posicaoLet];
         mat[tamanhoMat * i + j].marked = 0;
      }
   }
   stream.close();
   for (i =  words.begin(); i != words.end(); ++i){
      word = ls.front();
      ls.pop_front();
      tamanhoPal = contaCaracteres(word);
      for (int i = 0; i < tamanhoMat; i++)
      {
         for (int j = 0; j < tamanhoMat; j++)
         {
            if (rangeMat(j, i, (tamanhoPal - 1),tamanhoMat, tamanhoMat, 'd'))
            {
               
               if (palavraEncontrada(mat, (tamanhoPal - 1), 'd', j, i, word, tamanhoMat))
               {
                  for (int c = j; tamanhoPal > 0; c++, tamanhoPal--)
                  {
                     mat[tamanhoMat * i + c].marked = 1;
                  }
               }
            }
            if (rangeMat(j, i, (tamanhoPal - 1),tamanhoMat, tamanhoMat, 'e'))
            {
               if (palavraEncontrada(mat, tamanhoPal, 'e', j, i, word, tamanhoMat))
               {
                  for (int c = j; tamanhoPal > 0; c--, tamanhoPal--)
                  {
                     mat[tamanhoMat * i + c].marked = 1;
                  }
               }
            }
            if (rangeMat(j, i, (tamanhoPal - 1),tamanhoMat, tamanhoMat, 'c'))
            {
               if (palavraEncontrada(mat, tamanhoPal, 'c', j, i, word, tamanhoMat))
               {
                  for (int r = i; tamanhoPal > 0; r--, tamanhoPal--)
                  {
                     mat[tamanhoMat * r + j].marked = 1;
                  }
               }
            }
            if (rangeMat(j, i, (tamanhoPal - 1),tamanhoMat, tamanhoMat, 'b'))
            {
               if (palavraEncontrada(mat, tamanhoPal, 'b', j, i, word, tamanhoMat))
               {
                  for (int r = i; tamanhoPal > 0; r++, tamanhoPal--)
                  {
                     mat[tamanhoMat * r + j].marked = 1;
                  }
               }
            }
         }
      }
   }
   m.atribuir(mat);
   m.save(outputFileMatrix.c_str());
}