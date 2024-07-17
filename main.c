/*
  Coded by Nick Newman
  7/17/24
  Summer 24
  Computer Science 1
  Dr. Tanvir Ahmed
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct LocationStores{
  int x;
  int y;
}LocationStores;
typedef struct LocationMe{
  int x;
  int y;
}LocationMe;

void printArray(int*, int);
void printStores(LocationStores*, int);
void swap(int*, int*);
void mergeSort(LocationStores*, int, int);
void merge(LocationStores*, int, int, int);
void mergeInsertionSort(LocationStores*, int, int, int);
void insertionMergeSort(LocationStores*, int, int);


int main(void) {

  int x, y, n, s, t;
  
  scanf("%d %d %d %d %d",&x, &y, &n, &s, &t);

  LocationMe* my = malloc(sizeof(LocationMe));
  LocationStores* store = malloc(sizeof(LocationStores) * n);

  my->x = x;
  my->y = y;
  int THRESHOLD = t;

  for(int i = 0; i < n; i++){
    scanf("%d %d", &store[i].x, &store[i].y);
  }

  /*DEBUG VERIFY ALL INITIAL COORDINATES*/
  printf("\n\nInitial Coordinates:\nmy x = %d my y = %d\n", my->x, my->y);
  printStores(store, n);
  
  /*
  mergeSort(store, 0, n-1);

  //DEBUG VERIFY ALL COORDINATES//
  printf("\n\nmy x = %d my y = %d\n", my->x, my->y);
  printStores(store, n);
*/
  
  mergeInsertionSort(store, 0, n-1, THRESHOLD);

  /*DEBUG VERIFY ALL SORTED COORDINATES*/
  printf("\n\nSorted Coordinates:\nmy x = %d my y = %d\n", my->x, my->y);
  printStores(store, n);

}

void printStores(LocationStores* store, int n){
  //printf("\n");
  for(int i = 0; i < n; i++)
    printf("Store[%02d] x = %2d\tStore[%02d] y = %2d\n", i, store[i].x, i, store[i].y);
}
/*
void mergeSort(LocationStores* store, int l, int r){
  
  if(l < r){

    int m = (l + r) / 2;
    mergeSort(store, l, m);
    mergeSort(store, m + 1, r);
    merge(store, l, m, r); 
    
  }
  
}
*/
void merge(LocationStores* store, int l, int m, int r){

  int i, j, k;

  int n1 = m-l+1;
  int n2 = r - m;

  LocationStores* L = malloc(n1 * sizeof(LocationStores));
  LocationStores* R = malloc(n2 * sizeof(LocationStores));

  for(int i = 0; i < n1; i++)
    L[i] = store[l + i];


  for(int j = 0; j < n2; j++)
    R[j] = store[m + 1 + j];

  i = 0;
  j = 0;
  k = l;

  while(i < n1 && j < n2){

    if (L[i].x < R[j].x || (L[i].x == R[j].x && L[i].y <= R[j].y)){

      store[k] = L[i];
      i++;
      k++;
    
    } else {

      store[k] = R[j];
      j++;
      k++;
    
    }
}

while (i < n1) {

  store[k] = L[i];
  i++;
  k++;
}

while (j < n2) {

  store[k] = R[j];
  j++;
  k++;
}

free(L);
free(R);


}

void mergeInsertionSort(LocationStores* store, int l, int r, int THRESHOLD) {
    if (r - l + 1 <= THRESHOLD) {
        insertionMergeSort(store, l, r);
    } else if (r > l) {
        int mid = (l + r) / 2;
        mergeInsertionSort(store, l, mid, THRESHOLD);
        mergeInsertionSort(store, mid + 1, r, THRESHOLD);
        merge(store, l, mid, r);
    }
}

void insertionMergeSort(LocationStores* store, int l, int r) {
      for (int i = l + 1; i <= r; i++) {
          LocationStores hand = store[i];
          int j;
          for (j = i - 1; j >= l && (store[j].x > hand.x || (store[j].x == hand.x && store[j].y > hand.y)); j--) {
              store[j + 1] = store[j];
          }
          store[j + 1] = hand;
      }
  }