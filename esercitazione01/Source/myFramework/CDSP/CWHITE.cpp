/*
  ==============================================================================

    CWHITE.cpp
    Created: 14 Jun 2022 4:45:07pm
    Author:  gabrielepetrillo

  ==============================================================================
*/

#include "CWHITE.h"
#include "math.h"
#include <stdio.h>
#include <cstdlib>
WHITE::WHITE()
{
    init();
}

WHITE::~WHITE()
{
}

float WHITE::init(){
    
return (((double)(rand() % 100)/100.0)*0.5)-0.25;

}
