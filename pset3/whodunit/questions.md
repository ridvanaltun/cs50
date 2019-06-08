# Questions

## What's `stdint.h`?

The library offers some fixed data types based on integer.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The integer data type in C language can be 2 or 4 bytes, depending on whether the operating system is 32 or 64 bits. Since the data types in this library occupy a fixed amount of memory, we can use the data types in the library to ensure that the program we write is running smoothly on different systems.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is 1 byte.
DWORD is 4 bytes.
LONG is 4 bytes.
WORD is 8 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII : BM
DEC   : 66 77
HEX   : 0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

biSize represents the number of bytes required by the BITMAPINFOHEADER structure.
bfSize represents the size, in bytes, of the bitmap file.

## What does it mean if `biHeight` is negative?

For uncompressed RGB bitmaps can be placed in memory two different orientations, bottom-up and top-down. If biHeight value is positive using orientation is bottom-up. if biHeight is negative using orientation is top-down.

If we use a positive value, the first byte in memory is the bottom-left pixel of the image.
If we use a negative value, the first byte in memory is the top-left pixel of the image.

Read More: https://docs.microsoft.com/en-us/windows/desktop/directshow/top-down-vs--bottom-up-dibs

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

We may not have permission to read the file.
The file may be corrupted.
The file path given in the argument may be incorrect.

## Why is the third argument to `fread` always `1` in our code?

The value "one" means read once. This way, we have more control over the program. For example, when you want to manipulate color on the picture, you can access every pixel so you can easily process the picture.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

With the fseek function, we can change the file pointer. We can go up or down in memory. With this function, we can easily access any data of the file.

## What is `SEEK_CUR`?

We use this definition in the fseek function. In short, it allows the fseek function to process from the current position of the file pointer.