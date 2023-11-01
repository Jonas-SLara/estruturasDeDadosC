#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include <conio.h>
//cada tela possui aplicativos e o mesmo n�o pode estar em 2+ telas
struct app{
	char nome[20];
	struct app *next;
	struct app *bef;
};

typedef struct app app;

struct tela{
	int cont; //contador de apps em cada tela, max=6
	int info; //numero da tela	
	struct tela *next;
	struct tela *bef;
	app *L;	//ponteiro para o n� cabe�� da lista de aplicativos
};

typedef struct tela tela;

app *get_last_app(app *L){//recursividade, importante para depois inserir elementos no final da lista
	app *A =L;
	if(A->next==NULL){
		return A;
	}
	else{
		A=get_last_app(A->next);
		return A;
	}
}

tela *get_last_tela(tela *H){//antes de achar o ultimo app � preciso achar a ultima tela criada
	tela *P=H;
	if(P->next==NULL){
		return P;
	}
	P=get_last_tela(P->next);
	return P;	
}

app *get_app(app *q, char nome[20]){
//onde Q=P->L, P =ponteiro da tela onde h� o elemento achado pela busca
	if(strcmp(q->nome, nome)==0 || q==NULL){
		return q;
	}
	q=get_app(q->next, nome);
	return q;
}

tela *busca(tela *H, char nome[20]){//retorna NULL se n�o h� elemento com este nome, se h� retorna a tela onde esta
	tela *p=H;
	if(p==NULL){//n�o h� elementos
		return p;
	}
	else{
		app *a=p->L;
		while(a!=NULL && strcmp(a->nome, nome)!=0){
			a=a->next;
		}
		if(a!=NULL){//achou retorna o endere�o da tela onde ele esta
			return p; //p!=NULL
		}
		else{
			p=busca(p->next, nome);
			return p;
		}
	}
}

app *add(app *P, char nome[20]){//P � o n� cabe�a da lista da ultima tela criada
	app *novo=(app*)malloc(sizeof(app));
	novo->next=NULL;//ira inserir no final
	strcpy(novo->nome, nome);
	if(P==NULL){//caso a tela principal ou uma nova esta vazia
		novo->bef=NULL;
		printf("--> foi carregado um app %s\n", novo->nome);
		return novo;
	}
	else{//insere no final da lista
		app *q=P;
		q=get_last_app(q);//obtem o endere�o do ultimo app na tela em que esta
		novo->bef=q;
		q->next=novo;
		printf("--> foi carregado um app %s\n", novo->nome);
		return P;
	}
}

tela *new_tela(tela *P){//P aponta para a ultima tela criada
	tela *novo=(tela*)malloc(sizeof(tela));
	//etapas para a cria��o de uma tela antes de adicionar o 1 app
	novo->next=NULL;//ficara no final
	novo->bef=P;
	P->next=novo;
	novo->cont=0; 
	novo->L=NULL;//inicia em 0apps
	novo->info=P->info+1; //permite a ordem crescente dos elementos
	return novo;
}

tela *instala(tela *H, char op){//na ultima tela criada, insere no final at� quiser que pare
	tela *q;
	if(op=='i'){
		printf("instalando\n");
		printf("**************************************\n");
		char nome[20];
		printf("nome do app: ");
		fflush(stdin);
		gets(nome);
		strlwr(nome);//poe tudo em letras minusculas
		q = busca(H, nome);//se ha um app ja instalado retorna !=NULL
		
		if(q!=NULL){
			printf("\nelemento repetido na tela %d\n", q->info);
		}
		else{//continuar procedimento de instala��o
			q=H;//inicializar q para o algoritmo de inser��o na pilha
			q=get_last_tela(q);//obtem a ultima tela criada
			
			//q->L forma de obter o HEAD da lista de apps da tela sem uma nova variavel
			if(q->cont==6){	//testa se esta tela j� esta cheia, cria uma nova
				q=new_tela(q);
				q->L=add(q->L, nome);//add controla cada caso de inser��o, buscando a ultima posi��o
				q->cont++;
				printf("--> criado tela %d\n", q->info);
			}
			else{
				q->L=add(q->L, nome);
				q->cont++;//incrementa 
			}
		}
		printf("continuar i(instalar mais) !i(parar)");
		fflush(stdin);
		scanf("%c", &op);
		system("cls");
		instala(H, op);
		return H;
	}
	return H;
}

tela *inicializar(tela *H){ //aloca a tela inicial na memoria + lista com alguns aplicativos
	H =(tela*)malloc(sizeof(tela));
	H->L=NULL;
	H->next=NULL;
	H->bef=NULL;
	H->info=1;
	char app1[20];
	char app2[20];
	char app3[20];
	char app4[20];
	char app5[20];
	strcpy(app1, "eclipse");
	strcpy(app2, "calculadora");
	strcpy(app3, "calendario");
	strcpy(app4, "duolingo");
	strcpy(app5, "config");
	H->L=add(H->L, app1);
	H->L=add(H->L, app2);
	H->L=add(H->L, app3);
	H->L=add(H->L, app4);
	H->L=add(H->L, app5);
	H->cont=5;
	getch();
	system("cls");
	return H;
}

void view(app *P){//P � o n� HEAD de uma lista de apps em uma tela
	app *a = P;
	int n=0;
	if(a!=NULL){
		do{
			printf("| %s |\t", a->nome);
			n++;
			a=a->next;
		}while(a!=NULL && n<2);
		printf("\n----------------------------------\n");
		view(a);
	}
}

tela *go(tela *P, char op){//fun��o que interpreta para qual tela migrar o ponteiro P
	if((P->next==NULL && op=='n') || (P->bef==NULL && op=='b')){
		printf("esta tela ainda n�o existe\n");
		system("pause");
		system("cls");
		return P; //volta para a tela de onde partiu
	}
	P= (op=='n')? P->next:P->bef;//se n�o for n � b, n�o ha uma outra op��o
	return P;
}

char operar(){//comando de opera��es//
	printf("\n**************************************");
	printf("\n<<<<----b         n---->>>>\n");
	printf("d(deletar)   i(instalar)  p(parar)  e(executa)\n");
	char option;
	do{//valida��o do caractere
		fflush(stdin);
		scanf("%c", &option);
	}while(option != 'b' && option!='p'&& option!='i' 
	&& option!='d' && option!='n' && option!='e');
	system("cls");
	return option;
}

app *del(app*origem, app* HEAD){
	if(origem->bef==NULL && origem->next==NULL){//ficara vazia
		free(origem);
		return NULL;
	}
	else if(origem->bef==NULL){//se trata do primeiro elemento
		HEAD=origem->next;
		HEAD->bef=NULL;
		free(origem);
		return HEAD;
	}
	else if(origem->next==NULL){//ultimo elemento
		origem->bef->next=NULL;//p�nultimo aponta para NULL
		free(origem);
		return HEAD;
	}
	else{//elemento com 2 adjacentes na lista
		origem->bef->next=origem->next;
		origem->next->bef=origem->bef;
		free(origem);
		return HEAD;
	}
}

void mov(tela *P){
	if(P->next!=NULL){//se esta n�o � a ultima tela mover elementos
		tela *T=P;
		app *last=get_last_app(T->L);	
		last->next=T->next->L;//apontar para o primeiro da proxima tela	
		T->next->L->bef=last;//vice versa
		if(T->next->L->next==NULL){
		//se n�o h� ninguem depois, ent�o estamos na ultima tela que n�o � a main, mover e deleta-la
			free(T->next);
			T->next=NULL;
			T->cont++;
			//acaba aqui e ela n�o chama mais a si mesmo
		}
		else{
			T->next->L=T->next->L->next;//o n� cabe�a da outra tela vira o segundo
			T->next->L->bef=NULL;//este n� cabe�a agora n�o aponta mais para o seu anterior
			last->next->next=NULL;//agora limpa o campo next deste ultimo
			T->next->cont--;//diminui um app da proxima
			T->cont++;//aumenta um app de onde esta, de onde come�ou
			T=T->next;//tela seguinte
			mov(T);//recursividade
		}	
	}	
}

tela* desinstala(tela *H, char op){//permite desinstalar enquanto o usuario querer
	app *a;
	tela *p;
	if(op=='d'){
		printf("deletanto\n");
		printf("**************************************\n");
		
		char app[20];
		printf("nome do app: ");
		fflush(stdin);
		gets(app);
		strlwr(app);//tambem considera apenas minusculas
		p=busca(H, app);//em que tela vou remover
		
		if(p==NULL){//caso n�o h�
			printf("nenhum elemento achado\n");
			//return H;
		}
		
		else{//caso ha procure na lista desta tela onde achou
			a=get_app(p->L, app);
			printf("tela: %d\t %s\n",p->info, a->nome);
			p->L=del(a, p->L);//analisa cada um dos casos de remo��o
			p->cont--;//diminui em um app de onde achou
			
			//caso especifico de remo��o de tela, foi removido o unico app da ultima tela
			if(p->L==NULL && p!=H){
				p->bef->next=NULL;
				free(p);//deletar a tela onde n�o tem mais nada, desde que n�o seje a HEAD
			}
			else{
				mov(p);//desde que n�o caia no caso especifico de remo��o de tela
			}
		}
		
		printf("continuar: d(deletar mais apps) !d(parar)\n");
		fflush(stdin);
		scanf("%c", &op);
		system("cls");
		desinstala(H, op);
		return H;//voltar para a tela principal 
	}
	return H; //quando op for != 'd'
}

int main(){
	tela *H =NULL;
	H=inicializar(H);
	tela *P =H; 
	/*ponteiro de navega��o para as telas � este que permitira que HEAD
	 nunca seja excluido, se P->L==NULL e P = H n�o de o free(P)*/
	view(H->L);

	char op=operar();
	while(op!='p'){
		switch(op){
			case 'i':
				P=instala(H, op);
				break;
			case 'd':
				P=desinstala(H, op);//onde H=tela de inicio e op='d'
				break;
			case 'b':
				P=go(P, op);//op sera 'b' validado pela fun��o opera
				printf("tela atual: %d\n\n", P->info);
				break;
			case 'n':
				P=go(P, op);//tambem foi validado, o resto deixa para a fun�ao go()interpretar
				printf("tela atual: %d\n\n", P->info);
				break;
			case 'e':
				if(busca(H, "jogo da velha")==NULL){
					printf("--> precisa instalar o jogo da velha\n");
				}
				else{
					jogo();
				}
				break;	
		}
		getch();
		system("cls");
		view(P->L);
		op=operar();
	}	
	return 0;
}
