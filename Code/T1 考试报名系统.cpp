/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <climits>
#include <limits>
using namespace std;

const int MAX_ID_SIZE = 20;
const int MAX_NAME_SIZE = 50;
const int MAX_GENDER_SIZE = 20;
const int MAX_CATEGORY_SIZE = 30;

// 学生类
class Student {
private:
  char exam_id[MAX_ID_SIZE + 1];      // 准考证号
  char name[MAX_NAME_SIZE + 1];        // 姓名
  char gender[MAX_GENDER_SIZE + 1];    // 性别
  int age;                              // 年龄
  char exam_category[MAX_CATEGORY_SIZE]; // 报考类别
  Student* next;                        // 指向下一个学生节点

public:
  // 构造函数
  Student(const char* id = "", const char* n = "", const char* g = "", int a = 0, const char* category = "") {
    strcpy(exam_id, id);
    strcpy(name, n);
    strcpy(gender, g);
    age = a;
    strcpy(exam_category, category);
    next = nullptr;
  }

  // 设置和获取下一个节点指针
  void SetNext(Student* next_student) {
    next = next_student;
  }

  Student* GetNext() {
    return next;
  }

  // 打印考生信息
  void Display() const {
    cout << setiosflags(ios::left);
    cout << setw(10) << exam_id << setw(10) << name << setw(10) << gender
      << setw(10) << age << setw(10) << exam_category << endl;
  }

  // 获取准考证号
  const char* GetExamID() const {
    return exam_id;
  }

  const char* GetGender() const {
    return gender;
  }

  const int GetAge() const {
    return age;
  }
  // 修改学生信息
  void Modify(const char* n, const char* g, int a, const char* category) {
    strcpy(name, n);
    strcpy(gender, g);
    age = a;
    strcpy(exam_category, category);
  }
};

// 学生链表类
class StudentList {
private:
  Student* head;  // 链表的头节点指针

public:
  // 构造函数，初始化链表为空
  StudentList() : head(nullptr) {}

  int GetLength() const {
    int length = 0;
    Student* temp = head;
    while (temp != nullptr) {
      temp = temp->GetNext();
      length++;
    }
    return length;
  }

  // 插入考生信息
  void InsertStudent(const char* id, const char* name, const char* gender, int age, const char* category, int pos) {
    Student* new_student = new Student(id, name, gender, age, category);
    int list_len = GetLength();
    if (pos > list_len + 1) {
      pos = list_len + 1;
    }
    if (pos < 1) {
      pos = 1;
    }
    if (1 == pos) {
      new_student->SetNext(head);
      head = new_student;
    }
    else {
      Student* temp = head;
      Student* previous = nullptr;
      for (int i = 0; i < pos - 1; ++i) {
        previous = temp;
        temp = temp->GetNext();
      }
      previous->SetNext(new_student);
      new_student->SetNext(temp);
    }
  }

  // 显示所有考生信息
  void DisplayStudents() const {
    cout << endl;
    if (head == nullptr) {
      cout << "暂无考生信息。" << endl;
      return;
    }
    cout << "------------------所有考生信息---------------------" << endl;
    cout << "考号      姓名      性别      年龄      报考类别     " << endl;
    Student* temp = head;
    while (temp != nullptr) {
      temp->Display();
      temp = temp->GetNext();
    }
    cout << "---------------------------------------------------" << endl;
  }

  // 查询考生信息
  Student* SearchStudent(const char* exam_id) const {
    Student* temp = head;
    while (temp != nullptr) {
      if (strcmp(temp->GetExamID(), exam_id) == 0) {
        return temp;
      }
      temp = temp->GetNext();
    }
    return nullptr;
  }

  // 修改考生信息
  void ModifyStudent(const char* exam_id, const char* name, const char* gender, int age, const char* category) {
    Student* student = SearchStudent(exam_id);
    if (student == nullptr) {
      cout << "未找到该考生信息。" << endl;
    }
    else {
      student->Modify(name, gender, age, category);
      cout << "考生信息已更新。" << endl;
    }
  }

  // 删除考生信息
  void DeleteStudent(const char* exam_id) {
    cout << endl;
    if (head == nullptr) {
      cout << "列表为空，无法删除。" << endl;
      return;
    }

    if (strcmp(head->GetExamID(), exam_id) == 0) {
      Student* temp = head;
      head = head->GetNext();
      delete temp;
      cout << "考生信息已删除。" << endl;
      return;
    }

    Student* current = head;
    Student* previous = nullptr;
    while (current != nullptr && strcmp(current->GetExamID(), exam_id) != 0) {
      previous = current;
      current = current->GetNext();
    }

    if (current == nullptr) {
      cout << "未找到该考生信息。" << endl;
    }
    else {
      previous->SetNext(current->GetNext());
      delete current;
      cout << "考生信息已删除。" << endl;
    }
  }

  // 判断new_exam_id是否合法，合法意味着和每一个已经存在的exam_id不同，且为全都为数字
  bool IsIdValid(char* new_exam_id) {
    // 检查是否符合全数字要求
    char* temp_id = new_exam_id;
    while (*temp_id != 0) {
      if (*temp_id < '0' || *temp_id > '9') {
        return false;
      }
      ++temp_id;
    }
    // 检查是否和已经存在的exam_id有相同的
    Student* temp = head;
    while (temp != nullptr) {
      if (strcmp(temp->GetExamID(), new_exam_id) == 0) {
        return false;
      }
      temp = temp->GetNext();
    }
    return true;
  }

  // 统计男女百分比，各个年龄的百分比
  void Statistics() {
    Student* temp = head;
    int male_num = 0;
    int female_num = 0;
    unsigned int age_num[100] = {0}; // age[i] 表示年龄为i的人的人数
    while (temp != nullptr) {
      if (strcmp(temp->GetGender(), "男") == 0) {
        ++male_num;
      }
      else {
        ++female_num;
      }
      ++age_num[temp->GetAge()];
      temp = temp->GetNext();
    }
    double male_ratio =100 * double(male_num) / double(male_num + female_num);
    cout << "-----------------统计结果--------------------" << endl;
    cout << "男性占比："<< setprecision(3) << male_ratio << "%" << endl;
    cout << "女性占比：" << setprecision(3) << 100 - male_ratio << "%" << endl;
    for (int i = 0; i < 100; ++i) {
      if (age_num[i]) {
        cout << i << "岁,共   " << age_num[i] << "人" << endl;
      }
    }
    cout << "---------------------------------------------" << endl;
  }

  // 析构函数，释放链表中的所有节点
  ~StudentList() {
    while (head != nullptr) {
      Student* temp = head;
      head = head->GetNext();
      delete temp;
    }
  }
} stu_list;

// 打印输入规则
void RulesPrint() {
  cout << endl;
  cout << "-----------------------考生信息输入规则-----------------------" << endl;
  cout << "|考号：    |由0-9的构成的字符串，长度不超过20                |" << endl;
  cout << "|姓名：    |字符串，英文不超过50个字符，中文不超过25个字     |" << endl;
  cout << "|性别：    |男或女                                           |" << endl;
  cout << "|年龄：    |整数，1-150之间                                  |" << endl;
  cout << "|报考类别：|字符串，英文不超过30个字符，中文不超过15个字     |" << endl;
  cout << "|注意：    |参数之间用空格或回车分隔                         |" << endl;
  cout << "--------------------------------------------------------------" << endl;
}

// 输入一个考生的所有信息，默认值参数i是在初始化时使用的，其余的使用情况不给默认值参数传参。
void AllInfoInput(char* exam_id, char* name, char* gender, int& age, char* exam_category, const int i = -1) {
  cin >> exam_id;
  while (cin.fail() || !stu_list.IsIdValid(exam_id)) {

    if (-1 != i) {
      cout << "第" << i + 1 << "个考生的考号输入非法，请从第" << i + 1 << "个考生的考号开始重新输入" << endl;
    }
    else {
      cout << "考生的考号输入非法，请重新输入" << endl;
    }
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }

  cin >> name;
  while (cin.fail()) {
    if (-1 != i) {
      cout << "第" << i + 1 << "个考生的姓名输入非法，请从第" << i + 1 << "个考生的姓名开始重新输入" << endl;
    }
    else {
      cout << "考生的姓名输入非法，请重新输入" << endl;
    }
    memset(name, 0, sizeof(name));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> name;
  }

  cin >> gender;
  while (cin.fail() || (strcmp(gender, "男") != 0 && strcmp(gender, "女") != 0)) {
    if (-1 != i) {
      cout << "第" << i + 1 << "个考生的性别输入非法，请从第" << i + 1 << "个考生的性别开始重新输入" << endl;
    }
    else {
      cout << "考生的性别输入非法，请重新输入" << endl;
    }
    memset(gender, 0, sizeof(gender));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> gender;
  }

  cin >> age;
  while (cin.fail()) {
    if (-1 != i) {
      cout << "第" << i + 1 << "个考生的年龄输入非法，请从第" << i + 1 << "个考生的年龄开始重新输入" << endl;
    }
    else {
      cout << "考生的年龄输入非法，请重新输入" << endl;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> age;
  }

  cin >> exam_category;
  while (cin.fail()) {
    if (-1 != i) {
      cout << "第" << i + 1 << "个考生的报考类别输入非法，请从第" << i + 1 << "个考生的报考类别开始重新输入" << endl;
    }
    else {
      cout << "考生的报考类别输入非法，请重新输入" << endl;
    }
    memset(exam_category, 0, sizeof(exam_category));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_category;
  }
}

// 初始化考生信息系统
void InitExamSystem() {
  cout << "首先请建立考生信息系统！" << endl;
  cout << "请输入考生人数(1-2147483647)：";
  int student_num;
  cin >> student_num;
  while (cin.fail()) {
    cin.clear(); // 清除错误状态
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃缓冲区中的非法输入
    cout << "人数输入非法，请重新输入" << endl;
    cin >> student_num;
  }
  RulesPrint();
  cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;

  for (int i = 0; i < student_num; ++i) {
    char exam_id[MAX_ID_SIZE + 1], name[MAX_NAME_SIZE + 1], gender[MAX_GENDER_SIZE + 1], exam_category[MAX_CATEGORY_SIZE + 1];
    int age;
    AllInfoInput(exam_id, name, gender, age, exam_category, i);
    stu_list.InsertStudent(exam_id, name, gender, age, exam_category, i + 1); // 学生插入到链表的最后位置
  }
}

// 包括错误处理和提示的插入操作 [1] 
void InsertOperate() {
  int pos;
  cout << "请输入你要插入考生的位置(1为第一个位置)：";
  cin >> pos;
  while (cin.fail()) {
    cout << "位置输入非法，请重新输入" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> pos;
  }
  RulesPrint();
  cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;
  char exam_id[MAX_ID_SIZE + 1], name[MAX_NAME_SIZE + 1], gender[MAX_GENDER_SIZE + 1], exam_category[MAX_CATEGORY_SIZE + 1];
  int age;
  AllInfoInput(exam_id, name, gender, age, exam_category);
  stu_list.InsertStudent(exam_id, name, gender, age, exam_category, pos);
}

// 包括错误处理和提示的删除操作 [2] 
void DeleteOperate() {
  cout << "请输入要删除的考生的考号" << endl;
  char exam_id[MAX_ID_SIZE + 1];
  cin >> exam_id;
  while (cin.fail()) {
    cout << "输入考号不合法，请重新输入" << endl;
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }
  stu_list.DeleteStudent(exam_id);
}

// 包括错误处理和提示的查找操作 [3] 
void SearchOperate() {
  cout << "请输入要查询的考生的考号" << endl;
  char exam_id[MAX_ID_SIZE + 1];
  cin >> exam_id;
  while (cin.fail()) {
    cout << "输入考号不合法，请重新输入" << endl;
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }

  Student* searched_stu = stu_list.SearchStudent(exam_id);
  if (nullptr == searched_stu) {
    cout << "没有找到该考号的考生" << endl;
  }
  else {
    cout << "-------------------您查询的考生信息--------------------------" << endl;
    cout << "考号      姓名      性别      年龄      报考类别     " << endl;
    searched_stu->Display();
    cout << "-------------------------------------------------------------" << endl;
  }
}

// 包含错误处理和提示的修改操作 [4]
void ModifyOperate() {
  cout << "请依次输入被修改考生的考号以及修改后的姓名，性别，年龄及报考类别：" << endl;
  char exam_id[MAX_ID_SIZE + 1], name[MAX_NAME_SIZE + 1], gender[MAX_GENDER_SIZE + 1], exam_category[MAX_CATEGORY_SIZE + 1];
  int age;
  cin >> exam_id;
  while (cin.fail() || stu_list.IsIdValid(exam_id)) {
    cout << "考生的考号输入非法，请重新输入" << endl;
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }
  
  cin >> name;
  while (cin.fail()) {
    cout << "考生的姓名输入非法，请重新输入" << endl;
    memset(name, 0, sizeof(name));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> name;
  }

  cin >> gender;
  while (cin.fail() || (strcmp(gender, "男") != 0 && strcmp(gender, "女") != 0)) {
    cout << "考生的性别输入非法，请重新输入" << endl;
    memset(gender, 0, sizeof(gender));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> gender;
  }

  cin >> age;
  while (cin.fail()) {
    cout << "考生的年龄输入非法，请重新输入" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> age;
  }

  cin >> exam_category;
  while (cin.fail()) {
    cout << "考生的报考类别输入非法，请重新输入" << endl;
    memset(exam_category, 0, sizeof(exam_category));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_category;
  }
  stu_list.ModifyStudent(exam_id, name, gender, age, exam_category);
}

// 统计操作 [5]
void StatisticsOperate() {
  stu_list.Statistics();
}

// 对学生链表进行增删查改和统计操作
void StuListOperate(int& choice) {
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "|   输入   |    1    |    2    |    3    |    4    |    5    |      0     |" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "|   操作   |   插入  |   删除  |   查找  |   修改  |   统计  |  取消操作  |" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "请选择您要进行的操作（输入0-5的一个整数）：" << endl;
  cin >> choice;
  while (cin.fail()) {
    cout << "操作输入非法，请重新输入" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> choice;
  }

  while (cin.good() && (choice < 0 || choice > 5)) {
    cout << "输入的不是0-5之间的整数,请重新输入" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> choice;
  }

  cout << "您选择的操作为" << choice << endl;

  if (1 == choice) {
    InsertOperate();
    stu_list.DisplayStudents();
  }
  else if (2 == choice) {
    DeleteOperate();
    stu_list.DisplayStudents();
  }
  else if (3 == choice) {
    SearchOperate();
  }
  else if (4 == choice) {
    ModifyOperate();
    stu_list.DisplayStudents();
  }
  else if (5 == choice) {
    StatisticsOperate();
  }
  else {
    return;
  }
}

int main() {
  InitExamSystem();
  stu_list.DisplayStudents();
  int choice = -1; // 初始化为-1
  while (choice != 0) {
    StuListOperate(choice);
  }

  return 0;
}
