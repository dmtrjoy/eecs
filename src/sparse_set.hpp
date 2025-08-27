#ifndef MISHA_SPARSE_SET_HPP
#define MISHA_SPARSE_SET_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace misha {

template <typename T>
class sparse_set {
public:
    [[nodiscard]] const T& at(size_t id) const;
    [[nodiscard]] const T& operator[](size_t id) const;

    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] size_t size() const noexcept;

    void insert(size_t id, const T& value);
    void erase(size_t id) noexcept;

    [[nodiscard]] bool contains(size_t id) const;

private:
    static constexpr size_t npos = static_cast<size_t>(-1);

    std::vector<size_t> m_sparse;
    std::vector<size_t> m_dense_ids;
    std::vector<T> m_dense_values;
};

template <typename T>
const T& sparse_set<T>::at(const size_t id) const
{
    if (!contains(id)) {
        throw std::out_of_range("id not found");
    }
    return m_dense_values[m_sparse[id]];
}

template <typename T>
const T& sparse_set<T>::operator[](const size_t id) const
{
    return m_dense_values[m_sparse[id]];
}

template <typename T>
bool sparse_set<T>::empty() const noexcept
{
    return size() == 0;
}

template <typename T>
size_t sparse_set<T>::size() const noexcept
{
    return m_dense_ids.size();
}

template <typename T>
void sparse_set<T>::insert(const size_t id, const T& value)
{
    if (contains(id)) {
        m_dense_values[m_sparse[id]] = value;
        return;
    }

    if (id >= m_sparse.size()) {
        m_sparse.resize(id + 1, npos);
    }

    m_sparse[id] = m_dense_ids.size();
    m_dense_ids.push_back(id);
    m_dense_values.push_back(value);
}

template <typename T>
void sparse_set<T>::erase(const size_t id) noexcept
{
    if (!contains(id)) {
        return;
    }

    const size_t dense_idx { m_sparse[id] };

    std::swap(m_dense_ids[dense_idx], m_dense_ids.back());
    std::swap(m_dense_values[dense_idx], m_dense_values.back());

    m_dense_ids.pop_back();
    m_dense_values.pop_back();

    m_sparse[m_dense_ids[dense_idx]] = dense_idx;
    m_sparse[id] = npos;
}

template <typename T>
bool sparse_set<T>::contains(const size_t id) const
{
    if (id >= m_sparse.size()) {
        return false;
    }

    const size_t denseIdx { m_sparse[id] };
    return denseIdx != npos && m_dense_ids[denseIdx] == id;
}

} // namespace misha

#endif
