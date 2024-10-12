#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node*& node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node*& node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixViolation(Node*& node) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (node != root && node->color == RED && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        Node* newNode = new Node(data);
        if (root == nullptr) {
            newNode->color = BLACK;
            root = newNode;
        } else {
            Node* temp = root;
            Node* parent = nullptr;

            while (temp != nullptr) {
                parent = temp;
                if (data < temp->data)
                    temp = temp->left;
                else
                    temp = temp->right;
            }

            newNode->parent = parent;

            if (data < parent->data)
                parent->left = newNode;
            else
                parent->right = newNode;

            fixViolation(newNode);
        }
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->data << " (" << (node->color == RED ? "RED" : "BLACK") << ") ";
        inorderTraversal(node->right);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);

    cout << "Inorder Traversal of Red-Black Tree: ";
    rbt.display();

    return 0;
}
