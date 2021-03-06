//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include "dll/base_traits.hpp"
#include "dll/transform/transform_layer.hpp"

namespace dll {

/*!
 * \brief Simple shape information layer
 */
template <typename Desc>
struct shape_1d_layer_impl : transform_layer<shape_1d_layer_impl<Desc>> {
    using desc      = Desc;                       ///< The descriptor type
    using weight    = typename desc::weight;      ///< The data type
    using this_type = shape_1d_layer_impl<desc>;       ///< The type of this layer
    using base_type = transform_layer<this_type>; ///< The base type

    static constexpr size_t Size = desc::S; ///< The input size
    static constexpr size_t D    = 1;       ///< The number of dimensions

    using input_one_t  = etl::fast_dyn_matrix<weight, Size>; ///< The preferred type of input
    using output_one_t = etl::fast_dyn_matrix<weight, Size>; ///< The type of output

    shape_1d_layer_impl() = default;

    /*!
     * \brief Returns a string representation of the layer
     */
    static std::string to_short_string() {
        return "Shape";
    }

    /*!
     * \brief Return the size of the input of this layer
     * \return The size of the input of this layer
     */
    static constexpr size_t input_size() {
        return Size;
    }

    /*!
     * \brief Return the size of the output of this layer
     * \return The size of the output of this layer
     */
    static constexpr size_t output_size() {
        return Size;
    }

    /*!
     * \brief Apply the layer to the batch of input
     * \param output The batch of output
     * \param input The batch of input to apply the layer to
     */
    template <typename Input, typename Output>
    static void forward_batch(Output& output, const Input& input) {
        output = input;
    }

    /*!
     * \brief Adapt the errors, called before backpropagation of the errors.
     *
     * This must be used by layers that have both an activation fnction and a non-linearity.
     *
     * \param context the training context
     */
    template<typename C>
    void adapt_errors(C& context) const {
        cpp_unused(context);
    }

    /*!
     * \brief Backpropagate the errors to the previous layers
     * \param output The ETL expression into which write the output
     * \param context The training context
     */
    template<typename H, typename C>
    void backward_batch(H&& output, C& context) const {
        cpp_unused(output);
        cpp_unused(context);
    }

    /*!
     * \brief Compute the gradients for this layer, if any
     * \param context The trainng context
     */
    template<typename C>
    void compute_gradients(C& context) const {
        cpp_unused(context);
    }
};

//Allow odr-use of the constexpr static members

template <typename Desc>
const size_t shape_1d_layer_impl<Desc>::Size;

// Declare the traits for the layer

template<typename Desc>
struct layer_base_traits<shape_1d_layer_impl<Desc>> {
    static constexpr bool is_neural     = false; ///< Indicates if the layer is a neural layer
    static constexpr bool is_dense      = false; ///< Indicates if the layer is dense
    static constexpr bool is_conv       = false; ///< Indicates if the layer is convolutional
    static constexpr bool is_deconv     = false; ///< Indicates if the layer is deconvolutional
    static constexpr bool is_standard   = false; ///< Indicates if the layer is standard
    static constexpr bool is_rbm        = false; ///< Indicates if the layer is RBM
    static constexpr bool is_pooling    = false; ///< Indicates if the layer is a pooling layer
    static constexpr bool is_unpooling  = false; ///< Indicates if the layer is an unpooling laye
    static constexpr bool is_transform  = true;  ///< Indicates if the layer is a transform layer
    static constexpr bool is_dynamic    = false; ///< Indicates if the layer is dynamic
    static constexpr bool pretrain_last = false; ///< Indicates if the layer is dynamic
    static constexpr bool sgd_supported = true;  ///< Indicates if the layer is supported by SGD
};

/*!
 * \brief Specialization of sgd_context for shape_layer
 */
template <typename DBN, typename Desc, size_t L>
struct sgd_context<DBN, shape_1d_layer_impl<Desc>, L> {
    using layer_t = shape_1d_layer_impl<Desc>;
    using weight  = typename DBN::weight; ///< The data type for this layer

    static constexpr auto batch_size = DBN::batch_size;

    etl::fast_matrix<weight, batch_size, layer_t::Size> input;
    etl::fast_matrix<weight, batch_size, layer_t::Size> output;
    etl::fast_matrix<weight, batch_size, layer_t::Size> errors;

    sgd_context(const shape_1d_layer_impl<Desc>& /* layer */){}
};

} //end of dll namespace
