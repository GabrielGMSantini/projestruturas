#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
typedef struct produto{
	string codigo = "      ";
	string descricao = "                    ";
	int valor;
	int peso;
}produto;

int stoi(string s){
	int n;
	char aux[s.length()] ;
	strcpy(aux, s.c_str());
	sscanf(aux, "%d", &n);
	return n;
}

produto linetoprod(string s){
	produto p;
	string peso="               ";
	string valor="              ";
	int i=0;
	for(i;s[i]!=',';i++){
		p.codigo[i]=s[i];
	}
	i++;
	int j,k,l;
	for(j=0;s[i+j]!=',';j++){
		p.descricao[j]=s[i+j];
	}
	j++;
	for(k=0;s[i+j+k] != ',';k++){
		valor[k]=s[i+j+k];
	}
	k++;
	for(l=0;i+j+k+l<s.length();l++){
		peso[l]=s[i+j+k+l];
	}
	p.valor=stoi(valor);
	p.peso = stoi(peso);
	return p;
}
int main() {
  string line;
  string tamanhoString="   ";
  string capacidadestring="                                                                  ";
  int tamanho;
  int capacidade;
  produto produtos[100];
  cout<<"Digite o nome do arquivo onde estao os produtos(este arquivo deve estar contido no projeto criado no Devc++)\n";
  char filename[100];
  cin>>filename;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    getline (myfile,line);
    int i=0;
    while(line[i]!= ' '){
    	tamanhoString[i] =line[i];
    	i++;
		}
	i+=1;
	while(i<line.length()){
		capacidadestring[i]=line[i];
		i++;
	}
	tamanho = stoi(tamanhoString);
	capacidade = stoi(capacidadestring);
	int j =0;
	while(tamanho>0){
		getline (myfile,line);
		produtos[j]=linetoprod(line);
		cout<<produtos[j].codigo<<" "<<produtos[j].descricao<<" "<<produtos[j].valor<< " "<<produtos[j].peso<<'\n';
		j++;
		tamanho--;
	}
	
  }
	
  else
	return 0;
}
