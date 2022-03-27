/*
 * ZapisLog.c
 *
 *      Author: Maksym
 */

#include <stdio.h>
#include <string.h>
#include "../Inc/ZapisLog.h"
#include "usart.h"
#include "Pomiar.h"
#define SIZE_OF_BUFFER 3600
int32_t sizeOfUsedBuffer=0;

/**
 * @brief  przeciazenie funkcji printf
 * pozwala na latwe wyswietlenie wyniku za pomoca interfejsu UART na komputerze
 * 
 * @param ch 
 * @return int 
 */
int __io_putchar(int ch)
{
    if (ch == '\n') {
        uint8_t ch2 = '\r';
        HAL_UART_Transmit(&huart2, &ch2, 1, HAL_MAX_DELAY);
    }

    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return 1;
}
/**
 * @brief funkcja SavLog
 * wysyla za pomoca interfejsu UART zawartość bufora (tyle ile pomiarów zostalo wykonanych)
 * @param czujnik 
 */
void SaveLog(ADC_pomiary *czujnik){
	sizeOfUsedBuffer=0;

	for(int i=0;i<SIZE_OF_BUFFER;i++){
		sizeOfUsedBuffer++;
		if(czujnik->Bufor[i]==0){

			break;
		}

	}
	for(int i=0;i<sizeOfUsedBuffer;i++){
		printf("%d\t:\t%ld\n\r",i,czujnik->Bufor[i]);

	}


}


//Dont use- fatal error
//void Zapisz(uint32_t *bufor[]){
//
//FILE *fileptr=fopen("textFile", "a");
//if(fileptr==NULL){
//	perror("open file error");
////	exit(1);
//}
//
//for(int i=0;i<strlen(*bufor);i++){
//	fprintf(fileptr,"%d :%s \n",i,bufor[i]);
//
//}
//fclose(fileptr);
//
//}
