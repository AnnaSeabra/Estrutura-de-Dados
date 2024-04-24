#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pessoa{
  int tipo;
  void*item;
  struct pessoa*prox;
} Pessoa;

typedef struct aluno{
  int matricula;
  char nome [50];
  char curso[20];
  int ano; 
} Aluno;

typedef struct professor{
  int matricula;
  char nome [50];
  int salario;
} Prof;


Pessoa*CriarNo(Pessoa*inicio){
  
  Pessoa*no=(Pessoa*)malloc(sizeof(Pessoa));
  return no;
}

Pessoa*InserirInicio(Pessoa*inicio, Pessoa*no, void*info, int tipo){
  no->item=info;
  no->tipo=tipo;
  no->prox=inicio;
  inicio=no;
  return inicio;}

Pessoa*Remover(Pessoa*inicio, int matricula){
  
  Pessoa*aux1=inicio;
  if (aux1!=NULL){
    if (aux1->tipo==1){
      Aluno*aluno=(Aluno*)aux1->item;
      if (aluno->matricula==matricula){
        Pessoa*aux = aux1->prox;
        free(aux1);
        return aux;}
      else 
        aux1->prox=Remover(aux1->prox, matricula);   
  }
    else if (aux1->tipo==2){
      Prof*prof=(Prof*)aux1->item;
      if (prof->matricula==matricula){
        Pessoa*aux=aux1->prox;
        free(aux1);
        return aux;}
      else
        aux1->prox=Remover(aux1->prox, matricula);}}

    return aux1;}

void BuscarPessoa(Pessoa*inicio, int matricula){
  Pessoa*aux=inicio;
  if (aux!=NULL){
    if (aux->tipo==1){
      Aluno*aluno=(Aluno*)aux->item;
      if (aluno->matricula==matricula){
        printf("Aluno encontrado!!\n");
        printf("-------------------------------------\n");
        printf("Nome: %s\n", aluno->nome);
        printf("Matricula: %d\n", aluno->matricula);
        printf("Curso: %s\n", aluno->curso);
        printf("Ano de ingresso: %d\n", aluno->ano);}
      else 
        BuscarPessoa(aux->prox, matricula);}
    else if (aux->tipo==2){
      Prof*prof=(Prof*)aux->item;
      if (prof->matricula==matricula){
        printf("Professor encontrado!!\n");
        printf("-------------------------------------\n");
        printf("Nome: %s\n", prof->nome);
        printf("Matricula: %d\n", prof->matricula);
        printf("Salario: %d\n", prof->salario);}
      else
        BuscarPessoa(aux->prox, matricula);}
  }}

int ContarAlunosCurso(Pessoa*inicio, char curso[]){
  Pessoa*aux=inicio;
  int cont=0;
  while(aux!=NULL){
    if (aux->tipo==1){
      Aluno*aluno=(Aluno*)aux->item;
      if (strcmp(aluno->curso, curso)==0){
        aux=aux->prox;
        cont++;}
      else 
        aux=aux->prox;}
    else if (aux->tipo==2)
      aux=aux->prox;
  }

    return cont;}


int MaiorSalario(Pessoa*inicio){
  Pessoa*aux=inicio;
  int maior=0;
  while(aux!=NULL){
    if (aux->tipo==2){
      Prof*prof=(Prof*)aux->item;
      if (prof->salario>maior){
        maior=prof->salario;
        aux=aux->prox;}
      else 
        aux=aux->prox;}
    else if (aux->tipo==1)
      aux=aux->prox;
  }
    return maior;}

void ImprimirProfSalario(Pessoa*inicio){
  Pessoa*aux=inicio;
  int salario=MaiorSalario(inicio);
  while(aux!=NULL){
    if (aux->tipo==2){
      Prof*prof=(Prof*)aux->item;
      if (prof->salario==salario){
        printf("-------------------------------------\n");
        printf("Nome: %s\n", prof->nome);
        printf("Matricula: %d\n", prof->matricula);
        printf("Salario: %d\n", prof->salario);
        printf("-------------------------------------\n");
        aux=aux->prox;}
      else 
        aux=aux->prox;}
    else if (aux->tipo==1)
      aux=aux->prox;
  }
}

void ImprimirLista(Pessoa*inicio){
  Pessoa*aux=inicio;
  while(aux!=NULL){
    if (aux->tipo==1){
      Aluno*aluno=(Aluno*)aux->item;
      printf("-------------------------------------\n");
      printf("Nome: %s\n", aluno->nome);
      printf("Matricula: %d\n", aluno->matricula);
      printf("Curso: %s\n", aluno->curso);
      printf("Ano de ingresso: %d\n", aluno->ano);
      printf("-------------------------------------\n");
      aux=aux->prox;
}
    else if (aux->tipo==2){
      Prof*prof=(Prof*)aux->item;
      printf("-------------------------------------\n");
      printf("Nome: %s\n", prof->nome);
      printf("Matricula: %d\n", prof->matricula);
      printf("Salario: %d\n", prof->salario);
      printf("-------------------------------------\n");
      aux=aux->prox;}
    
  }
}
    


int main(void) {

  int mat, opcoes, ano;
  char curso[20];
  char nome[50];
  int tip;
  
  Pessoa*inicio=NULL;
  Aluno*a=NULL;
  Prof*p=NULL;
  Pessoa*No=NULL;
  

  while (1) {
      printf("\n\n\t\t\t Menu: Escolha um número ");
      printf("\n__________________________________________________");
      printf("\n\n 1) Inserir Pessoa ");
      printf("\n 2) Remover pessoa pela matrícula");
      printf("\n 3) Buscar uma pessoa pela matrícula");
      printf("\n 4) Quantidade de alunos de determinado curso");
      printf("\n 5) Imprimir professores de maior salário");
      printf("\n 6) Imprimir lista");
      printf("\n 7) Sair");
      printf("\n\t Digite uma opcao: ");
      printf("\n");
      scanf("%d", &opcoes);

      switch (opcoes) {

      case 1: //Inserir
        
        No=CriarNo(inicio);
        printf("Você escolheu a Opção 1\n");
        printf("Digite: \n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        scanf("%d", &tip);
        if (tip==1){
          
          a=(Aluno*)malloc(sizeof(Aluno));
          printf("\nDigite a matrícula do aluno:  ");
          scanf("%d", &a->matricula);
          printf("\nDigite o nome do aluno:  ");
          scanf("%s", a->nome);
          printf("\nDigite o curso do aluno:  ");
          scanf("%s", a->curso);
          printf("\nDigite o ano de ingresso do aluno:  ");
          scanf("%d", &a->ano);
          inicio= InserirInicio(inicio, No, a,tip);}
        
        else if (tip==2){

          p=(Prof*)malloc(sizeof(Prof));
          printf("\nDigite a matrícula do professor:  ");
          scanf("%d", &p->matricula);
          printf("\nDigite o nome do professor:  ");
          scanf("%s", p->nome);
          printf("\nDigite o salário do professor:  ");
          scanf("%d", &p->salario);
          inicio= InserirInicio(inicio, No, p,tip);
        }
        else{
        printf("\nDigite um número válido! ");
  
        break;

      case 2: //remover
        printf("Você escolheu a Opção 2\n");
        printf("\nDigite a matrícula da pessoa que deseja remover: ");
        scanf("%d", &mat);
        inicio=Remover(inicio, mat);
        break;


      case 3: //buscar
        printf("Você escolheu a Opção 3\n");
        printf("\nDigite a matrícula da pessoa que deseja buscar: ");
        scanf("%d", &mat);
        BuscarPessoa(inicio, mat);
        break;
     
      case 4: //contar
        printf("Você escolheu a Opção 4\n");
        printf("\nDigite o curso que deseja buscar: ");
        scanf("%s", curso);
        int cont= ContarAlunosCurso(inicio, curso);
        printf("São %d alunos do curso %s", cont, curso);
        break;

      case 5: //imprimir
        printf("Você escolheu a Opção 5\n");
        ImprimirProfSalario(inicio);
        break;

      case 6: //imprimir lista
          printf("Você escolheu a Opção 6\n");
          ImprimirLista(inicio);
          break;
          
      case 7: // Sair do programa
        printf("Saindo do programa...\n");
        return 0;
      default:
        printf("Opção inválida. Tente novamente.\n");
      }
    }

  }


  

  





  
  return 0;
}