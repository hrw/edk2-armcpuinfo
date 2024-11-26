/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "common.h"

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
    case b0011:
      Description = "FEAT_LSE128 implemented.";
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
    case b0010:
      Description = "FEAT_SPECRES2 implemented.";
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
    case b0011:
      Description = "FEAT_LRCPC3 implemented.";
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
    case b0110:
      Description = "FEAT_PAuth_LR implemented.";
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
    case b0110:
      Description = "FEAT_PAuth_LR implemented.";
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


  Bits  = "63:60";
  Name  = "ATS1A";
  Value = (Aa64Isar2 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Address Translate Stage 1 instructions without Permissions Checks are not implemented.";
      break;
    case b0001:
      Description = "Address Translate Stage 1 instructions without Permissions Checks are implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "LUT";
  Value = (Aa64Isar2 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_LUT not implemented.";
      break;
    case b0001:
      Description = "FEAT_LUT implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "CSSC";
  Value = (Aa64Isar2 >> 52) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_CSSC not implemented.";
      break;
    case b0001:
      Description = "FEAT_CSSC implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "RPRFM";
  Value = (Aa64Isar2 >> 48) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_RPRFM not implemented.";
      break;
    case b0001:
      Description = "FEAT_RPRFM implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  // 47:44 reserved

  Bits  = "43:40";
  Name  = "PRFMSLC";
  Value = (Aa64Isar2 >> 40) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PRFMSLC not implemented.";
      break;
    case b0001:
      Description = "FEAT_PRFMSLC implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SYSINSTR_128";
  Value = (Aa64Isar2 >> 36) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SYSINSTR128 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SYSINSTR128 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SYSREG_128";
  Value = (Aa64Isar2 >> 32) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SYSREG128 not implemented.";
      break;
    case b0001:
      Description = "FEAT_SYSREG128 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "CLRBHB";
  Value = (Aa64Isar2 >> 28) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_CLRBHB not implemented.";
      break;
    case b0001:
      Description = "FEAT_CLRBHB implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

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
    case b0110:
      Description = "FEAT_PAuth_LR implemented.";
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

