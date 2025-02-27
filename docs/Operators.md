<a class="mk-toclify" id="table-of-contents"></a>

# Table of Contents
- [Memory Layout](#memory-layout)
- [Operators](#operators)
    - [Activation](#activation)
    - [AddN](#addn)
    - [ArgMin/ArgMax](#argminargmax)
    - [Batch2Space](#batch2space)
    - [BatchNorm](#batchnorm)
    - [Clip](#clip)
    - [Concat](#concat)
    - [Conv2d](#conv2d)
    - [DeConv2d](#deconv2d)
    - [DeConv1d](#deconv1d)
    - [DepthToSpace](#depthtospace)
    - [Dropout](#dropout)
    - [Add](#add)
    - [Sub](#sub)
    - [Multiply](#multiply)
    - [Div](#div)
    - [Pow](#pow)
    - [Minimum](#minimum)
    - [Maximum](#maximum)
    - [FloorDiv](#floordiv)
    - [FullyConnected](#fullyconnected)
    - [Gather](#gather)
    - [GatherNd](#gathernd)
    - [GroupedConv2d](#groupedconv2d)
    - [L2Normalization](#l2normalization)
    - [LocalResponseNormalization](#localresponsenormalization)
    - [And](#and)
    - [Or](#or)
    - [LogSoftmax](#logsoftmax)
    - [MaxpoolWithArgmax](#maxpoolwithargmax)
    - [MaxUnpool2d](#maxunpool2d)
    - [NBG](#nbg)
    - [Pad](#pad)
    - [Pool2d](#pool2d)
    - [ReduceMin](#reducemin)
    - [ReduceMax](#reducemax)
    - [ReduceAny](#reduceany)
    - [ReduceAll](#reduceall)
    - [ReduceProd](#reduceprod)
    - [ReduceMean](#reducemean)
    - [ReduceSum](#reducesum)
    - [Greater](#greater)
    - [GreaterOrEqual](#greaterorequal)
    - [Less](#less)
    - [LessOrEqual](#lessorequal)
    - [NotEqual](#notequal)
    - [Equal](#equal)
    - [Reorg](#reorg)
    - [Reshape](#reshape)
    - [Resize](#resize)
    - [Resize1d](#resize1d)
    - [Reverse](#reverse)
    - [ScatterND](#scatternd)
    - [Select](#select)
    - [DataConvert](#dataconvert)
    - [Neg](#neg)
    - [Abs](#abs)
    - [Sin](#sin)
    - [Exp](#exp)
    - [Log](#log)
    - [Sqrt](#sqrt)
    - [Rsqrt](#rsqrt)
    - [Square](#square)
    - [LogicalNot](#logicalnot)
    - [Floor](#floor)
    - [Cast](#cast)
    - [Slice](#slice)
    - [Softmax](#softmax)
    - [Space2Batch](#space2batch)
    - [SpaceToDepth](#spacetodepth)
    - [Split](#split)
    - [Squeeze](#squeeze)
    - [Stack](#stack)
    - [StridedSlice](#stridedslice)
    - [Tile](#tile)
    - [Transpose](#transpose)
    - [Unstack](#unstack)

<a class="mk-toclify" id="memory-layout"></a>
# Memory Layout

There are two different memory layout mode:

- Row-Major. Also called C contiguous, which is firstly introduced in C by AT&T Bell Lab(1960s). Caffe/TensorFlow/Pytorch follow the Row-Major layout mode.

- Column-Major. Also called Fortran contiguous, which is firstly introduced in Fortran by IBM(1958). Matlab/OpenGL/OpenCL/OpenVX follow the Column-Major layout mode.

See also :

http://eigen.tuxfamily.org/dox/group__TopicStorageOrders.html

On the other hand, a memory layout can be described by both Row-Major and Column-Major mode.

It easily tranlate the layout mode from one to another: just reverse the dimesions of the tensor.

For example, TensorFlow usually describe the tensor as NHWC format. This is equal the CWHN format in OpenVX.

Likewise, the WHCN format in OpenVX is equal the NCHW format in Caffe.

<a class="mk-toclify" id="operators"></a>
# Operators

<a class="mk-toclify" id="activation"></a>
## Activation

Activation functions:

```
Relu(x)                : max(0, x)

Relu1(x)               : -1 if x <= -1; x if -1 < x < 1; 1 if x >= 1

Relu6(x)               : 0 if x <= 0; x if 0 < x < 6; 6 if x >= 6

Elu(x)                 : x if x >= 0 else alpha*(e^x - 1)

Tanh(x)                : (1 - e^{-2x})/(1 + e^{-2x})

Sigmoid(x)             : 1/(1 + e^{-x})

HardSwish(x)           : 0 if x <= -3; x(x + 3)/6 if -3 < x < 3; x if x >= 3

Mish(x)                : x if x >= 0 else alpha * x

HardSigmoid(x)         : min(max(alpha*x + beta, 0), 1)

SoftRelu(x)            : log(1 + e^x). Also known as SoftPlus.

LeakyRelu(x)           : alpha * x if x <= 0; x if x > 0. alpha is a scalar.

Prelu(x)               : alpha * x if x <= 0; x if x > 0. alpha is a tensor.
- axis                : describes the axis of the inputs when coerced to 2D.

Linear(x, a, b)        : a*x + b.
```

<a class="mk-toclify" id="addn"></a>
## AddN

```
AddN(x)                : Input0 + Input1 + ... + InputN
```

<a class="mk-toclify" id="argminargmax"></a>
## ArgMin/ArgMax

Computes the indices of the **min/max** elements of the input tensor's element
along the provided **axis**. The type of the output tensor is integer.

<a class="mk-toclify" id="batch2space"></a>
## Batch2Space

This operation reshapes the batch dimension (dimension 0) into M + 1 dimensions
of shape **block_size** + [batch], interleaves these blocks back into the grid
defined by the spatial dimensions [1, ..., M], to obtain a result with the same
rank as the input. This is the reverse transformation of Space2Batch.

- crop : corp the output tensor for ROI usage.

<a class="mk-toclify" id="batchnorm"></a>
## BatchNorm

Carries out batch normalization as described in the paper
https://arxiv.org/abs/1502.03167.

$$\hat x_i\leftarrow \frac{x_i-\mu_\mathcal{B}}{\sqrt{\sigma_\mathcal{B}^2+\epsilon}}$$

$$y_i=\gamma\hat x_i+\beta\equiv BN_{\gamma,\beta}(x_i)$$

<a class="mk-toclify" id="clip"></a>
## Clip

Clip(x) : min if x <= min; x if min < x < max; max if x >= max

<a class="mk-toclify" id="concat"></a>
## Concat

Concatenate a list of tensors into a single tensor.

- axis : Which axis to concat on.

<a class="mk-toclify" id="conv2d"></a>
## Conv2d

Performs a 2-D convolution operation, include classic Conv2D /
Depthwise Conv2D / Group Conv2D / Dilation Conv2D.

Input:
- input [WHCN or CWHN].
- kernel [ WHIcOc ] (Ic: Input Channels. Oc: Output Channels).
- bias [ O ]. Optional.

Attribute:
- weights : the output channel number for weight tensor.
- ksize : the height and width for weight tensor.
- padding : AUTO, VALID or SAME.
- pad : pad value for each spatial axis.
- stride : stride along each spatial axis.
- dilation : dilation value along each spatial axis of the filter.
- multiplier: function similar to group attribute on other framework,
but the value is different. multiplier = weights / group.
- layout : WHCN or CWHN.

<a class="mk-toclify" id="deconv2d"></a>
## DeConv2d

Performs the transpose of 2-D convolution operation.

This operation is sometimes called "deconvolution" after Deconvolutional Networks,
but is actually the transpose (gradient) of Conv2D rather than an actual deconvolution.

- oc_count_ : the out channel count for weight tensor.
- pad_type : SAME, VALID or AUTO.
- ksize : the height and width for weight tensor.
- padding : AUTO, VALID or SAME.
- pad : pad value for each spatial axis.
- stride : stride along each spatial axis.
- output_padding : specifying the amount of padding along the height and width of
the output tensor.
- group : the feature count of each group.
- input_layout : Layout for input, WHCN by default.
- kernel_layout: Layout for kernel, WHIO by default.

<a class="mk-toclify" id="deconv1d"></a>
## DeConv1d

Performs the transpose of 1-D convolution operation.

This operation is sometimes called "deconvolution1d" after Deconvolutional Networks,
but is actually the transpose (gradient) of Conv2D rather than an actual deconvolution.

- weights : the channel number for weight tensor.
- ksize : the length for weight tensor.
- padding : AUTO, VALID or SAME.
- pad : pad value for each spatial axis.
- stride : stride along each spatial axis.
- output_padding : specifying the amount of padding along the height and width of
the output tensor.

<a class="mk-toclify" id="depthtospace"></a>
## DepthToSpace

DepthToSpace rearranges (permutes) data from depth into blocks of spatial data.
This is the reverse transformation of SpaceToDepth.

Chunks of data of size block_size * block_size from depth are rearranged into
non-overlapping blocks of size block_size x block_size.

The width of the output tensor is input_depth * block_size, whereas the height
is input_height * block_size. The depth of the input tensor must be divisible
by block_size * block_size

- crop : corp the output tensor for ROI usage.

<a class="mk-toclify" id="dropout"></a>
## Dropout

The Dropout layer randomly sets input units to 0 with a frequency of rate at
each step during training time, which helps prevent overfitting.

TIM-VX only focus on inference time, and just scaling input tensor by **ratio**
for Dropout operator.

<a class="mk-toclify" id="add"></a>
## Add

Add(x, y) : x + y. This operation supports broadcasting.

<a class="mk-toclify" id="sub"></a>
## Sub

Sub(x, y) : x - y. This operation supports broadcasting.

<a class="mk-toclify" id="multiply"></a>
## Multiply

Multiply(x, y) : Multiplies two tensors, element-wise, also known as Hadamard
product. This operation supports broadcasting.

- scale: scaling the product.

<a class="mk-toclify" id="div"></a>
## Div

Div(x, y) : x / y. This operation supports broadcasting.

<a class="mk-toclify" id="pow"></a>
## Pow

Pow(x, y) : x ^ y. This operation supports broadcasting.

<a class="mk-toclify" id="minimum"></a>
## Minimum

Minimum(x, y) : min(x, y). This operation supports broadcasting.

<a class="mk-toclify" id="maximum"></a>
## Maximum

Maximum(x, y) : max(x, y). This operation supports broadcasting.

<a class="mk-toclify" id="floordiv"></a>
## FloorDiv

FloorDiv(x, y): floor( x / y ). This operation supports broadcasting.

<a class="mk-toclify" id="fullyconnected"></a>
## FullyConnected

Denotes a fully (densely) connected layer, which connects all elements in the
input tensor with each element in the output tensor. 

- axis: Describes the axis of the inputs when coerced to 2D.
- weights: the output channel number for weight tensor.

<a class="mk-toclify" id="gather"></a>
## Gather

Gather slices from input, **axis** according to **indices**.

<a class="mk-toclify" id="gathernd"></a>
## GatherNd

An operation similar to Gather but gathers across multiple axis at once.

<a class="mk-toclify" id="groupedconv2d"></a>
## GroupedConv2d

Performs a grouped 2-D convolution operation.

Input:
- input [WHCN or CWHN].
- kernel [ WHIcOc ] (Ic: Input Channels. Oc: Output Channels).
- bias [ O ]. Optional.

Attribute:
- weights : the output channel number for weight tensor.
- ksize : the height and width for weight tensor.
- padding : AUTO, VALID or SAME.
- pad : pad value for each spatial axis.
- stride : stride along each spatial axis.
- dilation : dilation value along each spatial axis of the filter.
- group_number: Split conv to n group.
- layout : WHCN or CWHN.

<a class="mk-toclify" id="l2normalization"></a>
## L2Normalization

Applies L2 normalization along the axis dimension:

```
output[batch, row, col, channel] =
input[batch, row, col, channel] /
sqrt(sum_{c} pow(input[batch, row, col, c], 2))
```

<a class="mk-toclify" id="localresponsenormalization"></a>
## LocalResponseNormalization

Applies Local Response Normalization along the depth dimension:

```
sqr_sum[a, b, c, d] = sum(
pow(input[a, b, c, d - depth_radius : d + depth_radius + 1], 2))
output = input / pow((bias + alpha * sqr_sum), beta)
```

<a class="mk-toclify" id="and"></a>
## And

Returns the truth value of x AND y element-wise. This operation supports broadcasting.

<a class="mk-toclify" id="or"></a>
## Or

Returns the truth value of x OR y element-wise. This operation supports broadcasting.

<a class="mk-toclify" id="logsoftmax"></a>
## LogSoftmax

Computes the log softmax activation on the input tensor element-wise, per batch.

```
logsoftmax = logits - log(reduce_sum(exp(logits), axis))
```

<a class="mk-toclify" id="maxpoolwithargmax"></a>
## MaxpoolWithArgmax

Performs an 2-D Max pooling operation and return indices

- padding : AUTO, VALID or SAME.
- ksize : filter size.
- stride : stride along each spatial axis.
- round_type : CEILING or FLOOR.

<a class="mk-toclify" id="maxunpool2d"></a>
## MaxUnpool2d

Performs an 2-D Max pooling operation upsample 

- stride : stride along each spatial axis.
- ksize : filter size.

<a class="mk-toclify" id="nbg"></a>
## NBG

Network Binary Graph is a precompile technology, which can compile a fuse graph into
a bianry file.

<a class="mk-toclify" id="pad"></a>
## Pad

Pads a tensor.

- const_val : the value to pad.

<a class="mk-toclify" id="pool2d"></a>
## Pool2d

Performs an 2-D pooling operation.

- type : MAX, AVG, L2 or AVG_ANDROID.
- padding : AUTO, VALID or SAME.
- ksize : filter size.
- stride : stride along each spatial axis.
- round_type : CEILING or FLOOR.

<a class="mk-toclify" id="reducemin"></a>
## ReduceMin

Reduces a tensor by computing the minimum of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="reducemax"></a>
## ReduceMax

Reduces a tensor by computing the maximum of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="reduceany"></a>
## ReduceAny

Reduces a tensor by computing the "logical or" of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="reduceall"></a>
## ReduceAll

Reduces a tensor by computing the "logical and" of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="reduceprod"></a>
## ReduceProd

Reduces a tensor by computing the multiplying of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="reducemean"></a>
## ReduceMean

Reduces a tensor by computing the mean of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="reducesum"></a>
## ReduceSum

Reduces a tensor by computing the summing of elements along given dimensions.

- axis : the dimensions to reduce.
- keep_dims : If keep_dims is true, the reduced dimensions are retained with
length 1. Otherwise, the rank of the tensor is reduced by 1 for each entry
in dimensions

<a class="mk-toclify" id="greater"></a>
## Greater

For input tensors x and y, computes x > y elementwise.

<a class="mk-toclify" id="greaterorequal"></a>
## GreaterOrEqual

For input tensors x and y, computes x >= y elementwise.

<a class="mk-toclify" id="less"></a>
## Less

For input tensors x and y, computes x < y elementwise.

<a class="mk-toclify" id="lessorequal"></a>
## LessOrEqual

For input tensors x and y, computes x <= y elementwise.

<a class="mk-toclify" id="notequal"></a>
## NotEqual

For input tensors x and y, computes x != y elementwise.

<a class="mk-toclify" id="equal"></a>
## Equal

For input tensors x and y, computes x == y elementwise.

<a class="mk-toclify" id="reorg"></a>
## Reorg

The layer used in YOLOv2. See also https://github.com/pjreddie/darknet/blob/master/src/reorg_layer.c

<a class="mk-toclify" id="reshape"></a>
## Reshape

Given tensor, this operation returns a tensor that has the same values as tensor, but with a newly specified shape.

- size : defining the shape of the output tensor.

<a class="mk-toclify" id="resize"></a>
## Resize

Resizes images to given size.

- type : NEAREST_NEIGHBOR, BILINEAR or AREA.
- factor : scale the input size. DO NOT use it with target_height / target_width together.
- align_corners : If True, the centers of the 4 corner pixels of the input and output
tensors are aligned, preserving the values at the corner pixels.
- half_pixel_centers : If True, the pixel centers are assumed to be at (0.5, 0.5).
This is the default behavior of image.resize in TF 2.0. If this parameter is True,
then align_corners parameter must be False.
- target_height / target_width : output height / width. DO NOT use it with factor together.

<a class="mk-toclify" id="resize1d"></a>
## Resize1d

Resize1ds 1D tensors to given size.

- type : NEAREST_NEIGHBOR, BILINEAR or AREA.
- factor : scale the input size. DO NOT use it with target_height / target_width together.
- align_corners : If True, the centers of the 4 corner pixels of the input and output
tensors are aligned, preserving the values at the corner pixels.
- half_pixel_centers : If True, the pixel centers are assumed to be at (0.5, 0.5).
This is the default behavior of image.resize in TF 2.0. If this parameter is True,
then align_corners parameter must be False.
- target_height / target_width : output height / width. DO NOT use it with factor together.

<a class="mk-toclify" id="reverse"></a>
## Reverse

Reverses specific dimensions of a tensor.

- axis : The indices of the dimensions to reverse. 

<a class="mk-toclify" id="scatternd"></a>
## ScatterND

Scatter updates into a new tensor according to indices.

- shape : The shape of the resulting tensor. 

<a class="mk-toclify" id="select"></a>
## Select

Using a tensor of booleans c and input tensors x and y select values elementwise
from both input tensors: O[i] = C[i] ? x[i] : y[i].

<a class="mk-toclify" id="dataconvert"></a>
## DataConvert

Change the format from input tensor to output tensor.

<a class="mk-toclify" id="neg"></a>
## Neg

Neg(x) : -x

<a class="mk-toclify" id="abs"></a>
## Abs

Abs(x) : x if x >= 0; -x if x < 0.

<a class="mk-toclify" id="sin"></a>
## Sin

Sin(x) : sin(x)

<a class="mk-toclify" id="exp"></a>
## Exp

Exp(x) : e^x

<a class="mk-toclify" id="log"></a>
## Log

Log(x) : ln(x)

<a class="mk-toclify" id="sqrt"></a>
## Sqrt

Sqrt(x) : $$\sqrt{x}$$

<a class="mk-toclify" id="rsqrt"></a>
## Rsqrt

Rsqrt(x) : $$\frac{1}{\sqrt{x}}$$

<a class="mk-toclify" id="square"></a>
## Square

Square : x^2

<a class="mk-toclify" id="logicalnot"></a>
## LogicalNot

LogicalNot(x) : NOT x

<a class="mk-toclify" id="floor"></a>
## Floor

returns the largest integer less than or equal to a given number.

<a class="mk-toclify" id="cast"></a>
## Cast

Change the format from input tensor to output tensor. This operation ignores
the scale and zeroPoint of quanized tensors.

<a class="mk-toclify" id="slice"></a>
## Slice

Extracts a slice of specified size from the input tensor starting at a specified location.

- start : the beginning indices of the slice in each dimension.
- length : the size of the slice in each dimension.

<a class="mk-toclify" id="softmax"></a>
## Softmax

Computes the softmax activation on the input tensor element-wise, per batch,
by normalizing the input vector so the maximum coefficient is zero:

```
output[batch, i] =
exp((input[batch, i] - max(input[batch, :])) * beta) /
sum_{k}{exp((input[batch, k] - max(input[batch, :])) * beta)}
```

<a class="mk-toclify" id="space2batch"></a>
## Space2Batch

This operation divides "spatial" dimensions [1, ..., M] of the input into a grid
of blocks of shape **block_size**, and interleaves these blocks with the "batch"
dimension (0) such that in the output, the spatial dimensions [1, ..., M] correspond
to the position within the grid, and the batch dimension combines both the position
within a spatial block and the original batch position. Prior to division into blocks,
the spatial dimensions of the input are optionally zero padded according to paddings.
This is the reverse transformation of Batch2Space.

- pad : the paddings for each spatial dimension of the input tensor.

<a class="mk-toclify" id="spacetodepth"></a>
## SpaceToDepth

SpaceToDepth rearranges blocks of spatial data into depth. More specifically,
this op outputs a copy of the input tensor where values from the height and
width dimensions are moved to the depth dimension. This is the reverse
transformation of DepthToSpace.

<a class="mk-toclify" id="split"></a>
## Split

Splits a tensor along a given axis into num_splits subtensors.

- axis : the axis along which to split.
- slices : indicating the number of splits along given axis.

<a class="mk-toclify" id="squeeze"></a>
## Squeeze

Removes dimensions of size 1 from the shape of a tensor. 

- axis : the dimensions to squeeze.

<a class="mk-toclify" id="stack"></a>
## Stack

Packs the list of tensors in inputs into a tensor with rank one higher than
each tensor in values, by packing them along the **axis** dimension. 

<a class="mk-toclify" id="stridedslice"></a>
## StridedSlice

Extracts a strided slice of a tensor.

Roughly speaking, this op extracts a slice of size (end - begin) / stride from
the given input tensor. Starting at the location specified by begin the slice
continues by adding stride to the index until all dimensions are not less than end.
Note that a stride can be negative, which causes a reverse slice.

- begin_dims : the starts of the dimensions of the input tensor to be sliced.
- end_dims : the ends of the dimensions of the input tensor to be sliced.
- stride_dims : the strides of the dimensions of the input tensor to be sliced.
- begin_mask :  if the ith bit of begin_mask is set, begin[i] is ignored and
the fullest possible range in that dimension is used instead.
- end_mask : if the ith bit of end_mask is set, end[i] is ignored and the fullest
possible range in that dimension is used instead.
- shrink_axis_mask : if the ith bit of shrink_axis_mask is set, the ith dimension
specification shrinks the dimensionality by 1, taking on the value at index begin[i].
In this case, the ith specification must define a slice of size 1,
e.g. begin[i] = x, end[i] = x + 1.

<a class="mk-toclify" id="tile"></a>
## Tile

Constructs a tensor by tiling a given tensor.
- multiples :  Must be one of the following types: int32, int64.
Length must be the same as the number of dimensions in input.

<a class="mk-toclify" id="transpose"></a>
## Transpose

Transposes the input tensor, permuting the dimensions according to the
**perm** tensor.

The returned tensor's dimension i corresponds to the input dimension perm[i].
If perm is not given, it is set to (n-1...0), where n is the rank of the input
tensor. Hence by default, this operation performs a regular matrix transpose on
2-D input Tensors.

<a class="mk-toclify" id="unstack"></a>
## Unstack

Unpacks the given dimension of a rank-R tensor into rank-(R-1) tensors.
- axis : An int. The axis to unstack along. Defaults to the first dimension.
Negative values wrap around, so the valid range is [-R, R).