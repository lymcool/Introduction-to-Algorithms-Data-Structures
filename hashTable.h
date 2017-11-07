#pragma once
//https://github.com/xuyicpp/Classical_Algorithms/blob/master/Introduction_to_Algorithms

#ifndef  _HASHTABLE_H_
#define _HASHTABLE_H_


const int EMPTY = 0;	//����0Ϊ�����ݱ�־(��ʱ�ؼ��ֲ���Ϊ0) 
const int TOMB = -1;	//����-1Ϊɾ�����ݱ�־(��ʱ�ؼ��ֲ���Ϊ-1) 

const int SUCCESS = 1;
const int UNSUCCESS = 0;
const int DUPLICATE = -1;	//	�ؽ��ֳ�ͻ(�ظ�)�������ٲ��� 
const int N = 4;		//hashsize[] ������ 
int hashsize[N] = { 11, 19, 37, 73 };


template<typename D>
class hashTable {
	D *elem;//����Ԫ�ش洢��ַ����̬��������
	int count, length;//����Ԫ�ظ�������ϣ������
	int
		sizeindex;//hashsize[sizeindex]Ϊ��ǰ����
	int *rando;//���������ָ��

	int Hash(keytype key) {
		return key%length;//һ���򵥹�ϣ����
	}
	int Hash2(keytype key) {
		return key % (length-2);//˫��ɢ��̽�鷨�ĵڶ�����ϣ����???
	}

	void Random() {//չʾ���̽�鷨	
		bool *ra = new bool[length];
		rando = new int[length];
		int i;
		for (i = 1;i < length;i++) {
			ra[i] = false;
		}
		for (i = 1;i < length;i++) {
			do {
				rando[i] = rand() % (length - 1) + 1;
				if (!ra[rando[i]])//δ���д���
					ra[rando[i]] = true;
				else
					rando[i] = 0;
			} while (rando[i] == 0);
			cout << "rand[" << i << "]=" << rando[i] << endl;
		}
		delete[] ra;
	}

	//�������к���,������0
	int increment(int i, keytype key) {
		switch(type){
		case 0:
			return i; 	//����̽�鷨
		case 1:
			return  ((i + 1) / 2)*((i + 1) / 2)*(int)pow(-1, i - 1);//����̽�鷨(1, -1, 4, -4, 9, -9,...)
		case 2:
			return i*Hash2(key);//˫��ɢ��̽�鷨
		case 3:
			return rando[i];//���̽�鷨(��Random()������һ��α�������)
		default:
				return i;//Ĭ������̽�鷨
           }
		return 0;
	}

	//����Ѱַ����ùؼ���ΪKey�ĵ�i�γ�ͻ�ĵ�ַP
	void collision(int i, keytype key,int &p) {
		p = (Hash(key)+increment(i,key)) % length;//��ϣ������������������
		if (p < 0)
			p += length;
	}

	//�ؽ���ϣ��
	void ReCreateHashTable(){
		int i;
		int len = length;
		D *p=elem;//pָ���ϣ��ԭ�����ݿռ�
		++sizeindex;
		if (sizeindex < N) {
			length = hashsize[sizeindex];
			elem = new D[length];
			assert(elem != NULL);////������ʽn ,���Ϊ��(��Ϊ0), ����stderr��ӡһ��������Ϣ,Ȼ��ͨ������ abort ����ֹ�������С� 
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
	int type;//̽�鷨����(0-3)
	hashTable() {
		count = 0;
		sizeindex = 0;
		length = hashsize[sizeindex];
		elem = new D[length];
		assert(elem != NULL);
		for (int i = 0;i < length;i++)
			elem[i].key = EMPTY;
		cout << "������̽�����ͣ�0:����;1:����;2:˫ɢ��;3:�������1" << endl;
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

	//�ڿ���Ѱַ��ϣ���в��ҹؼ���ΪKey��Ԫ�أ������ҳɹ�����pָ���������Ԫ���ڱ���λ�� 
	//������SUCCESS��������pָʾ����λ�ã�������UNSUCCESS 
	//c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο� 
	bool searchHash(int c, keytype key, int &p) {
		int c1;//��ͻ����
		int tomb = -1;//���ҵ��ĵ�һ��Ĺ����ַ����ɾ�����ݣ�
		p = Hash(key);	//��ϣ��ַ

		while (elem[p].key == TOMB ||elem[p].key!= EMPTY && !EQ(key, elem[p].key))
		{
		//�����ѱ�ɾ���������ҵ��ĵ�һ��Ĺ��
		if (elem[p].key == TOMB && tomb == -1) {
			tomb = p;
			c1 = c;
		}
		c++;
		//�ڳ�ͻ������ֵ�ڣ�����һ��̽���ַp
		if (c <= hashsize[sizeindex] / 2)
			collision(key, p, c);
		else
			break;
		}
		//���ҳɹ�
		if EQ(key, elem[p].key)
			return true;
		else {//���ҹ�����������Ĺ��
			if (tomb == -1) {
				p = tomb;
				c = c1;
			}
			return false;
		}
	}

	//���Ҳ��ɹ�ʱ������Ԫ��e���뵽����Ѱַ��ϣ���У�������SUCCESS�����ҳɹ�ʱ���� 
	//DUPLICATE������������Ԫ�أ�����ͻ���������򲻲��룬���ؽ���ϣ������UNSUCCESS 
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
		else//δ�ҵ�������ͻ�����Ѵﵽ���ޣ��ؽ���ϣ��
		{
			cout << "����ϣ��ַ��˳������ؽ�ǰ�Ĺ�ϣ��" << endl;
			traverseHash(visit);
			cout << "�ؽ���ϣ��" << endl;
			ReCreateHashTable();	
			return UNSUCCESS;
		}
	}

	//�ӹ�ϣ����ɾ���ؽ���ΪKey������Ԫ�أ��ɹ�����true��������λ�õĹؼ�����ΪTMOB; ���ɹ�����false 
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

	//����Ԫ��[i]��ֵ
	D getElem(int i)const {
		return elem[i];
	}
	//����ϣ��ַ��˳�������ϣ��H
	void traverseHash(void(*visit)(int, D*))const {
		int i;
		cout << "��ϣ��ַ0~" << length - 1 << endl;
		for (i = 0; i < length; ++i) {
			if (elem[i].key != EMPTY&&elem[i].key != TOMB)
				visit(i,&elem[i]);
		}

	}
};


#endif