// ITP 365 Fall 2018 
// HW6 ¨C Doubly Linked List and Movie Player
// Name: Yuzhi Lu
// Email: yuzhilu@usc.edu 
// Platform: Windows
//
// ITPDoubleList.hpp
// Defines and implements the ITPDoubleList collection
//

#pragma once
#include "error.h"
#include <ostream>
#include <sstream>
#include "leaker.h"

template <typename T>
class ITPDoubleList
{
private:

	// Node only used internally to list
	struct Node
	{
		// Data in this node
		T mData;
		// Link to previous node
		Node* mPrev;
		// Link to next node
		Node* mNext;
	};

	// Pointer to the head node
	Node* mHead;
	// Pointer to the tail node
	Node* mTail;
	// Number of nodes currently in the list
	unsigned mSize;

public:
	// Iterator helper class...
	class Iterator
	{
	private:
		Node* mCurr;
	public:
		// Needed for List access
		friend class ITPDoubleList;
		// Constructors
		Iterator()
		{
			mCurr = nullptr;
		}

		Iterator(Node* inCurr)
		{
			mCurr = inCurr;
		}

		Iterator(const Iterator& src)
		{
			mCurr = src.mCurr;
		}

		// Assignment
		Iterator& operator=(const Iterator& src)
		{
			mCurr = src.mCurr;
			return *this;
		}

		// Incrementors / Decrementors
		// ++i
		Iterator& operator++()
		{
			mCurr = mCurr->mNext;
			return *this;
		}

		// i++
		Iterator operator++(int)
		{
			Iterator retVal(*this);
			mCurr = mCurr->mNext;
			return retVal;
		}

		// --i
		Iterator& operator--()
		{
			mCurr = mCurr->mPrev;
			return *this;
		}

		// i--
		Iterator operator--(int)
		{
			Iterator retVal(*this);
			mCurr = mCurr->mPrev;
			return retVal;
		}

		// Dereference
		T& operator*() const
		{

			return mCurr->mData;
		}

		Node* operator->() const
		{
			return mCurr;
		}

		// Comparison
		bool operator==(const Iterator& rhs) const
		{
			return (mCurr == rhs.mCurr);
		}

		bool operator!=(const Iterator& rhs) const
		{
			return (mCurr != rhs.mCurr);
		}
	};

	// List functions...

	// Function: Default Constructor
	// Purpose: Initializes size to 0 and head/tail to null
	// Input: None
	// Returns: Nothing
	ITPDoubleList()
	{
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;
	}

	// Function: Copy Constructor
	// Purpose: Initializes this list as a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: Nothing
	ITPDoubleList(const ITPDoubleList& other)
	{
		// 1. Set size to 0, head null, tail null
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;

		// 2. Create a temp that points to the head node in ¡°other¡±
		Node* temp = other.mHead;
		// 3. While temp is not null¡­
		while (temp != nullptr)
		{
			// 3.1 Insert_back temp¡¯s data into this list
			push_back(temp->mData);
			// 3.2 Advance temp to the next node
			temp = temp->mNext;
		}
	}

	// Function: Destructor
	// Purpose: Calls the clear function to delete the list
	// Input: None
	// Returns: Nothing
	~ITPDoubleList()
	{
		clear();
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;
	}

	// Function: clear
	// Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
	// Input: None
	// Returns: Nothing
	void clear()
	{
		while (mSize > 0)
		{
			pop_front();
		}
	}

	// Assignment Operator
	// Function: Assignment Operator
	// Purpose: Clear this list, and then make a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: *this
	ITPDoubleList& operator=(const ITPDoubleList& other)
	{
		// 1. Call clear (to out any values already in this list)
		clear();
		// 2. Create a temp that points to the head node in ¡°other¡±
		Node* temp = other.mHead;
		// 3. While temp is not null¡­
		while (temp != nullptr)
		{
			//	1. Insert_back temp¡¯s data into this list
			push_back(temp->mData);
			//	2. Advance temp to the next node
			temp = temp->mNext;
		}
		//	4. By convention, operator= returns * this
		return *this;
	}

	// Function: size
	// Purpose: Gets the current size of the linked list
	// Input: None
	// Returns: size of the list
	unsigned size() const
	{
		return mSize;
	}

	// Function: push_front
	// Purpose: Inserts a node at the front of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void push_front(const T& value)
	{
		// 1. Dynamically allocate a new node
		Node* temp = new Node;
		//a)Set its data to the value
		temp->mData = value;
		//b) Set its previous to null (since this will be the new head)
		temp->mPrev = nullptr;
		//c) Set its next to the current head
		temp->mNext = mHead;
		// 2. If the size is 0¡­The tail new node
		if (mSize == 0)
		{
			mTail = temp;
		}
		// 3. Otherwise¡­set the previous of current head to new node
		else
		{
			mHead->mPrev = temp;
		}
		// 4. Set the head to new node
		mHead = temp;
		// 5. Increment the size
		mSize++;
	}

	// Function: front
	// Purpose: Gets the value of the node at the front of the list
	// Input: None
	// Returns: Value of the node at the front of the list
	T& front()
	{
		if (mSize == 0)
		{
			error("Empty List!");
		}
		return mHead->mData;
	}

	// Function: pop_front
	// Purpose: Removes the node at the front of the list
	// Input: None
	// Returns: None
	void pop_front()
	{
		// 1. If the size is 0¡­error! 
		if (mSize == 0)
		{
			error("Empty list!");
		}
		// 2. Otherwise if the size is 1¡­ 
		else if (mSize == 1)
		{
			//1. Delete the head node
			delete mHead;
			//2. Set head and tail to null, size to 0
			mHead = nullptr;
			mTail = nullptr;
			mSize = 0;
		}
		// 3. Otherwise¡­
		else
		{
			//1. Set a temp equal to the next node after head
			Node* temp = mHead->mNext;
			//2. Delete the head node
			delete mHead;
			//3. The new head is temp 
			mHead = temp;
			//4. The new head previous is now null
			mHead->mPrev = nullptr;
			//5. Decrement size
			mSize--;
		}
	}

	// Function: push_back
	// Purpose: Inserts a node at the end of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void push_back(const T& value)
	{
		// 1. Dynamically allocate a new node
		Node* temp = new Node;
		//a) Set its data to the value
		temp->mData = value;
		//b) Set its previous to the current tail
		temp->mPrev = mTail;
		//c) Set the next to null (since this will be the new tail)
		temp->mNext = nullptr;
		//	2. If the size is 0¡­The head is the new node
		if (mSize == 0)
		{
			mHead = temp;
		}
		//	3. Otherwise¡­set the next of current tail to the new node
		else
		{
			mTail->mNext = temp;
		}
		//	4. Set the tail to the new node
		mTail = temp;
		//	5. Increment the size
		mSize++;
	}

	// Function: back
	// Purpose: Gets the value of the node at the back of the list
	// Input: None
	// Returns: Value of the node at the back of the list
	T& back()
	{
		if (mSize == 0)
		{
			error("Empty List!");
		}
		return mTail->mData;
	}

	// Function: pop_back
	// Purpose: Removes the node at the end of the list
	// Input: None
	// Returns: None
	void pop_back()
	{
		// 1. If the size is 0¡­error! 
		if (mSize == 0)
		{
			error("Empty list!");
		}
		// 2. Otherwise if the size is 1¡­ 
		else if (mSize == 1)
		{
			//1. Delete the tail node
			delete mTail;
			//2. Set head and tail to null, size to 0
			mHead = nullptr;
			mTail = nullptr;
			mSize = 0;
		}
		// 3. Otherwise¡­
		else
		{
			//1. Set a temp equal to the previous node before the tail
			Node* temp = mTail->mPrev;
			//2. Delete the tail node
			delete mTail;
			//3. The new tail is temp 
			mTail = temp;
			//4. The new tail next is now null
			mTail->mNext = nullptr;
			//5. Decrement size
			mSize--;
		}
	}

	// Function: begin
	// Purpose: Gets an iterator for the start of the list
	// Input: None
	// Returns: Iterator pointing to beginning of list
	Iterator begin() const
	{
		Iterator retVal(mHead);
		return retVal;
	}

	// Function: end
	// Purpose: Gets an iterator for the end of the list
	// Input: None
	// Returns: Iterator pointing to end of list
	Iterator end() const
	{
		Iterator retVal(mTail->mNext);
		return retVal;
	}

	// Function: erase
	// Purpose: Removes the item at the node pointed to by i
	// Input: Iterator pointing to a valid node to remove before
	// Returns: A new iterator pointing to the node after the removed item
	Iterator erase(Iterator& i)
	{
		Iterator retVal;
		//  1. If the iterator is invalid ¡­ error!
		if (i == Iterator(nullptr))
		{
			error("Invalid Iterator!");
		}
		//	2. If the iterator is at begin
		else if (i == begin())
		{
			//	1. pop_front
			pop_front();
			//	2. Return begin
			retVal = begin();
		}
		//	3. If the iterator is at tail
		else if (i == Iterator(mTail))
		{
			//	1. pop_back
			pop_back();
			//	2. Return end
			retVal = end();
		}
		//	4. Otherwise¡­ 
		else
		{
			//	1. Make ¡° before¡±, after¡±, and "toDel" pointer
			Node* before = i.mCurr->mPrev;
			Node* after = i.mCurr->mNext;
			Node* toDel = i.mCurr;
			//	2. Delete ¡° toDel¡±
			delete toDel;
			//	3. Set before¡¯s next to after
			before->mNext = after;
			//	4. Set after¡¯s previous to before
			after->mPrev = before;
			//	5. Decrement size
			mSize--;
			//	6. Return an iterator to after
			retVal = Iterator(after);
		}
		return retVal;
	}

	// Function: insert
	// Purpose: Inserts a list item before node pointed to by i
	// Input: Iterator pointing to a valid node to insert before
	// Returns: A new iterator pointing to the inserted value
	Iterator insert(Iterator& i, const T& val)
	{
		Iterator retVal;
		//  1. If the iterator is invalid ¡­ error!
		if (i == Iterator(nullptr))
		{
			error("Invalid Iterator!");
		}
		//	2. If the iterator is at begin
		else if (i == begin())
		{
			//	1. push_front
			push_front(val);
			//	2. Return begin
			retVal = begin();
		}
		//	3. If the iterator is at end
		else if (i == end())
		{
			//	1. push_back
			push_back(val);
			//	2. Return iterator to last element(not end!)
			retVal = Iterator(mTail);
		}
		//4. Otherwise¡­
		else
		{
			//	1. Make ¡°before¡± and "after¡± pointers
			Node* before = i->mPrev;
			Node* after = i.mCurr;
			//	2. Dynamically allocate a new node
			Node* temp = new Node;
			//	a) Set its data to the value
			temp->mData = val;
			//	b) Set its previous to before
			temp->mPrev = before;
			//	c) Set its next to after
			temp->mNext = after;
			//	3. Set before¡¯s next to the new node
			before->mNext = temp;
			//	4. Set after¡¯s previous to the new node
			after->mPrev = temp;
			//	5. Increment size
			mSize++;
			//	6. Return an iterator pointing to the inserted node
			retVal = Iterator(temp);
		}
		return retVal;
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!! DO NOT EDIT BELOW THIS LINE !!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
public:
	// Function: Output Stream Operator
	// Purpose: Prints the contents of the list to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, list to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const ITPDoubleList<T>& list)
	{
		os << "{";

		Node* temp = list.mHead;
		while (temp != nullptr)
		{
			os << temp->mData;
			if (temp != list.mTail)
			{
				os << ",";
			}

			temp = temp->mNext;
		}

		os << "}";
		return os;
	}

	// Function: toString
	// Purpose: Converts list to a string
	// Input: None
	// Output: String (in the format as the ostream)
	std::string toString() const
	{
		std::stringstream str;
		str << *this;
		return str.str();
	}

	// Function: toReverseString
	// Purpose: Outputs the list in reverse
	// Input: None
	// Output: String in reverse
	std::string toReverseString() const
	{
		std::stringstream str;

		str << "{";

		Node* temp = mTail;
		while (temp != nullptr)
		{
			str << temp->mData;
			if (temp != mHead)
			{
				str << ",";
			}

			temp = temp->mPrev;
		}

		str << "}";

		return str.str();
	}
};
