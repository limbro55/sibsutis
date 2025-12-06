CC = gcc
TARGET = elf_analyzer

.PHONY: all clean test

all: $(TARGET)

$(TARGET): elf_analyzer.c
	$(CC) $(CFLAGS) -o $(TARGET) elf_analyzer.c

liblist.so: list.c list.h
	$(CC) $(CFLAGS) -fPIC -shared -o liblist.so list.c

run: $(TARGET) liblist.so
	@echo "=== Testing with our library ==="
	./$(TARGET) liblist.so

clean:
	rm -f $(TARGET) liblist.so

# Анализ системных библиотек
test-libc: $(TARGET)
	./$(TARGET) /lib/x86_64-linux-gnu/libc.so.6

test-ld: $(TARGET)
	./$(TARGET) /lib64/ld-linux-x86-64.so.2