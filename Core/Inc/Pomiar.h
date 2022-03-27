#ifndef INC_POMIAR_H
#define INC_POMIAR_H
#include <stdio.h>
#include "../Inc/ADC_Pomiary.h"
#include "../src/ADC_Pomiary.c"



void WykonajPomiar(ADC_pomiary *Pomiar);

void BuforData(ADC_pomiary *Pomiar,uint32_t);



#endif /* INC_POMIAR_H_ */
