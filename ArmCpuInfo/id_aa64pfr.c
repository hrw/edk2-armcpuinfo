/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "common.h"

/**
  Handle ID_AA64PFR0_EL1 system register.

  @param[in] Aa64Pfr0,  value of ID_AA64PFR0_EL1 system register
  @param[in] Aa64Pfr1,  value of ID_AA64PFR1_EL1 system register
**/
VOID
HandleAa64Pfr0 (
  CONST UINT64  Aa64Pfr0,
  CONST UINT64  Aa64Pfr1
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "PFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "63:60";
  Name  = "CSV3";
  Value = (Aa64Pfr0 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_CSV3 not implemented.";
      break;
    case b0001:
      Description = "FEAT_CSV3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "CSV2";
  Value = (Aa64Pfr0 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Not disclosed whether FEAT_CSV2 is implemented.";
      break;
    case b0001:
      Description = "FEAT_CSV2 implemented.";
      break;
    case b0010:
      Description = "FEAT_CSV2_2 implemented.";
      break;
    case b0011:
      Description = "FEAT_CSV2_3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Name  = "CSV2_frac";
  if (Value == b0001) {
    if (((Aa64Pfr1 >> 32) & 0xf) == b0001 ) {
      PrintValues ("PRF1", Name, "35:32", b0001, "FEAT_CSV2_1p1 implemented.");
    }

    if (((Aa64Pfr1 >> 32) & 0xf) == b0010 ) {
      PrintValues ("PRF1", Name, "35:32", b0010, "FEAT_CSV2_1p2 implemented.");
    }
  }

  Bits  = "55:52";
  Name  = "RME";
  Value = (Aa64Pfr0 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RME not implemented";
      break;
    case b0001:
      Description = "FEAT_RME implemented";
      break;
    case b0010:
      Description = "FEAT_RME_GPC2 implemented";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "DIT";
  Value = (Aa64Pfr0 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_DIT not implemented.";
      break;
    case b0001:
      Description = "FEAT_DIT implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "AMU";
  Value = (Aa64Pfr0 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_AMU not implemented.";
      break;
    case b0001:
      Description = "FEAT_AMUv1 implemented.";
      break;
    case b0010:
      Description = "FEAT_AMUv1p1 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "MPAM";
  Value = (Aa64Pfr0 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      if (((Aa64Pfr1 >> 16) & 0xf) == b0000 ) {
        Description = "FEAT_MPAM not implemented.";
      }

      if (((Aa64Pfr1 >> 16) & 0xf) == b0001 ) {
        Description = "FEAT_MPAM v0.1 implemented.";
      }

      break;
    case b0001:
      if (((Aa64Pfr1 >> 16) & 0xf) == b0000 ) {
        Description = "FEAT_MPAM v1.0 implemented.";
      }

      if (((Aa64Pfr1 >> 16) & 0xf) == b0001 ) {
        Description = "FEAT_MPAM v1.1 implemented.";
      }

      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SEL2";
  Value = (Aa64Pfr0 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Secure EL2 not implemented.";
      break;
    case b0001:
      Description = "Secure EL2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SVE";
  Value = (Aa64Pfr0 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SVE not implemented.";
      break;
    case b0001:
      Description = "FEAT_SVE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "RAS";
  Value = (Aa64Pfr0 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RAS not implemented.";
      break;
    case b0001:
      Description = "FEAT_RAS implemented.";
      break;
    case b0010:
      Description = "FEAT_RASv1p1 implemented.";
      // b0010 FEAT_RASv1p1 implemented and, if EL3 is implemented, FEAT_DoubleFault implemented.
      if ((((Aa64Pfr0 >> 12) & 0xf) == b0001) ||
          (((Aa64Pfr0 >> 12) & 0xf) == b0010))
      {
        Description = "FEAT_RASv1p1 implemented. FEAT_DoubleFault implemented.";
      }

      break;
    case b0011:
      Description = "FEAT_RASv2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value == b0001) {
    if (((Aa64Pfr1 >> 12) & 0xf) == b0001 ) {
      PrintValues ("PRF1", Name, "15:12", b0001, "FEAT_RASv1p1 implemented.");
    }
  }

  Bits  = "27:24";
  Name  = "GIC";
  Value = (Aa64Pfr0 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "System registers of GIC CPU not implemented.";
      break;
    case b0001:
      Description = "System registers to versions 3.0/4.0 of GIC CPU implemented.";
      break;
    case b0011:
      Description = "System registers to versions 4.1 of GIC CPU implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "AdvSIMD";
  Value = (Aa64Pfr0 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Advanced SIMD implemented.";
      break;
    case b0001:
      Description = "Advanced SIMD with half precision support (FEAT_FP16).";
      break;
    case b1111:
      Description = "Advanced SIMD not implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "FP";
  Value = (Aa64Pfr0 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Floating-point implemented.";
      break;
    case b0001:
      Description = "Floating-point with half-precision support (FEAT_FP16).";
      break;
    case b1111:
      Description = "Floating-point not implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "EL3";
  Value = (Aa64Pfr0 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "EL3 not implemented.";
      break;
    case b0001:
      Description = "EL3 in AArch64 only";
      break;
    case b0010:
      Description = "EL3 in AArch64 and AArch32";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "EL2";
  Value = (Aa64Pfr0 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "EL2 not implemented.";
      break;
    case b0001:
      Description = "EL2 in AArch64 only";
      break;
    case b0010:
      Description = "EL2 in AArch64 and AArch32";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "EL1";
  Value = (Aa64Pfr0 >>  4) & 0xf;
  switch (Value) {
    case b0001:
      Description = "EL1 in AArch64 only";
      break;
    case b0010:
      Description = "EL1 in AArch64 and AArch32";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "EL0";
  Value = Aa64Pfr0 & 0xf;
  switch (Value) {
    case b0001:
      Description = "EL0 in AArch64 only";
      break;
    case b0010:
      Description = "EL0 in AArch64 and AArch32";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}

/**
  Handle ID_AA64PFR1_EL1 system register.

  @param[in] Aa64Pfr1  value of ID_AA64PFR1_EL1 system register
**/
VOID
HandleAa64Pfr1 (
  CONST UINT64  Aa64Pfr1
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "PFR1";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "63:60";
  Name  = "PFAR";
  Value = (Aa64Pfr1 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PFAR not implemented.";
      break;
    case b0001:
      Description = "FEAT_PFAR implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "DF2";
  Value = (Aa64Pfr1 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_DoubleFault2 not implemented.";
      break;
    case b0001:
      Description = "FEAT_DoubleFault2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "MTEX";
  Value = (Aa64Pfr1 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Canonical Tag checking and Memory tagging with Address tagging disabled are not supported.";
      break;
    case b0001:
      Description = "FEAT_MTE_NO_ADDRESS_TAGS and FEAT_MTE_CANONICAL_TAG implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "THE";
  Value = (Aa64Pfr1 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_THE not implemented.";
      break;
    case b0001:
      Description = "FEAT_THE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "GCS";
  Value = (Aa64Pfr1 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_GCS not implemented.";
      break;
    case b0001:
      Description = "FEAT_GCS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "MTE_frac";
  Value = (Aa64Pfr1 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_MTE_ASYNC implemented.";
      break;
    case b1111:
      Description = "FEAT_MTE_ASYNC not implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "NMI";
  Value = (Aa64Pfr1 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_NMI not implemented.";
      break;
    case b0001:
      Description = "FEAT_NMI implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 35:32 is CSV2_frac (shown with PFR0)

  Bits  = "31:28";
  Name  = "RNDR_trap";
  Value = (Aa64Pfr1 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RNG_TRAP not implemented.";
      break;
    case b0001:
      Description = "FEAT_RNG_TRAP implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "SME";
  Value = (Aa64Pfr1 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SME not implemented.";
      break;
    case b0001:
      Description = "FEAT_SME implemented.";
      break;
    case b0010:
      Description = "FEAT_SME2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 23:20 is reserved
  // 19:16 is MPAM_frac (shown with PFR0)
  // 15:12 is RAS_frac (shown with PFR0)

  Bits  = "11:8 ";
  Name  = "MTE";
  Value = (Aa64Pfr1 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_MTE not implemented.";
      break;
    case b0001:
      Description = "FEAT_MTE implemented.";
      break;
    case b0010:
      Description = "FEAT_MTE2 implemented.";
      break;
    case b0011:
      Description = "FEAT_MTE3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "SSBS";
  Value = (Aa64Pfr1 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SSBS not implemented.";
      break;
    case b0001:
      Description = "FEAT_SSBS implemented.";
      break;
    case b0010:
      Description = "FEAT_SSBS2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "BT";
  Value = Aa64Pfr1 & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_BTI not implemented.";
      break;
    case b0001:
      Description = "FEAT_BTI implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}


