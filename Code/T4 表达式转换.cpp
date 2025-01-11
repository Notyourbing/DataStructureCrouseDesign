/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#ifdef _WIN32
  #include <conio.h>
#endif

using namespace std;
// 字符串类
class String {
private:
  char* data;
  size_t length;

public:
  // 默认构造函数
  String() {
	data = new char[1];
	data[0] = '\0';
	length = 0;
  }

  // 用char指针初始化的构造函数
  String(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str); // strcpy函数会将source的每个字符逐个复制，包括'\0'
  }

  // 用String对象初始化的构造函数
  String(const String& str) {
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.data);
  }

  // 析构函数
  ~String() {
	delete[] data;
  }
  
  // 置空字符串
  void Clear() {
    char* new_data = new char[1];
    delete[] data;
    data = new_data;
    data[0] = '\0';
    length = 0;
  }

  // 判断是否为空字符串
  bool Empty() {
    return (length == 0);
  }

  // 拷贝赋值运算符
  String& operator=(const String& other) {
	if (this == &other) {
	  return *this;
	}

	delete[] data;
	length = other.length;
	data = new char[length + 1];
	strcpy(data, other.data);

	return *this;
  }

  // 获取字符串的长度
  size_t Size() const {
	return length;
  }

  // 返回c风格字符串
  const char* C_str() const {
	return data;
  }

  // 向字符串尾添加字符
  void Append(const char ch) {
    *this += ch;
  }

  // 从pos开始（包括pos, 删除len个元素）
  void Erase(const size_t pos, size_t len = 1) {
    if (pos >= length) {
      return; // 起始位置超出字符串长度就不进行任何操作
    }
    // 如果删除的长度超过末尾, 只删除到末尾
    if (len > length - pos) { 
      len = length - pos;
    }

    size_t new_length = length - len;
    char* new_data = new char[new_length + 1];

    for (size_t i = 0; i < pos; ++i) {
      new_data[i] = data[i];
    }

    for (size_t i = pos + len; i < length; ++i) {
      new_data[i - len] = data[i];
    }

    new_data[new_length] = '\0';
    delete[] data;
    data = new_data;
    length = new_length;
  }

  // 重载[]操作符
  char& operator[](size_t index) {
	return data[index];
  }
  
  const char& operator[](size_t index) const{
    return data[index];
  }

  // 重载操作符+=
  String& operator+=(const String& other) {
	const size_t new_length = length + other.length;
	char* new_data = new char[new_length + 1];
	strcpy(new_data, data);
	strcat(new_data, other.data);

	delete[] data;
	data = new_data;
	length = new_length;
	return *this;
  }
  
  String& operator+=(const char ch) {
	const size_t new_length = length + 1;
	char* new_data = new char[new_length + 1];
	strcpy(new_data, data);
	new_data[new_length-1] = ch;
	new_data[new_length] = '\0';

	delete[] data;
	data = new_data;
	length = new_length;
	return *this;
  }

  // 友元函数重载输出流操作符
  friend ostream& operator<<(ostream& os, const String& str) {
	os << str.data;
	return os;
  }

  // 友元函数重载输入流操作符
  friend istream& operator>>(istream& is, String& str) {
    char buffer[1000];
    is >> buffer;
    str.length = strlen(buffer);
    delete[] str.data;
    str.data = new char[str.length + 1];
    strcpy(str.data, buffer);
    return is;
  }

  // 友元函数重载+操作符
  friend String operator+(const String& left, const String& right) {
	String temp(left);
	temp += right;
	return temp;
  }

  // 友元函数重载==操作符
  friend bool operator==(const String& left, const String& right) {
	return (strcmp(left.data, right.data) == 0);
  }

  friend bool operator!=(const String& left, const String& right) {
    return !(left == right);
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

  const T& operator[](size_t index) const {
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


// 二叉树节点类
template<typename T>
class TreeNode {
public:
  T value;
  TreeNode* left; //左子节点
  TreeNode* right; // 右子节点
  TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
};

// 二叉树类
template<typename T>
class BinaryTree {
protected:
  TreeNode<T>* root;

public:
  // 默认构造函数
  BinaryTree() : root(nullptr) {}

  // 析构函数，释放内存，是一个虚函数，确保派生类的析构函数能被正确调用
  ~BinaryTree() {
    Clear(root);
  }

  // 清空以node为根节点的树
  void Clear(TreeNode<T>* node) {
    if (node) {
      Clear(node->left);
      Clear(node->right);
    }
    delete node;
  }

  // 前序遍历（根 左 右）
  void PreOrderTraversal(TreeNode<T>* node) {
    if (node) {
      cout << node->value << ' ';
      PreOrderTraversal(node->left);
      PreOrderTraversal(node->right);
    }
  }

  // 中序遍历（左 根 右）
  void MidOrderTraversal(TreeNode<T>* node) {
    if (node) {
      MidOrderTraversal(node->left);
      cout << node->value << ' ';
      MidOrderTraversal(node->right);
    }
  }

  // 后序遍历（左 右 根）
  void PostOrderTraversal(TreeNode<T>* node) {
    if (node) {
      PostOrderTraversal(node->left);
      PostOrderTraversal(node->right);
      cout << node->value << ' ';
    }
  }

  // 三个公用的遍历接口
  void PreOrderTraversal() {
    PreOrderTraversal(root);
    cout << endl;
  }

  void MidOrderTraversal() {
    MidOrderTraversal(root);
    cout << endl;
  }

  void PostOrderTraversal() {
    PostOrderTraversal(root);
    cout << endl;
  }

  // 使用BFS输出二叉树的结构
  void PrintTree() {
    cout << "--------------------表达式的二叉树------------------------" << endl;
    if (!root) {
      return;
    }

    Queue<TreeNode<T>*> q;
    q.Push(root);
    int level = 0;
    int max_level = GetHeight(root);
    int width = (1 << max_level) * 2;

    while (!q.Empty()) {
      int level_node_count = q.Size();
      int spacing = width / (level_node_count + 1);
      for (int i = 0; i < level_node_count; ++i) {
        TreeNode<T>* current = q.Front();
        q.Pop();
        // 输出适当的空格以对齐节点
        cout << string(spacing, ' ');
        if (current) {
          cout << current->value;
          q.Push(current->left);
          q.Push(current->right);
        }
        else {
          cout << " ";
          q.Push(nullptr);
          q.Push(nullptr);
        }
      }
      cout << endl;
      ++level;
      if (level >= max_level) {
        break;
      }
    }
    cout << "----------------------------------------------------------" << endl;

  }

  // 计算树的高度
  int GetHeight(TreeNode<T>* node) {
    if (!node) {
      return 0;
    }
    return 1 + max(GetHeight(node->left), GetHeight(node->right));
  }

};

// 表达式树类，继承自二叉树类
class ExpressionTree : public BinaryTree<String> {
public:
  // 建二叉树树
  void BuildFromPostfix(const Vector<String>& postfix) {
    Stack<TreeNode<String>*> node_stack; // 二叉树的节点栈

    // 遍历后序表达式
    for (size_t i = 0; i < postfix.Size(); ++i) {
      if (!IsOperator(postfix[i])) { // 如果是操作数
        TreeNode<String>* leaf_node = new TreeNode<String>(postfix[i]); // 创建叶子结点
        node_stack.Push(leaf_node); // 将叶子结点入栈
      }
      else { // 是操作符
        TreeNode<String>* right_node = node_stack.Top(); // 从栈顶取出右子树
        node_stack.Pop();
        TreeNode<String>* left_node = node_stack.Top(); // 从栈顶取出左子树
        node_stack.Pop();

        TreeNode<String>* current_node = new TreeNode<String>(postfix[i]); // 创建当前节点
        // 链接左右子树
        current_node->left = left_node;
        current_node->right = right_node;
        node_stack.Push(current_node);  // 当前节点入栈
      }
    }
    if (!node_stack.Empty()) {
      root = node_stack.Top(); // 栈顶节点就是树的根节点
      node_stack.Pop();
    }
  }

  // 辅助函数，判断str是否是操作符
  bool IsOperator(const String& str) {
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "(" || str == ")") {
      return 1;
    }
    return 0;
  }

  // 辅助函数，返回操作符的优先级
  int GetPrecedence(const String& op) {
    if (op == "+" || op == "-") {
      return 1;
    }
    else if (op == "*" || op == "/") {
      return 2;
    }
    return 0;
  }

  // 辅助函数，去除表达式中的正号（不是加号）
  void RemovePlus(Vector<String>& infix) {
    for (size_t i = 0; i < infix.Size(); ++i) {
      // 如果不是操作符，且带有正号
      if (!IsOperator(infix[i]) && infix[i][0] == '+') { 
        infix[i].Erase(0, 1); // 移出字符串首的'+'
      }
    }
  }

  void OutputDebug(const Vector<String>& debug_str) {
    for (size_t i = 0; i < debug_str.Size(); ++i) {
      cout << "|" << debug_str[i] << "|" << endl;
    }
    cout << endl;
  }

  // 将中缀表达式转化为后缀表达式
  Vector<String> InfixToPostfix(const Vector<String>& infix) {
    Vector<String> postfix;
    Stack<String> operators; // 操作符栈
    // 遍历中缀表达式
    for (size_t i = 0; i < infix.Size(); ++i) {
      String temp = infix[i]; 

      // 如果不是操作符，即是操作数
      if (!IsOperator(temp)) {
        postfix.PushBack(temp); // 加入后缀表达式
      }
      else { // 是操作符
        if (temp == "(") { // 如果是左括号，入操作符栈
          operators.Push(temp);
        }
        else if (temp == ")") { // 如果是右括号，操作符不断出栈，直到遇到左括号
          while (!operators.Empty() && operators.Top() != "(") {
            postfix.PushBack(operators.Top()); // 操作符栈顶元素加入后缀表达式
            operators.Pop(); // 操作符栈出栈
          }
          operators.Pop(); //左括号出栈
        }
        else { // 是+-*/操作符
          if (operators.Empty() || GetPrecedence(temp) > GetPrecedence(operators.Top())) { // 当前操作符的优先级大于栈顶操作符
            operators.Push(temp); // 操作符入栈
          }
          else {
            while (!operators.Empty() && operators.Top() != "(" && GetPrecedence(temp) <= GetPrecedence(operators.Top())) { // 当前操作符的优先级小于等于栈顶操作符
              postfix.PushBack(operators.Top()); // 操作符栈顶元素加入后缀表达式
              operators.Pop(); // 操作符栈出栈
            }
            operators.Push(temp); // 操作符入栈
          }
        }
      }
    }
    // 把操作符栈中剩余的元素加入后缀表达式
    while (!operators.Empty()) {
      postfix.PushBack(operators.Top());
      operators.Pop();
    }

    return postfix;
  }

  // 检查中缀表达式是否合法
  bool IsValidInfix(Vector<String>& infix) {
    int operandCount = 0;
    int operatorCount = 0;
    int openParenthesisCount = 0;
    int closeParenthesisCount = 0;

    for (size_t i = 0; i < infix.Size(); ++i) {
      String token = infix[i];

      if (token == "(") {
        ++openParenthesisCount;
      }
      else if (token == ")") {
        ++closeParenthesisCount;
        // 检查是否存在未匹配的右括号
        if (closeParenthesisCount > openParenthesisCount) {
          return false;
        }
      }
      else if (token == "+" || token == "-" || token == "*" || token == "/") {
        // 检查操作符之前是否有足够的操作数
        if (operandCount == 0) {
          return false;
        }
        ++operatorCount;
        // 之后应该有操作数
        if (i + 1 >= infix.Size() || (infix[i + 1] == "+" || infix[i + 1] == "-" || infix[i + 1] == "*" || infix[i + 1] == "/" || infix[i + 1] == ")")) {
          return false;
        }
      }
      else {
        // 假设所有其他内容都是操作数
        ++operandCount;
      }
    }

    // 检查括号是否匹配，操作符和操作数的关系是否合法
    if (openParenthesisCount != closeParenthesisCount) {
      return false;
    }
    if (operandCount != operatorCount + 1) {
      return false;
    }

    return true;
  }

  // 输入中缀表达式,并调用建二叉树函数
  void InfixInput() {
    Vector<String> infix;
    String temp;
    while (1) {
      char ch;
      ch = getchar();
      if (ch == '\n') {
        if (!temp.Empty()) {
          infix.PushBack(temp);
        }
        break;
      }
      if (ch == ' ') {
        infix.PushBack(temp);
        temp.Clear();
      }
      else {
        temp += ch;
      }
    }

    RemovePlus(infix); // 去除表达式中的正号

    if (!IsValidInfix(infix)) {
      cout << "输入中缀表达式非法" << endl;
      exit(-1);
    }

    Vector<String> postfix = InfixToPostfix(infix); // 转化为后缀表达式

    BuildFromPostfix(postfix); // 建立表达式二叉树
  }
};

int main() {
  ExpressionTree expression; // 创建表达式二叉树

  cout << "请输入中缀表达式：" << endl;
  expression.InfixInput(); // 输入中缀表达式,并调用建二叉树函数
  cout<< endl << "表达式的二叉树为：" << endl;
  expression.PrintTree();
  cout << endl << "前缀表达式为：" << endl;
  expression.PreOrderTraversal();

  cout << endl << "后缀表达式为：" << endl;
  expression.PostOrderTraversal();

  cout << endl << "按回车键退出..." << endl;
  #ifdef _WIN32
    while (_getch() != '\r')
      continue;
  #endif

  return 0;
}