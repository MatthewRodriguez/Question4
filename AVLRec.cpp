#include <iostream>
using namespace std;

struct Node{
    Node *right, *left;
    int info;
    int height;
    
    Node(int i, Node *l, Node *r, int h = 1)
        :info(i), left(l), right(r), height(h){}
};

Node* deleteRec(Node *n, int item);
Node* insertRec(Node* &n, int item);
Node* rotateRight(Node* n);
Node* rotateLeft(Node* n);
Node* doubleLeft(Node* n);
Node* doubleRight(Node* n);
Node* findMaxRec(Node *n);
Node* findMinRec(Node *n);
Node* findPrevRec(Node *n, int item);
Node* findNextRec(Node *n, int item);
int getBalance(Node* n);
int height(Node *n);
int max(int lh, int rh);
void preOrder(Node *n);

int main(){
    Node *root = nullptr;
    
    root = insertRec(root, 10);
    root = insertRec(root, 8);
    root = insertRec(root, 5);
    //root = deleteRec(root, 5);
    preOrder(root);
    cout << endl;
    return 0;
}

int height(Node *n){
    return n == nullptr ? 0 : n->height;
}

int max(int lh, int rh)
{
    return lh > rh ? lh : rh;
}

int getBalance(Node* n){
    return n == nullptr ? 0 : (height(n->left) - height(n->right));
}

Node* deleteRec(Node *n, int item){
    Node *nothing = nullptr;
    if (n == nullptr)
        return nothing;
    if (item < n->info)
        n->left = deleteRec(n->left, item);
    else if (item > n->info)
        n->right = deleteRec(n->right, item);
    else if (n->left != nullptr && n->right != nullptr){
        n->info = findMinRec(n->right)->info;
        deleteRec(n->right, n->info);
    }
    else{
        Node *temp = n;
        n = (n->left != nullptr) ? n->left : n->right;
        delete temp;
    }
    int bf = getBalance(n);
    if (bf > 1 && item < n->left->info)
          return rotateRight(n);
    
    // Right Right Case
    if (bf < -1 && item > n->right->info)
        return rotateLeft(n);
    
    // Left Right Case
    if (bf > 1 && item > n->left->info)
    {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    
    // Right Left Case
    if (bf < -1 && item < n->right->info)
    {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

Node* insertRec(Node* &n, int item){
    if(n == nullptr)
        n = new Node(item, nullptr, nullptr);
    else if (item < n->info)
        insertRec(n->left, item);
    else if (item > n->info)
        insertRec(n->right, item);
    
    n->height = max(height(n->left), height(n->right)) + 1;
    int bf = getBalance(n);
    if (bf > 1 && item < n->left->info)
          return rotateRight(n);
    
    // Right Right Case
    if (bf < -1 && item > n->right->info)
        return rotateLeft(n);
    
    // Left Right Case
    if (bf > 1 && item > n->left->info)
    {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    
    // Right Left Case
    if (bf < -1 && item < n->right->info)
    {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

Node* rotateRight(Node *b){
    Node *a = b->left;
    Node *c = a->right;
    a->right = b;
    b->left = c;
    b->height = max(height(b->left), height(b->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    
    return a;
}

Node* rotateLeft(Node* a){
    Node *b = a->left;
    Node *c = b->left;
    b->left = a;
    a->right = c;
    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;
    return b;
}

Node* doubleLeft(Node* n){
    rotateRight(n->right);
    return rotateLeft(n);
}

Node* doubleRight(Node* n){
    rotateLeft(n->right);
    return rotateRight(n);
}

void preOrder(Node *n){
    if (n == nullptr)
        return;
    cout << n->info << " ";
    preOrder(n->left);
    preOrder(n->right);
}

Node* findMaxRec(Node *n){
    if (n != nullptr){
        if (n->right != nullptr)
            n = findMaxRec(n->right);
    }
    return n;
}

Node* findMinRec(Node *n){
    if (n != nullptr){
        if (n->left != nullptr)
            n = findMinRec(n->left);
    }
    return n;
}

Node* findPrevRec(Node *n, int item){
    Node *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    //while(current->right != nullptr){
    if (current->right != nullptr){
        if (current->info == item){
            if (current->left != nullptr){
                if(current->left->right != nullptr)
                    return current->left->right;
                else
                    return current->left;
            }
            else if (n->left == nullptr){
                if(parent->info > item)
                    return parent;
            }
        }
        else if (current->left->info == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)
                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->info > item)
                    return current;
            }
        }
        parent = current;
        current = findPrevRec(current->right, item);
    }
    
    if (t->left != nullptr){
        if (t->info == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->info > item)
                    return parent;
            }
        }
        parent = t;
        t = findPrevRec(t->left, item);
    }
    return nothing;
}

Node* findNextRec(Node *n, int item){
    Node *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    if (current->right != nullptr){
        if (current->info == item){
            if (current->right != nullptr){
                if(current->right->left != nullptr)
                    return current->right->left;
                else
                    return current->right;
            }
            else if (n->right == nullptr){
                if(parent->info > item)
                    return parent;
            }
        }
        else if (current->left->info == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)
                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->info > item)
                    return current;
            }
        }
        parent = current;
        current = findNextRec(current->right, item);
    }
    
    if (t->left != nullptr){
        if (t->info == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->info > item)
                    return parent;
            }
        }
        parent = t;
        t = findNextRec(t->left, item);
    }
    return nothing;
}

/*
void getSortedArray(int n){
    BST tree;
    Nodes *r = NULL;
    int arr[n];
    int j = n-1;
    if (n % 2 == 0){
        for (int i = 0; i < n; i++){
            if (i != (n/2)){
                arr[i] = i;
                arr[j] = i;
            }
            else
                break;
            j--;
        }
    }
    else
        cout << "it's not even";
    for (int j = 0; j < n; j++){
        tree.insertIter(j);
        r = rec(r, j);
    }
    cout << "BSt output: " << endl;
    tree.preOrder();
    cout << endl;
    cout << "AVL output: " << endl;
    preOrder(r);
    cout << endl;
    long s = tree.vec.size();
    cout << "Total traversals AVL: " << list[0] << endl;
    cout << "Total traversals BST: " << tree.vec[s-1] << endl;
    
}


void getRandomArray(int n){
    BST tree;
    Nodes *root = NULL;
    int arr[n], j, t;
    for (int i = 0; i < n; i++)
        arr[i] = i+1;

    for (int i = 0; i < n; i++) {
        j = rand()%n;

        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
       // tree.insertIter(t);
       // root = insertion(root, t);
    }
    
    
    for (int j = 0; j < n; j++){
        tree.insertIter(j);
        root = insertion(root, j, 0);
    }
    
    cout << endl;
    cout << "BSt output: " << endl;
    tree.preOrder();
    cout << endl;
    cout << "AVL output: " << endl;
    pOrder(root);
    cout << endl;
    long s = tree.vec.size();
    cout << "Total traversals AVL: " << list[list.size()-3] << endl;
    cout << "Total traversals BST: " << tree.vec[s-1] << endl;
}
*/
