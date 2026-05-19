#include "operacoes.h"


int processarCalculoHardware(String paramA, String paramB, String op) {
    
    int valA = strtol(paramA.c_str(), NULL, 2);
    int valB = strtol(paramB.c_str(), NULL, 2);

    int calculoBruto = (op == "add") ? (valA + valB) : (valA - valB);

    int resultado = (op == "add") ? (valA + valB) : (valA - valB);

    resultado = resultado & 0x0F;

    digitalWrite(LED_BIT0, resultado & 0x01); 
    digitalWrite(LED_BIT1, resultado & 0x02); 
    digitalWrite(LED_BIT2, resultado & 0x04); 
    digitalWrite(LED_BIT3, resultado & 0x08); 

    if (calculoBruto > 15 || calculoBruto < 0) {
        return -1;
    }

    return resultado;
}
