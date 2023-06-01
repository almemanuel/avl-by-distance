import random
import math

class City:
    def __init__(self, points):
        self.points = points
        self.graph = [[math.inf] * len(points) for _ in range(len(points))]

    def resize_graph(self, size):
        for row in self.graph:
            row.extend([math.inf] * size)
        self.graph.extend([[math.inf] * (size + len(self.points)) for _ in range(size)])


    def add_distance(self, point1, point2, distance):
        self.graph[point1][point2] = distance
        self.graph[point2][point1] = distance

def calculate_distances(city):
    n = len(city.points)
    for i in range(n):
        min_distance = min(city.graph[i])
        for j in range(n):
            if city.graph[i][j] != math.inf:
                city.graph[i][j] -= min_distance
    city.resize_graph(n)




def find_best_point(city):
    n = len(city.points)
    if n == 1:
        return city.points[0]

    # print(city.graph)
    mid = n // 2
    left_city = City(city.points[:mid])
    # print(left_city.points)
    right_city = City(city.points[mid:])
    # print(right_city.points)

    left_city.resize_graph(mid)
    right_city.resize_graph(n - mid)

    for i in range(mid):
        for j in range(mid, n):
            left_city.add_distance(i, j - mid, city.graph[i][j])
            right_city.add_distance(j - mid, i, city.graph[j][i + mid])

    # Atualize a matriz graph em right_city
    for i in range(n - mid):
        for j in range(mid):
            right_city.add_distance(i, j + mid, city.graph[i + mid][j])

    calculate_distances(left_city)
    calculate_distances(right_city)

    best_distance = math.inf
    best_point = None

    for i in range(n):
        distance = min(left_city.graph[i]) + min(right_city.graph[i])
        if distance < best_distance:
            best_distance = distance
            best_point = city.points[i + mid]

    return best_point


def calculate_distance(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def test_algorithm(points):
    city = City(points)
    for i in range(len(points)):
        for j in range(len(points)):
            city.add_distance(i, j, calculate_distance(points[i], points[j]))
    best_point = find_best_point(city)
    print("Melhor ponto de instalação:", best_point)

# Teste com 5 pontos aleatórios
points = [(random.randint(1, 100), random.randint(1, 100)) for _ in range(5)]
test_algorithm(points)

# Teste com 10 pontos aleatórios
points = [(random.randint(1, 100), random.randint(1, 100)) for _ in range(10)]
test_algorithm(points)

# Teste com 20 pontos aleatórios
points = [(random.randint(1, 100), random.randint(1, 100)) for _ in range(20)]
test_algorithm(points)

# Teste com 50 pontos aleatórios
points = [(random.randint(1, 100), random.randint(1, 100)) for _ in range(50)]
test_algorithm(points)

test_algorithm([(0, 0), (1, 2), (3, 1)])
test_algorithm([(10, 5), (8, 3), (6, 1), (4, 2), (2, 4)])
test_algorithm([(5, 5), (2, 2), (8, 8), (3, 3), (9, 9), (1, 1)])
test_algorithm([(1, 1)])
test_algorithm([(7, 2), (5, 8), (4, 4), (9, 6), (2, 9)])
