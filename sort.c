#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
            }
}

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++){
        int key = arr[i], j = i-1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);
    int arr[n], arr_copy[n];
    printf("Enter %d integers: ", n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i]; // copy for child
    }

    pid_t pid = fork();

    if(pid < 0){
        printf("Fork failed\n");
        return 1;
    }
    else if(pid == 0){
        // Child process - Insertion Sort
        insertionSort(arr_copy, n);
        printf("Child Process (Insertion Sort): ");
        for(int i = 0; i < n; i++) printf("%d ", arr_copy[i]);
        printf("\n");
    }
    else{
        // Parent process - Bubble Sort
        wait(NULL); // wait for child
        bubbleSort(arr, n);
        printf("Parent Process (Bubble Sort): ");
        for(int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}
