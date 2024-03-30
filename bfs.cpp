#include <vector>
#include <queue>
#include <iostream>
#include <cassert>


#define NO_VERTEX static_cast<size_t>(-1)

std::vector<size_t> bfs(const std::vector<std::vector<size_t>>& graph, size_t startingPoint)
{
    std::vector<bool> visited(graph.size(), false);
    std::vector<size_t> predecesors(graph.size(), NO_VERTEX);
    std::queue<size_t> q;
    visited[startingPoint] = true;
    q.push(startingPoint);
    while(!q.empty())
    {
        for(const size_t & next : graph[q.front()])
        {
            if(!visited[next])
            {
                visited[next] = true;
                q.push(next);
                predecesors[next] = q.front();
            }
        }
        q.pop();
    }
    return predecesors;
}



//basic tests
int main()
{
    std::vector<std::vector<size_t>> graph{
        {1, 2, 3},
        {0, 4, 7},
        {1, 3, 5, 7, 9},
        {2, 4, 6, 8},
        {1, 3, 5, 6},
        {0},
        {1, 3, 4},
        {9},
        {9},
        {0, 1, 2, 3, 4, 5, 7, 8}
    };
    assert(bfs(graph, 0) == std::vector<size_t>({NO_VERTEX, 0, 0, 0, 1, 2, 3, 1, 3, 2}));
    assert(bfs(graph, 7) == std::vector<size_t>({9, 9, 9, 9, 9, 9, 3, NO_VERTEX, 9, 7}));
    graph.push_back({});
    assert(bfs(graph, 10) == std::vector<size_t>(11, NO_VERTEX));
    assert(bfs(graph, 7) == std::vector<size_t>({9, 9, 9, 9, 9, 9, 3, NO_VERTEX, 9, 7, NO_VERTEX}));
}