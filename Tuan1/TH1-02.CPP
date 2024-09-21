#include<iostream>
#include<math.h>
#define maxm 200
#define maxn 500

void docfile(int a[maxm][maxn], int &m, int &n);
void ghifile(int a[maxm][maxn], int m, int n);
int demsnt(int a[maxm][maxn], int m, int n);
void tongdong(int a[maxm][maxn], int m, int n);
void tongcot(int a[maxm][maxn], int m, int n);
FILE *f;

int main(){
	int a[maxm][maxn],m,n;
	docfile(a,m,n);
	ghifile(a,m,n);
	return 0;
}

void docfile(int a[maxm][maxn], int &m, int &n){
	f=fopen("array2.txt","rt");
	fscanf(f,"%d%d",&m,&n);
	for (int i=0;i<m;i++)
	for (int j=0;j<n;j++)
	fscanf(f,"%d",&a[i][j]);
	fclose(f);
}

void ghifile(int a[maxm][maxn], int m, int n){
	f=fopen("array2.out","wt");
	fprintf(f,"So luong so nguyen to: %d\n",demsnt(a,m,n));
	fprintf(f,"Tong dong: "); 	tongdong(a,m,n);
	fprintf(f,"Tong cot: ");	tongcot(a,m,n);
	fclose(f);
}

int prime(int n){
	if (n<2) return 0;
	int k=sqrt(n);
	for (int i=2;i<=k;i++)
	if (n%i==0) return 0;
	return 1;
}

int demsnt(int a[maxm][maxn], int m, int n){
	int d=0;
	for (int i=0;i<m;i++)
	for (int j=0;j<n;j++)
	if(prime(a[i][j]))
	d++;
	return d;
}

void tongdong(int a[maxm][maxn], int m, int n){
	int s1;
	for (int i=0;i<m;i++)
    {
        s1=0;
        for (int j=0;j<n;j++)
            s1+=a[i][j];
        fprintf(f,"%d ",s1);
    }
	fprintf(f,"\n");
}

void tongcot(int a[maxm][maxn], int m, int n){
	int s2;
	for (int i=0;i<n;i++)
    {
        s2=0;
        for (int j=0;j<m;j++)
            s2+=a[j][i];
        fprintf(f,"%d ",s2);
    }
	fprintf(f,"\n");
}

