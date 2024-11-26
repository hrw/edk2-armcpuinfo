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
