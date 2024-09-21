#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main(){
	int m,n;
	int a[100][100];
	srand(time(NULL));
	FILE *f=fopen("array2.txt","wt");
	cout<<"Nhap m: "; cin>>m;
	cout<<"Nhap n: "; cin>>n;
	fprintf(f,"%d %d\n",m,n);
	for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            a[i][j]=rand()%98+1;
            fprintf(f,"%5d",a[i][j]);
        }
        fprintf(f,"\n");
	}
	fclose(f);
	return 0;
}

