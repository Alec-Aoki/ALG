import random

def generate_hamiltonian_cycle(num_cities, min_distance=1, max_distance=100):
    cities = list(range(1, num_cities + 1))
    random.shuffle(cities)
    cycle = cities + [cities[0]]  # Add the first city at the end to complete the cycle
    
    distances = {}
    for i in range(num_cities):
        city1, city2 = cycle[i], cycle[i+1]
        distances[(min(city1, city2), max(city1, city2))] = random.randint(min_distance, max_distance)
    
    return cycle[0], distances

def add_random_connections(distances, num_cities, additional_connections):
    cities = set(range(1, num_cities + 1))
    for _ in range(additional_connections):
        city1, city2 = random.sample(list(cities), 2)
        if city1 != city2 and (min(city1, city2), max(city1, city2)) not in distances:
            distances[(min(city1, city2), max(city1, city2))] = random.randint(1, 100)

def write_test_case(filename, num_cities, start_city, distances):
    with open(filename, 'w') as f:
        f.write(f"{num_cities}\n")
        f.write(f"{start_city}\n")
        f.write(f"{len(distances)}\n")
        for (city1, city2), distance in distances.items():
            f.write(f"{city1} {city2} {distance}\n")

def solve_tsp(start_city, distances, num_cities):
    cities = set(range(1, num_cities + 1))
    
    def travel(current, unvisited, path, total_distance):
        if not unvisited:
            return path + [start_city], total_distance + distances.get((min(current, start_city), max(current, start_city)), float('inf'))
        
        best_path, best_distance = None, float('inf')
        for next_city in unvisited:
            if (min(current, next_city), max(current, next_city)) in distances:
                new_path, new_distance = travel(
                    next_city,
                    unvisited - {next_city},
                    path + [next_city],
                    total_distance + distances[(min(current, next_city), max(current, next_city))]
                )
                if new_distance < best_distance:
                    best_path, best_distance = new_path, new_distance
        
        return best_path, best_distance

    return travel(start_city, cities - {start_city}, [start_city], 0)

def main():
    num_cities = int(input("Enter the number of cities: "))
    
    start_city, distances = generate_hamiltonian_cycle(num_cities)
    
    # Add some random additional connections
    max_additional = (num_cities * (num_cities - 1) // 2) - num_cities
    additional_connections = random.randint(0, max_additional)
    add_random_connections(distances, num_cities, additional_connections)
    
    write_test_case("testcase.in", num_cities, start_city, distances)
    
    print(f"Test case has been generated and saved to 'testcase.in'")
    
    best_route, best_distance = solve_tsp(start_city, distances, num_cities)
    
    print(f"{'-'.join(map(str, best_route))} {best_distance}")

if __name__ == "__main__":
    main()