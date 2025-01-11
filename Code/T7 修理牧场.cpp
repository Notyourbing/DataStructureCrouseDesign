/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdexcept>
// 条件编译，解决window和linux的差异
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

// 最小堆类
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

  // 将index位置的数向上调整
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

  // 将index位置的数向下调整
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

// 题目思路：考虑锯木头的反向过程：合并木块，一共要合并N-1次木块，
// 每次合并木块时，要想总花费最少，我们采用贪心策略每次合并长度最小的两个木块，所以用最小堆来维护现有的木块，每次从堆顶取出两个元素
int main() {
  int N;
  cin >> N;
  MinHeap min_heap;
  // 将木块的长度push进最小堆
  for (int i = 0; i < N; ++i) {
	int length;
	cin >> length;
	min_heap.Push(length);
  }
  long long total_cost = 0;
  // 当最小堆中木头个数多于一个
  while (min_heap.Size() > 1) {
	// 取出第一个最小的木板
	int len1 = min_heap.Top();
	min_heap.Pop();
	// 取出第二个最小的木板
	int len2 = min_heap.Top();
	min_heap.Pop();
	// 新的木板的长度
	int new_len = len1 + len2;
	// 合并木板花费的费用
	total_cost += new_len;
	// 将木板push进最小堆
	min_heap.Push(new_len);
  }
  cout << total_cost << endl;

  cout << endl << "按回车键退出..." << endl;
#ifdef _WIN32
  while (_getch() != '\r')
	continue;
#endif

  return 0;
}