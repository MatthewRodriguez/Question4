#include <iostream>
using namespace std;

class Nodes{
    public:
    int key;
    Nodes *left;
    Nodes *right;
    int height;
};

int max(int a, int b);
int height(Nodes *n);
int max(int a, int b);
int getBalance(Nodes *n);
Nodes* newNode(int key);
Nodes* rightRotate(Nodes *y);
Nodes* leftRotate(Nodes *x);
Nodes* deleteIter(Nodes *n, int item);
Nodes* deleteFromTree(Nodes* &n);
Nodes* findMaxIter(Nodes *n);
Nodes* findMinIter(Nodes *n);
Nodes* findPrevIter(Nodes *n, int item);
Nodes* findNextIter(Nodes *n, int item);
Nodes* insertRec(Nodes *node, int item, int count);
Nodes* insertIter(Nodes *n, int item);
void preOrder(Nodes *root);


int main(){
    Nodes *root = nullptr;
    root = insertRec(root, 10, 0);
    root = insertRec(root, 8, 0);
    root = insertRec(root, 5, 0);

    preOrder(root);
    return 0;
}

int height(Nodes *n){
    return n == nullptr ? 0 : n->height;
}
  
int max(int a, int b){
    return (a > b)? a : b;
}
  
Nodes* newNode(int key){
    Nodes* nod = new Nodes();
    nod->key = key;
    nod->left = NULL;
    nod->right = NULL;
    nod->height = 1;
    return(nod);
}
  
Nodes *rightRotate(Nodes *b){
    Nodes *a = b->left;
    Nodes *c = a->right;
    a->right = b;
    b->left = c;
    b->height = max(height(b->left), height(b->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}
  
Nodes *leftRotate(Nodes *a){
    Nodes *b = a->right;
    Nodes *c = b->left;
    b->left = a;
    a->right = c;
    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;
    return b;
}
  
int getBalance(Nodes *n){
    return n == nullptr ? 0 : height(n->left) - height(n->right);
}

Nodes* balance(Nodes* n, int key){
    int bf = getBalance(n);
    if (bf > 1 && key < n->left->key)
      return rightRotate(n);
    if (bf < -1 && key > n->right->key)
      return leftRotate(n);
    if (bf > 1 && key > n->left->key)
    {
      n->left = leftRotate(n->left);
      return rightRotate(n);
    }
    if (bf < -1 && key < n->right->key)
    {
      n->right = rightRotate(n->right);
      return leftRotate(n);
    }
    return n;
}

Nodes* insertRec(Nodes* node, int key, int c){
    int count = c;
    if (node == NULL)
        return(newNode(key));
  
    if (key < node->key){
        count++;
        node->left = insertRec(node->left, key, count);
    }
    else if (key > node->key){
        count++;
        node->right = insertRec(node->right, key, count);
    }
    else
        return node;
  
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
   
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Nodes* insertIter(Nodes* n, int item){
    Nodes *c, *p = nullptr, *node;
    int count = 0;
    node = newNode(item);
    
    if (n == nullptr)
       return n = node;
    else{
        n->height = 1 + max(height(n->left), height(n->right));
       c = n;
       while (c != nullptr){
           p = c;
           if (c->key == item)
               return n;
           else if (c->key > item){
               count++;
               c = c->left;
           }
           else{
               count++;
               c = c->right;
           }
       }
        node->height = 1 + max(height(node->left), height(node->right));
       if (p->key > item)
           p->left = node;
       else
           p->right = node;
    }
    balance(n, item);
    return n;
}

Nodes* deleteFromTree(Nodes* &n){
    Nodes *current, *prev, *temp;
    if (n == nullptr)
        return n;
    else if (n->left == nullptr && n->right == nullptr){
        temp = n;
        n = nullptr;
        delete temp;
    }
    else if (n->left == nullptr){
        temp = n;
        n = temp->left;
        delete temp;
    }
    else if (n->right == nullptr){
        temp = n;
        n = temp->right;
        delete temp;
    }
    else{
        current = n->left;
        prev = nullptr;
    
        while (current->right != nullptr){
            prev = current;
            current = current->right;
        }
        
        n->key = current->key;
        if (prev == nullptr)
            n->left = current->left;
        else
            prev->right = current->left;
            
        delete current;
    }
    balance(n, prev->key);
    return n;
}

Nodes* deleteIter(Nodes *n, int item){
    Nodes *current, *prev;
    bool found = false;
    
    if (n == nullptr)
        return n;
    else{
        current = n;
        prev = n;
        
        while(current != nullptr && !found){
            if (current->key == item)
                found = true;
            else{
                prev = current;
                if (current->key > item)
                    current = current->left;
                else
                    current = current->right;
            }
        }
        if (current == nullptr)
            return n;
        else if (found){
            if (current == n)
                deleteFromTree(n);
            else if (prev->key > item)
                deleteFromTree(prev->left);
            else
                deleteFromTree(prev->right);
        }
    }
    return n;
}

Nodes* findMaxIter(Nodes *n){
    if (n != nullptr)
        while(n->right != nullptr)
            n = n->right;
    return n;
}

Nodes* findMinIter(Nodes *n){
    if (n != nullptr)
        while (n->left != nullptr)
            n = n->left;
    return n;
}

Nodes* findPrevIter(Nodes *n, int item){
    Nodes *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    while(current->right != nullptr){
        if (current->key == item){
            if (current->left != nullptr){
                if(current->left->right != nullptr)
                    return current->left->right;
                else
                    return current->left;
            }
            else if (n->left == nullptr){
                if(parent->key > item)
                    return parent;
            }
        }
        else if (current->left->key == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)
                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->key > item)
                    return current;
            }
        }
        parent = current;
        current = current->right;
    }
    
    while(t->left != nullptr){
        if (t->key == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->key > item)
                    return parent;
            }
        }
        parent = t;
        t = t->left;
    }
    return nothing;
}

Nodes* findNextIter(Nodes *n, int item){
    Nodes *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    while(current->right != nullptr){
        if (current->key == item){
            if (current->right != nullptr){
                if(current->right->left != nullptr)
                    return current->right->left;
                else
                    return current->right;
            }
            else if (n->right == nullptr){
                if(parent->key > item)
                    return parent;
            }
        }
        else if (current->left->key == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)
                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->key > item)
                    return current;
            }
        }
        parent = current;
        current = current->right;
    }
    
    while(t->left != nullptr){
        if (t->key == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->key > item)
                    return parent;
            }
        }
        parent = t;
        t = t->left;
    }
    return nothing;
}

void preOrder(Nodes *root){
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
