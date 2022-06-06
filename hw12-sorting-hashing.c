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

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	printf("----- 허정윤 2021041047 -----\n");
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

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
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
	//a가 NULL인 경우의 에러메시지
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}

	//위에는 a[] 글자를 출력
	//아래는 값을 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

//선택정렬
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
		minindex = i; //비교군은 i번째 값부터
		min = a[i]; //뒤에서부터 하나씩

		//i 다음 값부터 비교 시작.(앞은 정렬되어있음)
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			//min보다 작은 값을 만나면
			if (min > a[j])
			{
				//min 값과 index를 바꿔줌
				min = a[j];
				minindex = j;
			}
		}
		//a[minindex]는 결국 min이라 a[minindex]와 a[i]의 값을 swap한 결과물이 된다.
		a[minindex] = a[i];
		a[i] = min;
	}
	//줄긋고 출력.
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

//삽입정렬
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	//앞에서 부터 훑기
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		//a[j-1]이 큰 경우는 계속 a[j]를 밖으로 한칸 옮기고, j는 1 빼줌.
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		//이때는 a[j-1]<t이거나 j가 0이 되버렸거나.(이때는 모든 값들이 t보다 크다는 의미.)
		//이때 j에다가 t를 넣어준다.
		a[j] = t;
	}

	//줄긋고 출력.
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//버블정렬
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	//한번 반복당 뒤에서부터 하나씩 정렬되므로.
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{	
		//j-1로 탐색하므로 1부터 반복
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			//앞 값이 뒷 값보다 크면
			if (a[j-1] > a[j])
			{
				//swap
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	//줄긋고 출력
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

	//정석대로 h를 크기의 반으로 두고, 반복마다 /2.
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				//k가 뒷쪽 값인가 && 'a[k-h]>a[k]'인가.
				//맞다면 k를 앞의 인덱스로 바꾸고.
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				//안쪽과 합쳐서 셸 안쪽의 값들이 어느정도 정렬됨(최소한 오른쪽에 v보다 큰 값들만 모임.)
				//한 칸(h크기)씩 옮기면서 v보다 큰 값들이 오른쪽에 모이고, 작은 값을 만나면/k가 h-1보다 작아지면 그대로 저장.
				a[k] = v;
			}
		}
	}
	//줄 긋고 출력.
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
		//v는 a 배열의 마지막 값
		//i는 전위로 더해져버린 값부터 비교하므로 -1로 두어 0부터 비교할 수 있게
		//j는 v 자체가 n-1에 있어서 n-1을 비교할 필요가 없으므로
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			//반복을 통해 a[i]가 v보다 크거나 같을 때의 i
			//a[j]가 v보다 작거나 같을 때의 j
			while(a[++i] < v);
			while(a[--j] > v);

			//이 경우면 둘에 한정해서는 순서가 맞으므로 넘어간다.
			if (i >= j) break;

			//a[i]와 a[j]의 값을 스왑한다.
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		//위의 반복을 끝냈을 때의 i는 a[i]가 v보다 크거나 같지만
		//j보다 큰 경우이다.
		//a[i]와 a[n-1]을 스왑한다.
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		//다시 퀵정렬을 실행해준다.
		//배열을 i를 기준으로 둘로 나눈다
		//앞의 i개/뒤의 n-i-1개. 중간에 i개는 고정된다.
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
	//정해둔 사이즈로 key 값에 나머지 연산을 한다.
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	//key값이 되면 안되므로 모든 값을 -1로 초기화.
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
		//a의 값을 key로 받아서 hashcode를 만든다.
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		//hashtable에 hashcode를 인덱스로 찾은 값이 -1이면(지정되지 않음) key 값을 넣어준다
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		//그렇지 않으면
		} else 	{
			//hashcode를 index로 받고
			index = hashcode;

			//지정되지 않은 칸을 찾을 때까지(종료조건)
			while(hashtable[index] != -1)
			{	
				//index에 1을 더한 값을 테이블 크기값으로 나머지 연산을 한 값을
				//index로 한다.
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			//나왔다는 것은 지정되지 않은 칸을 찾았단 의미이므로
			//그 칸에 key를 넣어준다.
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	//hashCode함수에 key를 넣어서 index를 가져온다.
	int index = hashCode(key);

	//ht(==hashtable)에 index를 넣은 값과 key가 일치하면 index 리턴.
	if(ht[index] == key)
		return index;

	//index를 1씩 더해가며 ht[index]가 key가 아니면 계속 반복
	while(ht[++index] != key)
	{
		//MAX_HASH_TABLE_SIZE로 나머지 연산.
		//결국 key가 될때까지 0~최대사이즈까지 돌게 됨.
		index = index % MAX_HASH_TABLE_SIZE;
	}
	//반복 종료는 ht[index]가 key와 일치한다는 의미
	//리턴해줌.
	return index;
}