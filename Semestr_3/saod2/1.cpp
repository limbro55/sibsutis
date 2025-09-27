#include <iostream>

//узал бинарного дерева
struct tnode {
  int data;           
  struct tnode *left;  
  struct tnode *right;
};

//новый узел
struct tnode * addnode(int key) 
{
	struct tnode* tree =new tnode; 
    tree->data = key;
    tree->left =  NULL;
    tree->right = NULL;
    
    return tree;
}

void TreeUpDown(struct tnode *p) { 
    if (p != NULL) {
        std::cout << p->data << " ";
        TreeUpDown(p->left);
        TreeUpDown(p->right);
    }
}

void TreeDownUp(struct tnode *p) { 
    if (p != NULL) {
        TreeDownUp(p->left);
        TreeDownUp(p->right);
        std::cout << p->data << " ";
    }
}

void TreeLeftRight(struct tnode *p) { 
    if (p != NULL) {
        TreeLeftRight(p->left);
        std::cout << p->data << " ";
        TreeLeftRight(p->right);
    }
}

int TreeSize(struct tnode *p){
    if (p == NULL) {return 0;}
    else {return 1 + TreeSize(p->left) + TreeSize(p->right);}
}

int TreeHeight(struct tnode *p){
    if (p == NULL) {return 0;}
    else {return 1 + std::max(TreeHeight(p->left), TreeHeight(p->right));}
}

int TreeSum(struct tnode *p){
    if (p == NULL) {return 0;}
    else {return p->data + TreeSum(p->left) + TreeSum(p->right);}
}

double TreeSDP(struct tnode *p, int L){
    if(p == NULL) {return 0;}
    else {return L + TreeSDP(p->left, L+1) + TreeSDP(p->right, L+1);}
}

double TreeSDPHight(struct tnode *p, int L){
    return TreeSDP(p, L)/TreeSize(p);
}



int main()
{	
	int L = 1;
	struct tnode* p = addnode(1);
	p -> right = addnode(2);
	p -> right -> right = addnode(3);
    p -> left = addnode(4);
    p -> left -> left = addnode(5);
    p -> left -> left -> right = addnode(6);
	
    std::cout << "sverhy vniz: ";
    TreeUpDown(p);
    std::cout << std::endl;
    
    std::cout << "snizy vverh: ";
    TreeDownUp(p);
    std::cout << std::endl;
    
    std::cout << "sleva v pravo: ";
    TreeLeftRight(p);
    std::cout << std::endl;
    
    std::cout << "Tree Size: " << TreeSize(p) << std::endl;
    std::cout << "Tree Hight: " << TreeHeight(p) << std::endl;
    std::cout << "Tree Summa: " << TreeSum(p) << std::endl;
    std::cout << "TreeSDPHight: " << TreeSDP(p,L) << std::endl;
    std::cout << "TreeSDPHight: " << TreeSDPHight(p,L) << std::endl;
    	
	
	return 0;
}