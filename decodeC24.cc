#include <iostream>
#include <string>
#include <vector>
using namespace std;

//CO331
//Decoding algorithm for C24-a (24,12)-code with distance 8
//G=[I_12|B] and H=[B|I_12] are both generator matrices and
//parity-check matrices for C24

//input r: received word/vector of length 24
//output: corrected code or reject
vector<int> syndrome(int B[][], int I[][], vector<int> r){
  
  vector<int> s(row*2, 0);
  for (int i = 0; i < row; i++) {
    for (int j =0; j < col; j++) {
      s[i] = s[i] + B[i][j]*r[j] + I[i][j]*r[j+12];
    }
    s[i] = s[i] % 2;
  }
  return s;
}

int weight(vector<int> s){

  int ws = 0;
  for (int i = 0; i < row*2; i++) {
    ws+=s1[i];
  }
  return ws;
}

vector<int> decodeC24(vector<int> r) {
  const int row = 12;
  const int col = 12;
  int B[row][col];
  int I[row][col] = {0};
  
  //Defining matrix B
  B[0] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  B[1] = {1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0};
  B[2] = {1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
  B[3] = {1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1};
  B[4] = {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0};
  B[5] = {1 1 1 0 0 0 1 0 1 1 0 1};
  B[6] = {1 1 0 0 0 1 0 1 1 0 1 1};
  B[7] = {1 0 0 0 1 0 1 1 0 1 1 1};
  B[8] = [1 0 0 1 0 1 1 0 1 1 1 0];
  B[9] = [1 0 1 0 1 1 0 1 1 1 0 0];
  B[10]= [1 1 0 1 1 0 1 1 1 0 0 0];
  B[11]= [1 0 1 1 0 1 1 1 0 0 0 1];

  //I = vector<vector<int> >(col, vector<int>(row,0));
  for(unsigned int t = 0; t < col; t++) {
    I[t][t] = 1;
  }
 
  //Computing syndrome
  vector<int> s1;
  s1 = syndrome(B,I,r);
  //weight of syndrome
 int ws = weight(s1);
 
  if (ws == 0) return r;
  if (ws <= 3) {
    for (int i = 0; i < 24; i++) {
      r[i] = r[i] + s[i];
      r[i] = r[i] % 2;
    }
    return r;
  }

  //Compare s with the rows of B
  int diff = 0;
  <vector<int> > pos;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (B[i][j]==s[j]) pos.pushback(j);
      if (I[i][j]==s[j+12]) pos.pushback(j+12);
    }
    diff = pos.size();
    if (diff <= 2) {
      r[pos[0]] = (r[pos[0]]+1) % 2;
      if (diff == 2) r[pos[1]] = (r[pos[1]]+1) % 2;
      r[i+12] = (r[i+12]+1) % 2;
      return r;
    pos.empty();
    diff = 0;
    }
  }

  //Computing syndrome
  vector<int> s2(row*2, 0);
  for (int i = 0; i < row; i++) {
    for (int j =0; j < col; j++) {
      s2[i] = s2[i] + B[i][j+12]*r[j] + I[i][j]*r[j];
    }
    s2[i] = s2[i] % 2;
  }

  //weight of syndrome
  for (int i = 0; i < row*2; i++) {
    ws+=s2[i];
  }
 
  if (ws == 0) return r;
  if (ws <= 3) {
    for (int i = 0; i < 24; i++) {
      r[i] = r[i] + s2[i];
      r[i] = r[i] % 2;
    }
    return r;
  }

  //Compare s with the rows of B
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (B[i][j]==s[j]) pos.pushback(j);
      if (I[i][j]==s2[j+12]) pos.pushback(j+12);
    }
    diff = pos.size();
    if (diff <= 2) {
      r[pos[0]] = (r[pos[0]]+1) % 2;
      if (diff == 2) r[pos[1]] = (r[pos[1]]+1) % 2;
      r[i+12] = (r[i+12]+1) % 2;
      return r;
    pos.empty();
    diff = 0;
    }
  }
  
  cerr<<"REJECT WORD"<<endl;
}

