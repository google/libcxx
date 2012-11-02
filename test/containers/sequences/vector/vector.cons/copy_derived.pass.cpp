//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <vector>

// vector(const vector& v);

#include <vector>
#include <cassert>
#include "../../../test_allocator.h"

template <class C, class D>
void
test(const D& x)
{
    unsigned s = x.size();
    C c(x);
    assert(c.__invariants());
    assert(c.size() == s);
    assert(c == x);
    assert(c.get_allocator() == x.get_allocator());
}

template<typename Allocator>
class DerivedVector : public std::vector<int, Allocator> {
  typedef std::vector<int, Allocator> base;
 public:
  DerivedVector(const int* first, const int* last, const Allocator& a)
      : base(first, last, a) {}
  DerivedVector(typename base::size_type n, const int& value, const Allocator& a)
      : base(n, value, a) {}
};

int main()
{
    {
        int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 1, 0};
        int* an = a + sizeof(a)/sizeof(a[0]);
        test<std::vector<int, test_allocator<int>>>(
            DerivedVector<test_allocator<int>>(a, an, test_allocator<int>(5)));
    }
    {
        DerivedVector<test_allocator<int>> v(3, 2, test_allocator<int>(5));
        std::vector<int, test_allocator<int> > v2 = v;
        assert(v2 == v);
        assert(v2.get_allocator() == v.get_allocator());
    }
#ifndef _LIBCPP_HAS_NO_ADVANCED_SFINAE
    {
        DerivedVector<other_allocator<int> > v(3, 2, other_allocator<int>(5));
        std::vector<int, other_allocator<int> > v2 = v;
        assert(v2 == v);
        assert(v2.get_allocator() == other_allocator<int>(-2));
    }
#endif  // _LIBCPP_HAS_NO_ADVANCED_SFINAE
}
