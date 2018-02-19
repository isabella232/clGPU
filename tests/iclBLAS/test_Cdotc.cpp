// Copyright (c) 2017-2018 Intel Corporation
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>
#include <iclBLAS.h>
#include <complex>

#define EXPECT_OCLCOMPLEX_EQ(expected, result) \
    EXPECT_FLOAT_EQ(expected.val[0], result.val[0]); \
    EXPECT_FLOAT_EQ(expected.val[1], result.val[1])

TEST(Cdotc, 11_noinc) {
    const int n = 11;
    const int incx = 1;
    const int incy = 1;

    oclComplex_t x[n*incx] = { {1.f, 1.f}, {2.f, 2.f}, {3.f, 3.f}, {4.f, 4.f},
    {5.f, 5.f}, {6.f, 6.f}, {7.f, 7.f}, {8.f, 8.f}, {9.f, 9.f}, {10.f, 10.f}, {11.f, 11.f} };
    oclComplex_t y[n*incy] = { { 11.f, 11.f }, { 10.f, 10.f }, { 9.f, 9.f }, { 8.f, 8.f },
    { 7.f, 7.f }, { 6.f, 6.f }, { 5.f, 5.f }, { 4.f, 4.f }, { 3.f, 3.f }, { 2.f, 2.f }, { 1.f, 1.f } };
    oclComplex_t result = { -3.f, -3.f };
    oclComplex_t expected = { 572.f, 0.f };

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, x, incx, y, incy, &result);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_OCLCOMPLEX_EQ(expected, result);
}

TEST(Cdotc, 5_2inc) {
    const int n = 5;
    const int incx = 2;
    const int incy = 2;

    oclComplex_t x[n*incx] = { { -1.f, 1.f }, { -2.f, 2.f }, { -3.f, 3.f }, { -4.f, 4.f },
    { -5.f, 5.f }, { -6.f, 6.f }, { -7.f, 7.f }, { -8.f, 8.f }, { -9.f, 9.f }, { -10.f, 10.f } };
    oclComplex_t y[n*incy] = { { 10.f, 10.f }, { 9.f, 9.f }, { 8.f, 8.f }, { 7.f, 7.f },
    { 6.f, 6.f }, { 5.f, 5.f }, { 4.f, 4.f }, { 3.f, 3.f }, { 2.f, 2.f }, { 1.f, 1.f } };
    oclComplex_t result = { -3.f, -3.f };
    oclComplex_t expected = { 0.f, -220.f };

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, x, incx, y, incy, &result);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_OCLCOMPLEX_EQ(expected, result);
}

TEST(Cdotc, 5_3incx) {
    const int n = 5;
    const int incx = 3;
    const int incy = 1;

    oclComplex_t x[n*incx] = { { -1.f, 0.f },{ -2.f, 0.f },{ -3.f, 0.f },{ -4.f, 0.f },
    { -5.f, 0.f },{ -6.f, 0.f },{ -7.f, 0.f },{ -8.f, 0.f },{ -9.f, 0.f },{ -10.f, 0.f },
    { -11.f, 0.f }, { -12.f, 0.f }, { -13.f, 0.f}, { -14.f, 0.f}, { -15.f, 0.f } };
    oclComplex_t y[n*incy] = { { 5.f, 5.f }, { 4.f, 4.f }, { 3.f, 3.f }, { 2.f, 2.f }, { 1.f, 1.f } };
    oclComplex_t result = { -3.f, -3.f };
    oclComplex_t expected = { -75.f, -75.f };

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, x, incx, y, incy, &result);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_OCLCOMPLEX_EQ(expected, result);
}

TEST(Cdotc, 16_inc2) {
    const int n = 16;
    const int incx = 2;
    const int incy = 2;

    std::vector<std::complex<float>> x(n*incx);
    for (int i = 0; i < n; i++) {
        x[i*incx] = { i % 16 * 1.f, i % 32 * 1.f };
    }
    std::vector<std::complex<float>> y(n*incy);
    for (int i = 0; i < n; i++) {
        y[i*incy] = { 32.f - i % 32, 16.f - i % 16 };
    }
    std::complex<float> result(-1.f, -2.f);
    std::complex<float> expected;
    for (int i = 0; i < n; i++) {
        expected += std::conj(x[i*incx]) * y[i*incy];
    }

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, reinterpret_cast<oclComplex_t*>(x.data()), incx,
        reinterpret_cast<oclComplex_t*>(y.data()), incy, reinterpret_cast<oclComplex_t*>(&result));
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_FLOAT_EQ(expected.real(), result.real());
    EXPECT_FLOAT_EQ(expected.imag(), result.imag());
}

TEST(Cdotc, 16_inc1) {
    const int n = 16;
    const int incx = 1;
    const int incy = 1;

    std::vector<std::complex<float>> x(n*incx);
    for (int i = 0; i < n; i++) {
        x[i*incx] = { i % 16 * 1.f, i % 32 * 1.f };
    }
    std::vector<std::complex<float>> y(n*incy);
    for (int i = 0; i < n; i++) {
        y[i*incy] = { 32.f - i % 32, 16.f - i % 16 };
    }
    std::complex<float> result(-1.f, -2.f);
    std::complex<float> expected;
    for (int i = 0; i < n; i++) {
        expected += std::conj(x[i*incx]) * y[i*incy];
    }

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, reinterpret_cast<oclComplex_t*>(x.data()), incx,
        reinterpret_cast<oclComplex_t*>(y.data()), incy, reinterpret_cast<oclComplex_t*>(&result));
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_FLOAT_EQ(expected.real(), result.real());
    EXPECT_FLOAT_EQ(expected.imag(), result.imag());
}

TEST(Cdotc, 257_inc2) {
    const int n = 257;
    const int incx = 2;
    const int incy = 2;

    std::vector<std::complex<float>> x(n*incx);
    for (int i = 0; i < n; i++) {
        x[i*incx] = { i % 16 * 1.f, i % 32 * 1.f };
    }
    std::vector<std::complex<float>> y(n*incy);
    for (int i = 0; i < n; i++) {
        y[i*incy] = { 32.f - i % 32, 16.f - i % 16 };
    }
    std::complex<float> result(-1.f, -2.f);
    std::complex<float> expected;
    for (int i = 0; i < n; i++) {
        expected += std::conj(x[i*incx]) * y[i*incy];
    }

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, reinterpret_cast<oclComplex_t*>(x.data()), incx,
        reinterpret_cast<oclComplex_t*>(y.data()), incy, reinterpret_cast<oclComplex_t*>(&result));
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_FLOAT_EQ(expected.real(), result.real());
    EXPECT_FLOAT_EQ(expected.imag(), result.imag());
}

TEST(Cdotc, 257_inc1) {
    const int n = 257;
    const int incx = 1;
    const int incy = 1;

    std::vector<std::complex<float>> x(n*incx);
    for (int i = 0; i < n; i++) {
        x[i*incx] = { i % 16 * 1.f, i % 32 * 1.f };
    }
    std::vector<std::complex<float>> y(n*incy);
    for (int i = 0; i < n; i++) {
        y[i*incy] = { 32.f - i % 32, 16.f - i % 16 };
    }
    std::complex<float> result(-1.f, -2.f);
    std::complex<float> expected;
    for (int i = 0; i < n; i++) {
        expected += std::conj(x[i*incx]) * y[i*incy];
    }

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, reinterpret_cast<oclComplex_t*>(x.data()), incx,
        reinterpret_cast<oclComplex_t*>(y.data()), incy, reinterpret_cast<oclComplex_t*>(&result));
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_FLOAT_EQ(expected.real(), result.real());
    EXPECT_FLOAT_EQ(expected.imag(), result.imag());
}

TEST(Cdotc, 65537_inc2) {
    const int n = 65537;
    const int incx = 2;
    const int incy = 2;

    std::vector<std::complex<float>> x(n*incx);
    for (int i = 0; i < n; i++) {
        x[i*incx] = { i % 16 * 1.f, i % 32 * 1.f };
    }
    std::vector<std::complex<float>> y(n*incy);
    for (int i = 0; i < n; i++) {
        y[i*incy] = { 32.f - i % 32, 16.f - i % 16 };
    }
    std::complex<float> result(-1.f, -2.f);
    std::complex<float> expected;
    for (int i = 0; i < n; i++) {
        expected += std::conj(x[i*incx]) * y[i*incy];
    }

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, reinterpret_cast<oclComplex_t*>(x.data()), incx,
        reinterpret_cast<oclComplex_t*>(y.data()), incy, reinterpret_cast<oclComplex_t*>(&result));
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_FLOAT_EQ(expected.real(), result.real());
    EXPECT_FLOAT_EQ(expected.imag(), result.imag());
}

TEST(Cdotc, 65537_inc1) {
    const int n = 65537;
    const int incx = 1;
    const int incy = 1;

    std::vector<std::complex<float>> x(n*incx);
    for (int i = 0; i < n; i++) {
        x[i*incx] = { i % 16 * 1.f, i % 32 * 1.f };
    }
    std::vector<std::complex<float>> y(n*incy);
    for (int i = 0; i < n; i++) {
        y[i*incy] = { 32.f - i % 32, 16.f - i % 16 };
    }
    std::complex<float> result(-1.f, -2.f);
    std::complex<float> expected;
    for (int i = 0; i < n; i++) {
        expected += std::conj(x[i*incx]) * y[i*incy];
    }

    iclblasHandle_t handle;
    iclblasStatus_t status = ICLBLAS_STATUS_SUCCESS;
    status = iclblasCreate(&handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    status = iclblasCdotc(handle, n, reinterpret_cast<oclComplex_t*>(x.data()), incx,
        reinterpret_cast<oclComplex_t*>(y.data()), incy, reinterpret_cast<oclComplex_t*>(&result));
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);
    status = iclblasDestroy(handle);
    ASSERT_EQ(status, ICLBLAS_STATUS_SUCCESS);

    EXPECT_FLOAT_EQ(expected.real(), result.real());
    EXPECT_FLOAT_EQ(expected.imag(), result.imag());
}
