//**************************************************************************************************************
/**
 *Lab05
 *Lourdes Ruiz
 */
//**************************************************************************************************************
// Librerias
//**************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"

#define XTAL 16000000

//**************************************************************************************************************
// Variables Globales
//**************************************************************************************************************
uint32_t i = 0;
uint32_t antirrebote = 0;

//**************************************************************************************************************
// Prototipos de Funciones
//**************************************************************************************************************
void delay(uint32_t msec);
void delay1ms(void);

//**************************************************************************************************************
// Funcion Principal
//**************************************************************************************************************
int main(void)
{
    // Se setea oscilador externo de 16MHz
    //pre-scaler | oscilador (no pll en este caso) | reloj principal | 16 MHz
    SysCtlClockSet(
            SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN
                    | SYSCTL_XTAL_16MHZ);  //16MHz

    // Se asigna reloj a puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Se establecen como salidas los pines 1, 2 y 3 del puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
                          GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); //se configura PUSH1 como entrada

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); // se configura PUSH 1 como weak pull-up
   //**********************************************************************************************************
   // Loop Principal
   //**********************************************************************************************************
   while (1)
    {
       if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0){
           antirrebote = 1;
       }

       if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) && antirrebote == 1){

           antirrebote = 0;

           // Se prende solo el led verde porque se esta utilizando la mascara
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
           delay(1000);

           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
           delay(500);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
           delay(500);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
           delay(500);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
           delay(500);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
           delay(500);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
           delay(500);

           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                        GPIO_PIN_3 | GPIO_PIN_1 );
           delay(1000);

           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                        GPIO_PIN_1 );
           delay(1000);


        }


    }
}
//**************************************************************************************************************
// Funcion para hacer delay en milisegundos
//**************************************************************************************************************
void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        delay1ms();
    }

}
//**************************************************************************************************************
// Funcion para hacer delay de 1 milisegundos
//**************************************************************************************************************
void delay1ms(void)
{
    SysTickDisable(); //deshabilita el contador del timer
    SysTickPeriodSet(16000-1); //se coloca el período del timer
    SysTickEnable();

    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0); //Pg. 138 / si bit COUNT está en 1, ya contó hasta 0 y esto deja de cumplirse

}


