/*
 * Copyright (c) 2020 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef RESOURCE_TABLE_H__
#define RESOURCE_TABLE_H__

#include <openamp/rpmsg.h>
#include <openamp/remoteproc.h>
#include <openamp/virtio.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (CONFIG_OPENAMP_RSC_TABLE_NUM_RPMSG_BUFF > 0)

#define VDEV_ID                 0xFF
#define VRING0_ID               CONFIG_OPENAMP_RSC_TABLE_IPM_RX_ID /* (host to remote) */
#define VRING1_ID               CONFIG_OPENAMP_RSC_TABLE_IPM_TX_ID /* (remote to host) */

#define VRING_COUNT             2
#define RPMSG_IPU_C0_FEATURES   1

#define VRING_RX_ADDRESS        -1  /* allocated by Master processor */
#define VRING_TX_ADDRESS        -1  /* allocated by Master processor */
#define VRING_BUFF_ADDRESS      -1  /* allocated by Master processor */
#define VRING_ALIGNMENT         16  /* fixed to match with Linux constraint */

#define RSC_VENDOR_EPT_TABLE    128 /* List of bound endpoints */

#endif

enum rsc_table_entries {
	RSC_TABLE_EPT_TABLE_ENTRY,
#if (CONFIG_OPENAMP_RSC_TABLE_NUM_RPMSG_BUFF > 0)
	RSC_TABLE_VDEV_ENTRY,
#endif
#if defined(CONFIG_RAM_CONSOLE)
	RSC_TABLE_TRACE_ENTRY,
#endif
	RSC_TABLE_NUM_ENTRY
};

METAL_PACKED_BEGIN
struct ept_info {
	char name[RPMSG_NAME_SIZE];
	uint32_t addr;
	uint32_t dest_addr;
} METAL_PACKED_END;

#define MAX_NUM_OF_EPTS 64

METAL_PACKED_BEGIN
struct fw_rsc_ept {
	uint32_t type;
	uint32_t num_of_epts;
	struct ept_info endpoints[MAX_NUM_OF_EPTS];
} METAL_PACKED_END;

struct fw_resource_table {
	struct resource_table hdr;
	uint32_t offset[RSC_TABLE_NUM_ENTRY];

	struct fw_rsc_ept ept_table;
#if (CONFIG_OPENAMP_RSC_TABLE_NUM_RPMSG_BUFF > 0)
	struct fw_rsc_vdev vdev;
	struct fw_rsc_vdev_vring vring0;
	struct fw_rsc_vdev_vring vring1;
#endif

#if defined(CONFIG_RAM_CONSOLE)
	/* rpmsg trace entry */
	struct fw_rsc_trace cm_trace;
#endif
} METAL_PACKED_END;

void rsc_table_get(struct fw_resource_table **table_ptr, int *length);

#if (CONFIG_OPENAMP_RSC_TABLE_NUM_RPMSG_BUFF > 0)

inline struct fw_rsc_vdev *rsc_table_to_vdev(struct fw_resource_table *rsc_table)
{
	return &rsc_table->vdev;
}

inline struct fw_rsc_vdev_vring *rsc_table_get_vring0(struct fw_resource_table *rsc_table)
{
	return &rsc_table->vring0;
}

inline struct fw_rsc_vdev_vring *rsc_table_get_vring1(struct fw_resource_table *rsc_table)
{
	return &rsc_table->vring1;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
