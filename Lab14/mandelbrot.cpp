#include "mandelbrot.h"
#include <xmmintrin.h>

// cubic_mandelbrot() takes an array of SIZE (x,y) coordinates --- these are
// actually complex numbers x + yi, but we can view them as points on a plane.
// It then executes 200 iterations of f, using the <x,y> point, and checks
// the magnitude of the result; if the magnitude is over 2.0, it assumes
// that the function will diverge to infinity.

// vectorize the code below using SIMD intrinsics
int *
cubic_mandelbrot_vector(float xi[SIZE], float yi[SIZE]) {
    static int ret[SIZE];
   /** float x1, y1, x2, y2;*/
    float temp[4], temp0[4], temp2[4], temp5[4];
    for (int x = 0; x <= 3; x++) 
	{
	temp[x] = 0.0;	
	temp0[x] = 3.0;
	temp5[x] = M_MAG;
	}
	__m128 x1, y1, x2, y2, s1, s2;
	__m128 M = _mm_loadu_ps(temp5);
    for (int i = 0; i < SIZE; i += 4) {
        x1 = _mm_loadu_ps(&temp[0]);
		y1 = _mm_loadu_ps(&temp[0]);
		s1 = _mm_loadu_ps(&xi[i]);
		s2 = _mm_loadu_ps(&yi[i]);
		
        // Run M_ITER iterations
        for (int j = 0; j < M_ITER; j ++) {
            // Calculate x1^2 and y1^2
           /** float x1_squared = x1 * x1;
            float y1_squared = y1 * y1;*/
			__m128 x1_squared = _mm_mul_ps(x1, x1);
			__m128 y1_squared = _mm_mul_ps(y1, y1);
			__m128 thr = _mm_loadu_ps(&temp0[0]);
            // Calculate the real piece of (x1 + (y1*i))^3 + (x + (y*i))
          /**  x2 = x1 * (x1_squared - 3 * y1_squared) + x[i];
			
            // Calculate the imaginary portion of (x1 + (y1*i))^3 + (x + (y*i))
            y2 = y1 * (3 * x1_squared - y1_squared) + y[i];

            // Use the resulting complex number as the input for the next
            // iteration
            x1 = x2;
            y1 = y2;*/
            x2 = _mm_add_ps(_mm_mul_ps(x1, _mm_sub_ps(x1_squared, _mm_mul_ps(thr, y1_squared))), s1);
            y2 = _mm_add_ps(_mm_mul_ps(y1, _mm_sub_ps(_mm_mul_ps(thr, x1_squared), y1_squared)), s2);
            x1 = x2;
            y1 = y2;
        }

        // caculate the magnitude of the result;
        // we could take the square root, but we instead just
        // compare squares
        _mm_storeu_ps(temp2, _mm_cmplt_ps(_mm_add_ps(_mm_mul_ps(x2, x2), _mm_mul_ps(y2, y2)), _mm_mul_ps(M, M)));
        for (int x = 0; x < 4; x ++) ret[i + x] = (temp2[x] < 0.01)? 0:1; 
      //  ret[i] = ((x2 * x2) + (y2 * y2)) < (M_MAG * M_MAG);
    }

    return ret;
}
