
//AVL
class Node
{
public:
    int val;
    Node *right;
    Node *left;
    int height;
    Node(int val) : val(val)
    {
        right = nullptr;
        left = nullptr;
        height = 1;
    }
};

class AVL
{
public:
    Node *root;
    AVL()
    {
        root = nullptr;
    }
    int height(Node *node)
    {
        return node ? node->height : 0;
    }
    int Balance(Node *node)
    {
        return height(node->left) - height(node->right);
    }
    Node *LeftRotate(Node *node)
    {
        Node *temp = node->right;
        Node *tempLeft = temp->left;
        temp->left = node;
        node->right = tempLeft;
        node->height = 1 + max(height(node->left), height(node->right));
        temp->height = 1 + max(height(temp->left), height(temp->right));
        return temp;
    }
    Node *RightRotate(Node *node)
    {
        Node *temp = node->left;
        Node *tempRight = temp->right;
        temp->right = node;
        node->left = tempRight;
        node->height = 1 + max(height(node->left), height(node->right));
        temp->height = 1 + max(height(temp->left), height(temp->right));
        return temp;
    }
    Node *InsertAVL(int newVal, Node *root)
    {
        if (root == nullptr)
        {
            Node *newNode = new Node(newVal);
            root = newNode;
            return newNode;
        }
        else
        {
            if (newVal > root->val)
            {
                root->right = InsertAVL(newVal, root->right);
            }
            else if (newVal < root->val)
            {
                root->left = InsertAVL(newVal, root->left);
            }
            else
            {
                return root;
            }
            root->height = 1 + max(height(root->left), height(root->right));
            int BalanceFactor = Balance(root);

            if (BalanceFactor > 1 && newVal < root->left->val)
            {
                root = RightRotate(root);
            }
            // Left rotate
            else if (BalanceFactor < -1 && newVal > root->right->val)
            {
                root = LeftRotate(root);
            }

            else if (BalanceFactor > 1 && newVal > root->left->val)
            {
                root->left = LeftRotate(root->left);
                return RightRotate(root);
            }
            else if (BalanceFactor < -1 && newVal < root->right->val)
            {
                root->right = RightRotate(root->right);
                return LeftRotate(root);
            }
        }
        return root;
    }
    void insert(int val)
    {
        root = InsertAVL(val, root);
    }

    void Inorder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        else
        {
            Inorder(root->left);
            cout << root->val << " ";
            Inorder(root->right);
        }
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *DeleteAVL(Node *root, int val)
    {
        if (!root)
            return root;

        if (val < root->val)
            root->left = DeleteAVL(root->left, val);
        else if (val > root->val)
            root->right = DeleteAVL(root->right, val);
        else
        {

            if (!root->left || !root->right)
            {
                Node *temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {

                Node *temp = minValueNode(root->right);
                root->val = temp->val;
                root->right = DeleteAVL(root->right, temp->val);
            }
        }

        if (!root)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int BalanceFactor = Balance(root);

        if (BalanceFactor > 1 && Balance(root->left) >= 0)
            return RightRotate(root);

        if (BalanceFactor > 1 && Balance(root->left) < 0)
        {
            root->left = LeftRotate(root->left);
            return RightRotate(root);
        }

        if (BalanceFactor < -1 && Balance(root->right) <= 0)
            return LeftRotate(root);

        if (BalanceFactor < -1 && Balance(root->right) > 0)
        {
            root->right = RightRotate(root->right);
            return LeftRotate(root);
        }

        return root;
    }

    void remove(int val)
    {
        root = DeleteAVL(root, val);
    }
};

//BST
struct Node
{
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST
{
    Node *root;

    Node *insert(Node *node, int val)
    {
        if (!node)
            return new Node(val);
        if (val < node->val)
            node->left = insert(node->left, val);
        else if (val > node->val)
            node->right = insert(node->right, val);
        return node;
    }

    bool search(Node *node, int val)
    {
        if (!node)
            return false;
        if (node->val == val)
            return true;
        if (val < node->val)
            return search(node->left, val);
        return search(node->right, val);
    }

    Node *findMin(Node *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    Node *remove(Node *node, int val)
    {
        if (!node)
            return nullptr;
        if (val < node->val)
            node->left = remove(node->left, val);
        else if (val > node->val)
            node->right = remove(node->right, val);
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }
            else if (!node->left)
            {
                Node *r = node->right;
                delete node;
                return r;
            }
            else if (!node->right)
            {
                Node *l = node->left;
                delete node;
                return l;
            }
            else
            {
                Node *m = findMin(node->right);
                node->val = m->val;
                node->right = remove(node->right, m->val);
            }
        }
        return node;
    }

    void inorder(Node *node)
    {
        if (!node)
            return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void preorder(Node *node)
    {
        if (!node)
            return;
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node *node)
    {
        if (!node)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }

    void clear(Node *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    bool search(int val) { return search(root, val); }
    void remove(int val) { root = remove(root, val); }
    void inorder()
    {
        inorder(root);
        cout << endl;
    }
    void preorder()
    {
        preorder(root);
        cout << endl;
    }
    void postorder()
    {
        postorder(root);
        cout << endl;
    }

    ~BST() { clear(root); }
};

//Heap
class MinHeap
{
public:
    int arr[1000];
    int size;

    MinHeap()
    {
        size = 0;
    }

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyDown(int i)
    {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && arr[l] < arr[smallest])
            smallest = l;
        if (r < size && arr[r] < arr[smallest])
            smallest = r;

        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i)
    {
        while (i > 0 && arr[parent(i)] > arr[i])
        {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    void insert(int val)
    {
        arr[size] = val;
        size++;
        heapifyUp(size - 1);
    }

    int extractMin()
    {
        if (size == 0)
            return -1;
        int root = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return root;
    }

    void buildHeap(int input[], int n)
    {
        size = n;
        for (int i = 0; i < n; i++)
            arr[i] = input[i];
        for (int i = size / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void heapSort()
    {
        int originalSize = size;
        for (int i = 0; i < originalSize; i++)
        {
            int minVal = extractMin();
            arr[i] = minVal;
        }
        size = originalSize;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};
//Bucket Hash
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* next;
    Node(int k) { key = k; next = NULL; }
};

class BucketHash {
    int bucketCount;
    Node** table;

    int hashFunc(int key) {
        return key % bucketCount;
    }

public:
    BucketHash(int b = 10) {
        bucketCount = b;
        table = new Node*[bucketCount];
        for (int i = 0; i < bucketCount; i++)
            table[i] = NULL;
    }

    ~BucketHash() {
        for (int i = 0; i < bucketCount; i++) {
            Node* cur = table[i];
            while (cur) {
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] table;
    }

    void insertKey(int key) {
        int idx = hashFunc(key);
        Node* n = new Node(key);
        n->next = table[idx];
        table[idx] = n;
    }

    bool searchKey(int key) {
        int idx = hashFunc(key);
        Node* cur = table[idx];
        while (cur) {
            if (cur->key == key) return true;
            cur = cur->next;
        }
        return false;
    }

    void deleteKey(int key) {
        int idx = hashFunc(key);
        Node* cur = table[idx];
        Node* prev = NULL;

        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next;
                else table[idx] = cur->next;
                delete cur;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    void display() {
        for (int i = 0; i < bucketCount; i++) {
            cout << "Bucket " << i << ": ";
            Node* cur = table[i];
            while (cur) {
                cout << cur->key << " -> ";
                cur = cur->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    BucketHash h(5);

    h.insertKey(12);
    h.insertKey(22);
    h.insertKey(32);
    h.insertKey(7);
    h.insertKey(17);

    cout << "Hash table:\n";
    h.display();

    cout << "\nSearch 22: " << (h.searchKey(22) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (h.searchKey(99) ? "Found" : "Not Found") << endl;

    cout << "\nDelete 22\n";
    h.deleteKey(22);
    h.display();

    return 0;
}


//Hash Double
class Hashing
{
    int size;
    int count;
    int *arr;
    int prime;

public:
    Hashing(int s)
    {
        size = s;
        arr = new int[size];
        count = 0;
        prime = getPrime();
        for (int i = 0; i < size; i++)
            arr[i] = -1;
    }

    ~Hashing()
    {
        delete[] arr;
    }

    int getPrime()
    {
        return size - 1;
    }

    int hash1(int key)
    {
        return key % size;
    }

    int hash2(int key)
    {
        return prime - (key % prime);
    }

    bool IsFull()
    {
        return count == size;
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    float LoadFactor()
    {
        return (float)count / size;
    }

    void rehash()
    {
        int oldSize = size;
        int *oldArr = arr;

        size = size * 2;
        arr = new int[size];
        count = 0;
        prime = getPrime();

        for (int i = 0; i < size; i++)
            arr[i] = -1;

        for (int i = 0; i < oldSize; i++)
            if (oldArr[i] >= 0)
                InsertKey(oldArr[i]);

        delete[] oldArr;
    }

    void InsertKey(int key)
    {
        if (LoadFactor() > 0.7)
            rehash();

        int h1 = hash1(key);
        int h2 = hash2(key);
        int idx = h1;
        int i = 1;

        while (arr[idx] >= 0)
        {
            idx = (h1 + i * h2) % size;
            i++;
            if (i > size)
                return;
        }

        arr[idx] = key;
        count++;
    }

    bool SearchKey(int key)
    {
        int h1 = hash1(key);
        int h2 = hash2(key);
        int idx = h1;
        int i = 1;
        int probes = 0;

        while (arr[idx] != -1 && probes < size)
        {
            if (arr[idx] == key)
                return true;
            idx = (h1 + i * h2) % size;
            i++;
            probes++;
        }
        return false;
    }

    bool DeleteKey(int key)
    {
        int h1 = hash1(key);
        int h2 = hash2(key);
        int idx = h1;
        int i = 1;
        int probes = 0;

        while (arr[idx] != -1 && probes < size)
        {
            if (arr[idx] == key)
            {
                arr[idx] = -2;
                count--;
                return true;
            }
            idx = (h1 + i * h2) % size;
            i++;
            probes++;
        }
        return false;
    }

    void Clear()
    {
        for (int i = 0; i < size; i++)
            arr[i] = -1;
        count = 0;
    }

    void Print()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

//Hash quad
class Hashing
{
    int size;
    int *HashArray;
    int count;

    int hashFunction(int key)
    {
        return key % size;
    }

    double loadFactor()
    {
        return (double)count / size;
    }

    void rehash()
    {
        int oldSize = size;
        int *oldArr = HashArray;

        size = size * 2 + 1;
        HashArray = new int[size];
        for (int i = 0; i < size; i++)
            HashArray[i] = -1;

        count = 0;

        for (int i = 0; i < oldSize; i++)
            if (oldArr[i] >= 0)
                InsertKey(oldArr[i]);

        delete[] oldArr;
    }

public:
    Hashing(int s) : size(s), count(0)
    {
        HashArray = new int[size];
        for (int i = 0; i < size; i++)
            HashArray[i] = -1;
    }

    void InsertKey(int key)
    {
        if (loadFactor() >= 0.7)
            rehash();

        int idx = hashFunction(key);
        int start = idx;
        int i = 1;

        while (HashArray[idx] >= 0)
        {
            idx = (start + i * i) % size;
            i++;
            if (idx == start)
                return;
        }

        HashArray[idx] = key;
        count++;
    }

    bool SearchKey(int key)
    {
        int idx = hashFunction(key);
        int start = idx;
        int i = 1;
        int probes = 0;

        while (HashArray[idx] != -1 && probes < size)
        {
            if (HashArray[idx] == key)
                return true;

            idx = (start + i * i) % size;
            i++;
            probes++;
        }
        return false;
    }

    void DeleteKey(int key)
    {
        int idx = hashFunction(key);
        int start = idx;
        int i = 1;
        int probes = 0;

        while (HashArray[idx] != -1 && probes < size)
        {
            if (HashArray[idx] == key)
            {
                HashArray[idx] = -2;
                count--;
                return;
            }
            idx = (start + i * i) % size;
            i++;
            probes++;
        }
    }

    void Clear()
    {
        for (int i = 0; i < size; i++)
            HashArray[i] = -1;
        count = 0;
    }

    int Count()
    {
        return count;
    }

    void PrintHash()
    {
        for (int i = 0; i < size; i++)
            cout << HashArray[i] << " ";
        cout << endl;
    }

    ~Hashing()
    {
        delete[] HashArray;
    }
};

//Hash Linear
class Hashing
{
    int size;
    int *HashArray;

public:
    Hashing(int s) : size(s)
    {
        HashArray = new int[size];
        for (int i = 0; i < size; i++)
            HashArray[i] = -1;
    }
    int hashFunction(int value)
    {
        return value % size;
    }
    void InsertKey(int key)
    {
        int idx = hashFunction(key);
        int start = idx;
        while (HashArray[idx] != -1)
        {
            idx = (idx + 1) % size;
            if (idx == start)
                return;
        }

        HashArray[idx] = key;
    }
    void PrintHash()
    {
        for (int i = 0; i < size; i++)
        {
            cout << HashArray[i] << " ";
        }
    }

    bool SearchKey(int key)
    {
        int idx = hashFunction(key);
        int start = idx;
        while (HashArray[idx] != -1)
        {
            if (key == HashArray[idx])
                return true;
            else
            {
                idx = (idx + 1) % size;
            }
            if (idx == start)
            {
                break;
            }
        }
        return false;
    }
};

//boyer
// Boyer-Moore
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define NO_OF_CHARS 256

void badCharHeuristic(const string &pattern, vector<int> &badChar)
{
    int m = pattern.length();
    for (int i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;
    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;
}

void boyerMooreSearch(const string &text, const string &pattern)
{
    int n = text.length();
    int m = pattern.length();

    vector<int> badChar(NO_OF_CHARS);
    badCharHeuristic(pattern, badChar);

    int s = 0;
    while (s <= n - m)
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0)
        {
            cout << "Pattern found at index " << s << endl;

            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else
        {
            int shift = max(1, j - badChar[text[s + j]]);
            s += shift;
        }
    }
}

//brute
void bruteForceSearch(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;

        while (j < m && text[i + j] == pattern[j])
        {
            j++;
        }

        if (j == m)
        { // Match found
            cout << "Pattern found at index " << i << endl;
        }
    }
}

//rabin Karp
void rabinKarp(string text, string pattern, int q)
{
    int n = text.length();
    int m = pattern.length();

    if (m == 0 || m > n)
    {
        cout << "No valid pattern to search.\n";
        return;
    }

    int p = 0;
    int t = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++)
    {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++)
    {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++)
    {

        if (p == t)
        {
            bool match = true;
            for (int j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                cout << "Pattern found at index " << i << endl;
            }
        }

        if (i < n - m)
        {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)
                t = t + q;
        }
    }
}

//KMP
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void computeLPSArray(const string &pattern, vector<int> &lps)
{
    int m = pattern.length();
    lps[0] = 0;
    int len = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(const string &text, const string &pattern)
{
    int n = text.length();
    int m = pattern.length();
    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
}

// Queue
class Queue
{
    int *arr;
    int front, rear, size, capacity;

public:
    Queue(int cap)
    {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == capacity;
    }

    void enqueue(int x)
    {
        if (!isFull())
        {
            rear = (rear + 1) % capacity;
            arr[rear] = x;
            size++;
        }
    }

    int dequeue()
    {
        if (!isEmpty())
        {
            int val = arr[front];
            front = (front + 1) % capacity;
            size--;
            return val;
        }
        return -1;
    }

    int peek()
    {
        if (!isEmpty())
            return arr[front];
        return -1;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }

    
};

//Stack
class Stack
{
    int *arr;
    int top;
    int size;

public:
    Stack(int s)
    {
        size = s;
        arr = new int[size];
        top = -1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == size - 1;
    }

    void push(int x)
    {
        if (!isFull())
        {
            arr[++top] = x;
        }
    }

    int pop()
    {
        if (!isEmpty())
        {
            return arr[top--];
        }
        return -1;
    }

    int peek()
    {
        if (!isEmpty())
        {
            return arr[top];
        }
        return -1;
    }

    void print()
    {
        for (int i = 0; i <= top; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

  
};

// merge sort
void mergeArr(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        mergeArr(arr, l, m, r);
    }
}

//quick sort
int partitionArr(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }

    int t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partitionArr(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}


