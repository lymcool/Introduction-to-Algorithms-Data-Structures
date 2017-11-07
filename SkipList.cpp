///* ����Ծ��������򵥵Ĳ����ɾ��Ԫ�أ����ṩO(logn)�Ĳ�ѯʱ�临�Ӷȡ� */
///*
//SkipList_Int������
//(1) �ɺܶ��ṹ��ɣ�level��ͨ��һ���ĸ�����������ģ�������50%�Ĳ������ʡ�
//(2) ÿһ�㶼��һ�����������Ĭ��������ÿһ�������ͷ��Ϊ���㡣
//(3) ��ײ�(Level 1)�������������Ԫ�ء�
//(4) ���һ��Ԫ�س�����Level i �������У�������Level i ֮�µ�����Ҳ������֡�
//(5) ÿ���ڵ�����ĸ�ָ�룬���п���Ϊnullptr��
//(6) ÿһ���������Ϊ�������ӣ�����Ϊ˫�����ӡ�
//*/
////http://www.cnblogs.com/learnhow/p/6749648.html
//
//#include <iostream>
//#include <cstdlib>//�������
//#include <ctime>
//
//using namespace std;
//
//class SkipList {
//	struct skiplistNode {
//		skiplistNode(int val=INT_MIN):value(val),up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
//		int value;
//		struct skiplistNode* up;
//		struct skiplistNode* down;
//		struct skiplistNode* left;
//		struct skiplistNode* right;
//	};
//	skiplistNode* head;// ͷ�ڵ㣬��ѯ��ʼ��
//	int lvl_num;// ��ǰ�������
//	bool randomVal();//����ж�
//
//public:
//	SkipList() :lvl_num(1) {
//		head = new skiplistNode();
//	}
//	void insert(int val);
//	bool search(int val);
//	void remove(int val);
//	void show();
//};
//
//static unsigned int seed = NULL;
//bool SkipList::randomVal() {
//	if (!seed)
//		seed = (unsigned)time(NULL);
//	::srand(seed);
//	int ret = ::rand() % 2;
//	seed = ::rand();
//	if (ret == 0)
//		return true;
//	else
//		return false;
//}
//
//
//void SkipList::insert(int val) {
//	//����L1����룬�ٵ���Ĳ����
//	/* ���Ȳ���L1�� */
//	skiplistNode* cursor = head;
//	skiplistNode* newNode = nullptr;
//	while (cursor->down)
//		cursor=cursor->down;//����
//	skiplistNode* curhead = cursor;// ��ǰ������ͷ
//	while(cursor->right){
//		if (val < cursor->right->value && !newNode) {	
//			newNode = new skiplistNode(val);
//			newNode->right = cursor->right;
//			cursor->right = newNode;
//		}
//		cursor = cursor->right;
//  }
//	if (!newNode) {//��β��
//		newNode = new skiplistNode(val);
//		cursor->right = newNode;
//	}
//	/* �ϲ���� */
//	int cur_lvl = 1;// ��ǰ���ڲ�
//	while (randomVal()) {
//		cur_lvl++;
//		if (lvl_num < cur_lvl) {// ����һ��
//			lvl_num++;
//			skiplistNode* newhead = new skiplistNode();
//			newhead->down = head;
//			head->up = newhead;
//			head = newhead;
//		}
//		curhead = curhead->up;// ��ǰ����ͷ����һ��
//		cursor = curhead;
//		skiplistNode* skipNode = nullptr;
//		while (cursor->right) {
//			if (val < cursor->right->value&&!skipNode) {
//				skipNode = new skiplistNode(val);
//				skipNode->right = cursor->right;
//			}
//			cursor = cursor->right;
//		}
//		if (!skipNode) {
//			skipNode = new skiplistNode(val);
//			cursor->right = skipNode;
//		}//
//		while (newNode->up) {
//			newNode = newNode->up;
//		}
//		/* ������newNode��skipNode�����ڵ� */
//		skipNode->down = newNode;
//		newNode->up=skipNode;
//
//	}
//}
//
//bool SkipList::search(int val) {
//	skiplistNode* cursor = nullptr;
//	if (!head)
//		return false;
//	cursor = head;
//	while (cursor->down) {
//		while (cursor->right) {
//			if (val <= cursor->right->value)// ��λԪ��
//				break;
//			cursor = cursor->right;
//		}
//		cursor = cursor->down;
//	}
//	while (cursor->right) {// L1��ѭ����ʼ�����ѯ
//		if (val > cursor->right->value)
//			cursor = cursor->right;
//		else if (val == cursor->right->value)
//			return true;
//		else //if(val < cursor->right->value)
//			return false;
//	}
//	return false;
//}
//
//void SkipList::remove(int val) {
//	skiplistNode* cursor = head;
//	skiplistNode* prehead = nullptr;
//	while (true) {
//		skiplistNode* curhead = cursor;
//		if (prehead) {
//			curhead->up= nullptr;
//			prehead->down = nullptr;// ������¼���ָ��
//			delete prehead;
//			prehead = nullptr;// ָ���0
//			lvl_num--;
//			head = curhead;// ����ָ����ʼָ��
//		}
//		while (cursor&&cursor->right) {// �ڵ�ǰ���в�ѯval
//			if (val == cursor->right->value) {
//				skiplistNode* delptr = cursor->right;
//				cursor->right = cursor->right->right;
//				delete delptr;
//			}
//			cursor = cursor->right;		
//		}
//		if (curhead->right == nullptr)// �жϵ�ǰ���Ƿ񻹴�������Ԫ�أ������������ɾ�����в���������Ծ��ά
//			prehead = curhead;
//		if (curhead->down == nullptr)
//			break;
//		else
//			cursor = curhead->down;
//	}
//}
//
//void SkipList::show() {
//	skiplistNode* curhead = head;
//	skiplistNode* cursor = nullptr;
//	while (curhead->down) {
//		cursor = curhead;
//		cursor = cursor->right;
//		while(cursor->right){
//		cout << cursor->right->value<<" ";
//		cursor = cursor->right;
//		}
//		curhead = curhead->down;
//		cout << endl;
//	}
//	cursor = curhead;
//	cursor = cursor->right;
//	do 
//	{
//		cout << cursor->value << " ";
//		cursor = cursor->right;
//	} while (cursor->right);
//	cout << cursor->value << endl;
//}
//
//
//void main() {
//	int testArray[] = {1,2,3,4,5,6,7,8,9,22};
//	SkipList* s1 = new SkipList();
//	for (auto a : testArray) {
//		s1->insert(a);
//	}
//	s1->show();
//	s1->insert(16);
//	s1->show();
//	s1->remove(16);
//	s1->show();
//
//	system("pause");
//}