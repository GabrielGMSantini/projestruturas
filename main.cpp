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

int max(int a, int b) { return (a > b)? a : b; }
// Returns the maximum value that can be put in a knapsack of capacity W
int calcknapSack(int W, int wt[], int val[], int n,int (&pos)[100]) 
{ 
    int i, w; 
   int** K = new int*[n+1];
		for(int m = 0; m < n+1; m++)
    		K[m] = new int[W+1];	
    // Build table K[][] in bottom up manner 
    for (i = 0; i <= n; i++) { 
        for (w = 0; w <= W; w++) { 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (wt[i - 1] <= w) 
                K[i][w] = max(val[i - 1] +  
                    K[i - 1][w - wt[i - 1]], K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    } 
//  	 for (int d = 0; d <= n; d++) { 
//        for (int e = 0; e <= W; e++) { 
//            cout<<K[d][e]<<" ";
//    	}
//    	cout<<"\n";
//    } 
//    system("pause");
    // stores the result of Knapsack 
    int res = K[n][W];
    int v=0;
    w = W; 
    for (i = n; i > 0 && res > 0; i--) { 
          
        // either the result comes from the top 
        // (K[i-1][w]) or from (val[i-1] + K[i-1] 
        // [w-wt[i-1]]) as in Knapsack table. If 
        // it comes from the latter one/ it means  
        // the item is included. 
        if (res == K[i - 1][w])  
            continue;         
        else { 
  
            // This item is included. 
           		pos[v]=i-1;
           		v++;
              
            // Since this weight is included its  
            // value is deducted 
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
        } 
    }
	return v; 
} 

int calc_valor(Queue Q){
	int soma=0;
	while(!isEmptyQ(Q)){
		produto Aux = eliminate(Q);
		soma+=Aux.valor;
	}
	return soma;
}

int calc_peso(Queue Q){
	int soma=0;
	while(!isEmptyQ(Q)){
		produto Aux = eliminate(Q);
		soma+=Aux.peso;
	}
	return soma;
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
	int n=tamanho;
	int w[100];
	int v[100];
	int pos[100];
	i=0;
	produto prods[100];
	//Colocar os produtos do arquivo na fila criada
	while(tamanho>0){
		getline (myfile,line);
		produto p;
		p = linetoprod(line);
		w[i]=p.peso;
		v[i]=p.valor;
		prods[i]=p;
		i++;
		tamanho--;
	}
	
	int x = calcknapSack(capacidade,w,v,n,pos);
	for(;x>0;x--){
		insert(fila,prods[pos[x-1]]);
	}
	system("cls");
	printqueue(fila);
	cout<<"\n\n\tValor Total: USD "<<calc_valor(fila)<<"\n\tPeso Total: "<<calc_peso(fila)<<"g\n\n";
  }	
  else
  cout<<"Vish, deu nao...";
	return 0;
}
