#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int data;
    struct n *left;
    struct n *right;
    int height;
} Node;

int height(Node *tree) {
    if (tree == NULL)
        return 0;
    return tree->height;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}


Node *turn_right(Node *tree) {
    Node *willRoot = tree->left;
    Node *willLeft = willRoot->right;
    willRoot->right = tree;
    tree->left = willLeft;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    willRoot->height = max(height(willRoot->left), height(willRoot->right)) + 1;
    return willRoot;
}

Node *turn_left(Node *tree) {
    Node *willRoot = tree->right;
    Node *willRight = willRoot->left;
    willRoot->left = tree;
    tree->right = willRight;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    willRoot->height = max(height(willRoot->left), height(willRoot->right)) + 1;
    return willRoot;
}

int dengeKontrol(Node *tree) {
    if (tree == NULL)
        return 0;
    return height(tree->left) - height(tree->right);
}

Node *ekle(Node *tree, int data) {
    if (tree == NULL) {
        Node *root = (Node *) malloc(sizeof(Node));
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        root->height = 1;
        return root;
    }

    if (tree->data < data) {
        tree->right = ekle(tree->right, data);

    } else if (tree->data > data) {
        tree->left = ekle(tree->left, data);
    } else
        return tree;

    tree->height = 1 + max(height(tree->left), height(tree->right));
    int denge = dengeKontrol(tree);
    //sol sol
    if (denge > 1 && data < tree->left->data) {
        return turn_right(tree);
    }
    //sol-sağ
    if (denge > 1 && data > tree->left->data) {
        tree->left = turn_left(tree->left);
        return turn_right(tree);
    }
    //sağ-sağ
    if (denge < -1 && data > tree->right->data) {
        return turn_left(tree);
    }
    //sağ-sol
    if (denge < -1 && data < tree->right->data) {
        tree->right = turn_right(tree->right);
        return turn_left(tree);
    }
    return tree;
}

void yazdir(Node *tree) {
    if (tree == NULL)
        return;
    yazdir(tree->left);
    printf("%d ", tree->data);
    yazdir(tree->right);
}

void yazdir2(Node *tree) {
    if (tree == NULL)
        return;
    yazdir2(tree->right);
    printf("%d ", tree->data);
    yazdir2(tree->left);
}

void yazdir3(Node *tree) {
    if (tree == NULL)
        return;
    printf("%d ", tree->data);
    yazdir3(tree->left);

    yazdir3(tree->right);
}


int main() {
    Node *Tree = NULL;
    Tree = ekle(Tree, 15);
    Tree = ekle(Tree, 21);
    Tree = ekle(Tree, 17);
    Tree = ekle(Tree, 16);
    Tree = ekle(Tree, 14);
    Tree = ekle(Tree, 8);
    Tree = ekle(Tree, 19);
    Tree = ekle(Tree, 18);
    Tree = ekle(Tree, 11);
    Tree = ekle(Tree, 12);
    Tree = ekle(Tree, 13);
    Tree = ekle(Tree, 31);
    Tree = ekle(Tree, 54);
    Tree = ekle(Tree, 1);
    Tree = ekle(Tree, 46);
    /*Tree = ekle(Tree,10);
    Tree = ekle(Tree,20);
    Tree = ekle(Tree,30);
    Tree = ekle(Tree,40);
    Tree = ekle(Tree,50);
    Tree = ekle(Tree,60);*/
    yazdir(Tree);
    printf("LNR\n");
    yazdir2(Tree);
    printf("RNL\n");
    yazdir3(Tree);
    printf("NLR");

    return 0;
}
