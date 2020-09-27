#include<iostream>
#include<vector>
using namespace std;

class Student     // ��� Ŭ����
{
public:
    int num;       // �ش����� ��ȣ
    int weight;    // ����� ���� ����
    bool top;       // �ֻ��� ������� ����
    bool check;    // ��尡 Ž���Ǿ����� ����
    vector<Student*> latters;   // �ڿ� ����� ����� �ּ� ����
    Student(int num)
    {
        this->num = num; weight = 0; top = true; check = false;
    }
};

void graph_reset(vector<Student>& students, vector<Student*>& current)  // �ش����� ���� Ʈ������ �ߺ��Ǵ� �κ��� ���� 
{
    if (current.size() >= 3) // �ߺ� ���Ŵ� �θ��� �θ��忡�� ���� ����
    {                        // current�� ���� ���� Ž���� ������ ����(�θ������ ����), current���հ� ����� �����
                           // ���� Ž����ġ�� ��尡 ��ġ�ϴ� ��� current�� ����� ��ġ�� ������ ����(����ȭ)�� �� �ִ�.
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

void graph_point(vector<Student>& students, vector<Student*>& current, int num)  // �׷����� ����� ��� Ž�� 
{
    current.push_back(&students[num - 1]); // ���� �湮�ϴ� ��带 current ���Ϳ� ����
    if (students[num - 1].check == false)  // �ѹ� ��尡 Ž���Ǿ����� ���� ������ �ȵ� �ٸ� �θ�κ��� �ٽ� Ž���Ǿ����� ��찡 ���ʿ�
    {
        students[num - 1].check = true;
        for (int i = 0; i < students[num - 1].latters.size(); i++)
        {
            students[num - 1].latters[i]->top = false;  // �θ�κ��� Ž���Ǿ����� �ֻ��� �θ��尡 �ƴ�
            graph_point(students, current, students[num - 1].latters[i]->num);
        }
    }
    graph_reset(students, current);   // ��忡�� ����ȭ �۾��� ����
    current.pop_back();   // �湮�� �������Ǹ� current���� pop
}

void search_seq(Student& start, int weight) // �θ𿡼� Ž�� �Ǵ� ������ �þ ���� weight 1�� ����
{
    if (start.weight < weight)   // �ٸ� �θ𿡼� Ž���Ǿ� weight���� �� ���� ��츦 �Ǵ��Ͽ�,  ���� weight ���� ������
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
    vector<Student> students;  // ������ ����
    vector<Student*> current;  // �׷��� Ž���� ���� �湮���� ����� �ּ� ����      
    vector<int> result;        // ���� ��� 
    for (int i = 1; i <= n; i++)
    {
        Student obj(i);
        students.push_back(obj);
    }
    for (int i = 0; i < m; i++)
    {
        int before = 0; int after = 0;
        cin >> before >> after;
        students[before - 1].latters.push_back(&students[after - 1]);   //�� ��忡 ������ �� �ڽ� ������ �ּҸ� �������� �߰�
    }

    for (int i = 0; i < students.size(); i++)  // �׷��� Ž��
    {
        if (students[i].check == false)     // Ž���� �ȵǾ��� ��忡������ �ٽ� ����
            graph_point(students, current, i + 1);
    }

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].top == true)       // weight ���� ����ϱ� ���� Ž��
            search_seq(students[i], 0);
    }

    int roof = students.size();            // weight������ ���� ����, ��º�
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




//���2 
//