/*******************************<GINKGO LICENSE>******************************
Copyright (c) 2017-2023, the Ginkgo authors
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

#ifndef GKO_REFERENCE_MATRIX_BATCH_STRUCT_HPP_
#define GKO_REFERENCE_MATRIX_BATCH_STRUCT_HPP_


#include "core/matrix/batch_struct.hpp"


#include <ginkgo/core/base/types.hpp>
#include <ginkgo/core/matrix/batch_dense.hpp>
#include <ginkgo/core/matrix/batch_ell.hpp>


#include "core/base/batch_struct.hpp"


namespace gko {
namespace kernels {
/**
 * @brief A namespace for shared functionality between omp and reference
 *  executors.
 */
namespace host {


/** @file batch_struct.hpp
 *
 * Helper functions to generate a batch struct from a batch LinOp.
 *
 * A specialization is needed for every format of every kind of linear algebra
 * object. These are intended to be called on the host.
 */


/**
 * Generates an immutable uniform batch struct from a batch of dense matrices.
 */
template <typename ValueType>
inline batch::matrix::dense::uniform_batch<const ValueType> get_batch_struct(
    const batch::matrix::Dense<ValueType>* const op)
{
    return {op->get_const_values(), op->get_num_batch_items(),
            static_cast<int32>(op->get_common_size()[1]),
            static_cast<int32>(op->get_common_size()[0]),
            static_cast<int32>(op->get_common_size()[1])};
}


/**
 * Generates a uniform batch struct from a batch of dense matrices.
 */
template <typename ValueType>
inline batch::matrix::dense::uniform_batch<ValueType> get_batch_struct(
    batch::matrix::Dense<ValueType>* const op)
{
    return {op->get_values(), op->get_num_batch_items(),
            static_cast<int32>(op->get_common_size()[1]),
            static_cast<int32>(op->get_common_size()[0]),
            static_cast<int32>(op->get_common_size()[1])};
}


/**
 * Generates an immutable uniform batch struct from a batch of ell matrices.
 */
template <typename ValueType, typename IndexType>
inline batch::matrix::ell::uniform_batch<const ValueType, const IndexType>
get_batch_struct(const batch::matrix::Ell<ValueType, IndexType>* const op)
{
    return {op->get_const_values(),
            op->get_const_col_idxs(),
            op->get_num_batch_items(),
            static_cast<IndexType>(op->get_common_size()[0]),
            static_cast<IndexType>(op->get_common_size()[0]),
            static_cast<IndexType>(op->get_common_size()[1]),
            static_cast<IndexType>(op->get_num_stored_elements_per_row())};
}


/**
 * Generates a uniform batch struct from a batch of ell matrices.
 */
template <typename ValueType, typename IndexType>
inline batch::matrix::ell::uniform_batch<ValueType, IndexType> get_batch_struct(
    batch::matrix::Ell<ValueType, IndexType>* const op)
{
    return {op->get_values(),
            op->get_col_idxs(),
            op->get_num_batch_items(),
            static_cast<IndexType>(op->get_common_size()[0]),
            static_cast<IndexType>(op->get_common_size()[0]),
            static_cast<IndexType>(op->get_common_size()[1]),
            static_cast<IndexType>(op->get_num_stored_elements_per_row())};
}


}  // namespace host
}  // namespace kernels
}  // namespace gko


#endif  // GKO_REFERENCE_MATRIX_BATCH_STRUCT_HPP_