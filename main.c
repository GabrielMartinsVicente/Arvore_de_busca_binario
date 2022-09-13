#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int* gerar_vetor(int tamanho){ //Função que gera o vetor aleatório

  int *vetor = (int*) malloc(sizeof(int)*tamanho);

  int numero_aleatorio;
  int chave;

  for(int i = 0; i<tamanho; i++){   //Algoritmo garante que não vai ter n° aleatórios repetidos
    chave = -1;
    while(chave < i){
      chave = 0;
      numero_aleatorio = 1 + (rand() % 1000);
      for(int j = 0; j<i; j++){
        if(vetor[j] != numero_aleatorio){
          chave++;
        }
      }
    }
    vetor[i] = numero_aleatorio;
  }
    
  return vetor;
}

void exclui_elemento_do_vetor(int vetor[],int valor, int tamanho){

  /* Quando o valor de exclusão é encontrado, recebe valor 0, isto é, "excluindo".
      Posteriormente os valores 0 vão sendo deslocados para o final da minha fila */

  for(int i = 0; i<tamanho; i++){

    if(vetor[i] == valor){
      vetor[i] = 0;

      for(int j=i; j<tamanho; j++){
        if((j+1) == tamanho){
          vetor[j] = 0;
        }
        else{
          vetor[j] = vetor[j+1];
        }

      }
      
    }
    
  }

}

typedef struct vertice{

  int dado;                  //Chave
  struct vertice *direita;   //Filho a direita
  struct vertice *esquerda;  //Filho a esquerda

}vertice;

vertice* cria_vertice(int valor){ /*Função cria um novo vértice na memória
                                    e retorna o endereço de memória */
    vertice *novo;
    novo = (vertice *)malloc(sizeof(vertice));
    novo->dado = valor;
    novo->direita = novo->esquerda = NULL;
    return novo;
 
}

vertice* insercao(vertice *raiz,int valor){ /*Função insere um novo vértice na árvore
                                              e retorna o endereco de memória da raiz
                                               por meio de um ponteiro da estrutura */
  if(raiz == NULL){            
    return cria_vertice(valor);
    //Se a árvore não tiver nenhum vértice (vazia), faz a inserção do novo vértice
  }

  //chave = condição lógica para onde vai ser inserido o novo

  if(valor < (raiz->dado)){    //Se a chave do novo vértice for MENOR que a raiz
    if(raiz->esquerda == NULL){    
      raiz->esquerda = cria_vertice(valor);
      //Se não houver nenhum vértice na esquerda, faz a insercao
    }
    else{
      insercao(raiz->esquerda,valor);  
      /*Recursividade (chama novamente a função), faz a inserção do novo vértice, 
        a partir do filho da esquerda, considerando o filho da esquerda como nova "raiz" */
      }
  }

  if(valor > (raiz->dado)){  //Se a chave do novo vértice for MAIOR que a raiz
    if(raiz->direita == NULL){
      raiz->direita = cria_vertice(valor);
      //Se não houver nenhum vértice na direita, faz a insercao
    }
    else{
      insercao(raiz->direita,valor);
      /*Recursividade (chama novamente a função), faz a inserção do novo vértice, 
        a partir do filho da direita, considerando o filho da direita como nova "raiz" */
      }
    
  }

  return raiz;
  //Retorna o endereco de memória da raiz
    
}

void imprimir_arvore(vertice *raiz,int barra_t){ /* Função faz a impressao da árvore  
                                                      do jeito solicitado*/

  barra_t++; /* Artifício Técnico (gambiarra):
              barra_t é o contador para contar 
                quantos \t vai ser usado*/

  if(raiz != NULL){

    for(int i = 0; i < barra_t; i++){printf("\t");}
    if(barra_t != 1){printf("+");}           // Artifício Técnico para não imprimir "+" na raiz
    printf("%d\n",raiz->dado);
    imprimir_arvore(raiz->esquerda,barra_t); // Algoritmo segue o mesmo padrão de 
    imprimir_arvore(raiz->direita,barra_t);  //  impressão da função 'pre_order'

  }

}

void pre_order(vertice *raiz){ /* Função primeiro faz impressão da raiz,
                                  depois o vértice da esquerda, 
                                      depois o vértice da direita. */

/*
            A
          /   \
         B     C
        / \   / \
       D   E F   G

  Pre_order: {A, B, D, E, C, F, G}


  * Dúvidas do funcionamento?

    * O que é uma função recursiva?
  
      Uma função recursiva é uma função que se refere a si própria durante sua execução
      (podendo ser de forma direta ou indiretamente), podemos observar que a função 
      "pre_order" esta sendo chamada dentro dela mesma.
  
      * Mais dúvidas??
  
        1) Porque usar recursidade? 
        2) Se a função esta chamando ela mesmo a todo momento, não torna-se um loop sem saída?
    
        Resposta:
    
        1) Utilizada usualmente para resolver problemas de caso Geral e Base (simples):

          Base -> É o caso mais simples de todos, cujo resultado é imediato (onde vai 
                  ser encerrado o algoritmo).

          Geral -> É o caso onde vai ser dividido 

      SE SOBRAR TEMPO FINALIZO


*/

  if(raiz != NULL){ // Apenas valores diferentes de NULL
    
    printf("%d",raiz->dado);
    if(raiz->esquerda != NULL){printf(", ");} // Artifício Técnico para imprimir ","
    pre_order(raiz->esquerda);                //Recursividade com o filho da esquerda.         
    if(raiz->direita != NULL){printf(", ");}  // Artifício Técnico para imprimir ","
    pre_order(raiz->direita);                 //Recursividade com o filho da direita.

  }


}

void in_order(vertice *raiz){  /* Função percorre os vértices de forma recursiva 
                                  da esquerda para direita e de baixo para cima, 
                                  começando na raiz. 

            A
          /   \
         B     C
        / \   / \
       D   E F   G

  In_order: {D, B, E, A, F, C, G}

*/
  
  if(raiz != NULL){
    
    in_order(raiz->esquerda);                 //Recursividade com o filho da esquerda.   
    if(raiz->esquerda != NULL){printf(", ");} // Artifício Técnico para imprimir ","
    printf("%d",raiz->dado);                  
    if(raiz->direita != NULL){printf(", ");}  // Artifício Técnico para imprimir ","
    in_order(raiz->direita);                  //Recursividade com o filho da direita.   
    
  }

}

void pos_order(vertice *raiz,int valor_raiz){  /* Função percorre os vértices de forma recursiva, 
                                                  onde a raiz é visitada por último,
                                                  então vemos todos os vértices da árvore esquerda, 
                                                  depois direita e por fim a raiz. 

            A
          /   \
         B     C
        / \   / \
       D   E F   G

  In_order: {D, E, B, F, G, C, A}

*/

  
  if(raiz->esquerda != NULL){
    pos_order(raiz->esquerda,valor_raiz); //Recursividade com o filho da esquerda. 

  }

  if(raiz->direita != NULL){
    pos_order(raiz->direita,valor_raiz); //Recursividade com o filho da direita.

  }

  
  printf("%d",raiz->dado);
  if(raiz->dado != valor_raiz){printf(", ");} /* Artifício Técnico para não imprimir ","
                                                  depois do último valor ser imprimido  */
}  

void encontra_folhas(vertice *raiz){

  if(raiz != NULL){
    
    encontra_folhas(raiz->esquerda);  //Recursividade com o filho da esquerda.
    encontra_folhas(raiz->direita);   //Recursividade com o filho da direita.
    if(raiz->direita == NULL && raiz->esquerda == NULL){
      printf("%d, ",raiz->dado);      /* Só vai ser impresso o valor se for uma folha,
                                          isto é, não tendo nenhum filho */
      
    }

  }
  
}

bool buscar_vertice(vertice *raiz, int valor){ /* Busca Binaria */

  if(raiz == NULL){
    return false;
    //Arvore vazia
  }

  else{
  
    if(valor > raiz->dado){
      return buscar_vertice(raiz->direita,valor);
      /* Se valor de busca for MAIOR que o valor da raiz, continua a busca
            por recursividade pela raiz da direita */
    }
    
    if(valor < raiz->dado){
      return buscar_vertice(raiz->esquerda,valor);
      /* Se valor de busca for MENOR que o valor da raiz, continua a busca
            por recursividade pela raiz da esquerda */
    } 
  
    if(valor == raiz->dado){
      return true;
      //Se encontrou o valor return true
    }
   
  }

  return 0;
}

vertice* apagar_vertice(vertice *raiz,int vertice){

  if(raiz == NULL){
    return NULL;
    //Árvore vazia
  }

  if(raiz != NULL){
      
    if(vertice > raiz->dado){ //Verificando se o valor é MAIOR
      raiz->direita = apagar_vertice(raiz->direita,vertice);
      //Recursividade com a busca sendo a partir do filho da direita
    }
    
    if(vertice < raiz->dado){ //Verificando se o valor é MENOR
      raiz->esquerda = apagar_vertice(raiz->esquerda,vertice);
      //Recursividade com a busca sendo a partir do filho da esquerda
    } 
  
    if(vertice == raiz->dado){ //Encontrou vértice

      if(raiz->direita == NULL && raiz->esquerda == NULL){ //Exclusão de um Vértice Folha
        free(raiz);
        return NULL;
        
      }

      if(raiz->direita == NULL && raiz->esquerda != NULL){ //Vértice com filho a esquerda
        struct vertice *aux;  //ponteiro auxiliar para fazer a troca
        aux = raiz->esquerda;
        free(raiz);
        return aux;
        
      }

      if(raiz->direita != NULL && raiz->esquerda == NULL){  //Vértice com filho a direita
        struct vertice *aux;  //ponteiro auxiliar para fazer a troca
        aux = raiz->direita;
        free(raiz);
        return aux;
        
      }

      else{ //Vértice com filho a direita e esquerda
        struct vertice *aux = raiz->esquerda;
        while(aux->direita != NULL){
          aux = aux->direita;
          /*Encontrando o último vértice na extrema direita
             para fazer a troca e não perder a sequência */
        }
        raiz->dado = aux->dado;
        aux->dado = vertice;
        raiz->esquerda = apagar_vertice(raiz->esquerda,vertice);
         /* Após a troca ser feita, o vértice que vai ser excluido se torna um vértice
            com um filho na esquerda ou um filho na direita ou pode ser apenas um nó,
            isto é, os métodos de exclusão para essas situações já existem. */
        return raiz;
        
      }
    
    }
    
  }

  return raiz;
}

bool valida(vertice *raiz,int n_vertices){

  /* Método de validação utiliza a metodologia In-Order para identificar
      se de fato é uma estrutura de árvore binaria de busca, para isso,
      utilizando uma estrutura de pilha auxiliar foi posssivel adicionar
      os valores em um array e depois verificar se os valores estão em
      ordem crescente */

  int posicao = 0, posicao_vetor = 0;
  struct vertice *aux, *pilha[n_vertices];
  int valores[n_vertices], troca;
  aux = raiz;

  while(aux != NULL || posicao > 0){

    if(aux != NULL){
      pilha[posicao++] = aux;
      aux = aux->esquerda;

    }

    else{
      aux = pilha[--posicao];
      valores[posicao_vetor++] = aux->dado;
      aux = aux->direita;
    }
    
  }

  for(int i = 0; i < n_vertices; i++){ //Verificando se os valores estão em Ordem Crescente
    for(int j = i+1; j < n_vertices; j++){ 
      if(valores[j] < valores[i]){
        return false;
      }
    }
  }

  return true;
}

int main(){

  srand(time(NULL));

  int n_vertices =  10 + (rand() % 17);
  vertice *raiz = (vertice*) NULL;
  int valor_aleatorio, n_arvore = 1, n_insercoes = 10, n_exclusao = 10; 
  int *vetor = gerar_vetor(n_vertices+n_insercoes); /* Vetor tem 20 espaços de memória para ser
                                                      reciclado nas operações */
  clock_t tempo;
  double soma = 0, media = 0;
  double populacao[10];
  
  
  for(int i = 0; i<n_vertices;i++){
    raiz = insercao(raiz,vetor[i]);
  }  

  //------------------------ 1° PARTE --------------------------------
  
  while(n_arvore <= 10){

    printf("\n\n___________________ %d° ARVORE ___________________\n\n",n_arvore);

    printf("\n1° Saída: \n\n");
    printf("Array Gerado: [");
    for(int i = 0; i<n_vertices; i++){
  
      if(n_vertices == i+1 ){
        printf("%d] \n",vetor[i]);
      }
      else{
        printf("%d, ",vetor[i]);
      }
     
    }
    
  //------------------------ 2° PARTE --------------------------------
    
    printf("\n2° Saída: \n\n");
  
    imprimir_arvore(raiz,0);
    
    printf("\n");
  
  //------------------------ 3° PARTE --------------------------------
  
    printf("\n3° Saída: \n\n");
    printf("Pre-order:{");
    pre_order(raiz);
    printf("}");
    
    printf("\n\n");
    
    printf("In-order:{");
    in_order(raiz);
    printf("}");
  
    printf("\n\n");
    printf("Pos-order:{");
    pos_order(raiz,vetor[0]);
    printf("}");
  
  //------------------------ 4° PARTE --------------------------------
   
    printf("\n\n4° Saída: \n\n");
    printf("Folhas: [");
    encontra_folhas(raiz);
    printf("]");
  
  //------------------------ 5° PARTE --------------------------------
    
    printf("\n\n\n5° Saída: \n\n");
  
    for(int i  = 0; i<10; i++){
      
      valor_aleatorio = (300 + (rand() % 276));
  
      if(buscar_vertice(raiz,valor_aleatorio) == true){
        printf("\nValor gerado: %d; Diagnóstico: presente\n",valor_aleatorio);
      }
  
      else{
        printf("\nValor gerado: %d; Diagnóstico: Ausente\n",valor_aleatorio);
      }
        
    }
     
  //------------------------ 6° PARTE: VALIDACAO INSERCAO -------------------------------
  
    printf("\n\nVALIDAÇÃO:\n");
  
    for(int i = 0; i<n_insercoes;i++){
      
      tempo = clock();
      valor_aleatorio = 1 + (rand() % 1000);
      while(buscar_vertice(raiz,valor_aleatorio) == true){ /* Verificando se o valor já esta 
                                                                na árvore */
        valor_aleatorio = 1 + (rand() % 1000);
      }

      vetor[n_vertices + i] = valor_aleatorio;
      raiz = insercao(raiz,valor_aleatorio);
      tempo = clock() - tempo;
      populacao[i] = ((double)tempo)/CLOCKS_PER_SEC;
      
    }

    soma = 0;
    for(int i = 0;i<n_insercoes;i++){  //Somatório de todos os tempos para depois fazer a média
      soma += populacao[i];
    }
  
    media = (double)((soma)/n_insercoes);
  
    if(valida(raiz,n_vertices+n_insercoes) == true){
      printf("\nInserções: %d; árvore geradas: %d; árvore validada %d\n",n_insercoes,n_arvore,n_arvore);
    }
  
    else{
      printf("\nInserções: %d; árvore geradas: %d; árvore invalidada %d\n",n_insercoes,n_arvore,n_arvore);
    }
  
    printf("Tempo médio para inserção: %fs\n\n",(double)((soma)/n_insercoes));
  
  
  //------------------------ 7° PARTE: VALIDACAO EXCLUSAO --------------------------------

    for(int i = 0; i<n_exclusao;i++){
      
      tempo = clock();
      valor_aleatorio = 1 + (rand() % 1000);
      while(buscar_vertice(raiz,valor_aleatorio) == false){ /* Verificando se o valor já esta 
                                                                na árvore */ 
        valor_aleatorio = 1 + (rand() % 1000);
      }
      
      exclui_elemento_do_vetor(vetor,valor_aleatorio,n_vertices+n_insercoes);
      raiz = apagar_vertice(raiz,valor_aleatorio);
      tempo = clock() - tempo;
      populacao[i] = ((double)tempo)/CLOCKS_PER_SEC;
      
    }
  
    soma = 0;
    for(int i = 0;i<n_exclusao;i++){  //Somatório de todos os tempos para depois fazer a média
      soma += populacao[i];
    }
  
    media = (double)((soma)/n_exclusao);
  
    if(valida(raiz,n_vertices) == true){
      printf("\nExclusões: %d; árvore geradas: %d; árvore validada %d\n",n_exclusao,n_arvore,n_arvore);
    }
  
    else{
      printf("\nExclusões: %d; árvore geradas: %d; árvore invalidada %d\n",n_exclusao,n_arvore,n_arvore);
    }
  
    printf("Tempo médio para exclusão: %fs\n\n",(double)((soma)/n_exclusao));

  n_arvore++;
    
  }

  
  return 0;
}