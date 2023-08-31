/* HASHING - LINEAR AND QUADRATIC PROBING */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


int hasht(int key,int tsize);
int rehashl(int key,int tsize); //-------LINEAR PROBING-------
int rehashq(int key, int j,int tsize); //-------QUADRATIC PROBING-------


int main(){
	
	int arr[] = {10,23,35,65,45,30};
	int tsize = 10;
	int hash[10];
	int op, key,k,i,j;
	int n = sizeof(arr)/sizeof(arr[0]);
	
	do{
		printf("--------------------\n");
		printf("1.Linear Probing\n2.Quadratic Probing \n3.Exit");
		printf("\n------------------\n");
		printf("Enter your option:");
		scanf("%d",&op);
		
		switch(op){
			case 1:
				memset(hash, -1, tsize*sizeof(hash[0]));
							
				for(k=0;k<n;k++){
					key=arr[k];
					i = hasht(key,tsize);
					while (hash[i]!=-1){
				      i = rehashl(i,tsize);
					}
					hash[i]=key ;
				}
				
				printf("Elements after linear probing: ");
				for(int i=0;i<tsize;i++){
					printf("%d ",hash[i]);
				}
				printf("\n");
			break;
			case 2:
				memset(hash, -1, tsize*sizeof(hash[0]));
					
				for(k=0;k<n;k++){
					j=1;
					key=arr[k] ;
					i = hasht(key,tsize);
					while (hash[i]!=-1){
					    i = rehashq(i,j,tsize);
					    j++;
					}
					hash[i]=key;
				}
				
				printf("Elements after quadratic probing: ");
				for(int i=0;i<tsize;i++){
					printf("%d ",hash[i]);
				}
				printf("\n");
			break;
			case 3: exit(0);
			break;
		}
		
		getch();
		
	}while(op!=3);
		
	
	return 0;
}

int hasht(int key,int tsize){
	int i;
	i = key%tsize;
	return i;
}

//-------LINEAR PROBING-------
int rehashl(int key,int tsize){
	int i;
	i = (key+1)%tsize;
	return i ;
}

//-------QUADRATIC PROBING-------
int rehashq(int key, int j,int tsize){
	int i;
	i = (key+(j*j))%tsize;
	return i;
}

