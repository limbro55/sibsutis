CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
LDFLAGS = -ldl

all: lab5_program liblist.so elf_analyzer dynamic_loader

# Лабораторная 5 - библиотека и программа
liblist.so: list.c list.h
	$(CC) $(CFLAGS) -shared -o liblist.so list.c

lab5_program: main.c liblist.so
	$(CC) $(CFLAGS) -o list.c main.c -L. -llist -Wl,-rpath,.

# Лабораторная 6 - ELF анализатор
elf_analyzer: elf_analyzer.c
	$(CC) $(CFLAGS) -o elf_analyzer elf_analyzer.c

# Лабораторная 7 - динамическая загрузка
dynamic_loader: dynamic_loader.c liblist.so
	$(CC) $(CFLAGS) -o dynamic_loader dynamic_loader.c $(LDFLAGS)

# Запуск программ
run5: program
	./program

run6: elf_analyzer liblist.so
	./elf_analyzer liblist.so

run7: dynamic_loader
	dynamic_loader

# Тестирование
test: run5 run6
	@echo "=== Testing Lab7 ==="
	@echo "Run manually: ./dynamic_loader"

# Мониторинг памяти для lab7
monitor:
	@echo "Monitoring memory maps:"
	@while true; do \
		PID=$$(pidof dynamic_loader); \
		if [ -z "$$PID" ]; then echo "Process not running"; break; fi; \
		echo "=== PID: $$PID ==="; \
		cat /proc/$$PID/maps | grep liblist || echo "Library not loaded"; \
		sleep 2; \
	done

# Очистка
clean:
	rm -f lab5_program elf_analyzer dynamic_loader liblist.so *.o

.PHONY: all run5 run6 run7 test monitor clean