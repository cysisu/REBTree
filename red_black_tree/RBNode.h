#pragma once

template <class keyType, class valueType>
class RBNode {
public:
	RBNode() :key(0), color(BLACK), p(NULL), left(NULL), right(NULL)
	{
		leftNodeNumber = 0;
		rightNodeNumber = 0;
	}
	RBNode(keyType k, valueType v, E_COLOR c) :
		key(k), val(v), color(c), p(NULL), left(NULL), right(NULL)
	{ 
		leftNodeNumber = 0;
		rightNodeNumber = 0;
	}
	RBNode(keyType k, valueType v, E_COLOR c, RBNode * ptr1, RBNode * ptr2, RBNode * ptr3) :
		key(k), val(v), color(c), p(ptr1), left(ptr2), right(ptr3)
	{ 
		leftNodeNumber = 0;
		rightNodeNumber = 0;
	}

	int leftNodeNumber;
	int rightNodeNumber;
	valueType val;
	keyType key;
	E_COLOR color;
	RBNode * p;
	RBNode * left;
	RBNode * right;
};
