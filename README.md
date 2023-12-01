# Arm cpu information command for UEFI Shell

The goal of this command is to show which cpu features/flags are supported.

Example output:

```
[..]
------|-------------|-------|-------|----------------------------------------------
MMFR0 | ECV         | 63:60 |  0000 | FEAT_ECV not implemented.
MMFR0 | FGT         | 59:56 |  0000 | FEAT_FGT not implemented.
MMFR0 | ExS         | 47:44 |  0000 | FEAT_ExS not implemented.
MMFR0 | TGran4      | 31:28 |  0000 |  4KB granule supported.
MMFR0 | TGran4_2    | 43:40 |  0000 |  4KB granule support at stage2 as above.
MMFR0 | Tgran16     | 23:20 |  0001 | 16KB granule supported.
MMFR0 | TGran16_2   | 35:32 |  0000 | 16KB granule support at stage2 as above.
MMFR0 | TGran64     | 27:24 |  0000 | 64KB granule supported.
MMFR0 | TGran64_2   | 39:36 |  0000 | 64KB granule support at stage2 as above.
MMFR0 | SNSMem      | 15:12 |  0001 | Supports a distinction between Secure and Non-Secure Memory.
MMFR0 | BigEnd      | 11:8  |  0001 | Mixed-endian support.
MMFR0 | BigEndEL0   | 19:16 |  0000 | No mixed-endian support at EL0.
MMFR0 | ASIDBits    |  7:4  |  0010 | ASID: 16 Bits
MMFR0 | PARange     |  3:0  |  0101 | 48 Bits (256TB) of physical address range supported.
------|-------------|-------|-------|----------------------------------------------
[..]
```


## Build instructions

1. clone this repository
2. clone [edk2](https://github.com/tianocore/edk2) repository
3. symlink ArmCpuInfo/ directory into edk2/ArmPkg/Application/ArmCpuInfo
4. edit edk2/ArmPkg/ArmPkg.dsc file and add one line into "[Components.AARCH64]"
   section:
   ```
   ArmPkg/Application/ArmCpuInfo/ArmCpuInfo.inf
   ```
5. build using this command:
   ```
   build -t GCC -a AARCH64 -b RELEASE -m edk2/ArmPkg/Application/ArmCpuInfo/ArmCpuInfo.inf -p edk2/ArmPkg/ArmPkg.dsc
   ```
6. resulting binary will be in "Build/Arm/RELEASE_GCC/AARCH64/" directory
