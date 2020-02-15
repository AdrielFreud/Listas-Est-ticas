#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaSequencial.h"

int main(void){
	Lista *li;
	struct aluno al;

	al.matricula = 3;
	strcpy(al.nome, "Adriel F.");
	al.n1 = 60;
	al.n2 = 50.0;
	al.n3 = 71.2;

	li = cria_lista();
	insere_lista_inicio(li, al);
	int x = tamanho_lista(li);

	printf("[+] Tamanho Lista: %d\n", x);

	if(lista_cheia(li)){
		printf("[!] Tamanho Lista: %d\n", lista_cheia(li));
	}

	if(lista_vazia(li)){
		printf("[+] Lista Vazia!\n");
	}

	x = consulta_lista_mat(li, 1, &al);
	printf("Consultando por Matricula: %d\n", x);
	
	x = consulta_lista_pos(li, 1, &al);
	printf("Consultando por Posicao: %d\n", x);

	remove_lista(li, 3);
	libera_lista(li);
	
	return 0;
}

Lista *cria_lista(void){
	Lista *li;
	li = (Lista *)malloc(sizeof(Lista));
	if(li != NULL){
		li->qtd = 0;
	}
	return li;
}

void libera_lista(Lista *li){
	free(li);
}

int tamanho_lista(Lista *li){
	if(li == NULL){
		return -1;
	}else{
		return li->qtd;
	}
}

int lista_cheia(Lista *li){
	if(li == NULL){
		return -1;
	}else{
		return (li->qtd == MAX);
	}
}

int lista_vazia(Lista *li){
	if(li == NULL){
		return -1;
	}else{
		return (li->qtd == 0);
	}
}

int insere_lista_final(Lista *li, struct aluno al){

	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}

	li->dados[li->qtd] = al;
	li->qtd++;

	return 1;
}

int insere_lista_inicio(Lista *li, struct aluno al){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li)){
		return 0;
	}

	for(int i = li->qtd-1; i>0; i--){
		li->dados[i+1] = li->dados[i];
	}

	li->dados[0] = al;
	li->qtd++;

	return 1;
}

int insere_lista_ordenada(Lista *li, struct aluno al){
	if(li == NULL) return 0;
	if(lista_cheia(li)) return 0;

	int k, i = 0;
	while(i < li->qtd && li->dados[i].matricula < al.matricula){
		i++;
	}

	for(k = li->qtd-1; k >= i; k--){
		li->dados[k+1] = li->dados[k];
	}

	li->dados[i] = al;
	li->qtd++;

	return 1;
}

int remove_lista_final(Lista *li){
	if(li == NULL){
		return 0;
	}

	if(li->qtd == 0){
		return 0;
	}

	li->qtd--;

	return 1;
}

int remove_lista_inicio(Lista *li){
	if(li == NULL) return 0;
	if(li->qtd == 0) return 0;

	int k = 0;

	for(k = 0; k < li->qtd-1; k++){
		li->dados[k] = li->dados[k+1];
	}
	li->qtd--;

	return 1;
}

int remove_lista(Lista *li, int mat){
	if(li == NULL){
		return 0;
	}
	if(li->qtd == 0){
		return 0;
	}

	int k, i = 0;

	while(i < li->qtd && li->dados[i].matricula != mat){
		i++;
	}

	if(i == li->qtd){
		return 0;
	}

	for(k = i; k < li->qtd-1; k++){
		li->dados[k] = li->dados[k+1];
	}
	
	li->qtd--;

	return 1;
}

int consulta_lista_mat(Lista *li, int mat, struct aluno *al){
	if(li == NULL) return 0;

	int k, i = 0;

	while(i < li->qtd && li->dados[i].matricula != mat){
		i++;
	}
	if(i == li->qtd) return 0;

	*al = li->dados[i];
	return 1;

}

int consulta_lista_pos(Lista *li, int pos, struct aluno *al){
	if(li == NULL || pos <= 0 || pos > li->qtd) return 0; 

	*al = li->dados[pos-1];
	return 1;
}
