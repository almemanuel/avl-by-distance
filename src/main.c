#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    int x;
    int y;
} Point;

// Calcula a distância ao quadrado entre dois pontos
double distance_squared(Point p1, Point p2) {
    // Calcula as diferenças nas coordenadas x e y
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    // Retorna a soma dos quadrados das diferenças
    return dx * dx + dy * dy;
}

// Função auxiliar usada na recursão para encontrar o melhor ponto de instalação
Point find_best_fire_station_recursive(Point points[], int start, int end, bool sortByX);

// Função principal para encontrar o melhor ponto de instalação
Point find_best_fire_station(Point points[], int start, int end, bool sortByX) {
    // Caso base: se o início e o fim são o mesmo, retorna o ponto único
    if (start == end)
        return points[start];

    // Calcula o ponto médio do intervalo
    int mid = start + (end - start) / 2;
    // Chama recursivamente a função para encontrar o melhor ponto na metade esquerda
    Point leftBest = find_best_fire_station(points, start, mid, sortByX);
    // Chama recursivamente a função para encontrar o melhor ponto na metade direita
    Point rightBest = find_best_fire_station(points, mid + 1, end, sortByX);

    // Calcula as distâncias quadradas dos pontos médios
    double leftDist = distance_squared(leftBest, points[mid]);
    double rightDist = distance_squared(rightBest, points[mid]);
    // Compara as distâncias e seleciona o melhor ponto
    Point bestPoint = (leftDist < rightDist) ? leftBest : rightBest;

    // Verifica se algum ponto fora da faixa tem uma distância menor
    for (int i = start; i <= end; i++) {
        double dist = distance_squared(points[i], points[mid]);
        // Se encontrarmos um ponto com uma distância menor, atualizamos o melhor ponto
        if (dist < distance_squared(bestPoint, points[mid]))
            bestPoint = points[i];
    }

    // Retorna o melhor ponto encontrado
    return bestPoint;
}

// Função auxiliar para chamar a função principal com a configuração inicial correta
Point find_best_fire_station_recursive(Point points[], int start, int end, bool sortByX) {
    // Chama a função principal para encontrar o melhor ponto de instalação
    return find_best_fire_station(points, start, end, sortByX);
}

int main() {
    // Cria um array de pontos
    Point points[] = {
        {1, 1},
        {2, 5},
        {3, 3},
        {5, 2},
        {7, 1}
    };
    // Calcula o número de pontos no array
    int numPoints = sizeof(points) / sizeof(points[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    Point bestPoint = find_best_fire_station(points, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 3 && bestPoint.y == 3);

    Point points_1[] = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_1) / sizeof(points_1[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_1, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 2 && bestPoint.y == 2);

    Point points_2[] = {
        {1, 1},
        {2, 5},
        {3, 3},
        {5, 2},
        {7, 1}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_2) / sizeof(points_2[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_2, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 3 && bestPoint.y == 3);

    Point points_3[] = {
        {1, 3},
        {2, 2},
        {3, 4},
        {4, 1},
        {5, 5}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_3) / sizeof(points_3[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_3, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 3 && bestPoint.y == 4);

    Point points_4[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_4) / sizeof(points_4[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_4, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 3 && bestPoint.y == 4);

    Point points_5[] = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
        {5, 5},
        {6, 6}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_5) / sizeof(points_5[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_5, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 3 && bestPoint.y == 3);

    Point points_6[] = {
        {2, 5},
        {4, 3},
        {6, 1},
        {8, 4},
        {10, 2},
        {12, 6},
        {14, 3}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_6) / sizeof(points_6[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_6, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 8 && bestPoint.y == 4);

    Point points_7[] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
        {2, 0},
        {2, 1}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_7) / sizeof(points_7[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_7, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 1 && bestPoint.y == 0);

    Point points_8[] = {
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_8) / sizeof(points_8[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_8, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 1 && bestPoint.y == 3);

    Point points_9[] = {
        {1, 2},
        {2, 2},
        {3, 2},
        {4, 2},
        {5, 2}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_9) / sizeof(points_9[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_9, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 3 && bestPoint.y == 2);

    Point points_10[] = {
        {2, 3},
        {4, 1},
        {5, 4},
        {7, 2},
        {8, 5},
        {9, 3}
    };
    // Calcula o número de pontos no array
    numPoints = sizeof(points_10) / sizeof(points_10[0]);

    // Chama a função para encontrar o melhor ponto de instalação, ordenando por x
    bestPoint = find_best_fire_station(points_10, 0, numPoints - 1, true);
    // Imprime o resultado
    assert(bestPoint.x == 5 && bestPoint.y == 4);

    printf("Sucesso\n");

    return 0;
}
