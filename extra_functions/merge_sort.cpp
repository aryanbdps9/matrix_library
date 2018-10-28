#include <bits/stdc++.h>
#include <time.h>
#include <pthread.h> 

#include <unistd.h>

#define start_routine clock_t begin = clock();
// #define end_routine clock_t end = clock(); double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; fprintf(stderr, "\nTime elapsed : %.3f seconds\n", elapsed_secs);return 0;
#define end_routine clock_t end = clock(); double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC; fprintf(stderr, "\nTime elapsed : %.3f seconds\n", elapsed_secs);
using namespace std;

typedef long long int ll;

int * arr;

int mod = 100;
typedef struct __myarg_t {
    int l;
    int r;
    int level;
} myarg_t;

void merge( int l, int m, int r);
void merge_sort( int l, int r);

void* multithread_merge_sort(void* arg) 
{ 
    myarg_t *m = (myarg_t *) arg;

    int low = m->l;
    int high = m->r; 

    int mid = low + (high - low) / 2; 
    if (low < high) { 
        merge_sort(low, mid); 
        merge_sort(mid + 1, high); 
        merge(low, mid, high); 
    } 
}

void multithread_mergesort(int l, int size, int no_of_thread){
    pthread_t threads[2];
    myarg_t arg[2];
    queue<myarg_t> index;

    for(int i=0;i<2;i++){
        if(i==0){
        arg[i].l=l ; arg[i].r = l+size/2; 
        }else{
        arg[i].l=l + size/2 +1 ; arg[i].r = l+ size -1;
        }
        index.push(arg[i]);
        pthread_create(&threads[i],NULL,multithread_merge_sort,& arg[i]);
    }

    for(int i=0;i<2;i++)
        pthread_join(threads[i],NULL);
    
    // merge(l,l+size/2,l+size-1);

    
    return;
    

}




int main()
{
	int n;
    cout<<"no of element: ";
    cin>>n;
    int multi_thread;
    cout<<"no of thread :" ;
    cin>>multi_thread;

    int * a ;
    a = (int *) malloc( n * sizeof (int ));
    srand(time(NULL));

    for(int i=0;i<n;i++){
        a[i]=rand()%mod;
    }

    arr = a;


    start_routine;

    if(multi_thread>1)
        multithread_mergesort(0,n,multi_thread);
    else  {
        merge_sort(0,n);
    }

    end_routine;

    // for(int i=0;i<n;i++)
    // cout << a[i]<<" ";

}

void merge( int l, int m, int r) 
{   
    // usleep(1);
    for(int y=0;y<1000;y++);
        ;
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    int L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void merge_sort( int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        merge_sort( l, m); 
        merge_sort( m+1, r); 
        merge(l, m, r); 
    } 
} 