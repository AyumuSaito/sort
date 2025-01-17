#include <stdio.h>

// 素数
#define N 2999

int A[N];
// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

void bubble_sort(int A[], int n){
    int i, j;
    for(j=0;j<n/2+1;j++){
        for(i=j+1; i < n; i++){
            if(A[i]<A[j]) swap(A+i, A+j);
        }
    }
}

int quick_select(int A[], int n, int k){
    int i, j, m, p, pivot;
    int B[N];
    if(n <= 5){
        for(j=0; j<n; j++){
            for(i=j+1; i<n; i++) if(A[j]>A[i]) swap(A+i,A+j);
        }
        return A[k];
    }
    else{
        for(i=0; i<n/5; i++){
            bubble_sort(A+(5*i),5);
            B[i] = A[5*i+2];
        }
        bubble_sort(A+n/5*5,(n+4)%5+1);
        B[n/5] = A[n/5*5+((n+4)%5+1)/2];
        m = quick_select(B,n/5+1,(n/5+1)/2);
        for(p=0; p<n; p++){
            if(A[p] == m){
                pivot = A[p];
                break;
            }
        }
        A[p] = A[0];
        A[0] = pivot;
        for(i = j = 1; i < n; i++){
            if(A[i] <= pivot){
                swap(A+i, A+j);
                j++;
            }
        }
        if(j == k+1) return pivot;
        else if(j < k+1) return quick_select(A+j, n-j, k-j);
        else return quick_select(A+1, j-1, k);
    }
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
  }
}
