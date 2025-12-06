CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
LDFLAGS = -ldl

TARGET = dynamic_loader
LIBRARY = liblist.so

.PHONY: all clean run debug

all: $(LIBRARY) $(TARGET)

$(LIBRARY): list.c list.h
	$(CC) $(CFLAGS) -shared -o $(LIBRARY) list.c

$(TARGET): dynamic_loader.c
	$(CC) $(CFLAGS) -o $(TARGET) dynamic_loader.c $(LDFLAGS)

run: all
	./$(TARGET)

# Отладочный запуск с подробной информацией
debug: all
	@echo "=== Starting debug session ==="
	@echo "Run these commands in another terminal to monitor:"
	@echo "watch -n 1 'cat /proc/\$$(pidof $(TARGET))/maps | grep liblist'"
	@echo ""
	./$(TARGET)

# Мониторинг в реальном времени
monitor: all
	@echo "Starting program and monitoring..."
	@./$(TARGET) &
	@sleep 1
	@echo "=== Monitoring memory maps ==="
	@while true; do \
		PID=$$(pidof $(TARGET)); \
		if [ -z "$$PID" ]; then break; fi; \
		echo "=== Current memory map ==="; \
		cat /proc/$$PID/maps | grep liblist || echo "Library not loaded"; \
		echo "==========================="; \
		sleep 2; \
	done

clean:
	rm -f $(TARGET) $(LIBRARY) *.o

# Проверка зависимостей
check:
	ldd $(TARGET)
	nm -D $(LIBRARY)