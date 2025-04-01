#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
using namespace std::chrono;


vector<int> Path;

void print(vector<int>& T)
{
    for(int i=0; i<T.size(); i++)
    {
        cout<<T[i]<<" ";
    }
    cout<<endl;
}

vector<int> generateRandomSequence(int n) {
    vector<int> seq(n);
    for (int &num : seq) {
        num = rand() % (10*n);
    }
    return seq;
}


struct Node 
{
    int key;
    Node* left;
    Node* right;
};

void levelOrderRec(Node* root, int level, vector<vector<int>>& res) {
    // Base case: If node is null, return
    if (root == nullptr) return;

    // Add a new level to the result if needed
    if (res.size() <= level)
        res.push_back({});
  
    // Add current node's data to its corresponding level
    res[level].push_back(root->key);

    // Recur for left and right children
    levelOrderRec(root->left, level + 1, res);
    levelOrderRec(root->right, level + 1, res);
}

// Function to perform level order traversal
vector<vector<int>> levelOrder(Node* root) {
    // Stores the result level by level
    vector<vector<int>> res; 
  
    levelOrderRec(root, 0, res);
    return res;
}

void printTree(Node* root, string indent, bool last)
{
   if (root != nullptr)
   {
    cout<<indent;
    if(last)
    {
        cout<<"R----";
        indent +="  ";
    }
    else
    {
        cout<<"L----";
        indent+="|  ";
    }
    cout<<root->key<<endl;
    printTree(root->left,indent,false);
    printTree(root->right,indent,true);
   }
}

Node* createNode(int key)
{
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* insertNode(Node* root, int key)
{
    if (root == nullptr) 
    { 
        return createNode(key);
    }

    if (key < root->key) 
    {
        root->left = insertNode(root->left, key);
    }
    else if (key > root->key) 
    {
        root->right = insertNode(root->right, key);
    }

    return root;
}

Node* minValueNode(Node* node)
{
    Node* current = node;
    Path.push_back(current->key);
    while (current && current->left != nullptr) {
        current = current->left;
        Path.push_back(current->key);
    }
    return current;
}

Node* maxValueNode(Node* node)
{
    Node* current = node;
    Path.push_back(current->key);
    while (current && current->right != nullptr) {
        current = current->right;
        Path.push_back(current->key);
    }
    return current;
}

Node* deleteNode(Node* root, int key)
{
    if (root == nullptr)
        return root;

    //szukanie
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }

    else {
        //0 or 1 child
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

        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void inorderTraversal(Node* root)
{
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

void preorderTraversal(Node* root)
{
    if (root != nullptr) {
        cout << root->key << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderDeletion(Node* root)
{
    if (root != nullptr) {
        postorderDeletion(root->left);
        postorderDeletion(root->right);
        cout << root->key << " ";
        delete root;
    }
}

Node* rightRotate(Node* y) 
{
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

Node* leftRotate(Node* x) 
{
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

Node* createVine(Node* root)
{
    Node* pseudoRoot = new Node();
    pseudoRoot->right = root;
    Node* temp = pseudoRoot;
    
    while (temp->right) {
        if (temp->right->left) {
            temp->right = rightRotate(temp->right);
        } else {
            temp = temp->right;
        }
    }
    return pseudoRoot->right;
}


Node* balanceVine(Node* root, int size)
{
    int w = log(size)/log(2);
    printTree(root,"",true);//
    cout<<"--------------"<<endl;
    Node* pseudoRoot = new Node();
    pseudoRoot->right = root;
    Node* temp = pseudoRoot;
    Node* last;
    for (int i = 0; i < size - pow(2,w); i++) {
        temp->right = leftRotate(temp->right);
        if(i>0)
        {
        last->right=temp->right;
        }
        if(i==0)
        {
            root=temp->right;
        }
        last=temp->right;
        temp = temp->right;
    }
    printTree(root,"",true);//
    cout<<"---------1"<<endl;
    int y =pow(2,w)-1;
    while (y > 1) {
        y /= 2;
        pseudoRoot->right = root;
        temp = pseudoRoot;
        for (int i = 0; i < y; i++) {
            temp->right = leftRotate(temp->right);
            if(i>0)
            {
            last->right=temp->right;
            }
            if(i==0)
            {
                root=temp->right;
            }
            last=temp->right;
            temp = temp->right;
        }
    }
    return root;
}

Node* balanceTree(Node* root) 
{
    root = createVine(root);
    int size = 0;
    Node* temp = root;
    while (temp) {
        size++;
        temp = temp->right;
    }
    return balanceVine(root, size);
}



int main()
{
    Node* root = nullptr;

    //random sequence generation
    srand(time(0));
    int n = 7;
    vector<int> randomSequence = generateRandomSequence(n);
    vector<int> Sequence;
    Sequence = {15,20,25,23,30,28,40};
    print(Sequence);

    //inserting
    for (int i = 0; i < n; i++) {
        root = insertNode(root, Sequence[i]);
    }
    
 
    cout<<"Inorder traversal of BST: ";
    inorderTraversal(root);
    cout<<endl;
    vector<vector<int>> res = levelOrder(root);
    printTree(root, "",true );
    cout<<"-----------------------------------"<<endl;
    root=balanceTree(root);
    printTree(root, "",true );



    cout<<"koniec"<<endl;

    return 0;
}