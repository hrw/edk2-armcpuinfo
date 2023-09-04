#include <Chipset/AArch64.h>
#include <AsmMacroIoLibV8.h>

ASM_FUNC(ArmReadIdAA64Smfr0)
  mrs   x0, ID_AA64SMFR0_EL1
  ret

ASM_FUNC(ArmReadIdAA64Zfr0)
  mrs   x0, ID_AA64ZFR0_EL1
  ret

