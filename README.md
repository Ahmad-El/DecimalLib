# Decimal Value Type in C Language - README

## Introduction

The Decimal value type in C represents decimal numbers with a range from positive 79,228,162,514,264,337,593,543,950,335 to negative 79,228,162,514,264,337,593,543,950,335. The default value of a Decimal is 0. This data type is particularly suited for financial calculations that require a high precision of both integral and fractional digits, minimizing errors due to rounding.

## Decimal Number Representation

A decimal number in C is a floating-point value comprising a sign, a numeric value with digits ranging from 0 to 9, and a scaling factor indicating the position of a floating decimal point between the integral and fractional parts.

## Binary Representation

The binary representation of a Decimal value consists of:

- 1-bit sign
- 96-bit integer number
- A scaling factor used to divide the 96-bit integer, implicitly set to the number 10 raised to an exponent ranging from 0 to 28.

The binary representation follows the form: ((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue, and 2^96-1 is equal to MaxValue.

## Implementation Details

A Decimal number can be implemented as a four-element array of 32-bit signed integers (`int bits[4]`):

- `bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number, respectively.
- `bits[3]` contains the scale factor and sign, with specific bit assignments:
  - Bits 0 to 15 (lower word): Unused and must be zero.
  - Bits 16 to 23: Exponent between 0 and 28, indicating the power of 10 to divide the integer number.
  - Bits 24 to 30: Unused and must be zero.
  - Bit 31: Sign; 0 means positive, 1 means negative.

It's important to note that the bit representation differentiates between negative and positive zero. However, these values are considered equal in all operations.
