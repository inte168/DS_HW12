/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	printf("----- ������ 2021041047 -----\n");
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{	
	//a�� NULL�� ����� �����޽���
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}

	//������ a[] ���ڸ� ���
	//�Ʒ��� ���� ���
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

//��������
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //�񱳱��� i��° ������
		min = a[i]; //�ڿ������� �ϳ���

		//i ���� ������ �� ����.(���� ���ĵǾ�����)
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			//min���� ���� ���� ������
			if (min > a[j])
			{
				//min ���� index�� �ٲ���
				min = a[j];
				minindex = j;
			}
		}
		//a[minindex]�� �ᱹ min�̶� a[minindex]�� a[i]�� ���� swap�� ������� �ȴ�.
		a[minindex] = a[i];
		a[i] = min;
	}
	//�ٱ߰� ���.
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

//��������
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	//�տ��� ���� �ȱ�
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		//a[j-1]�� ū ���� ��� a[j]�� ������ ��ĭ �ű��, j�� 1 ����.
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		//�̶��� a[j-1]<t�̰ų� j�� 0�� �ǹ��Ȱų�.(�̶��� ��� ������ t���� ũ�ٴ� �ǹ�.)
		//�̶� j���ٰ� t�� �־��ش�.
		a[j] = t;
	}

	//�ٱ߰� ���.
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//��������
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	//�ѹ� �ݺ��� �ڿ������� �ϳ��� ���ĵǹǷ�.
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{	
		//j-1�� Ž���ϹǷ� 1���� �ݺ�
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			//�� ���� �� ������ ũ��
			if (a[j-1] > a[j])
			{
				//swap
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	//�ٱ߰� ���
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	//������� h�� ũ���� ������ �ΰ�, �ݺ����� /2.
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				//k�� ���� ���ΰ� && 'a[k-h]>a[k]'�ΰ�.
				//�´ٸ� k�� ���� �ε����� �ٲٰ�.
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				//���ʰ� ���ļ� �� ������ ������ ������� ���ĵ�(�ּ��� �����ʿ� v���� ū ���鸸 ����.)
				//�� ĭ(hũ��)�� �ű�鼭 v���� ū ������ �����ʿ� ���̰�, ���� ���� ������/k�� h-1���� �۾����� �״�� ����.
				a[k] = v;
			}
		}
	}
	//�� �߰� ���.
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		//v�� a �迭�� ������ ��
		//i�� ������ ���������� ������ ���ϹǷ� -1�� �ξ� 0���� ���� �� �ְ�
		//j�� v ��ü�� n-1�� �־ n-1�� ���� �ʿ䰡 �����Ƿ�
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			//�ݺ��� ���� a[i]�� v���� ũ�ų� ���� ���� i
			//a[j]�� v���� �۰ų� ���� ���� j
			while(a[++i] < v);
			while(a[--j] > v);

			//�� ���� �ѿ� �����ؼ��� ������ �����Ƿ� �Ѿ��.
			if (i >= j) break;

			//a[i]�� a[j]�� ���� �����Ѵ�.
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		//���� �ݺ��� ������ ���� i�� a[i]�� v���� ũ�ų� ������
		//j���� ū ����̴�.
		//a[i]�� a[n-1]�� �����Ѵ�.
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		//�ٽ� �������� �������ش�.
		//�迭�� i�� �������� �ѷ� ������
		//���� i��/���� n-i-1��. �߰��� i���� �����ȴ�.
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
	//���ص� ������� key ���� ������ ������ �Ѵ�.
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	//key���� �Ǹ� �ȵǹǷ� ��� ���� -1�� �ʱ�ȭ.
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;

	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		//a�� ���� key�� �޾Ƽ� hashcode�� �����.
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		//hashtable�� hashcode�� �ε����� ã�� ���� -1�̸�(�������� ����) key ���� �־��ش�
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		//�׷��� ������
		} else 	{
			//hashcode�� index�� �ް�
			index = hashcode;

			//�������� ���� ĭ�� ã�� ������(��������)
			while(hashtable[index] != -1)
			{	
				//index�� 1�� ���� ���� ���̺� ũ�Ⱚ���� ������ ������ �� ����
				//index�� �Ѵ�.
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			//���Դٴ� ���� �������� ���� ĭ�� ã�Ҵ� �ǹ��̹Ƿ�
			//�� ĭ�� key�� �־��ش�.
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	//hashCode�Լ��� key�� �־ index�� �����´�.
	int index = hashCode(key);

	//ht(==hashtable)�� index�� ���� ���� key�� ��ġ�ϸ� index ����.
	if(ht[index] == key)
		return index;

	//index�� 1�� ���ذ��� ht[index]�� key�� �ƴϸ� ��� �ݺ�
	while(ht[++index] != key)
	{
		//MAX_HASH_TABLE_SIZE�� ������ ����.
		//�ᱹ key�� �ɶ����� 0~�ִ��������� ���� ��.
		index = index % MAX_HASH_TABLE_SIZE;
	}
	//�ݺ� ����� ht[index]�� key�� ��ġ�Ѵٴ� �ǹ�
	//��������.
	return index;
}