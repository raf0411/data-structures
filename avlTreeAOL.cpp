#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pressEnter()
{
	char ch;
	scanf("%c", &ch);
	getchar();
}

struct Data
{
	int value;
	int height;
	
	Data *left, *right;	
};

Data *newNode(int value)
{
	Data *temp = (Data*)malloc(sizeof(Data));
	temp->value = value;
	temp->height = 1;
	temp->left = temp->right = NULL;
	
	return temp;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int height(Data *root)
{
	if(root == NULL)
	{
		return(0);
	}
	return root->height;
}

int bf(Data *root)
{
	if(root == NULL)
	{
		return(0);
	}
	
	return height(root->left) - height(root->right);
}

Data *leftRotate(Data *root)
{
	Data *rightChild = root->right;
	Data *leftRightChild = rightChild->left;
	rightChild->left = root;
	root->right = leftRightChild;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	
	rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
	
	return rightChild;
}

Data *rightRotate(Data *root)
{
	Data *leftChild = root->left;
	Data *rightLeftChild = leftChild->left;
	leftChild->right = root;
	root->left = rightLeftChild;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	
	leftChild->height = max(height(root->left), height(root->right)) + 1;

	return leftChild;
}

Data *rebalance(Data *root)
{
	int factor = bf(root);
	
	if(factor > 1)
	{
		if(bf(root->left) >= 0)
		{
			return rightRotate(root);
		}
		else
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if(factor < -1)
	{
		if(bf(root->right) <= 0)
		{
			return leftRotate(root);
		}
		else
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	
	return root;
}

Data *insertion(Data *root, int value)
{
	if(root == NULL)
	{
		return newNode(value);
	}
	else if(value > root->value)
	{
		root->right = insertion(root->right, value);
	}
	else if(value < root->value)
	{
		root->left = insertion(root->left, value);
	}
	
	root->height = max(height(root->left), height(root->right)) + 1;
	return rebalance(root);
}

Data *pop(Data *root, int value)
{	
	if(root == NULL)
	{
		return NULL;
	}
	else if(value > root->value)
	{
		root->right = pop(root->right, value);
	}
	else if(value < root->value)
	{
		root->left = pop(root->left, value);
	}
	else
	{
		if(root->left == NULL)
		{
			Data *temp = root->right;
			free(root);
			root = NULL;
			printf("Data Found\n");
			printf("Value %d was deleted\n", value);
			return temp;
		}
		else if(root->right == NULL)
		{
			Data *temp = root->left;
			free(root);
			root = NULL;
			printf("Data Found\n");
			printf("Value %d was deleted\n", value);
			return temp;			
		}
		else
		{
			Data *temp = root->left;
			
			while(temp->right)
			{
				temp = temp->right;
			}
			
			root->value = temp->value;
			root->left = pop(root->left, value);
		}
	}
	
	
	root->height = max(height(root->left), height(root->right)) + 1;
	printf("Data not found\n");
	return rebalance(root);
}

void menu()
{
	puts("1. Insertion");
	puts("2. Deletion");
	puts("3. Transversal");
	puts("4. Exit");
	printf("Choose: ");
}

void inOrder(Data *root)
{
	if(root)
	{
		inOrder(root->left);
		printf("%d ", root->value);
		inOrder(root->right);
	} 
}

void preOrder(Data *root)
{
	if(root)
	{
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);
	} 
}

void postOrder(Data *root)
{
	if(root)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->value);
	} 
}

int main()
{
	Data *root = NULL;
	
	int option;
	
		do
		{
			menu();
			scanf("%d", &option);
			
			switch(option)
			{
				case 1:
					printf("Insert: ");
					int value;
					scanf("%d", &value);
					root = insertion(root, value);
					break;
				case 2:
					printf("Delete: ");
					int value1;
					scanf("%d", &value1);
					root = pop(root, value1);
					break;				
				case 3:
					printf("Preorder: ");
					preOrder(root);
					printf("\n");
					
					printf("Inorder: ");
					inOrder(root);
					printf("\n");
					
					printf("Postorder: ");
					postOrder(root);
					printf("\n");
					
					pressEnter();
					
					break;
				case 4:
					printf("Thank you\n");
					break;
			}
					
		}while(option != 4);
	
	return(0);
}
