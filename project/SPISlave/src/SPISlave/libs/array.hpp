#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdlib.h>

namespace std
{
  using ::size_t;
  using ptrdiff_t = int;
  
  template<class OutputIt, class Size, class T>
  OutputIt fill_n(OutputIt first, Size count, const T& value)
  {
    for (Size i = 0; i < count; i++) {
      *first++ = value;
    }
    return first;
  }

  template<class InputIt1, class InputIt2>
  bool equal(InputIt1 first1, InputIt1 last1, 
	     InputIt2 first2)
  {
    for (; first1 != last1; ++first1, ++first2) {
      if (!(*first1 == *first2)) {
	return false;
      }
    }
    return true;
  }
  template<typename _Tp, std::size_t _Nm>
  struct __array_traits
  {
    typedef _Tp _Type[_Nm];

    static constexpr _Tp&
    _S_ref(const _Type& __t, std::size_t __n) noexcept
    { return const_cast<_Tp&>(__t[__n]); }

    static constexpr _Tp*
    _S_ptr(const _Type& __t) noexcept
    { return const_cast<_Tp*>(__t); }
  };

  template<typename _Tp>
  struct __array_traits<_Tp, 0>
  {
    struct _Type { };

    static constexpr _Tp&
    _S_ref(const _Type&, std::size_t) noexcept
    { return *static_cast<_Tp*>(nullptr); }

    static constexpr _Tp*
    _S_ptr(const _Type&) noexcept
    { return nullptr; }
  };

  template<typename _Tp, std::size_t _Nm>
  struct array
  {
    typedef _Tp                   value_type;
    typedef value_type*           pointer;
    typedef const value_type*                       const_pointer;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef value_type*                   iterator;
    typedef const value_type*           const_iterator;
    typedef std::size_t                           size_type;
    typedef std::ptrdiff_t                          difference_type;

    // Support for zero-sized arrays mandatory.
    typedef __array_traits<_Tp, _Nm> _AT_Type;
    typename _AT_Type::_Type                         _M_elems;

    // No explicit construct/copy/destroy for aggregate type.

    // DR 776.
    void
    fill(const value_type& __u)
    { std::fill_n(begin(), size(), __u); }

    // Iterators.
    iterator
    begin() noexcept
    { return iterator(data()); }

    const_iterator
    begin() const noexcept
    { return const_iterator(data()); }

    iterator
    end() noexcept
    { return iterator(data() + _Nm); }

    const_iterator
    end() const noexcept
    { return const_iterator(data() + _Nm); }

    const_iterator
    cbegin() const noexcept
    { return const_iterator(data()); }

    const_iterator
    cend() const noexcept
    { return const_iterator(data() + _Nm); }

    // Capacity.
    constexpr size_type 
    size() const noexcept { return _Nm; }

    constexpr size_type 
    max_size() const noexcept { return _Nm; }

    constexpr bool 
    empty() const noexcept { return size() == 0; }

    // Element access.
    reference
    operator[](size_type __n) noexcept
    { return _AT_Type::_S_ref(_M_elems, __n); }

    constexpr const_reference
    operator[](size_type __n) const noexcept
    { return _AT_Type::_S_ref(_M_elems, __n); }

    reference 
    front() noexcept
    { return *begin(); }

    constexpr const_reference 
    front() const noexcept
    { return _AT_Type::_S_ref(_M_elems, 0); }

    reference 
    back() noexcept
    { return _Nm ? *(end() - 1) : *end(); }

    constexpr const_reference 
    back() const noexcept
    { 
      return _Nm ? _AT_Type::_S_ref(_M_elems, _Nm - 1) 
	: _AT_Type::_S_ref(_M_elems, 0);
    }

    pointer
    data() noexcept
    { return _AT_Type::_S_ptr(_M_elems); }

    const_pointer
    data() const noexcept
    { return _AT_Type::_S_ptr(_M_elems); }
  };

  // Array comparisons.
  template<typename _Tp, std::size_t _Nm>
  inline bool 
  operator==(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
  { return std::equal(__one.begin(), __one.end(), __two.begin()); }

  template<typename _Tp, std::size_t _Nm>
  inline bool
  operator!=(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
  { return !(__one == __two); }


} // namespace std

#endif
