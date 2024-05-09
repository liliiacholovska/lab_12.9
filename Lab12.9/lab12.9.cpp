#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* insertBST(Node* root, int value);
Node* deleteNode(Node* root, int value);
Node* deleteSubtree(Node* root, int value);
Node* minValueNode(Node* node);
Node* balanceBST(int array[], int start, int end);
void inorderToArray(Node* root, int array[], int* index);
int countNodes(Node* root);
void printTree(Node* root, int space = 0, int highlight = -1);
void deleteTree(Node* root);
int countLeafNodes(Node* root);
Node* createBST(int count);
void fillRandomArray(int arr[], int size);

int main() {
    int choice, value;
    Node* root = nullptr;

    while (true) {
        cout << "1. Create binary search tree\n"; //Створення бінарного дерева/пошуку
        cout << "2. Insert node into BST\n"; //Додавання нового елемента із збереженням порядку
        cout << "3. Delete node from BST\n"; //Видалення елемента, який не має дочірніх вузлів/один/два дочірніх вузла
        cout << "4. Print tree\n"; //Вивід бінарного дерева /пошуку
        cout << "5. Count leaf nodes\n"; //Визначення кількості елементів без дочірніх вузлів
        cout << "6. Balance the BST\n"; //Збалансування бінарного дерева пошуку
        cout << "7. Delete entire subtree\n"; //Видалення елемента з усіма його дочірніми вузлами
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            int count;
            cout << "Enter number of elements: ";
            cin >> count;
            root = createBST(count);
            break;
        case 2:
            cout << "Enter value to insert: ";
            cin >> value;
            root = insertBST(root, value);
            break;
        case 3:
            cout << "Enter value to delete: ";
            cin >> value;
            root = deleteNode(root, value);
            break;
        case 4:
            cout << "Enter value to highlight (or -1 for none): ";
            cin >> value;
            printTree(root, 0, value);
            break;
        case 5:
            cout << "Leaf nodes count: " << countLeafNodes(root) << endl;
            break;
        case 6:
        {
            int size = countNodes(root);
            int* array = new int[size];
            int index = 0;
            inorderToArray(root, array, &index);
            deleteTree(root);
            root = balanceBST(array, 0, size - 1);
            delete[] array;
            break;
        }
        case 7:
            cout << "Enter value of root node of subtree to delete: ";
            cin >> value;
            root = deleteSubtree(root, value);
            break;
        case 8:
            deleteTree(root);
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

Node* createBST(int count) {
    Node* root = nullptr;
    while (count--) {
        int value;
        cout << "Enter value to insert: ";
        cin >> value;
        root = insertBST(root, value);
    }
    return root;
}

void fillRandomArray(int arr[], int size) {
    srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

Node* insertBST(Node* root, int value) {
    if (root == nullptr) {
        return new Node{ value, nullptr, nullptr };
    }
    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

Node* deleteSubtree(Node* root, int value) {
    if (root == nullptr) return nullptr;

    if (value < root->data)
        root->left = deleteSubtree(root->left, value);
    else if (value > root->data)
        root->right = deleteSubtree(root->right, value);
    else {
        deleteTree(root);
        return nullptr;
    }

    return root;
}

void deleteTree(Node* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

void printTree(Node* root, int space, int highlight) {
    if (!root) return;

    space += 10;

    printTree(root->right, space, highlight);

    cout << endl;
    for (int i = 10; i < space; i++) cout << ' ';
    if (root->data == highlight)
        cout << "[" << root->data << "]" << "\n";
    else
        cout << root->data << "\n";

    printTree(root->left, space, highlight);
}

Node* balanceBST(int array[], int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    Node* node = new Node{ array[mid], nullptr, nullptr };
    node->left = balanceBST(array, start, mid - 1);
    node->right = balanceBST(array, mid + 1, end);

    return node;
}

void inorderToArray(Node* root, int array[], int* index) {
    if (root != nullptr) {
        inorderToArray(root->left, array, index);
        array[(*index)++] = root->data;
        inorderToArray(root->right, array, index);
    }
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}