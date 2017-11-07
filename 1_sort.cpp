#include <iostream>
#include <vector>
#include <time.h>

using namespace std;


//插入排序(直接，二分，希尔)
//归并排序（二路），选择排序（及时终止）,堆排序（大顶堆,下标从1开始）
//快排，顺序统计（随机选择算法；最坏线性选择算法）
//计数排序，桶排序（直接映射，*10%max），基数排序
//冒泡排序

     /*direct—InsertSort*/
template<class T>
void dirInsertSort(T a[], int n) {
	for (int i = 1;i < n;i++) {
		T t = a[i];
		int j;
		for (j = i - 1;j >= 0 && a[j]>t;j--) {
			a[j + 1] = a[j];
        }
		a[j + 1] = t;
	}
}

  /*binary—InsertSort*/
	template<class T>
	int BinarySearchIndex(T a[], int n,int x) {
		int l = 0;
		int r = n;
		while (l<=r) {
			int m = (l + r) / 2;
			if (x < a[m])
				r = m-1;
			else
				l = m + 1;
		}
		return l;
}
		template<class T>
		void binInsertSort(T a[], int n) {
			int i, j;
			for ( i = 1;i < n;i++) {
				int ind = BinarySearchIndex(a, i - 1, a[i]);
				if (i != ind) {
					T t = a[i];
					for ( j = i - 1;j >= ind;j--) {
						a[j + 1] = a[j];
					}
					a[j + 1] = t;//a[ind]=t;
				}
			}
		}

			/*shell—InsertSort*/     //O(nlog2n)
			template<class T>
			void ShellInsert(T a[], int n,int step) {
				int i,j;
				for (i = step;i < n;i++) {
					T t = a[i];
					for (j = i - step;j >= 0 && a[j] > t;) {
						a[j + step] = a[j];
						j = j - step;
					}
					a[j + step] = t;
				}
			}
			template<class T>
			void sheInsertSort(T a[], int n) {
				int step = n / 2;// Each increment is 1 / 2 of the original
				if (n>1) {
					while (step >= 1) {
						ShellInsert(a, n, step);
						step = step / 2;
					}
				}
			}



//////////////////////////////////////


template<class T>
void mergeSort(T a[], int n) {
	//merge a to b,merge b to a
	T *b = new T[n]; //b——Auxiliary array
	int segmentSize = 1;
	while (segmentSize < n)
	{
		mergePass(a, b, n, segmentSize);
		segmentSize += segmentSize;
		mergePass(b, a, n, segmentSize);
		segmentSize += segmentSize;
	}
	delete[]b;
}
template<class T>
void mergePass(T x[], T y[], int n, int segmentSize) {
	//Merge adjacent data segments from x[] to y[]	
	int i = 0;
	while (i <= n - 2 * segmentSize)
	{
		merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
		i += 2 * segmentSize;
	}
	if (i + segmentSize<n) {
		merge(x, y, i, i + segmentSize - 1, n - 1);
	}
	else {
		for (int j = i;j < n;j++)
			y[j] = x[j];
	}
}
template<class T>
void merge(T s[], T d[], int startOfFirst, int endOfFirst, int endOfSecond) {
	//Merge adjacent data segments from s[] to d[]	
	int first = startOfFirst;//index of first s
	int second = endOfFirst + 1;//index of second s
	int result = startOfFirst;//result initialize
	while ((first <= endOfFirst) && (second <= endOfSecond))
	{
		if (s[first] <= s[second]) {
			d[result++] = s[first++];
		}
		else {
			d[result++] = s[second++];
		}
	}
	//Remaining element
	if (first>endOfFirst) {
		for (int p = second;p <= endOfSecond;p++)
			d[result++] = s[p];
	}
	else {
		for (int q = first;q <= endOfFirst;q++)
			d[result++] = s[q];
	}
}

///////////////////////////////////


template<class T>
void selectionSort(T a[],int n) {
	bool sorted = false;
	for (int i = n;!sorted && (i >1) ;i--) {
		sorted = true;
		int indexofMax = 0;
		//find the max element		
		for (int j = 1;j < i;j++)
			if (a[j] >= a[indexofMax]) 
				indexofMax = j;
			else
				sorted = false;
		swap(a[indexofMax],a[i-1]);
	}
}
////////////////////////////////////////////

template<class T>
void HeapAdjust(T a[], int i,int n) {
	int lchild=2*i;
	int rchild = 2 * i+1;
	int max= i;
	if (i <= n / 2)//仅对非叶节点进行调整
	{
		if(lchild<=n && a[lchild]>a[max]){
			max = lchild;
		 }
		if(rchild <= n && a[rchild]>a[max]){
			 max = rchild;
		 }
		if(max!=i){
			swap(a[i],a[max]); 
		    HeapAdjust(a, max, n);//非叶节点最大序号值为size/2 
		 }
	}

}

template<class T>
void BuildHeap(T a[], int n) {
	int i;
	for (i = n / 2;i >= 1;i--) {
		HeapAdjust(a, i, n);//非叶节点最大序号值为size/2 
	}
}

template<class T>
void HeapSort(T a[], int n) {
	int i;
	BuildHeap(a,n);
	for (i = n;i >= 1;i--) {
		swap(a[1],a[i]); //交换堆顶和最后一个元素，即每次将剩余元素中的最大者放到最后面 
		HeapAdjust(a,1,i-1);  //重新调整堆顶节点成为大顶堆 
	}
}

///////////////////////////////////

template<class T>
void quickSort(T a[], int l, int r) {
	if (l<r) {
		int x = a[l];//Reference element
		int i = l;
		int j = r;//Two instructions
		while (i<j) {
			//move j form right to left,find a value to fill Vacant position a[ ],then start to move i
			while (i < j && a[j] >= x)
				j--;
			if (i < j)
				a[i++] = a[j];
			//move i form left to right,find a value to fill Vacant position a[ ],then start to move j
			while (i < j && a[i]<x)
				i++;
			if (i < j)
				a[j--] = a[i];
		}
		a[i] = x;//put the Reference element
				 // recursively call
		quickSort(a, l, i - 1);
		quickSort(a, i + 1, r);
	}
}
///////////////////////////////////
//顺序统计，找第k大的元素
        /*随机选择法*/
template<class T>
int randomized_partition(T a[], int l,int r) {
	srand(time(NULL));
	int m = rand() % (r - l + 1) + l;
	swap(a[l],a[m]);
	int x = a[l];
	int i = l;
	for (int j = l + 1;j <= r;j++) {
		if (a[j] > x) {
			i = i + 1;
			swap(a[j], a[i]);//??
		}
	}
	swap(a[i],a[l]);
	return i;
}
template<class T>
T randomized_select(T a[], int l,int r,int k) {
	if (l == r)
		return a[l];
	int pivot=randomized_partition(a,l,r);
	int i = pivot - l + 1;//rank of the pivot
	if (i == k)
		return a[pivot];
	else if (i < k)
		return randomized_select(a, pivot + 1, r,  k - i);
	else
		return randomized_select(a, l,pivot - 1, k);
}

       /*最坏线性选择算法*/   ////////找第k小的数
template<class T>
void insertion_sort(vector<T> &A, int p, int q) {
	int i, j, key;
	for (i = p + 1;i <= q;i++) {
		key = A[i];
		j = i - 1;
		while (A[j] > key &&j > p) {
			A[j] = A[j + 1];
			j--;
		}
			A[j + 1] = key;		
	}
}

template<class T>
T GetMedian(vector<T> & A, int l, int r) {
	insertion_sort(A,l,r);
	//return A[(l+r)/2];
	return A[l+(r-l) / 2];
}

template<class T>
int partitionWithPivot(vector<T> &A,int p,int q, T pivot) {
	for (int i = p; i <= q;i++) {
		if (A[i] == pivot) {
			swap(A[i], A[p]);
			break;
		}
	}
	T x= A[p];
	int i = p;
	for (int j = p + 1;j <= q;j++) {
		if (A[j] < x) {
			i = i + 1;
			swap(A[i], A[j]);
		}
	}
	swap(A[i], A[p]);
	return i;

}
	
template<class T>
T WorseLinearSelect(vector<T> &A, int l, int r, int k) {
	if (l == r) 
		return A[l];
		int length = r - l + 1;
		int medianCount = 1;
		if (length>5)
			medianCount = length % 5 > 0 ? length / 5 + 1 : length / 5;
		vector<T> medians(medianCount);
		int m, i;
		for (i = 0, m = l;i < medianCount - 1;i++) {
			medians[i] = GetMedian(A, m, m + 4);
			m += 5;
		}
		medians[medianCount - 1] = GetMedian(A, m, r);
		T  pivot = WorseLinearSelect(medians, 0, medianCount - 1, (medianCount + 1) / 2);
		int r0 = partitionWithPivot(A, l, r, pivot);
		int num = r0 - l + 1;//rank
		if (num== k)
			return pivot;
		else if (num > k)
			return WorseLinearSelect(A, l, r0 - 1, k);
		else
			return WorseLinearSelect(A, r0 + 1, r, k - num);

}


///////////////////////////////////
template<class T>
void countSort(T a[], int n) {
	//rank every element
	int *r = new int[n];
	for (int i = 0;i < n;i++) {
		r[i] = 0;//为什么需要初始化？后面用到了++操作
	}
	for (int i = 1;i < n;i++) {
		for (int j = 0;j < i;j++) {
			if (a[i] > a[j]) r[i]++;
			else r[j]++;
		}
	}
	//Auxiliary array u[n]
	T *u = new T[n];
	for (int i = 0;i < n;i++) 
		u[r[i]] = a[i];
	for (int i = 0;i < n;i++)
		a[i] = u[i];
	delete[] u;
	delete[] r;
}

///////////////////////////////////

//Classification+Collection+sorting
//directly mapping
void bucketSort0(int a[], int n) {
	//find max in the array
	int max=a[0];
	int i,j;
	for (i = 1;i < n;i++) {
		if (a[i] > max) max= a[i];
	}
	//Divide the element into the bucket
	max = max + 1;
	int *buckets;
    if ((buckets = new int[max]) == NULL)
	   return;
	 memset(buckets, 0, max * sizeof(int));
	 //count and sort
	for (i = 0;i < n;i++) {
		buckets[a[i]]++;
     }
	for (i = 0,j=0;i < max;i++) {
		while((buckets[i]--)>0)
		a[j++] =i;
    }
	delete[] buckets;
}

////映射到桶：每个数据乘以10再与最大数据相除(0~10)；桶内：插入排序
template<class T>
void insertion_sort(T a[], int l,int r) {
	for (int i = l + 1;i <=r;i++) {
		int x = a[i];
		int j = i - 1;
		while (j>=l && a[j]>x) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = x;
	}
}
template<class T>
void bucketSort(T a[], int n) {
	T max = a[0];
	int i, k;
	int l,r;
	for (i = 1;i < n;i++) {
		if (a[i] > max) max = a[i];
	}//find max in the array
	int count[11];
	for (i = 0;i < 11;i++) {
		count[i] = 0;
	}
	T *temp = new T[n];
	for (i = 0;i < n;i++) {
	k=(a[i]*10)/max ;
	count[k]++;
	}//Divide the element into the bucket
	for(i = 1;i < 11;i++) {
		count[i] = count[i] + count[i-1];
	}
	for (i = n - 1;i >= 0;i--) {
		k = (a[i] * 10) / max;
		temp[count[k] - 1] = a[i];
		count[k]--;
	}
	for (i = 0;i < n;i++) {
		a[i] = temp[i];
	}
	delete[]temp;
	//对每一个桶的元素进行排序
	for (i = 0;i < n;i++) {
		l = count[i];
		r= count[i+1]-1;
		if (l < r)
		  insertion_sort(a, l, r);
	}
}

///////////////////////////////////////////////////////
template<class T>
int maxbit(T a[], int n) {
	int d = 1;
	int p = 10;
	for (int i = 0;i < n;i++) {
		while (a[i] >= p) {
			d++;
			p *= 10;
		}
	}
	return d;
}
template<class T>
void RadixSort(T a[], int n) {
	int d = maxbit(a,n);//bit num
	T *temp = new T[n];
	int count[10];
	int radix = 1;
	int i, j,k;
	for ( i = 1;i <= d;i++) {//Sorted by d times
		for ( j = 0;j < 10;j++) {
			count[j] = 0;
		}
		for ( j = 0;j < n;j++) {//Classified by bit
			k = (a[j] / radix) % 10;
			count[k]++;
		}
		for ( j = 1;j <10;j++) {//rank
			count[j]=count[j]+count[j-1];
		}
		for (j = n-1;j >=0;j--) {//put into temp, from behind,keep stability
			k = (a[j]/radix) % 10;
			temp[count[k] - 1] = a[j];
			count[k]--;	
		}
		for (j = 0;j < n;j++) {//copy
			a[j]= temp[j];
		}
		radix = radix*10;
	}
	delete[]temp;
}



/////////////////////////////////////////////////////////

template<class T>
bool bubble(T a[], int n) {
	bool swapped = false;
	for (int i = 0;i < n-1;i++) {
		if (a[i] > a[i + 1]) {
			swap(a[i], a[i + 1]);
			swapped = true;
		}
	}
	return 	swapped;
}
template<class T>
void bubbleSort(T a[], int n) {
	for (int i = n;i > 1 && bubble(a, i);i--);
}





void main() {

	int a[6]= { 2,5,32,28,13,4 };
	vector<int> b(a,a+6);
	for (int i = 0;i < 6;i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	cout << "afer sort:"<<endl;
	countSort(a,6);
	for (int i = 0;i < 6;i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	int x = randomized_select(a, 0,5,3);
	cout << x;
	
	system("pause");
}