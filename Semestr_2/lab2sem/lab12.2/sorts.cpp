void select_sort(int *arr, int size)
{
    int min_index;
    for (int i = 0; i < size - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}
void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void shaker_sort(int *arr, int size){
	int t;
	int l = 0, r = size-1, k = size-1;
	do{
		for (int j = r;j>l;j--){
			if(arr[j]<arr[j-1]){
				t = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = t;
				k = j;
			}
		}
		l = k;
		for(int j = l;j<r;j++){
			if(arr[j]>arr[j+1]){
				t = arr[j];
				arr[j] = arr[j+1];
				arr[j-1] = t;
				k = j;
			}
		}
		r = k;
	}while(l<r);
}
void insert_sort(int *arr, int size)
{
    int temp, i, j;
    for (i = 1; i < size; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
}
void select_sort(float *arr, int size)
{
    int min_index;
    for (int i = 0; i < size - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        if (i != min_index) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}
void bubble_sort(float *arr, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void shaker_sort(float *arr, int size){
	int t;
	int l = 0, r = size-1, k = size-1;
	do{
		for (int j = r;j>l;j--){
			if(arr[j]<arr[j-1]){
				t = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = t;
				k = j;
			}
		}
		l = k;
		for(int j = l;j<r;j++){
			if(arr[j]>arr[j+1]){
				t = arr[j];
				arr[j] = arr[j+1];
				arr[j-1] = t;
				k = j;
			}
		}
		r = k;
	}while(l<r);
}
void insert_sort(float *arr, int size)
{
    int temp, i, j;
    for (i = 1; i < size; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
}