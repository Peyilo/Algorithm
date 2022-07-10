
// GCD最大公约数算法
int gcd1(int a, int b);
int gcd2(int a, int b);
int EuclidGCD(int a, int b);


// 交换两个数
void swap(int *a, int *b);

void myPrint(int *array, int length);

int * myRand(int length);

// 排序算法
void selectSort(int *arary, int length);

void bubbleSort(int *array, int length);

void insertSort(int *array, int length);

void quickSort(int *array, int length);

void quick(int *array, int lowIndex, int highIndex);

int partition(int *array, int lowIndex, int highIndex);

void mergeSort(int *array, int length);

void merge(int *array, int *temp, int lowIndex, int highIndex);

void arrayCopy(int *srcArray, int index1, int *desArray, int index2, int length);

void shellSort(int *array, int length);

void merge_sort(int arr[], const int len);

void merge_sort_recursive(int arr[], int reg[], int start, int end);