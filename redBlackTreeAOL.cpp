#include<stdio.h>
#include<stdlib.h>

struct Node 
{
    int value;
    int color;
    Node *parent, *left, *right;
};

struct RBT 
{
    Node *root, *nil;
};

Node* createNewNode(int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->parent = newNode->left = newNode->right = NULL;
    newNode->color = 1;
    
    return newNode;
}

RBT* createRBT() 
{
    RBT* tree = (RBT*)malloc(sizeof(RBT));
    tree->nil = createNewNode(0);
    tree->nil->color = 0;
    tree->root = tree->nil;
    
    return tree;
}

void leftRotate(RBT* tree, Node* x) 
{
    Node* y = x->right;
    x->right = y->left;
    if(y->left != tree->nil) 
	{
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == tree->nil) 
	{
        tree->root = y;
    } 
	else if(x == x->parent->left) 
	{
        x->parent->left = y;
    } 
	else 
	{
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

void rightRotate(RBT* tree, Node* x) 
{
    Node* y = x->left;
    x->left = y->right;
    
    if(y->right != tree->nil) 
	{
        y->right->parent = x;
    }
    y->parent = x->parent;
    
    if(x->parent == tree->nil) 
	{
        tree->root = y;
    } 
	else if(x == x->parent->right) 
	{
        x->parent->right = y;
    } 
	else 
	{
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}

void fixInsert(RBT* tree, Node* z) 
{
    while(z->parent->color == 1) 
	{
        if(z->parent == z->parent->parent->left) 
		{
            Node* y = z->parent->parent->right;
            if(y->color == 1) 
			{
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } 
			else 
			{
                if(z == z->parent->right) 
				{
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rightRotate(tree, z->parent->parent);
            }
        } 
		else 
		{
            Node* y = z->parent->parent->left;
            if(y->color == 1) 
			{
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } 
			else 
			{
                if(z == z->parent->left) 
				{
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    
    tree->root->color = 0;
}

void insertion(RBT* tree, int value) 
{
    Node* z = createNewNode(value);
    Node* y = tree->nil;
    Node* x = tree->root;
    
    while(x != tree->nil) 
	{
        y = x;
        if(z->value < x->value) 
		{
            x = x->left;
        } 
		else 
		{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == tree->nil) 
	{
        tree->root = z;
    } 
	else if(z->value < y->value) 
	{
        y->left = z;
    } 
	else 
	{
        y->right = z;
    }
    
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = 1;
    fixInsert(tree, z);
}

void inOrder(RBT* tree, Node* node) 
{
    if(node != tree->nil) 
	{
        inOrder(tree, node->left);
        printf("%d ", node->value);
        inOrder(tree, node->right);
    }
}

int main() 
{
    RBT* tree = createRBT();

    insertion(tree, 41);
    insertion(tree, 22);
    insertion(tree, 5);
    insertion(tree, 51);
    insertion(tree, 48);
    insertion(tree, 29);
    insertion(tree, 18);
    insertion(tree, 21);
    insertion(tree, 45);
    insertion(tree, 3);

    printf("Inorder Traversal of Created Tree\n");
    inOrder(tree, tree->root);

    return(0);
}
