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
  double x;
  double y;
  double distance;
}LocationStores;

typedef struct LocationMe {
  double x;
  double y;
}LocationMe;


void ReadData(LocationMe** my, LocationStores** store, LocationStores** query, int* n, int* s, int* t);
void printStores(LocationStores* store, int n);
void mergeInsertionSort(LocationStores* store, int l, int r, int THRESHOLD, LocationMe* my);
void merge(LocationStores* store, int l, int m, int r, LocationMe* my);
void insertionMergeSort(LocationStores* store, int l, int r, LocationMe* my);
void findStore(LocationStores* store, LocationStores* query, int numQueries, int numStores);
int binarySearch(LocationStores* store, int l, int r, LocationStores query);
int compareTo(LocationStores* store, LocationStores* query);

int myX, myY;

int main(void) {

  int numStores, numQueries, THRESHOLD;

  LocationMe* my;
  LocationStores* store;
  LocationStores* query;

  // Reading in all data and building arrays/structs
  ReadData(&my, &store, &query, &numStores, &numQueries, &THRESHOLD);


  // Sort main list coordinates
  mergeInsertionSort(store, 0, numStores - 1, THRESHOLD, my);

  // Print out sorted list as per output restriction
  printStores(store, numStores);

  // Start looking at queries and comparing to store coordinate list. Also print out in this function
  findStore(store, query, numQueries, numStores);


  free(my);
  free(store);
  free(query);

  return 0;

}

void ReadData(LocationMe** my, LocationStores** store, LocationStores** query, int* n, int* s, int* t) {

  scanf("%d %d %d %d %d", &myX, &myY, n, s, t);

  *my = malloc(sizeof(LocationMe));
  *store = malloc(sizeof(LocationStores) * *n);
  *query = malloc(sizeof(LocationStores) * *s);

  (*my)->x = myX;
  (*my)->y = myY;

  // Setting coordinates to stores
  for (int i = 0; i < *n; i++) {
    scanf("%lf %lf", &(*store)[i].x, &(*store)[i].y);
  }

  // Calculating distance from me to store and storing it in store[].distance
  for (int i = 0; i < *n; i++) {
    (*store)[i].distance = sqrt(pow(((*store)[i].x - (*my)->x), 2) + pow(((*store)[i].y - (*my)->y), 2));
  }

  // Setting Query coordinates
  for (int i = 0; i < *s; i++) {
    scanf("%lf %lf", &(*query)[i].x, &(*query)[i].y);
  }

  // Calculating Query points distance to me and storing un query[].distance
  for (int i = 0; i < *s; i++) {
    (*query)[i].distance = sqrt(pow(((*query)[i].x - (*my)->x), 2) + pow(((*query)[i].y - (*my)->y), 2));
  }

}

void printStores(LocationStores* store, int n) {

  for (int i = 0; i < n; i++) {
    printf("%1.0lf %1.0lf\n", store[i].x, store[i].y);
    }
}

void mergeInsertionSort(LocationStores* store, int l, int r, int THRESHOLD, LocationMe* my) {

  // if our array has been windled down to an element count below threshold we run insertion sort (O(n^2))
  if (r - l + 1 <= THRESHOLD) {
    insertionMergeSort(store, l, r, my);
  }
  else if (r > l) {
    // While we still have a HUGE array (O(log n))
    int mid = (l + r) / 2;
    mergeInsertionSort(store, l, mid, THRESHOLD, my);
    mergeInsertionSort(store, mid + 1, r, THRESHOLD, my);
    merge(store, l, mid, r, my);
  }

}

void merge(LocationStores* store, int l, int m, int r, LocationMe* my) {

  int i, j, k;

  int n1 = m - l + 1;// array size for left array
  int n2 = r - m; // array size for right array

  LocationStores* L = malloc(n1 * sizeof(LocationStores));
  LocationStores* R = malloc(n2 * sizeof(LocationStores));

    // loading the left array
  for (int i = 0; i < n1; i++)
    L[i] = store[l + i];

    // loading the right array 
  for (int j = 0; j < n2; j++)
    R[j] = store[m + 1 + j];


  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {// while we are still in bounds of either array

        // determining if this left index has the lowest distance first, the lowest x next, the lowest y last
    if (compareTo(&L[i], &R[j]) <= 0) {

      store[k] = L[i];
      i++;
      k++;

    } else {

            // if not the above if the right array element goes in to thhis store[k] pos
      store[k] = R[j];
      j++;
      k++;

    }
  }

    // Once we have exited the bounds of one or the other arrays we go here and fill the remainder of store[k]
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

void insertionMergeSort(LocationStores* store, int l, int r, LocationMe* my) {
    // This is like taking out a book +1 of current pos and comparing to the left.
    // If the book is smaller we move it down until it is no longer the smallest.

  for (int i = l + 1; i <= r; i++) {
    LocationStores hand = store[i];
    int j;
    
    for (j = i - 1; j >= l && compareTo(&store[j], &hand) > 0; j--) {

      store[j + 1] = store[j];

    }
    store[j + 1] = hand;
  }
}

void findStore(LocationStores* store, LocationStores* query, int numQueries, int numStores) {

  for (int i = 0; i < numQueries; i++) {

    int rank = binarySearch(store, 0, numStores - 1, query[i]);

    if (rank != -1) {
      printf("%1.0lf %1.0lf found at rank %d", query[i].x, query[i].y, rank+1);
    }
    else {
      printf("%1.0lf %1.0lf not found", query[i].x, query[i].y);
    }
    printf("\n");
  }
}

int binarySearch(LocationStores* store, int l, int r, LocationStores query) {
  int low = l;
  int high = r;

  while (low <= high) {
    int mid = low + (high - low) / 2;
    int searchVal = compareTo(&store[mid], &query);

    if (searchVal == 0) {
      return mid;
    }// ends if

    if (searchVal < 0) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }// ends if else

  }// ends while

  return -1; // Return -1 if not found

}// ends binarySearch

int compareTo(LocationStores* store, LocationStores* query) {

  if (store->distance < query->distance) return -1;
  if (store->distance > query->distance) return 1;
  if (store->x < query->x) return -1;
  if (store->x > query->x) return 1;
  if (store->y < query->y) return -1;
  if(store->y > query->y) return 1;

  return 0;
}
