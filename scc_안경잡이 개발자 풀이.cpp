#include <iostream>
#include <vector>
#include <stack>
#define MAX 10001 //총 노드의 개수
using namespace std;

int id, d[MAX];
bool finished[MAX];	//현재 특정한 노드의 DFS가 끝났는지 확인 1이 DFS를 진행하는가
vector<int> a[MAX];	//실질적으로 노드를 담는 
vector<vector<int> > SCC; //	한 그래프에서 여러개 나올수 있기에 2차원
stack <int> s;		//scc를 사용하기 위한 스택

//DFS는 총 정점의 갯수만큼 실행된다.

int dfs(int x) {
	d[x] = ++id;		//d 맨처음 부모로 선택된 값 
	s.push(x);			//스택에 자기 자신을 삽입한다.

	int parent = d[x];	//자신의 부모가 누구인지 -> 맨 처음은 자기 자신
	for (int i = 0; i < a[x].size(); i++) {
		int y = a[x][i];
		//방문하지 않은 노드
		if (d[y] == 0) parent = min(parent, dfs(y));		//방문하지 않은 이웃
		//방문은 했지만 처리 안된노드 (현재 dfs처리 되고 있는 상태)
		else if (!finished[y]) parent = min(parent, d[y]);
	}

	if(parent == d[x]) {			//부모노드가 자기 자신인 경우
		vector<int> scc;
		while (1) {
			int t = s.top();
			s.pop();
			scc.push_back(t);
			finished[t] = true;
			if (t == x) break;
		}
		SCC.push_back(scc);
	}		
	return parent;

}

int main(void) {
	int v = 11;
	a[1].push_back(2);
	a[2].push_back(3);
	a[3].push_back(1);
	a[4].push_back(2);
	a[4].push_back(5);
	a[5].push_back(7);
	a[6].push_back(5);
	a[7].push_back(6);
	a[8].push_back(5);
	a[8].push_back(9);
	a[9].push_back(10);
	a[10].push_back(11);
	a[11].push_back(3);
	a[11].push_back(8);

	for (int i = 1; i <= v; i++) {
		if (d[i] == 0) dfs(i);
	}
	for (int i = 0; i < SCC.size(); i++) {
		printf("%d번째 SCC : ", i + 1);
		for (int j = 0; j < SCC.size(); j++) {
			printf("%d ", SCC[i][j]);
		}
		printf("\n");
	}
	return 0;
}



