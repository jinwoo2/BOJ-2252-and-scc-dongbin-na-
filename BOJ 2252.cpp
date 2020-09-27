#include<iostream>
#include<vector>
using namespace std;

class Student     // 노드 클래스
{
public:
    int num;       // 해당노드의 번호
    int weight;    // 노드의 위상 순위
    bool top;       // 최상위 노드인지 여부
    bool check;    // 노드가 탐색되어진지 여부
    vector<Student*> latters;   // 뒤에 연결된 노드의 주소 집합
    Student(int num)
    {
        this->num = num; weight = 0; top = true; check = false;
    }
};

void graph_reset(vector<Student>& students, vector<Student*>& current)  // 해당노드의 상위 트리에서 중복되는 부분을 제거 
{
    if (current.size() >= 3) // 중복 제거는 부모의 부모노드에서 부터 제거
    {                        // current는 현재 까지 탐색된 노드들의 집합(부모노드들의 집합), current집합과 연결된 노드중
                           // 현재 탐색위치의 노드가 일치하는 경우 current에 연결된 일치한 노드들은 삭제(간략화)할 수 있다.
        for (int i = 0; i < current.size() - 2; i++)
        {
            for (int j = 0; j < current[i]->latters.size(); j++)
            {
                if (current[i]->latters[j] == current[current.size() - 1])
                    current[i]->latters.erase(current[i]->latters.begin() + j);
            }
        }
    }
}

void graph_point(vector<Student>& students, vector<Student*>& current, int num)  // 그래프에 연결된 노드 탐색 
{
    current.push_back(&students[num - 1]); // 현재 방문하는 노드를 current 벡터에 저장
    if (students[num - 1].check == false)  // 한번 노드가 탐색되어지면 이후 연결이 안된 다른 부모로부터 다시 탐색되어지는 경우가 불필요
    {
        students[num - 1].check = true;
        for (int i = 0; i < students[num - 1].latters.size(); i++)
        {
            students[num - 1].latters[i]->top = false;  // 부모로부터 탐색되어지면 최상위 부모노드가 아님
            graph_point(students, current, students[num - 1].latters[i]->num);
        }
    }
    graph_reset(students, current);   // 노드에서 간략화 작업을 진행
    current.pop_back();   // 방문이 마무리되면 current에서 pop
}

void search_seq(Student& start, int weight) // 부모에서 탐색 되는 연결이 늘어날 수록 weight 1씩 증가
{
    if (start.weight < weight)   // 다른 부모에서 탐색되어 weight값이 더 높은 경우를 판단하여,  높은 weight 값을 따른다
        start.weight = weight;
    weight++;
    for (int i = 0; i < start.latters.size(); i++)
    {
        search_seq(*start.latters[i], weight);
    }
}

int main()
{
    int n; int m;
    cin >> n >> m;
    vector<Student> students;  // 노드들의 집합
    vector<Student*> current;  // 그래프 탐색시 현재 방문중인 노드의 주소 집합      
    vector<int> result;        // 최종 출력 
    for (int i = 1; i <= n; i++)
    {
        Student obj(i);
        students.push_back(obj);
    }
    for (int i = 0; i < m; i++)
    {
        int before = 0; int after = 0;
        cin >> before >> after;
        students[before - 1].latters.push_back(&students[after - 1]);   //각 노드에 연결이 될 자식 노드들의 주소를 동적으로 추가
    }

    for (int i = 0; i < students.size(); i++)  // 그래프 탐색
    {
        if (students[i].check == false)     // 탐색이 안되어진 노드에서부터 다시 시작
            graph_point(students, current, i + 1);
    }

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].top == true)       // weight 값을 계산하기 위한 탐색
            search_seq(students[i], 0);
    }

    int roof = students.size();            // weight값으로 부터 정렬, 출력부
    for (int i = 0; i < roof; i++)
    {
        int small = 0;
        for (int j = 0; j < students.size(); j++)
        {
            if (students[small].weight > students[j].weight)
                small = j;
        }
        result.push_back(students[small].num);
        students.erase(students.begin() + small);
    }

    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;

    return 0;
}




//방법2 
//