<<<<<<< HEAD
/* ¼òµ¥ÌøÔ¾±í£¬ËüÔÊĞí¼òµ¥µÄ²åÈëºÍÉ¾³ıÔªËØ£¬²¢Ìá¹©O(logn)µÄ²éÑ¯Ê±¼ä¸´ÔÓ¶È¡£ */
/*
SkipList_IntµÄĞÔÖÊ
(1) ÓÉºÜ¶à²ã½á¹¹×é³É£¬levelÊÇÍ¨¹ıÒ»¶¨µÄ¸ÅÂÊËæ»ú²úÉúµÄ£¬»ù±¾ÊÇ50%µÄ²úÉú¼¸ÂÊ¡£
(2) Ã¿Ò»²ã¶¼ÊÇÒ»¸öÓĞĞòµÄÁ´±í£¬Ä¬ÈÏÊÇÉıĞò£¬Ã¿Ò»²ãµÄÁ´±íÍ·×÷ÎªÌøµã¡£
(3) ×îµ×²ã(Level 1)µÄÁ´±í°üº¬ËùÓĞÔªËØ¡£
(4) Èç¹ûÒ»¸öÔªËØ³öÏÖÔÚLevel i µÄÁ´±íÖĞ£¬ÔòËüÔÚLevel i Ö®ÏÂµÄÁ´±íÒ²¶¼»á³öÏÖ¡£
(5) Ã¿¸ö½Úµã°üº¬ËÄ¸öÖ¸Õë£¬µ«ÓĞ¿ÉÄÜÎªnullptr¡£
(6) Ã¿Ò»²ãÁ´±íºáÏòÎªµ¥ÏòÁ¬½Ó£¬×İÏòÎªË«ÏòÁ¬½Ó¡£
*/
//http://www.cnblogs.com/learnhow/p/6749648.html

=======
///* ç®€å•è·³è·ƒè¡¨ï¼Œå®ƒå…è®¸ç®€å•çš„æ’å…¥å’Œåˆ é™¤å…ƒç´ ï¼Œå¹¶æä¾›O(logn)çš„æŸ¥è¯¢æ—¶é—´å¤æ‚åº¦ã€‚ */
///*
//SkipList_Intçš„æ€§è´¨
//(1) ç”±å¾ˆå¤šå±‚ç»“æ„ç»„æˆï¼Œlevelæ˜¯é€šè¿‡ä¸€å®šçš„æ¦‚ç‡éšæœºäº§ç”Ÿçš„ï¼ŒåŸºæœ¬æ˜¯50%çš„äº§ç”Ÿå‡ ç‡ã€‚
//(2) æ¯ä¸€å±‚éƒ½æ˜¯ä¸€ä¸ªæœ‰åºçš„é“¾è¡¨ï¼Œé»˜è®¤æ˜¯å‡åºï¼Œæ¯ä¸€å±‚çš„é“¾è¡¨å¤´ä½œä¸ºè·³ç‚¹ã€‚
//(3) æœ€åº•å±‚(Level 1)çš„é“¾è¡¨åŒ…å«æ‰€æœ‰å…ƒç´ ã€‚
//(4) å¦‚æœä¸€ä¸ªå…ƒç´ å‡ºç°åœ¨Level i çš„é“¾è¡¨ä¸­ï¼Œåˆ™å®ƒåœ¨Level i ä¹‹ä¸‹çš„é“¾è¡¨ä¹Ÿéƒ½ä¼šå‡ºç°ã€‚
//(5) æ¯ä¸ªèŠ‚ç‚¹åŒ…å«å››ä¸ªæŒ‡é’ˆï¼Œä½†æœ‰å¯èƒ½ä¸ºnullptrã€‚
//(6) æ¯ä¸€å±‚é“¾è¡¨æ¨ªå‘ä¸ºå•å‘è¿æ¥ï¼Œçºµå‘ä¸ºåŒå‘è¿æ¥ã€‚
//*/
////http://www.cnblogs.com/learnhow/p/6749648.html
>>>>>>> b147b255ae52da1e62da73144dc4fcf281c5fc5d
#include <iostream>
#include <cstdlib>//Ëæ»úÖÖ×Ó
#include <ctime>

using namespace std;

class SkipList {
	struct skiplistNode {
		skiplistNode(int val=INT_MIN):value(val),up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
		int value;
		struct skiplistNode* up;
		struct skiplistNode* down;
<<<<<<< HEAD
		struct skiplistNode* left;
		struct skiplistNode* right;
	};
	skiplistNode* head;// Í·½Úµã£¬²éÑ¯ÆğÊ¼µã
	int lvl_num;// µ±Ç°Á´±í²ãÊı
	bool randomVal();//Ëæ»úÅĞ¶Ï
=======
		struct skiplistNode* left;		struct skiplistNode* right;	};
	skiplistNode* head;// å¤´èŠ‚ç‚¹ï¼ŒæŸ¥è¯¢èµ·å§‹ç‚¹
	int lvl_num;// å½“å‰é“¾è¡¨å±‚æ•°
	bool randomVal();//éšæœºåˆ¤æ–­
>>>>>>> b147b255ae52da1e62da73144dc4fcf281c5fc5d

public:
	SkipList() :lvl_num(1) {
		head = new skiplistNode();
	}
	void insert(int val);
	bool search(int val);
	void remove(int val);
	void show();
};

static unsigned int seed = NULL;
bool SkipList::randomVal() {
	if (!seed)
		seed = (unsigned)time(NULL);
	::srand(seed);
	int ret = ::rand() % 2;
	seed = ::rand();
	if (ret == 0)
		return true;
	else
		return false;
}

<<<<<<< HEAD

void SkipList::insert(int val) {
	//ÏÖÔÚL1²ã²åÈë£¬ÔÙµ½±ğµÄ²ã²åÈë
	/* Ê×ÏÈ²éÕÒL1²ã */
	skiplistNode* cursor = head;
	skiplistNode* newNode = nullptr;
	while (cursor->down)
		cursor=cursor->down;//ÍùÏÂ
	skiplistNode* curhead = cursor;// µ±Ç°²ãÁ´±íÍ·
	while(cursor->right){
		if (val < cursor->right->value && !newNode) {	
			newNode = new skiplistNode(val);
			newNode->right = cursor->right;
			cursor->right = newNode;
		}
		cursor = cursor->right;
  }
	if (!newNode) {//×îÎ²²¿
		newNode = new skiplistNode(val);
		cursor->right = newNode;
	}
	/* ÉÏ²ã²Ù×÷ */
	int cur_lvl = 1;// µ±Ç°ËùÔÚ²ã
	while (randomVal()) {
		cur_lvl++;
		if (lvl_num < cur_lvl) {// Ôö¼ÓÒ»²ã
			lvl_num++;
			skiplistNode* newhead = new skiplistNode();
			newhead->down = head;
			head->up = newhead;
			head = newhead;
		}
		curhead = curhead->up;// µ±Ç°Á´±íÍ·ÉÏÒÆÒ»²ã
		cursor = curhead;
		skiplistNode* skipNode = nullptr;
		while (cursor->right) {
			if (val < cursor->right->value&&!skipNode) {
				skipNode = new skiplistNode(val);
				skipNode->right = cursor->right;
			}
			cursor = cursor->right;
		}
		if (!skipNode) {
			skipNode = new skiplistNode(val);
			cursor->right = skipNode;
		}//
		while (newNode->up) {
			newNode = newNode->up;
		}
		/* Á¬½ÓÉÏnewNodeÏÂskipNodeÁ½¸ö½Úµã */
		skipNode->down = newNode;
		newNode->up=skipNode;

	}
}

bool SkipList::search(int val) {
	skiplistNode* cursor = nullptr;
	if (!head)
		return false;
	cursor = head;
	while (cursor->down) {
		while (cursor->right) {
			if (val <= cursor->right->value)// ¶¨Î»ÔªËØ
				break;
			cursor = cursor->right;
		}
		cursor = cursor->down;
	}
	while (cursor->right) {// L1²ãÑ­»·¿ªÊ¼¾ßÌå²éÑ¯
		if (val > cursor->right->value)
			cursor = cursor->right;
		else if (val == cursor->right->value)
			return true;
		else //if(val < cursor->right->value)
			return false;
	}
	return false;
}

void SkipList::remove(int val) {
	skiplistNode* cursor = head;
	skiplistNode* prehead = nullptr;
	while (true) {
		skiplistNode* curhead = cursor;
		if (prehead) {
			curhead->up= nullptr;
			prehead->down = nullptr;// ½â³ıÉÏÏÂ¼¶µÄÖ¸Õë
			delete prehead;
			prehead = nullptr;// Ö¸Õë¹é0
			lvl_num--;
			head = curhead;// ÖØĞÂÖ¸¶¨ÆğÊ¼Ö¸Õë
		}
		while (cursor&&cursor->right) {// ÔÚµ±Ç°ĞĞÖĞ²éÑ¯val
			if (val == cursor->right->value) {
				skiplistNode* delptr = cursor->right;
				cursor->right = cursor->right->right;
				delete delptr;
			}
			cursor = cursor->right;		
		}
		if (curhead->right == nullptr)// ÅĞ¶Ïµ±Ç°ĞĞÊÇ·ñ»¹´æÔÚÆäËüÔªËØ£¬Èç¹û²»´æÔÚÔòÉ¾³ı¸ÃĞĞ²¢½«Õû¸öÌøÔ¾±í½µÎ¬
			prehead = curhead;
		if (curhead->down == nullptr)
			break;
		else
			cursor = curhead->down;
	}
}

void SkipList::show() {
	skiplistNode* curhead = head;
	skiplistNode* cursor = nullptr;
	while (curhead->down) {
		cursor = curhead;
		cursor = cursor->right;
		while(cursor->right){
		cout << cursor->right->value<<" ";
		cursor = cursor->right;
		}
		curhead = curhead->down;
		cout << endl;
	}
	cursor = curhead;
	cursor = cursor->right;
	do 
	{
		cout << cursor->value << " ";
		cursor = cursor->right;
	} while (cursor->right);
	cout << cursor->value << endl;
}


void main() {
	int testArray[] = {1,2,3,4,5,6,7,8,9,22};
	SkipList* s1 = new SkipList();
	for (auto a : testArray) {
		s1->insert(a);
	}
	s1->show();
	s1->insert(16);
	s1->show();
	s1->remove(16);
	s1->show();

	system("pause");
}
=======

void SkipList::insert(int val) {
	//ç°åœ¨L1å±‚æ’å…¥ï¼Œå†åˆ°åˆ«çš„å±‚æ’å…¥
	/* é¦–å…ˆæŸ¥æ‰¾L1å±‚ */
	skiplistNode* cursor = head;
	skiplistNode* newNode = nullptr;
	while (cursor->down)
		cursor=cursor->down;//å¾€ä¸‹
	skiplistNode* curhead = cursor;// å½“å‰å±‚é“¾è¡¨å¤´
	while(cursor->right){
		if (val < cursor->right->value && !newNode) {	
			newNode = new skiplistNode(val);
			newNode->right = cursor->right;
			cursor->right = newNode;		}
		cursor = cursor->right;
  }
	if (!newNode) {//æœ€å°¾éƒ¨
		newNode = new skiplistNode(val);
		cursor->right = newNode;
	}
	/* ä¸Šå±‚æ“ä½œ */
	int cur_lvl = 1;// å½“å‰æ‰€åœ¨å±‚
	while (randomVal()) {
		cur_lvl++;
		if (lvl_num < cur_lvl) {// å¢åŠ ä¸€å±‚
			lvl_num++;			skiplistNode* newhead = new skiplistNode();
			newhead->down = head;
			head->up = newhead;
			head = newhead;
		}
		curhead = curhead->up;// å½“å‰é“¾è¡¨å¤´ä¸Šç§»ä¸€å±‚
		cursor = curhead;
		skiplistNode* skipNode = nullptr;
		while (cursor->right) {
			if (val < cursor->right->value&&!skipNode) {
				skipNode = new skiplistNode(val);
				skipNode->right = cursor->right;
			}
			cursor = cursor->right;
		}
		if (!skipNode) {
			skipNode = new skiplistNode(val);
			cursor->right = skipNode;
		}//
		while (newNode->up) {
			newNode = newNode->up;
		}
		/* è¿æ¥ä¸ŠnewNodeä¸‹skipNodeä¸¤ä¸ªèŠ‚ç‚¹ */
		skipNode->down = newNode;
		newNode->up=skipNode;

	}
}

bool SkipList::search(int val) {
	skiplistNode* cursor = nullptr;
	if (!head)
		return false;
	cursor = head;
	while (cursor->down) {
		while (cursor->right) {
			if (val <= cursor->right->value)// å®šä½å…ƒç´ 
				break;
			cursor = cursor->right;
		}
		cursor = cursor->down;
	}
	while (cursor->right) {// L1å±‚å¾ªç¯å¼€å§‹å…·ä½“æŸ¥è¯¢
		if (val > cursor->right->value)
			cursor = cursor->right;
		else if (val == cursor->right->value)
			return true;
		else //if(val < cursor->right->value)
			return false;
	}
	return false;
}

void SkipList::remove(int val) {
	skiplistNode* cursor = head;
	skiplistNode* prehead = nullptr;
	while (true) {
		skiplistNode* curhead = cursor;
		if (prehead) {
			curhead->up= nullptr;
			prehead->down = nullptr;// è§£é™¤ä¸Šä¸‹çº§çš„æŒ‡é’ˆ
			delete prehead;
			prehead = nullptr;// æŒ‡é’ˆå½’0//			lvl_num--;
			head = curhead;// é‡æ–°æŒ‡å®šèµ·å§‹æŒ‡é’ˆ
		}
		while (cursor&&cursor->right) {// åœ¨å½“å‰è¡Œä¸­æŸ¥è¯¢val
			if (val == cursor->right->value) {
				skiplistNode* delptr = cursor->right;//				cursor->right = cursor->right->right;
				delete delptr;
			}
			cursor = cursor->right;		
		}
		if (curhead->right == nullptr)// åˆ¤æ–­å½“å‰è¡Œæ˜¯å¦è¿˜å­˜åœ¨å…¶å®ƒå…ƒç´ ï¼Œå¦‚æœä¸å­˜åœ¨åˆ™åˆ é™¤è¯¥è¡Œå¹¶å°†æ•´ä¸ªè·³è·ƒè¡¨é™ç»´
			prehead = curhead;
		if (curhead->down == nullptr)
			break;
		else
			cursor = curhead->down;
	}
}

void SkipList::show() {
	skiplistNode* curhead = head;
	skiplistNode* cursor = nullptr;
	while (curhead->down) {
		cursor = curhead;
		cursor = cursor->right;
		while(cursor->right){
		cout << cursor->right->value<<" ";
		cursor = cursor->right;
		}
		curhead = curhead->down;
		cout << endl;
	}
	cursor = curhead;
	cursor = cursor->right;
	do 
	{
		cout << cursor->value << " ";
		cursor = cursor->right;
	} while (cursor->right);
	cout << cursor->value << endl;
}


void main() {
	int testArray[] = {1,2,3,4,5,6,7,8,9,22};
	SkipList* s1 = new SkipList();
	for (auto a : testArray) {
		s1->insert(a);
	}
	s1->show();
	s1->insert(16);
	s1->show();
	s1->remove(16);
	s1->show();

	system("pause");
}
>>>>>>> b147b255ae52da1e62da73144dc4fcf281c5fc5d
