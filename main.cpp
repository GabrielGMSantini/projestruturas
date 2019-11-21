#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
typedef struct produto{
	string codigo = "     ";
	string descricao = "                    ";
	int valor;
	int peso;
}produto;

typedef struct {
	produto prods[100];
	int valor=0;
	int peso=0;
	int n=0;//quantidade de produtos em prods 
}lista_prod;

typedef produto queue_element;

#include "QueueCF.h"

int stoi(string s){
	int n;
	char aux[s.length()] ;
	strcpy(aux, s.c_str());
	sscanf(aux, "%d", &n);
	return n;
}

void printqueue(Queue Q){
	produto x;
  	while(!isEmptyQ(Q)){
  		x= eliminate(Q);
  		cout<<x.codigo<<" "<<x.descricao<<" "<<x.valor<<" "<<x.peso<<"\n";
  }
}

void calc_lista(Queue allprods,lista_prod& prod_atual, lista_prod& principal,int capacidade){
	while(!isEmptyQ(allprods)){
		produto p = eliminate(allprods);
		printqueue(allprods);
		int pesoaux = prod_atual.peso + p.peso;
		if(pesoaux<capacidade){
			prod_atual.peso =pesoaux;
			prod_atual.valor+=p.valor;
			prod_atual.prods[prod_atual.n] = p;
			prod_atual.n++;
			calc_lista(allprods,prod_atual,principal,capacidade);
		}
		if(prod_atual.valor > principal.valor)
			principal = prod_atual;
		prod_atual.n--;
		prod_atual.valor-=prod_atual.prods[prod_atual.n].valor;
		prod_atual.peso-=prod_atual.prods[prod_atual.n].peso;
		for(int i=0;i<principal.n;i++){
			cout<<principal.prods[i].descricao<<"\n";
		}
	}
	return;
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
	//Para leitura do arquivo
  string line;
  string tamanhoString="   ";
  string capacidadestring="                                                                  ";
  int tamanho;//quantos produtos tem no arquivo
  int capacidade;//qual a capacidade do conteiner
  
  //Escolha do arquivo 
  Queue fila;
  initQueue(fila);
  cout<<"Digite o nome do arquivo onde estao os produtos(este arquivo deve estar contido no projeto criado no Devc++)\n";
  char filename[100];
  cin>>filename;
  ifstream myfile (filename);
  
  //Pegar o valor do tamanho e da capacidade apartir da string
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
	
	//Colocar os produtos do arquivo na fila criada
	while(tamanho>0){
		getline (myfile,line);
		produto p;
		p = linetoprod(line);
		
		insert(fila,p);
		
		tamanho--;
	}
	//printar o conteudo da fila para debugar
	printqueue(fila);
	lista_prod atual;
	lista_prod principal;
	calc_lista(fila,atual,principal,capacidade);
	int r;
	for(r=0;r<principal.n;r++)
		cout<<principal.prods[r].codigo<<"\n";
  }
 
  		
	
  else
  cout<<"Vish, deu nao...";
	return 0;
}
