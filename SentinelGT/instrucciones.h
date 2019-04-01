#ifndef INSTRUCCIONES_H_
#define INSTRUCCIONES_H_

/*
 * Esta seccion define los valores que se escribiran en los pines para dirigir la direccion
 * del carro, en caso de ser necesario modificar algun valor, se hace desde aqui y el cambio
 * se ve reflejado en el Switch - Case
 */

//adelante  01
//atras     10

#define ACELERAR    0x50           //Los 4 motores hacia adelante
#define RETROCEDER  0xA0         //Los 4 motores hacia atras
#define IZQ         0x60                //Los motores derechos hacia atras, los izquierdos hacia adelante
#define DER         0x90                //Los motores derechos hacia adelante, los izquierdos hacia atras
#define ADER        0x10               //Los motores derechos hacia adelante, los izquierdos detenidos
#define AIZQ        0x40               //Los motores izquierdos hacia adelante, los derechos detenidos
#define RDER        0x20               //Los motores derechos hacia atras, los izquierdos detenidos
#define RIZQ        0x80               //Los motores izquierdos hacia atras, los derechos detenidos
#define PARO        0x00               //Todos los motores detenidos

/*
 * Para abrir y cerrar la garra
 */

#define ABRIR       0x04
#define CERRAR      0x08
#define GARRA_DEF   0x0C

/*
 * Luz y cambio de velocidad
 */
#define LUZ         0x04
#define VELOCIDAD   0x08
#define AMBOS       0x0C
#define DEFAULT     0x00

/*
 * velocidad de servos
 */
#define velb1 3500
#define velb2 3500
#define posch 2000
#define poscv 2000

/*
 * set point servos
 */
#define spmaxb1 90
#define spminb1 45
#define spmaxb2 108
#define spminb2 60
#define spmaxch 90
#define spminch 50
#define spmaxcv 100
#define spmincv 50

#endif /* INSTRUCCIONES_H_ */
