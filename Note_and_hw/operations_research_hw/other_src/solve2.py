import numpy as np
import itertools
import random

# 给定距离矩阵
dist_matrix = np.array([
    [0, 5, 4.5, 6, 8],
    [5, 0, 5.5, 1.25, 14],
    [4.5, 5.5, 0, 5, 9.5],
    [6, 1.25, 5, 0, 12.5],
    [8, 14, 9.5, 12.5, 0]
])

# 获取所有边及其距离
edges = [(i, j, dist_matrix[i, j]) for i in range(len(dist_matrix)) for j in range(i + 1, len(dist_matrix))]

# 遗传算法参数
population_size = 50
mutation_rate = 0.1
generations = 100

# 计算适应度函数
def calculate_fitness(individual):
    total_distance = sum(dist_matrix[i, j] + 4 for i, j in individual)
    return -total_distance  # 由于遗传算法是寻找最大值，所以返回负值

# 生成初始种群
def generate_population(size):
    population = []
    for _ in range(size):
        individual = random.sample(edges, 5)
        population.append(individual)
    return population

# 选择父母
def select_parents(population, fitness):
    parents = random.choices(population, weights=fitness, k=2)
    return parents

# 交叉操作
def crossover(parent1, parent2):
    crossover_point = random.randint(1, len(parent1) - 1)
    child1 = parent1[:crossover_point] + parent2[crossover_point:]
    child2 = parent2[:crossover_point] + parent1[crossover_point:]
    return child1, child2

# 变异操作
def mutate(individual):
    if random.random() < mutation_rate:
        i, j = random.sample(range(len(individual)), 2)
        individual[i], individual[j] = individual[j], individual[i]

# 遗传算法主函数
def genetic_algorithm():
    population = generate_population(population_size)
    
    for _ in range(generations):
        fitness = [calculate_fitness(ind) for ind in population]
        new_population = []
        
        for _ in range(population_size // 2):
            parent1, parent2 = select_parents(population, fitness)
            child1, child2 = crossover(parent1, parent2)
            mutate(child1)
            mutate(child2)
            new_population.extend([child1, child2])
        
        population = new_population
    
    best_individual = max(population, key=calculate_fitness)
    best_fitness = calculate_fitness(best_individual)
    
    return best_individual, -best_fitness

best_individual, best_fitness = genetic_algorithm()
print("最优连接组合:", best_individual)
print("最小总距离:", best_fitness)
