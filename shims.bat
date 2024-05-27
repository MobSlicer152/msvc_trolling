for %%x in (1 1ast 2) do (
	if not exist "%XEDK%\bin\win32\c%%x_orig.dll" move "%XEDK%\bin\win32\c%%x.dll" "%XEDK%\bin\win32\c%%x_orig.dll"
	cl /Zi /LDd %~dp0shim.c -DPASSNUM=%%x /link /out:"%XEDK%\bin\win32\c%%x.dll" /def:"%~dp0c%%x.def"
)
