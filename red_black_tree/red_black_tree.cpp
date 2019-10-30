// red_black_tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<string>
#include<cstringt.h>
#include<cstring>


#include <assert.h>
#include <stdio.h>
#include<iostream>
using namespace std;

enum E_COLOR {
	BLACK,
	RED
};
#include"RBNode.h"
#include"RBTree.h"




int main()
{
	//RBTree<int,string> tree;
	////keyType Num[9] = { 'A', 'L', 'G', 'O', 'R', 'I', 'T', 'H', 'M' };
	//cout << "please select what you want to do:" << endl;
	//while (true)
	//{
	//	int operate = 0;
	//	cout << "\n1.insert, 2.delete, 3.find" << endl;
	//	cout << "please input：";
	//	cin >> operate;
	//	if (operate == 1)
	//	{
	//		int key;
	//		cout << "please input the key you want to insert:";
	//		cin >> key;
	//		tree.insert(key,"cy");
	//		tree.Output();
	//	}
	//	else if (operate == 2)
	//	{
	//		int key;
	//		cout << "please input the key you want to delete:";
	//		cin >> key;
	//		tree.remove(key);
	//		tree.Output();
	//	}
	//	else if (operate == 3)
	//	{
	//		int key;
	//		cout << "please in put the key you want to find:";
	//		cin >> key;
	//		RBNode<int,string>* node = tree.FindKey(key);
	//		if (node == NULL)
	//		{
	//			cout << key << "不在红黑树中" << endl;
	//		}
	//		else
	//		{
	//			cout << key << "在红黑树中" << endl;
	//		}

	//	}
	//	else
	//	{
	//		cout << "pleease input the correct operate" << endl;
	//	}

	//}

	int K[5] = { 10,20,30,40,34};
	string V[5] = { "cy","alber","Alin","Tom","Mei" };
	RBTree<int, string> tree2(K, V, 5);
	RBTree<int, string> tree1 = tree2;
	//RBTree<int, string> tree1(tree2);
	tree1.Output();
	cout << endl;
	string *valuePointer = tree1.search(20);
	cout << "搜索的值为:"<< *valuePointer << endl;
	cout << "tree size:"<<tree1.size() << endl;
	cout << "\n前序遍历:" << endl;
	tree1.preorder();
	cout << "\n中序遍历:" << endl;
	tree1.inorder();
	cout << "\n后序遍历:" << endl;
	tree1.postorder();
	printf("\n20的rank：%d\n", tree1.rank(20));
	
	/*while (true) {
		int pos = 0;
		printf("请输入select的位置:");
		cin >> pos;
		cout << "select key:" << tree1.select(pos) << endl;
	}*/
	//while (true) {
	//	cout << "请输入需要删除的key:";
	//	int key;
	//	cin >> key;
	//	tree1.remove(key);
	//	int pos = 0;
	//	printf("请输入select的位置:");
	//	cin >> pos;
	//	cout << "select key:" << tree1.select(pos) << endl;
	//}
	

	return 0;
}

