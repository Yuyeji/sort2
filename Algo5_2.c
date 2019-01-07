#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

void counting_sort(int *arr, int p, int size);
void radix_sort(int *arr, int size);
int heap_size(int *arr);

int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("input10000.txt", "r");

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

	radix_sort(arr, heap_size(arr));

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

int getMax(int *arr, int size) {
	int max = 0;

	for (int i = 0; i < size; i++)
		if (arr[i] > max)
			max = arr[i];

	return max;
}

/*couting_sort�̿��� radix_sort*/
void radix_sort(int *arr, int size) {
	int max = getMax(arr, size); //�ִ밪

	//��� digit������ counging_sort
	for (int p = 1; max / p > 0; p *= 10) {
		counting_sort(arr, p, size);
	}
}

void counting_sort(int arr[], int p, int size){
	int max = getMax(arr, size); //�ִ밪
	int *c, *count;
	int i ;

	c = (int *)malloc(sizeof(int)*(size));
	count = (int *)malloc(sizeof(int)*(max+1));
	
	//�迭 �ʱ�ȭ
	for (i = 0; i < 10;i++) 
		count[i] = 0;
	//count[]�� (arr[i] / p)%10 �� ����
	for (i = 0; i < size; i++)
		count[(arr[i] / p)%10]++;
	//���� ���� ����
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	//c�迭�� �����ϰ�, count[]�� ����
	for (i = size - 1; i >= 0; i--)
	{
		c[count[(arr[i] / p) % 10] - 1] = arr[i];
		count[(arr[i] /p) % 10]--;
	}

	//c�迭�� arr�迭�� ����
	for (i = 0; i < size; i++)
		arr[i] = c[i];
}