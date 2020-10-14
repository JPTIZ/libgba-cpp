#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
	for(int i = 1; i < n; i++) {
		int current = arr[i];
		int j;
		for(j = i - 1; j >= 0; j--) {
			if(current < arr[j]) {
				arr[j+1] = arr[j];
			}
			else {
				break;
			}
		}
		arr[j+1] = current;
	}

}

void printArray(int input[], int n) {
	for(int i = 0; i < n; i++) {
		cout << input[i] << " " ;
	}
	cout << endl;
}

int main() {
	// Take array input from the user
	int n;
	cin >> n;

	int input[100];
	
	for(int i = 0; i < n; i++) {
		cin >> input[i];
	}
	
	insertionSort(input, n);

	printArray(input, n);
	
}
