// 모듈형 문자 디바이스 드라이버(hello_drv.c) 및
// 응용프로그램 설계, 실행 순서 요약
//  PC에서
//  디바이스 드라이버 “hello_drv.c” 작성


//  Makefile 작성
//  Compile(make명령) 후, Target으로 ‘hello_drv.ko’ 를 전송 (scp, minicom, whatever)
//  키트에서
//  디바이스 노드 생성 (mknod)
//  디바이스 드라이브 적재 (insmod)
//  PC에서
//  응용프로그램 작성 (hello_test.c)
//  응용프로그램 컴파일 후, 실행 파일 (hello_test)을 타겟으로 전송
//  응용 프로그램 실행 (./hello_test

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>



#define HELLO_MAJOR_NUM 290
#define HELLO_NAME "hello"

static int hello_open(struct inode *node, struct file *pfile)
{
printk("hello_open enter\n");
return 0;
}

static ssize_t hello_read(struct file *pfile, char __user *pBuff, size_t size, loff_t *filepos)
{
char arrData[4] = {'1','2','3','4'};
printk("hello_read enter\n");
if ( size >= 4)
{
copy_to_user( pBuff, arrData, 4 );
//put_user (i, pBuff); //i 변수값을 pBuff 사용자 메모리값에 대입
return 4;
}
//pfile->f_flags 를 읽어보면 open시 줬던 옵션값을 읽힘: O_NONBLOCK 등
return 0;
}

static ssize_t hello_write(struct file *pfile, const char __user *pBuff, size_t size, loff_t *filepos) {
char arrData[4];
printk("hello_write enter\n");
if( size >= 4 )
{ copy_from_user ( arrData , pBuff , 4 );
//get_user ( i, pBuff ); //i변수에 pBuff의 값을 대입한다.
return 4; }
return 0;
}

static int hello_release(struct inode *node, struct file *pfile)
{ printk("hello_release enter\n");
return 0;
}

static const struct file_operations hello_fops = {
.owner = THIS_MODULE,
.open = hello_open,
.read = hello_read,
.write = hello_write,
.release = hello_release,
};

int flagRegisterSuccess = 0;

int __init init_hello(void)
{ int ret;
printk("Hello world.\n");
ret = register_chrdev(HELLO_MAJOR_NUM, HELLO_NAME, &hello_fops);
if ( ret < 0)
{ printk("Hello registr_chrdev fail\n");
return ret; }
flagRegisterSuccess = 1;
return 0;
}

void __exit exit_hello(void)
{ if ( flagRegisterSuccess)
{ flagRegisterSuccess = 0;
unregister_chrdev(HELLO_MAJOR_NUM, HELLO_NAME);
}
printk("Good-bye~ \n");
}

module_init(init_hello); //  모듈 로딩시(insmod) 해당 함수 호출
module_exit(exit_hello); //  모듈 제거시(rmmod) 해당 함수 호출
MODULE_LICENSE("GPL");