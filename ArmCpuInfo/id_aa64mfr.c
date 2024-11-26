/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "common.h"

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
    case b0111:
      Description = "56 Bits (64PB) of physical address range supported.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value == b0110) {
    PrintText ("", "", "", "", "FEAT_LPA implemented.");
  }
  if (Value == b0111) {
    PrintText ("", "", "", "", "FEAT_D128 implemented.");
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

  Bits  = "63:60";
  Name  = "ECBHB";
  Value = (Aa64Mmfr1 >> 60) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_ECBHB not implemented.";
      break;
    case b0001:
      Description = "FEAT_ECBHB implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
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
    case b0010:
      Description = "FEAT_ETS2 implemented.";
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
      PrintValues (RegName, Name, "27:24", b0000, "The PE never generates an SError interrupt due to "
                                                  "an External abort on a speculative read.");
    }

    if (((Aa64Mmfr1 >> 24) & 0xf) == b0001 ) {
      PrintValues (RegName, Name, "27:24", b0001, "The PE might generate an SError interrupt due to "
                                                  "an External abort on a speculative read.");
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
      Description = "Hardware update of the Access flag and dirty state are not supported.";
      break;
    case b0001:
      Description = "FEAT_HAFDBS implemented without dirty status support.";
      break;
    case b0010:
      Description = "FEAT_HAFDBS implemented with dirty status support.";
      break;
    case b0011:
      Description = "FEAT_HAFT implemented.";
      break;
    case b0100:
      Description = "FEAT_HDBSS implemented.";
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
    case b0010:
      Description = "FEAT_LVA3 implemented.";
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

