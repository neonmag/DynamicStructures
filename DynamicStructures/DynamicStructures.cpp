#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Queue {
private:
	struct Node {
		T data;
		Node* next;
		Node(T value) {
			data = value;
			next = nullptr;
		}
	};

	Node* front;
	Node* end; // Example for circled queue
	int size;

public:
	Queue() {
		front = nullptr;
		end = nullptr;
		size = 0;
	}

	void add(T value) { // enqueue
		Node* newElement = new Node(value);

		if (end == nullptr) {
			front = end = newElement;
		}
		else {
			end->next = newElement;
			end = newElement;
		}

		size++;
	}

	T remove() { // dequeue
		if (front == nullptr) {
			throw runtime_error("Empty queue!");
		}

		int value = front->data;

		Node* temp = front;
		front = front->next;

		if (front == nullptr) {
			end = nullptr;
		}

		delete temp;
		size--;
		return value;
	}

	T take() const { // peek
		if (front == nullptr) {
			throw runtime_error("empty queue!");
		}
		return front->data;
	}

	bool isEmpty() const {
		return size == 0;
	}

	int getSize() const {
		return size;
	}

	~Queue() {
		while (!isEmpty()) {
			remove();
		}
	}
};

template <typename T>
class PriorityQueue {
public:
	vector<pair<T, int>> queue;

	void push(T value, int priority) {
		queue.push_back({ value, priority });

		sort(queue.begin(), queue.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
			});
	}

	pair<T, int> top() const {
		if (!queue.empty()) {
			return queue.front();
		}

		throw out_of_range("Empty queue");
	}

	void pop() {
		if (!queue.empty()) {
			queue.erase(queue.begin());
		}
		else {
			throw out_of_range("Empty queue");
		}
	}

	bool empty() const {
		return queue.empty();
	}
};

template <typename T>
class BinaryTree {
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(T val) : data(val), left(nullptr), right(nullptr) {}
	};

	Node* root;

	Node* insert(Node* node, T value) {
		if (node == nullptr) {
			return new Node(value);
		}
		if (value < node->data) {
			node->left = insert(node->left, value);
		}
		else if (value > node->data) {
			node->right = insert(node->right, value);
		}
		return node;
	}

	void inorderTraversal(Node* node) {
		if (node != nullptr) {
			inorderTraversal(node->left);
			cout << node->data << " ";
			inorderTraversal(node->right);
		}
	}

	Node* search(Node* node, T value) {
		if (node == nullptr || node->data == value) {
			return node;
		}
		if (value < node->data) {
			return search(node->left, value);
		}
		return search(node->right, value);
	}

	void destroyTree(Node* node) {
		if (node != nullptr) {
			destroyTree(node->left);
			destroyTree(node->right);
			delete node;
		}
	}

public:
	BinaryTree() : root(nullptr) {}

	void insert(T value) {
		root = insert(root, value);
	}

	void display() {
		inorderTraversal(root);
		cout << endl;
	}

	bool search(T value) {
		return search(root, value) != nullptr;
	}

	~BinaryTree() {
		destroyTree(root);
	}
};


int main()
{
	Queue<int> q;
	q.add(10);
	q.add(20);
	q.add(30);

	cout << q.take() << endl;
	cout << q.getSize() << endl;

	while (!q.isEmpty()) {
		cout << q.remove() << endl;
	}

	PriorityQueue<int> pq;

	pq.push(10, 2);
	pq.push(20, 3);
	pq.push(30, 1);

	while (!pq.empty()) {
		pair<int, int> res = pq.top();
		cout << "(" << res.first << ", " << res.second << ")" << endl;
		pq.pop();
	}

	BinaryTree<int> tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(70);
	tree.insert(20);
	tree.insert(40);
	tree.insert(60);
	tree.insert(80);

	tree.display();

	cout <<  (tree.search(40) ? "found" : "not found") << endl;
	cout <<  (tree.search(90) ? "found" : "not found") << endl;

}
