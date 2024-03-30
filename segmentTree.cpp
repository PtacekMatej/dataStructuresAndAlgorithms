#include <vector>
#include <cassert>
#include <functional>

template<class _T, class _ADD>
class CSegmentTree
{
    public:
        CSegmentTree(const std::vector<_T> vec, _ADD add = _ADD()): m_Add(add)
        {
            m_Size = 1;
            while(m_Size < vec.size())
                m_Size*=2;
            m_Data.resize(2*m_Size);
            for(size_t i = m_Size; i < vec.size() + m_Size; ++i)
                m_Data[i] = vec[i - m_Size];
            for(size_t i = m_Size-1; i > 0; --i)
                m_Data[i] = m_Add(m_Data[2*i], m_Data[2*i + 1]);
        }
        void update(size_t index, _T value)
        {
            size_t indexToUpdate = m_Size + index;
            m_Data[indexToUpdate] = value;
            propagateUpdate(indexToUpdate);
        }
        _T query(size_t lower, size_t upper) // both bounds inclusive
        {
            lower += m_Size;
            upper += m_Size;
            _T result = _T();
            while(lower < upper)
            {
                if(lower%2)
                    result = m_Add(result, m_Data[lower++]);   
                if(!(upper%2))
                    result = m_Add(result, m_Data[upper--]);
                lower /= 2;
                upper /= 2;
            }
            return m_Add(result, m_Data[lower]);
        }
    private:
        _ADD m_Add;
        size_t m_Size;
        std::vector<_T> m_Data;

        void propagateUpdate(size_t index)
        {
            size_t indexToUpdate = index/2;
            if(indexToUpdate == 0)
                return;
            m_Data[indexToUpdate] = m_Add(m_Data[2*indexToUpdate], m_Data[2*indexToUpdate + 1]);
            return propagateUpdate(indexToUpdate);
        }

};


//basic tests
int main()
{
    CSegmentTree<int, std::function<int(int, int)>> segTree(std::vector<int>(100, 1), [](int a, int b){return a + b;});
    assert(segTree.query(0, 99) == 100);
    assert(segTree.query(10, 30) == 21);
    segTree.update(70, 30);
    assert(segTree.query(70, 70) == 30);
    assert(segTree.query(0, 99) == 129);
}