/*
  Coded by Nick Newman
  7/17/24
  Summer 24
  Computer Science 1
  Dr. Tanvir Ahmed
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct LocationStores{
  int x;
  int y;
}LocationStores;
typedef struct LocationMe{
  int x;
  int y;
}LocationMe;
typedef struct Locations{
    LocationStores* store;
    LocationMe* me;
}Locations;

void printArray(int*, int);
void printStores(LocationStores*, int);
void swap(int*, int*);
void mergeSort(LocationStores*, int, int);
void merge(LocationStores*, int, int, int, LocationMe*);
void mergeInsertionSort(LocationStores*, int, int, int, LocationMe*);
void insertionMergeSort(LocationStores*, int, int, LocationMe*);
LocationMe* ReadData(int*, int*);


int main(void) {

  int x, y, n, s, t;

  /* So number 3 in the PDF 3. You must implement a ReadData() function that reads the required data from the inputs and return the array of points to be sorted. Do i need 1 structure with both other structs in them? I would still need two different "ReadDatas" would I not ex LocationMe* me = ReadDataMe(&x, &y) and LocationStores* store = ReadDataStore(&n, &s, &t)
*/
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
  
  mergeInsertionSort(store, 0, n-1, THRESHOLD, my);

  /*DEBUG VERIFY ALL SORTED COORDINATES*/
  printf("\n\nSorted Coordinates:\nmy x = %d my y = %d\n", my->x, my->y);
  printStores(store, n);

  
  

}

LocationMe* ReadData(int* x, int* y){
  LocationMe* my = malloc(sizeof(LocationMe));
  scanf("%d %d", &my->x, &my->y);
  return my;
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
void merge(LocationStores* store, int l, int m, int r, LocationMe* my){

  // I guess I need a compare function in here?
  int i, j, k, leftDis, rightDis;

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

      leftDis = sqrt((L[i].x - my->x)^2 + (L[i].y - my->y)^2);
      rightDis = sqrt((R[j].x - my->x)^2 + (R[j].y - my->y)^2);
    
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

while (i < n1 && leftDis < rightDis) {

  store[k] = L[i];
  i++;
  k++;
}

while (j < n2 && rightDis > leftDis) {

  store[k] = R[j];
  j++;
  k++;
}

free(L);
free(R);


}

void mergeInsertionSort(LocationStores* store, int l, int r, int THRESHOLD, LocationMe* my) {
    if (r - l + 1 <= THRESHOLD) {
        insertionMergeSort(store, l, r, my);
    } else if (r > l) {
        int mid = (l + r) / 2;
        mergeInsertionSort(store, l, mid, THRESHOLD, my);
        mergeInsertionSort(store, mid + 1, r, THRESHOLD, my);
        merge(store, l, mid, r, my);
    }
}

void insertionMergeSort(LocationStores* store, int l, int r, LocationMe* my) {
      for (int i = l + 1; i <= r; i++) {
          LocationStores hand = store[i];
          int j;
          for (j = i - 1; j >= l && (store[j].x > hand.x || (store[j].x == hand.x && store[j].y > hand.y)); j--) {
              store[j + 1] = store[j];
          }
          store[j + 1] = hand;
      }
  }