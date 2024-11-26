/** @file
  Application to present AArch64 cpu information.

  Based on ARM DDI 0487J.a. Update this information when the
  app is updated with features from subsequent releases.

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/UefiLib.h>
#include <Library/ArmLib/AArch64/AArch64Lib.h>
#include "AArch64LibExtra.h"

UINTN
EFIAPI
ArmReadIdAA64Smfr0 (
  VOID
  );

UINTN
EFIAPI
ArmReadIdAA64Zfr0 (
  VOID
  );
#include "common.h"
#include "id_aa64.h"

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
    case b1111:
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

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINT64  Aa64Afr0;
  UINT64  Aa64Afr1;
  UINT64  Aa64Dfr0;
  UINT64  Aa64Dfr1;
  UINT64  Aa64Fpfr0;
  UINT64  Aa64Isar0;
  UINT64  Aa64Isar1;
  UINT64  Aa64Isar2;
  UINT64  Aa64Isar3;
  UINT64  Aa64Mmfr0;
  UINT64  Aa64Mmfr1;
  UINT64  Aa64Mmfr2;
  UINT64  Aa64Mmfr3;
  UINT64  Aa64Mmfr4;
  UINT64  Aa64Pfr0;
  UINT64  Aa64Pfr1;
  UINT64  Aa64Pfr2;
  UINT64  Aa64Smfr0;
  UINT64  Aa64Zfr0;

  Aa64Afr0  = ArmReadIdAA64Afr0 ();
  Aa64Afr1  = ArmReadIdAA64Afr1 ();
  Aa64Dfr0  = ArmReadIdAA64Dfr0 ();
  Aa64Dfr1  = ArmReadIdAA64Dfr1 ();
  Aa64Fpfr0 = ArmReadIdAA64Fpfr0 ();
  Aa64Isar0 = ArmReadIdAA64Isar0 ();
  Aa64Isar1 = ArmReadIdAA64Isar1 ();
  Aa64Isar2 = ArmReadIdAA64Isar2 ();
  Aa64Isar3 = ArmReadIdAA64Isar3 ();
  Aa64Mmfr0 = ArmReadIdAA64Mmfr0 ();
  Aa64Mmfr1 = ArmReadIdAA64Mmfr1 ();
  Aa64Mmfr2 = ArmReadIdAA64Mmfr2 ();
  Aa64Mmfr3 = ArmReadIdAA64Mmfr3 ();
  Aa64Mmfr4 = ArmReadIdAA64Mmfr4 ();
  Aa64Pfr0  = ArmReadIdAA64Pfr0 ();
  Aa64Pfr1  = ArmReadIdAA64Pfr1 ();
  Aa64Pfr2  = ArmReadIdAA64Pfr2 ();
  Aa64Smfr0 = ArmReadIdAA64Smfr0 ();
  Aa64Zfr0  = ArmReadIdAA64Zfr0 ();

  AsciiPrint ("ArmCpuInfo v1.3.0\n");
  AsciiPrint ("\n");

  AsciiPrint ("ID_AA64AFR0_EL1  = 0x%016lx\n", Aa64Afr0);
  AsciiPrint ("ID_AA64AFR1_EL1  = 0x%016lx\n", Aa64Afr1);
  AsciiPrint ("ID_AA64DFR0_EL1  = 0x%016lx\n", Aa64Dfr0);
  AsciiPrint ("ID_AA64DFR1_EL1  = 0x%016lx\n", Aa64Dfr1);
  AsciiPrint ("ID_AA64FPFR0_EL1 = 0x%016lx\n", Aa64Fpfr0);
  AsciiPrint ("ID_AA64ISAR0_EL1 = 0x%016lx\n", Aa64Isar0);
  AsciiPrint ("ID_AA64ISAR1_EL1 = 0x%016lx\n", Aa64Isar1);
  AsciiPrint ("ID_AA64ISAR2_EL1 = 0x%016lx\n", Aa64Isar2);
  AsciiPrint ("ID_AA64ISAR3_EL1 = 0x%016lx\n", Aa64Isar3);
  AsciiPrint ("ID_AA64MMFR0_EL1 = 0x%016lx\n", Aa64Mmfr0);
  AsciiPrint ("ID_AA64MMFR1_EL1 = 0x%016lx\n", Aa64Mmfr1);
  AsciiPrint ("ID_AA64MMFR2_EL1 = 0x%016lx\n", Aa64Mmfr2);
  AsciiPrint ("ID_AA64MMFR3_EL1 = 0x%016lx\n", Aa64Mmfr3);
  AsciiPrint ("ID_AA64MMFR4_EL1 = 0x%016lx\n", Aa64Mmfr4);
  AsciiPrint ("ID_AA64PFR0_EL1  = 0x%016lx\n", Aa64Pfr0);
  AsciiPrint ("ID_AA64PFR1_EL1  = 0x%016lx\n", Aa64Pfr1);
  AsciiPrint ("ID_AA64PFR2_EL1  = 0x%016lx\n", Aa64Pfr2);
  AsciiPrint ("ID_AA64SMFR0_EL1 = 0x%016lx\n", Aa64Smfr0);
  AsciiPrint ("ID_AA64ZFR0_EL1  = 0x%016lx\n", Aa64Zfr0);
  AsciiPrint ("\n");

  PrintText ("Reg", "Name", "Bits", "Value", "Feature");
  PrintSpacer ();

  HandleAa64Mmfr0 (Aa64Mmfr0);
  PrintSpacer ();

  if (Aa64Mmfr1) {
    HandleAa64Mmfr1 (Aa64Mmfr1, Aa64Pfr0);
    PrintSpacer ();
  }

  if (Aa64Mmfr2) {
    HandleAa64Mmfr2 (Aa64Mmfr2);
    PrintSpacer ();
  }

  HandleAa64Pfr0 (Aa64Pfr0, Aa64Pfr1);
  PrintSpacer ();

  if (Aa64Pfr1) {
    HandleAa64Pfr1 (Aa64Pfr1);
    PrintSpacer ();
  }

  HandleAa64Isar0 (Aa64Isar0);
  PrintSpacer ();

  if (Aa64Isar1) {
    HandleAa64Isar1 (Aa64Isar1);
    PrintSpacer ();
  }

  if (Aa64Isar2) {
    HandleAa64Isar2 (Aa64Isar2);
    PrintSpacer ();
  }

  HandleAa64Dfr0 (Aa64Dfr0);
  PrintSpacer ();

  if (Aa64Zfr0) {
    HandleAa64Zfr0 (Aa64Zfr0);
    PrintSpacer ();
  }

  if (Aa64Smfr0) {
    HandleAa64Smfr0 (Aa64Smfr0);
    PrintSpacer ();
  }

  if (Aa64Afr0 | Aa64Afr1 | Aa64Dfr1 | Aa64Mmfr3 | Aa64Mmfr4 | Aa64Isar3 | Aa64Pfr2) {
    AsciiPrint (
      "\n"
      "Your system has something this app does not handle. Please contact author.\n"
      "Open issue at https://github.com/hrw/edk2-armcpuinfo/issues and copy output.\n"
      "\n"
    );
  }

  return EFI_SUCCESS;
}
