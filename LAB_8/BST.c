#include <stdio.h>
#include <stdlib.h>

struct BST{
    int data;
    struct BST* left;
    struct BST* right;
    struct BST* parent;
};

struct BST* CreateNewNode(int element)
{
    struct BST* temp = (struct BST*)malloc(sizeof(struct BST));
    temp-> data = element;
    temp->left=temp->right=temp->parent=NULL;
    return temp;
}
struct BST* insert(struct BST* root, struct BST* NewNode)
{
    if (root == NULL)
    {
        root = NewNode;
    }
    else if (NewNode-> data < root-> data)
    {
        root -> left = insert(root->left, NewNode);
        root->left->parent = root;
    }
    else
    {
        root->right = insert(root->right, NewNode);
        root->right->parent = root;
    }
    return root;
}

struct BST* findMax(struct BST* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

struct BST* findMin(struct BST* root)
{
    if (root == NULL)
    {
        return NULL;
    }
   while(root->left != NULL){
        root = root->left;
    }
    return root;
}

struct BST* delete(struct BST* root, int element)
{
    if (root == NULL)
    {
        return root;
    }
    else if(element < root-> data)
    {
        root -> left = delete(root-> left, element);
        if (root-> left) root->left->parent = root;
    }
    else if(element > root-> data)
    {
        root -> right = delete(root-> right, element);
        if (root-> right) root->right->parent = root;
    }
    else{
        if (root-> left != NULL)
        {
            struct BST* temp = root-> left;
            if(temp) temp-> parent = root-> parent;
            free(root);
            return temp; 
        }
        else if (root->right != NULL)
        {
            struct BST* temp = root-> right;
            if(temp) temp-> parent = root-> parent;
            free(root);
            return temp; 
        }
        else
        {
            struct BST* temp = findMin(root->right);
            root->data= temp->data;
            root->right = delete(root->right, temp->data);
            if(root->right) root->right->parent = root;
        }
    }
    return root;
}

void preorder(struct BST* root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct BST* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(struct BST* root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

struct BST* search(struct BST* root, int key)
{
    if( root == NULL || key == root-> data)
        return root;

    else if (key < root-> data)
    {
        return search(root->left, key);
    }
    else{
        return search(root->right, key);
    }

}

int findHeight(struct BST *root)
{
    if (root == NULL)
        return 0;

    int left = findHeight(root->left);
    int right = findHeight(root->right);

    return (left > right ? left : right) + 1;
}

int main()
{
    struct BST *root, *temp;
    root = NULL;
    int choice, data;
    
    do
    {
        printf("\n\n0. CREATE\n1. INSERT\n2. DELETE\n3. SEARCH\n4. MAX\n5. MIN\n6. TRAVERSE\n7. Height\n8. EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 0:
                int A[]= {70, 40, 75, 77, 65, 30, 28, 72};
                for(int i = 0; i< 8; i++)
                {
                    temp = CreateNewNode(A[i]);
                    root = insert(root, temp);
                }
            break;

            case 1:
                printf("\n\nEnter the data: ");
                scanf("%d", &data);
                // temp = CreateNewNode(data);
                temp = (struct BST*)malloc(sizeof(struct BST));
                temp-> data = data;
                temp->left=temp->right=temp->parent=NULL;
                insert(root, temp);
            break;

            case 2:
                printf("\nEnter the data to delete: ");
                scanf("%d", &data);
                root = delete(root, data);
            break;

            case 3:
                printf("\nEnter the data: ");
                scanf("%d", &data);
                temp = delete(root, data);
                if(temp)
                {
                    printf("Element %d found\n", temp->data);
                }
                else
                {
                    printf("Search Unsuccessfullly");
                }

            break;

            case 4:
                temp = findMax(root);
                if(temp)
                    printf("MAXIMUM is %d", temp->data);
            break;

            case 5:
                temp = findMin(root);
                if(temp)
                    printf("MINIMUM is %d", temp->data);
            break;

            case 6:
                printf("Preorder\n");
                preorder(root);

                printf("\nInorder\n");
                inorder(root);

                printf("\nPostorder\n");
                postorder(root);
            break;

            case 7: printf("%d", findHeight(root));
            break;

            case 8: exit(1);
            break;

            default: printf("Invalid Input");
            break;
        }
    }
    while(choice != 7);
}