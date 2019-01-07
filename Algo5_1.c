#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

void counting_sort(int *arr, int size);
int getMax(int *arr, int size);

int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("counting.txt", "r");

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

	//counting sort ȣ��
	counting_sort(arr, heap_size(arr));

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\t", arr[j]);
	}

	printf("\n���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}
int heap_size(int *arr) { //arr�� ũ��
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
	int max = getMax(arr, size); //�ִ밪
	int *c, *count;
	int i;

	c = (int *)malloc(sizeof(int)*(size));
	count = (int *)malloc(sizeof(int)*(max + 1));

	//�迭 �ʱ�ȭ
	for (i = 0; i < max+1;i++)
		count[i] = 0;
	//count[]�� arr[i]�� ����
	for (i = 0; i < size; i++)
		count[arr[i]]++;
	//���� ���� ����
	for (i = 1; i < max+1; i++)
		count[i] += count[i - 1];
	//c�迭�� �����ϰ�, count[]�� ����
	for (i = size - 1; i >= 0; i--)
	{
		c[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	//c�迭�� arr�迭�� ����
	for (i = 0; i < size; i++)
		arr[i] = c[i];
}