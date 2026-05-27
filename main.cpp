#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int k)
        : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node* root;

    void rotateLeft(Node* x) {
        Node* y = x->right;
        if (!y) return;

        x->right = y->left;
        if (y->left)
            y->left->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        if (!y) return;

        x->left = y->right;
        if (y->right)
            y->right->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* z) {
        cout << "FixInsert called on key " << z->key << endl;
        root->color = BLACK; // temporary placeholder
    }

public:
    RBTree() : root(nullptr) {}

    void insert(int key) {
        if (key < 0 || key > 999) {
            cout << "Key out of range" << endl;
            return;
        }

        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (!y)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        fixInsert(z);
    }

    void print() {
        cout << "print" << endl;
    }
};

int main() {
    RBTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(15);

    tree.print();

    return 0;
}
