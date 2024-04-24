#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N=11;

typedef struct registro{
  int matricula;
  char nome[50];
  char curso[20];
  int disponibilidade;
} Registro;

void Inicializar(char*nomeArq){
  FILE *arq = fopen(nomeArq, "wb");
  Registro a;
  int i;
  a.disponibilidade=1;
  for(i=0;i<N;i++)
    fwrite(&a, sizeof(Registro),1,arq);
  fclose(arq);
}

int Hash(int matricula){
  return matricula%N;}

int Matricula(int x){
  return x%100;
}


int AcharPosição(char*nomeArq, int matricula){
  int pos= Hash(Matricula(matricula));
  Registro a;
  FILE*arq=fopen(nomeArq,"rb");
  fseek(arq,pos*sizeof(Registro), SEEK_SET);
  fread(&a, sizeof(Registro),1,arq);
  while(a.disponibilidade==0){
    pos= (pos+1)%N;
    fseek(arq, pos*sizeof(Registro), SEEK_SET);
    fread(&a, sizeof(Registro),1,arq);
  }
  fclose(arq);
  return pos;
}

void Inserir(char*nomeArq, char*nome, char*curso,int matricula){
  int pos= AcharPosição(nomeArq,matricula);
  FILE*arq=fopen(nomeArq,"r+b");
  Registro a;
  a.matricula=matricula;
  a.disponibilidade=0;
  strcpy(a.curso,curso);
  strcpy(a.nome,nome);
  fseek(arq,pos*sizeof(Registro), SEEK_SET);
  fwrite(&a, sizeof(Registro), 1, arq);
  fclose(arq);}


int BuscarAluno(char*nomeArq, int x){
  int pos= Hash(Matricula(x));
  Registro a;
  FILE*arq=fopen(nomeArq,"rb");
  fseek(arq,pos*sizeof(Registro), SEEK_SET);
  fread(&a, sizeof(Registro),1,arq);
  while(a.matricula!=x){
    if (a.disponibilidade==1)
      return -1;
    pos=(pos+1)%N;
    fseek(arq, pos*sizeof(Registro), SEEK_SET);
    fread(&a, sizeof(Registro),1,arq);
      }
  fclose(arq);
  return pos;
    }


void ImprimirAluno(char*nomeArq, int matricula){
  Registro a;
  FILE*arq=fopen(nomeArq,"rb");
  int pos= BuscarAluno(nomeArq, matricula);
  fseek(arq, pos*sizeof(Registro), SEEK_SET);
  fread(&a, sizeof(Registro),1,arq);
  printf("------------------------------- \n");
  printf("Aluno: %s\n", a.nome);
  printf("Matricula: %d\n", a.matricula);
  printf("Curso: %s\n", a.curso);
  printf("------------------------------- \n");
  fclose(arq);
  
}
  
void ImprimirHash(char*nomeArq){
  Registro a;
  int pos;
  FILE*arq=fopen(nomeArq,"rb");
  for(pos=0;pos<N;pos++){
  fseek(arq, pos*sizeof(Registro), SEEK_SET);
  fread(&a, sizeof(Registro),1,arq);
    if (a.disponibilidade==1)
      printf("Posição %d disponível\n", pos);
    else {
      printf("------------------------------- \n");
      printf("Aluno: %s\n", a.nome);
      printf("Matricula: %d\n", a.matricula);
      printf("Curso: %s\n", a.curso);
      printf("------------------------------- \n");}
      
  }

  fclose(arq);}

int main(void) {
  int mat, opcoes;
  char curso[20];
  char nome[50];
  
  Inicializar("aluno.bin.txt");

    while (1) {
      printf("\n\n\t\t\t Menu: Escolha um número ");
      printf("\n__________________________________________________");
      printf("\n\n 1) Inserir um novo aluno ");
      printf("\n 2) Imprimir as informações de um determinado aluno");
      printf("\n 3) Imprimir Hash");
      printf("\n 4) Sair");
      printf("\n\t Digite uma opcao: ");
      printf("\n");
      scanf("%d", &opcoes);

      switch (opcoes) {

      case 1: //Inserir
        printf("Você escolheu a Opção 1\n");
        printf("\nDigite o nome do aluno:  ");
        scanf("%s", nome);
        printf("\nDigite a matrícula do aluno:  ");
        scanf("%d", &mat);
        printf("\nDigite o curso do aluno:  ");
        scanf("%s", curso);
        Inserir("aluno.bin.txt", nome, curso, mat);
        
        break;

      case 2: //Imprimir um aluno
        printf("Você escolheu a Opção 2\n");
        printf("\nDigite a matrícula do aluno:  ");
        scanf("%d", &mat);
        ImprimirAluno("aluno.bin.txt", mat);
        break;
       

      case 3: //Imprimir Hash
        printf("Você escolheu a Opção 3\n");
        ImprimirHash("aluno.bin.txt");
        break;

      case 4: // Sair do programa
        printf("Saindo do programa...\n");
        return 0;
      default:
        printf("Opção inválida. Tente novamente.\n");
      }
    }

  }

