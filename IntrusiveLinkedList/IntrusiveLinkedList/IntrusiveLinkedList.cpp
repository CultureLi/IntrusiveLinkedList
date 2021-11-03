
#include <iostream>
#include "IntrusiveList.h"

using namespace std;

//#define offsetof(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))

class MyTest 
{
public:

    MyTest(int i) { data = i; }
    list_head lst;
    int data;
};


class Info
{
public:
    char c;
    int id;
    int data;
    char s[20];
};


int main()
{

	cout << offsetof(Info, c) << endl;
	cout << offsetof(Info, id) << endl;
	cout << offsetof(Info, data) << endl;
	cout << offsetof(Info, s) << endl;


    LIST_HEAD(startNode);

    // 1,2,3,4
    for (int i = 1; i < 5; ++i)
    {
		MyTest *t = new MyTest(i);
        list_add_tail(&t->lst, &startNode);
    }

	MyTest* pos;
    // del 1,3 remain 2,4
	list_for_each_entry(pos, &startNode, lst)
	{
        if (pos->data % 2)
        {
            __list_del_entry(&pos->lst);
       
        }
	}
    // replace last 4 with new node 5, result 2,5
    MyTest* newNode = new MyTest(5);
    MyTest *lastNode = list_last_entry(&startNode, MyTest, lst);
    list_replace(&lastNode->lst, &newNode->lst);

	list_for_each_entry(pos, &startNode, lst)
	{
		cout << pos->data << endl;
	}

    return 0;
}

