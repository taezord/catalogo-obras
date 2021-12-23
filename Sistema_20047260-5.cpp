#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define COD 18
#include <locale.h>

typedef struct cadastro
{
	char titulo[50];
	char autor[50];
	char editora[50];
	int quantidadeEstoque;
	int categoria;
	int caixa;
	int ano;
	char isbn[COD];
} Cadastro;

void identificacao();
void cadastrarObra(Cadastro obra[MAX]);
void ListarTodasObras(Cadastro obra[MAX]);
void ListarObrasCaixa(int buscaCaixa, Cadastro obra[MAX]);
void ListarObrasCategoria(int buscaCategoria, Cadastro obra[MAX]);
int contarRegistro(Cadastro obra[MAX]);

int main()
{
	
	Cadastro obra[MAX];
	setlocale(LC_ALL, "");	
	
	int op, buscaCategoria, buscaCaixa;
	do{
		identificacao();
		printf("\n1 - Cadastrar obra");
		printf("\n2 - Listar todos as obras");
		printf("\n3 - Listar obra por caixa");
		printf("\n4 - Listar obra por categoria");
		printf("\n0 - Sair");
		printf("\nEscolha Opção: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				cadastrarObra(obra);
				break;
			case 2:
				ListarTodasObras(obra);
				printf("\n");
				system("pause");
				break;
			case 3: 		
				printf("Informe a caixa da obra: \n [1] Manuais \n [2] Design \n [3] Paisagismo ");;
				fflush(stdin);
				scanf("%d", &buscaCaixa);
				ListarObrasCaixa(buscaCaixa, obra);
				printf("\n");
				system("pause");
				break;
			case 4: 
				printf("Informe a categoria: \n [1] Livros \n [2] Revistas \n");;
				fflush(stdin);
				scanf("%d", &buscaCategoria);
				ListarObrasCategoria(buscaCategoria, obra);
				printf("\n");
				system("pause");
				break;
			case 0:
				printf("\nEncerrando o sistema");
				break;
			default:
				printf("Valor indefinido");
				system("pause");
				break;
		}	
	}while(op!=0);
	return 0;
}

void identificacao(){
	system("cls");
	int t;
	for(t=0; t<80; t++) printf("-");
	printf("\n >>>> TAIANE SOLER <<<<");
	printf("\n >>>> RA: 20047260-5 <<<< ");
	printf("\n >>>> Engenharia de Software <<<< \n");
	for(t=0; t<80; t++) printf("-");
}
void cadastrarObra(Cadastro obra[MAX])
{
	identificacao();
	int i;
	FILE * arq;
 
	arq = fopen("arquivo.txt", "a+");

	if(arq != NULL)
	{
		for(i = 0; i < 1; i++){
			printf("\nInforme os dados da Obra: ");
			printf("\n........Título........: ");
			fflush(stdin);
			gets(obra[i].titulo);
			printf("\n........Autor.........: ");
			fflush(stdin);
			gets(obra[i].autor);
			printf("\n........Editora.......: ");
			fflush(stdin);
			gets(obra[i].editora);
			printf("\n........Quantidade....: ");
			fflush(stdin);
			scanf("%d", &obra[i].quantidadeEstoque);
			printf("\n........Categoria.....:\n [1] Livros \n [2] Revistas : ");
			scanf("%d", &obra[i].categoria);
			printf("\n........Caixas........:\n [1] Manuais | [2] Design | [3] Paisagismo : ");
			fflush(stdin);
			scanf("%d", &obra[i].caixa);
			printf("\n........Ano...........: ");
			scanf("%d", &obra[i].ano);
			printf("\n........ISBN..........: ");
			fflush(stdin);
			gets(obra[i].isbn);
			fwrite(&obra[i], sizeof(Cadastro), 1, arq);
		}
		fclose(arq); 
	}
	else
	{
		printf("\nErro ao abrir o arquivo!\n");
		exit(1); 
	}
}

int contarRegistro(Cadastro obra[MAX])
{
	FILE * arq = fopen("arquivo.txt", "r");
	if(arq != NULL)
	{
		int contador = 0;
		while(1)
		{
			Cadastro p;
		
			
			int registro = fread(&p, sizeof(Cadastro), 1, arq);
			
			
			if(registro < 1)
				break;
			else
				obra[contador] = p;
			contador++;
		}
		fclose(arq); 
		return contador;
	}
	else
	{
		printf("\nErro ao abrir o arquivo!\n");
		exit(1); 
	}
}

void ListarTodasObras(Cadastro obra[MAX]){	
	identificacao();
	
	int quantidadeobra = contarRegistro(obra);
	int i;
	
	printf("\n|\t Lista de Obras \t| %d\n", quantidadeobra);
	
	for(i = 0; i < quantidadeobra; i++)
 {
		printf("\n| ITEM \t %d\t|\n| TITULO \t| %s \t\n| AUTOR \t| %s  \t\t\n| EDITORA \t| %s  \t \t\n| ESTOQUE \t| %d \t\n| CAIXA \t| %d \t\n| ANO \t\t| %d \t\n| CATEGORIA \t| %d\n| ISBN \t\t| %s\t\n ", i+1, obra[i].titulo, obra[i].autor, obra[i].editora, obra[i].quantidadeEstoque, obra[i].caixa, obra[i].ano, obra[i].categoria, obra[i].isbn);	
	}
}

void ListarObrasCaixa(int buscaCaixa, Cadastro obra[MAX]){	
	identificacao();
	
	int quantidadeobra = contarRegistro(obra);
	int i;
	
	printf("\n>>>> Lista por caixa <<<< \n Caixas: \n[1] Manuais | [2] Design | [3] Paisagismo :");
	if (buscaCaixa == 1) {
		printf("\n\tCaixa pesquisada: Manuais \n");	
	}else if (buscaCaixa == 2) {
		printf("\n\tCaixa pesquisada: Design \n");	
	}else if (buscaCaixa == 3) {
		printf("\n\tCaixa pesquisada: Paisagismo \n");	
	}
	
	for(i = 0; i < quantidadeobra; i++)
	{
		if(obra[i].caixa == buscaCaixa){
		printf("\n| ITEM \t %d\t|\n| TITULO \t| %s \t\n| AUTOR \t| %s  \t\t\n| EDITORA \t| %s  \t \t\n| ESTOQUE \t| %d \t\n| CAIXA \t| %d \t\n| ANO \t\t| %d \t\n| CATEGORIA \t| %d\n| ISBN \t\t| %s\t\n ", i+1, obra[i].titulo, obra[i].autor, obra[i].editora, obra[i].quantidadeEstoque, obra[i].caixa, obra[i].ano, obra[i].categoria, obra[i].isbn);	
		}
	}
}
void ListarObrasCategoria(int buscarCategoria, Cadastro obra[MAX]){
	identificacao();
	
	int quantidadeobra = contarRegistro(obra);
	int i;
	
	printf("\n>>>> Lista de Obras por categoria <<<< \n");
	printf("Categoria pesquisada: %d \n", buscarCategoria);
	
	for(i = 0; i < quantidadeobra; i++)
	{
		if(obra[i].categoria == buscarCategoria){
		printf("\n| ITEM \t %d\t|\n| TITULO \t| %s \t\n| AUTOR \t| %s  \t\t\n| EDITORA \t| %s  \t \t\n| ESTOQUE \t| %d \t\n| CAIXA \t| %d \t\n| ANO \t\t| %d \t\n| CATEGORIA \t| %d\n| ISBN \t\t| %s\t\n ", i+1, obra[i].titulo, obra[i].autor, obra[i].editora, obra[i].quantidadeEstoque, obra[i].caixa, obra[i].ano, obra[i].categoria, obra[i].isbn);	
		}
	}
}
