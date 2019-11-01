#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#define N 4

int referencias[] = {0,2,1,3,5,4,6,3,7,4,7,3,3,5,5,3,1,1,1,7,1,3,4,1};
int fila[N];
int primeiro, ultimo;
int refs;
/*Funções para implementação da fila*/
void inicia_fila(){
  primeiro =0;
  ultimo =-1;
}

bool fila_vazia(){
  if (primeiro>ultimo) return false;
  else return true;
}

bool fila_cheia(){
  if (ultimo==refs-1) return false;
  else{
    return true;
  }

}


bool insere_fila(int valor){
  if (fila_cheia()) return false;
  else{
    ultimo++;
    fila[ultimo]=valor;
    return true;
  }
}
bool retira_fila(int valor){
  if (fila_vazia()) return false;
  else{
    valor = fila[primeiro];
    primeiro++;
    return true;
  }
}
bool procura_ref(int ref,int *fila){
  int achou=0;
  for(int i=0;i<N;i++){
    if(ref==fila[i]) return true;
    else{
      achou=1;
    }
  }
  if (achou==1){
    return false;
  }

}
int fifo(int quadros){
  int i=0;
  int aux;
  int falhas =0;
  while(fila_vazia()){
    inicia_fila();
    for(i=0;i<quadros;i++){
      fila[i] = referencias[i];
      falhas++;
    }
    aux=quadros;
  }
/*  for(int i=0;i<N;i++){
    printf("%d,",fila[i]);
  }*/
  while(aux !=23){


    for(i=0;i<(23-aux);i++){
      if(procura_ref(referencias[aux],fila)){
        aux++;
      }
      else{
        retira_fila(fila[aux]);
        insere_fila(referencias[aux]);
        falhas++;
        aux++;
        break;
      }
    }
  }
  return falhas;
}
struct referencias{
  int ref;
  int tempoChegada;
};
bool procura_ref_lru(int ref,struct referencias *fila){
  int achou=0;
  for(int i=0;i<N;i++){
    if(ref==fila[i].ref) return true;
    else{
      achou=1;
    }
  }
  if (achou==1){
    return false;
  }
}
bool inicia_estrutura(struct referencias *r){
  r[0].ref = -1;
}

int lru(int quadros,struct referencias *r){
  int i=0,aux=0;
  int menor=0;
  int lrufalhas =0;

  if(r[0].ref !=-1){
    inicia_estrutura(r);

    for(i=0;i<quadros;i++){
      r[i].ref = referencias[i];
      r[i].tempoChegada = i;
      lrufalhas++;
      //printf("%d,",lrufalhas);
    }
    aux=quadros;
  }
  /*for(int i=0;i<N;i++){
    printf("%d,",fila[i]);
  }*/
  while(aux !=23){

    for(i=0;i<=(23-aux);i++){
      if(procura_ref_lru(referencias[aux],r)){
        aux++;
        r[i].tempoChegada = aux;
      }
      else{
        menor = i;
        for(i=0;i<quadros;i++){
          if(r[i+1].tempoChegada < r[i].tempoChegada){
            menor =i+1;
          }
        }
        r[menor].ref=referencias[aux];
        r[menor].tempoChegada = aux;
        lrufalhas++;
        printf("%d,",lrufalhas);
        aux++;
        break;
      }
    }
  }
  return lrufalhas-1;
}
struct quant_refs{
  int referencia;
  int quantidade;
};
bool procura_ref_opt(int ref,struct quant_refs *o){
  int achou=0;
  for(int i=0;i<N;i++){
    if(ref==o[i].referencia) return true;
    else{
      achou=1;
    }
  }
  if (achou==1){
    return false;
  }
}


/*int conta_refs(struct quant_refs *r){
  for (int i = 0; i < 23; i++) {
    if (refs == o[i].referencia) {
      o[i].quantidade --;
      return true;
    }
    else{
      return false;
    }
}*/
void inicia_repeticoes(struct quant_refs *lista){
  for (int i = 0; i < 10; i++) {
    lista[i].referencia = i;
    lista[i].quantidade = 0;
  //  printf("%d vezes: %d\n",lista[i].referencia,lista[i].quantidade );
  }
}
int contaLinhas(FILE *arq){
  int numLinhas=0;
  int caracter;
  while (!feof(arq)) {
    fgets(caracter,100,arq);
    numLinhas++;
  }
  return numLinhas;
}
//Função principal
int main(int argc, char* argv[]) {
    int fifofalhas=0,lrufalhas=0, optfalhas=0;
    int quadros = atoi(argv[1]);
    struct referencias r[quadros];
    struct quant_refs o[23];
    int i,j,a,aux=0,cont=0, menor;
    int clone_refs[23];
    struct quant_refs lista[10];
    int *ref; //ponteiro para referÊncias
    FILE *arqRef; //arquivos dos dados de entrada
    int  vetor[1000];


    //le e valida os parametros de entrada
      if(argc < 3) {
       fprintf(stderr, "Digite: %s <quadros disponíveis> < <arquivo de referências> .\n", argv[0]);
       return 1;
    }

    //lê e armazena o numero de quadros
    quadros =  atoi(argv[1]);

   // printf("Quadros: %d\n",quadros);

    //abre o arquivo da lista de referências
    arqRef = fopen(argv[3], "r");
    //confere se o arquivo foi aberto corretamente
    if(arqRef == NULL) {
       fprintf(stderr, "Erro ao abrir o arquivo da lista de referências.\n");
       return 1;
    }

    //conta a quantidade de referências tem
    refs = contaLinhas(arqRef);

    fifofalhas = fifo(quadros);
    lrufalhas = lru(quadros,r);
/*    inicia_repeticoes(lista);

  for (int i = 0; i < 23; i++){
    clone_refs[i] = referencias[i];
    //  printf("%d\n",clone_refs[i] );
  }
  for (int i = 0; i < 23; i++){
    for (int j = 0; j < 23; j++){
          if (clone_refs[i] < clone_refs[j]){
            //aqui acontece a troca, do maior cara  vaia para a direita e o menor para a esquerda
            aux = clone_refs[i];
            clone_refs[i] = clone_refs[j];
            clone_refs[j] = aux;

          }
    }

  }
  for (int i = 0; i < 23; i++){
    o[i].referencia = referencias[i];
      //printf(" - %d\n",o[i].referencia );
  }

  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 23; j++){
          if (clone_refs[j] == lista[i].referencia){
            lista[i].quantidade +=1;
          }
    }
  //   printf("%d vezes: %d\n",lista[i].referencia,lista[i].quantidade );
}
    for (i = 0; i < 23; i++) {
      for ( j = 0; j < 10; j++) {
        if (o[i].referencia == lista[j].referencia) {
          o[i].quantidade =lista[j].quantidade;
        }
      }
    //  printf("referencia: %d, vezes referenciadas: %d\n",o[i].referencia,o[i].quantidade );
    }


    for(i=0;i<quadros;i++){
      fila[i] = o[i].referencia;
      o[i].quantidade-=1;
    //  optfalhas++;
    }
    printf("falha%d\n",optfalhas );
    if(optfalhas>=quadros){
      for(i=quadros;i<23;i++){
        for (size_t j = 0; j < count; j++) {
          if(fila[i]==o[j].referencia)){
           o[i].quantidade -=1;
        //    break;
          }
        }
}
        menor=1;
            for (int i = 0; i < quadros; i++){
              if (o[i].quantidade <= menor){
                lista[i].referencia = o[i].referencia;
                menor = o[i].referencia;
              }
            }

            lista[menor].quantidade -=1;
            //optfalhas++;
          }
          }
      }


*/
    printf("\n%d quadros, FIFO: %d falhas, LRU: %d falhas, OPT: %d falhas.\n",quadros,fifofalhas,lrufalhas,optfalhas);
    return 0;
}
