PHONY :=  hello 

hello:
	gcc -E hello.c -o hello.i
	gcc -S hello.i -o hello.S
	gcc -c hello.S -o hello.o
	gcc -o hello hello.o

PHONY += stage1

stage1:
	gcc -E hello.c -o hello.i

PHONY += stage2
stage2:
	gcc -S hello.i -o hello.S

PHONY += stage5
stage3:
	gcc -c hello.S -o hello.o

PHONY += stage4
stage4:
	gcc -o hello hello.o

PHONY += all
all:
	gcc -o hello hello.c

PHONY += clear
clean:
	rm -rf hello hello.i hello.S hello.o

.PHONY: $(PHONY)


