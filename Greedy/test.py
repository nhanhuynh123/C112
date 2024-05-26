from collections import deque

def bfs(m, n, start, end, grid):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    queue = deque([start])
    visited = set()
    visited.add(start)
    distance = 0
    
    while queue:
        for _ in range(len(queue)):
            x, y = queue.popleft()
            
            if (x, y) == end:
                return distance
            
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                
                if 0 <= nx < m and 0 <= ny < n and (nx, ny) not in visited and grid[nx][ny] == 0:
                    visited.add((nx, ny))
                    queue.append((nx, ny))
        
        distance += 1
    
    return -1

def main():
    # Đọc dữ liệu đầu vào
    m, n, sx, sy, ex, ey = map(int, input().split())
    grid = []
    for _ in range(m):
        grid.append(list(map(int, input().split())))
    
    # Tìm khoảng cách ngắn nhất bằng BFS
    start = (sx, sy)
    end = (ex, ey)
    
    result = bfs(m, n, start, end, grid)
    print(result)

if __name__ == "__main__":
    main()
