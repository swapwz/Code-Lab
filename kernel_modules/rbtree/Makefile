LINUX_BASEDIR ?= /lib/modules/`uname -r`/build

obj-m := rbtest.o
rbtest-objs := rbtree.o

all:
	$(MAKE) -C $(LINUX_BASEDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(LINUX_BASEDIR) SUBDIRS=$(PWD) clean

.PHONY: all clean
