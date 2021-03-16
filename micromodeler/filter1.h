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

// Begin header file, filter1.h

#ifndef FILTER1_H_ // Include guards
#define FILTER1_H_

/*
Generated code is based on the following filter design:
<micro.DSP.FilterDocument sampleFrequency="#1" arithmetic="float" biquads="Direct1" classname="filter1" inputMax="#1" inputShift="#15" >
  <micro.DSP.BoxcarFilter N="#5" >
    <micro.DSP.GainControl magnitude="#1" frequency="#0" peak="#true" />
    <micro.DSP.FilterStructure coefficientBits="#0" variableBits="#0" accumulatorBits="#0" biquads="Direct1" >
      <micro.DSP.FilterSection form="Fir" historyType="Double" accumulatorBits="#0" variableBits="#0" coefficientBits="#0" />
    </micro.DSP.FilterStructure>
    <micro.DSP.PoleOrZeroContainer >
      <micro.DSP.UnitZero i="#0.9510565162951535" r="#0.30901699437494745" isPoint="#true" isPole="#false" isZero="#true" symmetry="u" N="#1" cascade="#0" />
      <micro.DSP.UnitZero i="#0.587785252292473" r="#-0.8090169943749476" isPoint="#true" isPole="#false" isZero="#true" symmetry="u" N="#1" cascade="#0" />
    </micro.DSP.PoleOrZeroContainer>
    <micro.DSP.GenericC.CodeGenerator generateTestCases="#true" />
  </micro.DSP.BoxcarFilter>
</micro.DSP.FilterDocument>

*/

static const int filter1_length = 4;
extern float filter1_impulseInput[5];
extern float filter1_impulseOutput[5];
extern float filter1_noiseInput[15];
extern float filter1_noiseOutput[15];
extern float filter1_multiSineInput[10];
extern float filter1_multiSineOutput[10];
extern float filter1_overflowInput[5];
extern float filter1_overflowOutput[5];
extern float filter1_testOutput[15];

typedef struct
{
	float * pointer;
	float state[4];
	float output;
	float accumulator;
} filter1Type;


filter1Type *filter1_create( void );
void filter1_destroy( filter1Type *pObject );
 void filter1_init( filter1Type * pThis );
 void filter1_reset( filter1Type * pThis );
#define filter1_writeInput( pThis, input )  \
	filter1_filterBlock( pThis, &(input), &(pThis)->output, 1 );

#define filter1_readOutput( pThis )  \
	(pThis)->output

 int filter1_filterBlock( filter1Type * pThis, float * pInput, float * pOutput, unsigned int count );
#define filter1_outputToFloat( output )  \
	(output)

#define filter1_inputFromFloat( input )  \
	(input)

 void filter1_runTests(  void  );
 void filter1_compareResult( float * pInput, float * pReference, int count, float maxThreshold, float msThreshold );
 int filter1_filterInChunks( filter1Type * pThis, float * pInput, float * pOutput, int length );
#endif // FILTER1_H_
	
