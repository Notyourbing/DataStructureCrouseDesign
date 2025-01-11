/*赵卓冰 2252750*/
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <cstring> // for memset
#include <ctime>
#include <climits>
// 迷宫的墙、空地、路径
#define MAZE_WALL 0
#define MAZE_BLANK 1
#define MAZE_PATH 2
// 条件编译，用于在windows和linux上运行，因为二者的字符宽度不同
#ifdef _WIN32
#include <conio.h>
const char* WALL = "■";
const char* START = "☆";
const char* END = "○";
const char* PATH = "·";
#else
#include <ncurses.h>
const char* WALL = "■ ";
const char* START = "☆ ";
const char* END = "○ ";
const char* PATH = "· ";
#endif

using namespace std;


// 位置结构体
struct Pos {
  int row; // 行
  int col; // 列

  // 重载 + 运算符，用于坐标相加
  Pos operator+(const Pos& other) const {
    return Pos{ row + other.row, col + other.col };
  }

  // 重载 - 运算符, 用于坐标相减
  Pos operator-(const Pos& other) const {
    return Pos{ row - other.row, col - other.col };
  }

  // 重载 / 运算符，用于对坐标整体除以一个数n
  Pos operator/(const int n) const {
    return Pos{ row / n, col / n };
  }

  // 重载 += 运算符，用于累加坐标
  Pos& operator+=(const Pos& other) {
    row += other.row;
    col += other.col;
    return *this;
  }

  // 重载 -= 运算符，用于累减坐标
  Pos& operator-=(const Pos& other) {
    row -= other.row;
    col -= other.col;
    return *this;
  }

  // 重载 == 运算符，用于比较两坐标是否相等
  bool operator==(const Pos& other) {
    return (row == other.row && col == other.col);
  }

  // 重载 << 运算符，用于输出坐标
  friend ostream& operator<<(ostream& os, const Pos& pos) {
    os << "(" << pos.row << ',' << pos.col << ")";
    return os;
  }
};

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
};

// 栈类
template <typename T>
class Stack {
private:
  T* arr;
  int top_index;
  int capacity;

public:
  Stack(int size = 10000) {
    capacity = size;
    arr = new T[capacity];
    top_index = -1;
  }

  ~Stack() {
    delete[] arr;
  }

  // 入栈
  void Push(const T& value) {
    if (top_index + 1 >= capacity) {
      // 动态扩展容量
      int new_capacity = capacity * 2;
      T* new_arr = new T[new_capacity];
      for (int i = 0; i < capacity; ++i) {
        new_arr[i] = arr[i];
      }
      delete[] arr;
      arr = new_arr;
      capacity = new_capacity;
    }
    arr[++top_index] = value;
  }

  // 出栈
  void Pop() {
    if (!Empty()) {
      --top_index;
    }
  }

  T Top() const {
    if (!Empty()) {
      return arr[top_index];
    }
    return T();
  }

  // 判断是否是空栈
  bool Empty() const {
    return (top_index == -1);
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

// 优先队列类（最小堆实现）
template <typename T, typename Compare>
class PriorityQueue {
private:
  T* data;
  size_t size;
  size_t capacity;
  Compare comp;

  void Resize() {
    size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
    T* new_data = new T[new_capacity];
    for (int i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
  }

  void HeapifyUp(size_t index) {
    while (index > 0) {
      size_t parent = (index - 1) / 2;
      if (comp(data[index], data[parent])) {
        swap(data[index], data[parent]);
        index = parent;
      }
      else {
        break;
      }
    }
  }

  void HeapifyDown(size_t index) {
    while (index * 2 + 1 < size) {
      size_t left = index * 2 + 1;
      size_t right = index * 2 + 2;
      size_t smallest = left;
      if (right < size && comp(data[right], data[left])) {
        smallest = right;
      }
      if (!comp(data[index], data[smallest])) {
        swap(data[index], data[smallest]);
        index = smallest;
      }
      else {
        break;
      }
    }
  }

public:
  PriorityQueue() : data(nullptr), size(0), capacity(0) {}

  ~PriorityQueue() {
    delete[] data;
  }

  void Push(const T& value) {
    if (size == capacity) {
      Resize();
    }
    data[size] = value;
    ++size;
    HeapifyUp(size - 1);
  }

  void Pop() {
    if (Empty()) {
      throw out_of_range("PriorityQueue is empty!");
    }
    data[0] = data[size - 1];
    --size;
    HeapifyDown(0);
  }

  const T& Top() const {
    if (Empty()) {
      throw out_of_range("PriorityQueue is empty!");
    }
    return data[0];
  }

  bool Empty() const {
    return (size == 0);
  }
};

// A*算法的节点
struct Node {
  Pos pos; // 当前位置
  int start_cost; // 从起点到当前位置的代价
  int end_cost; // 启发函数的值（当前位置到终点的估计代价）
  int sum_cost;

  Node(const Pos& position, int init_start_cost, int init_end_cost)
    : pos(position), start_cost(init_start_cost), end_cost(init_end_cost), sum_cost(start_cost + end_cost) {}

  Node() : pos{ 0,0 }, start_cost(0), end_cost(0), sum_cost(0) {}
};

// 优先队列的比较函数
struct NodeCompare {
  bool operator()(const Node& a, const Node& b) const {
    return a.sum_cost < b.sum_cost; // 基于最小堆
  }
};

// 曼哈顿距离
int Heuristic(const Pos& a, const Pos& b) {
  return abs(a.row - b.row) + abs(a.col - b.col);
}

// 迷宫类
class MAZE {
private:
  int height; // 迷宫的高
  int width; // 迷宫的宽
  int** field; // 存储迷宫的二维数组，0表示墙壁，1表示空地, 2表示走出迷宫的路

  // 起点和终点
  int start_row;
  int start_col;
  int end_row;
  int end_col;
  Vector<Pos> solution_path; // 自定义的vector类保存解路径

public:
  // 构造函数
  MAZE(int init_height, int init_width) {
    height = (init_height % 2 == 0) ? init_height + 1 : init_height;
    width = (init_width % 2 == 0) ? init_width + 1 : init_width;
    start_row = 1;
    start_col = 1;
    end_row = height - 2;
    end_col = width - 2;
    field = new int* [height]; // 创建指向指针的数组，每个指针指向一行
    for (int i = 0; i < height; ++i) {
      field[i] = new int[width]; // 为每一行分配一个列数组
      memset(field[i], 0, width * sizeof(int)); // 初始化所有位置都是墙壁
    }
  }

  // 析构函数
  ~MAZE() {
    for (int i = 0; i < height; ++i) {
      delete[] field[i]; // 释放每一行
    }
    delete[] field; // 释放行指针数组
  }

  // 打印迷宫
  void PrintMaze();

  // 生成随机迷宫
  void MakeRandomMaze();

  // 判断位置是否在迷宫边界内
  bool IsInBounds(const Pos& pos);

  // 回溯法的递归函数
  bool TraceBack(Pos current_pos, int** visit);

  // 回溯法解迷宫
  void SolveWithTraceBack();

  // 基于栈的DFS法解迷宫
  void SolveWithStack();

  // BFS法解迷宫
  void SolveWithQueue();

  // A星算法解迷宫
  void SolveWithAStar();

  // 打印解路径
  void PrintSolutionPath();

  // 清除路径，恢复为空地
  void ClearPath();
};

// 打印迷宫
void MAZE::PrintMaze() {
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (field[row][col] == MAZE_WALL) { // 如果是墙壁
        cout << WALL;
      }
      else { // 如果是空地
        if (start_row == row && start_col == col) {
          cout << START;
        }
        else if (end_row == row && end_col == col) {
          cout << END;
        }
        else if (field[row][col] == MAZE_PATH) { // 标记解路径
          cout << PATH;
        }
        else {
          cout << "  ";
        }
      }
    }
    cout << endl;
  }
}

// 生成随机迷宫，深度优先搜索算法
void MAZE::MakeRandomMaze() {
  // 定义四个方向，分别是上、下、左、右
  Pos directions[4] = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };

  field[start_row][start_col] = MAZE_BLANK; // 起点设置为空地

  // 创建栈来保存路径，栈中存储坐标
  Stack<Pos> stack;
  stack.Push({ start_row, start_col });

  // 深度搜索生成迷宫
  while (!stack.Empty()) {
    Pos current_pos = stack.Top();
    stack.Pop();

    // 打乱四个方向的顺序
    for (int i = 0; i < 4; ++i) {
      int random_index = rand() % 4;
      swap(directions[i], directions[random_index]);
    }

    // 尝试朝随机的方向走
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      Pos between_pos = current_pos + directions[i] / 2;

      // 检查新的位置是否在边界内
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_WALL) {
        // 把路径之间的墙壁打通
        field[between_pos.row][between_pos.col] = MAZE_BLANK;
        // 把新的位置设置为空地
        field[new_pos.row][new_pos.col] = MAZE_BLANK;

        // cout << "current_pos:" << current_pos << "-> new_pos:" << new_pos << endl;
        // 把当前位置和新位置都推入栈中
        stack.Push(current_pos);
        stack.Push(new_pos);
        break;
      }
    }
  }
}

// 判断pos是否在边界内
bool MAZE::IsInBounds(const Pos& pos) {
  return pos.row > 0 && pos.row < height - 1 && pos.col > 0 && pos.col < width - 1;
}

// 回溯法解迷宫的递归函数
bool MAZE::TraceBack(Pos current_pos, int** visit) {
  // 定义四个方向，分别是上、下、左、右
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

  if (current_pos.row == end_row && current_pos.col == end_col) {
    solution_path.PushBack(current_pos);
    return 1;
  }

  // 标记当前位置为已经访问
  visit[current_pos.row][current_pos.col] = 1;
  solution_path.PushBack(current_pos);

  // 尝试4个方向
  for (int i = 0; i < 4; ++i) {
    Pos new_pos = current_pos + directions[i];
    if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && visit[new_pos.row][new_pos.col] == 0) {
      if (TraceBack(new_pos, visit)) {
        return 1;
      }
    }
  }
  // 所有路都走不通，回溯
  solution_path.PopBack();
  return 0;
}

// 回溯法（递归）解迷宫
void MAZE::SolveWithTraceBack() {
  // 清除路径和解路径
  ClearPath();
  solution_path.Clear();
  // 初始化访问数组
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // 初始化为0，表示未访问
  }

  if (TraceBack({ start_row, start_col }, visit)) {
    for (int i = 0; i < solution_path.Size(); ++i) {
      field[solution_path[i].row][solution_path[i].col] = MAZE_PATH;
    }
    PrintMaze();
    cout << endl << "解路径为:" << endl;
    PrintSolutionPath();
  }
  else {
    cout << "没有解" << endl;
  }
  // 释放visit内存
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
  }
  delete[] visit;
}

// 基于栈的DFS法解迷宫
void MAZE::SolveWithStack() {
  // 清除路径
  ClearPath();
  // 定义四个方向，分别是上、下、左、右
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
  // 初始化访问数组
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // 初始化为0， 表示未访问
  }

  Stack<Pos> stack; // 递归栈
  stack.Push({ start_row, start_col });
  visit[start_row][start_col] = 1; // 标记起始点为已访问
  while (!stack.Empty()) {
    Pos current_pos = stack.Top();
    // 如果到达了终点
    if (current_pos.row == end_row && current_pos.col == end_col) {
      solution_path.Clear();
      while (!stack.Empty()) {
        solution_path.PushBack(stack.Top());
        field[stack.Top().row][stack.Top().col] = MAZE_PATH;
        stack.Pop();
      }
      solution_path.Reverse(); // 由于是不断从栈顶push_back进solution_path,所以要reverse
      PrintMaze();
      cout << endl << "解路径为:" << endl;
      PrintSolutionPath();
      // 释放visit内存
      for (int i = 0; i < height; ++i) {
        delete[] visit[i];
      }
      delete[] visit;
      return;
    }

    bool is_found = 0; // 是否找到了可以走的位置
    // 遍历上下左右四个方向
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      // 如果在边界内，且为空地，且没有被访问过
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && !visit[new_pos.row][new_pos.col]) {
        is_found = 1; // 标记为找到了可以走的位置
        visit[new_pos.row][new_pos.col] = 1; // 标记新的点为已访问
        stack.Push(new_pos); // 新位置入栈
        break;
      }
    }
    // 如果四个方向都不能走，也就是没有可以走的位置，回溯
    if (!is_found) {
      stack.Pop();
    }
  }

  if (stack.Empty()) {
    cout << "没有解" << endl;
  }
  // 释放visit内存
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
  }
  delete[] visit;
}

// 基于队列的BFS法解迷宫
void MAZE::SolveWithQueue() {
  // 清除路径
  ClearPath();
  // 定义四个方向，分别是上、下、左、右
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
  // 初始化访问数组
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // 初始化为0， 表示未访问
  }
  // 初始化前驱节点数组
  Pos** pre = new Pos * [height];
  for (int i = 0; i < height; ++i) {
    pre[i] = new Pos[width];
    for (int j = 0; j < width; ++j) {
      pre[i][j] = { -1, -1 }; // 初始化为-1，-1表示没有前驱节点
    }
  }

  Queue<Pos> queue; // bfs搜索队列
  queue.Push({ start_row, start_col }); // 起始点入栈
  visit[start_row][start_col] = 1; // 标记起点为已访问

  while (!queue.Empty()) {
    Pos current_pos = queue.Front(); // 取队首元素

    // 如果当前位置是终点
    if (current_pos.row == end_row && current_pos.col == end_col) {
      solution_path.Clear(); // 清除解路径
      while (1) {
        // 如果当前节点没有前驱节点（也就是当前节点是起始位置的前驱结点）
        if (current_pos.row == -1 && current_pos.col == -1) {
          break;
        }
        solution_path.PushBack(current_pos);
        field[current_pos.row][current_pos.col] = MAZE_PATH;
        current_pos = pre[current_pos.row][current_pos.col]; // 不断更新当前节点为前驱节点
      }

      solution_path.Reverse();
      PrintMaze();
      cout << endl << "解路径为:" << endl;
      PrintSolutionPath();

      // 释放visit和pre内存
      for (int i = 0; i < height; ++i) {
        delete[] visit[i];
      }
      delete[] visit;
      for (int i = 0; i < height; ++i) {
        delete[] pre[i];
      }
      delete[] pre;
      return;
    }

    queue.Pop(); // 队首元素出队
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && !visit[new_pos.row][new_pos.col]) {
        queue.Push(new_pos); // 新位置入队
        visit[new_pos.row][new_pos.col] = 1; // 标记为已访问
        pre[new_pos.row][new_pos.col] = current_pos; // 当前位置是新位置的前驱结点
      }
    }

  }

  if (queue.Empty()) {
    cout << "没有解" << endl;
  }
  // 释放visit和pre内存
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
  }
  delete[] visit;
  for (int i = 0; i < height; ++i) {
    delete[] pre[i];
  }
  delete[] pre;
}

// A星算法解迷宫
void MAZE::SolveWithAStar() {
  // 清除路径
  ClearPath();
  // 定义四个方向，分别是上、下、左、右
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
  // 初始化访问数组
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // 初始化为0， 表示未访问
  }
  // 初始化前驱节点数组
  Pos** pre = new Pos * [height];
  for (int i = 0; i < height; ++i) {
    pre[i] = new Pos[width];
    for (int j = 0; j < width; ++j) {
      pre[i][j] = { -1, -1 }; // 初始化为-1，-1表示没有前驱节点
    }
  }

  // 初始化起点代价数组
  int** start_costs = new int* [height];
  for (int i = 0; i < height; ++i) {
    start_costs[i] = new int[width];
    for (int j = 0; j < width; ++j) {
      start_costs[i][j] = INT_MAX;
    }
  }

  const Pos start_pos = { start_row, start_col };
  const Pos end_pos = { end_row, end_col };
  int end_cost = Heuristic(start_pos, end_pos);
  Node start_node(start_pos, 0, end_cost);

  PriorityQueue<Node, NodeCompare> p_queue; // 优先队列
  p_queue.Push(start_node); // 起始点入队
  start_costs[start_pos.row][start_pos.col] = 0; // 起始点的start_cost为0
  visit[start_pos.row][start_pos.col] = 1; // 标记为已访问

  // 当优先队列非空
  while (!p_queue.Empty()) {
    Node current_node = p_queue.Top(); // 取队首节点
    Pos current_pos = current_node.pos;
    // 如果当前节点是终点
    if (current_pos == end_pos) {
      solution_path.Clear(); // 清除解路径
      while (1) {
        // 如果当前节点没有前驱节点（也就是当前节点是起始位置的前驱结点）
        if (current_pos.row == -1 && current_pos.col == -1) {
          break;
        }
        solution_path.PushBack(current_pos);
        field[current_pos.row][current_pos.col] = MAZE_PATH;
        current_pos = pre[current_pos.row][current_pos.col]; // 不断更新当前节点为前驱节点
      }

      solution_path.Reverse();
      PrintMaze();
      cout << endl << "解路径为:" << endl;
      PrintSolutionPath();

      // 释放visit和pre和start_costs内存
      for (int i = 0; i < height; ++i) {
        delete[] visit[i];
        delete[] pre[i];
        delete[] start_costs[i];
      }
      delete[] visit;
      delete[] pre;
      delete[] start_costs;
      return;
    }

    p_queue.Pop(); // 队首元素出队
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && !visit[new_pos.row][new_pos.col]) {
        const int new_start_cost = current_node.start_cost + 1;
        if (new_start_cost < start_costs[new_pos.row][new_pos.col]) {
          // 更新新节点的起点代价
          start_costs[new_pos.row][new_pos.col] = new_start_cost;
          // 计算曼哈顿距离
          const int new_end_cost = Heuristic(new_pos, end_pos);
          const Node new_node(new_pos, new_start_cost, new_end_cost);
          p_queue.Push(new_node); // 入队
          visit[new_pos.row][new_pos.col] = 1; // 标记为已经访问
          pre[new_pos.row][new_pos.col] = current_pos; // 记录前驱节点
        }
      }
    }
  }

  if (p_queue.Empty()) {
    cout << "没有解" << endl;
  }
  // 释放visit和pre和start_costs内存
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
    delete[] pre[i];
    delete[] start_costs[i];
  }
  delete[] visit;
  delete[] pre;
  delete[] start_costs;
}

// 打印解路径
void MAZE::PrintSolutionPath() {
  cout << "解路径: ";
  for (int i = 0; i < solution_path.Size(); ++i) {
    cout << solution_path[i];
    if (i != solution_path.Size() - 1) {
      cout << " -> ";
    }
  }
  cout << endl;
}

// 清除路径，恢复为空地
void MAZE::ClearPath() {
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (field[row][col] == MAZE_PATH) {
        field[row][col] = MAZE_BLANK;
      }
    }
  }
}

// 输入迷宫的高和宽
void InputSize(int& height, int& width) {
  cout << "请输入迷宫的高度[5-99]：" << endl;
  cin >> height;
  while (cin.fail() || height < 5 || height > 99) {
    cout << "高度输入非法,请重新输入高度：" << endl;
    cin.clear();
    cin.ignore(65535, '\n');
    cin >> height;
  }

  cout << "请输入迷宫的宽度[5-99]：" << endl;
  cin >> width;
  while (cin.fail() || width < 5 || width > 99) {
    cout << "宽度输入非法,请重新输入宽度：" << endl;
    cin.clear();
    cin.ignore(65535, '\n');
    cin >> width;
  }
}


int main() {
  srand(time(0));  // 初始化随机种子
  int height, width;
  InputSize(height, width); // 输入迷宫的高度和宽度

  MAZE maze(height, width); // 迷宫实例
  maze.MakeRandomMaze(); // 生成随机迷宫
  maze.PrintMaze(); // 打印迷宫

  while (1) {
    cout << "请选择迷宫算法：[1]回溯法(递归)    [2]DFS法(栈)    [3]BFS法    [4]A星算法    [0]退出" << endl;
    int choice;
    cin >> choice;
    while (cin.fail() || choice < 0 || choice > 4) {
      cout << "输入非法，请重新输入" << endl;
      cin >> choice;
    }
    if (choice == 0) {
      cout << "程序成功退出！" << endl;
      break;
    }
    else if (choice == 1) {
      maze.SolveWithTraceBack();
    }
    else if (choice == 2) {
      maze.SolveWithStack();
    }
    else if (choice == 3) {
      maze.SolveWithQueue();
    }
    else {
      maze.SolveWithAStar();
    }
  }

  cout << endl << "按回车键退出..." << endl;
  #ifdef _WIN32
    while (_getch() != '\r')
      continue;
  #elif __linux__
    char ch;
    do {
      initscr();
      noecho();
      cbreak();
      ch = getch();
      endwin();
    } while (ch != '\n');
  #endif
  return 0;
}