/*��׿�� 2252750*/
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <cstring> // for memset
#include <ctime>
#include <climits>
// �Թ���ǽ���յء�·��
#define MAZE_WALL 0
#define MAZE_BLANK 1
#define MAZE_PATH 2
// �������룬������windows��linux�����У���Ϊ���ߵ��ַ���Ȳ�ͬ
#ifdef _WIN32
#include <conio.h>
const char* WALL = "��";
const char* START = "��";
const char* END = "��";
const char* PATH = "��";
#else
#include <ncurses.h>
const char* WALL = "�� ";
const char* START = "�� ";
const char* END = "�� ";
const char* PATH = "�� ";
#endif

using namespace std;


// λ�ýṹ��
struct Pos {
  int row; // ��
  int col; // ��

  // ���� + ������������������
  Pos operator+(const Pos& other) const {
    return Pos{ row + other.row, col + other.col };
  }

  // ���� - �����, �����������
  Pos operator-(const Pos& other) const {
    return Pos{ row - other.row, col - other.col };
  }

  // ���� / ����������ڶ������������һ����n
  Pos operator/(const int n) const {
    return Pos{ row / n, col / n };
  }

  // ���� += ������������ۼ�����
  Pos& operator+=(const Pos& other) {
    row += other.row;
    col += other.col;
    return *this;
  }

  // ���� -= ������������ۼ�����
  Pos& operator-=(const Pos& other) {
    row -= other.row;
    col -= other.col;
    return *this;
  }

  // ���� == ����������ڱȽ��������Ƿ����
  bool operator==(const Pos& other) {
    return (row == other.row && col == other.col);
  }

  // ���� << ������������������
  friend ostream& operator<<(ostream& os, const Pos& pos) {
    os << "(" << pos.row << ',' << pos.col << ")";
    return os;
  }
};

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
};

// ջ��
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

  // ��ջ
  void Push(const T& value) {
    if (top_index + 1 >= capacity) {
      // ��̬��չ����
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

  // ��ջ
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

  // �ж��Ƿ��ǿ�ջ
  bool Empty() const {
    return (top_index == -1);
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

// ���ȶ����ࣨ��С��ʵ�֣�
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

// A*�㷨�Ľڵ�
struct Node {
  Pos pos; // ��ǰλ��
  int start_cost; // ����㵽��ǰλ�õĴ���
  int end_cost; // ����������ֵ����ǰλ�õ��յ�Ĺ��ƴ��ۣ�
  int sum_cost;

  Node(const Pos& position, int init_start_cost, int init_end_cost)
    : pos(position), start_cost(init_start_cost), end_cost(init_end_cost), sum_cost(start_cost + end_cost) {}

  Node() : pos{ 0,0 }, start_cost(0), end_cost(0), sum_cost(0) {}
};

// ���ȶ��еıȽϺ���
struct NodeCompare {
  bool operator()(const Node& a, const Node& b) const {
    return a.sum_cost < b.sum_cost; // ������С��
  }
};

// �����پ���
int Heuristic(const Pos& a, const Pos& b) {
  return abs(a.row - b.row) + abs(a.col - b.col);
}

// �Թ���
class MAZE {
private:
  int height; // �Թ��ĸ�
  int width; // �Թ��Ŀ�
  int** field; // �洢�Թ��Ķ�ά���飬0��ʾǽ�ڣ�1��ʾ�յ�, 2��ʾ�߳��Թ���·

  // �����յ�
  int start_row;
  int start_col;
  int end_row;
  int end_col;
  Vector<Pos> solution_path; // �Զ����vector�ౣ���·��

public:
  // ���캯��
  MAZE(int init_height, int init_width) {
    height = (init_height % 2 == 0) ? init_height + 1 : init_height;
    width = (init_width % 2 == 0) ? init_width + 1 : init_width;
    start_row = 1;
    start_col = 1;
    end_row = height - 2;
    end_col = width - 2;
    field = new int* [height]; // ����ָ��ָ������飬ÿ��ָ��ָ��һ��
    for (int i = 0; i < height; ++i) {
      field[i] = new int[width]; // Ϊÿһ�з���һ��������
      memset(field[i], 0, width * sizeof(int)); // ��ʼ������λ�ö���ǽ��
    }
  }

  // ��������
  ~MAZE() {
    for (int i = 0; i < height; ++i) {
      delete[] field[i]; // �ͷ�ÿһ��
    }
    delete[] field; // �ͷ���ָ������
  }

  // ��ӡ�Թ�
  void PrintMaze();

  // ��������Թ�
  void MakeRandomMaze();

  // �ж�λ���Ƿ����Թ��߽���
  bool IsInBounds(const Pos& pos);

  // ���ݷ��ĵݹ麯��
  bool TraceBack(Pos current_pos, int** visit);

  // ���ݷ����Թ�
  void SolveWithTraceBack();

  // ����ջ��DFS�����Թ�
  void SolveWithStack();

  // BFS�����Թ�
  void SolveWithQueue();

  // A���㷨���Թ�
  void SolveWithAStar();

  // ��ӡ��·��
  void PrintSolutionPath();

  // ���·�����ָ�Ϊ�յ�
  void ClearPath();
};

// ��ӡ�Թ�
void MAZE::PrintMaze() {
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (field[row][col] == MAZE_WALL) { // �����ǽ��
        cout << WALL;
      }
      else { // ����ǿյ�
        if (start_row == row && start_col == col) {
          cout << START;
        }
        else if (end_row == row && end_col == col) {
          cout << END;
        }
        else if (field[row][col] == MAZE_PATH) { // ��ǽ�·��
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

// ��������Թ���������������㷨
void MAZE::MakeRandomMaze() {
  // �����ĸ����򣬷ֱ����ϡ��¡�����
  Pos directions[4] = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };

  field[start_row][start_col] = MAZE_BLANK; // �������Ϊ�յ�

  // ����ջ������·����ջ�д洢����
  Stack<Pos> stack;
  stack.Push({ start_row, start_col });

  // ������������Թ�
  while (!stack.Empty()) {
    Pos current_pos = stack.Top();
    stack.Pop();

    // �����ĸ������˳��
    for (int i = 0; i < 4; ++i) {
      int random_index = rand() % 4;
      swap(directions[i], directions[random_index]);
    }

    // ���Գ�����ķ�����
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      Pos between_pos = current_pos + directions[i] / 2;

      // ����µ�λ���Ƿ��ڱ߽���
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_WALL) {
        // ��·��֮���ǽ�ڴ�ͨ
        field[between_pos.row][between_pos.col] = MAZE_BLANK;
        // ���µ�λ������Ϊ�յ�
        field[new_pos.row][new_pos.col] = MAZE_BLANK;

        // cout << "current_pos:" << current_pos << "-> new_pos:" << new_pos << endl;
        // �ѵ�ǰλ�ú���λ�ö�����ջ��
        stack.Push(current_pos);
        stack.Push(new_pos);
        break;
      }
    }
  }
}

// �ж�pos�Ƿ��ڱ߽���
bool MAZE::IsInBounds(const Pos& pos) {
  return pos.row > 0 && pos.row < height - 1 && pos.col > 0 && pos.col < width - 1;
}

// ���ݷ����Թ��ĵݹ麯��
bool MAZE::TraceBack(Pos current_pos, int** visit) {
  // �����ĸ����򣬷ֱ����ϡ��¡�����
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

  if (current_pos.row == end_row && current_pos.col == end_col) {
    solution_path.PushBack(current_pos);
    return 1;
  }

  // ��ǵ�ǰλ��Ϊ�Ѿ�����
  visit[current_pos.row][current_pos.col] = 1;
  solution_path.PushBack(current_pos);

  // ����4������
  for (int i = 0; i < 4; ++i) {
    Pos new_pos = current_pos + directions[i];
    if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && visit[new_pos.row][new_pos.col] == 0) {
      if (TraceBack(new_pos, visit)) {
        return 1;
      }
    }
  }
  // ����·���߲�ͨ������
  solution_path.PopBack();
  return 0;
}

// ���ݷ����ݹ飩���Թ�
void MAZE::SolveWithTraceBack() {
  // ���·���ͽ�·��
  ClearPath();
  solution_path.Clear();
  // ��ʼ����������
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // ��ʼ��Ϊ0����ʾδ����
  }

  if (TraceBack({ start_row, start_col }, visit)) {
    for (int i = 0; i < solution_path.Size(); ++i) {
      field[solution_path[i].row][solution_path[i].col] = MAZE_PATH;
    }
    PrintMaze();
    cout << endl << "��·��Ϊ:" << endl;
    PrintSolutionPath();
  }
  else {
    cout << "û�н�" << endl;
  }
  // �ͷ�visit�ڴ�
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
  }
  delete[] visit;
}

// ����ջ��DFS�����Թ�
void MAZE::SolveWithStack() {
  // ���·��
  ClearPath();
  // �����ĸ����򣬷ֱ����ϡ��¡�����
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
  // ��ʼ����������
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // ��ʼ��Ϊ0�� ��ʾδ����
  }

  Stack<Pos> stack; // �ݹ�ջ
  stack.Push({ start_row, start_col });
  visit[start_row][start_col] = 1; // �����ʼ��Ϊ�ѷ���
  while (!stack.Empty()) {
    Pos current_pos = stack.Top();
    // ����������յ�
    if (current_pos.row == end_row && current_pos.col == end_col) {
      solution_path.Clear();
      while (!stack.Empty()) {
        solution_path.PushBack(stack.Top());
        field[stack.Top().row][stack.Top().col] = MAZE_PATH;
        stack.Pop();
      }
      solution_path.Reverse(); // �����ǲ��ϴ�ջ��push_back��solution_path,����Ҫreverse
      PrintMaze();
      cout << endl << "��·��Ϊ:" << endl;
      PrintSolutionPath();
      // �ͷ�visit�ڴ�
      for (int i = 0; i < height; ++i) {
        delete[] visit[i];
      }
      delete[] visit;
      return;
    }

    bool is_found = 0; // �Ƿ��ҵ��˿����ߵ�λ��
    // �������������ĸ�����
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      // ����ڱ߽��ڣ���Ϊ�յأ���û�б����ʹ�
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && !visit[new_pos.row][new_pos.col]) {
        is_found = 1; // ���Ϊ�ҵ��˿����ߵ�λ��
        visit[new_pos.row][new_pos.col] = 1; // ����µĵ�Ϊ�ѷ���
        stack.Push(new_pos); // ��λ����ջ
        break;
      }
    }
    // ����ĸ����򶼲����ߣ�Ҳ����û�п����ߵ�λ�ã�����
    if (!is_found) {
      stack.Pop();
    }
  }

  if (stack.Empty()) {
    cout << "û�н�" << endl;
  }
  // �ͷ�visit�ڴ�
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
  }
  delete[] visit;
}

// ���ڶ��е�BFS�����Թ�
void MAZE::SolveWithQueue() {
  // ���·��
  ClearPath();
  // �����ĸ����򣬷ֱ����ϡ��¡�����
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
  // ��ʼ����������
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // ��ʼ��Ϊ0�� ��ʾδ����
  }
  // ��ʼ��ǰ���ڵ�����
  Pos** pre = new Pos * [height];
  for (int i = 0; i < height; ++i) {
    pre[i] = new Pos[width];
    for (int j = 0; j < width; ++j) {
      pre[i][j] = { -1, -1 }; // ��ʼ��Ϊ-1��-1��ʾû��ǰ���ڵ�
    }
  }

  Queue<Pos> queue; // bfs��������
  queue.Push({ start_row, start_col }); // ��ʼ����ջ
  visit[start_row][start_col] = 1; // ������Ϊ�ѷ���

  while (!queue.Empty()) {
    Pos current_pos = queue.Front(); // ȡ����Ԫ��

    // �����ǰλ�����յ�
    if (current_pos.row == end_row && current_pos.col == end_col) {
      solution_path.Clear(); // �����·��
      while (1) {
        // �����ǰ�ڵ�û��ǰ���ڵ㣨Ҳ���ǵ�ǰ�ڵ�����ʼλ�õ�ǰ����㣩
        if (current_pos.row == -1 && current_pos.col == -1) {
          break;
        }
        solution_path.PushBack(current_pos);
        field[current_pos.row][current_pos.col] = MAZE_PATH;
        current_pos = pre[current_pos.row][current_pos.col]; // ���ϸ��µ�ǰ�ڵ�Ϊǰ���ڵ�
      }

      solution_path.Reverse();
      PrintMaze();
      cout << endl << "��·��Ϊ:" << endl;
      PrintSolutionPath();

      // �ͷ�visit��pre�ڴ�
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

    queue.Pop(); // ����Ԫ�س���
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && !visit[new_pos.row][new_pos.col]) {
        queue.Push(new_pos); // ��λ�����
        visit[new_pos.row][new_pos.col] = 1; // ���Ϊ�ѷ���
        pre[new_pos.row][new_pos.col] = current_pos; // ��ǰλ������λ�õ�ǰ�����
      }
    }

  }

  if (queue.Empty()) {
    cout << "û�н�" << endl;
  }
  // �ͷ�visit��pre�ڴ�
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
  }
  delete[] visit;
  for (int i = 0; i < height; ++i) {
    delete[] pre[i];
  }
  delete[] pre;
}

// A���㷨���Թ�
void MAZE::SolveWithAStar() {
  // ���·��
  ClearPath();
  // �����ĸ����򣬷ֱ����ϡ��¡�����
  const Pos directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
  // ��ʼ����������
  int** visit = new int* [height];
  for (int i = 0; i < height; ++i) {
    visit[i] = new int[width];
    memset(visit[i], 0, width * sizeof(int)); // ��ʼ��Ϊ0�� ��ʾδ����
  }
  // ��ʼ��ǰ���ڵ�����
  Pos** pre = new Pos * [height];
  for (int i = 0; i < height; ++i) {
    pre[i] = new Pos[width];
    for (int j = 0; j < width; ++j) {
      pre[i][j] = { -1, -1 }; // ��ʼ��Ϊ-1��-1��ʾû��ǰ���ڵ�
    }
  }

  // ��ʼ������������
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

  PriorityQueue<Node, NodeCompare> p_queue; // ���ȶ���
  p_queue.Push(start_node); // ��ʼ�����
  start_costs[start_pos.row][start_pos.col] = 0; // ��ʼ���start_costΪ0
  visit[start_pos.row][start_pos.col] = 1; // ���Ϊ�ѷ���

  // �����ȶ��зǿ�
  while (!p_queue.Empty()) {
    Node current_node = p_queue.Top(); // ȡ���׽ڵ�
    Pos current_pos = current_node.pos;
    // �����ǰ�ڵ����յ�
    if (current_pos == end_pos) {
      solution_path.Clear(); // �����·��
      while (1) {
        // �����ǰ�ڵ�û��ǰ���ڵ㣨Ҳ���ǵ�ǰ�ڵ�����ʼλ�õ�ǰ����㣩
        if (current_pos.row == -1 && current_pos.col == -1) {
          break;
        }
        solution_path.PushBack(current_pos);
        field[current_pos.row][current_pos.col] = MAZE_PATH;
        current_pos = pre[current_pos.row][current_pos.col]; // ���ϸ��µ�ǰ�ڵ�Ϊǰ���ڵ�
      }

      solution_path.Reverse();
      PrintMaze();
      cout << endl << "��·��Ϊ:" << endl;
      PrintSolutionPath();

      // �ͷ�visit��pre��start_costs�ڴ�
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

    p_queue.Pop(); // ����Ԫ�س���
    for (int i = 0; i < 4; ++i) {
      Pos new_pos = current_pos + directions[i];
      if (IsInBounds(new_pos) && field[new_pos.row][new_pos.col] == MAZE_BLANK && !visit[new_pos.row][new_pos.col]) {
        const int new_start_cost = current_node.start_cost + 1;
        if (new_start_cost < start_costs[new_pos.row][new_pos.col]) {
          // �����½ڵ��������
          start_costs[new_pos.row][new_pos.col] = new_start_cost;
          // ���������پ���
          const int new_end_cost = Heuristic(new_pos, end_pos);
          const Node new_node(new_pos, new_start_cost, new_end_cost);
          p_queue.Push(new_node); // ���
          visit[new_pos.row][new_pos.col] = 1; // ���Ϊ�Ѿ�����
          pre[new_pos.row][new_pos.col] = current_pos; // ��¼ǰ���ڵ�
        }
      }
    }
  }

  if (p_queue.Empty()) {
    cout << "û�н�" << endl;
  }
  // �ͷ�visit��pre��start_costs�ڴ�
  for (int i = 0; i < height; ++i) {
    delete[] visit[i];
    delete[] pre[i];
    delete[] start_costs[i];
  }
  delete[] visit;
  delete[] pre;
  delete[] start_costs;
}

// ��ӡ��·��
void MAZE::PrintSolutionPath() {
  cout << "��·��: ";
  for (int i = 0; i < solution_path.Size(); ++i) {
    cout << solution_path[i];
    if (i != solution_path.Size() - 1) {
      cout << " -> ";
    }
  }
  cout << endl;
}

// ���·�����ָ�Ϊ�յ�
void MAZE::ClearPath() {
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (field[row][col] == MAZE_PATH) {
        field[row][col] = MAZE_BLANK;
      }
    }
  }
}

// �����Թ��ĸߺͿ�
void InputSize(int& height, int& width) {
  cout << "�������Թ��ĸ߶�[5-99]��" << endl;
  cin >> height;
  while (cin.fail() || height < 5 || height > 99) {
    cout << "�߶�����Ƿ�,����������߶ȣ�" << endl;
    cin.clear();
    cin.ignore(65535, '\n');
    cin >> height;
  }

  cout << "�������Թ��Ŀ��[5-99]��" << endl;
  cin >> width;
  while (cin.fail() || width < 5 || width > 99) {
    cout << "�������Ƿ�,�����������ȣ�" << endl;
    cin.clear();
    cin.ignore(65535, '\n');
    cin >> width;
  }
}


int main() {
  srand(time(0));  // ��ʼ���������
  int height, width;
  InputSize(height, width); // �����Թ��ĸ߶ȺͿ��

  MAZE maze(height, width); // �Թ�ʵ��
  maze.MakeRandomMaze(); // ��������Թ�
  maze.PrintMaze(); // ��ӡ�Թ�

  while (1) {
    cout << "��ѡ���Թ��㷨��[1]���ݷ�(�ݹ�)    [2]DFS��(ջ)    [3]BFS��    [4]A���㷨    [0]�˳�" << endl;
    int choice;
    cin >> choice;
    while (cin.fail() || choice < 0 || choice > 4) {
      cout << "����Ƿ�������������" << endl;
      cin >> choice;
    }
    if (choice == 0) {
      cout << "����ɹ��˳���" << endl;
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

  cout << endl << "���س����˳�..." << endl;
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