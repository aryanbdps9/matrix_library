#include <bits/stdc++.h>
// #include <+.3
using namespace std;


#define PI 3.14159265358979323846
#define  n 3
// #define  n 729
// #define  n 1000
// int a[n][n];
// int b[n][n];
// int c[n][n];
int a,b,c;
// int A[n][n];
// int B[n][n];
// int C[n][n];

int A[n*n];
int B[n*n];
int C[n*n];

// int Aa[n*n];
// int Ba[n*n];
int Ca[n*n];

void func(int ii, int jj, int kk ){
    for(int i=0;i<ii;i++){
            for(int k=0;k<kk;k++)
            Ca[i* n+ k]= 0;
    }
    for(int i=0;i<ii;i++){
        for(int j=0;j<jj;j++){
            for(int k=0;k<kk;k++)
            Ca[i * n + k] += A[i * n + j] * B[j * n + k];
        }
    }
}



void peanomult(int phsA, int phsB, int phsC, int dim)
{
    if (dim == 1) {
        C[c] += A[a] * B[b];
    }
    else
    {
        peanomult(phsA, phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, -phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, phsB, phsC, dim/3); a += phsA; b += phsB;
        peanomult(phsA, phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult(phsA, -phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult(phsA, phsB, -phsC, dim/3); a += phsA; b += phsB;
        peanomult(phsA, phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, -phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, phsB, phsC, dim/3); b += phsB; c += phsC;
        peanomult(-phsA, phsB, phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA, -phsB, phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA, phsB, phsC, dim/3); a -= phsA; b += phsB;
        peanomult(-phsA, phsB, -phsC, dim/3); a -= phsA; c -= phsC;
        peanomult(-phsA, -phsB, -phsC, dim/3); a -= phsA; c -= phsC;
        peanomult(-phsA, phsB, -phsC, dim/3); a -= phsA; b += phsB;
        peanomult(-phsA, phsB, phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA, -phsB, phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA, phsB, phsC, dim/3); b += phsB; c += phsC;
        peanomult(phsA, phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, -phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, phsB, phsC, dim/3); a += phsA; b += phsB;
        peanomult(phsA, phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult(phsA, -phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult(phsA, phsB, -phsC, dim/3); a += phsA; b += phsB;
        peanomult(phsA, phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, -phsB, phsC, dim/3); a += phsA; c += phsC;
        peanomult(phsA, phsB, phsC, dim/3);
    };
}

int main(){

    // int n ;
    // cin>>n;
    // int a[n][n];
    // int b[n][n];
    // int c[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i*n + j]= rand() % 10;
            B[i *n + j] = A[i*n + j];
            C[i * n + j ] = 0;
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<B[i *n + j]<<" ";
        }cout<<endl;
    }


    // func((int * )c);
    // func(c,a,b);
	auto t1 = chrono::high_resolution_clock::now();
    // func(n,n,n);
    a=n;b=n;c=n;
    // peanomult(-1,-1,-1,n);
    // peanomult(1,1,1,n);
    // func_ikj(n,n,n);
	// auto t2 = chrono::high_resolution_clock::now();
    // cout<<chrono::duration_cast<chrono::duration<double>>(t2 - t1).count()<<endl;
    func(n,n,n);

    int sum=0;

    // peanomult(-1,-1,-1,n);
    // peanomult(-1,-1,1,n);
    // peanomult(-1,1,-1,n);
    // peanomult(-1,1,1,n);
    // peanomult(1,-1,-1,n);
    // peanomult(1,-1,1,n);
    // peanomult(1,1,-1,n);
    peanomult(1,1,1,n);
    for(int i=0;i<n*n;i++)
        // cout<<C[i]<<" "<<Ca[i]<<endl;
        // sum+= abs(C[i]-A[i]);
        sum+= abs(C[i]-Ca[i]);
    cout<<sum<<endl;
    return 0;
}