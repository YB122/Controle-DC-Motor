#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "mcal_interrupt_config.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_DIASBLE()       (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_ENABLE()        (PIE1bits.ADIE = 1)

#define ADC_INTERRUPT_CLEAR_FLAG()    (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define ADC_HIGH_PRIORITY_SET()    (IPR1bits.ADIP = 1)
#define ADC_LOW_PRIORITY_SET()     (IPR1bits.ADIP = 0)

#endif
#endif
#endif	/* MCAL_INTERNAL_INTERRUPT_H */
