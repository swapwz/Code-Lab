subdirs := tree lru list math 

all:
	$(foreach subdir,$(subdirs),make -C $(subdir);)

clean:
	$(foreach subdir,$(subdirs),make -C $(subdir) clean;)

.PHONY: all clean

