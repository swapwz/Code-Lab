target1 = test_atoi
src1 = atoi.c

target2 = test_longest_palindrome
src2 = longest_palindrome.c

all: $(target1) $(target2)

$(target1): $(src1)
	gcc -o $@ $<

$(target2): $(src2)
	gcc -o $@ $<
	
clean:
	rm -rf *.o $(target1) $(target2)

.PHONY: all clean
