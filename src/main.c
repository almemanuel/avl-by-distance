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

Point* rightRotate(Point* y) {
    Point* x = y->left;
    Point* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Point* leftRotate(Point* x) {
    Point* y = x->right;
    Point* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Point* insert(Point* root, int x, int y) {
    // Etapa de inserção normal
    if (root == NULL) {
        return createNode(x, y, 0);
    }

    if (x < root->x) {
        root->left = insert(root->left, x, y);
    } else if (x > root->x) {
        root->right = insert(root->right, x, y);
    } else {
        // Se as coordenadas x forem iguais, verifique as coordenadas y
        if (y < root->y) {
            root->left = insert(root->left, x, y);
        } else if (y > root->y) {
            root->right = insert(root->right, x, y);
        } else {
            // Se as coordenadas x e y forem iguais, o ponto já está na árvore
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
