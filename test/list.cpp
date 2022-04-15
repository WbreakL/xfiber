#include <iostream>
#include <list>
#include <vector>
using namespace std;
int main(void)
{
    list<int> lst;
    list<int>::iterator it; //定义一个迭代器指针
    for (int i = 1; i <= 5; ++i)
    {
        lst.push_back(i);
    }
    //运行效果是：1 2 3 4 5
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    //将列表开始位置赋给迭代器指针
    it = lst.begin();
    //指针值加1，此时指向列表中的第2个元素
    ++it;
    //用第1个版本的insert函数进行插入，在列表的元素2之前插入新元素9，运行效果是：1 9 2 3 4 5
    lst.insert(it, 9); // 1 9 2 3 4 5
    cout<<*it<<endl;
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    //此时it指针没有改变，仍然指向最初列表的第二个元素，注意是最开始的列表，即：仍然指向元素2
    //用第2个版本的insert函数进行插入，在元素2之前插入两个新元素29，运行效果是：1 9 29 29 2 3 4 5
    lst.insert(it, 2, 29);
    cout << *it << endl;
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    //指针值减1，此时指向列表中元素2前面的那个元素，即：元素29（从左往右第二个29）
    --it;
    vector<int> v(2, 39);
    //用第3个版本的insert函数进行插入，在元素29之前插入数组区间（两个39），运行效果是：1 9 29 39 39 29 2 3 4 5
    lst.insert(it, v.begin(), v.end());
    cout << *it << endl;
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    cout << "\n";
    return 0;
}