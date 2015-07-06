#include<stdio.h>
#include<stdlib.h>
#include "regras.h"
int main(){
	int var;
	do
	{
		printf("\n\n\n\n\n\n\n\n\n\n");
		printf("                .::::Sistema de Agendamento Eletronico::::.  \n\n");
		printf("  Veja todas as funcoes disponiveis no menu   \n");
		printf("  use os numeros para selecionar a opcao desejada  \n");
		printf("  pressione qualquer tecla para continuar ou ESC para sair do programa agora.");
		var = getch();
		system("cls");

		printf("\n");
		printf("\n");
		printf("Escolha uma Opcao:\n");
		printf("\n");

		printf("1- Atendimento\n");
		printf("2- Sair\n");
		scanf("%d", &var);
		if (var == 2)
		{
			exit(1);
		}
		else
		{
			exibeServico();
		}


	} while (var != 2);



	system("pause");
}