/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <climits>
// �������룬���window��linux�Ĳ���
#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

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
    Vector(size_t n, const T& value) : capacity(n), size(n) {
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

    void Resize(size_t new_size, const T& default_value = T()) {
        if (new_size > capacity) {
            size_t new_capacity = max(new_size, capacity * 2);
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i]; // ����ԭ��Ԫ��
            }
            for (size_t i = size; i < new_size; ++i) {
                new_data[i] = default_value; // ��ʼ���·���Ŀռ�
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        else {
            for (size_t i = size; i < new_size; ++i) {
                data[i] = default_value;
            }
        }
        size = new_size;
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

    // ��ֵ������
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data;  // �ͷŵ�ǰ���ݵ��ڴ�
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
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

// ��������ṹ�壬��������ʱ������
struct Task {
    int start, end, duration, index;
};

// ��Ŀ������
class Scheduler {
private:
    int num_nodes; // �ڵ�����
    int num_tasks; // ��������
    Vector<Task> tasks; // �洢��������
    Vector<Vector<pair<int, int> > > graph; // �ڽӱ������ͼ
    Vector<int> in_degree; // �������
    Vector<int> earliest; // �������ʱ��
    Vector<int> latest; // ������ʱ��

public:
    Scheduler(int n, int m) : num_nodes(n), num_tasks(m) {
        graph = Vector<Vector<pair<int, int> > >(n + 1);
        in_degree = Vector<int>(n + 1, 0);
        earliest = Vector<int>(n + 1, 0);
        latest = Vector<int>(n + 1, INT_MAX);
    }

    void AddTask(int start, int end, int duration, int index) {
        tasks.PushBack({ start, end, duration, index });
        graph[start].PushBack({ end, duration });
        in_degree[end]++;
    }

    // ��������
    bool TopologicalSort(Vector<int>& topo_order) {
        Queue<int> q;

        // ���������Ϊ0�Ľڵ����
        for (int i = 1; i <= num_nodes; ++i) {
            if (in_degree[i] == 0) {
                q.Push(i);
            }
        }

        while (!q.Empty()) {
            int node = q.Front();
            q.Pop();
            topo_order.PushBack(node);

            for (auto& edge : graph[node]) {
                int next = edge.first;
                int duration = edge.second;

                // �����������ʱ��
                earliest[next] = max(earliest[next], earliest[node] + duration);

                // �������
                in_degree[next]--;
                if (in_degree[next] == 0) {
                    q.Push(next);
                }
            }
        }

        // �ж��Ƿ���ڻ�
        return topo_order.Size() == num_nodes;
    }

    void CalculateCriticalPath() {
        Vector<int> topo_order;

        // ��������
        if (!TopologicalSort(topo_order)) {
            cout << 0 << endl; // ���ɵ���
            return;
        }

        // ��Ŀ��ʱ��
        int project_time = 0;
        for (auto element : earliest) {
            project_time = max(project_time, element);
        }
        latest[topo_order[topo_order.Size() - 1]] = project_time;

        // �������������߻�����ʱ��
        for (int i = topo_order.Size() - 1; i >= 0; --i) {
            int node = topo_order[i];
            for (auto& edge : graph[node]) {
                int next = edge.first;
                int duration = edge.second;
                latest[node] = min(latest[node], latest[next] - duration);
            }
        }

        // �ҹؼ��
        Vector<int> critical_activities;  // �洢�ؼ������������
        for (size_t i = 0; i < tasks.Size(); ++i) {
            const auto& task = tasks[i];
            int start = task.start;
            int end = task.end;
            int duration = task.duration;

            // �ж�ʱ�������Ƿ�Ϊ0
            if (earliest[start] + duration == latest[end]) {
                critical_activities.PushBack(i);  // �洢��������
            }
        }

        // ����
        size_t n = critical_activities.Size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                const auto& task_a = tasks[critical_activities[j]];
                const auto& task_b = tasks[critical_activities[j + 1]];

                // �Ƚ��������񣬾����Ƿ񽻻�
                if (task_a.start > task_b.start ||
                    (task_a.start == task_b.start && task_a.index < task_b.index)) {
                    // ����
                    swap(critical_activities[j], critical_activities[j + 1]);
                }
            }
        }

        // ������
        cout << project_time << endl;
        for (int index : critical_activities) {
            const auto& task = tasks[index];
            cout << task.start << "->" << task.end << endl;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    // ������Ŀ������
    Scheduler scheduler(n, m);

    // ��������
    for (int i = 0; i < m; ++i) {
        int start, end, duration;
        cin >> start >> end >> duration;
        scheduler.AddTask(start, end, duration, i);
    }

    // ���㲢����ؼ�·��
    scheduler.CalculateCriticalPath();

    cout << endl << "���س����˳�..." << endl;
#ifdef _WIN32
    while (_getch() != '\r')
        continue;
#endif

    return 0;
}

