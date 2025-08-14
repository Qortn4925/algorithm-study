#include <stdio.h>

int main(void){
	int i , j ,temp ; 
	int array[10]={1,10,5,8,7,6,4,3,2,9};
	
	for(i =0; i<10; i++){
		
		for(j=i; j<10; j++){
			if(array[i] > array[j]){
				temp = array[i];
				 array[i]=array[j];
				 	array[j] =temp ;
			}
		}
		
		
	}
	for(i=0; i<10; i++){
		printf("%d ",array[i]);
	}
}