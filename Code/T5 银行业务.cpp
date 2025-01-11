/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 条件编译，解决window和linux的差异
#ifdef _WIN32
#include <conio.h>
#endif

const int SPEED_A = 2; // A窗口的业务速度
const int SPEED_B = 1; // B窗口的业务速度

using namespace std;

// 向量类
template<typename T>
class Vector {
private:
  T* data;  // 数据指针，存储元素
  size_t capacity; //分配的内存容量
  size_t size; // 当前存储的元素数量

  // 扩展容量
  void ExpandCapacity() {
    size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
  }

public:
  // 默认构造函数
  Vector() : data(nullptr), capacity(0), size(0) {}

  // 给定capacity的构造函数
  Vector(size_t n) : capacity(n), size(n) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = T();
    }
  }

  // 给定capacity和初始值的构造函数
  Vector(size_t n, T& value) : capacity(n), size(n) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = value;
    }
  }

  // 拷贝构造函数，允许初始化 Vector 的元素是其他 Vector 对象
  Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = other.data[i];
    }
  }

  // 析构函数
  ~Vector() {
    delete[] data;
  }

  // 返回size
  size_t Size() const {
    return size;
  }

  bool Empty() {
    return (size == 0);
  }

  void PushBack(const T& value) {
    if (size == capacity) {
      ExpandCapacity();
    }
    data[size++] = value;
  }

  void PopBack() {
    if (size == 0) {
      throw out_of_range("Vector is empty");
    }
    else {
      --size;
    }
  }

  void Reverse() {
    int start = 0, end = size - 1;
    while (start < end) {
      swap(data[start], data[end]);
      ++start, --end;
    }
  }

  void Clear() {
    size = 0;
  }

  // 访问指定位置的元素（不带边界检查）
  T& operator[](size_t index) {
    return data[index];
  }

  const T& operator[](size_t index) const{
    return data[index];
  }
};

// 队列类
template <typename T>
class Queue {
private:
  T* data;
  size_t front_index; // 队列头部元素的索引
  size_t back_index;  // 下一个可插入位置的索引，也就是尾部的后一个位置的索引
  size_t count; //当前队列中元素的数量
  size_t capacity; // 队列的容量

  void Resize() {
    size_t new_capacity = capacity * 2; // 扩大容量为原来的两倍
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < count; ++i) {
      new_data[i] = data[(front_index + i) % capacity];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    front_index = 0;
    back_index = count;
  }

public:
  // 构造函数
  Queue() : capacity(4), front_index(0), back_index(0), count(0) {
    data = new T[capacity]; // 初始化容量为4
  }

  // 析构函数
  ~Queue() {
    delete[] data;
  }

  // 检查队列是否为空
  bool Empty() const {
    return count == 0;
  }

  // 返回队列中元素个数
  size_t Size() const {
    return count;
  }

  // 返回队首元素
  T& Front() const {
    if (Empty()) {
      throw out_of_range("Queue is empty");
    }
    else {
      return data[front_index];
    }
  }

  // 返回队尾元素
  T& Back() const {
    if (Empty()) {
      throw out_of_range("Queue is empty");
    }
    else {
      return data[(back_index + capacity - 1) % capacity];
    }
  }

  // 向队尾添加元素
  void Push(const T& value) {
    if (count == capacity) {
      Resize();
    }
    data[back_index] = value;
    back_index = (back_index + 1) % capacity; // 循环更新back索引
    ++count;
  }

  // 删除队首元素
  void Pop() {
    if (Empty()) {
      throw out_of_range("Queue is empty!");
    }
    else {
      front_index = (front_index + 1) % capacity; // 循环更新front_index索引
      --count;
    }
  }
};

// 窗口类
class Window {
private:
  int speed; // 处理业务的速度
  Queue<int> clients; // 排队的客户

public:
  Window(const int speed_value){
    speed = speed_value;
  }

  bool Empty() {
    return clients.Empty();
  }

  // person加入队列
  void Push(const int person) {
    clients.Push(person);
  }

  // 办理完业务的人离开队列
  void Pop(Vector<int>& leave_order) {
    for (int i = 0; i < speed; ++i) {
      if (!Empty()) {
        leave_order.PushBack(clients.Front());
        clients.Pop();
      }
    }
  }
};

// 输入函数
void Input(Vector<int>& people) {
  cout << "请输入顾客的人数以及编号：" << endl;
  int num; // 顾客的人数
  cin >> num;
  for (int i = 0; i < num; ++i) {
    int number;
    cin >> number;
    people.PushBack(number);
  }
}

// 输出函数
void Output(const Vector<int>& leave_order) {
  cout << "结果是：" << endl;
  for (size_t i = 0; i < leave_order.Size(); ++i) {
    cout << leave_order[i];
    if (i != leave_order.Size() - 1) {
      cout << ' ';
    }
    else {
      cout << endl;
    }
  }
}

int main() {
  Vector<int> people; // 存储客户的向量
  Input(people); // 输入客户向量
  
  Window window_A(SPEED_A), window_B(SPEED_B); // 初始化两个窗口

  for (size_t i = 0; i < people.Size(); ++i) {
    // 如果是奇数
    if (1 == people[i] % 2) {
      window_A.Push(people[i]); // 加入A窗口队列
    }
    else {
      window_B.Push(people[i]); // 加入B窗口队列
    }
  }

  Vector<int> leave_order; // 存储客户离开顺序的向量

  // 当A窗口非空或B窗口非空时
  while (!window_A.Empty() || !window_B.Empty()) {
    window_A.Pop(leave_order); // A窗口中顾客离开
    window_B.Pop(leave_order); // B窗口中顾客离开
  }

  Output(leave_order); // 输出结果

  cout<< endl << "按回车键退出程序..." << endl;
  #ifdef _WIN32
    while (_getch() != '\r')
      continue;
  #endif

  return 0;
}