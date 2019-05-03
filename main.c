/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vitor
 *
 * Created on 2 de Maio de 2019, 15:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int id; //elemento aleatorio, definimos aqui para um numero int
}obj;

typedef struct noLista *ponteiro; //definicao dos ponteiros para serem usados

typedef struct{
    obj objeto; //obj dentro de no de lista
    ponteiro decima; 
    ponteiro debaixo;
    //imaginando a lista como uma literalmente lista para melhor compreensao
}noLista;

typedef struct{
    ponteiro first; //primeiro [atribuido no enlistar/desenlistar]
    ponteiro last; //ultimo [atribuido no enlistar/desenlistar]
    int tam; //tamanho
}LISTA;










void iniciaLista(LISTA *lista){
    lista->first = NULL;
    lista->tam = 0;
}

int tamanhoLista(LISTA *lista){
    return lista->tam;
}

bool estaVazia(LISTA *lista){
    return (lista->tam == 0);
}

void enlista(int X, LISTA *lista){
    ponteiro aux;
    
    aux = (ponteiro) malloc(sizeof(noLista));
    
    aux->objeto.id = X;
    if (estaVazia(lista)){
        aux->debaixo = NULL;
        aux->decima = NULL;
        lista->first = aux;
        lista->last = aux;
        lista->tam ++;
    }
    else{
        ponteiro auxteiro;
        auxteiro = lista->first;
        while(auxteiro->debaixo != NULL && X > auxteiro->objeto.id)
            auxteiro = auxteiro->debaixo;
        aux->debaixo = auxteiro;
        aux->decima = auxteiro->decima;
        auxteiro->decima = aux;
        aux->decima->debaixo = aux;
        free(auxteiro);
        lista->tam ++;
    }
}

void desenlista(LISTA *lista, int escolha){
    if (estaVazia(lista)){
        printf("erro: lista vazia");
        exit(3);
    }
    else{
        switch(escolha){
            case 1:{ //fim
                noLista aux;
                aux = lista->last;
                printf("item desenlistado: %i"
                        "\n[PRESSIONE ALGO PARA CONTINUAR]\n", lista->last->objeto.id);
                lista->last = lista->last->decima;
                lista->last->debaixo = NULL;
                free(aux);
            }
            case 2:{ //comeco
                noLista aux;
                aux = lista->first;
                printf("item desenlistado: %i"
                        "\n[PRESSIONE ALGO PARA CONTINUAR]\n", lista->first->objeto.id);
                lista->first = lista->first->debaixo;
                lista->first->decima = NULL;
                free(aux);
            }
        }
        lista->tam --;
    }
}

void imprimelista(LISTA *lista, int reverso){
    ponteiro auxteiro;
    if (reverso == 0){
        auxteiro = lista->first;
        printf("\nimprimindo lista...\n[ELEMENTOS DA LISTA:");
        while(auxteiro->debaixo != NULL){
            printf(" %i", auxteiro->objeto.id);
            auxteiro = auxteiro->debaixo;
        }
    }
    else{ //note que o de cima [reversao = 0] utiliza auxteiro->debaixo
          //e o de baixo [reversao != 0, ou seja, 1] utiliza auxteiro->decima
        auxteiro = lista->last;
        printf("\nimprimindo lista...\n[ELEMENTOS DA LISTA:");
        while(auxteiro->decima != NULL){
            printf(" %i", auxteiro->objeto.id);
            auxteiro = auxteiro->decima;
        }
    }
    printf("]"
            "\n[PRESSIONE ALGO PARA CONTINUAR]\n");
    getc();
}

int primeiro(LISTA *lista){
    int X;
    X = lista->first->objeto.id;
    return X;
}

int ultimo(LISTA *lista){
    int Y;
    Y = lista->last->objeto.id;
    return Y;
}

void destroilista(LISTA *lista){
    ponteiro auxteiro;
    auxteiro = lista->first;
    while(auxteiro->debaixo != NULL){
        free(auxteiro);
        auxteiro = auxteiro->debaixo;
    }
    printf("\nlista destruida........................"
            "\n[PRESSIONE ALGO PARA CONTINUAR]\n");
}

int pesquisa(LISTA *lista, int pesq){
    ponteiro auxteiro;
    auxteiro = lista->first;
    while(auxteiro->debaixo != NULL || auxteiro->objeto.id != pesq)
        auxteiro = auxteiro->debaixo;
    
    if (auxteiro->debaixo == NULL && auxteiro->objeto.id != pesq)
        return 0;
    if (auxteiro->objeto.id == pesq)
        return 1;
}

void removeelemento(LISTA *lista, int elem){
    ponteiro auxteiro;
    auxteiro = lista->first;
    while(auxteiro->objeto.id != elem)
        auxteiro = auxteiro->debaixo;
    
    noLista aux;
    aux = (ponteiro) malloc(sizeof(noLista));
    aux = auxteiro;
    auxteiro->debaixo->decima = auxteiro->decima;
    auxteiro->decima->debaixo = auxteiro->debaixo;
    free(aux);
    lista->tam --;
}




/*
 * 
 */
int main(int argc, char** argv) {
    LISTA listadupla;
    iniciaLista(&listadupla);
    printf("Tamanho atual da lista: %i\n"
            "[PRESSIONE ALGO PARA CONTINUAR]\n", tamanhoLista(&listadupla));
    
    getchar();
    
    if (estaVazia(&listadupla))
        printf("ta vazia");
    else
        printf("tem algo na lista");
    
    int inserir;
    printf("\nDigite um numero a ser inserido na lista: ");
    scanf("%i", &inserir);
    enlista(inserir, &listadupla);
    
    int escolha;
    printf("\nescolha se deve desenlistar do fim ou comeco"
            "[1-fim ou 2-comeco]: ");
    scanf("%i", &escolha);
    switch (escolha){
        case 1:{
            desenlista(&listadupla, escolha);
            return;
        }
        case 2:{
            desenlista(&listadupla, escolha);
            return;
        }
        default:{
            printf("erro, numero selecionado nao eh 1 nem 2");
            return;
        }
    }
    getc();
    
    printf("\ntamanho da lista: %i\n", tamanhoLista(&listadupla));
    getc();
    
    int reversao;
    printf("\nseleciona para imprimir[0-normal, 1-reverso]: ");
    scanf("%i", &reversao);
    imprimelista(&listadupla, reversao);
    
    printf("\nPRIMEIRO numero da lista: %i"
            "\n[PRESSIONE ALGO PARA CONTINUAR]\n", primeiro(&listadupla));
    getc();
    
    printf("\nULTIMO numero da lista: %i"
            "\n[PRESSIONE ALGO PARA CONTINUAR]\n", ultimo(&listadupla));
    getc();
    
    if (estaVazia == 0){
        int pesquisar;
        printf("\ndigite um numero para pesquisar: ");
        scanf("%i", &pesquisar);
        if (pesquisa(&listadupla, pesquisar))
            printf("\no elemento %i esta na lista.\n", pesquisar);
        else
            printf("\no elemento %i NAO esta na lista.\n", pesquisar);

        printf("\nremover o elemento?[1-sim, 0-nao]: ");
        scanf("%i", &escolha);
        if (escolha == 1)
            removeelemento(pesquisar, &listadupla);
        printf("item removido.\n"
                "[PRESSIONE ALGO PARA CONTINUAR]\n");
        getc();
    }
    
    destroilista(&listadupla);
    return (EXIT_SUCCESS);
}

/*
//void iniciaLista(ListaDupla *list); 
//void imprimeLista(ListaDupla *list); 
//void imprimeListaReversa(ListaDupla *list);
//void destroiLista(ListaDupla *list); 
//bool insere(ListaDupla *list, Item x); 
//bool estaVazia(ListaDupla *list);
//bool pesquisa(ListaDupla *list, int key);
//bool removeElemento(ListaDupla *list, int key, Item *item);
//bool removePrimeiro(ListaDupla *list, Item *item);
//bool removeUltimo(ListaDupla *list, Item *item);
//int tamanhoLista(ListaDupla *list);
//Item primeiro(ListaDupla *list);
//Item ultimo(ListaDupla *list);
 */