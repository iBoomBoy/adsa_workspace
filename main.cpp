#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, height;
    Node *left, *right;
    Node(int val) : key(val), height(1), left(NULL), right(NULL) {}
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) return rightRotate(root);
    if (balance < -1 && key > root->right->key) return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* getMaxValueNode(Node* root) {
    Node* current = root;
    while (current->right) current = current->right;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = getMaxValueNode(root->left);
            root->key = temp->key;
            root->left = deleteNode(root->left, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preorder(Node* root, vector<int>& res) {
    if (root) {
        res.push_back(root->key);
        preorder(root->left, res);
        preorder(root->right, res);
    }
}

void inorder(Node* root, vector<int>& res) {
    if (root) {
        inorder(root->left, res);
        res.push_back(root->key);
        inorder(root->right, res);
    }
}

void postorder(Node* root, vector<int>& res) {
    if (root) {
        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->key);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    getline(cin, line);
    stringstream ss(line);
    string move;
    vector<string> moves;
    while (ss >> move) moves.push_back(move);

    Node* root = NULL;
    for (int i = 0; i + 1 < (int)moves.size(); i++) {
        if (moves[i][0] == 'A') {
            int num = stoi(moves[i].substr(1));
            root = insert(root, num);
        } else if (moves[i][0] == 'D') {
            int num = stoi(moves[i].substr(1));
            root = deleteNode(root, num);
        }
    }

    vector<int> res;
    string command = moves.back();
    if (root) {
        if (command == "PRE") preorder(root, res);
        else if (command == "IN") inorder(root, res);
        else if (command == "POST") postorder(root, res);

        for (int i = 0; i < (int)res.size(); i++) {
            if (i) cout << " ";
            cout << res[i];
        }
        cout << "\n";
    } else {
        cout << "EMPTY\n";
    }
    return 0;
}
