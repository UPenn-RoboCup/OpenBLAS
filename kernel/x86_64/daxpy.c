/***************************************************************************
Copyright (c) 2014, The OpenBLAS Project
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.
3. Neither the name of the OpenBLAS project nor the names of
its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE OPENBLAS PROJECT OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/


#include "common.h"


#if defined(NEHALEM)
#include "daxpy_microk_nehalem-2.c"
#elif defined(BULLDOZER)
#include "daxpy_microk_bulldozer-2.c"
#endif


#ifndef HAVE_KERNEL_8

static void daxpy_kernel_8(BLASLONG n, FLOAT *x, FLOAT *y, FLOAT *alpha)
{
	BLASLONG register i = 0;
	FLOAT a = *alpha;

	while(i < n)
        {
              y[i]   += a * x[i];
              y[i+1] += a * x[i+1];
              y[i+2] += a * x[i+2];
              y[i+3] += a * x[i+3];
              y[i+4] += a * x[i+4];
              y[i+5] += a * x[i+5];
              y[i+6] += a * x[i+6];
              y[i+7] += a * x[i+7];
              i+=8 ;

       }

}

#endif

int CNAME(BLASLONG n, BLASLONG dummy0, BLASLONG dummy1, FLOAT da, FLOAT *x, BLASLONG inc_x, FLOAT *y, BLASLONG inc_y, FLOAT *dummy, BLASLONG dummy2)
{
	BLASLONG i=0;
	BLASLONG ix=0,iy=0;

	if ( n <= 0 )  return(0);

	if ( (inc_x == 1) && (inc_y == 1) )
	{

		int n1 = n & -8;

		if ( n1 )
			daxpy_kernel_8(n1, x, y , &da );

		i = n1;
		while(i < n)
		{

			y[i] += da * x[i] ;
			i++ ;

		}
		return(0);


	}

	while(i < n)
	{

		y[iy] += da * x[ix] ;
		ix  += inc_x ;
		iy  += inc_y ;
		i++ ;

	}
	return(0);

}


