#include <vector>
#include <queue>
#include <stdexcept>
#include <iostream>
#include <cassert>


std::vector<size_t> topSort(const std::vector<std::vector<size_t>> & graph)
{
    std::vector<size_t> dependencies(graph.size(),0);
    for(const auto & neighbors : graph)
        for(const auto & a : neighbors)
            ++dependencies[a];
    std::queue<size_t> toEval;
    for(size_t i = 0; i < graph.size(); ++i)
        if(dependencies[i] == 0)
            toEval.push(i);
    std::vector<size_t> result;
    while(!toEval.empty())
    {
        for(const auto & a : graph[toEval.front()])
            if(--dependencies[a] == 0)
                toEval.push(a);
        result.push_back(toEval.front());
        toEval.pop();
    }
    if(result.size() != graph.size())
        throw std::domain_error("directed graph with cycles can not be topologicaly sorted");
    return result;
}



//basic tests
int main()
{
    try{
        topSort({{1}, {0}, {0, 1}});
        std::cout << "exception not thrown\n";
    } catch (std::domain_error& e){}
    try{
        topSort({{}, {2}, {1}});
        std::cout << "exception not thrown\n";
    } catch (std::domain_error& e){}
    assert(topSort({{1}, {2}, {3}, {}}) == std::vector<size_t>({0, 1, 2, 3}));
    assert(topSort({{2},{0, 2, 3}, {}, {0, 2}}) == std::vector<size_t>({1, 3, 0, 2}));
}

