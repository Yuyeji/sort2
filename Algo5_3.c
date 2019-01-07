#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

void bucket_sort(float *arr, int size);
void InsertSort(int *arr, int n);
int heap_size(float *arr);

int main(void) {
	float *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("bucket.txt", "r");

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
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

	printf("���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

int heap_size(float *arr) { //arr�� ũ��
	return (_msize((void*)arr) / sizeof(int));
}

void bucket_sort(float *arr, int size) {
	int i;
	int *count;
	count = (int *)malloc(sizeof(int)*size);

	//�迭 �� �ʱ�ȭ
	for (i = 0; i < size; i++)
		count[i] = 0;
	//count[arr[i]]�� arr[i]�� ����
	for (i = 0; i < size; i++) {
		int k = arr[i];
		count[k] = arr[i];
	}

	//count�迭�� �����������ش�.
	for (i = 0; i < size; i++)
		InsertSort(count, i);

	//arr�� ����
	for (i = 0; i < size; i++)
		arr[i] = count[i];
}

/*���� ����*/
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