// Pham Duc Minh - BDATTT
// Sap xep chon 
// Khai bao thu vien
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Khai bao bien toan cuc
char inputPath[100] = "input_100000_3.txt";
char outputPath[100] = "output_100000_3.txt";

// Dinh nghia hang so 
#define MAXSIZE 100000
#define SELECTION_SORT 1
#define QUICK_SORT 2
#define INSERTION_SORT 3

// Quy uoc kieu
typedef int type;

// Tien dinh nghia ham 
void readFile(FILE*,type*,type*);
void sxChon(type*,type);
void sxNhanh(type*,type);
void sxChen(type*,type);
void thoiGianSX(type* ,type,FILE*,int);

// Main
int main(){
    // Khai bao con tro file
    FILE *f1,*f2;
    f1 = fopen(inputPath,"r");
    f2 = fopen(outputPath,"w");
    if (f1 == NULL or f2 == NULL)
    {
        printf("Khong mo duoc file !!!");
    }
    

    // Dinh nghia mang va doc so luong phan tu mang tu file input
    type n,i;
    fscanf(f1,"%ld",&n);

    // Cap phat 3 mang dong de luu du lieu cua file input
    type *a,*b,*c;
    a = (type*)calloc(n,sizeof(type));
    b = (type*)calloc(n,sizeof(type));
    c = (type*)calloc(n,sizeof(type));
    for(i = 0;i<n;i++){
        fscanf(f1,"%ld",a+i);
    }
    fclose(f1);
    memcpy(c,a,n*sizeof(type));
    memcpy(b,a,n*sizeof(type));

    // Tinh thoi gian cua tung loai sap xep
    thoiGianSX(a,n,f2,SELECTION_SORT);
    thoiGianSX(b,n,f2,QUICK_SORT);
    thoiGianSX(c,n,f2,INSERTION_SORT);

    // In ra ket qua sap xep
    for(i = 0;i<n;i++){
        fprintf(f2,"%ld ",*(a+i));
    }
    fclose(f2);
    return 0;
}


// Ham doi cho hai phan tu trong mang
void swap(type *a,type*b){
    type t;
    t = *a;
    *a = *b;
    *b = t;
}


// Sap xep chon
void sxChon(type *a,type n){
    for(type i  = 0;i<n-1;i++){
        for(type j = i+1;j<n;j++){
            if(a[i]>a[j]) swap(&a[i],&a[j]);
        }
    }
}

// Sap xep chen
void sxChen(type *a, int n){
    type t,j;
    for(type i  = 1;i<n;i++){
        t = a[i];
        j = i-1;
        while(j>=0 && a[j]>t){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = t;
    }
}

void sxNhanh(type *a, int l, int r) {
    int vitri = (l+r)/2;
    type x = a[vitri];  //gan x bang gia tri o giua
    int i = l;          //gan i = left
    int j = r;          //gan j  = right
    do{
        while(a[i] < x) i++; // tim phan tu lon hon x
        while(a[j] > x) j--; // tim phan tu nho hon x
        if(i <= j){
            swap(&a[i], &a[j]);
            i++;
            j--;
        } 
    } while(i <= j);
    if(l < j) sxNhanh(a,l,j);
    if(i < r) sxNhanh(a,i,r);
}

// Tinh thoi gian tung loai sap xep
// Tham so la mang can sap xep, so luong phan tu, con tro file out, key cua loai sap xep
void thoiGianSX(type a[],int n,FILE*f2,int key){
    if(key == SELECTION_SORT){
        clock_t startChon = clock();
        sxChon(a,n);
        clock_t finishChon = clock();
        double thoiGianSXC = (double) (finishChon - startChon)/CLOCKS_PER_SEC;
        fprintf(f2,"Thoi gian cua sx Chon la: %lf giay\n",thoiGianSXC);
    } else if(key == QUICK_SORT){
        clock_t startNhanh = clock();
        sxNhanh(a,0,n-1);
        clock_t finishNhanh = clock();
        double thoiGianSXN = (double) (finishNhanh - startNhanh)/CLOCKS_PER_SEC;
        fprintf(f2,"Thoi gian cua sx Nhanh la: %lf giay\n",thoiGianSXN);
    } else {
        clock_t startChen = clock();
        sxChen(a,n);
        clock_t finishChen = clock();
        double thoiGianSXChen = (double) (finishChen - startChen)/CLOCKS_PER_SEC;
        fprintf(f2,"Thoi gian cua sx Chen la: %lf giay\n",thoiGianSXChen);
    }
}