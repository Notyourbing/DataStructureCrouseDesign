/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdexcept>
// �������룬���window��linux�Ĳ���
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

// ��С����
class MinHeap {
private:
  int* data;
  size_t size;
  size_t capacity;

  void Resize() {
	size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
	int* new_data = new int[new_capacity];
	for (size_t i = 0; i < size; ++i) {
	  new_data[i] = data[i];
	}
	delete[] data;
	data = new_data;
	capacity = new_capacity;
  }

  // ��indexλ�õ������ϵ���
  void HeapifyUp(size_t index) {
	while (index > 0) {
	  size_t parent = (index - 1) / 2;
	  if (data[index] < data[parent]) {
		int temp = data[index];
		data[index] = data[parent];
		data[parent] = temp;
		index = parent;
	  }
	  else {
		break;
	  }
	}
  }

  // ��indexλ�õ������µ���
  void HeapifyDown(size_t index) {
	while (index * 2 + 1 < size) {
	  size_t left = index * 2 + 1;
	  size_t right = index * 2 + 2;
	  size_t smallest = left;
	  if (right < size && data[right] < data[left]) {
		smallest = right;
	  }
	  if (data[index] > data[smallest]) {
		int temp = data[index];
		data[index] = data[smallest];
		data[smallest] = temp;
		index = smallest;
	  }
	  else {
		break;
	  }
	}
  }

public:
  MinHeap() {
	data = nullptr;
	size = 0;
	capacity = 0;
  }

  ~MinHeap() {
	delete[] data;
  }

  size_t Size() {
	return size;
  }

  void Push(const int num) {
	if (size + 1 >= capacity) {
	  Resize();
	}
	data[size] = num;
	HeapifyUp(size);
	++size;
  }

  void Pop() {
	if (0 == size) {
	  throw out_of_range("Heap is empty!");
	}
	data[0] = data[size - 1];
	--size;
	HeapifyDown(0);
  }

  int Top() {
	if (0 == size) {
	  throw out_of_range("Heap is empty!");
	}
	return data[0];
  }

  bool Empty() {
	return (0 == size);
  }

  void Disp() {
	for (int i = 0; i < size; ++i) {
	  cout << data[i] << ' ';
	}
	cout << endl;
  }
};

// ��Ŀ˼·�����Ǿ�ľͷ�ķ�����̣��ϲ�ľ�飬һ��Ҫ�ϲ�N-1��ľ�飬
// ÿ�κϲ�ľ��ʱ��Ҫ���ܻ������٣����ǲ���̰�Ĳ���ÿ�κϲ�������С������ľ�飬��������С����ά�����е�ľ�飬ÿ�δӶѶ�ȡ������Ԫ��
int main() {
  int N;
  cin >> N;
  MinHeap min_heap;
  // ��ľ��ĳ���push����С��
  for (int i = 0; i < N; ++i) {
	int length;
	cin >> length;
	min_heap.Push(length);
  }
  long long total_cost = 0;
  // ����С����ľͷ��������һ��
  while (min_heap.Size() > 1) {
	// ȡ����һ����С��ľ��
	int len1 = min_heap.Top();
	min_heap.Pop();
	// ȡ���ڶ�����С��ľ��
	int len2 = min_heap.Top();
	min_heap.Pop();
	// �µ�ľ��ĳ���
	int new_len = len1 + len2;
	// �ϲ�ľ�廨�ѵķ���
	total_cost += new_len;
	// ��ľ��push����С��
	min_heap.Push(new_len);
  }
  cout << total_cost << endl;

  cout << endl << "���س����˳�..." << endl;
#ifdef _WIN32
  while (_getch() != '\r')
	continue;
#endif

  return 0;
}