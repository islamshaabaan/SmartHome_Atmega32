#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_


typedef unsigned char u8;            /*                            0 .. 255                         */
typedef unsigned short int u16;      /*                            0 .. 65,535                      */
typedef unsigned long int u32;       /*                            0 .. 4,294,967,295               */
typedef unsigned long long int u64;  /*                            0 .. 18,446,744,073,709,551,615  */

typedef signed char s8;              /*                         -128 .. +127                        */
typedef signed short int s16;        /*                      -32,768 .. +32,767                     */
typedef signed long int s32;         /*               -2,147,483,648 .. 2,147,483,647               */
typedef signed long long int s64;    /*   -9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807   */

typedef	float f32;                   /*   -3.4E+38 .. +3.4E+38   Accuracy: 6 decimal digit          */
typedef	double f64;                  /*  -1.7E+308 .. +1.7E+308  Accuracy: 6 decimal digit          */

#ifndef FALSE
#define FALSE		(0u)
#endif

#ifndef TRUE
#define TRUE		(1u)
#endif

/*  Definition of NULL Address  */
#define NULL_ADDRESS	((void*)0)



/************States Defintion**************/

#define HIGH			1
#define LOW				0

#define OK				1
#define ERROR			0
#define NULL_PTR		2
#define INPUT			0
#define OUTPUT			1


typedef enum
{
	STD_TYPES_OK,
	STD_TYPES_NOK
}ErrorState;

#endif
