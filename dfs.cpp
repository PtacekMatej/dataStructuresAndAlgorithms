#include <vector>
#include <stack>
#include <iostream>
#include <cassert>


#define NO_VERTEX static_cast<size_t>(-1)

std::vector<size_t> dfs(const std::vector<std::vector<size_t>>& graph, size_t startingPoint)
{
    std::vector<bool> visited(graph.size(), false);
    std::vector<size_t> predecesors(graph.size(), NO_VERTEX);
    std::vector<size_t> used(graph.size(), 0);
    std::stack<size_t> s;
    visited[startingPoint] = true;
    s.push(startingPoint);
    while(!s.empty())
    {
        if(used[s.top()] >= graph[s.top()].size())
        {
            s.pop();
            continue;
        }
        size_t next = graph[s.top()][used[s.top()]++];
        if(visited[next])
            continue;
        visited[next] = true;
        predecesors[next] = s.top();
        s.push(next);
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
    assert(dfs(graph, 0) == std::vector<size_t>({NO_VERTEX, 0, 3, 4, 1, 2, 3, 2, 9, 7}));
    assert(dfs(graph, 7) == std::vector<size_t>({9, 0, 3, 4, 1, 2, 3, NO_VERTEX, 3, 7}));
    graph.push_back({});
    assert(dfs(graph, 10) == std::vector<size_t>(11, NO_VERTEX));
    assert(dfs(graph, 7) == std::vector<size_t>({9, 0, 3, 4, 1, 2, 3, NO_VERTEX, 3, 7, NO_VERTEX}));
}