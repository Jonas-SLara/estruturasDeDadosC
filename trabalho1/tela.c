#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
//cada tela possui aplicativos e o mesmo não pode estar em 2+ telas
struct app{
	char nome[20];
	struct app *next;
	struct app *bef;
};

typedef struct app app;

struct tela{
	int cont; //contador de apps em cada tela, max=6	
	struct tela *next;
	struct tela *bef;
	app *L;	//ponteiro para o nó cabeçã da lista de aplicativos
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

tela *get_last_tela(tela *H){//antes de achar o ultimo app é preciso achar a ultima tela criada
	tela *P=H;
	if(P->next==NULL){
		return P;
	}
	else{
		P=get_last_tela(P->next);
		return P;
	}	
}

app *get_app(app *q, char nome[20]){
//onde Q=P->L, P =ponteiro da tela onde há o elemento achado pela busca
	if(strcmp(q->nome, nome)==0 || q==NULL){
		return q;
	}
	q=get_app(q->next, nome);
	return q;
}

tela *busca(tela *H, char nome[20]){//retorna NULL se não há elemento com este nome, se há retorna a tela onde esta
	tela *p=H;
	if(p==NULL){//não há elementos
		return p;
	}
	else{
		app *a=p->L;
		while(a!=NULL && strcmp(a->nome, nome)!=0){
			a=a->next;
		}
		if(a!=NULL){//achou retorna o endereço da tela onde ele esta
			return p; //p!=NULL
		}
		else{
			p=busca(p->next, nome);
			return p;
		}
	}
}

app *add(app *P, char nome[20]){//P é o nó cabeça da lista da ultima tela criada
	app *novo=(app*)malloc(sizeof(app));
	novo->next=NULL;
	strcpy(novo->nome, nome);
	if(P==NULL){//caso a tela principal ou uma nova esta vazia
		novo->bef=NULL;
		printf("foi carregado um app %s %x\n", novo->nome, novo);
		return novo;
	}
	else{//insere no final da lista
		app *q=P;
		q=get_last_app(q);//obtem o endereço do ultimo app na tela em que esta
		novo->bef=q;
		q->next=novo;
		printf("foi carregado um app %s %x\n", novo->nome, novo);
		return P;
	}
}

tela *new_tela(tela *P){//P aponta para a ultima tela criada
	tela *novo=(tela*)malloc(sizeof(tela));
	//etapas para a criação de uma tela antes de adicionar o 1 app
	novo->next=NULL;
	novo->bef=P;
	P->next=novo;
	novo->cont=0; 
	novo->L=NULL;
	return novo;
}

void instala(tela *H, char nome[20]){//na ultima tela criada, insere no final
	tela *q = busca(H, nome);//se ha um app ja instalado retorna !=NULL
	if(q!=NULL){
		printf("\nelemento repetido na tela %x\n", q);
	}
	else{
		tela *p = H;
		p=get_last_tela(p);	//acha a ultima tela criada
		if(p->cont==6){
			p=new_tela(p);
			p->L=add(p->L, nome);
			p->cont++;
			printf("criado uma nova tela:  %x\n", p);
		}
		else{
			p->L=add(p->L, nome);
			p->cont++;//incrementa 
		}
	}
}

tela *inicializar(tela *H){ //aloca a tela inicial na memoria + lista com alguns aplicativos
	H =(tela*)malloc(sizeof(tela));
	H->cont=0;
	H->L=NULL;
	H->next=NULL;
	H->bef=NULL;
	char app1[20];
	char app2[20];
	char app3[20];
	char app4[20];
	char app5[20];
	strcpy(app1, "configuracoes");
	strcpy(app2, "calculadora");
	strcpy(app3, "calendario");
	strcpy(app4, "system32");
	strcpy(app5, "jogo da velha");
	instala(H, app1);
	instala(H, app2);
	instala(H, app3);
	instala(H, app4);
	instala(H, app5);
	system("cls");
	return H;
}

void view(app *P){
	app *a = P;
	int n=0;
	if(a!=NULL){
		do{
			printf("%s\t", a->nome);
			n++;
			a=a->next;
		}while(a!=NULL && n<2);
		printf("\n----------------------------------\n");
		view(a);
	}
}

tela *next(tela *P){
	if(P->next==NULL){
		printf("esta tela ainda não existe\n");
		system("pause");
		system("cls");
		//view(P->L);//volta para a tela de onde veio
		return P;
	}
	else{
		P=P->next;
		//view(P->L);
		return P;
	}
}

tela *before(tela *P){
	if(P->bef==NULL){
		printf("esta tela ainda não existe\n");
		system("pause");
		system("cls");
		//view(P->L);
		return P;
	}
	else{
		P=P->bef;
		//view(P->L);
		return P;
	}
}

char operar(){//comando de operações//
	printf("**************************************");
	printf("\n<<-b i(instala) p(parar) d(deleta) n-->\n");
	char option;
	do{//validação do caractere
		fflush(stdin);
		scanf("%c", &option);
	}while(option != 'b' && option!='p'&& option!='i' 
	&& option!='d' && option!='n');
	system("cls");
	return option;
}

app *del(app*origem, app* HEAD){
	if(origem->bef==NULL){//se trata do primeiro elemento
		HEAD=origem->next;
		HEAD->bef=NULL;
		free(origem);
		return HEAD;
	}
	else if(origem->next==NULL){//ultimo elemento
		origem->bef->next=NULL;//pénultimo aponta para NULL
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

void desinstala(tela *H, char nome[20]){
	tela *p=busca(H, nome);//em que tela vou remover
	if(p==NULL){
		printf("nenhum elemento achado\n");
	}
	else{
		app *a=get_app(p->L, nome);
		printf("%x\t%x\t%s\n",p,  a, a->nome);
		p->L=del(a, p->L);
		p->cont--;
	}
}

int main(){
	setlocale(LC_ALL, "portuguese");
	tela *H =NULL;
	H=inicializar(H);
	tela *P =H; 
	/*ponteiro de navegação para as telas é este que permitira que HEAD
	 nunca seja excluido, se P->L==NULL e P = H não de o free(P)*/
	view(H->L);

	char op=operar();
	while(op!='p'){
		switch(op){
			case 'i':
				printf("instalando\n");
				printf("**************************************\n");
				char nome[20];
				printf("nome do app: ");
				fflush(stdin);
				gets(nome);
				instala(H, nome);
				break;
			case 'd':
				printf("deletanto\n");
				printf("**************************************\n");
				char app[20];
				printf("nome do app: ");
				fflush(stdin);
				gets(app);
				desinstala(H, app);
				break;
			case 'b':
				P=before(P);
				printf("tela atual: %x\n\n", P);
				break;
			case 'n':
				P=next(P);
				printf("tela atual: %x\n\n", P);
				break;	
		}
		getch();
		system("cls");
		view(P->L);
		op=operar();
	}	
	return 0;
}
