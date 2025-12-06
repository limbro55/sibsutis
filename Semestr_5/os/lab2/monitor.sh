#!/bin/bash

# Запускаем программу в фоне
./dynamic_loader &
PID=$!

echo "Monitoring PID: $PID"
echo ""

# Мониторим изменения в maps
while ps -p $PID > /dev/null; do
    echo "=== $(date) ==="
    if grep -q "liblist" /proc/$PID/maps 2>/dev/null; then
        echo "Library LOADED in memory:"
        grep "liblist" /proc/$PID/maps
    else
        echo "Library NOT LOADED in memory"
    fi
    echo "========================"
    sleep 1
done

echo "Process finished"