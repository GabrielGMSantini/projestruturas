
#include <stdlib.h>
#include <stdio.h>

struct no {
elemento info ;
struct no * link;
};
typedef struct no no;


no * criar_vazia()
{
    return NULL;
}


no * novo_no(){
    no* novo;
    novo=(no*)malloc(sizeof(no));
    if(novo==NULL){
        printf("\nErro Alocacao Novo no");
        return NULL;
    }
    return novo;
}



int Inserir_final(no ** pri,elemento x)
{
    no*p,*novo;
    novo=new no();
    p=*pri;
    novo->link=NULL;
    novo->info.codigo=x.codigo;
    novo->info.descricao=x.descricao;
    novo->info.peso=x.peso;
    novo->info.valor=x.valor;
    if(*pri==NULL)
    {
        *pri=novo;
    }
    else{
    while(p!=NULL && p->link!=NULL)
    {
        p=p->link;
    }
    p->link=novo;

    }

	return 0;

}


elemento remover_comeco(no **pri)
{
    no *p,*s;
    s=*pri;
    p=s;
    if(p!=NULL)
    {
        p=p->link;
         *pri=p;
        return s->info;

    }
}

int vazia(no *pri)
{
    if(pri==NULL)
    {
        return 1;
    }
    return 0;
}









