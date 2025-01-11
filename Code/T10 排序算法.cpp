/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <random>
#include <ctime>
#include <stdexcept>
#include <iomanip>
// 条件编译，解决window和linux的差异
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

// 取消下面的注释可以展示排序前后的数组
// #define DISP


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

  const T& operator[](size_t index) const {
    return data[index];
  }

  class Iterator {
  private:
    T* ptr;

  public:
    Iterator(T* p) : ptr(p) {}

    //  解引用操作符
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

  // 删除index的元素
  void erase(const size_t index) {
    if (index >= size) {
      throw out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
      data[i] = data[i + 1];
    }
    --size;
  }

  // 删除position指向的元素
  Iterator erase(const Iterator position) {
    // 检查迭代器是否在有效范围内
    if (position.ptr < data || position.ptr >= data + size) {
      throw out_of_range("Iterator out of range");
    }
    // 计算要删除位置的偏移量
    size_t index = position.ptr - data;
    for (size_t i = index; i < size - 1; ++i) {
      data[i] = data[i + 1];
    }
    --size;
    // 返回删除元素的下一个元素的迭代器
    return Iterator(data + index);
  }

  // 删除从start到end的元素，包含start，不包含end
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

// 交换两个元素
void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

// 打印数组
void DispArr(Vector<int>& arr) {
  for (size_t i = 0; i < arr.Size(); ++i) {
    cout << arr[i] << ' ';
  }
  cout << endl;
}

// 打印标题
void DispTitle() {
  cout << "------------------------------------" << endl;
  cout << "|           排序算法比较           |" << endl;
  cout << "|----------------------------------|" << endl;
  cout << "|           1--冒泡排序            |" << endl;
  cout << "|           2--选择排序            |" << endl;
  cout << "|           3--直接插入排序        |" << endl;
  cout << "|           4--希尔排序            |" << endl;
  cout << "|           5--快速排序            |" << endl;
  cout << "|           6--堆排序              |" << endl;
  cout << "|           7--归并排序            |" << endl;
  cout << "|           8--基数排序            |" << endl;
  cout << "|           9--退出程序            |" << endl;
  cout << "------------------------------------" << endl;
  cout << endl;
}

// 产生随机数组
Vector<int> GeneRandomArr(const size_t len) {
  mt19937 rng(42); // 固定种子为42
  uniform_int_distribution<int> dist(0, len * 2);
  Vector<int> random_arr(len);
  for (size_t i = 0; i < len; ++i) {
    random_arr[i] = dist(rng);
  }
  return random_arr;
}

// 冒泡排序
long long PopSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // i是已经排好序的元素的个数
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

// 选择排序
long long SelectSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // i是已经排好序的元素的个数
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

// 直接插入排序
long long InsertSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // i是已经排好序的元素个数
  for (int i = 1; i < len; ++i) {
    const int insert_element = arr[i]; // 要插入的元素
    int j = i;
    // 从后向前遍历，当前位置大于插入元素时
    while (j >= 1 && arr[j - 1] > insert_element) {
      arr[j] = arr[j - 1]; // 将大于insert_element的元素后移
      --j;
      basic_count++;
    }
    arr[j] = insert_element; // 在j处插入
  }
  return basic_count;
}

// 希尔排序
long long ShellSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();

  // gap是增量，初始值为数组长度的一半
  for (int gap = len / 2; gap >= 1; gap /= 2) {\
    // 从增量位置开始，逐个位置进行插入排序
    for (int i = gap; i < len; ++i) {
      int insert_element = arr[i]; // 要插入的元素
      int j = i;

      while (j >= gap && arr[j - gap] > insert_element) {
        arr[j] = arr[j - gap]; // j-gap位置元素后移gap位
        j -= gap;
        basic_count++;
      }
      arr[j] = insert_element; // 要插入的元素插入在j处
    }
  }
  return basic_count;
}

// 快速排序的分区函数
int Partition(Vector<int>& arr, int low, int high, long long& basic_count) {
  // 选择最后一个元素作为枢轴
  int pivot = arr[high];

  // 最后一个小于枢轴元素的位置
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    basic_count++;
    if (arr[j] < pivot) {
      ++i;
      // 小于枢轴的元素移到左侧
      Swap(arr[i], arr[j]);
    }
  }
  // 将枢轴放在正确的位置
  Swap(arr[i + 1], arr[high]);
  return i + 1;
}

// 快速排序的递归函数
void QuickSortRecursive(Vector<int>& arr,int low, int high, long long& basic_count) {
  if (low < high) {
    int pivot_index = Partition(arr, low, high, basic_count);
    QuickSortRecursive(arr, low, pivot_index - 1, basic_count);
    QuickSortRecursive(arr, pivot_index + 1, high , basic_count);
  }
}

// 快速排序
long long QuickSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  int len = arr.Size();
  long long basic_count = 0;
  QuickSortRecursive(arr, 0, len - 1, basic_count);
  return basic_count;
}

// 堆化函数
void Heapify(Vector<int>& arr, int n, int i, long long& basic_count) {
  // 将以i为根，长度为n的子树调整为最大堆
  int largest = i; // 初始化最大值为根节点
  int left = 2 * i + 1; // 左子节点
  int right = 2 * i + 2; // 右子节点
  if (left <= n - 1 && arr[left] > arr[largest]) {
    largest = left;
  }
  if (right <= n - 1 && arr[right] > arr[largest]) {
    largest = right;
  }
  // 如果最大值不是根节点，那么需要交换大的值和根节点，并继续向下堆化子树
  if (largest != i) {
    basic_count++;
    Swap(arr[largest], arr[i]);
    Heapify(arr, n, largest, basic_count);
  }
}

// 堆排序
long long HeapSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  long long basic_count = 0;
  size_t len = arr.Size();
  // 初始化堆，从第一个非叶子结点(因为叶子结点天然是堆)开始，从下向上构建最大堆
  for (int i = len / 2 - 1; i >= 0; --i) {
    // 节点个数为n的完全二叉树的第一个非叶子结点是n / 2 - 1
    Heapify(arr, len, i, basic_count);
  }

  // 逐步减少堆的有效长度i
  for (int i = len - 1; i > 0; --i) {
    // 堆顶元素和末尾元素交换
    Swap(arr[0], arr[i]);
    // 对剩余元素重新进行堆化
    Heapify(arr, i, 0, basic_count);
  }
  return basic_count;
}

// 合并左右两个子数组，[left...mid] 和 [mid+1...right]
void Merge(Vector<int>& arr,int left, int mid, int right, long long& basic_count) {
  const int len1 = mid - left + 1; // 左子数组的长度
  const int len2 = right - (mid + 1) + 1; // 右子数组的长度

  // 创建两个临时数组来存储左右子数组
  Vector<int> left_arr(len1), right_arr(len2);
  // 拷贝到左右子数组
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

  // 剩余的加进去
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

// 归并排序的递归函数
void MergeSortRecursive(Vector<int>& arr, int left, int right, long long& basic_count) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    // 排序左半边
    MergeSortRecursive(arr, left, mid, basic_count);
    // 排序右半边
    MergeSortRecursive(arr, mid + 1, right, basic_count);
    // 合并左右两个数组
    Merge(arr, left, mid, right, basic_count);
  }
}

// 归并排序
long long MergeSort(Vector<int>& arr) {
  if (arr.Empty()) {
    return -1;
  }
  int len = arr.Size();
  long long basic_count = 0;
  MergeSortRecursive(arr, 0, len - 1, basic_count);
  return basic_count;
}

// 获取数组中的最大值
int GetMax(const Vector<int>& arr) {
  int max = arr[0];
  for (int num : arr)
    if (num > max)
      max = num;
  return max;
}

// 基于当前位数的计数排序
void CountSort(Vector<int>& arr, int exp, long long& basic_count) {
  int len = arr.Size();
  Vector<int> output(len); // 输出数组
  int count[10] = { 0 };

  // 统计对应位数出现的次数
  for (int i = 0; i < len; ++i) {
    count[(arr[i] / exp) % 10]++;
  }

  // 更新计数数组，包含位置信息
  for (int i = 1; i < 10; ++i) {
    count[i] += count[i - 1];
  }

  // 逆序构建输出数组
  for (int i = len - 1; i >= 0; --i) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  // 将排序结果复制回原数组
  for (int i = 0; i < len; ++i) {
    arr[i] = output[i];
  }
  basic_count += len * 3 + 10;
}

// 基数排序函数
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
  cout << "请输入要产生的随机数的个数：";
  int len;
  cin >> len;
  Vector<int> random_arr = GeneRandomArr(len);

#ifdef DISP
  DispArr(random_arr);
#endif

  while (1) {
    Vector<int> arr(random_arr);
    int choice;
    cout << endl << "请选择排序算法：            ";
    cin >> choice;
    if (1 == choice) {
      clock_t start_time = clock();
      long long basic_count = PopSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "冒泡排序所用时间：          " << setiosflags(ios::fixed) <<  setprecision(6) << spent_time << "秒" << endl;
      cout << "冒泡排序基础操作次数：      " << basic_count << "次" << endl;
    }
    else if (2 == choice) {
      clock_t start_time = clock();
      long long basic_count = SelectSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "选择排序所用时间：          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "选择排序基础操作次数：      " << basic_count << "次" << endl;
    }
    else if (3 == choice) {
      clock_t start_time = clock();
      long long basic_count = InsertSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "直接插入排序所用时间：      " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "直接插入排序基础操作次数：  " << basic_count << "次" << endl;
    }
    else if (4 == choice) {
      clock_t start_time = clock();
      long long basic_count = ShellSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "希尔排序所用时间：          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "希尔排序基础操作次数：      " << basic_count << "次" << endl;
    }
    else if (5 == choice) {
      clock_t start_time = clock();
      long long basic_count = QuickSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "快速排序所用时间：          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "快速排序基础操作次数：      " << basic_count << "次" << endl;
    }
    else if (6 == choice) {
      clock_t start_time = clock();
      long long basic_count = HeapSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "堆排序所用时间：            " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "堆排序基础操作次数：        " << basic_count << "次" << endl;
    }
    else if (7 == choice) {
      clock_t start_time = clock();
      long long basic_count = MergeSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "归并排序所用时间：          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "归并排序基础操作次数：      " << basic_count << "次" << endl;
    }
    else if (8 == choice) {
      clock_t start_time = clock();
      long long basic_count = RadixSort(arr);
      double spent_time = (clock() - start_time) * 1.0 / CLOCKS_PER_SEC;
      cout << "基数排序所用时间：          " << setiosflags(ios::fixed) << setprecision(6) << spent_time << "秒" << endl;
      cout << "基数排序基础操作次数：      " << basic_count << "次" << endl;
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