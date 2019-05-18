target = test_lru
src += $(wildcard *.c)
obj += $(patsubst %.c,%.o,$(src))

define BuildTarget
$1: $(obj)
	gcc -o $1 $(obj)
endef

all: $(target)

$(eval $(call BuildTarget,$(target)))

clean:
	rm -rf *.o $(target)

.PHONY: all clean
