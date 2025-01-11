/*��׿�� 2252750*/
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

// ѧ����
class Student {
private:
  char exam_id[MAX_ID_SIZE + 1];      // ׼��֤��
  char name[MAX_NAME_SIZE + 1];        // ����
  char gender[MAX_GENDER_SIZE + 1];    // �Ա�
  int age;                              // ����
  char exam_category[MAX_CATEGORY_SIZE]; // �������
  Student* next;                        // ָ����һ��ѧ���ڵ�

public:
  // ���캯��
  Student(const char* id = "", const char* n = "", const char* g = "", int a = 0, const char* category = "") {
    strcpy(exam_id, id);
    strcpy(name, n);
    strcpy(gender, g);
    age = a;
    strcpy(exam_category, category);
    next = nullptr;
  }

  // ���úͻ�ȡ��һ���ڵ�ָ��
  void SetNext(Student* next_student) {
    next = next_student;
  }

  Student* GetNext() {
    return next;
  }

  // ��ӡ������Ϣ
  void Display() const {
    cout << setiosflags(ios::left);
    cout << setw(10) << exam_id << setw(10) << name << setw(10) << gender
      << setw(10) << age << setw(10) << exam_category << endl;
  }

  // ��ȡ׼��֤��
  const char* GetExamID() const {
    return exam_id;
  }

  const char* GetGender() const {
    return gender;
  }

  const int GetAge() const {
    return age;
  }
  // �޸�ѧ����Ϣ
  void Modify(const char* n, const char* g, int a, const char* category) {
    strcpy(name, n);
    strcpy(gender, g);
    age = a;
    strcpy(exam_category, category);
  }
};

// ѧ��������
class StudentList {
private:
  Student* head;  // �����ͷ�ڵ�ָ��

public:
  // ���캯������ʼ������Ϊ��
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

  // ���뿼����Ϣ
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

  // ��ʾ���п�����Ϣ
  void DisplayStudents() const {
    cout << endl;
    if (head == nullptr) {
      cout << "���޿�����Ϣ��" << endl;
      return;
    }
    cout << "------------------���п�����Ϣ---------------------" << endl;
    cout << "����      ����      �Ա�      ����      �������     " << endl;
    Student* temp = head;
    while (temp != nullptr) {
      temp->Display();
      temp = temp->GetNext();
    }
    cout << "---------------------------------------------------" << endl;
  }

  // ��ѯ������Ϣ
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

  // �޸Ŀ�����Ϣ
  void ModifyStudent(const char* exam_id, const char* name, const char* gender, int age, const char* category) {
    Student* student = SearchStudent(exam_id);
    if (student == nullptr) {
      cout << "δ�ҵ��ÿ�����Ϣ��" << endl;
    }
    else {
      student->Modify(name, gender, age, category);
      cout << "������Ϣ�Ѹ��¡�" << endl;
    }
  }

  // ɾ��������Ϣ
  void DeleteStudent(const char* exam_id) {
    cout << endl;
    if (head == nullptr) {
      cout << "�б�Ϊ�գ��޷�ɾ����" << endl;
      return;
    }

    if (strcmp(head->GetExamID(), exam_id) == 0) {
      Student* temp = head;
      head = head->GetNext();
      delete temp;
      cout << "������Ϣ��ɾ����" << endl;
      return;
    }

    Student* current = head;
    Student* previous = nullptr;
    while (current != nullptr && strcmp(current->GetExamID(), exam_id) != 0) {
      previous = current;
      current = current->GetNext();
    }

    if (current == nullptr) {
      cout << "δ�ҵ��ÿ�����Ϣ��" << endl;
    }
    else {
      previous->SetNext(current->GetNext());
      delete current;
      cout << "������Ϣ��ɾ����" << endl;
    }
  }

  // �ж�new_exam_id�Ƿ�Ϸ����Ϸ���ζ�ź�ÿһ���Ѿ����ڵ�exam_id��ͬ����Ϊȫ��Ϊ����
  bool IsIdValid(char* new_exam_id) {
    // ����Ƿ����ȫ����Ҫ��
    char* temp_id = new_exam_id;
    while (*temp_id != 0) {
      if (*temp_id < '0' || *temp_id > '9') {
        return false;
      }
      ++temp_id;
    }
    // ����Ƿ���Ѿ����ڵ�exam_id����ͬ��
    Student* temp = head;
    while (temp != nullptr) {
      if (strcmp(temp->GetExamID(), new_exam_id) == 0) {
        return false;
      }
      temp = temp->GetNext();
    }
    return true;
  }

  // ͳ����Ů�ٷֱȣ���������İٷֱ�
  void Statistics() {
    Student* temp = head;
    int male_num = 0;
    int female_num = 0;
    unsigned int age_num[100] = {0}; // age[i] ��ʾ����Ϊi���˵�����
    while (temp != nullptr) {
      if (strcmp(temp->GetGender(), "��") == 0) {
        ++male_num;
      }
      else {
        ++female_num;
      }
      ++age_num[temp->GetAge()];
      temp = temp->GetNext();
    }
    double male_ratio =100 * double(male_num) / double(male_num + female_num);
    cout << "-----------------ͳ�ƽ��--------------------" << endl;
    cout << "����ռ�ȣ�"<< setprecision(3) << male_ratio << "%" << endl;
    cout << "Ů��ռ�ȣ�" << setprecision(3) << 100 - male_ratio << "%" << endl;
    for (int i = 0; i < 100; ++i) {
      if (age_num[i]) {
        cout << i << "��,��   " << age_num[i] << "��" << endl;
      }
    }
    cout << "---------------------------------------------" << endl;
  }

  // �����������ͷ������е����нڵ�
  ~StudentList() {
    while (head != nullptr) {
      Student* temp = head;
      head = head->GetNext();
      delete temp;
    }
  }
} stu_list;

// ��ӡ�������
void RulesPrint() {
  cout << endl;
  cout << "-----------------------������Ϣ�������-----------------------" << endl;
  cout << "|���ţ�    |��0-9�Ĺ��ɵ��ַ��������Ȳ�����20                |" << endl;
  cout << "|������    |�ַ�����Ӣ�Ĳ�����50���ַ������Ĳ�����25����     |" << endl;
  cout << "|�Ա�    |�л�Ů                                           |" << endl;
  cout << "|���䣺    |������1-150֮��                                  |" << endl;
  cout << "|�������|�ַ�����Ӣ�Ĳ�����30���ַ������Ĳ�����15����     |" << endl;
  cout << "|ע�⣺    |����֮���ÿո��س��ָ�                         |" << endl;
  cout << "--------------------------------------------------------------" << endl;
}

// ����һ��������������Ϣ��Ĭ��ֵ����i���ڳ�ʼ��ʱʹ�õģ������ʹ���������Ĭ��ֵ�������Ρ�
void AllInfoInput(char* exam_id, char* name, char* gender, int& age, char* exam_category, const int i = -1) {
  cin >> exam_id;
  while (cin.fail() || !stu_list.IsIdValid(exam_id)) {

    if (-1 != i) {
      cout << "��" << i + 1 << "�������Ŀ�������Ƿ�����ӵ�" << i + 1 << "�������Ŀ��ſ�ʼ��������" << endl;
    }
    else {
      cout << "�����Ŀ�������Ƿ�������������" << endl;
    }
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }

  cin >> name;
  while (cin.fail()) {
    if (-1 != i) {
      cout << "��" << i + 1 << "����������������Ƿ�����ӵ�" << i + 1 << "��������������ʼ��������" << endl;
    }
    else {
      cout << "��������������Ƿ�������������" << endl;
    }
    memset(name, 0, sizeof(name));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> name;
  }

  cin >> gender;
  while (cin.fail() || (strcmp(gender, "��") != 0 && strcmp(gender, "Ů") != 0)) {
    if (-1 != i) {
      cout << "��" << i + 1 << "���������Ա�����Ƿ�����ӵ�" << i + 1 << "���������Ա�ʼ��������" << endl;
    }
    else {
      cout << "�������Ա�����Ƿ�������������" << endl;
    }
    memset(gender, 0, sizeof(gender));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> gender;
  }

  cin >> age;
  while (cin.fail()) {
    if (-1 != i) {
      cout << "��" << i + 1 << "����������������Ƿ�����ӵ�" << i + 1 << "�����������俪ʼ��������" << endl;
    }
    else {
      cout << "��������������Ƿ�������������" << endl;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> age;
  }

  cin >> exam_category;
  while (cin.fail()) {
    if (-1 != i) {
      cout << "��" << i + 1 << "�������ı����������Ƿ�����ӵ�" << i + 1 << "�������ı������ʼ��������" << endl;
    }
    else {
      cout << "�����ı����������Ƿ�������������" << endl;
    }
    memset(exam_category, 0, sizeof(exam_category));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_category;
  }
}

// ��ʼ��������Ϣϵͳ
void InitExamSystem() {
  cout << "�����뽨��������Ϣϵͳ��" << endl;
  cout << "�����뿼������(1-2147483647)��";
  int student_num;
  cin >> student_num;
  while (cin.fail()) {
    cin.clear(); // �������״̬
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �����������еķǷ�����
    cout << "��������Ƿ�������������" << endl;
    cin >> student_num;
  }
  RulesPrint();
  cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;

  for (int i = 0; i < student_num; ++i) {
    char exam_id[MAX_ID_SIZE + 1], name[MAX_NAME_SIZE + 1], gender[MAX_GENDER_SIZE + 1], exam_category[MAX_CATEGORY_SIZE + 1];
    int age;
    AllInfoInput(exam_id, name, gender, age, exam_category, i);
    stu_list.InsertStudent(exam_id, name, gender, age, exam_category, i + 1); // ѧ�����뵽��������λ��
  }
}

// �������������ʾ�Ĳ������ [1] 
void InsertOperate() {
  int pos;
  cout << "��������Ҫ���뿼����λ��(1Ϊ��һ��λ��)��";
  cin >> pos;
  while (cin.fail()) {
    cout << "λ������Ƿ�������������" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> pos;
  }
  RulesPrint();
  cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
  char exam_id[MAX_ID_SIZE + 1], name[MAX_NAME_SIZE + 1], gender[MAX_GENDER_SIZE + 1], exam_category[MAX_CATEGORY_SIZE + 1];
  int age;
  AllInfoInput(exam_id, name, gender, age, exam_category);
  stu_list.InsertStudent(exam_id, name, gender, age, exam_category, pos);
}

// �������������ʾ��ɾ������ [2] 
void DeleteOperate() {
  cout << "������Ҫɾ���Ŀ����Ŀ���" << endl;
  char exam_id[MAX_ID_SIZE + 1];
  cin >> exam_id;
  while (cin.fail()) {
    cout << "���뿼�Ų��Ϸ�������������" << endl;
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }
  stu_list.DeleteStudent(exam_id);
}

// �������������ʾ�Ĳ��Ҳ��� [3] 
void SearchOperate() {
  cout << "������Ҫ��ѯ�Ŀ����Ŀ���" << endl;
  char exam_id[MAX_ID_SIZE + 1];
  cin >> exam_id;
  while (cin.fail()) {
    cout << "���뿼�Ų��Ϸ�������������" << endl;
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }

  Student* searched_stu = stu_list.SearchStudent(exam_id);
  if (nullptr == searched_stu) {
    cout << "û���ҵ��ÿ��ŵĿ���" << endl;
  }
  else {
    cout << "-------------------����ѯ�Ŀ�����Ϣ--------------------------" << endl;
    cout << "����      ����      �Ա�      ����      �������     " << endl;
    searched_stu->Display();
    cout << "-------------------------------------------------------------" << endl;
  }
}

// �������������ʾ���޸Ĳ��� [4]
void ModifyOperate() {
  cout << "���������뱻�޸Ŀ����Ŀ����Լ��޸ĺ���������Ա����估�������" << endl;
  char exam_id[MAX_ID_SIZE + 1], name[MAX_NAME_SIZE + 1], gender[MAX_GENDER_SIZE + 1], exam_category[MAX_CATEGORY_SIZE + 1];
  int age;
  cin >> exam_id;
  while (cin.fail() || stu_list.IsIdValid(exam_id)) {
    cout << "�����Ŀ�������Ƿ�������������" << endl;
    memset(exam_id, 0, sizeof(exam_id));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_id;
  }
  
  cin >> name;
  while (cin.fail()) {
    cout << "��������������Ƿ�������������" << endl;
    memset(name, 0, sizeof(name));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> name;
  }

  cin >> gender;
  while (cin.fail() || (strcmp(gender, "��") != 0 && strcmp(gender, "Ů") != 0)) {
    cout << "�������Ա�����Ƿ�������������" << endl;
    memset(gender, 0, sizeof(gender));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> gender;
  }

  cin >> age;
  while (cin.fail()) {
    cout << "��������������Ƿ�������������" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> age;
  }

  cin >> exam_category;
  while (cin.fail()) {
    cout << "�����ı����������Ƿ�������������" << endl;
    memset(exam_category, 0, sizeof(exam_category));
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> exam_category;
  }
  stu_list.ModifyStudent(exam_id, name, gender, age, exam_category);
}

// ͳ�Ʋ��� [5]
void StatisticsOperate() {
  stu_list.Statistics();
}

// ��ѧ�����������ɾ��ĺ�ͳ�Ʋ���
void StuListOperate(int& choice) {
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "|   ����   |    1    |    2    |    3    |    4    |    5    |      0     |" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "|   ����   |   ����  |   ɾ��  |   ����  |   �޸�  |   ͳ��  |  ȡ������  |" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "��ѡ����Ҫ���еĲ���������0-5��һ����������" << endl;
  cin >> choice;
  while (cin.fail()) {
    cout << "��������Ƿ�������������" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> choice;
  }

  while (cin.good() && (choice < 0 || choice > 5)) {
    cout << "����Ĳ���0-5֮�������,����������" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> choice;
  }

  cout << "��ѡ��Ĳ���Ϊ" << choice << endl;

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
  int choice = -1; // ��ʼ��Ϊ-1
  while (choice != 0) {
    StuListOperate(choice);
  }

  return 0;
}
