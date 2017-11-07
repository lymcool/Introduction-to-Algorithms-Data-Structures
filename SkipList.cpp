///* 简单跳跃表，它允许简单的插入和删除元素，并提供O(logn)的查询时间复杂度。 */
///*
//SkipList_Int的性质
//(1) 由很多层结构组成，level是通过一定的概率随机产生的，基本是50%的产生几率。
//(2) 每一层都是一个有序的链表，默认是升序，每一层的链表头作为跳点。
//(3) 最底层(Level 1)的链表包含所有元素。
//(4) 如果一个元素出现在Level i 的链表中，则它在Level i 之下的链表也都会出现。
//(5) 每个节点包含四个指针，但有可能为nullptr。
//(6) 每一层链表横向为单向连接，纵向为双向连接。
//*/
////http://www.cnblogs.com/learnhow/p/6749648.html
//
//#include <iostream>
//#include <cstdlib>//随机种子
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
//	skiplistNode* head;// 头节点，查询起始点
//	int lvl_num;// 当前链表层数
//	bool randomVal();//随机判断
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
//	//现在L1层插入，再到别的层插入
//	/* 首先查找L1层 */
//	skiplistNode* cursor = head;
//	skiplistNode* newNode = nullptr;
//	while (cursor->down)
//		cursor=cursor->down;//往下
//	skiplistNode* curhead = cursor;// 当前层链表头
//	while(cursor->right){
//		if (val < cursor->right->value && !newNode) {	
//			newNode = new skiplistNode(val);
//			newNode->right = cursor->right;
//			cursor->right = newNode;
//		}
//		cursor = cursor->right;
//  }
//	if (!newNode) {//最尾部
//		newNode = new skiplistNode(val);
//		cursor->right = newNode;
//	}
//	/* 上层操作 */
//	int cur_lvl = 1;// 当前所在层
//	while (randomVal()) {
//		cur_lvl++;
//		if (lvl_num < cur_lvl) {// 增加一层
//			lvl_num++;
//			skiplistNode* newhead = new skiplistNode();
//			newhead->down = head;
//			head->up = newhead;
//			head = newhead;
//		}
//		curhead = curhead->up;// 当前链表头上移一层
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
//		/* 连接上newNode下skipNode两个节点 */
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
//			if (val <= cursor->right->value)// 定位元素
//				break;
//			cursor = cursor->right;
//		}
//		cursor = cursor->down;
//	}
//	while (cursor->right) {// L1层循环开始具体查询
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
//			prehead->down = nullptr;// 解除上下级的指针
//			delete prehead;
//			prehead = nullptr;// 指针归0
//			lvl_num--;
//			head = curhead;// 重新指定起始指针
//		}
//		while (cursor&&cursor->right) {// 在当前行中查询val
//			if (val == cursor->right->value) {
//				skiplistNode* delptr = cursor->right;
//				cursor->right = cursor->right->right;
//				delete delptr;
//			}
//			cursor = cursor->right;		
//		}
//		if (curhead->right == nullptr)// 判断当前行是否还存在其它元素，如果不存在则删除该行并将整个跳跃表降维
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