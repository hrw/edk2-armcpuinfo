/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "common.h"

/**
  Handle ID_AA64ZFR0_EL1 system register.

  @param[in] Aa64Zfr0,  value of ID_AA64ZFR0_EL1 system register
**/
VOID
HandleAa64Zfr0 (
  CONST UINT64  Aa64Zfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ZFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  // 63:60 reserved

  Bits  = "59:56";
  Name  = "F64MM";
  Value = (Aa64Zfr0 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_F64MM SVE not implemented";
      break;
    case b0001:
      Description = "FEAT_F64MM SVE implemented";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "F32MM";
  Value = (Aa64Zfr0 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_F32MM SVE not implemented";
      break;
    case b0001:
      Description = "FEAT_F32MM SVE implemented";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 51:48 reserved

  Bits  = "47:44";
  Name  = "I8MM";
  Value = (Aa64Zfr0 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_I8MM SVE not implemented.";
      break;
    case b0001:
      Description = "FEAT_I8MM SVE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "SM4";
  Value = (Aa64Zfr0 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE_SM4 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE_SM4 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 39:36 reserved

  Bits  = "35:32";
  Name  = "SHA3";
  Value = (Aa64Zfr0 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE_SHA3 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE_SHA3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 31:28 reserved

  Bits  = "27:24";
  Name  = "B16B16";
  Value = (Aa64Zfr0 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE_B16B16 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE_B16B16 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "BF16";
  Value = (Aa64Zfr0 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "SVE BFloat16 not implemented.";
      break;
    case b0001:
      Description = "FEAT_BF16 SVE implemented.";
      break;
    case b0010:
      Description = "FEAT_EBF16 SVE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "BitPerm";
  Value = (Aa64Zfr0 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE_BitPerm not implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE_BitPerm implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 15:8 reserved

  Bits  = "7:4 ";
  Name  = "AES";
  Value = (Aa64Zfr0 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE_AES not implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE_AES implemented.";
      break;
    case b0010:
      Description = "FEAT_SVE_AES and FEAT_SVE_PMULL128 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "SVEver";
  Value = Aa64Zfr0 & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE2 implemented.";
      break;
    case b0010:
      Description = "FEAT_SVE2p1 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}


