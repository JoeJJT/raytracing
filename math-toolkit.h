#ifndef __RAY_MATH_TOOLKIT_H
#define __RAY_MATH_TOOLKIT_H

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <immintrin.h>
static inline __attribute__((always_inline))
void normalize(double *v)
{
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    assert(d != 0.0 && "Error calculating normal");

    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

static inline __attribute__((always_inline))
double length(const double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static inline __attribute__((always_inline))
void add_vector(const double *a, const double *b, double *out)
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            out[0] = a[0] + b[0];
        }
        #pragma omp section
        {
            out[1] = a[1] + b[1];
        }
        #pragma omp section
        {
            out[2] = a[2] + b[2];
        }
    }
}

static inline __attribute__((always_inline))
void subtract_vector(const double *a, const double *b, double *out)
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            out[0] = a[0] - b[0];
        }
        #pragma omp section
        {
            out[1] = a[1] - b[1];
        }
        #pragma omp section
        {
            out[2] = a[2] - b[2];
        }
    }
}

static inline __attribute__((always_inline))
void multiply_vectors(const double *a, const double *b, double *out)
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            out[0] = a[0] * b[0];
        }
        #pragma omp section
        {
            out[1] = a[1] * b[1];
        }
        #pragma omp section
        {
            out[2] = a[2] * b[2];
        }
    }
}

static inline __attribute__((always_inline))
void multiply_vector(const double *a, double b, double *out)
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            out[0] = a[0] * b;
        }
        #pragma omp section
        {
            out[1] = a[1] * b;
        }
        #pragma omp section
        {
            out[2] = a[2] * b;
        }
    }
}

static inline __attribute__((always_inline))
void cross_product(const double *v1, const double *v2, double *out)
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            out[0] = v1[1] * v2[2] - v1[2] * v2[1];
        }
        #pragma omp section
        {
            out[1] = v1[2] * v2[0] - v1[0] * v2[2];
        }
        #pragma omp section
        {
            out[2] = v1[0] * v2[1] - v1[1] * v2[0];
        }
    }
}
/*SIMD 256avx
static inline __attribute__((always_inline))
double dot_product(const double *v1,const double *v2)
{
	register __m256d mv1,mv2,v1v2;
	mv1 = _mm256_set_pd(0,v1[2],v1[1],v1[0]);
	mv2 = _mm256_set_pd(0,v2[2],v2[1],v2[0]);
	v1v2 = _mm256_mul_pd(mv1,mv2);
	return (v1v2[0]+v1v2[1]+v1v2[2]);
}
*/

static inline __attribute__((always_inline))
double dot_product(const double *v1, const double *v2)
{
    double dp = 0.0;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            dp += v1[0] * v2[0];
        }
        #pragma omp section
        {
            dp += v1[1] * v2[1];
        }
        #pragma omp section
        {
            dp += v1[2] * v2[2];
        }
    }
    return dp;
}


static inline __attribute__((always_inline))
void scalar_triple_product(const double *u, const double *v, const double *w,
                           double *out)
{
    cross_product(v, w, out);
    multiply_vectors(u, out, out);
}

static inline __attribute__((always_inline))
double scalar_triple(const double *u, const double *v, const double *w)
{
    double tmp[3];
    cross_product(w, u, tmp);
    return dot_product(v, tmp);
}

#endif
