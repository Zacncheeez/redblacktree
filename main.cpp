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

    // ---------------- ROTATIONS ----------------
    void rotateLeft(Node* x) {
        Node* y = x->right;
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

    // ---------------- FIX INSERT ----------------
    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* gp = z->parent->parent;

            if (z->parent == gp->left) {
                Node* uncle = gp->right;

                // Case 1: Uncle is RED
                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                }
                else {
                    // Case 2: z is right child
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    // Case 3: z is left child
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rotateRight(gp);
                }
            }
            else {
                Node* uncle = gp->left;

                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rotateLeft(gp);
                }
            }
        }

        root->color = BLACK;
    }

    // ---------------- PRINT TREE ----------------
    void printHelper(Node* node, int indent) {
        if (!node) return;

        indent += 6;

        printHelper(node->right, indent);

        cout << endl;
        for (int i = 6; i < indent; i++)
            cout << " ";
        cout << node->key << (node->color == RED ? "(R)" : "(B)") << endl;

        printHelper(node->left, indent);
    }

public:
    RBTree() : root(nullptr) {}

    // ---------------- INSERT ----------------
    void insert(int key) {
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

    // ---------------- PUBLIC PRINT ----------------
    void print() {
        cout << "\n===== TREE =====\n";
        printHelper(root, 0);
        cout << "================\n";
    }
};

int main() {
    RBTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(15);
    tree.insert(5);
    tree.insert(1);
    tree.insert(25);
    tree.insert(2);

    tree.print();

    return 0;
}
