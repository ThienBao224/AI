#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
	int n;
	srand(time(NULL));
	FILE *f=fopen("array1.txt","w");
	cout<<"Nhap n: "; cin>>n;
	fprintf(f,"%d\n",n);
	for(int i=0;i<n;i++){
            fprintf(f,"%5d",rand()%100);
            if((i+1)%10==0) fprintf(f,"\n");
	}
	fclose(f);
	return 0;
}
