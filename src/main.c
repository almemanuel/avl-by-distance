#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Point {
    int x;
    int y;
    double distance;
    struct Point* left;
    struct Point* right;
    int height;
} Point;

int max(int a, int b);
int height(Point* node);
int getBalance(Point* node);
double calculateDistance(int x1, int y1, int x2, int y2);
Point* createNode(int x, int y, double distance);
Point* rightRotate(Point* y);
Point* leftRotate(Point* x);
Point* insert(Point* node, int x, int y);
int generateRandomNumber(int min, int max);
void generateRandomPoints(int n, int range, Point** root);
Point* findBestFireStation(Point* root);
void printAVLInOrder(Point* root);

int main() {
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios

    int n = generateRandomNumber(3, 10);  // Gera um valor aleatório entre 3 e 10 para n
    int range = generateRandomNumber(10, 100);  // Gera um valor aleatório entre 10 e 100 para range

    Point* root = NULL;
    printf("aqui\n");

    generateRandomPoints(n, range, &root);

    printf("Árvore AVL construída com sucesso.\n");

    Point* bestPoint = findBestFireStation(root);

    printf("O melhor ponto para a instalação do Corpo de Bombeiros é (%d, %d).\n", bestPoint->x, bestPoint->y);

    printAVLInOrder(root);

    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Point* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(Point* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

double calculateDistance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

Point* createNode(int x, int y, double distance) {
    Point* newNode = (Point*)malloc(sizeof(Point));
    newNode->x = x;
    newNode->y = y;
    newNode->distance = distance;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

Point* rightRotate(Point* node) {
    Point* leftChild = node->left;
    Point* rightChild = leftChild->right;

    // Realiza a rotação
    leftChild->right = node;
    node->left = rightChild;

    // Atualiza as alturas dos nós afetados
    node->height = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

    // Retorna a nova raiz
    return leftChild;
}

Point* leftRotate(Point* node) {
    Point* rightChild = node->right;
    Point* leftChild = rightChild->left;

    // Realiza a rotação
    rightChild->left = node;
    node->right = leftChild;

    // Atualiza as alturas dos nós afetados
    node->height = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

    // Retorna a nova raiz
    return rightChild;
}

Point* insert(Point* root, int x, int y) {
    if (root == NULL) {
        return createNode(x, y, 0);  // A distância para a raiz é 0 para o nó raiz
    }

    if (x < root->x) {
        root->left = insert(root->left, x, y);
    } else if (x > root->x) {
        root->right = insert(root->right, x, y);
    } else {
        if (y < root->y) {
            root->left = insert(root->left, x, y);
        } else if (y > root->y) {
            root->right = insert(root->right, x, y);
        } else {
            return root;
        }
    }

    // Atualiza a altura do nó atual
    root->height = max(height(root->left), height(root->right)) + 1;

    // Realiza o balanceamento da árvore
    int balance = getBalance(root);

    // Caso de rotação simples à esquerda (left-left)
    if (balance > 1 && x < root->left->x) {
        return rightRotate(root);
    }

    // Caso de rotação simples à direita (right-right)
    if (balance < -1 && x > root->right->x) {
        return leftRotate(root);
    }

    // Caso de rotação dupla à esquerda (left-right)
    if (balance > 1 && x > root->left->x) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso de rotação dupla à direita (right-left)
    if (balance < -1 && x < root->right->x) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Após inserir o novo nó, recalcule a distância
    root->distance = calculateDistance(x, y, root->x, root->y);

    // Retorna o nó atualizado
    return root;
}

// Definição das estruturas e funções da AVL (incluindo as funções que mencionamos anteriormente)

// Função para gerar um número aleatório entre min e max
int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Função para gerar pontos aleatórios
void generateRandomPoints(int n, int range, Point** root) {
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios

    int i;
    for (i = 0; i < n; i++) {
        int x = generateRandomNumber(-range, range);
        int y = generateRandomNumber(-range, range);
        *root = insert(*root, x, y);
    }
}

// Função para encontrar o melhor ponto de instalação dos bombeiros
Point* findBestFireStation(Point* root) {
    return root;  // O melhor ponto é a raiz da árvore AVL
}

void printAVLInOrder(Point* root) {
    if (root != NULL) {
        printAVLInOrder(root->left);
        printf("Ponto: (%d, %d) - Distância para a raiz: %.2f\n", root->x, root->y, root->distance);
        printAVLInOrder(root->right);
    }
}
