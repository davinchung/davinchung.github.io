#include <iostream>
#include <vector>
#include "decodeC24.cc"
using namespace std;


int main() {
  cout <<"Enter 24 length binary word: ";
  <vector<int> > word(24,0);
  int ind = 0;
  while(ind < 24) {
    cin>>word[ind];
    ind++;
  }
  cout<<"Decoding... "<< endl;
  <vector<int> > correct;
  correct = decodeC24(word);
  cout<<"Corrected to: ";
  for (int i = 0; i < 24; i++){
    cout<<correct[i]<<" ";
  }
  cout << endl;
  return;
}
  
