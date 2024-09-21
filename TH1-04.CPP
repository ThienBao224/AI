#include<iostream>
#include<cmath>
#include<limits.h>
#include<fstream>
#include<ctime>
using namespace std;
int snt(int n);

int snt(int n){
	if (n<2) return 0;
	int k=sqrt(n);
	for (int i=2;i<=k;i++)
	if (n%i==0) return 0;
	return 1;
}

int main(){
    int n,num,s=0;
    FILE*f=fopen("array1.txt","r");
    FILE*f1=fopen("array1.out","w");
    fscanf(f,"%d\n",&n);
    for(int i=0;i<n; i++){
            fscanf(f,"%d",&num);
            if(snt(num)) s++;
    }
    fprintf(f1,"So luong so nguyen to: %d\n",s);
    fclose(f);
    fclose(f1);
    return 0;
}
