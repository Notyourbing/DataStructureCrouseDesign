/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
using namespace std;

// 单链表节点类
template<typename T>
class Node {
public:
  T data;
  Node<T>* next; // 下一个节点

  Node(const T& value) {
	data = value;
	next = nullptr;
  }
};

// 单链表类
template <typename T>
class List {
private:
  Node<T>* head; // 头指针
  Node<T>* tail; // 尾指针
public:
  List() : head(nullptr), tail(nullptr) {}

  ~List() {
	Clear();
  }

  // 返回头指针
  Node<T>* GetHead() const {
	return head;
  }

  // 返回尾指针
  Node<T>* GetBack() const {
	return tail;
  }

  // 向链表末尾添加一个元素
  void Append(const T& value) {
	Node<T>* new_node_ptr = new Node<T>(value);
	if (head) {
	  Node<T>* temp = head;
	  while (temp->next) {
		temp = temp->next;
	  }
	  temp->next = new_node_ptr;
	  tail = new_node_ptr;
	}
	else {
	  head = new_node_ptr;
	  tail = new_node_ptr;
	}
  }

  // 打印链表中的内容，以空格分隔
  void Display() const {
	Node<T>* temp = head;
	while (temp) {
	  cout << temp->data << ' ';
	  temp = temp->next;
	}
	cout << endl;
  }

  // 释放链表中节点的内存
  void Clear() {
	while (head) {
	  Node<T>* temp = head;
	  head = head->next;
	  delete temp;
	}
  }
};

// 输入链表，遇到-1停止
void ListInput(List<int>& list) {
  while (1) {
	int num;
	cin >> num;
	if (num != -1) {
	  list.Append(num);
	}
	else {
	  break;
	}
  }
}

// 返回list_1和list_2的交集链表，注意两个链表是非降序，因此要考虑有连续相等的元素的情况。
List<int> GetCommonList(const List<int>& list_1, const List<int>& list_2) {
  List<int> res;
  Node<int>* node_ptr_1 = list_1.GetHead();
  Node<int>* node_ptr_2 = list_2.GetHead();
  int last_append = -1; // 记录最后插入的值

  // 当两个指针都为非空指针
  while (node_ptr_1 && node_ptr_2) {
	// 如果两个指针指向的数相等
	if (node_ptr_1->data == node_ptr_2->data) {
	  // 如果res链表为空，或者这个数不在res链表中
	  if (res.GetHead() == nullptr || last_append != node_ptr_1->data) {
		res.Append(node_ptr_1->data); // 将这个数添加到res链表最后
		last_append = node_ptr_1->data;
	  }
	  // 两个指针都右移
	  node_ptr_1 = node_ptr_1->next;
	  node_ptr_2 = node_ptr_2->next;
	}
	else if (node_ptr_1->data < node_ptr_2->data) { // 第一个数小于第二个数
	  node_ptr_1 = node_ptr_1->next; // 第一个指针右移
	}
	else { // 第一个数大于第二个数
	  node_ptr_2 = node_ptr_2->next;
	}
  }
  return res;
}

int main() {
  List<int> list_1; // 第一个链表
  List<int> list_2; // 第二个链表
  cout << "请输入两个链表(各占一行，每个链表以-1结尾)：" << endl;
  // 输入两个链表
  ListInput(list_1);
  ListInput(list_2);

  // 得到交集链表
  List<int> list_res = GetCommonList(list_1, list_2);
  // 如果交集链表为空
  if (list_res.GetHead() == nullptr) {
	cout << "NULL" << endl;
  }
  else {
	cout << "交集链表为：" << endl;
	list_res.Display();
  }

  cout << endl << "按回车键退出..." << endl;
  while (_getch() != '\r')
	continue;
  return 0;
}