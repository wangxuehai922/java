#include <iostream>
#include<stack>
#include<deque>
#include<string>
using namespace std;
//C++混合四则运算
int pri(char c)//标识运算符优先级
{
    switch (c)
    {
    case '+':
    case '-':return 0; break;

    case '*':
    case '/':return 1; break;

    case '('://基本上用不到括号的优先级判断
    case ')':return -1; break;
    }
}

bool ispunc(char c)//判断是否为括号
{
    if (c == '(' || c == ')') return true;
    else return false;
}

void check(char c, stack<char>& obj2, deque<char>& obj3)//当obj1中出列的是运算符时，判断优先级顺序，将运算符入列obj3.
{
    if (obj2.empty())
    {
        obj2.push(c);
        return;
    }
    if (ispunc(c))//如果是括号
    {
        if (c == '(') obj2.push(c);//如果是左括号直接压栈
        else {
            while (obj2.top() != '(')//如果是右括号，则出栈obj2直到遇见左括号为止，匹配括号
            {
                obj3.push_back(obj2.top());
                obj2.pop();
            }
            obj2.pop();//知道括号是不入队列obj3的（也就是说括号不存在后序序列的）
        }
    }
    else
    {
        if (pri(c) <= pri(obj2.top())) //如果不是括号，判断它与栈顶运算符的优先级优先级高入栈，否 
        {                                                 // 则出栈
            obj3.push_back(obj2.top());
            obj2.pop();
            check(c, obj2, obj3);
        }
        else obj2.push(c);
    }
}

void transf(deque<char>& obj1, stack<char>& obj2, deque<char>& obj3)
{
    while (!obj1.empty()) //利用栈obj2来将中序序列转换为后序序列obj3
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

void calcu(deque<char>& obj3)//利用逆波兰表达式求值
{
    stack<int>temp;
    while (!obj3.empty())
    {
        char fc = obj3.front();
        obj3.pop_front();
        if (fc >= '0' && fc <= '9') temp.push(fc - '0');//遇见数字入栈
        else  //遇见运算符，取出栈顶两个元素（与运算符操作数匹配，如果带有负号那么则取出一个）
        {
            int one = temp.top();
            temp.pop();
            int two = temp.top();
            temp.pop();
            switch (fc) //将运算后的结果压入栈中
            {
            case '+': {temp.push(two + one); break; }//注意操作数two在前
            case '-': {temp.push(two - one); break; }
            case '*': {temp.push(two * one); break; }
            case '/': {temp.push(two / one); break; }
            }
        }
    }
    cout << "The result is:" << temp.top() << endl;//取最后栈中唯一元素作为运算结果
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