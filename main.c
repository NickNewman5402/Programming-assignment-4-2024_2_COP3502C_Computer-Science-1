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

typedef struct Queries {
  double x;
  double y;
  double distance;
}Queries;

typedef struct Locations {
  LocationStores* store;
  LocationMe* me;
}Locations;

//LocationMe* ReadData(int*, int*);
void printStores(LocationStores*, int);
void swap(int*, int*);
void mergeSort(LocationStores*, int, int);
void merge(LocationStores*, int, int, int, LocationMe*);
void mergeInsertionSort(LocationStores*, int, int, int, LocationMe*);
void insertionMergeSort(LocationStores*, int, int, LocationMe*);
void findStore(LocationStores*, Queries*, int, int);
int compareTo(LocationStores*, Queries*);


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
    scanf("%lf %lf", &store[i].x, &store[i].y);
  }

  // Calculating distance from me to store and storing it in store[]
  for (int i = 0; i < numStores; i++) {
    store[i].distance = sqrt(pow((store[i].x - my->x), 2) + pow((store[i].y - my->y), 2));
  }

  // Setting Query coordinates
  for (int i = 0; i < numQueries; i++) {
    scanf("%lf %lf", &query[i].x, &query[i].y);
  }

  // Calculating Query points distance to me
  for (int i = 0; i < numQueries; i++) {
    query[i].distance = sqrt(pow((query[i].x - my->x), 2) + pow((query[i].y - my->y), 2));
  }

  // Sort main list coordinates
  mergeInsertionSort(store, 0, numStores - 1, THRESHOLD, my);

  // Print out sorted list as per output restriction
  printStores(store, numStores);
  // Start looking at queries and comparing to store coordinate list
  findStore(store, query, numQueries, numStores);


  free(my);
  free(store);
  free(query);

  return 0;

}
/*
LocationMe* ReadData(int* x, int* y) {
  LocationMe* my = malloc(sizeof(LocationMe));
  scanf("%d %d", &my->x, &my->y);
  return my;
}
*/
void printStores(LocationStores* store, int n) {
  //printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%1.0lf %1.0lf\n", store[i].x, store[i].y);
    //printf("Store[%02d] x = %2.0lf  Store[%02d] y = %2.0lf  Distance to me is %5.2lf\n", i, store[i].x, i, store[i].y, store[i].distance);
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

  // I guess I need a compare function in here?
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

        // determining is this left index has the lowest distance first, the lowest x next, the lowest y last
    if (L[i].distance < R[j].distance ||
       (L[i].distance == R[j].distance && L[i].x < R[j].x) ||
       (L[i].distance == R[j].distance && L[i].x == R[j].x && L[i].y < R[j].y)) {

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
      printf("%1.0lf %1.0lf found at rank %d", query[i].x, query[i].y, rank+1);
    }
    else {
      printf("%1.0lf %1.0lf not found", query[i].x, query[i].y);
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
    }// ends if

    if (compareTo(&store[mid], &query) < 0) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }// ends if else

  }// ends while

  return -1; // Return -1 if not found

}// ends binarySearch

int compareTo(LocationStores* store, Queries* query) {

  if (store->distance < query->distance) return -1;
  if (store->distance > query->distance) return 1;
  if (store->x < query->x) return -1;
  if (store->x > query->x) return 1;
  if (store->y < query->y) return -1;
  return 1;
}