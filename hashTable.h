
#pragma once
//https://github.com/xuyicpp/Classical_Algorithms/blob/master/Introduction_to_Algorithms
//http://www.cnblogs.com/zhoutaotao/p/4067749.html

#ifndef  _HASHTABLE_H_
#define _HASHTABLE_H_


const int EMPTY = 0;	//设置0为无数据标志(此时关键字不可为0) 
const int TOMB = -1;	//设置-1为删除数据标志(此时关键字不可为-1) 

const int SUCCESS = 1;
const int UNSUCCESS = 0;
const int DUPLICATE = -1;	//	关节字冲突(重复)，不能再插入 
const int N = 4;		//hashsize[] 的容量 
int hashsize[N] = { 11, 19, 37, 73 };


template<typename D>
class hashTable {
	D *elem;//数据元素存储基址，动态分配数组
	int count, length;//数据元素个数，哈希表容量
	int
		sizeindex;//hashsize[sizeindex]为当前容量
	int *rando;//随机数数组指针

	int Hash(keytype key) {
		return key%length;//一个简单哈希函数
	}
	int Hash2(keytype key) {
		return key % (length-2);//双重散列探查法的第二个哈希函数???
	}

	void Random() {//展示随机探查法	
		bool *ra = new bool[length];
		rando = new int[length];
		int i;
		for (i = 1;i < length;i++) {
			ra[i] = false;
		}
		for (i = 1;i < length;i++) {
			do {
				rando[i] = rand() % (length - 1) + 1;
				if (!ra[rando[i]])//未挑中此数
					ra[rando[i]] = true;
				else
					rando[i] = 0;
			} while (rando[i] == 0);
			cout << "rand[" << i << "]=" << rando[i] << endl;
		}
		delete[] ra;
	}

	//增量序列函数,出错返回0
	int increment(int i, keytype key) {
		switch(type){
		case 0:
			return i; 	//线性探查法
		case 1:
			return  ((i + 1) / 2)*((i + 1) / 2)*(int)pow(-1, i - 1);//二次探查法(1, -1, 4, -4, 9, -9,...)
		case 2:
			return i*Hash2(key);//双重散列探查法
		case 3:
			return rando[i];//随机探查法(由Random()建立的一个伪随机数列)
		default:
				return i;//默认线性探查法
           }
		return 0;
	}

	//开放寻址法求得关键字为Key的第i次冲突的地址P
	void collision(int i, keytype key,int &p) {
		p = (Hash(key)+increment(i,key)) % length;//哈希函数加增量后再求余
		if (p < 0)
			p += length;
	}

	//重建哈希表
	void ReCreateHashTable(){
		int i;
		int len = length;
		D *p=elem;//p指向哈希表原有数据空间
		++sizeindex;
		if (sizeindex < N) {
			length = hashsize[sizeindex];
			elem = new D[length];
			assert(elem != NULL);////计算表达式n ,如果为假(即为0), 先向stderr打印一条出错信息,然后通过调用 abort 来终止程序运行。 
			for (i = 0;i < length;i++)
				elem[i].key = EMPTY;
			for (i = 0;i < length;i++) {
				if (p[i].key != EMPTY && p[i].key != TOMB)
					InsertHash(p[i]);
			}
			delete[] p;

			if (type == 3)
				Random();
		}
   }

public:
	int type;//探查法类型(0-3)
	hashTable() {
		count = 0;
		sizeindex = 0;
		length = hashsize[sizeindex];
		elem = new D[length];
		assert(elem != NULL);
		for (int i = 0;i < length;i++)
			elem[i].key = EMPTY;
		cout << "请输入探查类型（0:线性;1:二次;2:双散列;3:随机）：1" << endl;
		type = 1;
		if (type == 3)
			Random();
		else
			rando = NULL;
	}

	//
	~hashTable() {
		if (elem)
			delete[] elem;
		if (type == 3)
			delete[] rando;
	}

	//在开放寻址哈希表中查找关键字为Key的元素，若查找成功，以p指向待查数据元素在表中位置 
	//并返回SUCCESS；否则，以p指示插入位置，并返回UNSUCCESS 
	//c用以计冲突次数，其初值置零，供建表插入时参考 
	bool searchHash(int c, keytype key, int &p) {
		int c1;//冲突次数
		int tomb = -1;//存找到的第一个墓碑地址（被删除数据）
		p = Hash(key);	//哈希地址

		while (elem[p].key == TOMB ||elem[p].key!= EMPTY && !EQ(key, elem[p].key))
		{
		//数据已被删除，且是找到的第一个墓碑
		if (elem[p].key == TOMB && tomb == -1) {
			tomb = p;
			c1 = c;
		}
		c++;
		//在冲突次数阈值内，求下一个探查地址p
		if (c <= hashsize[sizeindex] / 2)
			collision(key, p, c);
		else
			break;
		}
		//查找成功
		if EQ(key, elem[p].key)
			return true;
		else {//查找过程中遇到过墓碑
			if (tomb == -1) {
				p = tomb;
				c = c1;
			}
			return false;
		}
	}

	//查找不成功时将数据元素e插入到开放寻址哈希表中，并返回SUCCESS；查找成功时返回 
	//DUPLICATE，不插入数据元素；若冲突次数过大，则不插入，并重建哈希表，返回UNSUCCESS 
	int InsertHash(D e) {
		int p=0;
		int c = 0;
		if (searchHash(e.key, p, c))
			return DUPLICATE;
		else if (c <= hashsize[sizeindex] / 2) {
			elem[p]=e;
			++count;
			return SUCCESS;
		}
		else//未找到，但冲突次数已达到上限，重建哈希表
		{
			cout << "按哈希地址的顺序遍历重建前的哈希表：" << endl;
			traverseHash(visit);
			cout << "重建哈希表" << endl;
			ReCreateHashTable();	
			return UNSUCCESS;
		}
	}

	//从哈希表中删除关节字为Key的数据元素，成功返回true，并将该位置的关键字设为TMOB; 不成功返回false 
	bool deleteHash(keytype key, D &e) {
		int p=0;
		int c = 0;
		if (searchHash(key, p, c)) {
			e = elem[p];
			elem[p].key = TOMB;
			--count;
			return true;
		}
		else
			return false;
	}

	//返回元素[i]的值
	D getElem(int i)const {
		return elem[i];
	}
	//按哈希地址的顺序遍历哈希表H
	void traverseHash(void(*visit)(int, D*))const {
		int i;
		cout << "哈希地址0~" << length - 1 << endl;
		for (i = 0; i < length; ++i) {
			if (elem[i].key != EMPTY&&elem[i].key != TOMB)
				visit(i,&elem[i]);
		}

	}
};


#endif
