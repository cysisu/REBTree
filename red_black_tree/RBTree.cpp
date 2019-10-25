#include "stdafx.h"
#include"RBTree.h"
#include"RBNode.h"
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

template <class keyType, class valueType>
RBTree<keyType, valueType>::RBTree() {
	treeSize = 0;
	NIL = new RBNode<keyType, valueType>(0, "", BLACK);
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->p = NIL;
	root = NIL;
}

template <class keyType, class valueType>
RBTree<keyType, valueType>::RBTree(keyType K[], valueType V[], int s)
{
	treeSize = 0;
	NIL = new RBNode<keyType, valueType>(0, "", BLACK);
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->p = NIL;

	root = NIL;

	for (int i = 0; i < s; i++)
	{
		InsertKey(K[i], V[i]);
	}
}

template <class keyType, class valueType>
RBTree<keyType, valueType>::~RBTree() {
	Clear();
	delete NIL;
}

template <class keyType, class valueType>
RBNode<keyType, valueType> * RBTree<keyType, valueType>::FindKey(keyType key) {
	RBNode<keyType, valueType> * pNode = root;

	while (pNode != NIL) {
		if (pNode->key < key) {
			pNode = pNode->right;
		}
		else if (pNode->key > key) {
			pNode = pNode->left;
		}
		else {
			return pNode;
		}
	}

	return NULL;
}

template <class keyType, class valueType>
RBNode<keyType, valueType> * RBTree<keyType, valueType>::FindInsertPos(keyType key) {
	RBNode<keyType, valueType> * pNode = root;
	while (pNode != NIL) {
		if (pNode->key < key) {
			if (pNode->right == NIL) {
				return pNode;
			}
			else {
				pNode = pNode->right;
			}
		}
		else if (pNode->key > key) {
			if (pNode->left == NIL) {
				return pNode;
			}
			else {
				pNode = pNode->left;
			}
		}
		else {
			return NIL;
		}
	}

	return NIL;
}

template <class keyType, class valueType>
RBNode<keyType, valueType> * RBTree<keyType, valueType>::FindDeletePos(keyType key) {
	RBNode<keyType, valueType> * pNode = root;

	while (pNode != NIL) {
		if (pNode->key < key) {
			pNode = pNode->right;
		}
		else if (pNode->key > key) {
			pNode = pNode->left;
		}
		else {
			return pNode;
		}
	}

	return NIL;
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::InsertKey(keyType key, valueType v) {

	RBNode<keyType, valueType> * pNode = FindInsertPos(key);
	if (root != NIL && pNode == NIL) {
		return;
	}
	RBNode<keyType, valueType> * new_node = new RBNode<keyType, valueType>(key, v, RED, NIL, NIL, NIL);
	treeSize += 1;
	if (pNode == NIL) {
		root = new_node;
	}
	else if (pNode->key < key) {
		pNode->right = new_node;
		new_node->p = pNode;
	}
	else {
		pNode->left = new_node;
		new_node->p = pNode;
	}

	InsertAdjust(new_node);
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::InsertAdjust(RBNode<keyType, valueType> * cur_node) {
	if (root == cur_node) {
		cur_node->color = BLACK;
		NIL->left = cur_node;
		cur_node->p = NIL;
	}
	else if (cur_node->p->color == RED) {
		RBNode<keyType, valueType> * grandpa = cur_node->p->p;
		RBNode<keyType, valueType> * pa = cur_node->p;
		RBNode<keyType, valueType> * uncle = NIL;
		if (grandpa->left == cur_node->p) {
			uncle = grandpa->right;
			if (uncle->color == RED) {
				pa->color = BLACK;
				uncle->color = BLACK;
				grandpa->color = RED;
				InsertAdjust(grandpa);
			}
			else {
				if (pa->right == cur_node) {
					left_rotate(pa);
					pa = cur_node;
				}
				right_rotate(grandpa);
				grandpa->color = RED;
				pa->color = BLACK;
			}
		}
		else {
			uncle = grandpa->left;
			if (uncle->color == RED) {
				pa->color = BLACK;
				uncle->color = BLACK;
				grandpa->color = RED;
				InsertAdjust(grandpa);
			}
			else {
				if (pa->left == cur_node) {
					right_rotate(pa);
					pa = cur_node;
				}
				left_rotate(grandpa);
				grandpa->color = RED;
				pa->color = BLACK;
			}
		}
	}
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::left_rotate(RBNode<keyType, valueType> * x) { // y 是 x 的右孩子
	RBNode<keyType, valueType> * y = x->right;
	RBNode<keyType, valueType> * xp = x->p;
	RBNode<keyType, valueType> * yleft = y->left;

	y->p = xp;
	if (xp->left == x) {
		xp->left = y;
	}
	else {
		xp->right = y;
	}

	y->left = x;
	x->p = y;

	x->right = yleft;
	yleft->p = x;

	if (root == x) {
		root = y;
	}
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::right_rotate(RBNode<keyType, valueType> * x) { // y是 x的左孩子
	RBNode<keyType, valueType> * y = x->left;
	RBNode<keyType, valueType> * xp = x->p;
	RBNode<keyType, valueType> * yright = y->right;

	y->p = xp;
	if (xp->left == x) {
		xp->left = y;
	}
	else {
		xp->right = y;
	}

	y->right = x;
	x->p = y;
	x->left = yright;
	yright->p = x;

	if (root == x) {
		root = y;
	}
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::Output() {
	Output(root);
}

//中序遍历
template <class keyType, class valueType>
void RBTree<keyType, valueType>::Output(RBNode<keyType, valueType> * pNode) {
	if (pNode == NIL) return;

	Output(pNode->left);
	cout << pNode->key << " " << pNode->val << "\t";
	Output(pNode->right);
}



template <class keyType, class valueType>
void RBTree<keyType, valueType>::Clear(RBNode<keyType, valueType> * pNode) {
	if (pNode == NIL) {
		return;
	}
	Clear(pNode->left);
	Clear(pNode->right);
	delete pNode;
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::Clear() {
	Clear(root);
	root = NIL;
}

template <class keyType, class valueType>
RBNode<keyType, valueType> * RBTree<keyType, valueType>::FindSuccessor(RBNode<keyType, valueType> * z) {  // assume z have right tree
	assert(z->right != NIL);

	RBNode<keyType, valueType> * p = z->right;
	while (p->left != NIL) {
		p = p->left;
	}
	return p;
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::DeleteKey(keyType key) {
	RBNode<keyType, valueType> * z = FindDeletePos(key);
	if (z == NIL) return;
	treeSize -= 1;
	RBNode<keyType, valueType> * y = NIL;
	if (z->left == NIL || z->right == NIL) {
		y = z;
	}
	else {
		y = FindSuccessor(z);
		swap(y->key, z->key);
	}

	RBNode<keyType, valueType> * yp = y->p;
	RBNode<keyType, valueType> * ychild = y->left != NIL ? y->left : y->right;

	ychild->p = yp;
	if (yp->left == y) {
		yp->left = ychild;
	}
	else {
		yp->right = ychild;
	}

	if (yp == NIL) {
		root = ychild;
	}

	if (y->color == BLACK)
		DeleteAdjust(ychild);

	delete y;
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::DeleteAdjust(RBNode<keyType, valueType> *cur_node) {
	if (cur_node == root
		|| cur_node->color == RED) {
		cur_node->color = BLACK;
	}
	else {
		RBNode<keyType, valueType> * x = cur_node;
		RBNode<keyType, valueType> * y = x->p;
		if (y->left == x) {
			RBNode<keyType, valueType> * z = y->right;
			RBNode<keyType, valueType> * zleft = z->left;
			RBNode<keyType, valueType> * zright = z->right;

			if (z->color == RED) {
				left_rotate(y);
				y->color = RED;
				z->color = BLACK;
				DeleteAdjust(x);
			}
			else if (zleft->color == BLACK && zright->color == BLACK) {
				z->color = RED;
				DeleteAdjust(y);
			}
			else if (zleft->color == RED && zright->color == BLACK) {
				right_rotate(z);
				zleft->color = BLACK;
				z->color = RED;
				DeleteAdjust(x);
			}
			else {
				left_rotate(y);
				y->color = BLACK;
				z->color = RED;
				zright->color = BLACK;
			}

		}
		else {
			RBNode<keyType, valueType> * z = y->left;
			RBNode<keyType, valueType> * zleft = z->left;
			RBNode<keyType, valueType> * zright = z->right;

			if (z->color == RED) {
				right_rotate(y);
				y->color = RED;
				z->color = BLACK;
				DeleteAdjust(x);
			}
			else if (zleft->color == BLACK && zright->color == BLACK) {
				z->color = RED;
				DeleteAdjust(y);
			}
			else if (zleft->color == BLACK && zright->color == RED) {
				left_rotate(z);
				zright->color = BLACK;
				z->color = RED;
				DeleteAdjust(x);
			}
			else {
				right_rotate(y);
				y->color = BLACK;
				z->color = RED;
				zleft->color = BLACK;
			}
		}
	}
}

template <class keyType, class valueType>
valueType * RBTree<keyType, valueType>::search(keyType k)
{
	RBNode < keyType, valueType > *node = FindKey(k);
	if (node == NULL)
		return NULL;
	valueType * val = &node->val;
	return val;
}

template <class keyType, class valueType>
int RBTree<keyType, valueType>::size()
{
	return treeSize;
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::preorder(RBNode<keyType, valueType> * pNode)
{
	if (pNode == NIL) return;
	cout << pNode->key << " ";
	preorder(pNode->left);
	preorder(pNode->right);
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::preorder()
{
	preorder(root);
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::inorder(RBNode<keyType, valueType> * pNode)
{
	if (pNode == NIL) return;

	inorder(pNode->left);
	cout << pNode->key << " ";
	inorder(pNode->right);
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::inorder()
{
	inorder(root);
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::postorder(RBNode<keyType, valueType> * pNode)
{
	if (pNode == NIL) return;

	postorder(pNode->left);

	postorder(pNode->right);
	cout << pNode->key << " ";
}

template <class keyType, class valueType>
void RBTree<keyType, valueType>::postorder()
{
	postorder(root);
}

template <class keyType, class valueType>
int RBTree<keyType, valueType>::rank(keyType k)
{
	RBNode<keyType, valueType> *node = FindKey(k);
	if (node == NULL)
	{
		return 0;
	}
	int rankNumber = 0;
	while (node != NIL)
	{
		if (node->right->color == BLACK)
			rankNumber++;
		node = node->right;
	}
	return rankNumber;
}

