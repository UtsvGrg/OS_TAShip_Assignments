#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(twodcopy,float**,src,float**,dest,int,nrow,int,ncol){
	float buffer[20][20];
	if(__copy_from_user(buffer,src,sizeof(float)*(nrow)*(ncol))){
		return -EFAULT;
	}
	else{
		printk("__copy_from_user - success");
	}
	if(__copy_to_user(dest,buffer,sizeof(float)*(nrow)*(ncol))){
		return -EFAULT;
	}
	else{
		printk("__copy_to_user - success");
	}
	return 0;
}
