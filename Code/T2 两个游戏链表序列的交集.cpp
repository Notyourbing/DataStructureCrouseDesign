/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
using namespace std;

// ������ڵ���
template<typename T>
class Node {
public:
  T data;
  Node<T>* next; // ��һ���ڵ�

  Node(const T& value) {
	data = value;
	next = nullptr;
  }
};

// ��������
template <typename T>
class List {
private:
  Node<T>* head; // ͷָ��
  Node<T>* tail; // βָ��
public:
  List() : head(nullptr), tail(nullptr) {}

  ~List() {
	Clear();
  }

  // ����ͷָ��
  Node<T>* GetHead() const {
	return head;
  }

  // ����βָ��
  Node<T>* GetBack() const {
	return tail;
  }

  // ������ĩβ���һ��Ԫ��
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

  // ��ӡ�����е����ݣ��Կո�ָ�
  void Display() const {
	Node<T>* temp = head;
	while (temp) {
	  cout << temp->data << ' ';
	  temp = temp->next;
	}
	cout << endl;
  }

  // �ͷ������нڵ���ڴ�
  void Clear() {
	while (head) {
	  Node<T>* temp = head;
	  head = head->next;
	  delete temp;
	}
  }
};

// ������������-1ֹͣ
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

// ����list_1��list_2�Ľ�������ע�����������Ƿǽ������Ҫ������������ȵ�Ԫ�ص������
List<int> GetCommonList(const List<int>& list_1, const List<int>& list_2) {
  List<int> res;
  Node<int>* node_ptr_1 = list_1.GetHead();
  Node<int>* node_ptr_2 = list_2.GetHead();
  int last_append = -1; // ��¼�������ֵ

  // ������ָ�붼Ϊ�ǿ�ָ��
  while (node_ptr_1 && node_ptr_2) {
	// �������ָ��ָ��������
	if (node_ptr_1->data == node_ptr_2->data) {
	  // ���res����Ϊ�գ��������������res������
	  if (res.GetHead() == nullptr || last_append != node_ptr_1->data) {
		res.Append(node_ptr_1->data); // ���������ӵ�res�������
		last_append = node_ptr_1->data;
	  }
	  // ����ָ�붼����
	  node_ptr_1 = node_ptr_1->next;
	  node_ptr_2 = node_ptr_2->next;
	}
	else if (node_ptr_1->data < node_ptr_2->data) { // ��һ����С�ڵڶ�����
	  node_ptr_1 = node_ptr_1->next; // ��һ��ָ������
	}
	else { // ��һ�������ڵڶ�����
	  node_ptr_2 = node_ptr_2->next;
	}
  }
  return res;
}

int main() {
  List<int> list_1; // ��һ������
  List<int> list_2; // �ڶ�������
  cout << "��������������(��ռһ�У�ÿ��������-1��β)��" << endl;
  // ������������
  ListInput(list_1);
  ListInput(list_2);

  // �õ���������
  List<int> list_res = GetCommonList(list_1, list_2);
  // �����������Ϊ��
  if (list_res.GetHead() == nullptr) {
	cout << "NULL" << endl;
  }
  else {
	cout << "��������Ϊ��" << endl;
	list_res.Display();
  }

  cout << endl << "���س����˳�..." << endl;
  while (_getch() != '\r')
	continue;
  return 0;
}