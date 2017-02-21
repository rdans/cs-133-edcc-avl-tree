//-----------------------------------------------------------------------------
//   File: bstinherited.h
//-----------------------------------------------------------------------------
#ifndef BSTINHERITED_H
#define BSTINHERITED__H

#include "bst.h"

//-------------------------------------------------------------------------------------------
//    Class:			avltree
//
//    File:             bstinherited.h
//
//    Title:            avltree Class
//
//    Description:		This file contains the class definition for avltree
//
//    Programmer:		Reinaldo Daniswara
//   
//    Date:             6/6/2016
// 
//    Version:          1.0
//  
//   Environment:		Intel COre i7
//						Software: MS Windows 10 for execution;
//						Compiles under Microsoft Visual Studio 2015
// 
//	  class avltree : public bst<T> 
//
//	  Methods:
//	
//		inline:	
//		avltree() : bst(){} -- constructor of the avltree
//		avltree(const avltree<T>& t) : bst(t){} -- copy constructor
//		~avltree()-- destructor
//
//		non-inline:
//		node<T>* rotateRight(node<T> *nodeN);
//		node<T>* rotateLeft(node<T> *nodeN);
//		node<T>* rotateRightLeft(node<T> *nodeN);
//		node<T>* rotateLeftRight(node<T> *nodeN);
//		node<T>* rebalance(node<T> *&nodeN);
//		int getHeightDifference(const node<T> *const nodeN)const;
//
//		T popnode(node<T>* &cur);
//		T poplow(node<T>* &cur);
//		T pophigh(node<T>* &cur);
//		T popfirst(const T& d, node<T>* np);
//		void insert(T d);
//    
//    History Log:
//                          6/6/2016  RD  completed version 1.0
// ----------------------------------------------------------------------------
using namespace std;

namespace RD_BST
{
	template<class T>

	class avltree : public bst<T> 
	{
	public:
		avltree() : bst(){}
		avltree(const avltree<T>& t) : bst(t){}

		node<T>* rotateRight(node<T> *nodeN);
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		int getHeightDifference(const node<T> *const nodeN)const;

		void insert(T d);
		T popnode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T pophigh(node<T>* &cur);
		T popfirst(const T& d, node<T>* &np);
		avltree<T>& operator+=(const avltree<T>& t);
		avltree<T>& operator+=(const T d) { insert(d, root); return *this; }
		void addtree(const node<T>* np);
		~avltree() { bst::~bst(); }

	private:
		void insert(T d, node<T>* &cur);
	};

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			getHeightDifference(const node<T> *const nodeN)const
	//
	//	  Description:		find the height difference of left and right root
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            none
	//    Called By:		rebalance()
	// 
	//	  Return:			difference's value
	//    Parameters:		const node<T> *const nodeN
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	int avltree<T>::getHeightDifference(const node<T> *const nodeN)const
	{
		int r = 0;
		int l = 0;
		int diff = 0;
		if (nodeN != nullptr)
		{
			if (nodeN->right != nullptr)
				r = nodeN->right->getHeight();
			if (nodeN->left != nullptr)
				l = nodeN->left->getHeight();
			diff = r - l;
		}
		return diff;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			node<T>* rotateRight(node<T> *nodeN)
	//
	//	  Description:		rotate the tree to the right
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            setHeight()
	//    Called By:		rebalance(), rotateRightLeft(), rotateLeftRight()
	// 
	//	  Return:			temp
	//    Parameters:		node<T> *nodeN
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	node<T>* avltree<T>::rotateRight(node<T> *nodeN)
	{
		node<T>* returnValue = nodeN;

		node<T>* temp;
		temp = nodeN->right;
		nodeN->right = temp->left;
		temp->left = nodeN;
		nodeN = temp;

		root->setHeight();
		returnValue = temp;
		
		return temp;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			node<T>* rotateLeft(node<T> *nodeN)
	//
	//	  Description:		rotate the tree to the left
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            setHeight()
	//    Called By:		rebalance(), rotateRightLeft(), rotateLeftRight()
	// 
	//	  Return:			temp
	//    Parameters:		node<T> *nodeN
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	node<T>* avltree<T>::rotateLeft(node<T> *nodeN)
	{
		node<T>* returnValue = nodeN;

		node<T>* temp;
		temp = nodeN->left;
		nodeN->left = temp->right;
		temp->right = nodeN;
		nodeN = temp;

		root->setHeight();
		returnValue = temp;

		return temp;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			node<T>* rotateRightLeft(node<T> *nodeN)
	//
	//	  Description:		rotate the tree to the right then to the left
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            setHeight(), rotateLeft()
	//    Called By:		rebalance()
	// 
	//	  Return:			return rotateRight(nodeN);
	//    Parameters:		node<T> *nodeN
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	node<T>* avltree<T>::rotateRightLeft(node<T> *nodeN)
	{
		node<T>* temp;
		temp = nodeN->right;
		nodeN->right = rotateLeft(temp);
		root->setHeight();
		return rotateRight(nodeN);
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			node<T>* rotateLeftRight(node<T> *nodeN)
	//
	//	  Description:		rotate the tree to the left then to the right
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            setHeight(), rotateRight()
	//    Called By:		rebalance()
	// 
	//	  Return:			return rotateLeft(nodeN);
	//    Parameters:		node<T> *nodeN
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	node<T>* avltree<T>::rotateLeftRight(node<T> *nodeN)
	{
		node<T>* temp;
		temp = nodeN->left;
		nodeN->left = rotateRight(temp);

		root->setHeight();
		return rotateLeft(nodeN);
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree
	//	  Method:			node<T>* rebalance(node<T> *&nodeN)
	//
	//	  Description:		balance the tree
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            getHeightDifference(), rotateRightLeft(), rotateRight()
	//						rotateLeft(), rotateLeftRight()
	//    Called By:		popfirst(), insert()
	// 
	//	  Return:			nodeN
	//    Parameters:		node<T> *nodeN
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	node<T>* avltree<T>::rebalance(node<T> *&nodeN)
	{
		int diff = getHeightDifference(nodeN);

		if (diff > 1)
		{
			if (getHeightDifference(nodeN->right) > 0)
				nodeN = rotateRight(nodeN);
			else
				nodeN = rotateRightLeft(nodeN);
		}
		if (diff < -1)
		{
			if (getHeightDifference(nodeN->left) > 0)
				nodeN = rotateLeftRight(nodeN);
			else
				nodeN = rotateLeft(nodeN);
		}
		return nodeN;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			T popnode(node<T>* &cur)
	//
	//	  Description:		pop the node
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            setHeight()
	//    Called By:		popfirst()
	// 
	//	  Throw:			invalid_argument
	//	  Return:			contents
	//    Parameters:		node<T>* &cur
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------
	template <class T>
	T avltree<T>::popnode(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		T contents = cur->value();
		if (cur->left == nullptr && cur->right == nullptr)
		{ // no children
			delete cur;
			cur = nullptr;
		}
		else if (cur->left == nullptr)
		{ // only right child
			node<T>* temp = cur->right;
			delete cur;
			cur = temp;
		}
		else if (cur->right == nullptr)
		{ // only left child
			node<T>* temp = cur->left;
			delete cur;
			cur = temp;
		}
		else
		{ // two children
			cur->setdata(bst<T>::pophigh(cur->left));
			// pops rightmost node of left child and
			// places that value into the current node
		}
		if (root != nullptr)
			root->setHeight();
		return contents;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			poplow(node<T>* &cur)
	//
	//	  Description:		pop the lowest element of the selected root
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            popfirst()
	//    Called By:		none
	//
	//	  Throw:			invalid_argument 
	//	  Return:			contents
	//    Parameters:		node<T>* &cur
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------
	template <class T>
	T avltree<T>::poplow(node<T>* &cur)
	{
		if (cur == nullptr)
			throw (invalid_argument("Pointer does not point to a node"));
			T contents = cur->value();
			if ((cur->left)==nullptr)
			{
				contents = cur->value();
				popfirst(contents, root);
			}
			else
			{
				poplow(cur->left);
				if (root != nullptr)
					root->setHeight();
			}
			return contents;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			T pophigh(node<T>* &cur)
	//
	//	  Description:		pop the highest element of the selected root
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            popfirst()
	//    Called By:		popnode()
	// 
	//	  Throw:			invalid_argument
	//	  Return:			contents
	//    Parameters:		node<T>* &cur
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------
	template <class T>
	T avltree<T>::pophigh(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		T contents = cur->value();
		if ((cur->right)==nullptr)
		{
			contents = cur->value();
			popfirst(contents, root);
		}
		else
		{
			pophigh(cur->right);
			if (root != nullptr)
				root->setHeight();
		}
		return contents;
		
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree  
	//	  Method:			T popfirst(const T& d, node<T>* np)
	//
	//	  Description:		delete and rebalance the element
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            popnode(), rebalance()
	//    Called By:		poplow(), pophigh()
	// 
	//	  Return:			contents
	//    Parameters:		const T& d, node<T>* np
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------
	template <class T>
	T avltree<T>::popfirst(const T& d, node<T>*& np)
	{
		T contents = d;
		if (np->value() == d)
		{
			contents = popnode(np);
		}
		else
		{
			if (d < np->value())
				popfirst(d, np->left);
			else
				popfirst(d, np->right);

				if (root != nullptr)
					root->setHeight();
			np = rebalance(np);
		}
		return contents;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			void insert(T d)
	//
	//	  Description:		insert an element
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            None
	//    Called By:		None
	// 
	//	  Return:			none
	//    Parameters:		T d
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------
	template <class T>
	void avltree<T>::insert(T d)
	{
		insert(d, root);
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			void insert(T d)
	//
	//	  Description:		insert an element to the tree
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            setHeight(), rebalance()
	//    Called By:		addtree()
	// 
	//	  Return:			none
	//    Parameters:		T d
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	void avltree<T>::insert(T d, node<T>* &cur)
	{
		if (cur == nullptr)
		{
			cur = new node<T>(d);
			if (isempty())
				root = cur;
		}
		else
		{
			if (d < cur->value())
				insert(d, cur->left);
			else
				insert(d, cur->right);
			if (root != nullptr)
				root->setHeight();
			cur = rebalance(cur);
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			avltree<T>::operator+=(const avltree<T>& t)
	//
	//	  Description:		overloaded +=
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            addtree()
	//    Called By:		main()
	// 
	//	  Return:			*this
	//    Parameters:		const avltree<T>& t
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	avltree<T>& avltree<T>::operator+=(const avltree<T>& t)
	{
		addtree(t.root);
		return *this;
	}

	//-----------------------------------------------------------------------------
	//    Class:			avltree 
	//	  Method:			avltree<T>::addtree(const node<T>* np)
	//
	//	  Description:		recursively adds in the contents of a second tree
	//	  Programmer:		Reinaldo Daniswara
	//    Calls:            insert()
	//    Called By:		none
	// 
	//	  Return:			none
	//    Parameters:		const node<T>* np
	//
	//    History Log:
	//                      6/6/2016  RD  completed version 1.0
	//-----------------------------------------------------------------------------

	template <class T>
	void avltree<T>::addtree(const node<T>* np)
	{
		if (np != nullptr)
		{
			addtree(np->left);
			addtree(np->right);
			insert(np->value(), root);
			rebalance(np);
		}
	}
}

#endif