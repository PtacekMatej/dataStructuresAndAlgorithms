#include <vector>
#include <stdexcept>
#include <cassert>
#include <iostream>

class CUnionFind
{
    public:
        CUnionFind(size_t size)
        {
            m_Nodes.reserve(size);
            for(size_t i = 0; i < size; i++)
                m_Nodes.push_back(new CNode);
        }
        ~CUnionFind()
        {
            for(auto node : m_Nodes)
                delete node;
        }
        bool merge(size_t a, size_t b)
        {
            if(a >= m_Nodes.size() || b >= m_Nodes.size())
                throw std::out_of_range("wrong argument for CUnionFind::merge");
            return m_Nodes[a]->merge(m_Nodes[b]);
        }

    private:
        class CNode
        {
            public:
                bool merge(CNode* other)
                {
                    CNode* thisComponent = this->getComponent();
                    CNode* otherComponent = other->getComponent();
                    if(thisComponent == otherComponent)
                        return false;
                    if(thisComponent->m_Depth > otherComponent->m_Depth)
                        otherComponent->m_Parent = thisComponent;
                    else if(thisComponent->m_Depth <= otherComponent->m_Depth)
                        thisComponent->m_Parent = otherComponent;
                    if(thisComponent->m_Depth == otherComponent->m_Depth)
                        otherComponent->m_Depth++;
                    return true;
                }

            private:
                CNode* m_Parent = nullptr; 
                size_t m_Depth = 0;

                CNode* getComponent()
                {
                    CNode* result = this;
                    while(result->m_Parent != nullptr)
                        result = result->m_Parent;
                    return result;
                }
        };

        std::vector<CNode*> m_Nodes;
};



//basic testing
int main()
{
    CUnionFind UF(10);
    std::vector<std::pair<int, int>> edgesT{{0, 1}, {1, 2},{3, 4}, {7, 2},{5, 7}, {5, 9}};
    for(const auto & edge : edgesT)
        assert(UF.merge(edge.first, edge.second));
    std::vector<std::pair<int, int>> edgesF{{1, 0}, {0, 2},{3, 3}, {0, 7},{1, 5}, {7, 9}};
    for(const auto & edge : edgesF)
        assert(!UF.merge(edge.first, edge.second));
    std::vector<std::pair<int, int>> edgesT2{{1, 3},{4, 6},{9, 8}};
    for(const auto & edge : edgesT2)
        assert(UF.merge(edge.first, edge.second));
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
             assert(!UF.merge(i, j));
    try{
        UF.merge(1, 10);
        std::cout << "exception not thrown\n";
    } catch(std::out_of_range& e){}
    try{
        UF.merge(10, 5);
        std::cout << "exception not thrown\n";
    } catch(std::out_of_range& e){}
    try{
        UF.merge(100, 100);
        std::cout << "exception not thrown\n";
    } catch(std::out_of_range& e){}
}