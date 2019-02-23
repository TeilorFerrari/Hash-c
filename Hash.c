#include <stdio.h>
#include <stdlib.h>


typedef struct Hashe{
	int *vet;
	int size_table;
	int chavezInseridas;
}Hash;	


int FuncHash(int key, int size_table){
	return (key & 0x7FFFFFFF) % size_table;
}

Hash *iniciaHash(int size_table){
	Hash *acessoHash;

	acessoHash = malloc(sizeof(int));
	acessoHash->chavezInseridas=0;
	if(acessoHash==  NULL){
		return 0;
	}
	acessoHash->size_table = size_table;
	acessoHash->vet = malloc(size_table*sizeof(int));
	if(acessoHash ==  NULL){
		return 0;
		free(acessoHash);
	}
	for (int i = 0; i < size_table; ++i)
	{
		acessoHash->vet[i]=NULL;
	}
	return acessoHash;
}

Hash *insere_ReHash( Hash *acessoHash, Hash *ReHash){
	int i=0,k=0, posicao=0;

	printf("entrou no rehase");
	for(i=0; i<acessoHash->size_table; i++){
		posicao = FuncHash(acessoHash->vet[i], ReHash->size_table);
 		
 		if(ReHash->vet[posicao]==NULL){
 			ReHash->vet[posicao] = acessoHash->vet[i];
 			ReHash->chavezInseridas++;
 		}else if(ReHash->vet[posicao]==acessoHash->vet[i]){
		return 0;
		}
		else{ 
			for (int k = posicao+1 ; k < ReHash->size_table; ++k){
				if(ReHash->vet[k]==acessoHash->vet[i]){
					return 0;
				}
				if(ReHash->vet[k]== NULL){
					ReHash->vet[k] = acessoHash->vet[i];	
					ReHash->chavezInseridas++;	
					break;	
				}
			}	
		}
 	}

	return ReHash;
}

Hash *insere(int key, Hash *acessoHash){
	int i =0, k=0,new_size;
	int posicao;
	int chave = key;
	Hash *ReHash;
	printf("qtd chavezInseridas: %d\n----", acessoHash->chavezInseridas);
	printf("tamanho da tabela %d ", acessoHash->size_table);

	if(acessoHash->chavezInseridas >= acessoHash->size_table){
	
		printf("cheia\n");
		ReHash = iniciaHash(acessoHash->size_table*2);
		printf("tamnaho rehash%d-----\n",ReHash->size_table);
		for(i=0; i< acessoHash->size_table;i++){
			printf("entrou no for\n");
			if(acessoHash->vet[i]!= NULL){
				printf("entrou no if\n");
				ReHash = insere(acessoHash->vet[i], ReHash);
				printf("chamou a rerash\n");
			//	ReHash->vet[i] = acessoHashs->vet[i];
				//printf("rehash : %d \n--",ReHash->vet[i]);
			}
			printf("passou pelo if \n");
		}
		printf("fim ReHash");
		ReHash->chavezInseridas = acessoHash->chavezInseridas;
		acessoHash = ReHash;
		printf("tamanho acesso hashs: %d \n",acessoHash->size_table);
	}



	/*	printf("antes do malloc");
		new_size = (acessoHash->size_table*2);
		ReHash->vet = malloc(new_size * sizeof(int));

		printf("entrou no if##@@@@");

		acessoHash = insere_ReHash(acessoHash, ReHash);
	}
		*/
	printf("nao entrou no if ");
	

	if(acessoHash == NULL){
		return 0;
	}

	posicao = FuncHash(chave, acessoHash->size_table);
	
	if (acessoHash->vet[posicao]==NULL)
	{
		acessoHash->vet[posicao] = chave;
		acessoHash->chavezInseridas++;
	}else if(acessoHash->vet[posicao]==key){
		return 0;
	}
	else{ 
		for (int i = posicao+1 ; i < acessoHash->size_table; ++i){
			if(acessoHash->vet[i]==key){
				return 0;
			}
			if(acessoHash->vet[i]== NULL){
				acessoHash->vet[i] = chave;	
				acessoHash->chavezInseridas++;	
				break;	
			}
		}	
	}
	
return 1;	
}
void libera(Hash *acessoHash){
	if(acessoHash!=NULL){
		for(int i=0; i<acessoHash->size_table; i++){
			free(acessoHash->vet[i]);
		}
		free(acessoHash->vet);
	}
}

int main(){
	int tamanho = 10;
	int qtdchaves=15;
	int key;
	int ok;

	Hash *novo;
 	novo = iniciaHash(tamanho);
	
	clock_t begin = clock();
	for(int i=0;i < qtdchaves;i++){
		key =rand() % 1000;
		ok = insere(key ,novo);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin)/60; //CLOCKS_PER_SEC;
	printf("%f\n", time_spent);

	for(int i=0;i<tamanho;i++){
		printf("%d \n", novo->vet[i]);
	}


	return 0;
}
