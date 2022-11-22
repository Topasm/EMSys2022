#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

int init_hello(void);
void exit_hello(void);

static int hello_open(struct inode *, struct file *);
static int hello_close(struct inode *, struct file *);
static ssize_t hello_read(struct file *, char __user *, size_t , loff_t *);
static ssize_t hello_write(struct file *, const char *, size_t, loff_t *);
static loff_t hello_lseek(struct file *file, loff_t offset, int orig);

#define HELLO_MAJOR_NUM 290
#define HELLO_NAME "hello"
#define BUFFER_SIZE 2000
static char array[BUFFER_SIZE]; // Global 변수, Device Driver에서 사용

static int hello_ioctl(struct file *flip, unsigned int cmd, unsigned long arg) // from K.2.6.36
{
    
    int k = 0;
    if (_IOC_TYPE(cmd) != 0x55)
    {
        printk("Wrong Magic #!\n");
        return -1;
    }
    switch (_IOC_NR(cmd))
    {

        //그외 에러처리 (ex, *filepos > 2000 ) 등 처리를 해 줘야 함.

    case 99:
        printk("\tIOCTL Size: %d\n", _IOC_SIZE(cmd)); // should be 8
        copy_from_user(&array, arg, _IOC_SIZE(cmd));
        // do something.

        printk("99번 작동");

        break;
    case 98:
        printk("\tIOCTL Size: %d\n", _IOC_SIZE(cmd)); // should be 8
        copy_from_user(&array, arg, _IOC_SIZE(cmd));
        for (k = array[0]; k < (array[0] + array[1]); k++)
            printk("%c", array[k]);
        printk("\n");
        break;
    default:
        break;
    }
}
static int hello_open(struct inode *node, struct file *pfile)
{
    printk("hello_open enter\n");
    return 0;
}

static ssize_t hello_read(struct file *pfile, char __user *pBuff, size_t size, loff_t *filepos)
{
    printk("hello_read enter\n");
    copy_to_user(pBuff, &array[*filepos], size);
    *filepos += size;
    return size;
}

static ssize_t hello_write(struct file *pfile, const char __user *pBuff, size_t size, loff_t *filepos)
{
    printk("hello_write enter\n");
    copy_from_user(&array[*filepos], pBuff, size);
    *filepos += size;
    return size;
}

static int hello_release(struct inode *node, struct file *pfile)
{
    printk("hello_release enter\n");
    return 0;
}

static const struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_open,
    .read = hello_read,
    .write = hello_write,
    .release = hello_release,
    .unlocked_ioctl = hello_ioctl,
    .llseek = hello_lseek,
};

int flagRegisterSuccess = 0;

int __init init_hello(void)
{
    int ret;
    printk("Hello world.\n");
    ret = register_chrdev(HELLO_MAJOR_NUM, HELLO_NAME, &hello_fops);
    if (ret < 0)
    {
        printk("Hello registr_chrdev fail\n");
        return ret;
    }
    flagRegisterSuccess = 1;
    return 0;
}

void __exit exit_hello(void)
{
    if (flagRegisterSuccess)
    {
        flagRegisterSuccess = 0;
        unregister_chrdev(HELLO_MAJOR_NUM, HELLO_NAME);
    }
    printk("Good-bye~ \n");
}

static loff_t hello_lseek(struct file *file, loff_t offset, int orig)
{ // file read/write pointer: file->f_pos
    loff_t newPos = 0;
    printk("hello lseek working\n");
    if (orig == 0)
    {
        newPos = offset; // SEEK_SET
    }
    else if (orig == 1)
    {
        newPos = file->f_pos + offset; // SEEK_CUR
    }
    else
    {
        newPos = BUFFER_SIZE - offset; // SEEK_END, 내부 버퍼 사이즈=2000
    }

    if (newPos > BUFFER_SIZE)
        newPos = BUFFER_SIZE;
    if (newPos < 0)
        newPos = 0;
    file->f_pos = newPos;
    printk("New File R / W Ptr %d\n", (int)file->f_pos);
    return file->f_pos;
}

module_init(init_hello); //  모듈 로딩시(insmod) 해당 함수 호출
module_exit(exit_hello); //  모듈 제거시(rmmod) 해당 함수 호출
MODULE_LICENSE("GPL");