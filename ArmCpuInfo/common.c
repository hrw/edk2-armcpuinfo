/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/UefiLib.h>
#include "common.h"

#define MAX_DESC_LENGTH 60

/**
  Print formatted table line.

  Values can be empty if only new description line is needed.

  @param[in] Field       name of system register
  @param[in] Bits        bits of system register
  @param[in] Value       value of those bits
  @param[in] Description meaning of value
**/
VOID
PrintText (
  CONST CHAR8  *Field,
  CONST CHAR8  *Name,
  CONST CHAR8  *Bits,
  CONST CHAR8  *Value,
  CONST CHAR8  *Description
  )
{
  AsciiPrint ("%-5a | %-12a | %5a | %5a | %a\n", Field, Name, Bits, Value, Description);
}


UINTN
AsciiStrStrPos (
  CONST CHAR8 *String,
  CONST CHAR8 *SubString,
  UINTN MaxPos
  )
{
  CHAR8* StrStrPos = AsciiStrStr(String, SubString) + 1;
  UINTN PrevPos = 0;

  do {
    StrStrPos = AsciiStrStr(StrStrPos, SubString) + 1;

    if (StrStrPos - String < MaxPos) {
      PrevPos = StrStrPos - String;
    }

  } while (MaxPos > StrStrPos - String);

  return PrevPos;
}

/**
  Print formatted table line with value printed in binary.

  @param[in] Field       name of system register
  @param[in] Bits        bits of system register
  @param[in] Value       value of those bits
  @param[in] Description meaning of value
**/
VOID
PrintValues (
  CONST CHAR8  *Field,
  CONST CHAR8  *Name,
  CONST CHAR8  *Bits,
  CONST UINT8  Value,
  CONST CHAR8  *Description
  )
{
  STATIC CONST CHAR8  Nibbles[][5] = {
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
  };

  UINTN Length;

  Length = AsciiStrLen(Description);

  if (Length > MAX_DESC_LENGTH) {
     CHAR8 Buffer[MAX_DESC_LENGTH + 1];

     UINTN SpacePos =  AsciiStrStrPos(Description, " ", MAX_DESC_LENGTH);

     AsciiStrnCpyS(Buffer, MAX_DESC_LENGTH + 1, Description, SpacePos);

	PrintText (Field, Name, Bits, Nibbles[Value & 0xf], Buffer);
	PrintText ("",    "",   "",   "",                   Description + SpacePos);
  }
  else {
	PrintText (Field, Name, Bits, Nibbles[Value & 0xf], Description);
  }
}

/**
  Print spacer for results table.
**/
VOID
PrintSpacer (
  VOID
  )
{
  AsciiPrint ("------|--------------|-------|-------|----------------------------------------------\n");
}
