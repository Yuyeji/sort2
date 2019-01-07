#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

void randomized_select(int *arr, int left, int right);
int partition(int *arr, int left, int right);
int rancomized_partition(int *arr, int left, int right);
int heap_size(int *arr);

int main(void) {
	int *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	int size = 1;
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("input10000.txt", "r");

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	startTime = clock();

	randomized_select(arr, 0, heap_size(arr) - 1);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);


	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\t", arr[j]);
	}

	printf("측정 시간 : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // 테스트 보기 위해.

}

int heap_size(int *arr) { //arr의 크기
	return (_msize((void*)arr) / sizeof(int));
}

void randomized_select(int *arr, int left, int right) {
	if (left == right)
		arr[left];


	if (left < right) { //정렬할 범위가 두 개 이상이면 
		int q = rancomized_partition(arr, left, right); //rancomized
		int k = q - left + 1;

		if ((right +1) == k)
			arr[q];

		randomized_select(arr, left, q - 1); //pivot의 왼쪽 퀵 소트
		randomized_select(arr, q + 1, right); //pivot의 오른쪽 퀵 소트
	}
}

int partition(int *arr, int left, int right) {
	int x, i, j, temp;
	int index;

	x = arr[right];
	i = left - 1;

	for (j = left; j <= right - 1; j++) {
		if (arr[j] <= x) {
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//pivot을 중간으로 위치
	temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;

	return i + 1; //pivot의 위치 반환
}

int rancomized_partition(int *arr, int left, int right) {
	int i = left + rand() % (right - left + 1);
	int temp;

	temp = arr[right];
	arr[right] = arr[i];
	arr[i] = temp;

	return partition(arr, left, right);
}