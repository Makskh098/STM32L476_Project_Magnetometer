/*
 * Pomiar.c
 *
 *
 *      Author: Maksym
 */


#include "../Inc/Pomiar.h"
#include "adc.h"
#include "GFX.h"
#include "../Inc/ADC_Pomiary.h"
#include "displayManager.h"

#define NUMBER_OF_CHAR_ON_DISPLAY 20
#define SUPPLY_VOLTAGE 3.3f
#define RESOLUTION_OF_ADC 4096.0f
#define SIZE_OF_BUFFER 3600 // bufor jest w stanie zmiescic godzine pomiarow (można zwiększać)


char str[NUMBER_OF_CHAR_ON_DISPLAY];
uint32_t iterator=0;
/**
 * @brief funkcja WykonajPomiar wlacza przetwornik, pobiera wynik oraz wyswietla go w 2 formach (UART oraz OLED)
 * 
 * @param czujnik  wskaznik na strukture ADC_POmiary
 */
void WykonajPomiar(ADC_pomiary *czujnik){


	HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY);
		  czujnik->value=HAL_ADC_GetValue(&hadc1);
		  czujnik->Volt=SUPPLY_VOLTAGE*czujnik->value/(RESOLUTION_OF_ADC*2);

		  BuforData(czujnik,czujnik->value); // dodanie pomiaru do bufora
		//  printf("wynik: %ld   w Voltach: %f  \n\r",czujnik->value[1],czujnik->Volt[1]);//wyswietlenie przez Uart na bieżąco
		  displayMeas(czujnik->value);	// wyswieltenie na ekranie

}
/**
 * @brief funkcja BuforData
 * sluzy do wpisywania wynikow do bufora
 * @param czujnik 
 * @param data 
 */

void BuforData(ADC_pomiary *czujnik,uint32_t data){
	czujnik->Bufor[iterator]=data;
	iterator++;
	if(iterator>=SIZE_OF_BUFFER) iterator=0;// cyklicznosc bufora
}
/**
 * @brief funkcja ClearBufor
 * sluzy do wyzerowania calego bufora
 * @param czujnik 
 */
void ClearBufor(ADC_pomiary *czujnik)
{
	for(int i=0;i<SIZE_OF_BUFFER;i++)
	czujnik->Bufor[i]=0;
	iterator=0;

}


