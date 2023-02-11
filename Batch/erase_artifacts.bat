echo Remove directory %1
if exist %1\Platforms\.vs (rmdir %1\Platforms\.vs /s /q)
if exist %1\Platforms\Linux\nxp_imx6 (rmdir %1\Platforms\Linux\arm /s /q)
if exist %1\Platforms\Linux\nxp_imx8 (rmdir %1\Platforms\Linux\arm64 /s /q)
if exist %1\Platforms\Linux\pi (rmdir %1\Platforms\Linux\pi64 /s /q)
if exist %1\Platforms\Linux\x64  (rmdir %1\Platforms\Linux\x64 /s /q)
if exist %1\Platforms\Windows\x64 (rmdir %1\Platforms\Windows\x64 /s /q)
if exist %1\Platforms\Windows\x86 (rmdir %1\Platforms\Windows\x86 /s /q)
