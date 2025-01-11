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

// Note: 每个人的姓名是唯一id

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

  const char& operator[](size_t index) const {
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
    new_data[new_length - 1] = ch;
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

    bool operator!=(const Iterator& other) const{
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

// 树的节点
struct Node {
  String name; // 姓名
  String mate; // 配偶
  int depth = 0;
  Node* parent; // 父亲节点
  Vector<Node*> children; // 孩子们的节点向量
  Node(const String& init_name, Node* init_parent) {
    name = init_name;
    parent = init_parent;
  }
};

// 家谱树类
class GeneTree {
private:
  Node* root; // 祖先节点

  // 为member添加child
  void AddChild(Node* member, Node* child) {
    child->parent = member;
    member->children.PushBack(child);
  }

  // 在以current_node为根结点的树上用dfs查找member_name
  Node* FindMemberRecursive(Node* current_node, const String& member_name) {
    if (current_node == nullptr) {
      return nullptr;
    }
    // 匹配成功
    if (current_node->name == member_name) {
      return current_node;
    }
    for (auto child : current_node->children) {
      Node* result = FindMemberRecursive(child, member_name);
      if (result) {
        return result;
      }
    }
    return nullptr;
  }

  // 删除以current_node为根节点的子树
  void DeleteSubTreeRecursive(Node* current_node) {
    if (current_node == nullptr) {
      return;
    }
    // 递归删除所有孩子节点
    for (auto child : current_node->children) {
      DeleteSubTreeRecursive(child);
    }
    // 删除当前节点
    delete current_node;
  }

  void DispTreeRecursive(Node* current_node) {
    if (current_node == nullptr) {
      return;
    }
    for (int i = 0; i < current_node->depth; ++i) {
      cout << "    ";
    }
    cout << current_node->name << endl;
    for (auto child : current_node->children) {
      DispTreeRecursive(child);
    }
  }
public:
  GeneTree() {
    root = nullptr;
  }

  ~GeneTree() {
    ClearTree();
  }

  // 建树
  void BulidGeneTree(const String& ancestor_name) {
    root = new Node(ancestor_name, nullptr);
  }

  // 获取祖先名字
  String& GetAncestorName() {
    if (root) {
      return root->name;
    }
    throw runtime_error("The tree is empty");
  }

  // dfs查找名为member_name的成员，返回其结点
  Node* FindMember(const String& member_name) {
    return FindMemberRecursive(root, member_name);
  }

  // 为名为parent_name的成员添加名为children_names的孩子们
  void AddChildren(const String& parent_name, const Vector<String>& children_names) {
    Node* parent_node = FindMember(parent_name);
    if (parent_node == nullptr) {
      throw runtime_error("Parent not found");
    }
    for (const String& child_name : children_names) {
      Node* child_node = new Node(child_name, parent_node);
      child_node->depth = parent_node->depth + 1;
      AddChild(parent_node, child_node);
    }
  }

  // 删除子树
  void DeleteSubTree(Node* sub_root) {
    if (sub_root == root) {
      DeleteSubTreeRecursive(root);
      root = nullptr;
    }
    else {
      Node* sub_parent = sub_root->parent;
      for (int i = 0; i < sub_parent->children.Size(); ++i) {
        if (sub_parent->children[i] == sub_root) {
          sub_parent->children.erase(i);
        }
      }
      DeleteSubTreeRecursive(sub_root);
    }
  }

  // 打印儿女
  void DispChildren(const String& parent_name) {
    Node* parent_node = FindMember(parent_name);
    if (parent_node == nullptr) {
      throw runtime_error("Parent not found");
    }
    for (auto child : parent_node->children) {
      cout << child->name << "    ";
    }
  }

  // 打印家谱树
  void DispTree() {
    DispTreeRecursive(root);
  }

  // 清除整棵树
  void ClearTree() {
    DeleteSubTree(root);
  }
 };

GeneTree gene_tree;

// 建立家谱
void BuildGeneTree() {
  cout << "首先建立一个家谱！" << endl;
  String ancestor_name;
  cout << "请输入祖先的姓名：";
  cin >> ancestor_name;
  gene_tree.BulidGeneTree(ancestor_name);
  cout << "此家族的祖先是：" << gene_tree.GetAncestorName() << endl;
}

// 打印标题
void PrintTitle() {
  cout << "---------------------------------------------" << endl;
  cout << "|               家谱管理系统                |" << endl;
  cout << "|-------------------------------------------|" << endl;
  cout << "|            请选择要执行的操作：           |" << endl;
  cout << "|             A --- 完善家谱                |" << endl;
  cout << "|             B --- 添加家庭成员            |" << endl;
  cout << "|             C --- 解散局部家庭            |" << endl;
  cout << "|             D --- 更改家庭成员姓名        |" << endl;
  cout << "|             E --- 打印家谱                |" << endl;
  cout << "|             F --- 退出程序                |" << endl;
  cout << "---------------------------------------------" << endl;
  cout << endl;
}

// 完善家谱
void OperationA() {
  cout << "请输入要建立家庭的成员姓名：";
  String member_name;
  cin >> member_name;
  Node* member = gene_tree.FindMember(member_name);
  if (member == nullptr) {
    cout << "没有找到这个成员" << endl;
    return;
  }
  int children_num;
  cout << "请输入" << member_name << "的儿女人数：";
  cin >> children_num;
  Vector<String> children_names;
  cout << "请依次输入" << member_name << "的儿女的姓名：";
  for (int i = 0; i < children_num; ++i) {
    String temp;
    cin >> temp;
    children_names.PushBack(temp);
  }
  gene_tree.AddChildren(member_name, children_names);
  cout << member_name << "的第一代后代是：";
  gene_tree.DispChildren(member_name);
  cout << endl;
}

// 添加家庭成员
void OperationB() {
  cout << "请输入要添加儿/女的成员的姓名：";
  String member_name;
  cin >> member_name;
  Node* member = gene_tree.FindMember(member_name);
  if (member == nullptr) {
    cout << "没有找到这个成员" << endl;
    return;
  }
  String child_name;
  cout << "请输入" << member_name << "新添加的儿/女的姓名：";
  cin >> child_name;
  Vector<String> children(1, child_name);
  gene_tree.AddChildren(member_name, children);
  cout << member_name << "的第一代后代是：";
  gene_tree.DispChildren(member_name);
  cout << endl;
}

// 解散局部家庭
void OperationC() {
  cout << "请输入要解散家庭的人的姓名：" << endl;
  String delete_name;
  cin >> delete_name;
  Node* member = gene_tree.FindMember(delete_name);
  if (member == nullptr) {
    cout << "没有找到这个成员" << endl;
    return;
  }
  gene_tree.DeleteSubTree(member);
}

// 更改家庭成员姓名
void OperationD() {
  cout << "请输入要更改姓名的人的目前姓名：";
  String ori_name;
  cin >> ori_name;
  Node* member = gene_tree.FindMember(ori_name);
  if (member == nullptr) {
    cout << "没有找到这个成员" << endl;
    return;
  }
  cout << "请输入更改后的姓名：";
  String new_name;
  cin >> new_name;
  member->name = new_name;
  cout << ori_name << "已更名为" << new_name << endl;
}

// 打印家谱
void OperationE() {
  cout << endl << "--------家谱的目录结构(缩进表示下一代）--------" << endl;
  gene_tree.DispTree();
  cout << endl << "-----------------------------------------------" << endl;
}

int main() {
  PrintTitle();
  BuildGeneTree();
  
  char choice;
  while (1) {
    cout<< endl << "请选择要执行的操作：";
    cin >> choice;
    if (choice >= 'a' && choice <= 'z') {
      choice = choice - 'a' + 'A';
    }
    if (choice == 'A') {
      OperationA();
    }
    else if (choice == 'B') {
      OperationB();
    }
    else if (choice == 'C') {
      OperationC();
    }
    else if (choice == 'D') {
      OperationD();
    }
    else if (choice == 'E') {
      OperationE();
    }
    else if (choice == 'F') {
      break;
    }
  }
  return 0;
}
