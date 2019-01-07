#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

void counting_sort(int *arr, int size);
int getMax(int *arr, int size);

int main(void) {
	int *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	int size = 1;
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("counting.txt", "r");

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

	//counting sort 호출
	counting_sort(arr, heap_size(arr));

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\t", arr[j]);
	}

	printf("\n측정 시간 : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // 테스트 보기 위해.

}
int heap_size(int *arr) { //arr의 크기
	return (_msize((void*)arr) / sizeof(int));
}

int getMax(int *arr, int size) {
	int max = 0;

	for (int i = 0; i < size; i++)
		if (arr[i] > max)
			max = arr[i];

	return max;
}

void counting_sort(int *arr,int size) {
	int max = getMax(arr, size); //최대값
	int *c, *count;
	int i;

	c = (int *)malloc(sizeof(int)*(size));
	count = (int *)malloc(sizeof(int)*(max + 1));

	//배열 초기화
	for (i = 0; i < max+1;i++)
		count[i] = 0;
	//count[]에 arr[i]값 누적
	for (i = 0; i < size; i++)
		count[arr[i]]++;
	//앞의 값을 누적
	for (i = 1; i < max+1; i++)
		count[i] += count[i - 1];
	//c배열에 누적하고, count[]값 감소
	for (i = size - 1; i >= 0; i--)
	{
		c[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	//c배열을 arr배열에 복사
	for (i = 0; i < size; i++)
		arr[i] = c[i];
}