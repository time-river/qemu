#include "qemu/osdep.h"

#include "hw/virtio/virtio.h"
#include "hw/virtio/virtio-access.h"
#include "hw/virtio/virtio-dri.h"

static void virtio_dri_handle_output(VirtIODevice *vdev, VirtQueue *vq)
{
	VirtIODri *d = VIRTIO_DRI(vdev);
	VirtQueueElement *elem;

	while (true) {
		size_t offset = 0;
		size_t count;
		uint32_t pfn;

		elem = virtqueue_pop(vq, sizeof(VirtQueueElement));
		if (!elem)
			break;

		count = iov_to_buf(elem->out_sg, elem->out_num, offset, &pfn, 4);
		while (count == 4) {
			int p = virtio_ldl_p(vdev, &pfn);

			offset += 4;
			printf("recv elem, count %d\n", p);
		}

		virtqueue_push(vq, elem, 0);
		virtio_notify(vdev, vq);
		g_free(elem);
	}

	return;
}

static void timer_poll_cb(void *opaque)
{
	VirtIODri *d = opaque;
	VirtIODevice *vdev = VIRTIO_DEVICE(d);

	printf(">>> set count %d\n", d->count);
	d->count += 1;

	virtio_notify_config(vdev);
	timer_mod(d->timer, qemu_clock_get_ms(QEMU_CLOCK_VIRTUAL) + 1000);
}

static void virtio_dri_device_realize(DeviceState *dev, Error **errp)
{
	VirtIODevice *vdev = VIRTIO_DEVICE(dev);
	VirtIODri *d = VIRTIO_DRI(dev);

	printf(">>> %s\n", __func__);
	virtio_init(vdev, "virtio-dri", VIRTIO_ID_DRI, d->config_size);

	d->ivq = virtio_add_queue(vdev, 128, virtio_dri_handle_output);

	/* create timer to triger events */
	d->timer = timer_new_ms(QEMU_CLOCK_VIRTUAL, timer_poll_cb, d);
	timer_mod(d->timer, qemu_clock_get_ms(QEMU_CLOCK_VIRTUAL) + 30000);

	return;
}

static void virtio_dri_device_unrealize(DeviceState *dev)
{
	VirtIODevice *vdev = VIRTIO_DEVICE(dev);
	VirtIODri *d = VIRTIO_DRI(dev);

	printf(">>> %s\n", __func__);

	virtio_cleanup(vdev);
	return;
}

static void virtio_dri_device_reset(VirtIODevice *vdev)
{
	printf(">>> %s\n", __func__);

	return;
}

static void virtio_dri_get_config(VirtIODevice *vdev, uint8_t *config)
{
	printf(">>> %s\n", __func__);

	return;
}

static void virtio_dri_set_config(VirtIODevice *vdev, const uint8_t *config)
{
	printf(">>> %s\n", __func__);

	return;
}

static uint64_t virtio_dri_get_features(VirtIODevice *vdev, uint64_t features, Error **errp)
{
	VirtIODri *dev = VIRTIO_DRI(vdev);

	printf(">>> %s, features 0x%lx\n", __func__, features);
	virtio_add_feature(&f, VIRTIO_DRI_F_PING_PONG);

	return features;
}

static void virtio_dri_set_features(VirtIODevice *vdev, uint64_t features)
{
	printf(">>> %s, features 0x%lx\n", __func__, features);
}

static void virtio_dri_set_status(struct VirtIODevice *vdev, uint8_t status)
{
	printf(">>> %s, status 0x%x\n", __func__, status);

	return;
}

static const VMStateDescription vmstate_virtio_dri = {
	.name = "virtio-dri",
	.version_id = 1,
	.fields =  (VMStateField[]) {
		VMSTATE_VIRTIO_DEVICE,
		VMSTATE_END_OF_LIST()
	},
};

static Property virtio_dri_properties[] = {
	DEFINE_PROP_END_OF_LIST(),
};

static const VMStateDescription vmstate_virtio_dri_device = {
};

static void virtio_dri_class_init(ObjectClass *klass, void *data)
{
	DeviceClass *dc = DEVICE_CLASS(klass);
	VirtioDeviceClass *vdc = VIRTIO_DEVICE_CLASS(klass);

	device_class_set_props(dc, virtio_dri_properties);
	dc->vmsd = &vmstate_virtio_dri;
	set_bit(DEVICE_CATEGORY_DISPLAY, dc->categories);
	vdc->realize = virtio_dri_device_realize;
	vdc->unrealize = virtio_dri_device_unrealize;
	vdc->get_config = virtio_dri_get_config;
	vdc->set_config = virtio_dri_set_config;
	vdc->get_features = virtio_dri_get_features;
	vdc->set_features = virtio_dri_set_features;
	vdc->reset = virtio_dri_device_reset;
	vdc->set_status = virtio_dri_set_status;
	vdc->vmsd = &vmstate_virtio_dri_device;
}

static void virtio_dri_instance_init(Object *obj)
{
	printf(">>> %s\n", __func__);

	return;
}

static const TypeInfo virtio_dri_info = {
    .name = TYPE_VIRTIO_DRI,
    .parent = TYPE_VIRTIO_DEVICE,
    .instance_size = sizeof(VirtIODri),
    .instance_init = virtio_dri_instance_init,
    .class_init = virtio_dri_class_init,
};

static void virtio_dri_register(void)
{
	printf(">> %s\n", __func__);
	type_register_static(&virtio_dri_info);

	return;
}

type_init(virtio_dri_register)
