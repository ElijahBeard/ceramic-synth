#!/usr/bin/env bash

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
arduino-cli board list
echo
read -p "Burn bootloader first? (y/n): " BURN

read -p "Enter serial port [/dev/cu.usbmodem1101]: " PORT
PORT=${PORT:-/dev/cu.usbmodem1101}

if [[ "$BURN" =~ ^[Yy]$ ]]; then
    echo "Burning bootloader..."
    arduino-cli burn-bootloader \
        -b arduino:avr:uno \
        --programmer arduinoasisp \
        -p "$PORT"

    echo "Bootloader burned successfully."
fi

echo "Updating Arduino core index..."
arduino-cli core update-index
if ! arduino-cli core list | grep -q "arduino:avr"; then
    echo "Installing Arduino AVR core..."
    arduino-cli core install arduino:avr
else
    echo "Arduino AVR core already installed."
fi

echo "Installing mozzi library..."
arduino-cli lib install mozzi