#include "qemu/osdep.h"

#include "hw/pci/pci.h"
#include "hw/virtio/virtio.h"
#include "hw/virtio/virtio-pci.h"
#include "hw/virtio/virtio-dri.h"

#include "standard-headers/linux/virtio_dri.h"

DECLARE_INSTANCE_CHECKER(VirtIODriPCI, VIRTIO_DRI_PCI, TYPE_VIRTIO_DRI_PCI)

static void virtio_dri_pci_realize(VirtIOPCIProxy *vpci_dev, Error **errp)
{
	VirtIODriPCI *dev = VIRTIO_DRI_PCI(vpci_dev);
	DeviceState *vdev = DEVICE(&dev->vdev);

	printf(">>> %s\n", __func__);
	vpci_dev->class_code = PCI_CLASS_OTHERS;
	qdev_realize(vdev, BUS(&vpci_dev->bus), errp);
}

static void virtio_dri_pci_class_init(ObjectClass *klass, void *data)
{
	DeviceClass *dc = DEVICE_CLASS(klass);
	VirtioPCIClass *k = VIRTIO_PCI_CLASS(klass);
	PCIDeviceClass *pcidev_k = PCI_DEVICE_CLASS(klass);

	printf(">>> %s\n", __func__);
	set_bit(DEVICE_CATEGORY_MISC, dc->categories);
	k->realize = virtio_dri_pci_realize;
	pcidev_k->vendor_id = PCI_VENDOR_ID_REDHAT_QUMRANET;
	pcidev_k->device_id = PCI_DEVICE_ID_VIRTIO_DRI;
	pcidev_k->revision = VIRTIO_PCI_ABI_VERSION;
	pcidev_k->class_id = PCI_CLASS_OTHERS;
}

static void virtio_dri_pci_instance_init(Object *obj)
{
	VirtIODriPCI *dev = VIRTIO_DRI_PCI(obj);

	printf(">>> %s\n", __func__);
	virtio_instance_init_common(obj, &dev->vdev, sizeof(dev->vdev),
					TYPE_VIRTIO_DRI);
}

static const VirtioPCIDeviceTypeInfo virtio_dri_pci_info = {
	.generic_name	= TYPE_VIRTIO_DRI_PCI,
	.instance_size	= sizeof(VirtIODriPCI),
	.instance_init	= virtio_dri_pci_instance_init,
	.class_init	= virtio_dri_pci_class_init,
};

static void virtio_dri_pci_register(void)
{
	printf(">> %s\n", __func__);
	virtio_pci_types_register(&virtio_dri_pci_info);
}

type_init(virtio_dri_pci_register)
