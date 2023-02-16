#ifndef QEMU_VIRTIO_DRI_H
#define QEMU_VIRTIO_DRI_H

#include "standard-headers/linux/virtio_dri.h"
#include "hw/virtio/virtio.h"
#include "hw/virtio/virtio-pci.h"

/* virtio-dri device */
#define TYPE_VIRTIO_DRI		"virtio-dri"

typedef struct {
	VirtIODevice parent_obj;

	size_t config_size;
} VirtIODri;

#define VIRTIO_DRI(obj)	\
	OBJECT_CHECK(VirtIODri, (obj), TYPE_VIRTIO_DRI)

/* virtio-dri-pci device */
#define TYPE_VIRTIO_DRI_PCI	"virtio-dri-pci"

typedef struct {
	VirtIOPCIProxy parent_obj;
	VirtIODri vdev;
} VirtIODriPCI;

#endif /* QEMU_VIRTIO_DRI_H */
