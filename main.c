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

typedef struct LocationStores {
  int x;
  int y;
  int distance;
}LocationStores;

typedef struct LocationMe {
  int x;
  int y;
}LocationMe;

typedef struct Queries {
  int x;
  int y;
  int distance;
}Queries;

typedef struct Locations {
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
void findStore(LocationStores*, Queries*, int, int);
LocationMe* ReadData(int*, int*);

int myX, myY;

int main(void) {

  int numStores, numQueries, THRESHOLD;

  /* So number 3 in the PDF 3. You must implement a ReadData() function that reads the required data from the inputs and return the array of points to be sorted. Do i need 1 structure with both other structs in them? I would still need two different "ReadDatas" would I not ex LocationMe* me = ReadDataMe(&x, &y) and LocationStores* store = ReadDataStore(&n, &s, &t)
  */
  scanf("%d %d %d %d %d", &myX, &myY, &numStores, &numQueries, &THRESHOLD);


  LocationMe* my = malloc(sizeof(LocationMe));
  LocationStores* store = malloc(sizeof(LocationStores) * numStores);
  Queries* query = malloc(sizeof(Queries) * numQueries);

  my->x = myX;
  my->y = myY;

  // Setting coordinates to stores
  for (int i = 0; i < numStores; i++) {
    scanf("%d %d", &store[i].x, &store[i].y);
  }

  // Calculating distance from me to store and storing it in store[]
  for (int i = 0; i < numStores; i++) {
    store[i].distance = sqrt(pow((store[i].x - my->x), 2) + pow((store[i].y - my->y), 2));
  }

  for (int i = 0; i < numQueries; i++) {
    scanf("%d %d", &query[i].x, &query[i].y);
  }

  for (int i = 0; i < numQueries; i++) {
    query[i].distance = sqrt(pow((query[i].x - my->x), 2) + pow((query[i].y - my->y), 2));
  }


  /*DEBUG VERIFY ALL INITIAL COORDINATES*/
  //printf("\n\nInitial Coordinates:\nmy x = %0.0lf my y = %0.0lf\n", my->x, my->y);
  //printStores(store, numStores);
  //for (int i = 0; i < numQueries; i++) {
  //	printf("\nquery[%d].x = %d and query[%d].y = %d", i, query[i].x, i, query[i].y);
  //}

  /*
  mergeSort(store, 0, n-1);

  //DEBUG VERIFY ALL COORDINATES//
  printf("\n\nmy x = %d my y = %d\n", my->x, my->y);
  printStores(store, n);
  */

  mergeInsertionSort(store, 0, numStores - 1, THRESHOLD, my);

  /*DEBUG VERIFY ALL SORTED COORDINATES*/
  //printf("\n\nSorted Coordinates:\nmy x = %0.0lf my y = %0.0lf\n", my->x, my->y);
  //printf("\n");
  printStores(store, numStores);
  findStore(store, query, numQueries, numStores);




  return 0;

}

LocationMe* ReadData(int* x, int* y) {
  LocationMe* my = malloc(sizeof(LocationMe));
  scanf("%d %d", &my->x, &my->y);
  return my;
}

void printStores(LocationStores* store, int n) {
  //printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%d %d\n", store[i].x, store[i].y);
    //printf("Store[%02d] x = %2.0lf  Store[%02d] y = %2.0lf  Distance to me is %5.2lf\n", i, store[i].x, i, store[i].y, store[i].distance);
  }
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
void merge(LocationStores* store, int l, int m, int r, LocationMe* my) {

  // I guess I need a compare function in here?
  int i, j, k, leftDis, rightDis;

  int n1 = m - l + 1;
  int n2 = r - m;

  LocationStores* L = malloc(n1 * sizeof(LocationStores));
  LocationStores* R = malloc(n2 * sizeof(LocationStores));

  for (int i = 0; i < n1; i++)
    L[i] = store[l + i];


  for (int j = 0; j < n2; j++)
    R[j] = store[m + 1 + j];


  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {

    if (L[i].distance < R[j].distance ||
       (L[i].distance == R[j].distance && L[i].x < R[j].x) ||
       (L[i].distance == R[j].distance && L[i].x == R[j].x && L[i].y < R[j].y)) {

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

void mergeInsertionSort(LocationStores* store, int l, int r, int THRESHOLD, LocationMe* my) {
  if (r - l + 1 <= THRESHOLD) {
    insertionMergeSort(store, l, r, my);
  }
  else if (r > l) {
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
    for (j = i - 1; j >= l &&
      (store[j].distance > hand.distance ||
      (store[j].distance == hand.distance && store[j].x > hand.x) ||
      (store[j].distance == hand.distance && store[j].x == hand.x && store[j].y > hand.y)); j--) {

      store[j + 1] = store[j];

    }
    store[j + 1] = hand;
  }
}

void findStore(LocationStores* store, Queries* query, int numQueries, int numStores) {

  for (int i = 0; i < numQueries; i++) {

    int rank = binarySearch(store, 0, numStores - 1, query[i]);

    if (rank != -1) {
      printf("%d %d found at rank %d", query[i].x, query[i].y, rank+1);
    }
    else {
      printf("%d %d not found", query[i].x, query[i].y);
    }
    printf("\n");
  }
}

int binarySearch(LocationStores* store, int l, int r, Queries query) {
  int low = l;
  int high = r;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (store[mid].x == query.x && store[mid].y == query.y) {
      return mid;
    }
    if (compareTo(&store[mid], &query) < 0) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  return -1; // Return -1 if not found
}


int compareTo(const void* a, const void* b) {
  LocationStores* locA = (LocationStores*)a;
  LocationStores* locB = (LocationStores*)b;

  if (locA->distance < locB->distance) return -1;
  if (locA->distance > locB->distance) return 1;
  if (locA->x < locB->x) return -1;
  if (locA->x > locB->x) return 1;
  if (locA->y < locB->y) return -1;
  return 1;
}