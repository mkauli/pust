obj-m += pust.o

KDIR := $(PUST_KDIR)

all:
		make -C $(KDIR) M=$(PWD) modules

clean:
		make -C $(KDIR) M=$(PWD) clean
