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

// Note: ÿ���˵�������Ψһid

// �ַ�����
class String {
private:
  char* data;
  size_t length;

public:
  // Ĭ�Ϲ��캯��
  String() {
    data = new char[1];
    data[0] = '\0';
    length = 0;
  }

  // ��charָ���ʼ���Ĺ��캯��
  String(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str); // strcpy�����Ὣsource��ÿ���ַ�������ƣ�����'\0'
  }

  // ��String�����ʼ���Ĺ��캯��
  String(const String& str) {
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.data);
  }

  // ��������
  ~String() {
    delete[] data;
  }

  // �ÿ��ַ���
  void Clear() {
    char* new_data = new char[1];
    delete[] data;
    data = new_data;
    data[0] = '\0';
    length = 0;
  }

  // �ж��Ƿ�Ϊ���ַ���
  bool Empty() {
    return (length == 0);
  }

  // ������ֵ�����
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

  // ��ȡ�ַ����ĳ���
  size_t Size() const {
    return length;
  }

  // ����c����ַ���
  const char* C_str() const {
    return data;
  }

  // ���ַ���β����ַ�
  void Append(const char ch) {
    *this += ch;
  }

  // ��pos��ʼ������pos, ɾ��len��Ԫ�أ�
  void Erase(const size_t pos, size_t len = 1) {
    if (pos >= length) {
      return; // ��ʼλ�ó����ַ������ȾͲ������κβ���
    }
    // ���ɾ���ĳ��ȳ���ĩβ, ֻɾ����ĩβ
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

  // ����[]������
  char& operator[](size_t index) {
    return data[index];
  }

  const char& operator[](size_t index) const {
    return data[index];
  }

  // ���ز�����+=
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

  // ��Ԫ�������������������
  friend ostream& operator<<(ostream& os, const String& str) {
    os << str.data;
    return os;
  }

  // ��Ԫ��������������������
  friend istream& operator>>(istream& is, String& str) {
    char buffer[1000];
    is >> buffer;
    str.length = strlen(buffer);
    delete[] str.data;
    str.data = new char[str.length + 1];
    strcpy(str.data, buffer);
    return is;
  }

  // ��Ԫ��������+������
  friend String operator+(const String& left, const String& right) {
    String temp(left);
    temp += right;
    return temp;
  }

  // ��Ԫ��������==������
  friend bool operator==(const String& left, const String& right) {
    return (strcmp(left.data, right.data) == 0);
  }

  friend bool operator!=(const String& left, const String& right) {
    return !(left == right);
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

// ���Ľڵ�
struct Node {
  String name; // ����
  String mate; // ��ż
  int depth = 0;
  Node* parent; // ���׽ڵ�
  Vector<Node*> children; // �����ǵĽڵ�����
  Node(const String& init_name, Node* init_parent) {
    name = init_name;
    parent = init_parent;
  }
};

// ��������
class GeneTree {
private:
  Node* root; // ���Ƚڵ�

  // Ϊmember���child
  void AddChild(Node* member, Node* child) {
    child->parent = member;
    member->children.PushBack(child);
  }

  // ����current_nodeΪ������������dfs����member_name
  Node* FindMemberRecursive(Node* current_node, const String& member_name) {
    if (current_node == nullptr) {
      return nullptr;
    }
    // ƥ��ɹ�
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

  // ɾ����current_nodeΪ���ڵ������
  void DeleteSubTreeRecursive(Node* current_node) {
    if (current_node == nullptr) {
      return;
    }
    // �ݹ�ɾ�����к��ӽڵ�
    for (auto child : current_node->children) {
      DeleteSubTreeRecursive(child);
    }
    // ɾ����ǰ�ڵ�
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

  // ����
  void BulidGeneTree(const String& ancestor_name) {
    root = new Node(ancestor_name, nullptr);
  }

  // ��ȡ��������
  String& GetAncestorName() {
    if (root) {
      return root->name;
    }
    throw runtime_error("The tree is empty");
  }

  // dfs������Ϊmember_name�ĳ�Ա����������
  Node* FindMember(const String& member_name) {
    return FindMemberRecursive(root, member_name);
  }

  // Ϊ��Ϊparent_name�ĳ�Ա�����Ϊchildren_names�ĺ�����
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

  // ɾ������
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

  // ��ӡ��Ů
  void DispChildren(const String& parent_name) {
    Node* parent_node = FindMember(parent_name);
    if (parent_node == nullptr) {
      throw runtime_error("Parent not found");
    }
    for (auto child : parent_node->children) {
      cout << child->name << "    ";
    }
  }

  // ��ӡ������
  void DispTree() {
    DispTreeRecursive(root);
  }

  // ���������
  void ClearTree() {
    DeleteSubTree(root);
  }
 };

GeneTree gene_tree;

// ��������
void BuildGeneTree() {
  cout << "���Ƚ���һ�����ף�" << endl;
  String ancestor_name;
  cout << "���������ȵ�������";
  cin >> ancestor_name;
  gene_tree.BulidGeneTree(ancestor_name);
  cout << "�˼���������ǣ�" << gene_tree.GetAncestorName() << endl;
}

// ��ӡ����
void PrintTitle() {
  cout << "---------------------------------------------" << endl;
  cout << "|               ���׹���ϵͳ                |" << endl;
  cout << "|-------------------------------------------|" << endl;
  cout << "|            ��ѡ��Ҫִ�еĲ�����           |" << endl;
  cout << "|             A --- ���Ƽ���                |" << endl;
  cout << "|             B --- ��Ӽ�ͥ��Ա            |" << endl;
  cout << "|             C --- ��ɢ�ֲ���ͥ            |" << endl;
  cout << "|             D --- ���ļ�ͥ��Ա����        |" << endl;
  cout << "|             E --- ��ӡ����                |" << endl;
  cout << "|             F --- �˳�����                |" << endl;
  cout << "---------------------------------------------" << endl;
  cout << endl;
}

// ���Ƽ���
void OperationA() {
  cout << "������Ҫ������ͥ�ĳ�Ա������";
  String member_name;
  cin >> member_name;
  Node* member = gene_tree.FindMember(member_name);
  if (member == nullptr) {
    cout << "û���ҵ������Ա" << endl;
    return;
  }
  int children_num;
  cout << "������" << member_name << "�Ķ�Ů������";
  cin >> children_num;
  Vector<String> children_names;
  cout << "����������" << member_name << "�Ķ�Ů��������";
  for (int i = 0; i < children_num; ++i) {
    String temp;
    cin >> temp;
    children_names.PushBack(temp);
  }
  gene_tree.AddChildren(member_name, children_names);
  cout << member_name << "�ĵ�һ������ǣ�";
  gene_tree.DispChildren(member_name);
  cout << endl;
}

// ��Ӽ�ͥ��Ա
void OperationB() {
  cout << "������Ҫ��Ӷ�/Ů�ĳ�Ա��������";
  String member_name;
  cin >> member_name;
  Node* member = gene_tree.FindMember(member_name);
  if (member == nullptr) {
    cout << "û���ҵ������Ա" << endl;
    return;
  }
  String child_name;
  cout << "������" << member_name << "����ӵĶ�/Ů��������";
  cin >> child_name;
  Vector<String> children(1, child_name);
  gene_tree.AddChildren(member_name, children);
  cout << member_name << "�ĵ�һ������ǣ�";
  gene_tree.DispChildren(member_name);
  cout << endl;
}

// ��ɢ�ֲ���ͥ
void OperationC() {
  cout << "������Ҫ��ɢ��ͥ���˵�������" << endl;
  String delete_name;
  cin >> delete_name;
  Node* member = gene_tree.FindMember(delete_name);
  if (member == nullptr) {
    cout << "û���ҵ������Ա" << endl;
    return;
  }
  gene_tree.DeleteSubTree(member);
}

// ���ļ�ͥ��Ա����
void OperationD() {
  cout << "������Ҫ�����������˵�Ŀǰ������";
  String ori_name;
  cin >> ori_name;
  Node* member = gene_tree.FindMember(ori_name);
  if (member == nullptr) {
    cout << "û���ҵ������Ա" << endl;
    return;
  }
  cout << "��������ĺ��������";
  String new_name;
  cin >> new_name;
  member->name = new_name;
  cout << ori_name << "�Ѹ���Ϊ" << new_name << endl;
}

// ��ӡ����
void OperationE() {
  cout << endl << "--------���׵�Ŀ¼�ṹ(������ʾ��һ����--------" << endl;
  gene_tree.DispTree();
  cout << endl << "-----------------------------------------------" << endl;
}

int main() {
  PrintTitle();
  BuildGeneTree();
  
  char choice;
  while (1) {
    cout<< endl << "��ѡ��Ҫִ�еĲ�����";
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
