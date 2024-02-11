#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

#include "std_libraries.h"
#include "compiler.h"

typedef unsigned char uint8   ;
typedef unsigned short uint16 ;
typedef unsigned int uint32   ;
typedef uint8 std_ReturneType ;

#define BIT_MASK        (uint8)1 
#define STD_HIGH        0x01
#define STD_LOW         0x00
#define STD_ON          0x01
#define STD_OFF         0x00
#define STD_ACTIVE      0x01
#define STD_IDLE        0x00
#define E_OK            (std_ReturneType)0x01
#define E_NOT_OK        (std_ReturneType)0x00

#endif	/* MCAL_STD_TYPES_H */
