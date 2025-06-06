#pragma once
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

//二分搜索树

template<typename Key, typename Value>
class BST {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }

        Node(Node* node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

private:
    Node* root; // 根节点
    int count;  // 树中的节点个数

public:
    BST() {
        root = NULL;
        count = 0;
    }
    ~BST() {
        destroy(root);
    }

    int size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contain(Key key) const {
        return contain(root, key);
    }

    Value* search(Key key) {
        return search(root, key);
    }

    // 二分搜索树的前序遍历
    void preOrder() {
        preOrder(root);
    }

    // 二分搜索树的中序遍历
    void inOrder() {
        inOrder(root);
    }

    // 二分搜索树的后序遍历
    void postOrder() {
        postOrder(root);
    }

    // 二分搜索树的层序遍历
    void levelOrder() {
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            cout << node->key << endl;

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
    }

    // 寻找二分搜索树的最小的键值
    Key minimum() {
        assert(count != 0);
        Node* minNode = minimum(root);
        return minNode->key;
    }

    // 寻找二分搜索树的最大的键值
    Key maximum() {
        assert(count != 0);
        Node* maxNode = maximum(root);
        return maxNode->key;
    }

    // 从二分搜索树中删除最小值所在节点
    void removeMin() {
        root = removeMin(root);
    }

    // 从二分搜索树中删除最大值所在节点
    void removeMax() {
        root = removeMax(root);
    }

    // 从二分搜索树中删除键值为key的节点
    void remove(Key key) {
        root = remove(root, key);
    }

    Node* successor();
    Node* predecessor();
    Node* floor();
    Node* ceil();
    int rank(Value value);
    Value select(int nth);

private:
    //向以node为根的二叉搜索树中，插入节点(key,value)
    //返回插入新节点后的二叉搜索树的根
    Node* insert(Node* node, Key key, Value value) {
        if (node == NULL) {
            count++;
            return new Node(key, value);
        }

        if (key == node->key)
            node->value = value;
        else if (key < node->key)
            node->left = insert(node->left, key, value);
        else //key > node->key
            node->right = insert(node->right, key, value);

        return node;
    }

    // 查看以node为根的二分搜索树中是否包含键值为key的节点, 使用递归算法
    bool contain(Node* node, Key key) const {
        if (node == NULL)
            return false;

        if (key == node->key)
            return true;
        else if (key < node->key)
            return contain(node->left, key);
        else // key > node->key
            return contain(node->right, key);
    }

    // 在以node为根的二分搜索树中查找key所对应的value, 递归算法
    // 若value不存在, 则返回NULL
    Value* search(Node* node, Key key) {
        if (node == NULL)
            return NULL;

        if (key == node->key)
            return &(node->value);
        else if (key < node->key)
            return search(node->left, key);
        else // key > node->key
            return search(node->right, key);
    }

    // 对以node为根的二分搜索树进行前序遍历, 递归算法
    void preOrder(Node* node) {
        if (node != NULL) {
            cout << node->key << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // 对以node为根的二分搜索树进行中序遍历, 递归算法
    void inOrder(Node* node) {
        if (node != NULL) {
            inOrder(node->left);
            cout << node->key << endl;
            inOrder(node->right);
        }
    }

    // 对以node为根的二分搜索树进行后序遍历, 递归算法
    void postOrder(Node* node) {
        if (node != NULL) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << endl;
        }
    }

    // 释放以node为根的二分搜索树的所有节点
    // 采用后续遍历的递归算法
    void destroy(Node* node) {
        if (node != NULL) {
            destroy(node->left);
            destroy(node->right);

            delete node;
            count--;
        }
    }

    // 返回以node为根的二分搜索树的最小键值所在的节点, 递归算法
    Node* minimum(Node* node) {
        if (node->left == NULL)
            return node;

        return minimum(node->left);
    }

    // 返回以node为根的二分搜索树的最大键值所在的节点, 递归算法
    Node* maximum(Node* node) {
        if (node->right == NULL)
            return node;

        return maximum(node->right);
    }

    // 删除掉以node为根的二分搜索树中的最小节点, 递归算法
    // 返回删除节点后新的二分搜索树的根
    Node* removeMin(Node* node) {
        if (node == NULL)
            return NULL;

        if (node->left == NULL) {
            Node* rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }

        node->left = removeMin(node->left);
        return node;
    }

    // 删除掉以node为根的二分搜索树中的最大节点, 递归算法
    // 返回删除节点后新的二分搜索树的根
    Node* removeMax(Node* node) {
        if (node == NULL)
            return NULL;

        if (node->right == NULL) {
            Node* leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }

        node->right = removeMax(node->right);
        return node;
    }

    // 删除掉以node为根的二分搜索树中键值为key的节点, 递归算法
    // 返回删除节点后新的二分搜索树的根
    Node* remove(Node* node, Key key) {
        if (node == NULL)
            return NULL;

        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        }
        else {   // key == node->key
            if (node->left == NULL) {
                Node* rightNode = node->right;
                delete node;
                count--;
                return rightNode;
            }

            if (node->right == NULL) {
                Node* leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }

            // node->left != NULL && node->right != NULL
            Node* successor = new Node(minimum(node->right));
            count++;

            successor->right = removeMin(node->right);
            successor->left = node->left;

            delete node;
            count--;

            return successor;
        }
    }
};
