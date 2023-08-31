
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct node{
    char* key;
    int value;
    struct node* next;
}node;

// Defines the HashTable.
typedef struct HashTable{
    node** array;
	int size;
} HashTable;


HashTable* initHashTable(HashTable *table,int size);
void printHashTable(HashTable* ht);
int hash_function1(int size,char* string,int n);
int hash_function2(int size,int number);
node* create_node(char* key,int size);
void insertInHashTable(HashTable* ht,char* key);
bool searchInHashTable(HashTable *ht,char *key);
void printSearch(HashTable* ht,char* key);
void deleteFromHashTable(HashTable* ht,char* key);



int main(){
	
	int size = 5;
	
	printf("----- Create Hash Table---------------\n");
	
	HashTable* ht = initHashTable(ht,size);    
	printHashTable(ht);
	
//	char word[] = "word";
//	int n = strlen(word);
	
	printf("----- Add items-----------------------\n");
//	8,11,12,15,20,27,34,45,56,70

	insertInHashTable(ht,"8");
	insertInHashTable(ht,"11");
	insertInHashTable(ht,"12");
	insertInHashTable(ht,"15");
	insertInHashTable(ht,"20");
	insertInHashTable(ht,"27");
	insertInHashTable(ht,"34");
	insertInHashTable(ht,"45");	
	insertInHashTable(ht,"56");
	insertInHashTable(ht,"70");
	
	printHashTable(ht);
	
	printf("----- delete items--------------------\n");
//  34,70,11

	deleteFromHashTable(ht,"70");
	deleteFromHashTable(ht,"34");
	
	printHashTable(ht);
	
	printf("----- search items--------------------\n");
//  70,45,11
	
	printSearch(ht,"23");	
	printSearch(ht,"70");
	printSearch(ht,"11");
	
	
}

int hash_function1(int size,char* string,int n){
    
    int hash = 0;
    for(int i = 0; i < n; i++) {
        hash = hash + (string[i] % size) ;
    }
    
    return hash;
}

int hash_function2(int size,int number){
    
    int hash = 0;
    
    hash = hash + (number % size) ;
    
    return hash;
}
	
HashTable* initHashTable(HashTable *table,int size){
    
	table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->array = (node**)calloc(table->size, sizeof(node *));
     
    for(int i = 0; i <table->size; i++){
    	table->array[i] = NULL;
	}
	
	return table;
}

node* create_node(char* key,int size){
	
	node* item = (node *)malloc(sizeof(node));
    item->key = (char *)malloc(strlen(key) + 1);
    item->key = key;
    item->value = hash_function1(size,item->key,strlen(key) + 1);
    item->value = hash_function2(size,item->value);
    
    item->next = NULL;
    
    return item;
}

void insertInHashTable(HashTable* ht,char* key){
    
	//create a newnode with value
    node *item = create_node(key,ht->size);
    int index = item->value;
    
//    int i;
//	sscanf(key, "%d", &i);   from char to int 
    
    if(ht->array[index] == NULL){
    	ht->array[index] = item;
	}else{  //collision
        //add the node at the head of array[key].
		// node *temp = ht->array[i];
		item->next = ht->array[index];
		ht->array[index] = item;
    }
    
}

bool searchInHashTable(HashTable *ht,char *key){
    // Searches for the key in the HashTable.
    bool trv = false;
    
	for(int i = 0; i < ht->size; i++){
        node *temp = ht->array[i];
        while(temp != NULL){
            if (temp->key == key){
				trv = true;
				break;
			}
			temp = temp->next;
	    }    
	}
	
	return trv;
}

void printSearch(HashTable* ht,char* key){
	
	bool trv = searchInHashTable(ht,key);
	if(trv == true){
		printf("la cle %s existe\n",key);
	}else{
		printf("la cle %s n'existe pas\n",key);
	}
	
}

void printHashTable(HashTable* ht){
  
    for(int i = 0; i < ht->size; i++){
        node *temp = ht->array[i];
        printf("array[%d]-->",i);
        while(temp){
            printf("%s -->",temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void deleteFromHashTable(HashTable* ht,char* key) {
    
	int index = hash_function2(ht->size, hash_function1(ht->size, key, strlen(key)));
    node* temp = ht->array[index];
    node* prev = NULL;
    
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
                // node to be deleted is the head of the linked list
                ht->array[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

/*
Time Complexity:

Search : O(1+(n/m))
Delete : O(1+(n/m))
where n =  Total elements in hash table , m = Size of hash table
Here n/m is the Load Factor.
Load Factor (?) must be as small as possible.
If load factor increases,then possibility of collision increases.
Load factor is trade of space and time .
Assume , uniform distribution of keys ,
Expected chain length : O(?)
Expected time to search : O( 1 + ? )
Expected time to insert/ delete :  O( 1 + ? )
Auxiliary Space: O(1), since no extra space has been taken.
*/