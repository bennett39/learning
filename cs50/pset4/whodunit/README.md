# Questions

## What's `stdint.h`?

A header file that allows programmers to specify the exact width on memory of a piece of data, in this case, integers.

Allows you to set minimum and maximum values for memory storage. Also makes the program more portable b/c it's now standardized.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To tell the computer how much memory a specific data type occupies.

`uint` signifies unsigned integer. It means that this data type will definitely store positive values.
Just `int` is a signed integer. It can store negative values, but overflows in half the time of a uint when counting up from zero.

1 byte uint can count from 0 to 256.
1 byte int can count from -128 to 128.

Bitmaps (thanks to Microsoft) use `BYTE`, `DWORD`, `LONG`, and `WORD` in the file header, so it's easier to define them and keep using them.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE` = 8 bits, 1 byte
`DWORD` = 32 bits, 4 bytes
`LONG` = 32 bits, 4 bytes
`WORD` = 16 bits, 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM - so, `0x42` or `0b1000010`

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the total file size in bytes, including header
`biSize` is the number of bytes in the structure (image) itself

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, then the file is a top-down device independent bitmap (DIB).
This means that the first byte after the header is the top left pixel in the image.
The program should create the image from left to right, top-down.

If `biHeight` is positive, then the file is a bottom-up DIB
The first byte is the bottom left
Build order is left to right, bottom-up.

(Bottom-up DIBs can be compressed. Top-down cannot.)

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Because the user didn't provide an in file or out file in the command line.

## Why is the third argument to `fread` always `1` in our code?

We want it to read the size of the `BMPFILEHEADER` once, then read the size of the `BMPINFOHEADER` once.

Using 2, for instance, would tell the computer to read a chunk of memory the size of `BMPFILEHEADER` twice.
`BMPFILEHEADER * 2` = `14 bytes * 2` = Read 28 bytes into file <= WRONG
We only want it to read 14 bytes.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3 bytes of `0x00`, so `0x000000`.

## What does `fseek` do?

`fseek` jumps over parts of a file you want to ignore.
More formally, it sets the file position, given an offset and starting point.

SYNTAX: `fseek(stream, offset, whence);`
OUR EXAMPLE: `fseek(inptr, padding, SEEK_CUR);`

`inptr` - the file we're currently working on, known as the "stream" in fseek parlance
`padding` - a variable we previously defined, indicating the length in bytes to offset
`SEEK_CUR` - from whence should the offset begin? "SEEK_CUR" means the current file position

## What is `SEEK_CUR`?

See above. A predefinted constant that indicates the current file position.

Other options:
`SEEK_SET` = the beginning of the file
`SEEK_END` = the end of the file

## Whodunit?

It was Professor Plum with the candlestick in the library
