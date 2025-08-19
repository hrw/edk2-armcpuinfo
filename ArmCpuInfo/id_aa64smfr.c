/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "common.h"

/**
  Handle ID_AA64SMFR0_EL1 system register.

  @param[in] Aa64Smfr0,  value of ID_AA64SMFR0_EL1 system register
**/
VOID
HandleAa64Smfr0 (
  CONST UINT64  Aa64Smfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "SMFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "   63";
  Name  = "FA64";
  Value = (Aa64Smfr0 >> 63) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_FA64 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_FA64 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 62:61 reserved

  Bits  = "   60";
  Name  = "LUTv2";
  Value = (Aa64Smfr0 >> 60) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_LUTv2 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_LUTv2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "SMEver";
  Value = (Aa64Smfr0 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Mandatory SME instructions are implemented.";
      break;
    case b0001:
      Description = "FEAT_SME2 implemented.";
      break;
    case b0010:
      Description = "FEAT_SME2p1 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "I16I64";
  Value = (Aa64Smfr0 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SME_I16I64 not implemented";
      break;
    case b1111:
      Description = "FEAT_SME_I16I64 implemented";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 51:49 reserved

  Bits  = "   48";
  Name  = "F64F64";
  Value = (Aa64Smfr0 >> 48) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_F64F64 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_F64F64 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "I16I32";
  Value = (Aa64Smfr0 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "SME2 I16I32 not implemented.";
      break;
    case b0101:
      Description = "SME2 I16I32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   43";
  Name  = "B16B16";
  Value = (Aa64Smfr0 >> 43) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_B16B16 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_B16B16 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   42";
  Name  = "F16F16";
  Value = (Aa64Smfr0 >> 42) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_F16F16 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_F16F16 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   41";
  Name  = "F8F16";
  Value = (Aa64Smfr0 >> 41) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_F8F16 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_F8F16 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   40";
  Name  = "F8F32";
  Value = (Aa64Smfr0 >> 40) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SME_F8F32 not implemented.";
      break;
    case 1:
      Description = "FEAT_SME_F8F32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Name  = "I8I32";
  Value = (Aa64Smfr0 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "SME I8I32 not implemented.";
      break;
    case b1111:
      Description = "SME I8I32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   35";
  Name  = "F16F32";
  Value = (Aa64Smfr0 >> 35) & 0x1;
  switch (Value) {
    case 0:
      Description = "SME F16F32 not implemented.";
      break;
    case 1:
      Description = "SME F16F32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   34";
  Name  = "B16F32";
  Value = (Aa64Smfr0 >> 34) & 0x1;
  switch (Value) {
    case 0:
      Description = "SME B16F32 not implemented.";
      break;
    case 1:
      Description = "SME B16F32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   33";
  Name  = "BI32I32";
  Value = (Aa64Smfr0 >> 33) & 0x1;
  switch (Value) {
    case 0:
      Description = "SME BI32I32 not implemented.";
      break;
    case 1:
      Description = "SME BI32I32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   32";
  Name  = "F32F32";
  Value = (Aa64Smfr0 >> 32) & 0x1;
  switch (Value) {
    case 0:
      Description = "SME F32F32 not implemented.";
      break;
    case 1:
      Description = "SME F32F32 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 31 reserved

  Bits  = "   30";
  Name  = "SF8FMA";
  Value = (Aa64Smfr0 >> 30) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SSVE_FP8FMA not implemented.";
      break;
    case 1:
      Description = "FEAT_SSVE_FP8FMA implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   29";
  Name  = "SF8DP4";
  Value = (Aa64Smfr0 >> 29) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SSVE_FP8DOT4 not implemented.";
      break;
    case 1:
      Description = "FEAT_SSVE_FP8DOT4 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   28";
  Name  = "SF8DP2";
  Value = (Aa64Smfr0 >> 30) & 0x1;
  switch (Value) {
    case 0:
      Description = "FEAT_SSVE_FP8DOT2 not implemented.";
      break;
    case 1:
      Description = "FEAT_SSVE_FP8DOT2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 27:0 reserved
}


