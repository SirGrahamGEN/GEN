echo Remove directory %1
if exist %1\Platforms\.vs (rmdir %1\Platforms\.vs /s /q)
if exist %1\Platforms\Linux (rmdir %1\Platforms\Linux /s /q)
if exist %1\Platforms\Windows (rmdir %1\Platforms\Windows /s /q)
if exist %1\Platforms\Android (rmdir %1\Platforms\Android /s /q)
