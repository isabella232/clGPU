/* Copyright (c) 2017-2018 Intel Corporation
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

__kernel void Caxpy_noincx(complex_t alpha, __global complex_t* x, __global complex_t* y, uint incy)
{
    uint gid = get_global_id(0);
    complex_t this_x = x[gid];
    complex_t this_y = y[gid * incy];
    this_y += cmul(alpha, this_x);
    y[gid * incy] = this_y;
}
