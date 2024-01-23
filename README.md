# ATOMS3 Timer Clicker

This project works as a USB HID mouse on AtomS3 Lite and generates a click event every 10/30/60 seconds. LED on AtomS3 Lite shows mode and timing.

## Notes

This project sets USB interface HID after programming. Please press and hold the reset button until green LED lights up to program another project.

## Supported Hardware

* [ATOMS3 Lite](https://docs.m5stack.com/en/core/AtomS3%20Lite)

## Build Environment

* PlatformIO

## Dependencies

*	m5stack/M5AtomS3@^1.0.0
* m5stack/M5Unified@^0.1.12
*	fastled/FastLED@^3.6.0

## Motivation

I developed this project to control Canon EOS Utility which connected to DSLR wirelessly and took photos. This project enables timer-controlled shooting with live view. 

// Some Canon cameras have built-in timer-controlled shooting feature. Unfortunately, it does not work while live view is on.
