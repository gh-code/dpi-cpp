//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_DPI_HPP
#define GH_SYSTEMVERIOLG_DPI_HPP

#include <tuple>
#include <cstddef>
#include <svdpi.h>

namespace gh {

template<typename T, T... Ints>
struct integer_sequence
{
    typedef T value_type;
    static constexpr std::size_t size() { return sizeof...(Ints); }
};

template<std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

template<typename T, std::size_t N, T... Is>
struct make_integer_sequence : make_integer_sequence<T, N-1, N-1, Is...> {};

template<typename T, T... Is>
struct make_integer_sequence<T, 0, Is...> : integer_sequence<T, Is...> {};

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

namespace systemverilog {

namespace detail {

template<class... IT>
class dimension_base
{
public:
    dimension_base(svOpenArrayHandle h, IT... is)
    : m_h(h), m_indices(std::make_tuple<IT...>(std::move(is)...))
    { }

    int
    left() const noexcept
    { return m_h ? svLeft(m_h, sizeof...(IT) + 1) : 0; }

    int
    right() const noexcept
    { return m_h ? svRight(m_h, sizeof...(IT) + 1) : 0; }

    int
    low() const noexcept
    { return m_h ? svLow(m_h, sizeof...(IT) + 1) : 0; }

    int
    high() const noexcept
    { return m_h ? svHigh(m_h, sizeof...(IT) + 1) : 0; }

    int
    increment() const noexcept
    { return m_h ? svIncrement(m_h, sizeof...(IT) + 1) : 0; }

    int
    size() const noexcept
    { return m_h ? svSize(m_h, sizeof...(IT) + 1) : 0; }

protected:
    svOpenArrayHandle m_h;
    std::tuple<IT...> m_indices;
};

template<class T,std::size_t N,class... IT>
class dimension : public dimension_base<IT...>
{
public:
    explicit dimension(svOpenArrayHandle h, IT... is)
    : dimension_base<IT...>(h, is...)
    { }

    const dimension<T,N-1,IT...,int>
    operator[](int i) const noexcept
    { return get(i, make_index_sequence<sizeof...(IT)>()); }

    dimension<T,N-1,IT...,int>
    operator[](int i) noexcept
    { return get(i, make_index_sequence<sizeof...(IT)>()); }

    const dimension<T,N-1,IT...,int>
    at(int i) const
    {
        if (i < this->low() || i > this->high())
            throw std::string("dimension ") + std::to_string(sizeof...(IT) + 1) + ": out-of-bound";
        return (*this)[i];
    }

    dimension<T,N-1,IT...,int>
    at(int i)
    { return static_cast<const dimension&>(*this).at(i); }

private:
    template<std::size_t... I>
    dimension<T,N-1,IT...,int>
    get(int i, index_sequence<I...>) const
    { return dimension<T,N-1,IT...,int>(this->m_h, std::get<I>(this->m_indices)..., i); }
};

template<class T,class... IT>
class dimension<T,1,IT...> : public dimension_base<IT...>
{
public:
    typedef typename T::value_type  value_type;
    typedef value_type*             pointer;
    typedef const value_type*       const_pointer;
    typedef value_type&             reference;
    typedef const value_type&       const_reference;

    explicit dimension(svOpenArrayHandle h, IT... is)
    : dimension_base<IT...>(h, is...)
    { }

    const_reference
    operator[](int i) const noexcept
    { return get(i, make_index_sequence<sizeof...(IT)>()); }

    reference
    operator[](int i) noexcept
    { return get(i, make_index_sequence<sizeof...(IT)>()); }

    const_reference
    at(int i) const
    { return const_cast<dimension&>(*this).at(i); }

    reference
    at(int i)
    {
        if (i < this->low() || i > this->high())
            throw std::string("dimension ") + std::to_string(sizeof...(IT) + 1) + ": out-of-bound";
        return (*this)[i];
    }

private:
    template<std::size_t... I>
    reference
    get(int i, index_sequence<I...>) const
    {
        return get_ref(svGetArrElemPtr(this->m_h,
            std::get<I>(this->m_indices)...,
            i));
    }

    template<std::size_t I,std::size_t I2>
    reference
    get(int i, index_sequence<I,I2>) const
    {
        return get_ref(svGetArrElemPtr3(this->m_h,
            std::get<I>(this->m_indices),
            std::get<I2>(this->m_indices),
            i));
    }

    template<std::size_t I>
    reference
    get(int i, index_sequence<I>) const
    {
        return get_ref(svGetArrElemPtr2(this->m_h,
            std::get<I>(this->m_indices),
            i));
    }

    reference
    get(int i, index_sequence<>) const
    { return get_ref(svGetArrElemPtr1(this->m_h, i)); }

    reference get_ref(void* p) const
    { return p ? *static_cast<pointer>(p) : dimension::oob; }

private:
    static value_type oob;
};

template<class T,class... IT>
typename T::value_type
dimension<T,1,IT...>::oob = 0xdeadbeef;

} // namespace detail

template<class...>
using void_t = void;

template<class T,class=void>
struct is_sv_type : std::false_type {};

template<class T>
struct is_sv_type<T,void_t<
    typename T::value_type
> > : std::true_type {};

template<class T,std::size_t D>
class openarray_base
{
public:
    static_assert(is_sv_type<T>::value, "T requirement not met");

    typedef typename T::value_type  value_type;
    typedef value_type*             pointer;
    typedef const value_type*       const_pointer;
    typedef value_type&             reference;
    typedef const value_type&       const_reference;

    explicit openarray_base(svOpenArrayHandle h)
    {
        if (svDimensions(h) == D) {
            m_h = h;
        } else {
            m_h = nullptr;
            throw std::string("dimension not met");
        }
    }

    pointer
    data() noexcept
    { return m_h ? static_cast<pointer>(svGetArrayPtr(m_h))
                 : nullptr; }

    const_pointer
    data() const noexcept
    { return m_h ? static_cast<const_pointer>(svGetArrayPtr(m_h))
                 : nullptr; }

    int
    type_left() const noexcept
    { return m_h ? svLeft(m_h, 0) : 0; }

    int
    type_right() const noexcept
    { return m_h ? svRight(m_h, 0) : 0; }

    int
    dimensions() const noexcept
    { return D; }

protected:
    svOpenArrayHandle m_h;
};

template<class T,std::size_t D,int I=1>
class openarray_query : public openarray_base<T,D>
{
public:
    openarray_query(svOpenArrayHandle h)
    : openarray_base<T,D>(h)
    { }

    int
    left() const noexcept
    { return this->m_h ? svLeft(this->m_h, I) : 0; }

    int
    right() const noexcept
    { return this->m_h ? svRight(this->m_h, I) : 0; }

    int
    low() const noexcept
    { return this->m_h ? svLow(this->m_h, I) : 0; }

    int
    high() const noexcept
    { return this->m_h ? svHigh(this->m_h, I) : 0; }

    int
    increment() const noexcept
    { return this->m_h ? svIncrement(this->m_h, I) : 0; }

    int
    size() const noexcept
    { return this->m_h ? svSize(this->m_h, I) : 0; }
};

template<class T,std::size_t D>
class openarray : public openarray_query<T,D>
{
public:
    static_assert(is_sv_type<T>::value, "T requirement not met");

    typedef typename T::value_type value_type;

    explicit openarray(svOpenArrayHandle h)
    : openarray_query<T,D>(h)
    { }

    const detail::dimension<T,D-1,int>
    operator[](int i) const noexcept
    { return detail::dimension<T,D-1,int>{this->m_h, i}; }

    detail::dimension<T,D-1,int>
    operator[](int i) noexcept
    { return detail::dimension<T,D-1,int>{this->m_h, i}; }

    const detail::dimension<T,D-1,int>
    at(int i) const
    {
        if (i < this->low() || i > this->high())
            throw std::string("dimension 1: out-of-bound");
        return this->operator[](i);
    }

    detail::dimension<T,D-1,int>
    at(int i)
    { return static_cast<const openarray&>(*this).at(i); }

    using openarray_query<T,D>::left;
    using openarray_query<T,D>::right;
    using openarray_query<T,D>::low;
    using openarray_query<T,D>::high;
    using openarray_query<T,D>::size;
    using openarray_query<T,D>::increment;

    int
    left(int d) const
    { return this->check(d) ? svLeft(this->m_h, d) : 0; }

    int
    right(int d) const
    { return this->check(d) ? svRight(this->m_h, d) : 0; }

    int
    low(int d) const
    { return this->check(d) ? svLow(this->m_h, d) : 0; }

    int
    high(int d) const
    { return this->check(d) ? svHigh(this->m_h, d) : 0; }

    int
    increment(int d) const
    { return this->check(d) ? svIncrement(this->m_h, d) : 0; }

    int
    size(int d) const
    { return this->check(d) ? svSize(this->m_h, d) : 0; }

    bool check(int d) const
    {
        if (!this->m_h)
            return false;
        if (d < 0 || d >= static_cast<int>(D))
        {
            throw std::string("dimension out-of-bound");
            return false;
        }
        return true;
    }
};

template<class T>
class openarray<T,1> : public openarray_base<T,1>, public detail::dimension<T,1>
{
public:
    explicit openarray(svOpenArrayHandle h)
    : openarray_base<T,1>(h), detail::dimension<T,1>(h)
    { }
};

template<class T>
class openarray<T,0> : public openarray_query<T,0,0>
{
public:
    static_assert(is_sv_type<T>::value, "T requirement not met");

    typedef typename T::value_type value_type;

    explicit openarray(svOpenArrayHandle h)
    : openarray_query<T,0,0>(h)
    { }

    value_type
    operator[](int i) const noexcept
    { return i; }

    value_type
    at(int i) const
    { return const_cast<openarray&>(*this).at(i); }

    value_type
    at(int i)
    {
        if (i < this->low() || i > this->high())
            throw std::string("dimension 0: out-of-bound");
        return (*this)[i];
    }
};

struct byte_t      { using value_type = char; };
struct shortint_t  { using value_type = short int; };
struct int_t       { using value_type = int; };
struct longint_t   { using value_type = long long; };
struct real_t      { using value_type = double; };
struct shortreal_t { using value_type = float; };
struct chandle_t   { using value_type = void*; };
struct string_t    { using value_type = const char*; };
struct bit_t       { using value_type = unsigned char; };
struct logic_t     { using value_type = unsigned char; };
struct reg_t       { using value_type = unsigned char; };

} // namespace sv
} // namespace gh

#endif // GH_SYSTEMVERIOLG_DPI_HPP