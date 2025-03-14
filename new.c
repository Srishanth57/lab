#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;

} *node;

node createNode(int data)
{
    node temp = (node)malloc(sizeof(struct NODE));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
node insertNode(node root, int value)
{
    if (root == NULL)
    {
        root = createNode(value);
        return root;
    }
    if (value < root->data)
    {
        root->left = insertNode(root->left, value);
    }
    else
    {
        root->right = insertNode(root->right, value);
    }
    return root;
}
node makeTree(node root)
{
    int n;
    printf("Enter the no of nodes to create the tree: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int value;
        scanf("%d", &value);
        root = insertNode(root, value);
    }
    return root;
}
void inorder(node root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d\t", root->data);
        inorder(root->right);
    }
}
void postorder(node root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d\t", root->data);
    }
}
void preorder(node root)
{
    if (root != NULL)
    {
        printf("%d\t", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void traversal(node root)
{
    printf("Inorder traversal : ");
    inorder(root);
    printf("\n");
    printf("Preorder traversal : ");
    preorder(root);
    printf("\n");
    printf("Postorder traversal : ");
    postorder(root);
}

void search(node root, int n)
{
    if (root == NULL)
    {
        printf("Element %d not found.\n", n);
        return;
    }

    if (root->data == n)
    {
        printf("Element %d found.\n", n);
        return;
    }
    else if (n < root->data)
    {
        search(root->left, n);
    }
    else
    {
        search(root->right, n);
    }
}
node deleteNode(node root, int n)
{
    if (root == NULL)
        return root;
    if (n < root->data)
    {
        root->left = deleteNode(root->left, n);
    }
    else if (n > root->data)
    {
        root->right = deleteNode(root->right, n);
    }
    else
    {
        if (root->left == NULL)
        {
            node temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node temp = root->left;
            free(root);
            return temp;
        }
        node temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
        }

    return root;
}

int main()
{
    char c[100];
    node root = NULL;

    root = makeTree(root);

    traversal(root);
    free(root);
    return 0;
}


