/** @file
  Application to present AArch64 cpu information.

  Based on ARM DDI 0487: https://developer.arm.com/documentation/ddi0487

Copyright (c) 2023, Linaro Ltd. All rights reserved.<BR>
Copyright (c) Marcin Juszkiewicz<BR>

SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/UefiLib.h>
#include "id_aa64.h"

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
  AsciiPrint ("ArmCpuInfo v1.4.1\n\n");

  // All register processing is now handled by generated code
  ProcessAllRegisters ();

  return EFI_SUCCESS;
}
