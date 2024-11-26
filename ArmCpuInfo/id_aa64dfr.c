/** @file

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) 2023 - 2024, Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "common.h"

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

  Bits  = "59:56";
  Name  = "ExtTrcBuff";
  Value = (Aa64Dfr0 >> 56) & 0xf;
  switch (Value) {
    case b0000:
      Description = "Trace Buffer External Mode not implemented.";
      break;
    case b0001:
      Description = "FEAT_TRBE_EXT implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

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
    case b0101:
      Description = "FEAT_SPEv1p4 implemented.";
      break;
    case b0110:
      Description = "FEAT_SPE_SME implemented.";
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

  Bits  = "27:24";
  Name  = "SEBEP";
  Value = (Aa64Dfr0 >> 24) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_SEBEP not implemented.";
      break;
    case b0001:
      Description = "FEAT_SEBEP implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

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

  Bits  = "19:16";
  Name  = "PMSS";
  Value = (Aa64Dfr0 >> 16) & 0xf;
  switch (Value) {
    case b0000:
      Description = "FEAT_PMUv2_SS not implemented.";
      break;
    case b0001:
      Description = "FEAT_PMUv2_SS implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);

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
    case b1001:
      Description = "FEAT_PMUv3p9 implemented.";
      break;
    case b1010:
      Description = "FEAT_PMUv3_SME implemented.";
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
    case b1011:
      Description = "FEAT_Debugv8p9 implemented.";
      break;
    default:
      Description = "unknown";
      break;
  }

  PrintValues (RegName, Name, Bits, Value, Description);
}


