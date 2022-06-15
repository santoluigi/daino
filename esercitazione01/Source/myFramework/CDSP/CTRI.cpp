/*
  ==============================================================================

    CTRI.cpp
    Created: 14 Jun 2022 11:31:54am
    Author:  gabrielepetrillo

  ==============================================================================
*/

#include "CTRI.h"
#include "Math.h"

CTRI::CTRI()
{
    init();
}

CTRI::~CTRI()
{
}

void CTRI::init(){
    
    int ct1;
    int ct3=1;
    double fase;
    double sample = 0;
    for(ct1=0; ct1<KCOSCMaxSampleNumber; ct1++){
        
        for(int ct2 = 1; ct2<64; ct2++){
            
            if(ct2%2 == 0){
                sample += 0.0 * (sin((float)(ct2) * (mTWOPI*(ct1/(double)(KCOSCMaxSampleNumber)))));
            } else {
                if(ct3 %2 == 1){
                    fase = 1.0;
                    ct3++;
                } else {
                    fase = -1.0;
                    ct3++;
                }
            sample += (fase/(double)(pow(ct2,2))) * (sin((float)(ct2) * (mTWOPI*(ct1/(double)(KCOSCMaxSampleNumber)))));
            }
            
        }
       
        table1[ct1] = sample;
        sample = 0;
    }
    
    currentTableIndex = 0;
}

void CTRI::setNormalizedFreq(double freq){
    
    inc = KCOSCMaxSampleNumber * freq;
}

void CTRI::process(float *buffer, long bufferLenght, int currentTableIndex, float freq){
    
    long ct1;
    
    double y0;
    double y1;
    
    double *currentTable = table1;
    
    if(freq > 10000){
        currentTableIndex = 0;
    };
    
    //Switch per la tabella
    
    switch(currentTableIndex)    {
        case 0:
            currentTable = table1;
            break;
        case 1:
            currentTable = table1;
            break;
        default:
            currentTable = table1;
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
