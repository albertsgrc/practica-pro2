#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

typedef  vector<char> fila;

bool doesexist (string name) {
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }   
}

bool areequal(string filename1, string filename2){
  ifstream if1;
  if1.open (filename1.c_str(), ifstream::in);
  ifstream if2;
  if2.open (filename2.c_str(), ifstream::in);
  string s1, s2;
  while (if1>>s1){
    if (!(if2>>s2)) return false;
    if (s1!=s2) return false;
  }
  if ((if2>>s2)) return false;
  return true;
}


int main(){
  int n; //Nombre de jugadors
  int m; //Nombre de txt
  cin >> n >> m;
  fila A (n, '0'); 
  vector< fila > pat (m, A);
  for (int i=0; i<m; ++i){
    char patro = 'A';
    for (int j=0; j<n; ++j){
     stringstream ss;
     string aux;
     ss<<"OUTPUT/"<<j+1<<'/'<<i+1<<".txt";
     aux=ss.str();
      if (doesexist ( aux  ) ) {
	bool found =  false;
	int t=0;
	while (not found and t<j){
	  stringstream ss1, ss2;
	  ss1<<"OUTPUT/"<<j+1<<'/'<<i+1<<".txt";
	  ss2<<"OUTPUT/"<<t+1<<'/'<<i+1<<".txt";
          aux=ss1.str();
	  string aux2;
          aux2=ss2.str();
	  if ( areequal (aux, aux2) ) found = true;
	  else ++t;
	}
	if (found) pat[i][j]=pat[i][t];
	else{
	  pat[i][j]=patro;
	  ++patro;
	}
      } else pat[i][j]= 'W';
      
    }
  }
  //sortida
    cout << "      ";
    for (int j=0; j<n; ++j){
      cout << " " << j+1;
    }
    cout << endl;
    for (int i=0; i<m; ++i){
      if (i < 9) cout << "0";
      cout << i+1 << ".txt" ;
      for (int j=0; j<n; ++j){
	cout << " " << pat[i][j];
      }
      cout << endl;
    }
}
