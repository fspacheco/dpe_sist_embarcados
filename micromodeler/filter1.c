/******************************* SOURCE LICENSE *********************************
Copyright (c) 2020 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to 
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at http://www.micromodeler.com/launch.jsp

#include "filter1.h"

#include <stdlib.h> // For malloc/free
#include <string.h> // For memset
#include <stdio.h>		// For test case I/O

float filter1_impulseInput[5] = 
{
	1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000
};

float filter1_impulseOutput[5] = 
{
	0.20000000, 0.20000000, 0.20000000, 0.20000000, 0.20000000
};

float filter1_noiseInput[15] = 
{
	1.00000000, 1.00000000, 1.00000000, 1.00000000, -1.00000000, -1.00000000, -1.00000000, 1.00000000,
	-1.00000000, -1.00000000, 1.00000000, 1.00000000, -1.00000000, 1.00000000, -1.00000000
};

float filter1_noiseOutput[15] = 
{
	0.20000000, 0.40000000, 0.60000000, 0.80000000, 0.60000000, 0.20000000, -0.20000000, -0.20000000,
	-0.60000000, -0.60000000, -0.20000000, 0.20000000, -0.20000000, 0.20000000, 0.20000000
};

float filter1_multiSineInput[10] = 
{
	0.61981526, -0.07454356, -0.17000082, -0.66514568, 0.85011492, -0.50378551, 0.54830706, -0.74390119,
	1.00000000, -0.79128664
};

float filter1_multiSineOutput[10] = 
{
	0.12396305, 0.10905434, 0.07505418, -0.05797496, 0.11204802, -0.11267213, 0.01189799, -0.10288208,
	0.23014705, -0.09813326
};

float filter1_overflowInput[5] = 
{
	1.00000000, 1.00000000, 1.00000000, 1.00000000, 1.00000000
};

float filter1_overflowOutput[5] = 
{
	0.20000000, 0.40000000, 0.60000000, 0.80000000, 1.00000000
};

float filter1_testOutput[15];

filter1Type *filter1_create( void )
{
	filter1Type *result = (filter1Type *)malloc( sizeof( filter1Type ) );	// Allocate memory for the object
	filter1_init( result );											// Initialize it
	return result;																// Return the result
}

void filter1_destroy( filter1Type *pObject )
{
	free( pObject );
}

 void filter1_init( filter1Type * pThis )
{
	filter1_reset( pThis );

}

 void filter1_reset( filter1Type * pThis )
{
	memset( &pThis->state, 0, sizeof( pThis->state ) ); // Reset state to 0
	pThis->pointer = pThis->state;						// History buffer points to start of state buffer
	pThis->output = 0;									// Reset output
	pThis->accumulator = 0; // Reset accumulator

}

 int filter1_filterBlock( filter1Type * pThis, float * pInput, float * pOutput, unsigned int count )
{
	int originalCount = count;
 	float accumulator = pThis->accumulator;
 
 	while( count-- )
 	{
 		accumulator += *pInput;					// Add the new sample
		*(pOutput++) = accumulator * 0.2;	// Write the output. (Divide by $filter.N})
 		accumulator -= *(pThis->pointer);		// Subtract the oldest sample
 	
 		*(pThis->pointer++) = *(pInput++);	// Store the new sample in the circular history buffer
 		if( pThis->pointer >= pThis->state + filter1_length )		// Handle wrap-around
 			pThis->pointer -= filter1_length; 		
 	}
 
 	 pThis->accumulator = accumulator;	// Store the accumulator
 	 return originalCount;

}

 void filter1_runTests(  void  )
{
	int samplesProcessed;

	filter1Type *filter = filter1_create();	// Create an instance of the filter

	printf( "\n\nRunning tests for: filter1\n" );

	printf( "\nimpulse test\n" );
 	filter1_reset( filter );
	samplesProcessed = filter1_filterInChunks( filter, filter1_impulseInput, filter1_testOutput, 5 );		// Filter the input test signal
	filter1_compareResult( filter1_testOutput, filter1_impulseOutput, samplesProcessed, 0.01, 0.01 );	// Compare with the pre-computed output signal

	printf( "\nnoise test\n" );
 	filter1_reset( filter );
	samplesProcessed = filter1_filterInChunks( filter, filter1_noiseInput, filter1_testOutput, 15 );		// Filter the input test signal
	filter1_compareResult( filter1_testOutput, filter1_noiseOutput, samplesProcessed, 0.01, 0.01 );	// Compare with the pre-computed output signal

	printf( "\nmultiSine test\n" );
 	filter1_reset( filter );
	samplesProcessed = filter1_filterInChunks( filter, filter1_multiSineInput, filter1_testOutput, 10 );		// Filter the input test signal
	filter1_compareResult( filter1_testOutput, filter1_multiSineOutput, samplesProcessed, 0.01, 0.01 );	// Compare with the pre-computed output signal

	printf( "\noverflow test\n" );
 	filter1_reset( filter );
	samplesProcessed = filter1_filterInChunks( filter, filter1_overflowInput, filter1_testOutput, 5 );		// Filter the input test signal
	filter1_compareResult( filter1_testOutput, filter1_overflowOutput, samplesProcessed, 0.01, 0.01 );	// Compare with the pre-computed output signal
	filter1_destroy( filter );

}

 void filter1_compareResult( float * pInput, float * pReference, int count, float maxThreshold, float msThreshold )
{
	float ms = 0.0f, mx = 0.0f, referenceMax = 0.0f, actual, normalizedDelta, delta, reference, scale;
	int index;

	// Measure maximum value of the expected signal
	for (index = 0; index < count; ++index)
	{
		reference = pReference[ index ];
		if ( reference > referenceMax) referenceMax = reference;
		else if (-reference > referenceMax) referenceMax = -reference;
	}

	// Scale error by (100%)/(max of reference signal)
	scale = referenceMax > 0.0000001f ? 1.0f / referenceMax : 1.0f;

	printf( "actual  	expected	delta   	norm. error\n" );
	for (index = 0; index < count; ++index)
	{
		reference = pReference[ index ];
		actual = filter1_outputToFloat( pInput[index] );
		delta = (actual - reference);
		normalizedDelta = delta * scale;
		ms += normalizedDelta * normalizedDelta;
		if(  normalizedDelta > mx ) mx =  normalizedDelta;
		if( -normalizedDelta > mx ) mx = -normalizedDelta;
		printf( "%.6f	%.6f	%.6f	%.6f\n", actual, reference, delta, normalizedDelta );
	}

	printf( "Reference Max %f\n", referenceMax);
	printf( "Maximum Error: %f%%. Threshold = %f%%. Ratio = %f, %s\n",      mx, maxThreshold, 	mx / maxThreshold, mx < maxThreshold 	? "PASS" : "FAIL" );
	printf( "Mean Squared Error: %f%%. Threshold = %f%%. Ratio = %f, %s\n", ms, msThreshold, 	ms / msThreshold,  ms < msThreshold 	? "PASS" : "FAIL" );

}

 int filter1_filterInChunks( filter1Type * pThis, float * pInput, float * pOutput, int length )
{
 	int processedLength = 0;
	unsigned int chunkLength, outLength;
	static long random = 0x6428734; // Use pseudo-random number generator to split input into small random length chunks.
	while( length > 0 )
	{
		chunkLength = random & 0xf;                                         // Choose random chunkLength from 0 - 15
		if( chunkLength > length ) chunkLength = length;                    // Limit chunk length to the number of remaining samples
		outLength = filter1_filterBlock( pThis,  pInput, pOutput, chunkLength );     // Filter the block and determine the number of returned samples
		pOutput += outLength;                                               // Update the output pointer
		processedLength += outLength;                                       // Update the total number of samples output
		pInput += chunkLength;                                              // Update the input pointer
		length -= chunkLength;                                              // Update the number of samples remaining
		random = random + 0x834f4527;                                       // Cycle the simple random number generator
	}
	return processedLength;                                                 // Return the number of samples processed

}


