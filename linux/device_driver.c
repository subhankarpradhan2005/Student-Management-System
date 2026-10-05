#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "student_driver"
#define CLASS_NAME  "student"

static int major_number;
static struct class *student_class;
static struct device *student_device;
static struct cdev student_cdev;

static char driver_message[128] = "Student Management Driver: ACTIVE\n";

static int driver_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "student_driver: device opened\n");
    return 0;
}

static int driver_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "student_driver: device closed\n");
    return 0;
}

static ssize_t driver_read(struct file *file,
                           char __user *buffer,
                           size_t length,
                           loff_t *offset)
{
    int message_length = strlen(driver_message);

    if (*offset >= message_length)
        return 0;

    if (copy_to_user(buffer, driver_message, message_length))
        return -EFAULT;

    *offset = message_length;

    return message_length;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .read = driver_read,
    .release = driver_release,
};

static int __init student_driver_init(void)
{
    dev_t dev;

    if (alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME) < 0)
        return -1;

    major_number = MAJOR(dev);

    cdev_init(&student_cdev, &fops);

    if (cdev_add(&student_cdev, dev, 1) < 0) {
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    student_class = class_create(CLASS_NAME);

    if (IS_ERR(student_class)) {
        cdev_del(&student_cdev);
        unregister_chrdev_region(dev, 1);
        return PTR_ERR(student_class);
    }

    student_device = device_create(
        student_class,
        NULL,
        dev,
        NULL,
        DEVICE_NAME
    );

    if (IS_ERR(student_device)) {
        class_destroy(student_class);
        cdev_del(&student_cdev);
        unregister_chrdev_region(dev, 1);
        return PTR_ERR(student_device);
    }

    printk(KERN_INFO "student_driver: loaded successfully\n");

    return 0;
}

static void __exit student_driver_exit(void)
{
    dev_t dev = MKDEV(major_number, 0);

    device_destroy(student_class, dev);
    class_destroy(student_class);

    cdev_del(&student_cdev);
    unregister_chrdev_region(dev, 1);

    printk(KERN_INFO "student_driver: unloaded\n");
}

module_init(student_driver_init);
module_exit(student_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Milan");
MODULE_DESCRIPTION("Student Management System Linux Character Device Driver");
MODULE_VERSION("1.0");
