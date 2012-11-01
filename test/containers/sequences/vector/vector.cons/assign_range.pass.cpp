//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <vector>

// vector& operator=(const vector& c);

#include <vector>
#include <cassert>
#include "../../../iterators.h"
#include "../../../stack_allocator.h"

namespace ns {
struct min_range {
  const int* first;
  const int* last;
};

input_iterator<const int*> begin(min_range r) { return input_iterator<const int*>{r.first}; }
input_iterator<const int*> end(min_range r) { return input_iterator<const int*>{r.last}; }
}

template <class C, class Range>
void
test(Range range)
{
    C c(range);
    C c2(3, 2);
    c2 = range;
    assert(c.__invariants());
    assert(c2 == c);
    C c3(3, 2);
    c3.assign(range);
    assert(c3 == c);
    C c4(3, 2);
    c4.assign(c3);
    assert(c4 == c);
}

int main()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 1, 0};
    int* an = a + sizeof(a)/sizeof(a[0]);
    test<std::vector<int> >(ns::min_range{a, an});
    test<std::vector<int, stack_allocator<int, 63> > >(ns::min_range{a, an});
}
