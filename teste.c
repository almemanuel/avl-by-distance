#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int x;
    int y;
    int dist;
} Point;

// Inicio Quick Sort
// Função de troca de elementos
void trocar(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// Função para encontrar o pivô
int encontrarPivo(Point point[], int inicio, int fim) {
    Point pivo = point[fim];
    int i = inicio - 1;
    
    for (int j = inicio; j <= fim - 1; j++) {
        if (point[j].x < pivo.x || (point[j].x == pivo.x && point[j].y < pivo.y)) { // Ordena de maneira crescente os pontos em relação a X e se for igual considera o Y tbm
            i++;
            trocar(&point[i], &point[j]);
        }
    }
    
    trocar(&point[i + 1], &point[fim]);
    return i + 1;
}

// Função de ordenação QuickSort
void quicksort(Point point[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = encontrarPivo(point, inicio, fim);
        
        quicksort(point, inicio, pivo - 1);
        quicksort(point, pivo + 1, fim);
    }
}

// Função auxiliar para exibir o vetor ordenado
void exibirPontos(Point point[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("(%d, %d) ", point[i].x, point[i].y);
    }
    printf("\n");
}    

//Cria Pontos ramdomicos com base no seu tamanho e faixa de valores delimitado
Point randomizar(Point point[], int tamanho, int minX, int maxX, int minY, int maxY){
    int truemaxX = maxX - minX;
    int truemaxY = maxY - minY;
    int i;
    for (i = 0; i < tamanho; i++) {   
        point[i].x = minX + rand() % truemaxX;  // gera um número inteiro aleatório entre o min e o max para x
        point[i].y = minY + rand() % truemaxY;  // gera um número inteiro aleatório entre o min e o max para y
    }
    return *point;
}

// Calcula a distância ao quadrado entre dois pontos
double distance(Point p1, Point p2) {
    // Calcula as diferenças nas coordenadas x e y
    int dx = ((p1.x - p2.x) * (p1.x - p2.x));
    int dy = ((p1.y - p2.y) * (p2.y - p2.y));
    // Retorna a soma dos quadrados das diferenças
    return sqrt(dx + dy);
}



// Função principal para encontrar o melhor ponto de instalação
Point find_best_fire_station_recursive(Point points[], int start, int end) {
    // Caso base: se o início e o fim são o mesmo, retorna o ponto único
    if (start == end)
        return points[start];

    // Calcula o ponto médio do intervalo
    int mid = start + (end - start) / 2;
    // Chama recursivamente a função para encontrar o melhor ponto na metade esquerda
    Point leftBest = find_best_fire_station_recursive(points, start, mid);
    // Chama recursivamente a função para encontrar o melhor ponto na metade direita
    Point rightBest = find_best_fire_station_recursive(points, mid + 1, end);

    // Calcula as distâncias quadradas dos pontos médios
    double leftDist = distance(leftBest, points[mid]);
    double rightDist = distance(rightBest, points[mid]);
    // Compara as distâncias e seleciona o melhor ponto
    Point bestPoint = (leftDist < rightDist) ? leftBest : rightBest;

    // Verifica se algum ponto fora da faixa tem uma distância menor
    for (int i = start; i <= end; i++) {
        double dist = distance(points[i], points[mid]);
        // Se encontrarmos um ponto com uma distância menor, atualizamos o melhor ponto
        if (dist < distance(bestPoint, points[mid]))
            bestPoint = points[i];
    }
        
    // Retorna o melhor ponto encontrado
    return bestPoint; 
}

// Função auxiliar usada na recursão para encontrar o melhor ponto de instalação
Point find_best_fire_station(Point points[], int tamanho, int start, int end) {
    quicksort(points, 0, tamanho - 1);
    printf("Pontos Ordenados\n");
    exibirPontos(points, tamanho);
    return find_best_fire_station_recursive(points, 0, tamanho -1);
}

int main() {
    int z=0;
    srand(time(NULL));
    int n, minX, minY, maxX, maxY;
    minX = minY = 1;
    maxX = maxY = 10;
    Point teste [10];
    int numPoints = sizeof(teste) / sizeof(teste[0]);

    randomizar(teste, numPoints, minX, maxX, minY, maxY); // Chama função para criar os pontos randomicos com os valores mínimos e max de X e Y baseado em seu tamanho
    
    exibirPontos(teste, numPoints);
    quicksort(teste, 0, numPoints -1);
    //exibirPontos(teste, numPoints);
    Point bestPoint = find_best_fire_station(teste, numPoints, 0, numPoints - 1);
    printf("Divisão e Conquista\n(%d, %d)\n", bestPoint.x, bestPoint.y);

    //Verificação por Força Bruta ---------------------------
    int k, l;
    /*Point bestbruto;
    int dist;
    double bestdist = INFINITY;
    for (k = 0; k < numPoints; k++) {
        dist = 0;
        for(l = 0; l < numPoints; l++){
            dist += distance(teste[k],teste[l]);
        }
        if (dist < bestdist) {
            bestdist = dist;
            bestbruto = teste[k];
        }
    }*/
    /*if((bestbruto.x != bestPoint.x) || (bestbruto.y != bestPoint.y)){                                                                                                 //printf("Força Bruta \n(%d, %d)\n", bestbruto.x, bestbruto.y);
        printf("ERRO!!\n");
        exibirPontos(teste, 10);
        printf("bruto:  (%d, %d)\n", bestbruto.x, bestbruto.y);
        printf("divisão:(%d, %d)\n", bestPoint.x, bestPoint.y);
        printf("ERRO!!\n");
    }*/
                                                                                              //printf("Sucesso\n");
    return 0;
}
