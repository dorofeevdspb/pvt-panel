#! /bin/bash
avrdude -c usbasp -p m328p -U flash:w:.pio/build/uno/firmware.hex:i
