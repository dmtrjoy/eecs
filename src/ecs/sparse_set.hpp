#ifndef EECS_SPARSE_SET_HPP
#define EECS_SPARSE_SET_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

#include "types.hpp"

namespace eecs {

template <typename T, std::unsigned_integral IdType = u32>
class sparse_set {
public:
    using value_type = T;
    using id_type = IdType;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    /// Returns a reference to the value that `id` maps to.
    ///
    /// \param id The `id` of the element to find.
    /// \return A reference to the mapped value.
    [[nodiscard]] reference operator[](const id_type id) noexcept
    {
        assert(id != s_tombstone);
        assert(contains(id));
        return m_dense_values[m_sparse[id]];
    }

    /// Returns a constant reference to the value that `id` maps to.
    ///
    /// \param id The `id` of the element to find.
    /// \return A constant reference to the mapped value.
    [[nodiscard]] const_reference operator[](const id_type id) const noexcept
    {
        assert(id != s_tombstone);
        assert(contains(id));
        return m_dense_values[m_sparse[id]];
    }

    /// Returns an iterator to the first element of this container.
    ///
    /// \return An iterator to the first element.
    iterator begin() noexcept { return m_dense_values.begin(); }

    /// Returns a constant iterator to the first element of this container.
    ///
    /// \return A constant iterator to the first element.
    const_iterator begin() const noexcept { return m_dense_values.begin(); };

    /// Returns an iterator to the last element of this container.
    ///
    /// \return An iterator to the last element.
    iterator end() noexcept { return m_dense_values.end(); }

    /// Returns a constant iterator to the last element of this container.
    ///
    /// \return A constant iterator to the last element.
    const_iterator end() const noexcept { return m_dense_values.end(); };

    /// Checks whether the container is empty.
    ///
    /// \return Whether the container is empty.
    [[nodiscard]] bool empty() const noexcept { return size() == 0; }

    /// Returns the size of the container.
    ///
    /// \return The size of the container.
    [[nodiscard]] id_type size() const noexcept { return m_dense_ids.size(); }

    void insert(const id_type id, const value_type& value)
    {
        assert(id != s_tombstone);

        if (contains(id)) {
            m_dense_values[m_sparse[id]] = value;
            return;
        }

        if (id >= m_sparse.size()) {
            m_sparse.resize(id + 1, s_tombstone);
        }

        m_sparse[id] = m_dense_ids.size();
        m_dense_ids.push_back(id);
        m_dense_values.push_back(value);
    }

    /// Inserts a new element into the container constructed in-place with the
    /// given `args`. Overwrites the value that `id` maps to if one already
    /// exists.
    ///
    /// \param id The `id` of the element to insert.
    /// \param args The arguments to forward to the constructor of the element.
    /// \return A reference to the inserted element.
    template <typename... Args>
    reference emplace(const id_type id, Args&&... args)
    {
        assert(id != s_tombstone);

        if (contains(id)) {
            reference value = m_dense_values[m_sparse[id]];
            value = value_type(std::forward<Args>(args)...);
            return value;
        }

        if (id >= m_sparse.size()) {
            m_sparse.resize(id + 1, s_tombstone);
        }

        m_sparse[id] = m_dense_ids.size();
        m_dense_ids.push_back(id);
        m_dense_values.emplace_back(std::forward<Args>(args)...);
    }

    /// Removes the element (if one exists) with the identifier equivalent to
    /// `id`.
    ///
    /// \param id The `id` of the element to remove.
    void erase(const id_type id) noexcept
    {
        assert(id != s_tombstone);

        if (!contains(id)) {
            return;
        }

        const id_type dense_id { m_sparse[id] };

        std::swap(m_dense_ids[dense_id], m_dense_ids.back());
        std::swap(m_dense_values[dense_id], m_dense_values.back());

        m_dense_ids.pop_back();
        m_dense_values.pop_back();

        m_sparse[m_dense_ids[dense_id]] = dense_id;
        m_sparse[id] = s_tombstone;
    };

    /// Checks if there is an element with an identifier equivalent to `id` in
    /// the container.
    ///
    /// \param id The `id` of the element to search for.
    /// \return `true` if a matching element is found; `false` otherwise.
    [[nodiscard]] bool contains(const id_type id) const noexcept
    {
        assert(id != s_tombstone);

        if (id >= m_sparse.size()) {
            return false;
        }

        const id_type dense_id { m_sparse[id] };
        return dense_id != s_tombstone && m_dense_ids[dense_id] == id;
    };

private:
    static constexpr id_type s_tombstone = std::numeric_limits<id_type>().max();

    std::vector<id_type> m_sparse;
    std::vector<id_type> m_dense_ids;
    std::vector<value_type> m_dense_values;
};

} // namespace eecs

#endif
