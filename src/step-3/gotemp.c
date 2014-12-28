#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/slab.h>

#define VENDOR_ID	0x08f7
#define PRODUCT_ID	0x0002

/* table of devices that work with this driver */
static struct usb_device_id id_table[] = {
	{ USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

struct gotemp {
	struct usb_device *udev;
	int temp;
};

static int gotemp_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct gotemp *gdev;

	gdev = kzalloc(sizeof(*gdev), GFP_KERNEL);
	if (gdev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		return -ENOMEM;
	}

	gdev->udev = usb_get_dev(udev);

	usb_set_intfdata(interface, gdev);

	dev_info(&interface->dev, "USB GoTemp device now attached\n");
	return 0;
}

static void gotemp_disconnect(struct usb_interface *interface)
{
	struct gotemp *gdev;

	gdev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	usb_put_dev(gdev->udev);

	kfree(gdev);

	dev_info(&interface->dev, "USB GoTemp now disconnected\n");
}

static struct usb_driver gotemp_driver = {
	.name =		"gotemp",
	.probe =	gotemp_probe,
	.disconnect =	gotemp_disconnect,
	.id_table =	id_table,
};

static int __init gotemp_init(void)
{
	return usb_register(&gotemp_driver);
}

static void __exit gotemp_exit(void)
{
	usb_deregister(&gotemp_driver);
}

module_init(gotemp_init);
module_exit(gotemp_exit);

MODULE_AUTHOR("My name here");
MODULE_DESCRIPTION("Simple driver");
MODULE_LICENSE("GPL");
