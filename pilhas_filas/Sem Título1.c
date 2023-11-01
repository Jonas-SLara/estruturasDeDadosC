#include <stdio.h>
#include <stdlib.h>

struct pilha{
	int info;
	struct pilha *cima;
};
typedef struct pilha pilha;

pilha *push(pilha *base, int num){
	pilha *novo=(pilha*)malloc(sizeof(pilha));
	novo->info=num;
	novo->cima=NULL;
	if(base==NULL){
		base=novo;
		return base;
	}
	else{
		pilha *topo=base;
		while(topo->cima!=NULL){
			topo=topo->cima;
		}
		topo->cima=novo;
		return base;
	}
}

pilha *busca(pilha *base, int x){
	pilha *temp=base;
	if(temp==NULL){
			return NULL;
	}
	else if(temp->info==x){
		return temp;
	}
	return busca(base->cima, x);
}

void add(pilha **base, int num){//não permite inserir valores repetidos
	if(busca(*base, num)==NULL){
		*base=push(*base, num);
	}
}

void print(pilha *base){
	pilha *temp=base;
	while(temp!=NULL){
		printf("%d\n", temp->info);
		temp=temp->cima;
	}
}

pilha *inv(pilha *b1){
	if(b1!=NULL){
		pilha *top=b1, *pre=NULL;
		while(top->cima!=NULL){
			pre=top;
			top=top->cima;
		}
		if(top!=b1)
			pre->cima=NULL;
		if(top==b1)
			b1=NULL;
		top->cima=inv(b1);
		return top;
	}
	else{
		return NULL;
	}
}









int main(){
	pilha *B=NULL;
	add(&B, 10);
	add(&B, 20);
	add(&B, 30);
	B=inv(B);
	print(B);
	return 0;
}
