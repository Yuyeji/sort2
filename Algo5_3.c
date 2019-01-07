#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

void bucket_sort(float *arr, int size);
void InsertSort(int *arr, int n);
int heap_size(float *arr);

int main(void) {
	float *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	int size = 1;
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("bucket.txt", "r");

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	arr = (float *)malloc(sizeof(float));

	while (feof(f) == 0) {
		arr = (float *)realloc(arr, (size) * sizeof(float));
		fscanf(f, "%f", &arr[size - 1]);
		arr[size - 1] = arr[size - 1] * 1000;
		size++;
	}

	startTime = clock();

	bucket_sort(arr, heap_size(arr));

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);


	for (int j = 0; j < heap_size(arr); j++) {
		printf("%.3f\t", arr[j] / 1000);
	}

	printf("측정 시간 : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // 테스트 보기 위해.

}

int heap_size(float *arr) { //arr의 크기
	return (_msize((void*)arr) / sizeof(int));
}

void bucket_sort(float *arr, int size) {
	int i;
	int *count;
	count = (int *)malloc(sizeof(int)*size);

	//배열 값 초기화
	for (i = 0; i < size; i++)
		count[i] = 0;
	//count[arr[i]]에 arr[i]값 삽입
	for (i = 0; i < size; i++) {
		int k = arr[i];
		count[k] = arr[i];
	}

	//count배열을 삽입정렬해준다.
	for (i = 0; i < size; i++)
		InsertSort(count, i);

	//arr에 복사
	for (i = 0; i < size; i++)
		arr[i] = count[i];
}

/*삽입 정렬*/
void InsertSort(int *arr, int n) {
	int i, j, k;
	int num;

	for (k = 0; k < n; k++) {
		for (i = 1; i < n; i++) {
			for (j = 0; j < i;j++) {
				if (arr[i] < arr[j]) {
					num = arr[i];
					arr[i] = arr[j];
					arr[j] = num;
					break;
				}
			}
		}
	}
}