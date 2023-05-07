#include <iostream>
#include<stack>
#include<deque>
#include<string>
using namespace std;
//C++�����������
int pri(char c)//��ʶ��������ȼ�
{
    switch (c)
    {
    case '+':
    case '-':return 0; break;

    case '*':
    case '/':return 1; break;

    case '('://�������ò������ŵ����ȼ��ж�
    case ')':return -1; break;
    }
}

bool ispunc(char c)//�ж��Ƿ�Ϊ����
{
    if (c == '(' || c == ')') return true;
    else return false;
}

void check(char c, stack<char>& obj2, deque<char>& obj3)//��obj1�г��е��������ʱ���ж����ȼ�˳�򣬽����������obj3.
{
    if (obj2.empty())
    {
        obj2.push(c);
        return;
    }
    if (ispunc(c))//���������
    {
        if (c == '(') obj2.push(c);//�����������ֱ��ѹջ
        else {
            while (obj2.top() != '(')//����������ţ����ջobj2ֱ������������Ϊֹ��ƥ������
            {
                obj3.push_back(obj2.top());
                obj2.pop();
            }
            obj2.pop();//֪�������ǲ������obj3�ģ�Ҳ����˵���Ų����ں������еģ�
        }
    }
    else
    {
        if (pri(c) <= pri(obj2.top())) //����������ţ��ж�����ջ������������ȼ����ȼ�����ջ���� 
        {                                                 // ���ջ
            obj3.push_back(obj2.top());
            obj2.pop();
            check(c, obj2, obj3);
        }
        else obj2.push(c);
    }
}

void transf(deque<char>& obj1, stack<char>& obj2, deque<char>& obj3)
{
    while (!obj1.empty()) //����ջobj2������������ת��Ϊ��������obj3
    {
        char temp = obj1.front();
        obj1.pop_front();
        if (temp >= '0' && temp <= '9')
        {
            obj3.push_back(temp);
        }
        else
            check(temp, obj2, obj3);
    }
    while (!obj2.empty())
    {
        obj3.push_back(obj2.top());
        obj2.pop();
    }
}

void calcu(deque<char>& obj3)//�����沨�����ʽ��ֵ
{
    stack<int>temp;
    while (!obj3.empty())
    {
        char fc = obj3.front();
        obj3.pop_front();
        if (fc >= '0' && fc <= '9') temp.push(fc - '0');//����������ջ
        else  //�����������ȡ��ջ������Ԫ�أ��������������ƥ�䣬������и�����ô��ȡ��һ����
        {
            int one = temp.top();
            temp.pop();
            int two = temp.top();
            temp.pop();
            switch (fc) //�������Ľ��ѹ��ջ��
            {
            case '+': {temp.push(two + one); break; }//ע�������two��ǰ
            case '-': {temp.push(two - one); break; }
            case '*': {temp.push(two * one); break; }
            case '/': {temp.push(two / one); break; }
            }
        }
    }
    cout << "The result is:" << temp.top() << endl;//ȡ���ջ��ΨһԪ����Ϊ������
    temp.pop();
}

int main()
{
    stack<char>obj2;
    deque<char>obj1, obj3;
    string str;
    cin >> str;
    for (int i = 0; i < str.size(); ++i)
        obj1.push_back(str.at(i));
    transf(obj1, obj2, obj3);
    calcu(obj3);
    return 0;
}