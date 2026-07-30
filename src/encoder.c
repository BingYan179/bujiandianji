/* encoder.c
 * Minimal encoder interface for incremental A/B encoder (500 CPR). Implementation expects
 * the QEI or GPIO interrupts to increment/decrement an internal counter.
 */

#include "encoder.h"
#include <stdint.h>

static volatile int64_t encoder_counts = 0;

void Encoder_init(void)
{
    // TODO: configure TIMG QEI or GPIO interrupts using SysConfig to update encoder_counts.
    // The SysConfig step-by-step is in sysconfig-guides.txt
}

int64_t Encoder_getCounts(void)
{
    return encoder_counts;
}

// Example ISR to be wired to your QEI driver or GPIO interrupt:
// void QEI_IRQHandler(void) {
//     // read hardware count and update encoder_counts accordingly (atomic)
// }
