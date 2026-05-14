#!/usr/bin/env bash

# This script will 
# 1. optionally burn bootloader
# 2. compile ceramic-core
# 3. upload program to MCU

set -e

BOARD="arduino:avr:uno"
SKETCH="ceramic-core"

if ! command -v arduino-cli &> /dev/null; then
    echo "ERROR: arduino-cli is not installed."
    echo
    echo "Install it from:"
    echo "https://arduino.github.io/arduino-cli/latest/installation/"
    exit 1
fi

echo
read -p "Burn bootloader first? (y/N): " BURN

if [[ "$BURN" =~ ^[Yy]$ ]]; then
    echo "Burning bootloader..."
    arduino-cli burn-bootloader \
        -b arduino:avr:uno \
        --programmer arduinoasisp \
        -p "$PORT"

    echo "Bootloader burned successfully."
fi

echo "[1/5] Updating Arduino core index..."
arduino-cli core update-index
if ! arduino-cli core list | grep -q "arduino:avr"; then
    echo "[2/5] Installing Arduino AVR core..."
    arduino-cli core install arduino:avr
else
    echo "[2/5] Arduino AVR core already installed."
fi
echo

read -p "Enter serial port [/dev/cu.usbmodem1101]: " PORT
PORT=${PORT:-/dev/cu.usbmodem1101}

echo "[3/5] Compiling ceramic core..."
arduino-cli compile -b "$BOARD" "$SKETCH"
echo
echo "Compilation successful."
echo
echo "[4/5] Uploading sketch..."
arduino-cli upload -p "$PORT" -b "$BOARD" "$SKETCH" -v
echo
echo "[5/5] Done!"
echo "Upload completed successfully."