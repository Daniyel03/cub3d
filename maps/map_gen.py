import random

def generate_map(width, height):
    # Initialize the map with all walls
    map_layout = [[1 for _ in range(width)] for _ in range(height)]
    
    # Create walkable space inside
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            map_layout[i][j] = 0
    
    # Create some random walls inside
    for _ in range(width * height // 20):  # Add about 5% internal walls
        x = random.randint(1, width - 2)
        y = random.randint(1, height - 2)
        map_layout[y][x] = 1
    
    # Create some rooms
    for _ in range(10):  # Create 10 rooms
        room_width = random.randint(5, 20)
        room_height = random.randint(5, 20)
        x = random.randint(1, width - room_width - 1)
        y = random.randint(1, height - room_height - 1)
        
        for i in range(y, y + room_height):
            for j in range(x, x + room_width):
                map_layout[i][j] = 0
        
        # Add walls around the room
        for i in range(y - 1, y + room_height + 1):
            map_layout[i][x - 1] = 1
            map_layout[i][x + room_width] = 1
        for j in range(x - 1, x + room_width + 1):
            map_layout[y - 1][j] = 1
            map_layout[y + room_height][j] = 1
    
    return map_layout

# Generate the map
map_600x600 = generate_map(499, 499)

# To visualize a small part of the map (e.g., top-left 20x20)
for row in map_600x600:
    print(''.join(str(cell) for cell in row))