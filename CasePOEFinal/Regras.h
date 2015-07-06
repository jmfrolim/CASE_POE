/* main.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

typedef struct atendimento
{
	char Nome[40];
	char Data[15];
	char hora[10];
	char Solicitacao[10];
	char Descricao[200];
}T_dados;

// prototipos
void inclusao(void);
void listar(void);
void listarServicos(void);
void ordenar(void);
void pesquisar(void);
char validaResp();
void menu();
void exibeServico(void);

static int qtd = 0;

T_dados Tab[100];
FILE *fp;


// =================================================================
// ======Incluir dados no arquivo ==================================
void inclusao(void){
	int total = 0, retorno;
	char op = 's';

	if ((fp = fopen("siagel.db", "a")) == NULL)
	{
		printf("O arquivo da lista não pode ser aberto!\n");
		printf("Insira dados!\n");
		getch();
		exit(1);
	}
	while ((total < 100) && (op == 's'))
	{
		fflush(stdin);
		printf("Digite o nome: ");
		gets(Tab[total].Nome);

		printf("Digite qual sera data do atendimeto: ");
		gets(Tab[total].Data);
		printf("Digite o servico solicitado: ");
		gets(Tab[total].Solicitacao);
		printf("Descreva o sobre o que se trata: ");
		gets(Tab[total].Descricao);
		printf("Digite o horario do atendimento: ");
		gets(Tab[total].hora);

		retorno = fwrite(&Tab[total], sizeof(struct atendimento), 1, fp);

		if (retorno == 1) {
			printf(" \nGravacao ok ! ");
		}
		total++;
		op = validaResp();
		qtd++;
	}
	fclose(fp);
}

//======================================================================
// ======Valida resposta ===============================================

char validaResp() {
	char op;
	do {
		printf(" \nDeseja inserir novos dados? [S ou N] ? ");
		op = getch();
		printf("\n");
	} while (op != 's' && op != 'n');
	return op;
}

//======================================================================
// ======Organizar em ordem alfabetica =================================

void ordenar(void){

	T_dados vet;
	int aux, i, j, k, retorno;
	char *str, *str2, *straux;


	aux = qtd; // aux recebe a quantidade d inscritos
	for (i = 0; i < aux; i++){
		str = Tab[i].Nome;
		for (j = i + 1; j < aux; j++){
			str2 = Tab[j].Nome;
			if (strcmp(str, str2) > 0){
				vet = Tab[i];
				Tab[i] = Tab[j];
				Tab[j] = vet;
			}
		}
	}

	remove("siagel.db");
	if ((fp = fopen("siagel.db", "w+")) == NULL){
		printf("ERRO!\n");
		getch();
		exit(1);
	}
	for (k = 0; k < aux; k++){
		retorno = fwrite(&Tab[k], sizeof(struct atendimento), 1, fp);
		if (retorno != 1) {
			printf(" \nERRO ! ");
		}
	}
	fclose(fp);
	printf("\nLista Ordenada! \n");
	getch();
}

//======================================================================
// ======Pesquisar contato pelo nome ===================================

void pesquisar(void){
	int indice = 0, retorno = 1, cont = 0;
	char nome[80], op;

	if ((fp = fopen("siagel.db", "r")) == NULL){
		printf("O arquivo da lista não pode ser aberto!\n");
		printf("Insira dados!\n");
		getch();
		exit(1);
	}
	printf("Digite o nome: ");
	gets(nome);

	retorno = fread(&Tab[indice], sizeof(struct atendimento), 1, fp);

	while (retorno == 1){
		if (strcmp(nome, Tab[indice].Nome) == 0){
			printf("\nNome ..: %s\nData ..: %s\nHora ..: %s\nSevico ..: %s\nDescricao", nome, Tab[indice].Data, Tab[indice].hora, Tab[indice].Solicitacao, Tab[indice].Descricao);
			cont++;
		}
		indice++;
		retorno = fread(&Tab[indice], sizeof(struct atendimento), 1, fp);
	}
	if (cont == 0){
		printf("Nao ha cadastros com este nome!\n");
	}
	getch();
	fclose(fp);
}

//======================================================================
// ======Pesquisar Data============================================

void pesquisardata(void){
	int indice = 0, retorno = 1, cont = 0;
	char data[80], op;

	if ((fp = fopen("siagel.db", "r")) == NULL){
		printf("O arquivo da lista não pode ser aberto!\n");
		printf("Insira dados!\n");
		getch();
		exit(1);
	}
	printf("Digite o digite a data: ");
	gets(data);

	retorno = fread(&Tab[indice], sizeof(struct atendimento), 1, fp);

	while (retorno == 1){
		if (strcmp(data, Tab[indice].Data) == 0){
			printf("\nNome ..: %s\nData ..: %s\nHora ..: %s\nSevico ..: %s\nDescricao", Tab[indice].Nome, Tab[indice].Data, Tab[indice].hora, Tab[indice].Solicitacao, Tab[indice].Descricao);
			cont++;
		}
		indice++;
		retorno = fread(&Tab[indice], sizeof(struct atendimento), 1, fp);
	}
	if (cont == 0){
		printf("Nao ha cadastros para esse data!\n");
	}
	getch();
	fclose(fp);
}

//======================================================================
// ======Pesquisar por Servico ===================================

void pesquisarServico(void){
	int indice = 0, retorno = 1, cont = 0;
	char servico[80], op;

	if ((fp = fopen("siagel.db", "r")) == NULL){
		printf("O arquivo da lista não pode ser aberto!\n");
		printf("Insira dados!\n");
		getch();
		exit(1);
	}
	printf("Digite o Servico: ");
	gets(servico);

	retorno = fread(&Tab[indice], sizeof(struct atendimento), 1, fp);

	while (retorno == 1){
		if (strcmp(servico, Tab[indice].Solicitacao) == 0){
			printf("\nNome ..: %s\nData ..: %s\nHora ..: %s\nSevico ..: %s\nDescricao", Tab[indice].Nome, Tab[indice].Data, Tab[indice].hora, Tab[indice].Solicitacao, Tab[indice].Descricao);
			cont++;
		}
		indice++;
		retorno = fread(&Tab[indice], sizeof(struct atendimento), 1, fp);
	}
	if (cont == 0){
		printf("Nao ha dados cadastrados para esse servico!\n");
	}
	getch();
	fclose(fp);
}

//======================================================================
// ======Listar cadastros=================================

void listar(void){
	int i = 0, retorno;


	if ((fp = fopen("siagel.db", "r")) == NULL)
	{
		printf("O arquivo da lista não pode ser aberto!\n");
		printf("Insira dados!\n");
		getch();
		exit(1);
	}

	retorno = fread(&Tab[i], sizeof(struct atendimento), 1, fp);
	// fread retorna a quantidade de itens ...

	while (retorno == 1) {

		printf("\n Nome ..: %s", Tab[i].Nome);
		printf("\n Data ..: %s", Tab[i].Data);
		printf("\n Hora ..: %s", Tab[i].hora);
		printf("\n Servico ..: %s", Tab[i].Solicitacao);
		printf("\n Descricao ..: %s\n", Tab[i].Descricao);
		i++;
		retorno = fread(&Tab[i], sizeof(struct atendimento), 1, fp);

	}
	printf(" \n\n %d registros salvos!\n", i);
	getch();
	fclose(fp);
}

void listarServicos(void){
	int i = 0, retorno;
	char tipoServico[10];

	if ((fp = fopen("siagel.db", "r")) == NULL)
	{
		printf("O arquivo da lista não pode ser aberto!\n");
		printf("Insira dados!\n");
		getch();
		exit(1);
	}
	printf("Dig");

	retorno = fread(&Tab[i], sizeof(struct atendimento), 1, fp);
	// fread retorna a quantidade de itens ...

	while (retorno == 1) {
		printf("Informe o servico:");
		if (Tab[i].Solicitacao == "Ouvidoria")
		{
			printf("\n Nome ..: %s", Tab[i].Nome);
			printf("\n Data ..: %s", Tab[i].Data);
			printf("\n Hora ..: %s", Tab[i].hora);
			printf("\n Servico ..: %s", Tab[i].Solicitacao);
			printf("\n Descricao ..: %s\n", Tab[i].Descricao);
			i++;
			retorno = fread(&Tab[i], sizeof(struct atendimento), 1, fp);
		}
	}
	printf(" \n\n %d registros salvos!\n", i);
	getch();
	fclose(fp);
}
//======================================================================
// ======Menu ==========================================================

void menu(void){
	char op;
	int teste;

	if ((fp = fopen("siagel.db", "r")) != NULL){
		qtd = 0;
		do {
			teste = fread(&Tab, sizeof(struct atendimento), 1, fp);
			qtd++;
		} while (teste == 1);
		qtd--;
	}

	do{
		system("cls");
		printf("\n(1)Incluir\n(2)Ordenar\n(3)Pesquisar por nome\n");
		printf("(4)Pesquisar por Data\n(5)Pesquisar por Servico\n(6)Aperte essa tecla para sair\n(7)Voltar ao menu anterior\n\n");
		op = getch();
		switch (op){
		case '1':
			inclusao();
			break;
		case '2':
			ordenar();
			break;
		case '3':
			pesquisar();
			break;
		case '4':
			pesquisardata();
			break;
		case '5':
			pesquisarServico();
			break;
		case '7':
			exibeServico();
			break;
		default:
			printf("Digite uma opcao valida!");
			exit(1);
		}
	} while (op != '7');
}

void exibeServico(void)
{
	char op;
	do
	{

		system("cls");
		printf("Escolha o Servico desejado\n (1) Nada Consta\n (2) Pagamento\n (3) Atualizacao de Cadastro\n (4) Ouvidoria\n (5) Renovacao de Contrato\n (6) Listar todos os atendimentos \n (0) Sair\n");
		printf("Digite um valor\n");
		op = getch();
		printf("\n");
		switch (op)
		{
		case '1':
			menu();
			break;
		case'2':
			menu();
			break;
		case '3':
			menu();
			break;
		case '4':
			menu();
			break;
		case'5':
			menu();
			break;
		case '6':
			listar();
			break;
		case'0':
			exit(1);

		default:printf("Uma opção valida invalido!");
			break;
		}

	} while (op != '0');
}