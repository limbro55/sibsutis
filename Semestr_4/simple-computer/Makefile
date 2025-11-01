TARGET = console/test.out

.PHONY: all
all: $(TARGET)

mySimpleComputer/libmySimpleComputer.a: $(wildcard mySimpleComputer/sc_*.c)
	$(MAKE) -C mySimpleComputer

myTerm/libmyTerm.a: $(wildcard myTerm/mt_*.c)
	$(MAKE) -C myTerm

myBigChars/libmyBigChars.a: $(wildcard myBigChars/bc_*.c)
	$(MAKE) -C myBigChars

myReadKey/libmyReadKey.a: $(wildcard myReadKey/rk_*.c)
	$(MAKE) -C myReadKey

myCuAlu/libmyCuAlu.a: $(wildcard myCuAlu/ca_*.c)
	$(MAKE) -C myCuAlu

myMemoryController/libmyMemoryController.a: $(wildcard myMemoryController/mc_*.c)
	$(MAKE) -C myMemoryController

$(TARGET): $(wildcard console/*.c) mySimpleComputer/libmySimpleComputer.a myTerm/libmyTerm.a \
																	 myBigChars/libmyBigChars.a myReadKey/libmyReadKey.a myCuAlu/libmyCuAlu.a \
																	 myMemoryController/libmyMemoryController.a
	$(MAKE) -B -C console
	$(MAKE) -C simple-assembler

.PHONY: run
run:
	$(MAKE) $@ -C console

.PHONY: clean
clean:
	$(MAKE) $@ -C console
	$(MAKE) $@ -C simple-assembler
	$(MAKE) $@ -C myMemoryController
	$(MAKE) $@ -C mySimpleComputer
	$(MAKE) $@ -C myTerm
	$(MAKE) $@ -C myBigChars
	$(MAKE) $@ -C myReadKey
	$(MAKE) $@ -C myCuAlu

.PHONY: rebuild
rebuild: clean all