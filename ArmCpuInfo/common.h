/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef ACI_COMMON_H
#define ACI_COMMON_H

// We cannot assume GCC extensions to be present so let use
// binary numbers via enum.
// Arm ARM uses binary numbers so this way it is more readable.
enum {
  b0000,
  b0001,
  b0010,
  b0011,
  b0100,
  b0101,
  b0110,
  b0111,
  b1000,
  b1001,
  b1010,
  b1011,
  b1100,
  b1101,
  b1110,
  b1111
};

VOID
PrintText (
  CONST CHAR8  *Field,
  CONST CHAR8  *Name,
  CONST CHAR8  *Bits,
  CONST CHAR8  *Value,
  CONST CHAR8  *Description
  );

UINTN
AsciiStrStrPos (
  CONST CHAR8 *String,
  CONST CHAR8 *SubString,
  UINTN MaxPos
  );

VOID
PrintValues (
  CONST CHAR8  *Field,
  CONST CHAR8  *Name,
  CONST CHAR8  *Bits,
  CONST UINT8  Value,
  CONST CHAR8  *Description
  );


#endif
