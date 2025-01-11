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

// 并查集类
class UnionFind {
private:
    Vector<int> parent; // 每个节点的父节点
    Vector<int> rank; // 每个节点的秩，用来优化树的高度
    
public:
    UnionFind(int n) {
        parent.Resize(n);
        rank.Resize(n);
        // 初始化，每个节点都是独立的集合
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]); //路径压缩
        }
        return parent[x];
    }

    void Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        if (root_x != root_y) {
            // 按秩合并，保持树的平衡
            if (rank[root_x] > rank[root_y]) {
                parent[root_y] = root_x;
            }
            else if (rank[root_x] < rank[root_y]) {
                parent[root_x] = root_y;
            }
            else {
                parent[root_y] = root_x;
                ++rank[root_x];
            }
        }
    }
};

// 最小堆的比较函数
struct PairGreater {
    bool operator()(const pair<int, int> p1, const pair<int, int> p2) {
        return p1.first < p2.first;
    }
};

// 最小生成树类
class MinSpanTree {
private:
    int vertices; // 图的顶点数
    int mst_cost;
    Vector<char> v_names; // 顶点的名字
    Vector<Vector<int> > graph_matrix; // 图的邻接矩阵
    Vector<Vector<pair<int, int>>> graph_list; // 图的邻接表
    Vector<pair<int, int> > mst_edges; // 最小生成树的边集合

public:
    // 构造函数和析构函数
    MinSpanTree() : vertices(0), mst_cost(0) {}
    ~MinSpanTree() {}

    // 判断空图
    bool Empty() {
        return (vertices == 0);
    }

    // 设置顶点数
    void SetVertices(const int v) {
        vertices = v;
        graph_matrix.Resize(v, Vector<int>(v, 0));
        graph_list.Resize(v);
        v_names.Resize(v);
    }

    // 获取顶点姓名数组
    Vector<char> GetVerticesName() const {
        return v_names;
    }

    // 设置顶点名称
    void SetVerticesName(const Vector<char>& names) {
        if (vertices != names.Size()) {
            throw out_of_range("v_names out of range");
        }
        v_names = names;
    }

    // 添加边
    void AddEdge(const int v1, const int v2, const int value) {
        graph_matrix[v1][v2] = value;
        graph_matrix[v2][v1] = value;
        graph_list[v1].PushBack({ v2, value });
        graph_list[v2].PushBack({ v1, value });
    }
         
    // 邻接矩阵的Prim算法
    void PrimWithMatrix() {
        mst_edges.Clear();
        mst_cost = 0;

        Vector<bool> visited(vertices, false); // 记录节点是否被访问
        Vector<int> min_weight(vertices, INT_MAX); // 到生成树的最小边权值
        Vector<int> parent(vertices, -1); // 记录最小生成树每个节点的父节点
        min_weight[0] = 0; // 从第一个节点开始

        for (int i = 0; i < vertices; ++i) {
            int u = -1, min_edge = INT_MAX;

            // 找到未访问中权值最小的顶点
            for (int v = 0; v < vertices; ++v) {
                if (!visited[v] && min_weight[v] < min_edge) {
                    u = v;
                    min_edge = min_weight[v];
                }
            }
            if (-1 == u) { // 没有可以加入的节点
                break;
            }
            visited[u] = true; // 标记为已经访问
            mst_cost += min_edge; // 累加最小权值
            if (parent[u] != -1) { // u 有父节点
                mst_edges.PushBack({ parent[u], u });
            }
            // 更新邻接节点的最小边权值
            for (int v = 0; v < vertices; ++v) {
                if (graph_matrix[u][v] != 0 && !visited[v] && graph_matrix[u][v] < min_weight[v]) {
                    min_weight[v] = graph_matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // 邻接链表的Prim算法
    void PrimWithList() {
        mst_edges.Clear();
        mst_cost = 0;

        Vector<bool> visited(vertices, false); // 记录节点是否被访问过
        Vector<int> min_weight(vertices, INT_MAX); // 到生成树的最小边权值
        Vector<int> parent(vertices, -1); // 记录最小生成树每个节点的父节点
        min_weight[0] = 0;

        // 优先队列（最小堆）来管理待处理的节点，pair的第一个元素是权值，第二个元素是顶点
        PriorityQueue<pair<int, int>, PairGreater> pq;
        pq.Push({ 0, 0 }); // 初始节点，权值为0

        while (!pq.Empty()) {
            // 取出权值最小的顶点
            int weight = pq.Top().first;
            int u = pq.Top().second;
            pq.Pop();

            if (visited[u]) continue;
            visited[u] = true;
            mst_cost += weight; // 累加当前边的权重

            if (parent[u] != -1) {
                mst_edges.PushBack({ parent[u], u });
            }

            // 遍历当前节点u所有相邻的边
            for (auto& element : graph_list[u]) {
                int& v = element.first;
                int& w = element.second;
                // 如果v未被访问，且该边的权重更小
                if (!visited[v] && w < min_weight[v]) {
                    min_weight[v] = w;
                    parent[v] = u;
                    pq.Push({ w, v }); // 将更新后的节点v加入优先队列
                }

            }
        }

    }

    // Kruskal算法
    void Kruskal() {
        mst_edges.Clear();
        mst_cost = 0;

        // 创建一个并查集
        UnionFind uf(vertices);

        // 将所有边按权重排序，每条边的格式为(weight, (v1, v2))
        Vector<pair<int, pair<int, int > > > edges;

        // 遍历图的所有的边（邻接矩阵表示）
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                if (graph_matrix[i][j] != 0) {
                    edges.PushBack({ graph_matrix[i][j], {i, j} });
                }
            }
        }
        
        // 按照边的权重升序排序
        for (int i = 0; i < edges.Size(); ++i) {
            for (int j = 0; j < edges.Size() - 1 - i; ++j) {
                if (edges[j].first > edges[j + 1].first) {
                    swap(edges[j], edges[j + 1]);
                }
            }
        }

        // 依次处理每条边
        for (auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            // 如果u和v在不同的集合中，就把这条边加入到生成树中
            if (uf.Find(u) != uf.Find(v)) {
                uf.Union(u, v);
                mst_edges.PushBack({ u, v });
                mst_cost += weight;
            }
        }

    }

    // 获取最小花费
    int GetMstCost() const {
        return mst_cost;
    }

    // 打印最小生成树
    void Disp() {
        cout << "最小生成树的边:\n";
        for (int i = 0; i < mst_edges.Size(); ++i) {
            auto temp = mst_edges[i];
            cout << v_names[mst_edges[i].first] << "---" << v_names[mst_edges[i].second] << " :" << graph_matrix[mst_edges[i].first][mst_edges[i].second] << endl;
        }
    }
};

// 打印标题
void PrintTitle() {
    cout << "|------------------------------------------------|" << endl;
    cout << "|                电网造价模拟系统                |" << endl;
    cout << "|------------------------------------------------|" << endl;
    cout << "|                A---创建电网顶点                |" << endl;
    cout << "|                B---添加电网的边                |" << endl;
    cout << "|                C---选择最小生成树算法          |" << endl;
    cout << "|                D---显示最小生成树              |" << endl;
    cout << "|                E---退出程序                    |" << endl;
    cout << "|------------------------------------------------|" << endl;
    cout << endl;
}

int main() {
    PrintTitle();
    char choice;

    MinSpanTree min_span_tree;
    int vertices = 0;
    while (1) {
        cout << endl << "请选择操作：";
        cin >> choice;
        if (choice >= 'a' && choice <= 'z') {
            choice = choice - 'a' + 'A';
        }
        if ('A' == choice) {
            cout << "请输入顶点个数" << endl;
            while (true) {
                cin >> vertices;
                if (cin.fail() || vertices <= 0) {
                    cin.clear();  // 清除错误标志
                    cin.ignore(INT_MAX, '\n');  // 清空输入缓存
                    cout << "输入无效，请重新输入顶点个数（大于0）：" << endl;
                }
                else {
                    break;
                }
            }
            min_span_tree.SetVertices(vertices);
            cout << "请依次输入各顶点的名称" << endl;
            Vector<char> v_names(vertices);
            for (int i = 0; i < vertices; ++i) {
                cin >> v_names[i];
            }
            min_span_tree.SetVerticesName(v_names);
            cout << "顶点输入成功" << endl;
        }
        else if ('B' == choice) {
            if (vertices == 0) {
                cout << "图没有顶点" << endl;
                break;
            }
            while (1) {
                cout << "请输入两个边顶点名称及边的权值(输入0结束)" << endl;
                char name1, name2;
                int value;
                cin >> name1;
                if (name1 == '0') {
                    cout << "输入完毕" << endl;
                    break;
                }
                cin >> name2;
                cin >> value;
                Vector<char> v_names = min_span_tree.GetVerticesName();
                int v1 = -1, v2 = -1;
                for (int i = 0; i < v_names.Size(); ++i) {
                    char ch = v_names[i];
                    if (name1 == ch) {
                        v1 = i;
                    }
                    if (name2 == ch) {
                        v2 = i;
                    }
                }
                if (-1 == v1 || -1 == v2 || v1 == v2) {
                    cout << "输入完毕" << endl;
                    break;
                }
                min_span_tree.AddEdge(v1, v2, value);              
            }
        }
        else if ('C' == choice) {
            cout << "请选择最小生成树算法" << endl;
            cout << "---------------------------" << endl;
            cout << " 1---Prim算法（邻接矩阵实现）" << endl;
            cout << " 2---Prim算法（邻接链表实现）" << endl;
            cout << " 3---Kruskal算法" << endl;
            cout << "---------------------------" << endl;

            cout << "你的选择是：";
            int algo;
            cin >> algo;
            if (1 == algo) {
                min_span_tree.PrimWithMatrix();
            }
            else if (2 == algo) {
                min_span_tree.PrimWithList();
            }
            else if (3 == algo) {
                min_span_tree.Kruskal();
            }
            cout<< endl << "最小生成树生成成功!" << endl;
        }
        else if ('D' == choice) {
            min_span_tree.Disp();
            cout << "电网造价最少为：" << min_span_tree.GetMstCost() << endl;
        }
        else if ('E' == choice) {
            break;
        }
    }

    return 0;
}