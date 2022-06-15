/*
  ==============================================================================

    COSC.cpp
    Created: 12 Apr 2022 12:08:51pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#include "COSC.h"
#include "math.h"

COSC::COSC()
{
    init();
}

COSC::~COSC()
{
}

void COSC::init(){
    
    int ct1;
    for(ct1=0; ct1<KCOSCMaxSampleNumber; ct1++){
        table[ct1] = sin(mTWOPI*(ct1/(double)(KCOSCMaxSampleNumber)));
        
        table2[ct1] = 0.5 * (sin(mTWOPI*(ct1/(double)(KCOSCMaxSampleNumber))) + sin(2.0 * (mTWOPI*(ct1/(double)(KCOSCMaxSampleNumber)))));
    }
    
    currentTableIndex = 0;
}

void COSC::setNormalizedFreq(double freq){
    
    inc = KCOSCMaxSampleNumber * freq;
}

void COSC::process(float *buffer, long bufferLenght, int currentTableIndex, float freq){
    
    long ct1;
    
    double y0;
    double y1;
    
    double *currentTable = table;
    
    if(freq > 10000){
        currentTableIndex = 0;
    };
    
    //Switch per la tabella
    
    switch(currentTableIndex)    {
        case 0:
            currentTable = table;
            break;
        case 1:
            currentTable = table2;
            break;
        default:
            currentTable = table;
            break;
    }
    
    for(ct1 = 0; ct1 < bufferLenght; ct1++){
        y0 = currentTable[(long) readPos];
        
        if(readPos + 1 > KCOSCMaxSampleNumber){
            y1 = currentTable[0];
        } else {
            y1 = currentTable[(long) (readPos + 1)];
        }
        
        buffer[ct1] = y0 + ((readPos - (long) readPos) * (y1 - y0));
        
        readPos = readPos + inc;
        
        if(readPos > KCOSCMaxSampleNumber){
            readPos -= KCOSCMaxSampleNumber;
        }
    }
}
