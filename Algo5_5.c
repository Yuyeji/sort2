#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

void quick_sort(int *arr, int left, int right);
int partition(int *arr, int left, int right);
int getPivot(int *arr, int left, int right);
int getMid(int left, int right);
int heap_size(int *arr);

int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("input500.txt", "r");

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	startTime = clock();

	quick_sort(arr, 0, heap_size(arr) - 1);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);


	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\t", arr[j]);
	}

	printf("���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

int heap_size(int *arr) { //arr�� ũ��
	return (_msize((void*)arr) / sizeof(int));
}

void quick_sort(int *arr, int left, int right) {
	if (left == right)
		arr[left];


	if (left < right) { //������ ������ �� �� �̻��̸� 
		int q = getPivot(arr, left, right); //getPivot
		int k = q - left + 1;

		if ((right + 1) == k)
			arr[q];

		quick_sort(arr, left, q - 1); //pivot�� ���� �� ��Ʈ
		quick_sort(arr, q + 1, right); //pivot�� ������ �� ��Ʈ
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
	//pivot�� �߰����� ��ġ
	temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;

	return i + 1; //pivot�� ��ġ ��ȯ
}

int getPivot(int *arr, int left, int right) {
	int i,mid;
	int temp;
	int size = right - left + 1;
	int *median;

	median = (int *)malloc(sizeof(int)*(size / 5));

	//5���� ��� �߰� ������ ã�´�.
	for (i = 0; i<(size / 5); i++)
		median[i] = getMid(i * 5, (i * 5) + 4);

	//�߰������� �迭���� �߰����� ã�´�.
	mid = getMid(0, (size / 5) - 1);

	temp = arr[right];
	arr[right] = arr[mid];
	arr[mid] = temp;

	return partition(arr, left, right);
}

int getMid(int left, int right) {
	return (left+right)/2;
}