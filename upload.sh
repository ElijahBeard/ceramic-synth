#!/usr/bin/env bash

set -e

BOARD="arduino:avr:uno"
PORT="/dev/cu.usbmodem1101"
SKETCH="ceramic-core"

read -p "Enter serial port [/dev/cu.usbmodem1101]: " PORT
PORT=${PORT:-/dev/cu.usbmodem1101}

echo "Compiling ceramic core..."
arduino-cli compile -b "$BOARD" "$SKETCH"
echo
echo "Compilation successful."
echo
echo "Uploading sketch..."
echo
arduino-cli upload -p "$PORT" -b "$BOARD" "$SKETCH" -v
echo
echo "Upload completed successfully."