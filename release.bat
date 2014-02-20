set NAME=cfscc
set VERSION=1.0.0
set DIR_NAME=%NAME%-%VERSION%
set ZIP_NAME=%NAME%-windows-%VERSION%
set BIN_DIR=bin
set TOP=%BIN_DIR%\%NAME%-%VERSION%

echo off

rmdir /S /Q %BIN_DIR% 2> nul

:setup_directories
echo Creating Directories...
mkdir %TOP%\
for %%A in (src, docs, examples, utils) do mkdir %TOP%\%%A
for %%A in (test, loop, r2f) do mkdir %TOP%\utils\%%A

:build_library_and_utils
echo Building Library and Utilities...
nmake clean & nmake & nmake DEBUG
for %%A in (test, loop, r2f) do cd utils\%%A\ & nmake clean & nmake & cd ..\..

:copy_files
echo Copying Release Files...
for %%A in (.dll, d.dll, .lib, d.lib, d.pdb) do copy %NAME%%%A %TOP%\ > nul

:copy_source
echo Copying Source Code Files...
copy docs\*.md %TOP%\docs\ > nul
copy examples\*.c %TOP%\examples\ > nul
copy src\*.c %TOP%\src\ > nul
copy src\*.h %TOP%\src\ > nul

:copy_utlities
echo Copying Utilities...
for %%A in (test, loop, r2f) do copy utils\%%A\*.c %TOP%\utils\%%A\ > nul
for %%A in (test, loop, r2f) do copy utils\%%A\*.exe %TOP%\utils\%%A\ > nul
for %%A in (test, loop, r2f) do copy utils\%%A\makefile %TOP%\utils\%%A\ > nul

:copy_changelog
echo Copying ChangeLog...
copy ChangeLog.md %TOP%\ > nul

:copy_readme
echo Copying README...
copy README.md %TOP%\ > nul

:zip_packages
echo Zipping Drivers...
cd %TOP%\ > nul
cd ..\ > nul
..\7za.exe a -tzip %ZIP_NAME%.zip %DIR_NAME% > nul
cd ..\ > nul