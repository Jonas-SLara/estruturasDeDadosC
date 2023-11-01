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
			do{//validação do numero a ser escolhido
				printa(M);
				printf("linha:de 1 a 3:  ");
				scanf("%d", &l);
				printf("coluna: de 1 a 3:  ");
				scanf("%d", &c);
			}while(c>3 || c<1 || l>3 || l<1);//condições falsas
			//validação do campo que passou no teste anterior
			system("cls");		
		}while(M[l-1][c-1]!='0');//condiçoes falsas
	M[l-1][c-1]=value;
}
void jogo(){
	int cont=0;
	int A=1, B=1;
	char M[3][3];
	zerar(M);
	do{
		printf("jogador A: \n");
		jogada(M, 'x');
		cont++;
		A=vitoria(M);
		if(A==1 && cont<9){//somente se não houve vitoria anterior
			system("cls");
			printf("jogador B: \n");
			jogada(M, '@');
			cont++;
			B=vitoria(M);
		}
		system("cls");
	}while(A==1 && B==1 && cont<9);
	printa(M);
	if(cont>=9){
		printf("empate!");
	}
	if(A==0){
		printf("A ganhou!");
	}
	if(B==0){
		printf("B ganhou!");
	}
}

