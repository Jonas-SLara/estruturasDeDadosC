void printa(char M[3][3]){
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			printf("%c ", M[i][j]);
		}
		printf("\n");
	}
}
int vitoria(char M[3][3]){
	int i;//verificar colunas 
	for(i=0; i<3; i++){
		if(M[i][0]==M[i][1] && M[i][1]==M[i][2] && M[i][0]!='0'){
			return 0;
		}
	}
	for(i=0; i<3; i++){//verificar linhas
		if(M[0][i]==M[1][i] && M[1][i]==M[2][i] && M[0][i]!='0'){
			return 0;
		}
	}
	if(M[0][0]==M[1][1] && M[1][1]==M[2][2] && M[1][1]!='0'){
		return 0;
	}
	if(M[0][2]==M[1][1] && M[1][1]==M[2][0] && M[1][1]!='0'){
		return 0;
	}
	return 1;//sem vitorias ainda
}
void zerar(char M[3][3]){
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			M[i][j]='0';
		}
	}
}

void jogada(char M[3][3], char value){
	int l,c;
		do{ 
			printa(M);
			printf("linha/coluna de 1 a 3: ");
			scanf("%d %d", &l, &c);
			if(M[c-1][l-1]!='0'){
				printf("\nja foi preenchido\n");
				getch();
				system("cls");
			}		
		}while((c>3 && l>3 && c<1 && l<1) || M[l-1][c-1]!='0');//condiçoes falsas
	M[l-1][c-1]=value;
}

void jogo(){
	int A=1, B=1;
	char M[3][3];
	zerar(M);
	do{
		printf("jogador A: \n");
		jogada(M, 'x');
		A=vitoria(M);
		if(A==1){//somente se não houve vitoria anterior
			system("cls");
			printf("jogador B: \n");
			jogada(M, '@');
			B=vitoria(M);
		}
		system("cls");
	}while(A==1 && B==1);
	printa(M);
	if(A==0){
		printf("A ganhou!");
	}
	else{
		printf("B ganhou!");
	}
}

