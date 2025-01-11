/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <random>
#include <ctime>
#include <stdexcept>
#include <iomanip>
// �������룬���window��linux�Ĳ���
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

// ȡ�������ע�Ϳ���չʾ����ǰ�������
// #define DISP


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

  const T& operator[](size_t index) const {
    return data[index];
  }

  class Iterator {
  private:
    T* ptr;

  public:
    Iterator(T* p) : ptr(p) {}

    //  �����ò�����
    T& operator*() {
      return *ptr;
    }

    T* operator->() {
      return ptr;
    }

    Iterator& operator++() {
      ++ptr;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++ptr;
      return tmp;
    }

    bool operator!=(const Iterator& other) const {
      return ptr != other.ptr;
    }

    int operator-(const Iterator& other) const {
      return ptr - other.ptr;
    }

    Iterator operator+(const int x) {
      if (ptr + x > data + size) {
        throw out_of_range("Vector Iterator out of range!");
      }
      return Iterator(ptr + x);
    }

    bool operator>=(const Iterator& other) const {
      return (ptr >= other.ptr);
    }

    bool operator>(const Iterator& other) const {
      return (ptr > other.ptr);
    }

    bool operator<=(const Iterator& other) const {
      return (ptr <= other.ptr);
    }

    bool operator<(const Iterator& other) const {
      return (ptr < other.ptr);
    }
  };

  Iterator begin() {
    return Iterator(data);
  }

  Iterator end() {
    return Iterator(data + size);
  }

  const Iterator begin() const {
    return Iterator(data);
  }

  const Iterator end() const {
    return Iterator(data + size);
  }

  // ɾ��index��Ԫ��
  void erase(const size_t index) {
    if (index >= size) {
      throw out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
      data[i] = data[i + 1];
    }
    --size;
  }

  // ɾ��positionָ���Ԫ��
  Iterator erase(const Iterator position) {
    // ���������Ƿ�����Ч��Χ��
    if (position.ptr < data || position.ptr >= data + size) {
      throw out_of_range("Iterator out of range");
    }
    // ����Ҫɾ��λ�õ�ƫ����
    size_t index = position.ptr - data;
    for (size_t i = index; i < size - 1; ++i) {
      data[i] = data[i + 1];
    }
    --size;
    // ����ɾ��Ԫ�ص���һ��Ԫ�صĵ�����
    return Iterator(data + index);
  }

  // ɾ����start��end��Ԫ�أ�����start��������end
  Iterator erase(const Iterator start, const Iterator end) {
    if (start.ptr < data || end.ptr > data + size || start.ptr > end.ptr) {
      throw out_of_range("Iterator out of range");
    }
    const int erase_len = end - start;
    size_t index = start.ptr - data;
    for (size_t i = index; i < size - erase_len; ++i) {
      data[i] = data[i + erase_len];
    }
    size -= erase_len;
    return Iterator(data + index);
  }
};

// ��������Ԫ��
void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

// ��ӡ����
void DispArr(Vector<int>& arr) {
  for (size_t i = 0; i < arr.Size(); ++i) {
    cout << arr[i] << ' ';
  }
  cout << endl;
}

// ��ӡ����
void DispTitle() {
  cout << "------------------------------------" << endl;
  cout << "|           �����㷨�Ƚ�           |" << endl;
  cout << "|----------------------------------|" << endl;
  cout << "|           1--ð������            |" << endl;
  cout << "|           2--ѡ������            |" << endl;
  cout << "|           3--ֱ�Ӳ�������        |" << endl;
  cout << "|           4--ϣ������            |" << endl;
  cout << "|           5--��������            |" << endl;
  cout << "|           6--������              |" << endl;
  cout << "|           7--�鲢����            |" << endl;
  cout << "|           8--��������            |" << endl;
  cout << "|           9--�˳�����            |" << endl;
  cout << "------------------------------------" << endl;
  cout << endl;
}

// �����������
Vector<int> GeneRandomArr(const size_t len) {
  mt19937 rng(42); // �̶�����Ϊ42
  uniform_int_distribution<int> dist(0, len * 2);
  Vector<int> random_arr(len);
  for (size_t i = 0; i < len; ++i) {
    random_arr[i] = dist(rng);
  }
  return random_arr;
}

// ð������
long long PopSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // i���Ѿ��ź����Ԫ�صĸ���
  for (size_t i = 0; i < len - 1; ++i) {
    for (size_t j = 0; j < len - 1 - i; ++j) {
      basic_count++;
      if (arr[j] > arr[j + 1]) {
        Swap(arr[j], arr[j + 1]);
      }
    }
  }
  return basic_count;
}

// ѡ������
long long SelectSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // i���Ѿ��ź����Ԫ�صĸ���
  for (size_t i = 0; i < len - 1; ++i) {
    int min_index = i;
    for (size_t j = i + 1; j < len; ++j) {
      basic_count++;
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    Swap(arr[i], arr[min_index]);
  }
  return basic_count;
}

// ֱ�Ӳ�������
long long InsertSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // i���Ѿ��ź����Ԫ�ظ���
  for (int i = 1; i < len; ++i) {
    const int insert_element = arr[i]; // Ҫ�����Ԫ��
    int j = i;
    // �Ӻ���ǰ��������ǰλ�ô��ڲ���Ԫ��ʱ
    while (j >= 1 && arr[j - 1] > insert_element) {
      arr[j] = arr[j - 1]; // ������insert_element��Ԫ�غ���
      --j;
      basic_count++;
    }
    arr[j] = insert_element; // ��j������
  }
  return basic_count;
}

// ϣ������
long long ShellSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();

  // gap����������ʼֵΪ���鳤�ȵ�һ��
  for (int gap = len / 2; gap >= 1; gap /= 2) {\
    // ������λ�ÿ�ʼ�����λ�ý��в�������
    for (int i = gap; i < len; ++i) {
      int insert_element = arr[i]; // Ҫ�����Ԫ��
      int j = i;

      while (j >= gap && arr[j - gap] > insert_element) {
        arr[j] = arr[j - gap]; // j-gapλ��Ԫ�غ���gapλ
        j -= gap;
        basic_count++;
      }
      arr[j] = insert_element; // Ҫ�����Ԫ�ز�����j��
    }
  }
  return basic_count;
}

// ��������ķ�������
int Partition(Vector<int>& arr, int low, int high, long long& basic_count) {
  // ѡ�����һ��Ԫ����Ϊ����
  int pivot = arr[high];

  // ���һ��С������Ԫ�ص�λ��
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    basic_count++;
    if (arr[j] < pivot) {
      ++i;
      // С�������Ԫ���Ƶ����
      Swap(arr[i], arr[j]);
    }
  }
  // �����������ȷ��λ��
  Swap(arr[i + 1], arr[high]);
  return i + 1;
}

// ��������ĵݹ麯��
void QuickSortRecursive(Vector<int>& arr,int low, int high, long long& basic_count) {
  if (low < high) {
    int pivot_index = Partition(arr, low, high, basic_count);
    QuickSortRecursive(arr, low, pivot_index - 1, basic_count);
    QuickSortRecursive(arr, pivot_index + 1, high , basic_count);
  }
}

// ��������
long long QuickSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  int len = arr.Size();
  long long basic_count = 0;
  QuickSortRecursive(arr, 0, len - 1, basic_count);
  return basic_count;
}

// �ѻ�����
void Heapify(Vector<int>& arr, int n, int i, long long& basic_count) {
  // ����iΪ��������Ϊn����������Ϊ����
  int largest = i; // ��ʼ�����ֵΪ���ڵ�
  int left = 2 * i + 1; // ���ӽڵ�
  int right = 2 * i + 2; // ���ӽڵ�
  if (left <= n - 1 && arr[left] > arr[largest]) {
    largest = left;
  }
  if (right <= n - 1 && arr[right] > arr[largest]) {
    largest = right;
  }
  // ������ֵ���Ǹ��ڵ㣬��ô��Ҫ�������ֵ�͸��ڵ㣬���������¶ѻ�����
  if (largest != i) {
    basic_count++;
    Swap(arr[largest], arr[i]);
    Heapify(arr, n, largest, basic_count);
  }
}

// ������
long long HeapSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // ��ʼ���ѣ��ӵ�һ����Ҷ�ӽ��(��ΪҶ�ӽ����Ȼ�Ƕ�)��ʼ���������Ϲ�������
  for (int i = len / 2 - 1; i >= 0; --i) {
    // �ڵ����Ϊn����ȫ�������ĵ�һ����Ҷ�ӽ����n / 2 - 1
    Heapify(arr, len, i, basic_count);
  }

  // �𲽼��ٶѵ���Ч����i
  for (int i = len - 1; i > 0; --i) {
    // �Ѷ�Ԫ�غ�ĩβԪ�ؽ���
    Swap(arr[0], arr[i]);
    // ��ʣ��Ԫ�����½��жѻ�
    Heapify(arr, i, 0, basic_count);
  }
  return basic_count;
}

// �ϲ��������������飬[left...mid] �� [mid+1...right]
void Merge(Vector<int>& arr,int left, int mid, int right, long long& basic_count) {
  const int len1 = mid - left + 1; // ��������ĳ���
  const int len2 = right - (mid + 1) + 1; // ��������ĳ���

  // ����������ʱ�������洢����������
  Vector<int> left_arr(len1), right_arr(len2);
  // ����������������
  for (int i = 0; i < len1; ++i) {
    left_arr[i] = arr[left + i];
  }
  for (int i = 0; i < len2; ++i) {
    right_arr[i] = arr[mid + 1 + i];
  }

  int left_index = 0, right_index = 0;
  int k = left;
  while(left_index < len1 && right_index < len2) {
    if (left_arr[left_index] < right_arr[right_index]) {
      arr[k] = left_arr[left_index];
      ++left_index;
    }
    else {
      arr[k] = right_arr[right_index];
      ++right_index;
    }
    ++k;
  }

  // ʣ��ļӽ�ȥ
  while (left_index < len1) {
    arr[k] = left_arr[left_index];
    ++k;
    ++left_index;
  }
  while (right_index < len2) {
    arr[k] = right_arr[right_index];
    ++k;
    ++right_index;
  }
  basic_count += (len1 + len2) * 2;
}

// �鲢����ĵݹ麯��
void MergeSortRecursive(Vector<int>& arr, int left, int right, long long& basic_count) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    // ��������
    MergeSortRecursive(arr, left, mid, basic_count);
    // �����Ұ��
    MergeSortRecursive(arr, mid + 1, right, basic_count);
    // �ϲ�������������
    Merge(arr, left, mid, right, basic_count);
  }
}

// �鲢����
long long MergeSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  int len = arr.Size();
  long long basic_count = 0;
  MergeSortRecursive(arr, 0, len - 1, basic_count);
  return basic_count;
}

// ��ȡ�����е����ֵ
int GetMax(const Vector<int>& arr) {
  int max = arr[0];
  for (int num : arr)
    if (num > max)
      max = num;
  return max;
}

// ���ڵ�ǰλ���ļ�������
void CountSort(Vector<int>& arr, int exp, long long& basic_count) {
  int len = arr.Size();
  Vector<int> output(len); // �������
  int count[10] = { 0 };

  // ͳ�ƶ�Ӧλ�����ֵĴ���
  for (int i = 0; i < len; ++i) {
    count[(arr[i] / exp) % 10]++;
  }

  // ���¼������飬����λ����Ϣ
  for (int i = 1; i < 10; ++i) {
    count[i] += count[i - 1];
  }

  // ���򹹽��������
  for (int i = len - 1; i >= 0; --i) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  // �����������ƻ�ԭ����
  for (int i = 0; i < len; ++i) {
    arr[i] = output[i];
  }
  basic_count += len * 3 + 10;
}

// ����������
long long RadixSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  int max = GetMax(arr);
  
  for (int exp = 1; max / exp > 0; exp *= 10) {
    CountSort(arr, exp, basic_count);
  }
  return basic_count;
}

int main() {
  DispTitle();
  cout << "������Ҫ������������ĸ�����";
  int len;
  cin >> len;
  Vector<int> random_arr = GeneRandomArr(len);

#ifdef DISP
  DispArr(random_arr);
#endif

  while (1) {
    Vector<int> arr(random_arr);
    int choice;
    cout << endl << "��ѡ�������㷨��            ";
    cin >> choice;
    if (1 == choice) {
      clock_t start_time = clock();
      long long basic_count = PopSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "ð����������ʱ�䣺          " << setiosflags(ios::fixed) <<  setprecision(6) << spent_time << "��" << endl;
      cout << "ð�������������������      " << basic_count << "��" << endl;
    }
    else if (2 == choice) {
      clock_t start_time = clock();
      long long basic_count = SelectSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "ѡ����������ʱ�䣺          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "ѡ�������������������      " << basic_count << "��" << endl;
    }
    else if (3 == choice) {
      clock_t start_time = clock();
      long long basic_count = InsertSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "ֱ�Ӳ�����������ʱ�䣺      " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "ֱ�Ӳ��������������������  " << basic_count << "��" << endl;
    }
    else if (4 == choice) {
      clock_t start_time = clock();
      long long basic_count = ShellSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "ϣ����������ʱ�䣺          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "ϣ�������������������      " << basic_count << "��" << endl;
    }
    else if (5 == choice) {
      clock_t start_time = clock();
      long long basic_count = QuickSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "������������ʱ�䣺          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "���������������������      " << basic_count << "��" << endl;
    }
    else if (6 == choice) {
      clock_t start_time = clock();
      long long basic_count = HeapSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "����������ʱ�䣺            " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "�������������������        " << basic_count << "��" << endl;
    }
    else if (7 == choice) {
      clock_t start_time = clock();
      long long basic_count = MergeSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "�鲢��������ʱ�䣺          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "�鲢�����������������      " << basic_count << "��" << endl;
    }
    else if (8 == choice) {
      clock_t start_time = clock();
      long long basic_count = RadixSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "������������ʱ�䣺          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "��" << endl;
      cout << "���������������������      " << basic_count << "��" << endl;
    }
    else if (9 == choice){
      break;
    }

#ifdef DISP
    DispArr(arr);
#endif
  }

  return 0;
}