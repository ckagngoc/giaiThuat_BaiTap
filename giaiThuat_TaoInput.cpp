#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main() {
    char *fileName;
    printf("Nhap ten file input: ");
    gets(fileName);
    FILE* f1 = fopen(fileName,"w");
    long int i,n,N;
    printf("Nhap so luong phan tu: ");
    scanf("%ld",&n);
    fprintf(f1,"%d \n",n);
    printf("Nhap gioi han input: ");
    scanf("%ld",&N);
    for(i=0;i<n;i++){
        fprintf(f1,"%ld  ",rand()%N);
    }
    return 0;
}