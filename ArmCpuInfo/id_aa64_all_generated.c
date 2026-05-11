/** @file
  GENERATED FILE - DO NOT EDIT
  Generated from registers.yaml by generate_handlers.py

Copyright (c) 2026, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/UefiLib.h>
#include <Library/ArmLib/AArch64/AArch64Lib.h>
#include "AArch64LibExtra.h"
#include "common.h"

// ArmLib register read function declarations
UINT64 ArmReadIdAA64Mmfr0 (VOID);
UINT64 ArmReadIdAA64Mmfr1 (VOID);
UINT64 ArmReadIdAA64Mmfr2 (VOID);
UINT64 ArmReadIdAA64Pfr0 (VOID);
UINT64 ArmReadIdAA64Pfr1 (VOID);
UINT64 ArmReadIdAA64Isar0 (VOID);
UINT64 ArmReadIdAA64Isar1 (VOID);
UINT64 ArmReadIdAA64Isar2 (VOID);
UINT64 ArmReadIdAA64Dfr0 (VOID);
UINT64 ArmReadIdAA64Zfr0 (VOID);
UINT64 ArmReadIdAA64Smfr0 (VOID);

/**
  Handle ID_AA64MMFR0_EL1 system register.

  @param[in] Aa64Mmfr0  value of ID_AA64MMFR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Mmfr0 (
  CONST UINT64  Aa64Mmfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "MMFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *ECVDesc[] = {
    "FEAT_ECV not implemented.",
    "FEAT_ECV implemented.",
    "FEAT_ECV implemented with extras."
  };
  STATIC CONST CHAR8 *FGTDesc[] = {
    "FEAT_FGT not implemented.",
    "FEAT_FGT implemented."
  };
  STATIC CONST CHAR8 *ExSDesc[] = {
    "FEAT_ExS not implemented.",
    "FEAT_ExS implemented."
  };
  STATIC CONST CHAR8 *TGran4Desc[] = {
    [0] = " 4KB granule supported.",
    [1] = " 4KB granule supported for 52-bit address.",
    [15] = " 4KB granule not supported."
  };
  STATIC CONST CHAR8 *TGran4_2Desc[] = {
    " 4KB granule support at stage2 as above.",
    " 4KB granule not supported at stage 2.",
    " 4KB granule supported at stage 2.",
    " 4KB granule supported at stage 2 for 52-bit address."
  };
  STATIC CONST CHAR8 *TGran16Desc[] = {
    "16KB granule not supported.",
    "16KB granule supported.",
    "16KB granule supported for 52-bit address."
  };
  STATIC CONST CHAR8 *TGran16_2Desc[] = {
    "16KB granule support at stage2 as above.",
    "16KB granule not supported at stage 2.",
    "16KB granule supported at stage 2.",
    "16KB granule supported at stage 2 for 52-bit address."
  };
  STATIC CONST CHAR8 *TGran64Desc[] = {
    [0] = "64KB granule supported.",
    [15] = "64KB granule not supported."
  };
  STATIC CONST CHAR8 *TGran64_2Desc[] = {
    "64KB granule support at stage2 as above.",
    "64KB granule not supported at stage 2.",
    "64KB granule supported at stage 2."
  };
  STATIC CONST CHAR8 *SNSMemDesc[] = {
    "No support for a distinction between Secure and Non-Secure Memory.",
    "Supports a distinction between Secure and Non-Secure Memory."
  };
  STATIC CONST CHAR8 *BigEndDesc[] = {
    "No mixed-endian support.",
    "Mixed-endian support."
  };
  STATIC CONST CHAR8 *BigEndEL0Desc[] = {
    "No mixed-endian support at EL0.",
    "Mixed-endian support at EL0."
  };
  STATIC CONST CHAR8 *ASIDBitsDesc[] = {
    [0] = "ASID: 8 Bits",
    [2] = "ASID: 16 Bits"
  };
  STATIC CONST CHAR8 *PARangeDesc[] = {
    "32 Bits (4GB) of physical address range supported.",
    "36 Bits (64GB) of physical address range supported.",
    "40 Bits (1TB) of physical address range supported.",
    "42 Bits (4TB) of physical address range supported.",
    "44 Bits (16TB) of physical address range supported.",
    "48 Bits (256TB) of physical address range supported.",
    "52 Bits (4PB) of physical address range supported.",
    "56 Bits (64PB) of physical address range supported."
  };
  STATIC CONST CHAR8 *PARangeExtraInfo[] = {
    [6] = "FEAT_LPA implemented.",
    [7] = "FEAT_D128 implemented."
  };

  Bits  = "63:60";
  Name  = "ECV";
  Value = (Aa64Mmfr0 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(ECVDesc) && ECVDesc[Value] != NULL) {
    Description = ECVDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "FGT";
  Value = (Aa64Mmfr0 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(FGTDesc) && FGTDesc[Value] != NULL) {
    Description = FGTDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "ExS";
  Value = (Aa64Mmfr0 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(ExSDesc) && ExSDesc[Value] != NULL) {
    Description = ExSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "TGran4";
  Value = (Aa64Mmfr0 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(TGran4Desc) && TGran4Desc[Value] != NULL) {
    Description = TGran4Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "TGran4_2";
  Value = (Aa64Mmfr0 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(TGran4_2Desc) && TGran4_2Desc[Value] != NULL) {
    Description = TGran4_2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "TGran16";
  Value = (Aa64Mmfr0 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(TGran16Desc) && TGran16Desc[Value] != NULL) {
    Description = TGran16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "TGran16_2";
  Value = (Aa64Mmfr0 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(TGran16_2Desc) && TGran16_2Desc[Value] != NULL) {
    Description = TGran16_2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "TGran64";
  Value = (Aa64Mmfr0 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(TGran64Desc) && TGran64Desc[Value] != NULL) {
    Description = TGran64Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "TGran64_2";
  Value = (Aa64Mmfr0 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(TGran64_2Desc) && TGran64_2Desc[Value] != NULL) {
    Description = TGran64_2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "SNSMem";
  Value = (Aa64Mmfr0 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(SNSMemDesc) && SNSMemDesc[Value] != NULL) {
    Description = SNSMemDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "BigEnd";
  Value = (Aa64Mmfr0 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(BigEndDesc) && BigEndDesc[Value] != NULL) {
    Description = BigEndDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Name = "BigEndEL0";
  // conditional field
  if (((Aa64Mmfr0 >>  8) & 0xf) != b0000)
  {{
    Value = (Aa64Mmfr0 >> 16) & 0xf;
    if (Value < ARRAY_SIZE(BigEndEL0Desc) && BigEndEL0Desc[Value] != NULL) {
      Description = BigEndEL0Desc[Value];
    } else {
      Description = "unknown";
    }
    if (AsciiStrCmp(Description, "unknown") == 0) {
      UnknownCount++;
    }
    PrintValues (RegName, Name, "19:16", Value, Description);
  }}

  Bits  = "7:4 ";
  Name  = "ASIDBits";
  Value = (Aa64Mmfr0 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(ASIDBitsDesc) && ASIDBitsDesc[Value] != NULL) {
    Description = ASIDBitsDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "PARange";
  Value = Aa64Mmfr0 & 0xf;
  if (Value < ARRAY_SIZE(PARangeDesc) && PARangeDesc[Value] != NULL) {
    Description = PARangeDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value < ARRAY_SIZE(PARangeExtraInfo) && PARangeExtraInfo[Value] != NULL) {
    PrintText("", "", "", "", PARangeExtraInfo[Value]);
  }

  return UnknownCount;
}

/**
  Handle ID_AA64MMFR1_EL1 system register.

  @param[in] Aa64Mmfr1  value of ID_AA64MMFR1_EL1 system register
  @param[in] Aa64Pfr0,  value of ID_AA64PFR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Mmfr1 (
  CONST UINT64  Aa64Mmfr1, CONST UINT64  Aa64Pfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "MMFR1";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *ECBHBDesc[] = {
    "FEAT_ECBHB not implemented.",
    "FEAT_ECBHB implemented."
  };
  STATIC CONST CHAR8 *CMOWDesc[] = {
    "FEAT_CMOW not implemented.",
    "FEAT_CMOW implemented."
  };
  STATIC CONST CHAR8 *TIDCP1Desc[] = {
    "FEAT_TIDCP1 not implemented",
    "FEAT_TIDCP1 implemented"
  };
  STATIC CONST CHAR8 *nTLBPADesc[] = {
    "FEAT_nTLBPA not implemented.",
    "FEAT_nTLBPA implemented."
  };
  STATIC CONST CHAR8 *AFPDesc[] = {
    "FEAT_AFP not implemented.",
    "FEAT_AFP implemented."
  };
  STATIC CONST CHAR8 *HCXDesc[] = {
    "FEAT_HCX not implemented.",
    "FEAT_HCX implemented."
  };
  STATIC CONST CHAR8 *ETSDesc[] = {
    "FEAT_ETS not implemented.",
    "FEAT_ETS implemented.",
    "FEAT_ETS2 implemented."
  };
  STATIC CONST CHAR8 *TWEDDesc[] = {
    "FEAT_TWED not implemented.",
    "FEAT_TWED implemented."
  };
  STATIC CONST CHAR8 *XNXDesc[] = {
    "FEAT_XNX not implemented.",
    "FEAT_XNX implemented."
  };
  STATIC CONST CHAR8 *SpecSEIDesc[] = {
    "The PE never generates an SError interrupt due to an External abort on a speculative read.",
    "The PE might generate an SError interrupt due to an External abort on a speculative read."
  };
  STATIC CONST CHAR8 *PANDesc[] = {
    "FEAT_PAN not implemented.",
    "FEAT_PAN implemented.",
    "FEAT_PAN2 implemented.",
    "FEAT_PAN3 implemented."
  };
  STATIC CONST CHAR8 *LODesc[] = {
    "FEAT_LOR not implemented.",
    "FEAT_LOR implemented."
  };
  STATIC CONST CHAR8 *HPDSDesc[] = {
    "FEAT_HPDS not implemented.",
    "FEAT_HPDS implemented.",
    "FEAT_HPDS2 implemented."
  };
  STATIC CONST CHAR8 *VHDesc[] = {
    "FEAT_VHE not implemented.",
    "FEAT_VHE implemented."
  };
  STATIC CONST CHAR8 *VMIDBitsDesc[] = {
    [0] = "FEAT_VMID16 not implemented.",
    [2] = "FEAT_VMID16 implemented."
  };
  STATIC CONST CHAR8 *HAFDBSDesc[] = {
    "Hardware update of the Access flag and dirty state are not supported.",
    "FEAT_HAFDBS implemented without dirty status support.",
    "FEAT_HAFDBS implemented with dirty status support.",
    "FEAT_HAFT implemented.",
    "FEAT_HDBSS implemented."
  };

  Bits  = "63:60";
  Name  = "ECBHB";
  Value = (Aa64Mmfr1 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(ECBHBDesc) && ECBHBDesc[Value] != NULL) {
    Description = ECBHBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "CMOW";
  Value = (Aa64Mmfr1 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(CMOWDesc) && CMOWDesc[Value] != NULL) {
    Description = CMOWDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "TIDCP1";
  Value = (Aa64Mmfr1 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(TIDCP1Desc) && TIDCP1Desc[Value] != NULL) {
    Description = TIDCP1Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "nTLBPA";
  Value = (Aa64Mmfr1 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(nTLBPADesc) && nTLBPADesc[Value] != NULL) {
    Description = nTLBPADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "AFP";
  Value = (Aa64Mmfr1 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(AFPDesc) && AFPDesc[Value] != NULL) {
    Description = AFPDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "HCX";
  Value = (Aa64Mmfr1 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(HCXDesc) && HCXDesc[Value] != NULL) {
    Description = HCXDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "ETS";
  Value = (Aa64Mmfr1 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(ETSDesc) && ETSDesc[Value] != NULL) {
    Description = ETSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "TWED";
  Value = (Aa64Mmfr1 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(TWEDDesc) && TWEDDesc[Value] != NULL) {
    Description = TWEDDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "XNX";
  Value = (Aa64Mmfr1 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(XNXDesc) && XNXDesc[Value] != NULL) {
    Description = XNXDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Name = "SpecSEI";
  // conditional field
  if (((Aa64Pfr0 >> 28) & 0xf) == b0001 || ((Aa64Pfr0 >> 28) & 0xf) == b0010)
  {{
    Value = (Aa64Mmfr1 >> 24) & 0xf;
    if (Value < ARRAY_SIZE(SpecSEIDesc) && SpecSEIDesc[Value] != NULL) {
      Description = SpecSEIDesc[Value];
    } else {
      Description = "unknown";
    }
    if (AsciiStrCmp(Description, "unknown") == 0) {
      UnknownCount++;
    }
    PrintValues (RegName, Name, "27:24", Value, Description);
  }}

  Bits  = "23:20";
  Name  = "PAN";
  Value = (Aa64Mmfr1 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(PANDesc) && PANDesc[Value] != NULL) {
    Description = PANDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "LO";
  Value = (Aa64Mmfr1 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(LODesc) && LODesc[Value] != NULL) {
    Description = LODesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "HPDS";
  Value = (Aa64Mmfr1 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(HPDSDesc) && HPDSDesc[Value] != NULL) {
    Description = HPDSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "VH";
  Value = (Aa64Mmfr1 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(VHDesc) && VHDesc[Value] != NULL) {
    Description = VHDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "VMIDBits";
  Value = (Aa64Mmfr1 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(VMIDBitsDesc) && VMIDBitsDesc[Value] != NULL) {
    Description = VMIDBitsDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "HAFDBS";
  Value = Aa64Mmfr1 & 0xf;
  if (Value < ARRAY_SIZE(HAFDBSDesc) && HAFDBSDesc[Value] != NULL) {
    Description = HAFDBSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64MMFR2_EL1 system register.

  @param[in] Aa64Mmfr2  value of ID_AA64MMFR2_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Mmfr2 (
  CONST UINT64  Aa64Mmfr2
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "MMFR2";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *E0PDDesc[] = {
    "FEAT_E0PD not implemented.",
    "FEAT_E0PD implemented."
  };
  STATIC CONST CHAR8 *EVTDesc[] = {
    "FEAT_EVT not implemented.",
    "FEAT_EVT: HCR_EL2.{TOCU, TICAB, TID4} traps.",
    "FEAT_EVT: HCR_EL2.{TTLBOS, TTLSBIS, TOCU, TICAB, TID4} traps."
  };
  STATIC CONST CHAR8 *BBMDesc[] = {
    "FEAT_BBM: Level 0 support for changing block size.",
    "FEAT_BBM: Level 1 support for changing block size.",
    "FEAT_BBM: Level 2 support for changing block size."
  };
  STATIC CONST CHAR8 *TTLDesc[] = {
    "FEAT_TTL not implemented.",
    "FEAT_TTL implemented."
  };
  STATIC CONST CHAR8 *FWBDesc[] = {
    "FEAT_S2FWB not implemented.",
    "FEAT_S2FWB implemented."
  };
  STATIC CONST CHAR8 *IDSDesc[] = {
    "FEAT_IDST not implemented.",
    "FEAT_IDST implemented."
  };
  STATIC CONST CHAR8 *ATDesc[] = {
    "FEAT_LSE2 not implemented.",
    "FEAT_LSE2 implemented."
  };
  STATIC CONST CHAR8 *STDesc[] = {
    "FEAT_TTST not implemented.",
    "FEAT_TTST implemented."
  };
  STATIC CONST CHAR8 *NVDesc[] = {
    "FEAT_NV not implemented.",
    "FEAT_NV implemented.",
    "FEAT_NV2 implemented."
  };
  STATIC CONST CHAR8 *CCIDXDesc[] = {
    "FEAT_CCIDX not implemented.",
    "FEAT_CCIDX implemented."
  };
  STATIC CONST CHAR8 *VARangeDesc[] = {
    "FEAT_LVA not implemented.",
    "FEAT_LVA implemented.",
    "FEAT_LVA3 implemented."
  };
  STATIC CONST CHAR8 *VARangeExtraInfo[] = {
    [2] = "FEAT_D128 implemented."
  };
  STATIC CONST CHAR8 *IESBDesc[] = {
    "FEAT_IESB not implemented.",
    "FEAT_IESB implemented."
  };
  STATIC CONST CHAR8 *LSMDesc[] = {
    "FEAT_LSMAOC not implemented.",
    "FEAT_LSMAOC implemented."
  };
  STATIC CONST CHAR8 *UAODesc[] = {
    "FEAT_UAO not implemented.",
    "FEAT_UAO implemented."
  };
  STATIC CONST CHAR8 *CnPDesc[] = {
    "FEAT_TTCNP not implemented.",
    "FEAT_TTCNP implemented."
  };

  Bits  = "63:60";
  Name  = "E0PD";
  Value = (Aa64Mmfr2 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(E0PDDesc) && E0PDDesc[Value] != NULL) {
    Description = E0PDDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "EVT";
  Value = (Aa64Mmfr2 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(EVTDesc) && EVTDesc[Value] != NULL) {
    Description = EVTDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "BBM";
  Value = (Aa64Mmfr2 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(BBMDesc) && BBMDesc[Value] != NULL) {
    Description = BBMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "TTL";
  Value = (Aa64Mmfr2 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(TTLDesc) && TTLDesc[Value] != NULL) {
    Description = TTLDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "FWB";
  Value = (Aa64Mmfr2 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(FWBDesc) && FWBDesc[Value] != NULL) {
    Description = FWBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "IDS";
  Value = (Aa64Mmfr2 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(IDSDesc) && IDSDesc[Value] != NULL) {
    Description = IDSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "AT";
  Value = (Aa64Mmfr2 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(ATDesc) && ATDesc[Value] != NULL) {
    Description = ATDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "ST";
  Value = (Aa64Mmfr2 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(STDesc) && STDesc[Value] != NULL) {
    Description = STDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "NV";
  Value = (Aa64Mmfr2 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(NVDesc) && NVDesc[Value] != NULL) {
    Description = NVDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "CCIDX";
  Value = (Aa64Mmfr2 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(CCIDXDesc) && CCIDXDesc[Value] != NULL) {
    Description = CCIDXDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "VARange";
  Value = (Aa64Mmfr2 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(VARangeDesc) && VARangeDesc[Value] != NULL) {
    Description = VARangeDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value < ARRAY_SIZE(VARangeExtraInfo) && VARangeExtraInfo[Value] != NULL) {
    PrintText("", "", "", "", VARangeExtraInfo[Value]);
  }

  Bits  = "15:12";
  Name  = "IESB";
  Value = (Aa64Mmfr2 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(IESBDesc) && IESBDesc[Value] != NULL) {
    Description = IESBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "LSM";
  Value = (Aa64Mmfr2 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(LSMDesc) && LSMDesc[Value] != NULL) {
    Description = LSMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "UAO";
  Value = (Aa64Mmfr2 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(UAODesc) && UAODesc[Value] != NULL) {
    Description = UAODesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "CnP";
  Value = Aa64Mmfr2 & 0xf;
  if (Value < ARRAY_SIZE(CnPDesc) && CnPDesc[Value] != NULL) {
    Description = CnPDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64PFR0_EL1 system register.

  @param[in] Aa64Pfr0  value of ID_AA64PFR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Pfr0 (
  CONST UINT64  Aa64Pfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "PFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *CSV3Desc[] = {
    "FEAT_CSV3 not implemented.",
    "FEAT_CSV3 implemented."
  };
  STATIC CONST CHAR8 *CSV2Desc[] = {
    "Not disclosed whether FEAT_CSV2 is implemented.",
    "FEAT_CSV2 implemented.",
    "FEAT_CSV2_2 implemented.",
    "FEAT_CSV2_3 implemented."
  };
  STATIC CONST CHAR8 *RMEDesc[] = {
    "FEAT_RME not implemented",
    "FEAT_RME implemented",
    "FEAT_RME_GPC2 implemented"
  };
  STATIC CONST CHAR8 *DITDesc[] = {
    "FEAT_DIT not implemented.",
    "FEAT_DIT implemented."
  };
  STATIC CONST CHAR8 *AMUDesc[] = {
    "FEAT_AMU not implemented.",
    "FEAT_AMUv1 implemented.",
    "FEAT_AMUv1p1 implemented."
  };
  STATIC CONST CHAR8 *MPAMDesc[] = {
    "FEAT_MPAM not implemented.",
    "FEAT_MPAM v1.0 implemented."
  };
  STATIC CONST CHAR8 *SEL2Desc[] = {
    "Secure EL2 not implemented.",
    "Secure EL2 implemented."
  };
  STATIC CONST CHAR8 *SVEDesc[] = {
    "FEAT_SVE not implemented.",
    "FEAT_SVE implemented."
  };
  STATIC CONST CHAR8 *RASDesc[] = {
    "FEAT_RAS not implemented.",
    "FEAT_RAS implemented.",
    "FEAT_RASv1p1 implemented.",
    "FEAT_RASv2 implemented."
  };
  STATIC CONST CHAR8 *GICDesc[] = {
    [0] = "System registers of GIC CPU not implemented.",
    [1] = "System registers to versions 3.0/4.0 of GIC CPU implemented.",
    [3] = "System registers to versions 4.1 of GIC CPU implemented."
  };
  STATIC CONST CHAR8 *AdvSIMDDesc[] = {
    [0] = "Advanced SIMD implemented.",
    [1] = "Advanced SIMD with half precision support (FEAT_FP16).",
    [15] = "Advanced SIMD not implemented."
  };
  STATIC CONST CHAR8 *FPDesc[] = {
    [0] = "Floating-point implemented.",
    [1] = "Floating-point with half-precision support (FEAT_FP16).",
    [15] = "Floating-point not implemented."
  };
  STATIC CONST CHAR8 *EL3Desc[] = {
    "EL3 not implemented.",
    "EL3 in AArch64 only",
    "EL3 in AArch64 and AArch32"
  };
  STATIC CONST CHAR8 *EL2Desc[] = {
    "EL2 not implemented.",
    "EL2 in AArch64 only",
    "EL2 in AArch64 and AArch32"
  };
  STATIC CONST CHAR8 *EL1Desc[] = {
    [1] = "EL1 in AArch64 only",
    [2] = "EL1 in AArch64 and AArch32"
  };
  STATIC CONST CHAR8 *EL0Desc[] = {
    [1] = "EL0 in AArch64 only",
    [2] = "EL0 in AArch64 and AArch32"
  };

  Bits  = "63:60";
  Name  = "CSV3";
  Value = (Aa64Pfr0 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(CSV3Desc) && CSV3Desc[Value] != NULL) {
    Description = CSV3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "CSV2";
  Value = (Aa64Pfr0 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(CSV2Desc) && CSV2Desc[Value] != NULL) {
    Description = CSV2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "RME";
  Value = (Aa64Pfr0 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(RMEDesc) && RMEDesc[Value] != NULL) {
    Description = RMEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "DIT";
  Value = (Aa64Pfr0 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(DITDesc) && DITDesc[Value] != NULL) {
    Description = DITDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "AMU";
  Value = (Aa64Pfr0 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(AMUDesc) && AMUDesc[Value] != NULL) {
    Description = AMUDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "MPAM";
  Value = (Aa64Pfr0 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(MPAMDesc) && MPAMDesc[Value] != NULL) {
    Description = MPAMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SEL2";
  Value = (Aa64Pfr0 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(SEL2Desc) && SEL2Desc[Value] != NULL) {
    Description = SEL2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SVE";
  Value = (Aa64Pfr0 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(SVEDesc) && SVEDesc[Value] != NULL) {
    Description = SVEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "RAS";
  Value = (Aa64Pfr0 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(RASDesc) && RASDesc[Value] != NULL) {
    Description = RASDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "GIC";
  Value = (Aa64Pfr0 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(GICDesc) && GICDesc[Value] != NULL) {
    Description = GICDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "AdvSIMD";
  Value = (Aa64Pfr0 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(AdvSIMDDesc) && AdvSIMDDesc[Value] != NULL) {
    Description = AdvSIMDDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "FP";
  Value = (Aa64Pfr0 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(FPDesc) && FPDesc[Value] != NULL) {
    Description = FPDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "EL3";
  Value = (Aa64Pfr0 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(EL3Desc) && EL3Desc[Value] != NULL) {
    Description = EL3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "EL2";
  Value = (Aa64Pfr0 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(EL2Desc) && EL2Desc[Value] != NULL) {
    Description = EL2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "EL1";
  Value = (Aa64Pfr0 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(EL1Desc) && EL1Desc[Value] != NULL) {
    Description = EL1Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "EL0";
  Value = Aa64Pfr0 & 0xf;
  if (Value < ARRAY_SIZE(EL0Desc) && EL0Desc[Value] != NULL) {
    Description = EL0Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64PFR1_EL1 system register.

  @param[in] Aa64Pfr1  value of ID_AA64PFR1_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Pfr1 (
  CONST UINT64  Aa64Pfr1
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "PFR1";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *PFARDesc[] = {
    "FEAT_PFAR not implemented.",
    "FEAT_PFAR implemented."
  };
  STATIC CONST CHAR8 *DF2Desc[] = {
    "FEAT_DoubleFault2 not implemented.",
    "FEAT_DoubleFault2 implemented."
  };
  STATIC CONST CHAR8 *MTEXDesc[] = {
    "Canonical Tag checking and Memory tagging with Address tagging disabled are not supported.",
    "FEAT_MTE_NO_ADDRESS_TAGS and FEAT_MTE_CANONICAL_TAG implemented."
  };
  STATIC CONST CHAR8 *THEDesc[] = {
    "FEAT_THE not implemented.",
    "FEAT_THE implemented."
  };
  STATIC CONST CHAR8 *GCSDesc[] = {
    "FEAT_GCS not implemented.",
    "FEAT_GCS implemented."
  };
  STATIC CONST CHAR8 *MTE_fracDesc[] = {
    [0] = "FEAT_MTE_ASYNC implemented.",
    [15] = "FEAT_MTE_ASYNC not implemented."
  };
  STATIC CONST CHAR8 *NMIDesc[] = {
    "FEAT_NMI not implemented.",
    "FEAT_NMI implemented."
  };
  STATIC CONST CHAR8 *RNDR_trapDesc[] = {
    "FEAT_RNG_TRAP not implemented.",
    "FEAT_RNG_TRAP implemented."
  };
  STATIC CONST CHAR8 *SMEDesc[] = {
    "FEAT_SME not implemented.",
    "FEAT_SME implemented.",
    "FEAT_SME2 implemented."
  };
  STATIC CONST CHAR8 *MTEDesc[] = {
    "FEAT_MTE not implemented.",
    "FEAT_MTE implemented.",
    "FEAT_MTE2 implemented.",
    "FEAT_MTE3 implemented."
  };
  STATIC CONST CHAR8 *SSBSDesc[] = {
    "FEAT_SSBS not implemented.",
    "FEAT_SSBS implemented.",
    "FEAT_SSBS2 implemented."
  };
  STATIC CONST CHAR8 *BTDesc[] = {
    "FEAT_BTI not implemented.",
    "FEAT_BTI implemented."
  };

  Bits  = "63:60";
  Name  = "PFAR";
  Value = (Aa64Pfr1 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(PFARDesc) && PFARDesc[Value] != NULL) {
    Description = PFARDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "DF2";
  Value = (Aa64Pfr1 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(DF2Desc) && DF2Desc[Value] != NULL) {
    Description = DF2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "MTEX";
  Value = (Aa64Pfr1 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(MTEXDesc) && MTEXDesc[Value] != NULL) {
    Description = MTEXDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "THE";
  Value = (Aa64Pfr1 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(THEDesc) && THEDesc[Value] != NULL) {
    Description = THEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "GCS";
  Value = (Aa64Pfr1 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(GCSDesc) && GCSDesc[Value] != NULL) {
    Description = GCSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "MTE_frac";
  Value = (Aa64Pfr1 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(MTE_fracDesc) && MTE_fracDesc[Value] != NULL) {
    Description = MTE_fracDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "NMI";
  Value = (Aa64Pfr1 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(NMIDesc) && NMIDesc[Value] != NULL) {
    Description = NMIDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "RNDR_trap";
  Value = (Aa64Pfr1 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(RNDR_trapDesc) && RNDR_trapDesc[Value] != NULL) {
    Description = RNDR_trapDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "SME";
  Value = (Aa64Pfr1 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(SMEDesc) && SMEDesc[Value] != NULL) {
    Description = SMEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "MTE";
  Value = (Aa64Pfr1 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(MTEDesc) && MTEDesc[Value] != NULL) {
    Description = MTEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "SSBS";
  Value = (Aa64Pfr1 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(SSBSDesc) && SSBSDesc[Value] != NULL) {
    Description = SSBSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "BT";
  Value = Aa64Pfr1 & 0xf;
  if (Value < ARRAY_SIZE(BTDesc) && BTDesc[Value] != NULL) {
    Description = BTDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64ISAR0_EL1 system register.

  @param[in] Aa64Isar0  value of ID_AA64ISAR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Isar0 (
  CONST UINT64  Aa64Isar0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ISAR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *RNDRDesc[] = {
    "FEAT_RNG not implemented.",
    "FEAT_RNG implemented."
  };
  STATIC CONST CHAR8 *TLBDesc[] = {
    "FEAT_TLBIOS/FEAT_TLBIRANGE not implemented.",
    "FEAT_TLBIOS implemented.",
    "FEAT_TLBIRANGE implemented."
  };
  STATIC CONST CHAR8 *TSDesc[] = {
    "FEAT_FlagM/FEAT_FlagM2 not implemented.",
    "FEAT_FlagM implemented.",
    "FEAT_FlagM2 implemented."
  };
  STATIC CONST CHAR8 *FHMDesc[] = {
    "FEAT_FHM not implemented.",
    "FEAT_FHM implemented."
  };
  STATIC CONST CHAR8 *DPDesc[] = {
    "FEAT_DotProd not implemented.",
    "FEAT_DotProd implemented."
  };
  STATIC CONST CHAR8 *SM4Desc[] = {
    "FEAT_SM4 not implemented.",
    "FEAT_SM4 implemented."
  };
  STATIC CONST CHAR8 *SM3Desc[] = {
    "FEAT_SM3 not implemented.",
    "FEAT_SM3 implemented."
  };
  STATIC CONST CHAR8 *SHA3Desc[] = {
    "FEAT_SHA3 not implemented.",
    "FEAT_SHA3 implemented."
  };
  STATIC CONST CHAR8 *RDMDesc[] = {
    "FEAT_RDM not implemented.",
    "FEAT_RDM implemented."
  };
  STATIC CONST CHAR8 *TMEDesc[] = {
    "TME instructions not implemented.",
    "TME instructions implemented."
  };
  STATIC CONST CHAR8 *AtomicDesc[] = {
    [0] = "FEAT_LSE not implemented.",
    [2] = "FEAT_LSE implemented.",
    [3] = "FEAT_LSE128 implemented."
  };
  STATIC CONST CHAR8 *CRC32Desc[] = {
    "CRC32 not implemented.",
    "CRC32 instructions implemented."
  };
  STATIC CONST CHAR8 *SHA2Desc[] = {
    "FEAT_SHA256, FEAT_SHA512 not implemented.",
    "FEAT_SHA256 implemented.",
    "FEAT_SHA512 implemented."
  };
  STATIC CONST CHAR8 *SHA1Desc[] = {
    "FEAT_SHA1 not implemented.",
    "FEAT_SHA1 implemented."
  };
  STATIC CONST CHAR8 *AESDesc[] = {
    "FEAT_AES, FEAT_PMULL not implemented.",
    "FEAT_AES implemented.",
    "FEAT_AES and FEAT_PMULL implemented."
  };

  Bits  = "63:60";
  Name  = "RNDR";
  Value = (Aa64Isar0 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(RNDRDesc) && RNDRDesc[Value] != NULL) {
    Description = RNDRDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "TLB";
  Value = (Aa64Isar0 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(TLBDesc) && TLBDesc[Value] != NULL) {
    Description = TLBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "TS";
  Value = (Aa64Isar0 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(TSDesc) && TSDesc[Value] != NULL) {
    Description = TSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "FHM";
  Value = (Aa64Isar0 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(FHMDesc) && FHMDesc[Value] != NULL) {
    Description = FHMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "DP";
  Value = (Aa64Isar0 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(DPDesc) && DPDesc[Value] != NULL) {
    Description = DPDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "SM4";
  Value = (Aa64Isar0 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(SM4Desc) && SM4Desc[Value] != NULL) {
    Description = SM4Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SM3";
  Value = (Aa64Isar0 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(SM3Desc) && SM3Desc[Value] != NULL) {
    Description = SM3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SHA3";
  Value = (Aa64Isar0 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(SHA3Desc) && SHA3Desc[Value] != NULL) {
    Description = SHA3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "RDM";
  Value = (Aa64Isar0 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(RDMDesc) && RDMDesc[Value] != NULL) {
    Description = RDMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "TME";
  Value = (Aa64Isar0 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(TMEDesc) && TMEDesc[Value] != NULL) {
    Description = TMEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "Atomic";
  Value = (Aa64Isar0 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(AtomicDesc) && AtomicDesc[Value] != NULL) {
    Description = AtomicDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "CRC32";
  Value = (Aa64Isar0 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(CRC32Desc) && CRC32Desc[Value] != NULL) {
    Description = CRC32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "SHA2";
  Value = (Aa64Isar0 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(SHA2Desc) && SHA2Desc[Value] != NULL) {
    Description = SHA2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "SHA1";
  Value = (Aa64Isar0 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(SHA1Desc) && SHA1Desc[Value] != NULL) {
    Description = SHA1Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "AES";
  Value = (Aa64Isar0 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(AESDesc) && AESDesc[Value] != NULL) {
    Description = AESDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64ISAR1_EL1 system register.

  @param[in] Aa64Isar1  value of ID_AA64ISAR1_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Isar1 (
  CONST UINT64  Aa64Isar1
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ISAR1";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *LS64Desc[] = {
    "FEAT_LS64 not implemented.",
    "FEAT_LS64 implemented.",
    "FEAT_LS64_V implemented.",
    "FEAT_LS64_ACCDATA implemented."
  };
  STATIC CONST CHAR8 *XSDesc[] = {
    "FEAT_XS not implemented.",
    "FEAT_XS implemented."
  };
  STATIC CONST CHAR8 *I8MMDesc[] = {
    "FEAT_I8MM not implemented.",
    "FEAT_I8MM implemented."
  };
  STATIC CONST CHAR8 *DGHDesc[] = {
    "FEAT_DGH not implemented.",
    "FEAT_DGH implemented."
  };
  STATIC CONST CHAR8 *BF16Desc[] = {
    "FEAT_BF16 not implemented.",
    "FEAT_BF16 implemented.",
    "FEAT_EBF16 implemented."
  };
  STATIC CONST CHAR8 *SPECRESDesc[] = {
    "FEAT_SPECRES not implemented.",
    "FEAT_SPECRES implemented.",
    "FEAT_SPECRES2 implemented."
  };
  STATIC CONST CHAR8 *SBDesc[] = {
    "FEAT_SB not implemented.",
    "FEAT_SB implemented."
  };
  STATIC CONST CHAR8 *FRINTTSDesc[] = {
    "FEAT_FRINTTS not implemented.",
    "FEAT_FRINTTS implemented."
  };
  STATIC CONST CHAR8 *GPIDesc[] = {
    "FEAT_PACIMP not implemented.",
    "FEAT_PACIMP implemented."
  };
  STATIC CONST CHAR8 *GPADesc[] = {
    "FEAT_PACQARMA5 not implemented.",
    "FEAT_PACQARMA5 implemented."
  };
  STATIC CONST CHAR8 *LRCPCDesc[] = {
    "FEAT_LRCPC(2) not implemented.",
    "FEAT_LRCPC implemented.",
    "FEAT_LRCPC2 implemented.",
    "FEAT_LRCPC3 implemented."
  };
  STATIC CONST CHAR8 *FCMADesc[] = {
    "FEAT_FCMA not implemented.",
    "FEAT_FCMA implemented."
  };
  STATIC CONST CHAR8 *JSCVTDesc[] = {
    "FEAT_JSCVT not implemented.",
    "FEAT_JSCVT implemented."
  };
  STATIC CONST CHAR8 *APIDesc[] = {
    "Address Authentication (API) not implemented.",
    "FEAT_PAuth implemented.",
    "FEAT_EPAC implemented.",
    "FEAT_PAuth2 implemented.",
    "FEAT_FPAC implemented.",
    "FEAT_FPACCOMBINE implemented.",
    "FEAT_PAuth_LR implemented."
  };
  STATIC CONST CHAR8 *APIExtraInfo[] = {
    [1] = "FEAT_PACIMP implemented.",
    [2] = "FEAT_PACIMP implemented.",
    [3] = "FEAT_PACIMP implemented.",
    [4] = "FEAT_PACIMP implemented.",
    [5] = "FEAT_PACIMP implemented.",
    [6] = "FEAT_PACIMP implemented."
  };
  STATIC CONST CHAR8 *APADesc[] = {
    "Address Authentication (APA) not implemented.",
    "FEAT_PAuth implemented.",
    "FEAT_EPAC implemented.",
    "FEAT_PAuth2 implemented.",
    "FEAT_FPAC implemented.",
    "FEAT_FPACCOMBINE implemented.",
    "FEAT_PAuth_LR implemented."
  };
  STATIC CONST CHAR8 *DPBDesc[] = {
    "DC CVAP not implemented.",
    "FEAT_DPB implemented.",
    "FEAT_DPB2 implemented."
  };

  Bits  = "63:60";
  Name  = "LS64";
  Value = (Aa64Isar1 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(LS64Desc) && LS64Desc[Value] != NULL) {
    Description = LS64Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "XS";
  Value = (Aa64Isar1 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(XSDesc) && XSDesc[Value] != NULL) {
    Description = XSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "I8MM";
  Value = (Aa64Isar1 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(I8MMDesc) && I8MMDesc[Value] != NULL) {
    Description = I8MMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "DGH";
  Value = (Aa64Isar1 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(DGHDesc) && DGHDesc[Value] != NULL) {
    Description = DGHDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "BF16";
  Value = (Aa64Isar1 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(BF16Desc) && BF16Desc[Value] != NULL) {
    Description = BF16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "SPECRES";
  Value = (Aa64Isar1 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(SPECRESDesc) && SPECRESDesc[Value] != NULL) {
    Description = SPECRESDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SB";
  Value = (Aa64Isar1 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(SBDesc) && SBDesc[Value] != NULL) {
    Description = SBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "FRINTTS";
  Value = (Aa64Isar1 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(FRINTTSDesc) && FRINTTSDesc[Value] != NULL) {
    Description = FRINTTSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "GPI";
  Value = (Aa64Isar1 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(GPIDesc) && GPIDesc[Value] != NULL) {
    Description = GPIDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "GPA";
  Value = (Aa64Isar1 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(GPADesc) && GPADesc[Value] != NULL) {
    Description = GPADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "LRCPC";
  Value = (Aa64Isar1 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(LRCPCDesc) && LRCPCDesc[Value] != NULL) {
    Description = LRCPCDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "FCMA";
  Value = (Aa64Isar1 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(FCMADesc) && FCMADesc[Value] != NULL) {
    Description = FCMADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "JSCVT";
  Value = (Aa64Isar1 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(JSCVTDesc) && JSCVTDesc[Value] != NULL) {
    Description = JSCVTDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "API";
  Value = (Aa64Isar1 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(APIDesc) && APIDesc[Value] != NULL) {
    Description = APIDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);
  if (Value < ARRAY_SIZE(APIExtraInfo) && APIExtraInfo[Value] != NULL) {
    PrintText("", "", "", "", APIExtraInfo[Value]);
  }

  Bits  = "7:4 ";
  Name  = "APA";
  Value = (Aa64Isar1 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(APADesc) && APADesc[Value] != NULL) {
    Description = APADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "DPB";
  Value = Aa64Isar1 & 0xf;
  if (Value < ARRAY_SIZE(DPBDesc) && DPBDesc[Value] != NULL) {
    Description = DPBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64ISAR2_EL1 system register.

  @param[in] Aa64Isar2  value of ID_AA64ISAR2_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Isar2 (
  CONST UINT64  Aa64Isar2
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ISAR2";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *ATS1ADesc[] = {
    "Address Translate Stage 1 instructions without Permissions Checks are not implemented.",
    "Address Translate Stage 1 instructions without Permissions Checks are implemented."
  };
  STATIC CONST CHAR8 *LUTDesc[] = {
    "FEAT_LUT not implemented.",
    "FEAT_LUT implemented."
  };
  STATIC CONST CHAR8 *CSSCDesc[] = {
    "FEAT_CSSC not implemented.",
    "FEAT_CSSC implemented."
  };
  STATIC CONST CHAR8 *RPRFMDesc[] = {
    "FEAT_RPRFM not implemented.",
    "FEAT_RPRFM implemented."
  };
  STATIC CONST CHAR8 *PRFMSLCDesc[] = {
    "FEAT_PRFMSLC not implemented.",
    "FEAT_PRFMSLC implemented."
  };
  STATIC CONST CHAR8 *SYSINSTR_128Desc[] = {
    "FEAT_SYSINSTR128 not implemented.",
    "FEAT_SYSINSTR128 implemented."
  };
  STATIC CONST CHAR8 *SYSREG_128Desc[] = {
    "FEAT_SYSREG128 not implemented.",
    "FEAT_SYSREG128 implemented."
  };
  STATIC CONST CHAR8 *CLRBHBDesc[] = {
    "FEAT_CLRBHB not implemented.",
    "FEAT_CLRBHB implemented."
  };
  STATIC CONST CHAR8 *PAC_fracDesc[] = {
    "FEAT_CONSTPACFIELD not implemented.",
    "FEAT_CONSTPACFIELD implemented."
  };
  STATIC CONST CHAR8 *BCDesc[] = {
    "FEAT_HBC not implemented.",
    "FEAT_HBC implemented."
  };
  STATIC CONST CHAR8 *MOPSDesc[] = {
    "FEAT_MOPS not implemented.",
    "FEAT_MOPS implemented."
  };
  STATIC CONST CHAR8 *APA3Desc[] = {
    "Address Authentication (APA3) not implemented.",
    "FEAT_PAuth implemented.",
    "FEAT_EPAC implemented.",
    "FEAT_PAuth2 implemented.",
    "FEAT_FPAC implemented.",
    "FEAT_FPACCOMBINE implemented.",
    "FEAT_PAuth_LR implemented."
  };
  STATIC CONST CHAR8 *GPA3Desc[] = {
    "FEAT_PACQARMA3 not implemented.",
    "FEAT_PACQARMA3 implemented."
  };
  STATIC CONST CHAR8 *RPRESDesc[] = {
    "FEAT_RPRES not implemented.",
    "FEAT_RPRES implemented."
  };
  STATIC CONST CHAR8 *WFxTDesc[] = {
    [0] = "FEAT_WFxT not implemented.",
    [2] = "FEAT_WFxT implemented."
  };

  Bits  = "63:60";
  Name  = "ATS1A";
  Value = (Aa64Isar2 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(ATS1ADesc) && ATS1ADesc[Value] != NULL) {
    Description = ATS1ADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "LUT";
  Value = (Aa64Isar2 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(LUTDesc) && LUTDesc[Value] != NULL) {
    Description = LUTDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "CSSC";
  Value = (Aa64Isar2 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(CSSCDesc) && CSSCDesc[Value] != NULL) {
    Description = CSSCDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "RPRFM";
  Value = (Aa64Isar2 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(RPRFMDesc) && RPRFMDesc[Value] != NULL) {
    Description = RPRFMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "PRFMSLC";
  Value = (Aa64Isar2 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(PRFMSLCDesc) && PRFMSLCDesc[Value] != NULL) {
    Description = PRFMSLCDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "SYSINSTR_128";
  Value = (Aa64Isar2 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(SYSINSTR_128Desc) && SYSINSTR_128Desc[Value] != NULL) {
    Description = SYSINSTR_128Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SYSREG_128";
  Value = (Aa64Isar2 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(SYSREG_128Desc) && SYSREG_128Desc[Value] != NULL) {
    Description = SYSREG_128Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "CLRBHB";
  Value = (Aa64Isar2 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(CLRBHBDesc) && CLRBHBDesc[Value] != NULL) {
    Description = CLRBHBDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "PAC_frac";
  Value = (Aa64Isar2 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(PAC_fracDesc) && PAC_fracDesc[Value] != NULL) {
    Description = PAC_fracDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "BC";
  Value = (Aa64Isar2 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(BCDesc) && BCDesc[Value] != NULL) {
    Description = BCDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "MOPS";
  Value = (Aa64Isar2 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(MOPSDesc) && MOPSDesc[Value] != NULL) {
    Description = MOPSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "APA3";
  Value = (Aa64Isar2 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(APA3Desc) && APA3Desc[Value] != NULL) {
    Description = APA3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "GPA3";
  Value = (Aa64Isar2 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(GPA3Desc) && GPA3Desc[Value] != NULL) {
    Description = GPA3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "RPRES";
  Value = (Aa64Isar2 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(RPRESDesc) && RPRESDesc[Value] != NULL) {
    Description = RPRESDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "WFxT";
  Value = Aa64Isar2 & 0xf;
  if (Value < ARRAY_SIZE(WFxTDesc) && WFxTDesc[Value] != NULL) {
    Description = WFxTDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64DFR0_EL1 system register.

  @param[in] Aa64Dfr0  value of ID_AA64DFR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Dfr0 (
  CONST UINT64  Aa64Dfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "DFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *HPMN0Desc[] = {
    "Setting MDCR_EL2.HPMN to zero has CONSTRAINED UNPREDICTABLE behavior.",
    "FEAT_HPMN0 implemented."
  };
  STATIC CONST CHAR8 *ExtTrcBuffDesc[] = {
    "Trace Buffer External Mode not implemented.",
    "FEAT_TRBE_EXT implemented."
  };
  STATIC CONST CHAR8 *BRBEDesc[] = {
    "FEAT_BRBE not implemented.",
    "FEAT_BRBE implemented.",
    "FEAT_BRBEv1p1 implemented."
  };
  STATIC CONST CHAR8 *MTPMUDesc[] = {
    [0] = "FEAT_MTPMU not implemented.",
    [1] = "FEAT_MTPMU and FEAT_PMUv3 implemented.",
    [15] = "FEAT_MTPMU not implemented."
  };
  STATIC CONST CHAR8 *TraceBufferDesc[] = {
    "FEAT_TRBE not implemented.",
    "FEAT_TRBE implemented.",
    "FEAT_TRBEv1p1 implemented."
  };
  STATIC CONST CHAR8 *TraceFiltDesc[] = {
    "FEAT_TRF not implemented.",
    "FEAT_TRF implemented."
  };
  STATIC CONST CHAR8 *DoubleLockDesc[] = {
    [0] = "FEAT_DoubleLock implemented.",
    [15] = "FEAT_DoubleLock not implemented."
  };
  STATIC CONST CHAR8 *PMSVerDesc[] = {
    "FEAT_SPE not implemented.",
    "FEAT_SPE implemented.",
    "FEAT_SPEv1p1 implemented.",
    "FEAT_SPEv1p2 implemented.",
    "FEAT_SPEv1p3 implemented.",
    "FEAT_SPEv1p4 implemented.",
    "FEAT_SPEv1p5 implemented."
  };
  STATIC CONST CHAR8 *CTX_CMPsDesc[] = {
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1.",
    "Number of breakpoints that are context-aware, minus 1."
  };
  STATIC CONST CHAR8 *WRPsDesc[] = {
    "reserved",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1.",
    "Number of watchpoints, minus 1."
  };
  STATIC CONST CHAR8 *PMSSDesc[] = {
    "FEAT_PMUv3_SS not implemented.",
    "FEAT_PMUv3_SS implemented."
  };
  STATIC CONST CHAR8 *BRPsDesc[] = {
    "reserved",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1.",
    "Number of breakpoints, minus 1."
  };
  STATIC CONST CHAR8 *PMUVerDesc[] = {
    [0] = "Performance Monitors Extension not implemented.",
    [1] = "FEAT_PMUv3 implemented.",
    [4] = "FEAT_PMUv3p1 implemented.",
    [5] = "FEAT_PMUv3p4 implemented.",
    [6] = "FEAT_PMUv3p5 implemented.",
    [7] = "FEAT_PMUv3p7 implemented.",
    [8] = "FEAT_PMUv3p8 implemented.",
    [9] = "FEAT_PMUv3p9 implemented.",
    [15] = "IMPLEMENTATION DEFINED form of performance monitors supported."
  };
  STATIC CONST CHAR8 *TraceVerDesc[] = {
    "Trace unit System registers not implemented.",
    "Trace unit System registers implemented."
  };
  STATIC CONST CHAR8 *DebugVerDesc[] = {
    [6] = "Armv8 debug architecture",
    [7] = "Armv8 debug architecture with VHE",
    [8] = "FEAT_Debugv8p2 implemented.",
    [9] = "FEAT_Debugv8p4 implemented.",
    [10] = "FEAT_Debugv8p8 implemented.",
    [11] = "FEAT_Debugv8p9 implemented."
  };

  Bits  = "63:60";
  Name  = "HPMN0";
  Value = (Aa64Dfr0 >> 60) & 0xf;
  if (Value < ARRAY_SIZE(HPMN0Desc) && HPMN0Desc[Value] != NULL) {
    Description = HPMN0Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "ExtTrcBuff";
  Value = (Aa64Dfr0 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(ExtTrcBuffDesc) && ExtTrcBuffDesc[Value] != NULL) {
    Description = ExtTrcBuffDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "BRBE";
  Value = (Aa64Dfr0 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(BRBEDesc) && BRBEDesc[Value] != NULL) {
    Description = BRBEDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "51:48";
  Name  = "MTPMU";
  Value = (Aa64Dfr0 >> 48) & 0xf;
  if (Value < ARRAY_SIZE(MTPMUDesc) && MTPMUDesc[Value] != NULL) {
    Description = MTPMUDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "TraceBuffer";
  Value = (Aa64Dfr0 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(TraceBufferDesc) && TraceBufferDesc[Value] != NULL) {
    Description = TraceBufferDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "TraceFilt";
  Value = (Aa64Dfr0 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(TraceFiltDesc) && TraceFiltDesc[Value] != NULL) {
    Description = TraceFiltDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "DoubleLock";
  Value = (Aa64Dfr0 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(DoubleLockDesc) && DoubleLockDesc[Value] != NULL) {
    Description = DoubleLockDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "PMSVer";
  Value = (Aa64Dfr0 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(PMSVerDesc) && PMSVerDesc[Value] != NULL) {
    Description = PMSVerDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "31:28";
  Name  = "CTX_CMPs";
  Value = (Aa64Dfr0 >> 28) & 0xf;
  if (Value < ARRAY_SIZE(CTX_CMPsDesc) && CTX_CMPsDesc[Value] != NULL) {
    Description = CTX_CMPsDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "WRPs";
  Value = (Aa64Dfr0 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(WRPsDesc) && WRPsDesc[Value] != NULL) {
    Description = WRPsDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "PMSS";
  Value = (Aa64Dfr0 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(PMSSDesc) && PMSSDesc[Value] != NULL) {
    Description = PMSSDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "15:12";
  Name  = "BRPs";
  Value = (Aa64Dfr0 >> 12) & 0xf;
  if (Value < ARRAY_SIZE(BRPsDesc) && BRPsDesc[Value] != NULL) {
    Description = BRPsDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "11:8 ";
  Name  = "PMUVer";
  Value = (Aa64Dfr0 >> 8) & 0xf;
  if (Value < ARRAY_SIZE(PMUVerDesc) && PMUVerDesc[Value] != NULL) {
    Description = PMUVerDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "TraceVer";
  Value = (Aa64Dfr0 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(TraceVerDesc) && TraceVerDesc[Value] != NULL) {
    Description = TraceVerDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "DebugVer";
  Value = Aa64Dfr0 & 0xf;
  if (Value < ARRAY_SIZE(DebugVerDesc) && DebugVerDesc[Value] != NULL) {
    Description = DebugVerDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64ZFR0_EL1 system register.

  @param[in] Aa64Zfr0  value of ID_AA64ZFR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Zfr0 (
  CONST UINT64  Aa64Zfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "ZFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *F64MMDesc[] = {
    "FEAT_F64MM SVE not implemented",
    "FEAT_F64MM SVE implemented"
  };
  STATIC CONST CHAR8 *F32MMDesc[] = {
    "FEAT_F32MM SVE not implemented",
    "FEAT_F32MM SVE implemented"
  };
  STATIC CONST CHAR8 *I8MMDesc[] = {
    "FEAT_I8MM SVE not implemented.",
    "FEAT_I8MM SVE implemented."
  };
  STATIC CONST CHAR8 *SM4Desc[] = {
    "FEAT_SVE_SM4 not implemented.",
    "FEAT_SVE_SM4 implemented."
  };
  STATIC CONST CHAR8 *SHA3Desc[] = {
    "FEAT_SVE_SHA3 not implemented.",
    "FEAT_SVE_SHA3 implemented."
  };
  STATIC CONST CHAR8 *B16B16Desc[] = {
    "FEAT_SVE_B16B16 not implemented.",
    "FEAT_SVE_B16B16 implemented."
  };
  STATIC CONST CHAR8 *BF16Desc[] = {
    "SVE BFloat16 not implemented.",
    "FEAT_BF16 SVE implemented.",
    "FEAT_EBF16 SVE implemented."
  };
  STATIC CONST CHAR8 *BitPermDesc[] = {
    "FEAT_SVE_BitPerm not implemented.",
    "FEAT_SVE_BitPerm implemented."
  };
  STATIC CONST CHAR8 *AESDesc[] = {
    "FEAT_SVE_AES not implemented.",
    "FEAT_SVE_AES implemented.",
    "FEAT_SVE_AES and FEAT_SVE_PMULL128 implemented."
  };
  STATIC CONST CHAR8 *SVEverDesc[] = {
    "FEAT_SVE implemented.",
    "FEAT_SVE2 implemented.",
    "FEAT_SVE2p1 implemented."
  };

  Bits  = "59:56";
  Name  = "F64MM";
  Value = (Aa64Zfr0 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(F64MMDesc) && F64MMDesc[Value] != NULL) {
    Description = F64MMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "F32MM";
  Value = (Aa64Zfr0 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(F32MMDesc) && F32MMDesc[Value] != NULL) {
    Description = F32MMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "I8MM";
  Value = (Aa64Zfr0 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(I8MMDesc) && I8MMDesc[Value] != NULL) {
    Description = I8MMDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "43:40";
  Name  = "SM4";
  Value = (Aa64Zfr0 >> 40) & 0xf;
  if (Value < ARRAY_SIZE(SM4Desc) && SM4Desc[Value] != NULL) {
    Description = SM4Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "35:32";
  Name  = "SHA3";
  Value = (Aa64Zfr0 >> 32) & 0xf;
  if (Value < ARRAY_SIZE(SHA3Desc) && SHA3Desc[Value] != NULL) {
    Description = SHA3Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "27:24";
  Name  = "B16B16";
  Value = (Aa64Zfr0 >> 24) & 0xf;
  if (Value < ARRAY_SIZE(B16B16Desc) && B16B16Desc[Value] != NULL) {
    Description = B16B16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "23:20";
  Name  = "BF16";
  Value = (Aa64Zfr0 >> 20) & 0xf;
  if (Value < ARRAY_SIZE(BF16Desc) && BF16Desc[Value] != NULL) {
    Description = BF16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "19:16";
  Name  = "BitPerm";
  Value = (Aa64Zfr0 >> 16) & 0xf;
  if (Value < ARRAY_SIZE(BitPermDesc) && BitPermDesc[Value] != NULL) {
    Description = BitPermDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "7:4 ";
  Name  = "AES";
  Value = (Aa64Zfr0 >> 4) & 0xf;
  if (Value < ARRAY_SIZE(AESDesc) && AESDesc[Value] != NULL) {
    Description = AESDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "3:0 ";
  Name  = "SVEver";
  Value = Aa64Zfr0 & 0xf;
  if (Value < ARRAY_SIZE(SVEverDesc) && SVEverDesc[Value] != NULL) {
    Description = SVEverDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Handle ID_AA64SMFR0_EL1 system register.

  @param[in] Aa64Smfr0  value of ID_AA64SMFR0_EL1 system register

  @retval Number of unknown field values encountered
**/
UINT32
HandleAa64Smfr0 (
  CONST UINT64  Aa64Smfr0
  )
{
  UINT64              Value;
  STATIC CONST CHAR8  RegName[] = "SMFR0";
  CONST CHAR8         *Description;
  CONST CHAR8         *Name;
  CONST CHAR8         *Bits;
  UINT32              UnknownCount = 0;

  STATIC CONST CHAR8 *FA64Desc[] = {
    "FEAT_SME_FA64 not implemented.",
    "FEAT_SME_FA64 implemented."
  };
  STATIC CONST CHAR8 *LUTv2Desc[] = {
    "FEAT_SME_LUTv2 not implemented.",
    "FEAT_SME_LUTv2 implemented."
  };
  STATIC CONST CHAR8 *SMEverDesc[] = {
    "Mandatory SME instructions are implemented.",
    "FEAT_SME2 implemented.",
    "FEAT_SME2p1 implemented."
  };
  STATIC CONST CHAR8 *I16I64Desc[] = {
    [0] = "FEAT_SME_I16I64 not implemented",
    [15] = "FEAT_SME_I16I64 implemented"
  };
  STATIC CONST CHAR8 *F64F64Desc[] = {
    "FEAT_SME_F64F64 not implemented.",
    "FEAT_SME_F64F64 implemented."
  };
  STATIC CONST CHAR8 *I16I32Desc[] = {
    [0] = "SME2 I16I32 not implemented.",
    [5] = "SME2 I16I32 implemented."
  };
  STATIC CONST CHAR8 *B16B16Desc[] = {
    "FEAT_SME_B16B16 not implemented.",
    "FEAT_SME_B16B16 implemented."
  };
  STATIC CONST CHAR8 *F16F16Desc[] = {
    "FEAT_SME_F16F16 not implemented.",
    "FEAT_SME_F16F16 implemented."
  };
  STATIC CONST CHAR8 *F8F16Desc[] = {
    "FEAT_SME_F8F16 not implemented.",
    "FEAT_SME_F8F16 implemented."
  };
  STATIC CONST CHAR8 *F8F32Desc[] = {
    "FEAT_SME_F8F32 not implemented.",
    "FEAT_SME_F8F32 implemented."
  };
  STATIC CONST CHAR8 *I8I32Desc[] = {
    [0] = "SME I8I32 not implemented.",
    [15] = "SME I8I32 implemented."
  };
  STATIC CONST CHAR8 *F16F32Desc[] = {
    "SME F16F32 not implemented.",
    "SME F16F32 implemented."
  };
  STATIC CONST CHAR8 *B16F32Desc[] = {
    "SME B16F32 not implemented.",
    "SME B16F32 implemented."
  };
  STATIC CONST CHAR8 *BI32I32Desc[] = {
    "SME BI32I32 not implemented.",
    "SME BI32I32 implemented."
  };
  STATIC CONST CHAR8 *F32F32Desc[] = {
    "SME F32F32 not implemented.",
    "SME F32F32 implemented."
  };
  STATIC CONST CHAR8 *SF8FMADesc[] = {
    "FEAT_SSVE_FP8FMA not implemented.",
    "FEAT_SSVE_FP8FMA implemented."
  };
  STATIC CONST CHAR8 *SF8DP4Desc[] = {
    "FEAT_SSVE_FP8DOT4 not implemented.",
    "FEAT_SSVE_FP8DOT4 implemented."
  };
  STATIC CONST CHAR8 *SF8DP2Desc[] = {
    "FEAT_SSVE_FP8DOT2 not implemented.",
    "FEAT_SSVE_FP8DOT2 implemented."
  };
  STATIC CONST CHAR8 *SBitPermDesc[] = {
    "FEAT_SSVE_BitPerm not implemented.",
    "FEAT_SSVE_BitPerm implemented."
  };
  STATIC CONST CHAR8 *AESDesc[] = {
    "FEAT_SSVE_AES not implemented.",
    "FEAT_SSVE_AES implemented."
  };
  STATIC CONST CHAR8 *SFEXPADesc[] = {
    "FEAT_SSVE_FEXPA not implemented.",
    "FEAT_SSVE_FEXPA implemented."
  };
  STATIC CONST CHAR8 *STMOPDesc[] = {
    "FEAT_SME_TMOP not implemented.",
    "FEAT_SME_TMOP implemented."
  };
  STATIC CONST CHAR8 *SMOP4Desc[] = {
    "FEAT_SME_MOP4 not implemented.",
    "FEAT_SME_MOP4 implemented."
  };

  Bits  = "   63";
  Name  = "FA64";
  Value = (Aa64Smfr0 >> 63) & 0x1;
  if (Value < ARRAY_SIZE(FA64Desc) && FA64Desc[Value] != NULL) {
    Description = FA64Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   60";
  Name  = "LUTv2";
  Value = (Aa64Smfr0 >> 60) & 0x1;
  if (Value < ARRAY_SIZE(LUTv2Desc) && LUTv2Desc[Value] != NULL) {
    Description = LUTv2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "59:56";
  Name  = "SMEver";
  Value = (Aa64Smfr0 >> 56) & 0xf;
  if (Value < ARRAY_SIZE(SMEverDesc) && SMEverDesc[Value] != NULL) {
    Description = SMEverDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "55:52";
  Name  = "I16I64";
  Value = (Aa64Smfr0 >> 52) & 0xf;
  if (Value < ARRAY_SIZE(I16I64Desc) && I16I64Desc[Value] != NULL) {
    Description = I16I64Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   48";
  Name  = "F64F64";
  Value = (Aa64Smfr0 >> 48) & 0x1;
  if (Value < ARRAY_SIZE(F64F64Desc) && F64F64Desc[Value] != NULL) {
    Description = F64F64Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "47:44";
  Name  = "I16I32";
  Value = (Aa64Smfr0 >> 44) & 0xf;
  if (Value < ARRAY_SIZE(I16I32Desc) && I16I32Desc[Value] != NULL) {
    Description = I16I32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   43";
  Name  = "B16B16";
  Value = (Aa64Smfr0 >> 43) & 0x1;
  if (Value < ARRAY_SIZE(B16B16Desc) && B16B16Desc[Value] != NULL) {
    Description = B16B16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   42";
  Name  = "F16F16";
  Value = (Aa64Smfr0 >> 42) & 0x1;
  if (Value < ARRAY_SIZE(F16F16Desc) && F16F16Desc[Value] != NULL) {
    Description = F16F16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   41";
  Name  = "F8F16";
  Value = (Aa64Smfr0 >> 41) & 0x1;
  if (Value < ARRAY_SIZE(F8F16Desc) && F8F16Desc[Value] != NULL) {
    Description = F8F16Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   40";
  Name  = "F8F32";
  Value = (Aa64Smfr0 >> 40) & 0x1;
  if (Value < ARRAY_SIZE(F8F32Desc) && F8F32Desc[Value] != NULL) {
    Description = F8F32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "39:36";
  Name  = "I8I32";
  Value = (Aa64Smfr0 >> 36) & 0xf;
  if (Value < ARRAY_SIZE(I8I32Desc) && I8I32Desc[Value] != NULL) {
    Description = I8I32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   35";
  Name  = "F16F32";
  Value = (Aa64Smfr0 >> 35) & 0x1;
  if (Value < ARRAY_SIZE(F16F32Desc) && F16F32Desc[Value] != NULL) {
    Description = F16F32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   34";
  Name  = "B16F32";
  Value = (Aa64Smfr0 >> 34) & 0x1;
  if (Value < ARRAY_SIZE(B16F32Desc) && B16F32Desc[Value] != NULL) {
    Description = B16F32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   33";
  Name  = "BI32I32";
  Value = (Aa64Smfr0 >> 33) & 0x1;
  if (Value < ARRAY_SIZE(BI32I32Desc) && BI32I32Desc[Value] != NULL) {
    Description = BI32I32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   32";
  Name  = "F32F32";
  Value = (Aa64Smfr0 >> 32) & 0x1;
  if (Value < ARRAY_SIZE(F32F32Desc) && F32F32Desc[Value] != NULL) {
    Description = F32F32Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   30";
  Name  = "SF8FMA";
  Value = (Aa64Smfr0 >> 30) & 0x1;
  if (Value < ARRAY_SIZE(SF8FMADesc) && SF8FMADesc[Value] != NULL) {
    Description = SF8FMADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   29";
  Name  = "SF8DP4";
  Value = (Aa64Smfr0 >> 29) & 0x1;
  if (Value < ARRAY_SIZE(SF8DP4Desc) && SF8DP4Desc[Value] != NULL) {
    Description = SF8DP4Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   28";
  Name  = "SF8DP2";
  Value = (Aa64Smfr0 >> 28) & 0x1;
  if (Value < ARRAY_SIZE(SF8DP2Desc) && SF8DP2Desc[Value] != NULL) {
    Description = SF8DP2Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   25";
  Name  = "SBitPerm";
  Value = (Aa64Smfr0 >> 25) & 0x1;
  if (Value < ARRAY_SIZE(SBitPermDesc) && SBitPermDesc[Value] != NULL) {
    Description = SBitPermDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   24";
  Name  = "AES";
  Value = (Aa64Smfr0 >> 24) & 0x1;
  if (Value < ARRAY_SIZE(AESDesc) && AESDesc[Value] != NULL) {
    Description = AESDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   23";
  Name  = "SFEXPA";
  Value = (Aa64Smfr0 >> 23) & 0x1;
  if (Value < ARRAY_SIZE(SFEXPADesc) && SFEXPADesc[Value] != NULL) {
    Description = SFEXPADesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "   16";
  Name  = "STMOP";
  Value = (Aa64Smfr0 >> 16) & 0x1;
  if (Value < ARRAY_SIZE(STMOPDesc) && STMOPDesc[Value] != NULL) {
    Description = STMOPDesc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  Bits  = "    0";
  Name  = "SMOP4";
  Value = Aa64Smfr0 & 0x1;
  if (Value < ARRAY_SIZE(SMOP4Desc) && SMOP4Desc[Value] != NULL) {
    Description = SMOP4Desc[Value];
  } else {
    Description = "unknown";
  }
  if (AsciiStrCmp(Description, "unknown") == 0) {
    UnknownCount++;
  }
  PrintValues (RegName, Name, Bits, Value, Description);

  return UnknownCount;
}

/**
  Process all ID_AA64*_EL1 registers.

  Reads all registers, prints their values, and calls handlers.
**/
VOID
ProcessAllRegisters (
  VOID
  )
{
  UINT64  Aa64Mmfr0;
  UINT64  Aa64Mmfr1;
  UINT64  Aa64Mmfr2;
  UINT64  Aa64Pfr0;
  UINT64  Aa64Pfr1;
  UINT64  Aa64Isar0;
  UINT64  Aa64Isar1;
  UINT64  Aa64Isar2;
  UINT64  Aa64Dfr0;
  UINT64  Aa64Zfr0;
  UINT64  Aa64Smfr0;
  UINT64  Aa64Afr0;
  UINT64  Aa64Afr1;
  UINT64  Aa64Dfr1;
  UINT64  Aa64Dfr2;
  UINT64  Aa64Fpfr0;
  UINT64  Aa64Isar3;
  UINT64  Aa64Mmfr4;
  UINT64  Aa64Pfr2;

  Aa64Mmfr0 = ArmReadIdAA64Mmfr0 ();
  Aa64Mmfr1 = ArmReadIdAA64Mmfr1 ();
  Aa64Mmfr2 = ArmReadIdAA64Mmfr2 ();
  Aa64Pfr0 = ArmReadIdAA64Pfr0 ();
  Aa64Pfr1 = ArmReadIdAA64Pfr1 ();
  Aa64Isar0 = ArmReadIdAA64Isar0 ();
  Aa64Isar1 = ArmReadIdAA64Isar1 ();
  Aa64Isar2 = ArmReadIdAA64Isar2 ();
  Aa64Dfr0 = ArmReadIdAA64Dfr0 ();
  Aa64Zfr0 = ArmReadIdAA64Zfr0 ();
  Aa64Smfr0 = ArmReadIdAA64Smfr0 ();
  Aa64Afr0 = ArmReadIdAA64Afr0 ();
  Aa64Afr1 = ArmReadIdAA64Afr1 ();
  Aa64Dfr1 = ArmReadIdAA64Dfr1 ();
  Aa64Dfr2 = ArmReadIdAA64Dfr2 ();
  Aa64Fpfr0 = ArmReadIdAA64Fpfr0 ();
  Aa64Isar3 = ArmReadIdAA64Isar3 ();
  Aa64Mmfr4 = ArmReadIdAA64Mmfr4 ();
  Aa64Pfr2 = ArmReadIdAA64Pfr2 ();

  AsciiPrint ("ID_AA64MMFR0_EL1 = 0x%016lx\n", Aa64Mmfr0);
  AsciiPrint ("ID_AA64MMFR1_EL1 = 0x%016lx\n", Aa64Mmfr1);
  AsciiPrint ("ID_AA64MMFR2_EL1 = 0x%016lx\n", Aa64Mmfr2);
  AsciiPrint ("ID_AA64PFR0_EL1  = 0x%016lx\n", Aa64Pfr0);
  AsciiPrint ("ID_AA64PFR1_EL1  = 0x%016lx\n", Aa64Pfr1);
  AsciiPrint ("ID_AA64ISAR0_EL1 = 0x%016lx\n", Aa64Isar0);
  AsciiPrint ("ID_AA64ISAR1_EL1 = 0x%016lx\n", Aa64Isar1);
  AsciiPrint ("ID_AA64ISAR2_EL1 = 0x%016lx\n", Aa64Isar2);
  AsciiPrint ("ID_AA64DFR0_EL1  = 0x%016lx\n", Aa64Dfr0);
  AsciiPrint ("ID_AA64ZFR0_EL1  = 0x%016lx\n", Aa64Zfr0);
  AsciiPrint ("ID_AA64SMFR0_EL1 = 0x%016lx\n", Aa64Smfr0);
  AsciiPrint ("ID_AA64AFR0_EL1  = 0x%016lx\n", Aa64Afr0);
  AsciiPrint ("ID_AA64AFR1_EL1  = 0x%016lx\n", Aa64Afr1);
  AsciiPrint ("ID_AA64DFR1_EL1  = 0x%016lx\n", Aa64Dfr1);
  AsciiPrint ("ID_AA64DFR2_EL1  = 0x%016lx\n", Aa64Dfr2);
  AsciiPrint ("ID_AA64FPFR0_EL1 = 0x%016lx\n", Aa64Fpfr0);
  AsciiPrint ("ID_AA64ISAR3_EL1 = 0x%016lx\n", Aa64Isar3);
  AsciiPrint ("ID_AA64MMFR4_EL1 = 0x%016lx\n", Aa64Mmfr4);
  AsciiPrint ("ID_AA64PFR2_EL1  = 0x%016lx\n", Aa64Pfr2);
  AsciiPrint ("\n");

  PrintText ("Reg", "Name", "Bits", "Value", "Feature");
  PrintSpacer ();

  UINT32 TotalUnknowns = 0;
  UINT32 UnknownCount = 0;
  UINT32 RegistersWithUnknowns = 0;
  CONST CHAR8 *RegisterNames[20];  // Max registers with unknowns

  UnknownCount = HandleAa64Mmfr0 (Aa64Mmfr0);
  PrintSpacer ();
  if (UnknownCount > 0) {
    RegisterNames[RegistersWithUnknowns++] = "MMFR0";
    TotalUnknowns += UnknownCount;
  }

  if (Aa64Mmfr1) {
    UnknownCount = HandleAa64Mmfr1 (Aa64Mmfr1, Aa64Pfr0);
    PrintSpacer ();
    if (UnknownCount > 0) {
      RegisterNames[RegistersWithUnknowns++] = "MMFR1";
      TotalUnknowns += UnknownCount;
    }
  }

  if (Aa64Mmfr2) {
    UnknownCount = HandleAa64Mmfr2 (Aa64Mmfr2);
    PrintSpacer ();
    if (UnknownCount > 0) {
      RegisterNames[RegistersWithUnknowns++] = "MMFR2";
      TotalUnknowns += UnknownCount;
    }
  }

  UnknownCount = HandleAa64Pfr0 (Aa64Pfr0);
  PrintSpacer ();
  if (UnknownCount > 0) {
    RegisterNames[RegistersWithUnknowns++] = "PFR0";
    TotalUnknowns += UnknownCount;
  }

  if (Aa64Pfr1) {
    UnknownCount = HandleAa64Pfr1 (Aa64Pfr1);
    PrintSpacer ();
    if (UnknownCount > 0) {
      RegisterNames[RegistersWithUnknowns++] = "PFR1";
      TotalUnknowns += UnknownCount;
    }
  }

  UnknownCount = HandleAa64Isar0 (Aa64Isar0);
  PrintSpacer ();
  if (UnknownCount > 0) {
    RegisterNames[RegistersWithUnknowns++] = "ISAR0";
    TotalUnknowns += UnknownCount;
  }

  if (Aa64Isar1) {
    UnknownCount = HandleAa64Isar1 (Aa64Isar1);
    PrintSpacer ();
    if (UnknownCount > 0) {
      RegisterNames[RegistersWithUnknowns++] = "ISAR1";
      TotalUnknowns += UnknownCount;
    }
  }

  if (Aa64Isar2) {
    UnknownCount = HandleAa64Isar2 (Aa64Isar2);
    PrintSpacer ();
    if (UnknownCount > 0) {
      RegisterNames[RegistersWithUnknowns++] = "ISAR2";
      TotalUnknowns += UnknownCount;
    }
  }

  UnknownCount = HandleAa64Dfr0 (Aa64Dfr0);
  PrintSpacer ();
  if (UnknownCount > 0) {
    RegisterNames[RegistersWithUnknowns++] = "DFR0";
    TotalUnknowns += UnknownCount;
  }

  UnknownCount = HandleAa64Zfr0 (Aa64Zfr0);
  PrintSpacer ();
  if (UnknownCount > 0) {
    RegisterNames[RegistersWithUnknowns++] = "ZFR0";
    TotalUnknowns += UnknownCount;
  }

  UnknownCount = HandleAa64Smfr0 (Aa64Smfr0);
  PrintSpacer ();
  if (UnknownCount > 0) {
    RegisterNames[RegistersWithUnknowns++] = "SMFR0";
    TotalUnknowns += UnknownCount;
  }

  // Print summary of unknown values
  if (TotalUnknowns > 0) {
    AsciiPrint ("\n");
    AsciiPrint ("WARNING: %u field(s) have unknown/undefined values!\n", TotalUnknowns);
    AsciiPrint ("Affected registers: ");
    for (UINT32 i = 0; i < RegistersWithUnknowns; i++) {
      AsciiPrint ("%a", RegisterNames[i]);
      if (i < RegistersWithUnknowns - 1) {
        AsciiPrint (", ");
      }
    }
    AsciiPrint ("\n");
    AsciiPrint ("\n");
    AsciiPrint ("This may indicate:\n");
    AsciiPrint ("  - New CPU features not yet documented in YAML\n");
    AsciiPrint ("  - Reserved field values being used\n");
    AsciiPrint ("  - Incorrect register value\n");
    AsciiPrint ("\n");
    AsciiPrint ("Consider reporting at: https://github.com/hrw/edk2-armcpuinfo/issues\n");
  }

  // Check if any unhandled registers have non-zero values
  if (Aa64Afr0 | Aa64Afr1 | Aa64Dfr1 | Aa64Dfr2 | Aa64Fpfr0 |
      Aa64Isar3 | Aa64Mmfr4 | Aa64Pfr2) {
    AsciiPrint ("\n");
    AsciiPrint ("Your system has unhandled registers with non-zero values.\n");
    AsciiPrint ("Please contact author and report at:\n");
    AsciiPrint ("  https://github.com/hrw/edk2-armcpuinfo/issues\n");
    AsciiPrint ("\n");
  }
}
