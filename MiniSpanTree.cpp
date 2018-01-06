//http://blog.csdn.net/luoshixian099/article/details/51908175
//̰���㷨������С������
//Kruskal�㷨�����ӱ߷�������ʼ��С����������Ϊ0��ÿ����һ�ξ�ѡ��һ��������������С���۱ߣ����뵽��С�������ı߼����
//Prim�㷨:���ӵ㷨����ÿ�ε���ѡ�������С�ı߶�Ӧ�ĵ㣬���뵽��С�������С�

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 0xFFFFFFFF 
#define UINT unsigned int
#define vexCounts 6
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

struct Arc {//ԭʼͼ�ı���Ϣ
	UINT u;
	UINT v;
	UINT cost;
};

void AdjMatrix(UINT adjMat[][vexCounts]) {//�ڽӾ����ʾ��
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


struct node {//����
	UINT data;
	UINT lowestcost;
};

int Minimum(node* closedge) {//������С���۱߶�Ӧ�ĵ�

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

///////////////////////Prim�㷨:���ӵ㷨��
void MiniSpanTree_Prim(UINT adjMat[][vexCounts], UINT verData) {
	node  closedge[vexCounts];
	for (int i = 0;i < vexCounts;i++) {
		closedge[i].lowestcost= INFINITE;
	}
	closedge[verData].data = verData;
	closedge[verData].lowestcost = 0;//��ʼ��
	for (int i = 0;i < vexCounts;i++) {
		if (i != verData) {
			closedge[i].data = verData;
			closedge[i].lowestcost = adjMat[verData][i];
		}
	}
	for (int i = 1;i < vexCounts;i++) {//�ܱ���
		int k = Minimum(closedge);
		cout<<vextex[closedge[k].data]<< "--" << vextex[k] << endl;//���뵽��С������
		closedge[k].lowestcost = 0;
		for (int i = 0;i < vexCounts;i++) {//����v�ж�����С���۱���Ϣ
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
	if (u_index != v_index) {//u,v����һ�����ϣ��ϲ�������
		for (UINT i = 0;i < Tree[v_index].size();i++)
		{
			Tree[u_index].push_back(Tree[v_index][i]);
		}
		Tree[v_index].clear();
		return true;
	}
		return false;
}


////////////////////////////Kruskal�㷨�����ӱ߷���
void MiniSpanTree_Kruskal(UINT adjMat[][vexCounts]) {
	vector<Arc> vecArc;
	ReadArc(adjMat, vecArc);
	sort(vecArc.begin(), vecArc.end(),compareArc);
	vector<vector<UINT>> Tree(vexCounts);//6�ö�����
	for (int i = 0; i < vexCounts; i++)
	{
		Tree[i].push_back(i);  //��ʼ��6�ö���������Ϣ
	}
	for (int i = 0;i < vecArc.size();i++) {
		UINT u = vecArc[i].u;
		UINT v = vecArc[i].v;
		if (FindTree(u, v, Tree)){//���˱ߵ����������Ƿ���һ������
			cout << vextex[u] << "---" << vextex[v] << endl;//�Ѵ˱߼��뵽��С��������
		}
	}
}


int main() {
	UINT adjMat[vexCounts][vexCounts] = {0};
	AdjMatrix(adjMat);
	cout << "Prim :" << endl;
	MiniSpanTree_Prim(adjMat, 0); //Prim�㷨���Ӷ���0��ʼ.
	cout << "-------------" << endl << "Kruskal:" << endl;
	MiniSpanTree_Kruskal(adjMat);//Kruskal�㷨
	system("pause");
	return 0;
}