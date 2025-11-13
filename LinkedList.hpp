#pragma once
#include <iostream>
using namespace std;



template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const{
		Node<T>* initial = head;
		while (initial){
			cout << initial->data<<endl;
			initial = initial->next;
		}
	}
	void printReverse() const{
		Node<T>* initial = tail;
		while(initial){
			cout << initial->data<<endl;
			initial = initial->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node<T>* getHead(){
		return head;
	}
	const Node<T>* getHead() const{
		return head;
	}
	Node<T>* getTail(){
		return tail;
	}
	const Node<T>* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		Node<T>* nHead = new Node<T>();
		nHead->data = data;
		nHead->prev = nullptr;
		nHead->next = head;

		//in the case that there is no first node
		if (head){
			head->prev = nHead;
		} else {
			tail = nHead;
		}

		head = nHead;

		count++;
	}

	void addTail(const T& data){
		Node<T>* nTail = new Node<T>();
		nTail->data = data;
		nTail->prev = tail;
		nTail->next = nullptr;

		if (tail){
			tail->next = nTail;
		} else {
			head = nTail;
		}
		tail = nTail;

		count++;
	}

	// Removal
	bool removeHead(){
		if (!head){
			return false;
		}
		//Delete all of head
		Node<T>* prevHead = head;
		head = head->next;

		if (head){
			head->prev = nullptr;
		} else {
			tail = nullptr;
		}

		delete prevHead;
		count--;
		return true;
	}
	bool removeTail(){
		if (!tail){
			return false;
		}
		Node<T>* prevTail = tail;
		tail = tail->prev;
		if (tail){
			tail->next = nullptr;
		} else {
			head = nullptr;
		}
		delete prevTail;

		count--;
		return true;
	}
	void clear(){
		size_t iCount = count;
		for (size_t i = 0; i < iCount; i++){
			removeHead();
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if(this == &other){
			return *this;
		}
		clear();

		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this == &rhs){
			return *this; 
		}
		
        clear();

        Node<T>* initial = rhs.head;
        while (initial){
			addTail(initial->data);
			initial = initial->next;
		}

        return *this;
    }
	

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0){}

	LinkedList(const LinkedList<T>& list)
		: head(nullptr), tail(nullptr), count(0) {
			Node<T>* initial = list.head;
			while(initial){
				addTail(initial->data);
				initial = initial->next;
			}
	}
	


	LinkedList(LinkedList<T>&& other) noexcept 
		: head(other.head), tail(other.tail), count(other.count) {
			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;
		}
	~LinkedList(){
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};


