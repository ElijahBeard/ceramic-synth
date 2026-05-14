# Ceramic Synth
Multidisciplinary electronic audio generation project created by Julia Weber and Elijah Beard. This project combines the arts of ceramics and electronics. By using the ceramic material as a natural insulator for electronic traces, ceramic synth operates as a simple circuit board that runs a stripped down MCU.

To deploy this system on your own embedded system, run `setup.sh` to burn the arduino bootloader to your MCU and install the mozzi library. Then, run `upload.sh` to compile and upload the ceramic-core to the MCU. Check the [Mozzi Official Site](https://sensorium.github.io/Mozzi/#supported-boards-output-modes-and-default-pins) for compatibility and audio output modes on several different chipsets.

## Form
The original clay form before firing included an amplifier and audio input circuit which was meant to include piezoelectric components as microphones for interactive audio feedback. These prototype forms shown below have been split into a second bread-board style form and an MCU unit form.

## Hardware
The project is based on an ATMEGA328P-PU (DIP 28). . This MCU was chosen for it's low power operation, mozzi compatability and large DIP package size. Using SMD components on this project was not possible due to the shrinkage of clay not allowing for the level of precision required for `> 1mm` width pads.
<div align="center">
<img width="450" alt="Screenshot 2026-05-14 at 10 09 47 AM" src="https://github.com/user-attachments/assets/5e0b3c83-dcf6-4365-8ec1-01f0dc7cba61" />
<p>Ceramic Synth Schematic</p>
</div>

The circuit is based on many designs for a minimal atmega328p circuit. It features the bare essentials and nothing more. A pullup resistor, decoupling capacitor, external oscillator (which could be removed), SPI / I2C and an audio jack.

## Software
The MCU is loaded with the arduino bootloader managed by arduino-cli tools. Also on board is the [mozzi](https://sensorium.github.io/Mozzi/examples/) sound engine. Mozzi is a library that allows rapid prototyping for this type of project, please support the project on their site!

. . .
