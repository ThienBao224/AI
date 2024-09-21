#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}

void xaotron(int a[], int n){
    srand(time(NULL));
    for (int i=n-1;i> 0;i--){
        int j=rand()%(i+1);
        swap(a[i],a[j]);
    }
}

int main(){
    int n;
    FILE *f=fopen("taci.txt","wt");
    cout<<"Nhap n: "; cin>>n;
    fprintf(f,"%d\n",n);
    int a[n*n];
    for(int i=0;i<n*n;i++){
        a[i]=i+1;
    }
    xaotron(a,n*n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fprintf(f,"%5d",a[i*n+j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
    return 0;
}
