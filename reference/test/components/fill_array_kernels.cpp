/*******************************<GINKGO LICENSE>******************************
Copyright (c) 2017-2022, the Ginkgo authors
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************<GINKGO LICENSE>*******************************/

#include "core/components/fill_array_kernels.hpp"


#include <memory>
#include <random>
#include <vector>


#include <gtest/gtest.h>


#include <ginkgo/core/base/array.hpp>


#include "core/test/utils.hpp"


namespace {


template <typename T>
class FillArray : public ::testing::Test {
protected:
    using value_type = T;
    FillArray()
        : ref(gko::ReferenceExecutor::create()),
          total_size(6344),
          expected(ref, total_size),
          vals(ref, total_size),
          seqs(ref, total_size)
    {
        std::fill_n(expected.get_data(), total_size, T(6453));
        std::iota(seqs.get_data(), seqs.get_data() + total_size, 0);
    }

    std::shared_ptr<gko::ReferenceExecutor> ref;
    gko::size_type total_size;
    gko::array<value_type> expected;
    gko::array<value_type> vals;
    gko::array<value_type> seqs;
};

TYPED_TEST_SUITE(FillArray, gko::test::ValueAndIndexTypes,
                 TypenameNameGenerator);


TYPED_TEST(FillArray, EqualsReference)
{
    using T = typename TestFixture::value_type;
    gko::kernels::reference::components::fill_array(
        this->ref, this->vals.get_data(), this->total_size, T(6453));

    GKO_ASSERT_ARRAY_EQ(this->vals, this->expected);
}


TYPED_TEST(FillArray, FillSeqEqualsReference)
{
    using T = typename TestFixture::value_type;
    gko::kernels::reference::components::fill_seq_array(
        this->ref, this->vals.get_data(), this->total_size);

    GKO_ASSERT_ARRAY_EQ(this->vals, this->seqs);
}


}  // namespace
