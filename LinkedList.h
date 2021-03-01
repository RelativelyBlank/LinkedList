#pragma once
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class LinkedList {


public:

	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node() {
			next = nullptr;
			prev = nullptr;
		};

	};
	LinkedList();
	~LinkedList();

	LinkedList(const LinkedList<T>& list);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	bool operator==(const LinkedList<T>& rhs) const;


	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	unsigned int NodeCount() const;
	void PrintForward() const;
	void PrintReverse() const;

	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;



	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	void FindAll(vector<Node*>& outData, const T& value) const;

	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);


private:
	Node* headNode;
	Node* tailNode;
	int nodeCounter;
};
template <typename T>
LinkedList<T>::LinkedList() {
	headNode = nullptr;
	tailNode = nullptr;
	nodeCounter = 0;
}
template <typename T>
LinkedList<T>::~LinkedList() {
	Node* deleteNode = headNode;
	int allCounter = nodeCounter;
	for(int i =0; i<allCounter;i++) {
		Node* next = deleteNode->next;
		delete deleteNode;
		deleteNode = next;
		nodeCounter--;
	}

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	headNode = nullptr;
	tailNode = nullptr;
	nodeCounter = 0;
	for (int i = list.nodeCounter - 1; i >= 0; i--) {
		T nodeData = list[i];
		AddHead(nodeData);
	}
	this->nodeCounter = list.nodeCounter;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	Clear();
	headNode = nullptr;
	tailNode = nullptr;
	for (int i = rhs.nodeCounter - 1; i >= 0; i--) {
		T nodeData = rhs[i];
		AddHead(nodeData);
	}
	this->nodeCounter = rhs.nodeCounter;
	return *this;

}
template <typename T>
void LinkedList<T>::Clear() {
	Node* lastNode = headNode;
	Node* temp;
	for (int i = 0; i < nodeCounter; i++) {
		temp = lastNode->next;
		delete lastNode;
		lastNode = temp;
	}
	nodeCounter = 0;
	headNode = nullptr;
	tailNode = nullptr;
}
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	Node* lastNode = headNode;
	for (int x = 0; x < rhs.nodeCounter; x++) {
		if (lastNode->data == rhs[x])
			return true;
		lastNode = lastNode->next;
	}
	return false;

}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node* newNode = new Node;
	newNode->data = data;
	if (headNode == nullptr || tailNode == nullptr) {
		tailNode = newNode;
		headNode = newNode;
	}
	else {
		newNode->next = headNode;
		headNode->prev = newNode;
		headNode = newNode;
	}
	nodeCounter++;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (headNode != nullptr) {
		Node* nextNode = headNode->next;
		if(nextNode!=nullptr)
			nextNode->prev = nullptr;
		nodeCounter--;
		delete headNode;
		headNode = nextNode;
		return true;
	}
	return false;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* newNode = new Node;
	newNode->data = data;
	if (headNode == nullptr || tailNode == nullptr) {
		tailNode = newNode;
		headNode = newNode;
	}
	else {
		tailNode->next = newNode;
		newNode->prev = tailNode;
		tailNode = newNode;
	}
	nodeCounter++;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (tailNode != nullptr) {
		Node* nextNode = tailNode->prev;
		if (nextNode != nullptr)
			nextNode->next = nullptr;
		nodeCounter--;
		delete tailNode;
		tailNode = nextNode;
		return true;
	}
	return false;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	Node* lastNode = headNode;
	Node* temp;
	if (index == 0) {
		RemoveHead();
		return true;
	}
	else if ((int)index == nodeCounter) {
		RemoveTail();
		return true;
	}
	else {
		for (int i = 0; i < nodeCounter; i++) {
			if (i == (int)index) {
				temp = lastNode->prev;
				temp->next = lastNode->next;
				lastNode->next->prev = temp;
				delete lastNode;
				nodeCounter--;
				return true;
			}
			else
				lastNode = lastNode->next;

		}
		return false;
	}

}


template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (int i = (int)count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
}
template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	for (int i = 0; i < (int)count; i++) {
		AddTail(data[i]);
	}
}
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return nodeCounter;
}
template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		cout << lastNode->data << endl;
		lastNode = lastNode->next;
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	cout << node->data << endl;
	PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	cout << node->data << endl;
	PrintReverseRecursive(node->prev);
}
template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	int removeCounter = 0;
	Node* lastNode = headNode;
	Node* NodeAfter;
	Node* NodeBefore;
	int allCounters = nodeCounter;
	for (int x = 0; x < allCounters; x++) {
		if (lastNode->data == data && headNode != nullptr && tailNode != nullptr) {
			NodeBefore = lastNode->prev;
			NodeAfter = lastNode->next;
			NodeBefore->next = NodeAfter;
			NodeAfter->prev = NodeBefore;
			removeCounter++;
			nodeCounter--;
			delete lastNode;
			lastNode = NodeAfter;
		}
		else
			lastNode = lastNode->next;

	}
	return removeCounter;
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* lastNode = tailNode;
	for (int x = nodeCounter; x > 0; x--) {
		cout << lastNode->data << endl;
		lastNode = lastNode->prev;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tailNode;
}


template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return headNode;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tailNode;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return headNode;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		lastNode = lastNode->next;
		if (x == (int)index)
			return lastNode;
	}
	throw out_of_range("Out of range");
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		if (x == (int)index)
			return lastNode;
		lastNode = lastNode->next;
	}
	throw out_of_range("Out of range");
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		if (x == (int)index)
			return lastNode->data;

		lastNode = lastNode->next;
	}
	throw out_of_range("Out of range");
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		if (x == (int)index)
			return lastNode->data;
		lastNode = lastNode->next;
	}
	throw out_of_range("Out of range");
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		if (lastNode->data == data)
			return lastNode;
		lastNode = lastNode->next;
	}
	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		if (lastNode->data == data)
			return lastNode;
		lastNode = lastNode->next;
	}
	return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<LinkedList<T>::Node*>& outData, const T& value) const {
	Node* lastNode = headNode;
	for (int x = 0; x < nodeCounter; x++) {
		if (lastNode->data == value)
			outData.push_back(lastNode);
		lastNode = lastNode->next;
	}
}


template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	Node* lastNode = headNode;
	Node* insertNode = new Node;
	insertNode->data = data;
	for (int x = 0; x < nodeCounter - 1; x++) {
		if (lastNode->data == node->data) {
			insertNode->next = lastNode->next;
			lastNode->next->prev = insertNode;
			lastNode->next = insertNode;
			insertNode->prev = lastNode;
		}

		lastNode = lastNode->next;
	}
	nodeCounter++;
}
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	Node* lastNode = headNode;
	Node* insertNode = new Node;
	insertNode->data = data;
	for (int x = 0; x < nodeCounter; x++) {
		if (lastNode->data == node->data) {
			insertNode->prev = lastNode->prev;
			lastNode->prev->next = insertNode;
			lastNode->prev = insertNode;
			insertNode->next = lastNode;
		}

		lastNode = lastNode->next;
	}
	nodeCounter++;
}
template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (index == 0)
		AddHead(data);
	else if ((int)index == nodeCounter)
		AddTail(data);
	else
		InsertBefore(GetNode(index), data);
}
