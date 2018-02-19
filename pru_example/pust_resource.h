#ifndef _RESOURCE_HOST_SIGNAL_H_
#define _RESOURCE_HOST_SIGNAL_H_

#include <stddef.h>
#include <rsc_types.h>

/* Definition for unused interrupts */
#define HOST_UNUSED     255

/* Mapping sysevts to a channel. Each pair contains a sysevt, channel. */
struct ch_map pru_intc_map[] = { { 17, 2 }, };

struct my_resource_table
{
    struct resource_table base;

    uint32_t offset[1]; /* Should match 'num' in actual definition */

    /* intc definition */
    struct fw_rsc_custom pru_ints;
};

#pragma DATA_SECTION(resourceTable, ".resource_table")
#pragma RETAIN(resourceTable)
struct my_resource_table resourceTable =
{
    1, /* Resource table version: only version 1 is supported by the current driver */
    1, /* number of entries in the table */
    0, 0, /* reserved, must be zero */
    /* offsets to entries */
    {
        offsetof(struct my_resource_table, pru_ints),
    },

    {
        TYPE_CUSTOM, TYPE_PRU_INTS,
        sizeof(struct fw_rsc_custom_ints),
        { /* PRU_INTS version */
            0x0000,
            /* Channel-to-host mapping, 255 for unused */
            HOST_UNUSED, HOST_UNUSED, 2, HOST_UNUSED, HOST_UNUSED,
            HOST_UNUSED, HOST_UNUSED, HOST_UNUSED, HOST_UNUSED, HOST_UNUSED,
            /* Number of evts being mapped to channels */
            (sizeof(pru_intc_map) / sizeof(struct ch_map)),
            /* Pointer to the structure containing mapped events */
            pru_intc_map,
        },
    },
};

#endif
