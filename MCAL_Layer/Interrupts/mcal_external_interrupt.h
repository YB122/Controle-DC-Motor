#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INT0_INTERRUPT_ENABLE()     (INTCONbits.INT0IE = 1)
#define EXTERNAL_INT0_INTERRUPT_DISABLE()    (INTCONbits.INT0IE = 0)

#define EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR() (INTCONbits.INT0IF = 0)

#define EXTERNAL_INT0_RISING_EDGE_SET()      (INTCON2bits.INTEDG0 = 1)
#define EXTERNAL_INT0_FALLING_EDGE_SET()     (INTCON2bits.INTEDG0 = 0)


#define EXTERNAL_INT1_INTERRUPT_ENABLE()     (INTCON3bits.INT1IE = 1)
#define EXTERNAL_INT1_INTERRUPT_DISABLE()    (INTCON3bits.INT1IE = 0)

#define EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR() (INTCON3bits.INT1IF = 0)

#define EXTERNAL_INT1_RISING_EDGE_SET()      (INTCON2bits.INTEDG1 = 1)
#define EXTERNAL_INT1_FALLING_EDGE_SET()     (INTCON2bits.INTEDG1 = 0)

#define EXTERNAL_INT2_INTERRUPT_ENABLE()     (INTCON3bits.INT2IE = 1)
#define EXTERNAL_INT2_INTERRUPT_DISABLE()    (INTCON3bits.INT2IE = 0)

#define EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR() (INTCON3bits.INT2IF = 0)

#define EXTERNAL_INT2_RISING_EDGE_SET()      (INTCON2bits.INTEDG2 = 1)
#define EXTERNAL_INT2_FALLING_EDGE_SET()     (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INT1_HIGH_PRIORITY_SET()    (INTCON3bits.INT1IP = 1)
#define EXTERNAL_INT1_LOW_PRIORITY_SET()     (INTCON3bits.INT1IP = 0)

#define EXTERNAL_INT2_HIGH_PRIORITY_SET()    (INTCON3bits.INT2IP = 1)
#define EXTERNAL_INT2_LOW_PRIORITY_SET()     (INTCON3bits.INT2IP = 0)

#endif

#endif

#if EXTERNAL_INTERRUPT_ON_CHANGE_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_RBx_INTERRUPT_ENABLE()      (INTCONbits.RBIE = 1)
#define EXTERNAL_RBx_INTERRUPT_DISABLE()     (INTCONbits.RBIE = 0)

#define EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR()  (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_RBx_HIGH_PRIORITY_SET()     (INTCON2bits.RBIP = 1)
#define EXTERNAL_RBx_LOW_PRIORITY_SET()      (INTCON2bits.RBIP = 0)

#endif

#endif

typedef void (* Interrupt_handler)(void);

typedef enum
{
    FALLING,
    RISING
}interrupt_INTx_EDGE;

typedef enum
{
    INT_0,
    INT_1,
    INT_2
}interrupt_INTx_SRC;

typedef struct
{
    void (* external_interrupt) (void);
    pin_config_t           mcu_pin;
    interrupt_INTx_EDGE    edge;
    interrupt_INTx_SRC     source;
    INTERRUPT_PRIORITY_CFG priority;
}interrupt_INTx_t;

typedef struct
{
    void (* external_interrupt_HIGH) (void);
    void (* external_interrupt_LOW)  (void);
    pin_config_t           mcu_pin;
    INTERRUPT_PRIORITY_CFG priority;
}interrupt_RBx_t;

std_ReturneType Interrupt_INTx_initialize(const interrupt_INTx_t *int_obj);
std_ReturneType Interrupt_INTx_deinitialize(const interrupt_INTx_t *int_obj);
std_ReturneType Interrupt_RBx_initialize(const interrupt_RBx_t *int_obj);
std_ReturneType Interrupt_RBx_deinitialize(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */