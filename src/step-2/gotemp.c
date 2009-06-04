#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>

#define VENDOR_ID	0x08f7
#define PRODUCT_ID	0x0002

/* table of devices that work with this driver */
static struct usb_device_id id_table[] = {
	{ USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static int gotemp_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	dev_info(&interface->dev, "USB GoTemp device now attached\n");
	return 0;
}

static void gotemp_disconnect(struct usb_interface *interface)
{
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
