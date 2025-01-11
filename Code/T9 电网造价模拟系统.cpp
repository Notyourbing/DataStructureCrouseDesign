/*赵卓冰 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <climits>
// 条件编译，解决window和linux的差异
#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

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
    Vector(size_t n, const T& value) : capacity(n), size(n) {
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

    void Resize(size_t new_size, const T& default_value = T()) {
        if (new_size > capacity) {
            size_t new_capacity = max(new_size, capacity * 2);
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i]; // 复制原有元素
            }
            for (size_t i = size; i < new_size; ++i) {
                new_data[i] = default_value; // 初始化新分配的空间
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

    // 访问指定位置的元素（不带边界检查）
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // 赋值操作符
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data;  // 释放当前数据的内存
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

// 定义任务结构体，增加输入时的索引
struct Task {
    int start, end, duration, index;
};

// 项目调度类
class Scheduler {
private:
    int num_nodes; // 节点数量
    int num_tasks; // 任务数量
    Vector<Task> tasks; // 存储所有任务
    Vector<Vector<pair<int, int> > > graph; // 邻接表存任务图
    Vector<int> in_degree; // 入度数组
    Vector<int> earliest; // 最早完成时间
    Vector<int> latest; // 最迟完成时间

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

    // 拓扑排序
    bool TopologicalSort(Vector<int>& topo_order) {
        Queue<int> q;

        // 将所有入度为0的节点入队
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

                // 更新最早完成时间
                earliest[next] = max(earliest[next], earliest[node] + duration);

                // 减少入度
                in_degree[next]--;
                if (in_degree[next] == 0) {
                    q.Push(next);
                }
            }
        }

        // 判断是否存在环
        return topo_order.Size() == num_nodes;
    }

    void CalculateCriticalPath() {
        Vector<int> topo_order;

        // 拓扑排序
        if (!TopologicalSort(topo_order)) {
            cout << 0 << endl; // 不可调度
            return;
        }

        // 项目总时长
        int project_time = 0;
        for (auto element : earliest) {
            project_time = max(project_time, element);
        }
        latest[topo_order[topo_order.Size() - 1]] = project_time;

        // 倒序计算最晚万策划给你时间
        for (int i = topo_order.Size() - 1; i >= 0; --i) {
            int node = topo_order[i];
            for (auto& edge : graph[node]) {
                int next = edge.first;
                int duration = edge.second;
                latest[node] = min(latest[node], latest[next] - duration);
            }
        }

        // 找关键活动
        Vector<int> critical_activities;  // 存储关键活动的任务索引
        for (size_t i = 0; i < tasks.Size(); ++i) {
            const auto& task = tasks[i];
            int start = task.start;
            int end = task.end;
            int duration = task.duration;

            // 判断时间余量是否为0
            if (earliest[start] + duration == latest[end]) {
                critical_activities.PushBack(i);  // 存储任务索引
            }
        }

        // 排序
        size_t n = critical_activities.Size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                const auto& task_a = tasks[critical_activities[j]];
                const auto& task_b = tasks[critical_activities[j + 1]];

                // 比较两个任务，决定是否交换
                if (task_a.start > task_b.start ||
                    (task_a.start == task_b.start && task_a.index < task_b.index)) {
                    // 交换
                    swap(critical_activities[j], critical_activities[j + 1]);
                }
            }
        }

        // 输出结果
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

    // 创建项目调度器
    Scheduler scheduler(n, m);

    // 输入任务
    for (int i = 0; i < m; ++i) {
        int start, end, duration;
        cin >> start >> end >> duration;
        scheduler.AddTask(start, end, duration, i);
    }

    // 计算并输出关键路径
    scheduler.CalculateCriticalPath();

    cout << endl << "按回车键退出..." << endl;
#ifdef _WIN32
    while (_getch() != '\r')
        continue;
#endif

    return 0;
}

