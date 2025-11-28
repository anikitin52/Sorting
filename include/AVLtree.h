#pragma once
#ifndef AVLTREE_H_
#define AVLTREE_H_

template<typename KeyType>
class AVLTree {
private:
    struct Node {
        KeyType key;
        int balance;
        Node* left;
        Node* right;

        Node(const KeyType& k, Node* l = nullptr, Node* r = nullptr, int bal = 0)
            : key(k), balance(bal), left(l), right(r) {}
    };

    Node* root_;

private:
    void insertBool(const KeyType& x, Node*& p, bool& h);
    void deleteBool(const KeyType& x, Node*& p, bool& h);
    void inOrderTraversal(Node* node, KeyType* array, int& index) const;

    Node* clone(Node* node) const;
    void clear(Node* node);

    void rotateLL(Node*& p, bool q);
    void rotateLR(Node*& p, bool q);
    void rotateRR(Node*& p, bool q);
    void rotateRL(Node*& p, bool q);

    void balanceLeft(Node*& p, bool& h);
    void balanceRight(Node*& p, bool& h);

public:
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);
    AVLTree(const KeyType* array, int n);
    ~AVLTree();

    void insert(const KeyType& x);
    void remove(const KeyType& x);
    bool is_contain(const KeyType& x) const;
    void toSortedArray(KeyType* array, int size) const;

    void clear();
    bool isEmpty() const;
};

template<typename KeyType>
AVLTree<KeyType>::AVLTree() : root_(nullptr) {}

template<typename KeyType>
AVLTree<KeyType>::AVLTree(const AVLTree& other) {
    root_ = clone(other.root_);
}

template<typename KeyType>
AVLTree<KeyType>& AVLTree<KeyType>::operator=(const AVLTree& other) {
    if (this != &other) {
        clear(root_);
        root_ = clone(other.root_);
    }
    return *this;
}

template<typename KeyType>
AVLTree<KeyType>::~AVLTree() {
    clear(root_);
}

template<typename KeyType>
void AVLTree<KeyType>::clear() {
    clear(root_);
    root_ = nullptr;
}

template<typename KeyType>
bool AVLTree<KeyType>::isEmpty() const {
    return root_ == nullptr;
}

template<typename KeyType>
typename AVLTree<KeyType>::Node* AVLTree<KeyType>::clone(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    return new Node(node->key, clone(node->left), clone(node->right), node->balance);
}

template<typename KeyType>
void AVLTree<KeyType>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename KeyType>
void AVLTree<KeyType>::rotateLL(Node*& p, bool q) {
    Node* p1 = p->left;
    p->left = p1->right;
    p1->right = p;

    if (q) {
        p->balance = 0;
        p1->balance = 0;
    }
    else {
        int b1 = p1->balance;
        if (b1 == 0) {
            p->balance = -1;
            p1->balance = 1;
        }
        else {
            p->balance = 0;
            p1->balance = 0;
        }
    }
    p = p1;
}

template<typename KeyType>
void AVLTree<KeyType>::rotateLR(Node*& p, bool q)
{
    Node* p1 = p->left;
    Node* p2 = p1->right;
    p1->right = p2->left;
    p2->left = p1;
    p->left = p2->right;
    p2->right = p;

    if (p2->balance == -1) {
        p->balance = 1;
    }
    else {
        p->balance = 0;
    }

    if (p2->balance == 1) {
        p1->balance = -1;
    }
    else {
        p1->balance = 0;
    }

    p = p2;

    if (q) {
        p->balance = 0;
    }
    else {
        p2->balance = 0;
    }
}

template<typename KeyType>
void AVLTree<KeyType>::rotateRR(Node*& p, bool q)
{
    Node* p1 = p->right;
    p->right = p1->left;
    p1->left = p;

    if (q) {
        p->balance = 0;
        p1->balance = 0;
    }
    else {
        int b1 = p1->balance;
        if (b1 == 0) {
            p->balance = 1;
            p1->balance = -1;
        }
        else {
            p->balance = 0;
            p1->balance = 0;
        }
    }
    p = p1;
}

template<typename KeyType>
void AVLTree<KeyType>::rotateRL(Node*& p, bool q)
{
    Node* p1 = p->right;
    Node* p2 = p1->left;
    int b2 = p2->balance;
    p1->left = p2->right;
    p2->right = p1;
    p->right = p2->left;
    p2->left = p;

    if (b2 == 1) {
        p->balance = -1;
    }
    else {
        p->balance = 0;
    }

    if (b2 == -1) {
        p1->balance = 1;
    }
    else {
        p1->balance = 0;
    }

    p = p2;

    if (q) {
        p->balance = 0;
    }
    else {
        p2->balance = 0;
    }
}

template<typename KeyType>
void AVLTree<KeyType>::insertBool(const KeyType& x, Node*& p, bool& h) {
    if (p == nullptr) {
        p = new Node(x);
        h = true;
    }
    else if (x < p->key) {
        insertBool(x, p->left, h);
        if (h) {
            switch (p->balance) {
            case 1:
                p->balance = 0;
                h = false;
                break;
            case 0:
                p->balance = -1;
                break;
            case -1:
                if (p->left->balance == -1) {
                    rotateLL(p, true);
                }
                else {
                    rotateLR(p, true);
                }
                h = false;
                break;
            }
        }
    }
    else {
        insertBool(x, p->right, h);
        if (h) {
            switch (p->balance) {
            case -1:
                p->balance = 0;
                h = false;
                break;
            case 0:
                p->balance = 1;
                break;
            case 1:
                if (p->right->balance == 1) {
                    rotateRR(p, true);
                }
                else {
                    rotateRL(p, true);
                }
                h = false;
                break;
            }
        }
    }
}

template<typename KeyType>
void AVLTree<KeyType>::insert(const KeyType& x) {
    bool h = false;
    insertBool(x, root_, h);
}

template<typename KeyType>
void AVLTree<KeyType>::balanceLeft(Node*& p, bool& h) {
    int b = p->balance;
    switch (b) {
    case -1:
        p->balance = 0;
        break;
    case 0:
        p->balance = 1;
        h = false;
        break;
    case 1:
        int b1 = p->right->balance;
        if (b1 >= 0) {
            rotateRR(p, false);
        }
        else {
            rotateRL(p, false);
        }
        if (b1 == 0) {
            h = false;
        }
        break;
    }
}

template<typename KeyType>
void AVLTree<KeyType>::balanceRight(Node*& p, bool& h) {
    int b = p->balance;
    switch (b) {
    case 1:
        p->balance = 0;
        break;
    case 0:
        p->balance = -1;
        h = false;
        break;
    case -1:
        int b1 = p->left->balance;
        if (b1 <= 0) {
            rotateLL(p, false);
        }
        else {
            rotateLR(p, false);
        }
        if (b1 == 0) {
            h = false;
        }
        break;
    }
}

template<typename KeyType>
void AVLTree<KeyType>::deleteBool(const KeyType& x, Node*& p, bool& h) {
    if (p == nullptr) {
        h = false;
    }
    else if (x < p->key) {
        deleteBool(x, p->left, h);
        if (h) balanceLeft(p, h);
    }
    else if (p->key < x) {
        deleteBool(x, p->right, h);
        if (h) balanceRight(p, h);
    }
    else {
        Node* q = p;
        if (q->right == nullptr) {
            p = q->left;
            h = true;
        }
        else if (q->left == nullptr) {
            p = q->right;
            h = true;
        }
        else {
            // Упрощенная версия без лямбды
            Node* r = q->left;
            Node* parent = nullptr;
            while (r->right != nullptr) {
                parent = r;
                r = r->right;
            }

            q->key = r->key;

            if (parent != nullptr) {
                parent->right = r->left;
            }
            else {
                q->left = r->left;
            }

            delete r;
            h = true;
        }
        delete q;
    }
}

template<typename KeyType>
void AVLTree<KeyType>::remove(const KeyType& x) {
    bool h = false;
    deleteBool(x, root_, h);
}

template<typename KeyType>
bool AVLTree<KeyType>::is_contain(const KeyType& x) const {
    Node* current = root_;
    while (current != nullptr) {
        if (current->key == x) {
            return true;
        }
        else if (x < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

template<typename KeyType>
AVLTree<KeyType>::AVLTree(const KeyType* array, int n) : root_(nullptr) {
    for (int i = 0; i < n; i++) {
        insert(array[i]);
    }
}

template<typename KeyType>
void AVLTree<KeyType>::toSortedArray(KeyType* array, int size) const {
    int index = 0;
    inOrderTraversal(root_, array, index);
}

template<typename KeyType>
void AVLTree<KeyType>::inOrderTraversal(Node* node, KeyType* array, int& index) const {
    if (node != nullptr) {
        inOrderTraversal(node->left, array, index);
        array[index] = node->key;
        index++;
        inOrderTraversal(node->right, array, index);
    }
}

#endif  // AVLTREE_H_