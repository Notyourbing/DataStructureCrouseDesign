/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#ifdef _WIN32
  #include <conio.h>
#endif

using namespace std;
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
  
  const char& operator[](size_t index) const{
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
	new_data[new_length-1] = ch;
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


// �������ڵ���
template<typename T>
class TreeNode {
public:
  T value;
  TreeNode* left; //���ӽڵ�
  TreeNode* right; // ���ӽڵ�
  TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
};

// ��������
template<typename T>
class BinaryTree {
protected:
  TreeNode<T>* root;

public:
  // Ĭ�Ϲ��캯��
  BinaryTree() : root(nullptr) {}

  // �����������ͷ��ڴ棬��һ���麯����ȷ������������������ܱ���ȷ����
  ~BinaryTree() {
    Clear(root);
  }

  // �����nodeΪ���ڵ����
  void Clear(TreeNode<T>* node) {
    if (node) {
      Clear(node->left);
      Clear(node->right);
    }
    delete node;
  }

  // ǰ��������� �� �ң�
  void PreOrderTraversal(TreeNode<T>* node) {
    if (node) {
      cout << node->value << ' ';
      PreOrderTraversal(node->left);
      PreOrderTraversal(node->right);
    }
  }

  // ����������� �� �ң�
  void MidOrderTraversal(TreeNode<T>* node) {
    if (node) {
      MidOrderTraversal(node->left);
      cout << node->value << ' ';
      MidOrderTraversal(node->right);
    }
  }

  // ����������� �� ����
  void PostOrderTraversal(TreeNode<T>* node) {
    if (node) {
      PostOrderTraversal(node->left);
      PostOrderTraversal(node->right);
      cout << node->value << ' ';
    }
  }

  // �������õı����ӿ�
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

  // ʹ��BFS����������Ľṹ
  void PrintTree() {
    cout << "--------------------���ʽ�Ķ�����------------------------" << endl;
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
        // ����ʵ��Ŀո��Զ���ڵ�
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

  // �������ĸ߶�
  int GetHeight(TreeNode<T>* node) {
    if (!node) {
      return 0;
    }
    return 1 + max(GetHeight(node->left), GetHeight(node->right));
  }

};

// ���ʽ���࣬�̳��Զ�������
class ExpressionTree : public BinaryTree<String> {
public:
  // ����������
  void BuildFromPostfix(const Vector<String>& postfix) {
    Stack<TreeNode<String>*> node_stack; // �������Ľڵ�ջ

    // ����������ʽ
    for (size_t i = 0; i < postfix.Size(); ++i) {
      if (!IsOperator(postfix[i])) { // ����ǲ�����
        TreeNode<String>* leaf_node = new TreeNode<String>(postfix[i]); // ����Ҷ�ӽ��
        node_stack.Push(leaf_node); // ��Ҷ�ӽ����ջ
      }
      else { // �ǲ�����
        TreeNode<String>* right_node = node_stack.Top(); // ��ջ��ȡ��������
        node_stack.Pop();
        TreeNode<String>* left_node = node_stack.Top(); // ��ջ��ȡ��������
        node_stack.Pop();

        TreeNode<String>* current_node = new TreeNode<String>(postfix[i]); // ������ǰ�ڵ�
        // ������������
        current_node->left = left_node;
        current_node->right = right_node;
        node_stack.Push(current_node);  // ��ǰ�ڵ���ջ
      }
    }
    if (!node_stack.Empty()) {
      root = node_stack.Top(); // ջ���ڵ�������ĸ��ڵ�
      node_stack.Pop();
    }
  }

  // �����������ж�str�Ƿ��ǲ�����
  bool IsOperator(const String& str) {
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "(" || str == ")") {
      return 1;
    }
    return 0;
  }

  // �������������ز����������ȼ�
  int GetPrecedence(const String& op) {
    if (op == "+" || op == "-") {
      return 1;
    }
    else if (op == "*" || op == "/") {
      return 2;
    }
    return 0;
  }

  // ����������ȥ�����ʽ�е����ţ����ǼӺţ�
  void RemovePlus(Vector<String>& infix) {
    for (size_t i = 0; i < infix.Size(); ++i) {
      // ������ǲ��������Ҵ�������
      if (!IsOperator(infix[i]) && infix[i][0] == '+') { 
        infix[i].Erase(0, 1); // �Ƴ��ַ����׵�'+'
      }
    }
  }

  void OutputDebug(const Vector<String>& debug_str) {
    for (size_t i = 0; i < debug_str.Size(); ++i) {
      cout << "|" << debug_str[i] << "|" << endl;
    }
    cout << endl;
  }

  // ����׺���ʽת��Ϊ��׺���ʽ
  Vector<String> InfixToPostfix(const Vector<String>& infix) {
    Vector<String> postfix;
    Stack<String> operators; // ������ջ
    // ������׺���ʽ
    for (size_t i = 0; i < infix.Size(); ++i) {
      String temp = infix[i]; 

      // ������ǲ����������ǲ�����
      if (!IsOperator(temp)) {
        postfix.PushBack(temp); // �����׺���ʽ
      }
      else { // �ǲ�����
        if (temp == "(") { // ����������ţ��������ջ
          operators.Push(temp);
        }
        else if (temp == ")") { // ����������ţ����������ϳ�ջ��ֱ������������
          while (!operators.Empty() && operators.Top() != "(") {
            postfix.PushBack(operators.Top()); // ������ջ��Ԫ�ؼ����׺���ʽ
            operators.Pop(); // ������ջ��ջ
          }
          operators.Pop(); //�����ų�ջ
        }
        else { // ��+-*/������
          if (operators.Empty() || GetPrecedence(temp) > GetPrecedence(operators.Top())) { // ��ǰ�����������ȼ�����ջ��������
            operators.Push(temp); // ��������ջ
          }
          else {
            while (!operators.Empty() && operators.Top() != "(" && GetPrecedence(temp) <= GetPrecedence(operators.Top())) { // ��ǰ�����������ȼ�С�ڵ���ջ��������
              postfix.PushBack(operators.Top()); // ������ջ��Ԫ�ؼ����׺���ʽ
              operators.Pop(); // ������ջ��ջ
            }
            operators.Push(temp); // ��������ջ
          }
        }
      }
    }
    // �Ѳ�����ջ��ʣ���Ԫ�ؼ����׺���ʽ
    while (!operators.Empty()) {
      postfix.PushBack(operators.Top());
      operators.Pop();
    }

    return postfix;
  }

  // �����׺���ʽ�Ƿ�Ϸ�
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
        // ����Ƿ����δƥ���������
        if (closeParenthesisCount > openParenthesisCount) {
          return false;
        }
      }
      else if (token == "+" || token == "-" || token == "*" || token == "/") {
        // ��������֮ǰ�Ƿ����㹻�Ĳ�����
        if (operandCount == 0) {
          return false;
        }
        ++operatorCount;
        // ֮��Ӧ���в�����
        if (i + 1 >= infix.Size() || (infix[i + 1] == "+" || infix[i + 1] == "-" || infix[i + 1] == "*" || infix[i + 1] == "/" || infix[i + 1] == ")")) {
          return false;
        }
      }
      else {
        // ���������������ݶ��ǲ�����
        ++operandCount;
      }
    }

    // ��������Ƿ�ƥ�䣬�������Ͳ������Ĺ�ϵ�Ƿ�Ϸ�
    if (openParenthesisCount != closeParenthesisCount) {
      return false;
    }
    if (operandCount != operatorCount + 1) {
      return false;
    }

    return true;
  }

  // ������׺���ʽ,�����ý�����������
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

    RemovePlus(infix); // ȥ�����ʽ�е�����

    if (!IsValidInfix(infix)) {
      cout << "������׺���ʽ�Ƿ�" << endl;
      exit(-1);
    }

    Vector<String> postfix = InfixToPostfix(infix); // ת��Ϊ��׺���ʽ

    BuildFromPostfix(postfix); // �������ʽ������
  }
};

int main() {
  ExpressionTree expression; // �������ʽ������

  cout << "��������׺���ʽ��" << endl;
  expression.InfixInput(); // ������׺���ʽ,�����ý�����������
  cout<< endl << "���ʽ�Ķ�����Ϊ��" << endl;
  expression.PrintTree();
  cout << endl << "ǰ׺���ʽΪ��" << endl;
  expression.PreOrderTraversal();

  cout << endl << "��׺���ʽΪ��" << endl;
  expression.PostOrderTraversal();

  cout << endl << "���س����˳�..." << endl;
  #ifdef _WIN32
    while (_getch() != '\r')
      continue;
  #endif

  return 0;
}