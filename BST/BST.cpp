#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

int SPACE=5;
vector<int> Path;
vector<int> inorderPath;

void print(vector<int>& T)
{
    for(int i=0; i<T.size(); i++)
    {
        cout<<T[i]<<" ";
    }
    cout<<endl;
}

vector<int> generateRandomSequence(int n) 
{
    vector<int> seq(n);
    for (int &num : seq) {
        num = rand() % (10*n);
    }
    return seq;
}

vector<int> generateIncreasingSequence(int n) {
    vector<int> seq = generateRandomSequence(n);
    sort(seq.begin(), seq.end());
    return seq;
}

vector<int> generateDecreasingSequence(int n) {
    vector<int> seq = generateIncreasingSequence(n);
    reverse(seq.begin(), seq.end());
    return seq;
}

struct Node 
{
    int key;
    Node* left;
    Node* right;
};

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
    else if (key >= root->key) 
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
        inorderPath.push_back(root->key);
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
    int w = log2(size+1);
    Node* pseudoRoot = new Node();
    pseudoRoot->right = root;
    Node* temp = pseudoRoot;
    Node* last;
    for (int i = 0; i < size+1 - pow(2,w); i++) {
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

void preorderfromkey(Node* root, int key)
{
    if (root == nullptr)
    {
        cout<<"Klucz nie istnieje"<<endl;
        return;
    }
    else if(root->key==key)
    {
    preorderTraversal(root);
    }
    else if (key < root->key) {
        preorderfromkey(root->left, key);
    }
    else if (key > root->key) {
        preorderfromkey(root->right, key);
    }
}

void printastree(Node* root, int space)
{
    if(root==nullptr)
    {
        return;
    }
    space+=SPACE;
    printastree(root->right,space);
    for(int i=SPACE;i<space;i++)
    {
        cout<<" ";
    }
    cout<<root->key<<endl;
    printastree(root->left,space);

}

Node* creatingBST(Node* root, vector<int>& Sequence)
{
    for (int i = 0; i < Sequence.size(); i++) 
    {
        root = insertNode(root, Sequence[i]);
    }
    return root;
}

//----------------------------------------------------
// AVL Tree Implementation

struct AVLNode 
{
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
};

AVLNode *createAVLNode(int key) 
{
    AVLNode* newNode = new AVLNode();
    newNode->key = key;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1; // New node is initially added at leaf
    return newNode;
}

int height(AVLNode* node) 
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int balanceFactor(AVLNode* node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode* rightRotateAVL(AVLNode* y) 
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* leftRotateAVL(AVLNode* x) 
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLNode* insertNodeAVL(AVLNode* node, int key)
{
    if (node == nullptr)
        return createAVLNode(key);

    if (key < node->key)
        node->left = insertNodeAVL(node->left, key);
    else if (key > node->key)
        node->right = insertNodeAVL(node->right, key);
    else
        return node;

    node->height = 1
                   + max(height(node->left),
                         height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rightRotateAVL(node);


    if (balance < -1 && key > node->right->key)
        return leftRotateAVL(node);


    if (balance > 1 && key > node->left->key) 
    {
        node->left = leftRotateAVL(node->left);
        return rightRotateAVL(node);
    }

    if (balance < -1 && key < node->right->key) 
    {
        node->right = rightRotateAVL(node->right);
        return leftRotateAVL(node);
    }

    return node;
}

AVLNode* minValueNodeAVL(AVLNode* node) 
{
    AVLNode* current = node;
    while (current->left != nullptr)
    {
        current = current->left;
        Path.push_back(current->key);
    }
    return current;
}

AVLNode* maxValueNodeAVL(AVLNode* node) 
{
    AVLNode* current = node;
    while (current->right != nullptr)
    { 
        current = current->right;
        Path.push_back(current->key);
    }
    return current;
}

AVLNode* deleteNodeAVL(AVLNode* root, int key) 
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNodeAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteNodeAVL(root->right, key);
    else 
    {
        if ((root->left == nullptr) || (root->right == nullptr)) 
        {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == nullptr) 
            {
                temp = root;
                root = nullptr;
            } 
            else 
            {
                *root = *temp; 
            }
            delete temp;
        } 
        else 
        {
            AVLNode* temp = minValueNodeAVL(root->right);
            root->key = temp->key;
            root->right = deleteNodeAVL(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

   
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotateAVL(root);

    if (balance > 1 && balanceFactor(root->left) < 0) 
    {
        root->left = leftRotateAVL(root->left);
        return rightRotateAVL(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotateAVL(root);

    if (balance < -1 && balanceFactor(root->right) > 0) 
    {
        root->right = rightRotateAVL(root->right);
        return leftRotateAVL(root);
    }

    return root;
}

AVLNode* creatingAVL(AVLNode* root, vector<int>& Sequence)
{
    if(Sequence.size()==1)
    {
        root=insertNodeAVL(root,Sequence[0]);
        return root;
    }
    int mid = Sequence.size()/2;
    root=insertNodeAVL(root,Sequence[mid]);
    vector<int> L(mid);
    vector<int> R(Sequence.size()-mid-1);
    for(int i=0; i<mid; i++)
    {
        L[i] = Sequence[i];
    }
    for(int i=mid+1; i<Sequence.size(); i++)
    {
        R[i-mid-1] = Sequence[i];
    }
    root=creatingAVL(root,L);
    if(R.size()>0)
        root=creatingAVL(root,R);
    return root;
}

void preorderAVL(AVLNode* root)
{
    if (root != nullptr) {
        cout << root->key << " ";
        preorderAVL(root->left);
        preorderAVL(root->right);
    }
}

void inorderAVL(AVLNode* root)
{
    if (root != nullptr) {
        inorderAVL(root->left);
        inorderPath.push_back(root->key);
        inorderAVL(root->right);
    }
}

void postorderAVL(AVLNode* root)
{
    if (root != nullptr) {
        postorderAVL(root->left);
        postorderAVL(root->right);
        cout << root->key << " ";
    }
}

void preorderfromkeyAVL(AVLNode* root, int key)
{
    if (root == nullptr)
    {
        cout<<"Klucz nie istnieje"<<endl;
        return;
    }
    else if(root->key==key)
    {
    preorderAVL(root);
    }
    else if (key < root->key) {
        preorderfromkeyAVL(root->left, key);
    }
    else if (key > root->key) {
        preorderfromkeyAVL(root->right, key);
    }
}

void postorderDeletionAVL(AVLNode* root)
{
    if (root != nullptr) {
        postorderDeletionAVL(root->left);
        postorderDeletionAVL(root->right);
        cout << root->key << " ";
        delete root;
    }
}

void printastreeAVL(AVLNode* root, int space)
{
    if(root==nullptr)
    {
        return;
    }
    space+=SPACE;
    printastreeAVL(root->right,space);
    for(int i=SPACE;i<space;i++)
    {
        cout<<" ";
    }
    cout<<root->key<<endl;
    printastreeAVL(root->left,space);

}

void testBST()
{
    ofstream foutT("testBSTT.csv");
    ofstream foutM("testBSTM.csv");
    ofstream foutI("testBSTI.csv");
    ofstream foutR("testBSTR.csv");
    vector<int> N={10,1000,10000,20000,50000};
    for(int i=0; i<N.size(); i++)
    {
        Node* root=nullptr;
        cout<<N[i]<<endl;
        vector<int> T=generateDecreasingSequence(N[i]);
        auto start = high_resolution_clock::now();
        root = creatingBST(root,T);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        foutT <<N[i]<<";"<<duration.count()<<endl;
        auto start1 = high_resolution_clock::now();
        minValueNode(root);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        foutM <<N[i]<<";"<<duration1.count()<<endl;
        auto start2 = high_resolution_clock::now();
        inorderTraversal(root);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        foutI <<N[i]<<";"<<duration2.count()<<endl;
        inorderPath.clear();
        auto start3 = high_resolution_clock::now();
        root=balanceTree(root);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        foutR <<N[i]<<";"<<duration3.count()<<endl;
    }
    foutT.close();
    foutM.close();
    foutI.close();
    foutR.close();
}

void testAVL()
{
    ofstream foutT("testAVLT.csv");
    ofstream foutM("testAVLM.csv");
    ofstream foutI("testAVLI.csv");
    vector<int> N={10,1000,10000,20000,50000};
    for(int i=0; i<N.size(); i++)
    {
        AVLNode* root=nullptr;
        cout<<N[i]<<endl;
        vector<int> T=generateDecreasingSequence(N[i]);
        auto start = high_resolution_clock::now();
        root = creatingAVL(root,T);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        foutT <<N[i]<<";"<<duration.count()<<endl;
        auto start1 = high_resolution_clock::now();
        minValueNodeAVL(root);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        foutM <<N[i]<<";"<<duration1.count()<<endl;
        auto start2 = high_resolution_clock::now();
        inorderAVL(root);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        foutI <<N[i]<<";"<<duration2.count()<<endl;
        inorderPath.clear();
    }
}

int main()
{
    AVLNode* rootAVL = nullptr;
    Node* root = nullptr;
    int o,d,k,r,t;
    //random sequence generation
    srand(time(0));
    int n = 10;
    vector<int> randomSequence = generateRandomSequence(n);
    vector<int> Sequence;
    Sequence = {9,10,3,5,4,6,7,2,1,8};
    //Sequence=randomSequence;
    cout<< "1-AVL"<<endl<<"2-BST(losowe)"<<endl<<"3-TestBST"<<endl<<"4-TestAVL"<<endl;
    cin>>t;
    if(t==1)
    {
        sort(Sequence.begin(), Sequence.end());
        rootAVL=creatingAVL(rootAVL,Sequence);

    }
    else if(t==2)
    {
        root=creatingBST(root,Sequence);
    }
    else if(t==3)
    {
        testBST();
        return 0;
    }
    else if(t==4)
    {
        testAVL();
        return 0;
    }
    else
        return 0;

    if(t==1)
    {
        while(true)
        {
            cout<<"Wybierz operacje: "<<endl<<"1-MinVal"<<endl<<"2-MaxVal"<<endl<<"3-usuniecie"<<endl<<"4-inorder"<<endl<<"5-preorder"<<endl<<"6-usuniecie dzrzewa postorder"<<endl<<"7-preorder poddrzewa"<<endl<<"8-dzrzewo"<<endl<<"9-wyjdz"<<endl;
            cin>>o;
            cout<<"-----------------------------------------"<<endl;
            switch(o)
            {
                case 1:
                    Path.clear();
                    cout<<"Minimalna wartosc: "<<minValueNodeAVL(rootAVL)->key<<endl<<"Sciezka: ";
                    print(Path);
                    break;
                case 2:
                    Path.clear();
                    cout<<"Maksymalna wartosc: "<<maxValueNodeAVL(rootAVL)->key<<endl<<"Sciezka: ";
                    print(Path);
                    break;
                case 3:
                    cout<<"Podaj ilosc elementow do usuniecia: "<<endl;
                    cin>>d;
                    for(int i=0;i<d;i++)
                    {
                        cout<<"Podaj wartosc klucza: "<<endl;
                        cin>>k;
                        rootAVL=deleteNodeAVL(rootAVL,k);
                    }
                    break;
                case 4:
                    inorderAVL(rootAVL);
                    cout<<endl;
                    break;
                case 5:
                    preorderAVL(rootAVL);
                    cout<<endl;
                    break;
                case 6:
                    postorderDeletionAVL(rootAVL);
                    break;
                case 7:
                    cout<<"Podaj wartosc korzenia"<<endl;
                    cin>>r;
                    preorderfromkeyAVL(rootAVL,r);
                    cout<<endl;
                    break;
                case 8:
                    printastreeAVL(rootAVL,0);
                    break;
                case 9:
                    return 0;
            }
            if(o==6)
                return 0;
            cout<<"------------------------------------------"<<endl;
        }
    }
    else if(t==2)
    {
       
        while(true)
        {
            cout<<"Wybierz operacje: "<<endl<<"1-MinVal"<<endl<<"2-MaxVal"<<endl<<"3-usuniecie"<<endl<<"4-inorder"<<endl<<"5-preorder"<<endl<<"6-usuniecie dzrzewa postorder"<<endl<<"7-preorder poddrzewa"<<endl<<"8-rownowaznienie"<<endl<<"9-dzrzewo"<<endl<<"10-wyjdz"<<endl;
            cin>>o;
            cout<<"-----------------------------------------"<<endl;
            switch(o)
            {
                case 1:
                    Path.clear();
                    cout<<"Minimalna wartosc: "<<minValueNode(root)->key<<endl<<"Sciezka: ";
                    print(Path);
                    break;
                case 2:
                    Path.clear();
                    cout<<"Maksymalna wartosc: "<<maxValueNode(root)->key<<endl<<"Sciezka: ";
                    print(Path);
                    break;
                case 3:
                    cout<<"Podaj ilosc elementow do usuniecia: "<<endl;
                    cin>>d;
                    for(int i=0;i<d;i++)
                    {
                        cout<<"Podaj wartosc klucza: "<<endl;
                        cin>>k;
                        root=deleteNode(root,k);
                    }
                    break;
                case 4:
                    inorderTraversal(root);
                    cout<<endl;
                    break;
                case 5:
                    preorderTraversal(root);
                    cout<<endl;
                    break;
                case 6:
                    postorderDeletion(root);
                    break;
                case 7:
                    cout<<"Podaj wartosc korzenia"<<endl;
                    cin>>r;
                    preorderfromkey(root,r);
                    cout<<endl;
                    break;
                case 8:
                    cout<<"Przed: "<<endl;
                    preorderTraversal(root);
                    root=balanceTree(root);
                    cout<<endl<<"Po: "<<endl;
                    preorderTraversal(root);
                    break;
                case 9:
                    printastree(root,0);
                    break;
                case 10:
                    return 0;
            }
            if(o==6)
                return 0;
            cout<<"------------------------------------------"<<endl;
        }
    }
    else
    return 0;
}