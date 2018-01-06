//http://blog.csdn.net/luoshixian099/article/details/51908175
//贪婪算法——最小生成树
//Kruskal算法：“加边法”，初始最小生成树边数为0，每迭代一次就选择一条满足条件的最小代价边，加入到最小生成树的边集合里。
//Prim算法:“加点法”，每次迭代选择代价最小的边对应的点，加入到最小生成树中。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 0xFFFFFFFF 
#define UINT unsigned int
#define vexCounts 6
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

struct Arc {//原始图的边信息
	UINT u;
	UINT v;
	UINT cost;
};

void AdjMatrix(UINT adjMat[][vexCounts]) {//邻接矩阵表示法
	for (int i = 0;i < vexCounts;i++) {
		for (int j = 0;j < vexCounts;j++) {
			adjMat[i][j] = INFINITE;
		}
	}
	adjMat[0][1] = 6; adjMat[0][2] = 1; adjMat[0][3] = 5;
	adjMat[1][0] = 6; adjMat[1][2] = 5; adjMat[1][4] = 3;
	adjMat[2][0] = 1; adjMat[2][1] = 5; adjMat[2][3] = 5; adjMat[2][4] = 6; adjMat[2][5] = 4;
	adjMat[3][0] = 5; adjMat[3][2] = 5; adjMat[3][5] = 2;
	adjMat[4][1] = 3; adjMat[4][2] = 6; adjMat[4][5] = 6;
	adjMat[5][2] = 4; adjMat[5][3] = 2; adjMat[5][4] = 6;

}


struct node {//辅助
	UINT data;
	UINT lowestcost;
};

int Minimum(node* closedge) {//返回最小代价边对应的点

	UINT min = INFINITE;
	int index = -1;
	for (int i = 0;i < vexCounts;i++) {
		if (closedge[i].lowestcost < min && closedge[i].lowestcost != 0) {
			min = closedge[i].lowestcost;
			index = i;
		}
	}
	return index;
}

///////////////////////Prim算法:“加点法”
void MiniSpanTree_Prim(UINT adjMat[][vexCounts], UINT verData) {
	node  closedge[vexCounts];
	for (int i = 0;i < vexCounts;i++) {
		closedge[i].lowestcost= INFINITE;
	}
	closedge[verData].data = verData;
	closedge[verData].lowestcost = 0;//起始点
	for (int i = 0;i < vexCounts;i++) {
		if (i != verData) {
			closedge[i].data = verData;
			closedge[i].lowestcost = adjMat[verData][i];
		}
	}
	for (int i = 1;i < vexCounts;i++) {//总边数
		int k = Minimum(closedge);
		cout<<vextex[closedge[k].data]<< "--" << vextex[k] << endl;//加入到最小生成树
		closedge[k].lowestcost = 0;
		for (int i = 0;i < vexCounts;i++) {//更新v中顶点最小代价边信息
			if (adjMat[k][i] < closedge[i].lowestcost) {
				closedge[i].data = k;
				closedge[i].lowestcost = adjMat[k][i];
			}
        }
	}
}

void ReadArc(UINT adjMat[][vexCounts], vector<Arc> &vecArc) {
	for (int i = 0;i < vexCounts;i++) {
		for (int j = 0;j < i;j++) {
			if (adjMat[i][j] != INFINITE) {
				Arc temp;
				temp.cost = adjMat[i][j];
				temp.u = i;
				temp.v = j;
				vecArc.push_back(temp);
			}
		}
	}
}
bool compareArc(Arc p1, Arc p2){
	return p1.cost < p2.cost;
}
bool FindTree(UINT u, UINT v, vector<vector<UINT> > &Tree) {
	UINT u_index= INFINITE;
	UINT v_index = INFINITE;
	for (UINT i = 0;i < Tree.size();i++) {
		if (find(Tree[i].begin(), Tree[i].end(),u) != Tree[i].end()) 
			u_index = i;
		if (find(Tree[i].begin(), Tree[i].end(), v) != Tree[i].end())
			v_index = i;
	}
	if (u_index != v_index) {//u,v不在一颗树上，合并两颗树
		for (UINT i = 0;i < Tree[v_index].size();i++)
		{
			Tree[u_index].push_back(Tree[v_index][i]);
		}
		Tree[v_index].clear();
		return true;
	}
		return false;
}


////////////////////////////Kruskal算法：“加边法”
void MiniSpanTree_Kruskal(UINT adjMat[][vexCounts]) {
	vector<Arc> vecArc;
	ReadArc(adjMat, vecArc);
	sort(vecArc.begin(), vecArc.end(),compareArc);
	vector<vector<UINT>> Tree(vexCounts);//6棵独立树
	for (int i = 0; i < vexCounts; i++)
	{
		Tree[i].push_back(i);  //初始化6棵独立树的信息
	}
	for (int i = 0;i < vecArc.size();i++) {
		UINT u = vecArc[i].u;
		UINT v = vecArc[i].v;
		if (FindTree(u, v, Tree)){//检查此边的两个顶点是否在一颗树内
			cout << vextex[u] << "---" << vextex[v] << endl;//把此边加入到最小生成树中
		}
	}
}


int main() {
	UINT adjMat[vexCounts][vexCounts] = {0};
	AdjMatrix(adjMat);
	cout << "Prim :" << endl;
	MiniSpanTree_Prim(adjMat, 0); //Prim算法，从顶点0开始.
	cout << "-------------" << endl << "Kruskal:" << endl;
	MiniSpanTree_Kruskal(adjMat);//Kruskal算法
	system("pause");
	return 0;
}