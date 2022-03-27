/*
 * ADC_Pomiary.h
 *
 *      Author: Maksym
 */

#ifndef INC_ADC_POMIARY_H_
#define INC_ADC_POMIARY_H_
#define BUFORSIZE 3600

#include <stdint.h>

/**
 * @brief Struktura przechowywujaca pomiary
 * 
 */
typedef struct ADC_pomiary{
	 uint32_t value;
	 float Volt;
	 float Induction_G; // indukcja w Gaussach
	 float Induction_T; // indukcja w Teslach

	 uint32_t Bufor[BUFORSIZE];
}ADC_pomiary;





#endif /* INC_ADC_POMIARY_H_ */
