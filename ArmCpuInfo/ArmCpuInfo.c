/** @file
  Application to present AArch64 cpu information.

  Based on ARM DDI 0487J.a. Update this information when the
  app is updated with features from subsequent releases.

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/UefiLib.h>
#include <Library/ArmLib/AArch64/AArch64Lib.h>

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
  AsciiPrint ("%-5a | %-11a | %5a | %5a | %a\n", Field, Name, Bits, Value, Description);
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

  PrintText (Field, Name, Bits, Nibbles[Value & 0xf], Description);
}

/**
  Print spacer for results table.
**/
VOID
PrintSpacer (
  VOID
  )
{
  AsciiPrint ("------|-------------|-------|-------|----------------------------------------------\n");
}

/**
  Handle ID_AA64DFR0_EL1 system register.

  @param[in] Aa64Dfr0  value of ID_AA64DFR0_EL1 system register
**/
VOID
HandleAa64Dfr0 (
  CONST UINT64  Aa64Dfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "DFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "63:60";
  Name  = "HPMN0";
  Value = (Aa64Dfr0 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Setting MDCR_EL2.HPMN to zero has CONSTRAINED UNPREDICTABLE behavior.";
      break;
    case b0001:
      Description = "FEAT_HPMN0 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 59:56 reserved

  Bits  = "55:52";
  Name  = "BRBE";
  Value = (Aa64Dfr0 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_BRBE not implemented.";
      break;
    case b0001:
      Description = "FEAT_BRBE implemented.";
      break;
    case b0010:
      Description = "FEAT_BRBEv1p1 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "MTPMU";
  Value = (Aa64Dfr0 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_MTPMU not implemented.";
      break;
    case b0001:
      Description = "FEAT_MTPMU and FEAT_PMUv3 implemented.";
      break;
    case b1111:
      Description = "FEAT_MTPMU not implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "TraceBuffer";
  Value = (Aa64Dfr0 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TRBE not implemented.";
      break;
    case b0001:
      Description = "FEAT_TRBE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "TraceFilt";
  Value = (Aa64Dfr0 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TRF not implemented.";
      break;
    case b0001:
      Description = "FEAT_TRF implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "DoubleLock";
  Value = (Aa64Dfr0 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_DoubleLock implemented.";
      break;
    case b1111:
      Description = "FEAT_DoubleLock not implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "PMSVer";
  Value = (Aa64Dfr0 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SPE not implemented.";
      break;
    case b0001:
      Description = "FEAT_SPE implemented.";
      break;
    case b0010:
      Description = "FEAT_SPEv1p1 implemented.";
      break;
    case b0011:
      Description = "FEAT_SPEv1p2 implemented.";
      break;
    case b0100:
      Description = "FEAT_SPEv1p3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "CTX_CMPs";
  Value = (Aa64Dfr0 >> 28) & 0xf;
  switch (Value) {
    default:
      Description = "Number of breakpoints that are context-aware, minus 1.";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 27:24 reserved

  Bits  = "23:20";
  Name  = "WRPs";
  Value = (Aa64Dfr0 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "reserved";
      break;
    default:
      Description = "Number of watchpoints, minus 1.";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 19:16 reserved

  Bits  = "15:12";
  Name  = "BRPs";
  Value = (Aa64Dfr0 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "reserved";
      break;
    default:
      Description = "Number of breakpoints, minus 1.";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "PMUVer";
  Value = (Aa64Dfr0 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Performance Monitors Extension not implemented.";
      break;
    case b0001:
      Description = "FEAT_PMUv3 implemented.";
      break;
    case b0100:
      Description = "FEAT_PMUv3p1 implemented.";
      break;
    case b0101:
      Description = "FEAT_PMUv3p4 implemented.";
      break;
    case b0110:
      Description = "FEAT_PMUv3p5 implemented.";
      break;
    case b0111:
      Description = "FEAT_PMUv3p7 implemented.";
      break;
    case b1000:
      Description = "FEAT_PMUv3p8 implemented.";
      break;
    case b1111:
      Description = "IMPLEMENTATION DEFINED form of performance monitors supported.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "TraceVer";
  Value = (Aa64Dfr0 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Trace unit System registers not implemented.";
      break;
    case b0001:
      Description = "Trace unit System registers implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "DebugVer";
  Value = Aa64Dfr0 & 0xf;
  switch (Value) {
    case b0110:
      Description = "Armv8 debug architecture";
      break;
    case b0111:
      Description = "Armv8 debug architecture with VHE";
      break;
    case b1000:
      Description = "FEAT_Debugv8p2 implemented.";
      break;
    case b1001:
      Description = "FEAT_Debugv8p4 implemented.";
      break;
    case b1010:
      Description = "FEAT_Debugv8p8 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}

/**
  Handle ID_AA64ISAR0_EL1 system register.

  @param[in] Aa64Isar0  value of ID_AA64ISAR0_EL1 system register
**/
VOID
HandleAa64Isar0 (
  CONST UINT64  Aa64Isar0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ISAR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;


  Bits  = "63:60";
  Name  = "RNDR";
  Value = (Aa64Isar0 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RNG not implemented.";
      break;
    case b0001:
      Description = "FEAT_RNG implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "TLB";
  Value = (Aa64Isar0 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TLBIOS/FEAT_TLBIRANGE not implemented.";
      break;
    case b0001:
      Description = "FEAT_TLBIOS implemented.";
      break;
    case b0010:
      Description = "FEAT_TLBIRANGE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "TS";
  Value = (Aa64Isar0 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_FlagM/FEAT_FlagM2 not implemented.";
      break;
    case b0001:
      Description = "FEAT_FlagM implemented.";
      break;
    case b0010:
      Description = "FEAT_FlagM2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "FHM";
  Value = (Aa64Isar0 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_FHM not implemented.";
      break;
    case b0001:
      Description = "FEAT_FHM implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "DP";
  Value = (Aa64Isar0 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_DotProd not implemented.";
      break;
    case b0001:
      Description = "FEAT_DotProd implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "SM4";
  Value = (Aa64Isar0 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SM4 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SM4 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SM3";
  Value = (Aa64Isar0 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SM3 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SM3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SHA3";
  Value = (Aa64Isar0 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SHA3 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SHA3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "RDM";
  Value = (Aa64Isar0 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RDM not implemented.";
      break;
    case b0001:
      Description = "FEAT_RDM implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "TME";
  Value = (Aa64Isar0 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "TME instructions not implemented.";
      break;
    case b0001:
      Description = "TME instructions implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "Atomic";
  Value = (Aa64Isar0 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LSE not implemented.";
      break;
    case b0010:
      Description = "FEAT_LSE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "CRC32";
  Value = (Aa64Isar0 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "CRC32 not implemented.";
      break;
    case b0001:
      Description = "CRC32 instructions implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "SHA2";
  Value = (Aa64Isar0 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SHA256, FEAT_SHA512 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SHA256 implemented.";
      break;
    case b0010:
      Description = "FEAT_SHA512 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "SHA1";
  Value = (Aa64Isar0 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SHA1 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SHA1 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "AES";
  Value = (Aa64Isar0 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_AES, FEAT_PMULL not implemented.";
      break;
    case b0001:
      Description = "FEAT_AES implemented.";
      break;
    case b0010:
      Description = "FEAT_AES and FEAT_PMULL implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 3:0 reserved
}

/**
  Handle ID_AA64ISAR1_EL1 system register.

  @param[in] Aa64Isar1  value of ID_AA64ISAR1_EL1 system register
**/
VOID
HandleAa64Isar1 (
  CONST UINT64  Aa64Isar1
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ISAR1";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "63:60";
  Name  = "LS64";
  Value = (Aa64Isar1 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LS64 not implemented.";
      break;
    case b0001:
      Description = "FEAT_LS64 implemented.";
      break;
    case b0010:
      Description = "FEAT_LS64_V implemented.";
      break;
    case b0011:
      Description = "FEAT_LS64_ACCDATA implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "XS";
  Value = (Aa64Isar1 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_XS not implemented.";
      break;
    case b0001:
      Description = "FEAT_XS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "I8MM";
  Value = (Aa64Isar1 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_I8MM not implemented.";
      break;
    case b0001:
      Description = "FEAT_I8MM implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "DGH";
  Value = (Aa64Isar1 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_DGH not implemented.";
      break;
    case b0001:
      Description = "FEAT_DGH implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "BF16";
  Value = (Aa64Isar1 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_BF16 not implemented.";
      break;
    case b0001:
      Description = "FEAT_BF16 implemented.";
      break;
    case b0010:
      Description = "FEAT_EBF16 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "SPECRES";
  Value = (Aa64Isar1 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SPECRES not implemented.";
      break;
    case b0001:
      Description = "FEAT_SPECRES implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SB";
  Value = (Aa64Isar1 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SB not implemented.";
      break;
    case b0001:
      Description = "FEAT_SB implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "FRINTTS";
  Value = (Aa64Isar1 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_FRINTTS not implemented.";
      break;
    case b0001:
      Description = "FEAT_FRINTTS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "GPI";
  Value = (Aa64Isar1 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PACIMP not implemented.";
      break;
    case b0001:
      Description = "FEAT_PACIMP implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "GPA";
  Value = (Aa64Isar1 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PACQARMA5 not implemented.";
      break;
    case b0001:
      Description = "FEAT_PACQARMA5 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "LRCPC";
  Value = (Aa64Isar1 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LRCPC(2) not implemented.";
      break;
    case b0001:
      Description = "FEAT_LRCPC implemented.";
      break;
    case b0010:
      Description = "FEAT_LRCPC2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "FCMA";
  Value = (Aa64Isar1 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_FCMA not implemented.";
      break;
    case b0001:
      Description = "FEAT_FCMA implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "JSCVT";
  Value = (Aa64Isar1 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_JSCVT not implemented.";
      break;
    case b0001:
      Description = "FEAT_JSCVT implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "API";
  Value = (Aa64Isar1 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Address Authentication (API) not implemented.";
      break;
    case b0001:
      Description = "FEAT_PAuth implemented.";
      break;
    case b0010:
      Description = "FEAT_EPAC implemented.";
      break;
    case b0011:
      Description = "FEAT_PAuth2 implemented.";
      break;
    case b0100:
      Description = "FEAT_FPAC implemented.";
      break;
    case b0101:
      Description = "FEAT_FPACCOMBINE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value > 0) {
    PrintText ("", "", "", "", "FEAT_PACIMP implemented.");
  }

  Bits  = "7:4 ";
  Name  = "APA";
  Value = (Aa64Isar1 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Address Authentication (APA) not implemented.";
      break;
    case b0001:
      Description = "FEAT_PAuth implemented.";
      break;
    case b0010:
      Description = "FEAT_EPAC implemented.";
      break;
    case b0011:
      Description = "FEAT_PAuth2 implemented.";
      break;
    case b0100:
      Description = "FEAT_FPAC implemented.";
      break;
    case b0101:
      Description = "FEAT_FPACCOMBINE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value > 0) {
    PrintText ("", "", "", "", "FEAT_PACQARMA5 implemented.");
  }

  Bits  = "3:0 ";
  Name  = "DPB";
  Value = Aa64Isar1 & 0xf;
  switch (Value) {
    case b0000:
      Description = "DC CVAP not implemented.";
      break;
    case b0001:
      Description = "FEAT_DPB implemented.";
      break;
    case b0010:
      Description = "FEAT_DPB2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}

/**
  Handle ID_AA64ISAR2_EL1 system register.

  @param[in] Aa64Isar2  value of ID_AA64ISAR2_EL1 system register
**/
VOID
HandleAa64Isar2 (
  CONST UINT64  Aa64Isar2
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ISAR2";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  // 63:28 reserved

  Bits  = "27:24";
  Name  = "PAC_frac";
  Value = (Aa64Isar2 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_CONSTPACFIELD not implemented.";
      break;
    case b0001:
      Description = "FEAT_CONSTPACFIELD implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "BC";
  Value = (Aa64Isar2 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_HBC not implemented.";
      break;
    case b0001:
      Description = "FEAT_HBC implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "MOPS";
  Value = (Aa64Isar2 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_MOPS not implemented.";
      break;
    case b0001:
      Description = "FEAT_MOPS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "APA3";
  Value = (Aa64Isar2 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Address Authentication (APA3) not implemented.";
      break;
    case b0001:
      Description = "FEAT_PAuth implemented.";
      break;
    case b0010:
      Description = "FEAT_EPAC implemented.";
      break;
    case b0011:
      Description = "FEAT_PAuth2 implemented.";
      break;
    case b0100:
      Description = "FEAT_FPAC implemented.";
      break;
    case b0101:
      Description = "FEAT_FPACCOMBINE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "GPA3";
  Value = (Aa64Isar2 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PACQARMA3 not implemented.";
      break;
    case b0001:
      Description = "FEAT_PACQARMA3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "RPRES";
  Value = (Aa64Isar2 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RPRES not implemented.";
      break;
    case b0001:
      Description = "FEAT_RPRES implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "WFxT";
  Value = Aa64Isar2 & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_WFxT not implemented.";
      break;
    case b0010:
      Description = "FEAT_WFxT implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}

/**
  Handle ID_AA64MMFR0_EL1 system register.

  @param[in] Aa64Mmfr0  value of ID_AA64MMFR0_EL1 system register
**/
VOID
HandleAa64Mmfr0 (
  CONST UINT64  Aa64Mmfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "MMFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "63:60";
  Name  = "ECV";
  Value = (Aa64Mmfr0 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_ECV not implemented.";
      break;
    case b0001:
      Description = "FEAT_ECV implemented.";
      break;
    case b0010:
      Description = "FEAT_ECV implemented with extras.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "FGT";
  Value = (Aa64Mmfr0 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_FGT not implemented.";
      break;
    case b0001:
      Description = "FEAT_FGT implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 55:48 reserved

  Bits  = "47:44";
  Name  = "ExS";
  Value = (Aa64Mmfr0 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_ExS not implemented.";
      break;
    case b0001:
      Description = "FEAT_ExS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "TGran4";
  Value = (Aa64Mmfr0 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = " 4KB granule supported.";
      break;
    case b0001:
      Description = " 4KB granule supported for 52-bit address.";
      break;
    case b1111:
      Description = " 4KB granule not supported.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "TGran4_2";
  Value = (Aa64Mmfr0 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = " 4KB granule support at stage2 as above.";
      break;
    case b0001:
      Description = " 4KB granule not supported at stage 2.";
      break;
    case b0010:
      Description = " 4KB granule supported at stage 2.";
      break;
    case b0011:
      Description = " 4KB granule supported at stage 2 for 52-bit address.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "TGran16";
  Value = (Aa64Mmfr0 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "16KB granule not supported.";
      break;
    case b0001:
      Description = "16KB granule supported.";
      break;
    case b0010:
      Description = "16KB granule supported for 52-bit address.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "TGran16_2";
  Value = (Aa64Mmfr0 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "16KB granule support at stage2 as above.";
      break;
    case b0001:
      Description = "16KB granule not supported at stage 2.";
      break;
    case b0010:
      Description = "16KB granule supported at stage 2.";
      break;
    case b0011:
      Description = "16KB granule supported at stage 2 for 52-bit address.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "TGran64";
  Value = (Aa64Mmfr0 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "64KB granule supported.";
      break;
    case b1111:
      Description = "64KB granule not supported.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "TGran64_2";
  Value = (Aa64Mmfr0 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "64KB granule support at stage2 as above.";
      break;
    case b0001:
      Description = "64KB granule not supported at stage 2.";
      break;
    case b0010:
      Description = "64KB granule supported at stage 2.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "SNSMem";
  Value = (Aa64Mmfr0 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "No support for a distinction between Secure and Non-Secure Memory.";
      break;
    case b0001:
      Description = "Supports a distinction between Secure and Non-Secure Memory.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "BigEnd";
  Value = (Aa64Mmfr0 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "No mixed-endian support.";
      break;
    case b0001:
      Description = "Mixed-endian support.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Name = "BigEndEL0";
  // If mixed-endian is present, check whether supported at EL0
  if (((Aa64Mmfr0 >>  8) & 0xf) != b0000 ) {
    if (((Aa64Mmfr0 >> 16) & 0xf) == b0000 ) {
      PrintValues (RegName, Name, "19:16", b0000, "No mixed-endian support at EL0.");
    }

    if (((Aa64Mmfr0 >> 16) & 0xf) == b0001 ) {
      PrintValues (RegName, Name, "19:16", b0001, "Mixed-endian support at EL0.");
    }
  }

  Bits  = "7:4 ";
  Name  = "ASIDBits";
  Value = (Aa64Mmfr0 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "ASID: 8 Bits";
      break;
    case b0010:
      Description = "ASID: 16 Bits";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "PARange";
  Value = Aa64Mmfr0 & 0xf;
  switch (Value) {
    case b0000:
      Description = "32 Bits (4GB) of physical address range supported.";
      break;
    case b0001:
      Description = "36 Bits (64GB) of physical address range supported.";
      break;
    case b0010:
      Description = "40 Bits (1TB) of physical address range supported.";
      break;
    case b0011:
      Description = "42 Bits (4TB) of physical address range supported.";
      break;
    case b0100:
      Description = "44 Bits (16TB) of physical address range supported.";
      break;
    case b0101:
      Description = "48 Bits (256TB) of physical address range supported.";
      break;
    case b0110:
      Description = "52 Bits (4PB) of physical address range supported.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value == b0110) {
    PrintText ("", "", "", "", "FEAT_LPA implemented.");
  }
}

/**
  Handle ID_AA64MMFR1_EL1 system register.

  @param[in] Aa64Mmfr1  value of ID_AA64MMFR1_EL1 system register
  @param[in] Aa64Pfr0,  value of ID_AA64PFR0_EL1 system register
**/
VOID
HandleAa64Mmfr1 (
  CONST UINT64  Aa64Mmfr1,
  CONST UINT64  Aa64Pfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "MMFR1";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  // 63:60 reserved

  Bits  = "59:56";
  Name  = "CMOW";
  Value = (Aa64Mmfr1 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_CMOW not implemented.";
      break;
    case b0001:
      Description = "FEAT_CMOW implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "TIDCP1";
  Value = (Aa64Mmfr1 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TIDCP1 not implemented";
      break;
    case b0001:
      Description = "FEAT_TIDCP1 implemented";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "nTLBPA";
  Value = (Aa64Mmfr1 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_nTLBPA not implemented.";
      break;
    case b0001:
      Description = "FEAT_nTLBPA implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "AFP";
  Value = (Aa64Mmfr1 >> 44) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_AFP not implemented.";
      break;
    case b0001:
      Description = "FEAT_AFP implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "HCX";
  Value = (Aa64Mmfr1 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_HCX not implemented.";
      break;
    case b0001:
      Description = "FEAT_HCX implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "ETS";
  Value = (Aa64Mmfr1 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_ETS not implemented.";
      break;
    case b0001:
      Description = "FEAT_ETS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "TWED";
  Value = (Aa64Mmfr1 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TWED not implemented.";
      break;
    case b0001:
      Description = "FEAT_TWED implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "XNX";
  Value = (Aa64Mmfr1 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_XNX not implemented.";
      break;
    case b0001:
      Description = "FEAT_XNX implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Name = "SpecSEI";
  // when FEAT_RAS implemented
  if ((((Aa64Pfr0 >> 28) & 0xf) == b0001) ||
      (((Aa64Pfr0 >> 28) & 0xf) == b0010))
  {
    if (((Aa64Mmfr1 >> 24) & 0xf) == b0000 ) {
      PrintValues (RegName, Name, "27:24", b0000, "The PE never generates an SError interrupt due to");
      PrintText ("", "", "", "", "an External abort on a speculative read.");
    }

    if (((Aa64Mmfr1 >> 24) & 0xf) == b0001 ) {
      PrintValues (RegName, Name, "27:24", b0001, "The PE might generate an SError interrupt due to");
      PrintText ("", "", "", "", "an External abort on a speculative read.");
    }
  }

  Bits  = "23:20";
  Name  = "PAN";
  Value = (Aa64Mmfr1 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PAN not implemented.";
      break;
    case b0001:
      Description = "FEAT_PAN implemented.";
      break;
    case b0010:
      Description = "FEAT_PAN2 implemented.";
      break;
    case b0011:
      Description = "FEAT_PAN3 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "LO";
  Value = (Aa64Mmfr1 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LOR not implemented.";
      break;
    case b0001:
      Description = "FEAT_LOR implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "HPDS";
  Value = (Aa64Mmfr1 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_HPDS not implemented.";
      break;
    case b0001:
      Description = "FEAT_HPDS implemented.";
      break;
    case b0010:
      Description = "FEAT_HPDS2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "VH";
  Value = (Aa64Mmfr1 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_VHE not implemented.";
      break;
    case b0001:
      Description = "FEAT_VHE implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "VMIDBits";
  Value = (Aa64Mmfr1 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_VMID16 not implemented.";
      break;
    case b0010:
      Description = "FEAT_VMID16 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "HAFDBS";
  Value = Aa64Mmfr1 & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_HAFDBS not implemented.";
      break;
    case b0001:
      Description = "FEAT_HAFDBS implemented without dirty status support.";
      break;
    case b0010:
      Description = "FEAT_HAFDBS implemented with dirty status support.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}

/**
  Handle ID_AA64MMFR2_EL1 system register.

  @param[in] Aa64Mmfr2  value of ID_AA64MMFR2_EL1 system register
**/
VOID
HandleAa64Mmfr2 (
  CONST UINT64  Aa64Mmfr2
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "MMFR2";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;

  Bits  = "63:60";
  Name  = "E0PD";
  Value = (Aa64Mmfr2 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_E0PD not implemented.";
      break;
    case b0001:
      Description = "FEAT_E0PD implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "EVT";
  Value = (Aa64Mmfr2 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_EVT not implemented.";
      break;
    case b0001:
      Description = "FEAT_EVT: HCR_EL2.{TOCU, TICAB, TID4} traps.";
      break;
    case b0010:
      Description = "FEAT_EVT: HCR_EL2.{TTLBOS, TTLSBIS, TOCU, TICAB, TID4} traps.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "BBM";
  Value = (Aa64Mmfr2 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_BBM: Level 0 support for changing block size.";
      break;
    case b0001:
      Description = "FEAT_BBM: Level 1 support for changing block size.";
      break;
    case b0010:
      Description = "FEAT_BBM: Level 2 support for changing block size.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "TTL";
  Value = (Aa64Mmfr2 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TTL not implemented.";
      break;
    case b0001:
      Description = "FEAT_TTL implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 47:44 reserved

  Bits  = "43:40";
  Name  = "FWB";
  Value = (Aa64Mmfr2 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_S2FWB not implemented.";
      break;
    case b0001:
      Description = "FEAT_S2FWB implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "IDS";
  Value = (Aa64Mmfr2 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_IDST not implemented.";
      break;
    case b0001:
      Description = "FEAT_IDST implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "AT";
  Value = (Aa64Mmfr2 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LSE2 not implemented.";
      break;
    case b0001:
      Description = "FEAT_LSE2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "ST";
  Value = (Aa64Mmfr2 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TTST not implemented.";
      break;
    case b0001:
      Description = "FEAT_TTST implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "NV";
  Value = (Aa64Mmfr2 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_NV not implemented.";
      break;
    case b0001:
      Description = "FEAT_NV implemented.";
      break;
    case b0010:
      Description = "FEAT_NV2 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "CCIDX";
  Value = (Aa64Mmfr2 >> 20) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_CCIDX not implemented.";
      break;
    case b0001:
      Description = "FEAT_CCIDX implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "VARange";
  Value = (Aa64Mmfr2 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LVA not implemented.";
      break;
    case b0001:
      Description = "FEAT_LVA implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "IESB";
  Value = (Aa64Mmfr2 >> 12) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_IESB not implemented.";
      break;
    case b0001:
      Description = "FEAT_IESB implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "LSM";
  Value = (Aa64Mmfr2 >>  8) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LSMAOC not implemented.";
      break;
    case b0001:
      Description = "FEAT_LSMAOC implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "UAO";
  Value = (Aa64Mmfr2 >>  4) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_UAO not implemented.";
      break;
    case b0001:
      Description = "FEAT_UAO implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "CnP";
  Value = Aa64Mmfr2 & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_TTCNP not implemented.";
      break;
    case b0001:
      Description = "FEAT_TTCNP implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
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

  // 63:40 are reserved

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

  // 62:60 reserved

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

  // 43:40 reserved

  Bits  = "39:36";
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

  // 31:0 reserved
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

  // 31:24 reserved

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
  UINT64  Aa64Dfr0;
  UINT64  Aa64Isar0;
  UINT64  Aa64Isar1;
  UINT64  Aa64Isar2;
  UINT64  Aa64Mmfr0;
  UINT64  Aa64Mmfr1;
  UINT64  Aa64Mmfr2;
  UINT64  Aa64Pfr0;
  UINT64  Aa64Pfr1;
  UINT64  Aa64Smfr0;
  UINT64  Aa64Zfr0;

  Aa64Dfr0  = ArmReadIdAA64Dfr0 ();
  Aa64Isar0 = ArmReadIdAA64Isar0 ();
  Aa64Isar1 = ArmReadIdAA64Isar1 ();
  Aa64Isar2 = ArmReadIdAA64Isar2 ();
  Aa64Mmfr0 = ArmReadIdAA64Mmfr0 ();
  Aa64Mmfr1 = ArmReadIdAA64Mmfr1 ();
  Aa64Mmfr2 = ArmReadIdAA64Mmfr2 ();
  Aa64Pfr0  = ArmReadIdAA64Pfr0 ();
  Aa64Pfr1  = ArmReadIdAA64Pfr1 ();
  Aa64Smfr0 = ArmReadIdAA64Smfr0 ();
  Aa64Zfr0  = ArmReadIdAA64Zfr0 ();

  AsciiPrint ("ArmCpuInfo v1.1.1\n");
  AsciiPrint ("\n");

  AsciiPrint ("ID_AA64MMFR0_EL1 = 0x%016lx\n", Aa64Mmfr0);
  AsciiPrint ("ID_AA64MMFR1_EL1 = 0x%016lx\n", Aa64Mmfr1);
  AsciiPrint ("ID_AA64MMFR2_EL1 = 0x%016lx\n", Aa64Mmfr2);
  AsciiPrint ("ID_AA64PFR0_EL1  = 0x%016lx\n", Aa64Pfr0);
  AsciiPrint ("ID_AA64PFR1_EL1  = 0x%016lx\n", Aa64Pfr1);
  AsciiPrint ("ID_AA64ISAR0_EL1 = 0x%016lx\n", Aa64Isar0);
  AsciiPrint ("ID_AA64ISAR1_EL1 = 0x%016lx\n", Aa64Isar1);
  AsciiPrint ("ID_AA64ISAR2_EL1 = 0x%016lx\n", Aa64Isar2);
  AsciiPrint ("ID_AA64DFR0_EL1  = 0x%016lx\n", Aa64Dfr0);
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

  if (Aa64Smfr0) {
    HandleAa64Smfr0 (Aa64Smfr0);
    PrintSpacer ();
  }

  if (Aa64Zfr0) {
    HandleAa64Zfr0 (Aa64Zfr0);
    PrintSpacer ();
  }

  return EFI_SUCCESS;
}
