#ifndef EECS_ANY_HPP
#define EECS_ANY_HPP

#include <any>
#include <concepts>
#include <format>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <utility>

namespace eecs {

/// A type-safe container for single values of any type.
class any {
public:
    /// Constructs an empty `::any`.
    any() noexcept = default;

    /// Constructs an `::any` by copying from an existing one.
    ///
    /// \param other The object to copy from.
    any(const any& other)
    {
        if (other.has_value()) {
            m_pimpl = other.m_pimpl->clone();
            m_type_index = other.m_type_index;
        }
    }

    /// Constructs an `::any` by moving the contents of another `::any` into
    /// this one.
    ///
    /// \param other The object to move from. Left in a valid but unspecified
    ///     state.
    any(any&& other) noexcept = default;

    /// Constructs an `::any` holding an object of type `ValueType`,
    /// constructed in place.
    ///
    /// \tparam ValueType The type of the object to construct and store.
    /// \tparam Args The types of argument to forward.
    /// \param args Arguments forwarded to the constructor of the held object.
    template <typename ValueType, typename... Args>
    explicit any(std::in_place_type_t<ValueType> /*unused*/, Args&&... args)
        : m_pimpl(
              std::make_unique<holder<ValueType>>(std::forward<Args>(args)...))
        , m_type_index(std::type_index(typeid(ValueType)))
    {
    }

    /// Constructs an `::any` holding an object of type `ValueType`,
    /// moved from another instance.
    ///
    /// \tparam ValueType The type of the object to move from and store.
    /// \param value The object to move from and store. Left in a valid but
    ///     unspecified state.
    template <typename ValueType>
    explicit any(ValueType&& value)
        requires(!std::is_same_v<std::decay_t<ValueType>, any>)
        : m_pimpl(std::make_unique<holder<ValueType>>(
              std::forward<ValueType>(value)))
        , m_type_index(std::type_index(typeid(ValueType)))
    {
    }

    /// Copies the contents of another `::any` into this one.
    ///
    /// \param other The object to copy from.
    /// \return A reference to this object.
    any& operator=(const any& other)
    {
        if (&other != this) {
            if (other.has_value()) {
                m_pimpl = other.m_pimpl->clone();
                m_type_index = other.m_type_index;
            } else {
                m_pimpl.reset();
                m_type_index = std::type_index(typeid(void));
            }
        }

        return *this;
    }

    /// Moves the contents of another `::any` into this one.
    ///
    /// \param other The object to move from. Left in a valid but unspecified
    ///     state.
    /// \return A reference to this object.
    any& operator=(any&& other) noexcept = default;

    /// Destroys an `::any` and its held object, if one exists.
    ~any() = default;

    bool operator==(const any& other) const noexcept
    {
        if (has_value() != other.has_value()) {
            return false;
        }
        if (type() != other.type()) {
            return false;
        }
        if (!has_value() && !other.has_value()) {
            return true;
        }
        return m_pimpl->equals(*other.m_pimpl);
    }

    /// Checks whether this `::any` object is holding an object.
    ///
    /// \return Whether this object is empty.
    [[nodiscard]] bool has_value() const noexcept { return m_pimpl != nullptr; }

    /// Returns the type index of the object held by this `::any`.
    ///
    /// \return The type index of the held object.
    [[nodiscard]] std::type_index type() const noexcept { return m_type_index; }

private:
    /// An abstract base class which provides the polymorphic interface for type
    /// erasure.
    struct placeholder {
        placeholder() noexcept = default;
        placeholder(const placeholder& other) = default;
        placeholder(placeholder&& other) noexcept = default;
        placeholder& operator=(const placeholder& other) = default;
        placeholder& operator=(placeholder&& other) noexcept = default;
        virtual ~placeholder() = default;

        [[nodiscard]] virtual std::unique_ptr<placeholder> clone() const = 0;
        [[nodiscard]] virtual bool equals(const placeholder& other) const = 0;
    };

    /// A simple container for an object of type `T`.
    template <typename T>
    struct holder final : placeholder {
        /// Constructs a `::holder` containing an object of type `T`,
        /// constructed in place.
        ///
        /// \tparam Args The types of arguments to forward.
        /// \param args Arguments forwarded to the constructor of the held
        ///     object.
        template <typename... Args>
        explicit holder(Args&&... args)
            : data(std::forward<Args>(args)...)
        {
        }

        /// Copies a `::holder` if the held object is copy constructible.
        ///
        /// \return A copy of this object.
        /// \throw `std::logic_error` if the held object is not copy
        ///     constructible.
        [[nodiscard]] std::unique_ptr<placeholder> clone() const override
        {
            if constexpr (std::is_copy_constructible_v<T>) {
                return std::make_unique<holder<T>>(data);
            } else {
                throw std::logic_error(std::format(
                    "Type {} is not copy constructible", typeid(T).name()));
            }
        }

        [[nodiscard]] bool equals(const placeholder& other) const override
        {
            if constexpr (std::equality_comparable<T>) {
                return data == static_cast<const holder<T>&>(other).data;
            } else {
                throw std::logic_error(std::format(
                    "Type {} is not equality comparable", typeid(T).name()));
            }
        }

        T data;
    };

    std::unique_ptr<placeholder> m_pimpl;
    std::type_index m_type_index { std::type_index(typeid(void)) };

    /// Casts an `::any` to a reference of its held object.
    ///
    /// \tparam T The type of the held object.
    /// \param operand The object to cast from.
    /// \return A reference to the held object.
    template <typename T>
    friend T& any_cast(any& operand);

    /// Casts an `::any` to a constant reference of its held object.
    ///
    /// \tparam T The type of the held object.
    /// \param operand The object to cast from.
    /// \return A constant reference to the held object.
    template <typename T>
    friend const T& any_cast(const any& operand);
};

template <typename T>
T& any_cast(any& operand)
{
    if (operand.type() != std::type_index(typeid(T))) {
        throw std::bad_any_cast();
    }
    auto* holder = static_cast<any::holder<T>*>(operand.m_pimpl.get());
    return holder->data;
}

template <typename T>
const T& any_cast(const any& operand)
{
    if (operand.type() != std::type_index(typeid(T))) {
        throw std::bad_any_cast();
    }
    const auto* holder
        = static_cast<const any::holder<T>*>(operand.m_pimpl.get());
    return holder->data;
}

} // namespace eecs

#endif // !EECS_ANY_HPP
