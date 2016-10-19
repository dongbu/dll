//=======================================================================
// Copyright (c) 2014-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*
 * This is mostly a compilation test to ensure that Convolutional
 * RBMs are accepting enough input types
 */

#include <vector>
#include <list>
#include <deque>

#include "catch.hpp"
#include "template_test.hpp"

#include "dll/rbm/conv_rbm_mp.hpp"
#include "dll/rbm/conv_rbm.hpp"

#include "mnist/mnist_reader.hpp"
#include "mnist/mnist_utils.hpp"

namespace {

struct crbm_mp_double {
    using rbm_t = dll::conv_rbm_mp_desc<
            1, 28, 28, 10, 20, 20, 2,
            dll::weight_type<double>,
            dll::batch_size<25>>::layer_t;

    static void init(rbm_t&){}
};

struct crbm_mp_float {
    using rbm_t = dll::conv_rbm_mp_desc<
            1, 28, 28, 10, 20, 20, 2,
            dll::weight_type<float>,
            dll::batch_size<25>>::layer_t;

    static void init(rbm_t&){}
};

struct dyn_crbm_mp_float {
    using rbm_t = dll::dyn_conv_rbm_mp_desc<
            dll::weight_type<float>
            >::layer_t;

    static void init(rbm_t& rbm){
        rbm.init_layer(1, 28, 28, 10, 20, 20, 2);
        rbm.batch_size = 25;
    }
};

struct dyn_crbm_mp_double {
    using rbm_t = dll::dyn_conv_rbm_mp_desc<
            dll::weight_type<double>
            >::layer_t;

    static void init(rbm_t& rbm){
        rbm.init_layer(1, 28, 28, 10, 20, 20, 2);
        rbm.batch_size = 25;
    }
};

} // end of anonymous namespace

#define TYPES_TEST_PREFIX "crbm_mp"
#define TYPES_TEST_T1 crbm_mp_float
#define TYPES_TEST_T2 crbm_mp_double
#define TYPES_TEST_T3 dyn_crbm_mp_float
#define TYPES_TEST_T4 dyn_crbm_mp_double
#define TYPES_TEST_MP

#include "types_test.inl"
