#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 

//FUNÇÃO PRÓXIMO 
//então acho q aqui posso pegar simbolo por simbolo do arquivo texto
//verificar fim da linha e fazer contagem de linha 

void proximo (FILE* arquivo){
	char texto[200];
	arquivo = fopen("Exemplo1_Trab1_Compiladores.txt","r");
	
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		exit(0);
	}

	int linha=1;
		while (fgets(texto,199,arquivo) != NULL){
		
			linha++; //fgets pega mesmo a linha
			if(!texto) //se não conseguir pegar carcterre relata erro
			erro(linha);
		}
	printf("\nQte total de linhas: %d\n",linha);
}

int eh_reserva(char atomo[]){ //vou recebr aqui cada palavra
	char keywords[15][10] = {"program","var","procedure","function","begin","end","if",
							"then","else","while","do","or","and","div","not"};
	int i, flag = 0;
	
	for(i = 0; i < 15; ++i){
		if(strcmp(keywords[i], atomo) == 0){
			flag = 1;
			break;
		}
	}
	
	return flag;
}

//FUNÇÃO CÓDIGO
//verifica se eh palavra reservada 
//verifica se eh identificador (simbolo especial ou nome de função)
//verifica se eh numero

int codigo(FILE* fp,char ch, char atomo[],char simbolos_especiais[]){
	//coloco os printf aqui se for identifcador etc
	int j=0,i;
	printf("\nAnalisando o programa:\n\n");
	while((ch = fgetc(fp)) != EOF){ //pega carctere por caractere
   	
	   	for(i = 0; i < 12; ++i){
   			if(ch == simbolos_especiais[i]){
   				printf("%c: \nCorresponde simbolo especial  -> recebe codigo de identificador\n\n", ch); 
   	 			//printf("eh codigo de operador");
   	 		}}
   	 			
		if(isalnum(ch)){ //isanum devolve valor != 0 se for letra ou digito
						//se não for alfanumérico devolveo 0
		   	atomo[j++] = ch; //vou para o proximo
	   	}
   		
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   				atomo[j] = '\0';  //se tiver espaço ou barra n no finall minha cadeia acabou
   				j = 0;
   				   				
   				if(eh_reserva(atomo) == 1){
   					printf("%s: \nCorresponde palavra reservada -> recebe codigo de palavra reservada\n\n", atomo);
				   }else{
   					printf("%s: \nCorresponde identificador -> recebe codigo de identificador\n\n", atomo);}
					   } 
	}
}

//FUNÇÃO ERRO
//se tiver erro mostra a linha não aceita por exemplo

int erro(int k){
	printf("\nErro na linha %d",k);
	exit(1); 
}
 

int main(){
	char ch, atomo[15], simbolos_especiais[] = ";,():=<>+=*";
	FILE *fp;
	int i,j=0;
	printf("\n\n\t\t\tANALISADOR LEXICO \n\n");
	printf("\n\tA definir:\n");
	printf("Codigo de numero, codigo de identificador, codigo de palavra reservada\n");
	
	fp = fopen("Exemplo1_Trab1_Compiladores.txt","r");
	
	if(fp == NULL){
		printf("Erro ao abrir o arquivo\n");
		exit(0);
	}
	
	proximo(fp);
	codigo(fp,ch,atomo,simbolos_especiais);   		
	fclose(fp);
	
	return 0;
}
