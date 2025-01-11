/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// �������룬���window��linux�Ĳ���
#ifdef _WIN32
#include <conio.h>
#endif

const int SPEED_A = 2; // A���ڵ�ҵ���ٶ�
const int SPEED_B = 1; // B���ڵ�ҵ���ٶ�

using namespace std;

// ������
template<typename T>
class Vector {
private:
  T* data;  // ����ָ�룬�洢Ԫ��
  size_t capacity; //������ڴ�����
  size_t size; // ��ǰ�洢��Ԫ������

  // ��չ����
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
  // Ĭ�Ϲ��캯��
  Vector() : data(nullptr), capacity(0), size(0) {}

  // ����capacity�Ĺ��캯��
  Vector(size_t n) : capacity(n), size(n) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = T();
    }
  }

  // ����capacity�ͳ�ʼֵ�Ĺ��캯��
  Vector(size_t n, T& value) : capacity(n), size(n) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = value;
    }
  }

  // �������캯���������ʼ�� Vector ��Ԫ�������� Vector ����
  Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
      data[i] = other.data[i];
    }
  }

  // ��������
  ~Vector() {
    delete[] data;
  }

  // ����size
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

  // ����ָ��λ�õ�Ԫ�أ������߽��飩
  T& operator[](size_t index) {
    return data[index];
  }

  const T& operator[](size_t index) const{
    return data[index];
  }
};

// ������
template <typename T>
class Queue {
private:
  T* data;
  size_t front_index; // ����ͷ��Ԫ�ص�����
  size_t back_index;  // ��һ���ɲ���λ�õ�������Ҳ����β���ĺ�һ��λ�õ�����
  size_t count; //��ǰ������Ԫ�ص�����
  size_t capacity; // ���е�����

  void Resize() {
    size_t new_capacity = capacity * 2; // ��������Ϊԭ��������
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
  // ���캯��
  Queue() : capacity(4), front_index(0), back_index(0), count(0) {
    data = new T[capacity]; // ��ʼ������Ϊ4
  }

  // ��������
  ~Queue() {
    delete[] data;
  }

  // �������Ƿ�Ϊ��
  bool Empty() const {
    return count == 0;
  }

  // ���ض�����Ԫ�ظ���
  size_t Size() const {
    return count;
  }

  // ���ض���Ԫ��
  T& Front() const {
    if (Empty()) {
      throw out_of_range("Queue is empty");
    }
    else {
      return data[front_index];
    }
  }

  // ���ض�βԪ��
  T& Back() const {
    if (Empty()) {
      throw out_of_range("Queue is empty");
    }
    else {
      return data[(back_index + capacity - 1) % capacity];
    }
  }

  // ���β���Ԫ��
  void Push(const T& value) {
    if (count == capacity) {
      Resize();
    }
    data[back_index] = value;
    back_index = (back_index + 1) % capacity; // ѭ������back����
    ++count;
  }

  // ɾ������Ԫ��
  void Pop() {
    if (Empty()) {
      throw out_of_range("Queue is empty!");
    }
    else {
      front_index = (front_index + 1) % capacity; // ѭ������front_index����
      --count;
    }
  }
};

// ������
class Window {
private:
  int speed; // ����ҵ����ٶ�
  Queue<int> clients; // �ŶӵĿͻ�

public:
  Window(const int speed_value){
    speed = speed_value;
  }

  bool Empty() {
    return clients.Empty();
  }

  // person�������
  void Push(const int person) {
    clients.Push(person);
  }

  // ������ҵ������뿪����
  void Pop(Vector<int>& leave_order) {
    for (int i = 0; i < speed; ++i) {
      if (!Empty()) {
        leave_order.PushBack(clients.Front());
        clients.Pop();
      }
    }
  }
};

// ���뺯��
void Input(Vector<int>& people) {
  cout << "������˿͵������Լ���ţ�" << endl;
  int num; // �˿͵�����
  cin >> num;
  for (int i = 0; i < num; ++i) {
    int number;
    cin >> number;
    people.PushBack(number);
  }
}

// �������
void Output(const Vector<int>& leave_order) {
  cout << "����ǣ�" << endl;
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
  Vector<int> people; // �洢�ͻ�������
  Input(people); // ����ͻ�����
  
  Window window_A(SPEED_A), window_B(SPEED_B); // ��ʼ����������

  for (size_t i = 0; i < people.Size(); ++i) {
    // ���������
    if (1 == people[i] % 2) {
      window_A.Push(people[i]); // ����A���ڶ���
    }
    else {
      window_B.Push(people[i]); // ����B���ڶ���
    }
  }

  Vector<int> leave_order; // �洢�ͻ��뿪˳�������

  // ��A���ڷǿջ�B���ڷǿ�ʱ
  while (!window_A.Empty() || !window_B.Empty()) {
    window_A.Pop(leave_order); // A�����й˿��뿪
    window_B.Pop(leave_order); // B�����й˿��뿪
  }

  Output(leave_order); // ������

  cout<< endl << "���س����˳�����..." << endl;
  #ifdef _WIN32
    while (_getch() != '\r')
      continue;
  #endif

  return 0;
}