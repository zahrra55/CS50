#include<cs50.h>
#include<stdio.h>

int main(void){
    int n=get_int("Howmany blocks do you want? ");
    for(int i=0;i<n;i++){
       printf("\n");
        for(int j=0; j<i;j++)
        printf("#");
    }


}
