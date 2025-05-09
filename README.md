# WAV Audio Processor in C

This is a C program for basic WAV audio file manipulation. It supports:

- **Cropping**: Cutting a section from a WAV file based on a start and end time.
- **Reversing**: Reversing the audio samples of a WAV file to play backward.

The program directly manipulates the PCM data of WAV files with proper handling of headers.

## Project Info

This project was developed as part of a **group assignment** for a university course. It demonstrates low-level audio file processing using the C programming language.

## Features

- Works with standard uncompressed PCM `.wav` files (e.g., 16-bit, 44.1kHz).
- Preserves WAV headers after transformation.
- Outputs new WAV files with the selected operation applied.

## Usage

The program is run from the command line and takes arguments for the input file, operation, and any required parameters.

### Example Commands

**Crop a WAV file between 5 and 10 seconds:**
```bash
./wav_processor crop input.wav output.wav 5 10
```

# Compilation

## Option 1: Using **gcc** directly
```bash
gcc -o main wav_processor.c
```

## Option 2: Using a **Makefile**
```bash
make
```
