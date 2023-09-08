#include <stdio.h>
#include <stdlib.h>
/*lista duplamente encadeada com funcoes para adicionar elementos, 
buscar na lista, imprimir na ordem normal ou inversa, remover elementos
da lista, concatenar 2 listas, copiar uma lista encadeada para um ponteiro*/
struct dados{
	int value;
	struct dados* next;
	struct dados* ant;
};
typedef struct dados dados;
dados* buscaDL(dados* L, int y){//retorna o primeiro endere�o onde ha este valor y
	dados* adress=L;
	while(adress!=NULL && adress->value==y){
		adress=adress->next;
	}
	if(adress==NULL){
		return NULL;
	}
	else{
		return adress;
	}
}
dados* addDL(dados* L, int x){
	dados* novo=NULL;
	novo=(dados*)malloc(sizeof(dados));//aloca
	novo->next=L;//aponta para o n� cabe�� anterior
	novo->value=x;
	novo->ant=NULL;
	if(novo->next==NULL){//apenas o primeiro sera inicializado assim
		novo->ant=NULL;
		return novo;//sera guardodo no ponteiro para o head da lista
	}
	L->ant=novo;//o n� anterior aponta para novo n�
	return novo;
}
void printDL(dados* L){//imprime na ordem normal
	dados* p=L;
	while(p!=NULL){
		printf("endereco: %x\n", p);
		printf("proximo: %x\n", p->next);
		printf("anterior: %x\n", p->ant);
		printf("value: %d\n\n", p->value);
		p=p->next;
	}
	system("pause");
	system("cls");
}
void printDL_(dados* L){//imprime na ordem inversa
	dados* q=L;
	while(q->next!=NULL){//achou o ultimo elemento
		q=q->next;
	}
	while(q!=NULL){
		printf("endereco: %x\n", q);
		printf("proximo: %x\n", q->next);
		printf("anterior: %x\n", q->ant);
		printf("value: %d\n\n", q->value);
		q=q->ant;
	}
	system("pause");
	system("cls");	
}
dados* delDL(dados*L, int x){//deleta o primeiro a ser encontrado
	dados* p=buscaDL(L, x);
	if(p==NULL){//nao esta na lista
		return L;
	}
	if(p==L){//esta no primeiro n� da lista
		L=L->next;
		free(p);
		return L;
	}
	else{//entre dois n�s
		p->ant->next=p->next;
		free(p);
		return L;
	}
}

int main(){
	dados* Head=NULL;
	Head=addDL(Head, 1);
	Head=addDL(Head, 2);
	Head=addDL(Head, 3);
	Head=addDL(Head, 4);
	Head=addDL(Head, 5);
	printDL(Head);
	printDL_(Head);
	return 0;
}
