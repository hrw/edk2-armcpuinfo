#------------------------------------------------------------------------------
#
# Copyright (c) 2008 - 2010, Apple Inc. All rights reserved.<BR>
# Copyright (c) 2011 - 2017, ARM Limited. All rights reserved.
# Copyright (c) 2016 - 2024, Linaro Limited. All rights reserved.
# Copyright (c) 2020, NUVIA Inc. All rights reserved.
# Copyright (c) Marcin Juszkiewicz
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
#------------------------------------------------------------------------------

#include <AArch64/AArch64.h>
#include <AsmMacroLib.h>

ASM_FUNC(ArmReadIdAA64Afr0)
  mrs   x0, ID_AA64AFR0_EL1
  ret

ASM_FUNC(ArmReadIdAA64Afr1)
  mrs   x0, ID_AA64AFR1_EL1
  ret

ASM_FUNC(ArmReadIdAA64Dfr2)
  mrs   x0, s3_0_c0_c7_2
#  mrs   x0, ID_AA64DFR2_EL1
  ret

ASM_FUNC(ArmReadIdAA64Fpfr0)
  mrs   x0, s3_0_c0_c4_7
#  mrs   x0, ID_AA64FPFR0_EL1
  ret

ASM_FUNC(ArmReadIdAA64Isar3)
  mrs   x0, s3_0_c0_c6_3
#  mrs   x0, ID_AA64ISAR3_EL1
  ret

ASM_FUNC(ArmReadIdAA64Mmfr3)
  mrs   x0, s3_0_c0_c7_3
#  mrs   x0, ID_AA64MMFR3_EL1
  ret

ASM_FUNC(ArmReadIdAA64Mmfr4)
  mrs   x0, s3_0_c0_c7_4
#  mrs   x0, ID_AA64MMFR4_EL1
  ret

ASM_FUNC(ArmReadIdAA64Smfr0)
  mrs   x0, ID_AA64SMFR0_EL1
  ret

ASM_FUNC(ArmReadIdAA64Zfr0)
  mrs   x0, s3_0_c0_c4_4
#  mrs   x0, ID_AA64ZFR0_EL1
  ret
