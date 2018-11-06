#include <bits/stdc++.h>
// #include <+.3
using namespace std;

#define PI 3.14159265358979323846

vector<complex<double > > dft(vector<complex<double > > x){
    int n = x.size();
    vector< vector< complex< double >>> w(n, vector<complex<double> > (n));

    double sq_n = sqrt(n);
    double two_pi_by_n = (2.0 * PI) / n;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            w[i][j]= polar(1.0,- (j*i) * two_pi_by_n  );
            // w[i][j]= polar(1.0/sq_n,- (j*i) / two_pi_by_n  );
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
        cout<< w[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<complex<double > > ans(n);

    for(int i=0;i<n;i++){
        ans[i] = 0;
        for(int j=0;j<n;j++)
        ans[i]+=w[i][j] * x[j];
    }

    return ans;
}

// vector<complex<double > > dft(vector<complex<double > > x){
//     return x;
// }
vector<complex<double > > fft(vector<complex<double > > x){
    // dft_helper(x, x.size());
    return x;
}

int main(){
    int n ;
    n = 4;
    vector<complex<double > > x(n) ;
    for(float  i=0;i<n;i++){
        x[i]=polar(1+0.0,PI);
    }
    x[0]= 1;
    x[1]= complex<double >(2,-1);
    x[2]= complex<double >(0,-1);
    x[3]= complex<double >(-1,2);

    // for(int i=0;i<n;i++){
    //         cout<<x[i]<<endl;
    // }
    vector<complex<double > > ans = dft(x);



    for(int i=0;i<n;i++){
            cout<<ans[i]<<endl;
    }
    return 0;
}