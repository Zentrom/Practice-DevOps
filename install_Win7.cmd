call :Resume
goto %current%
goto :eof

:one
REM .NET 4.5.2
powershell (New-Object Net.WebClient).DownloadFile('https://download.microsoft.com/download/E/2/1/E21644B5-2DF2-47C2-91BD-63C560427900/NDP452-KB2901907-x86-x64-AllOS-ENU.exe', 'NDP452-KB2901907-x86-x64-AllOS-ENU.exe')
start /wait .\NDP452-KB2901907-x86-x64-AllOS-ENU.exe /passive /norestart
REM Powershell v2 -> v3
powershell (New-Object Net.WebClient).DownloadFile('https://download.microsoft.com/download/E/7/6/E76850B8-DA6E-4FF5-8CCE-A24FC513FD16/Windows6.1-KB2506143-x64.msu', 'Windows6.1-KB2506143-x64.msu')
start /wait .\Windows6.1-KB2506143-x64.msu /quiet /norestart
REM Add script to run after restart
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\RunOnce /v "%~n0" /d "%~dpnx0" /f
echo two >%~dp0current.txt
shutdown -r -t 180 /c "Restarting in 3 minutes to update PowerShell V3. Installation will continue..."
pause
goto :eof

:two
REM Get back to dir saved in registry
cd %~dp0
del %~dp0current.txt
REM 7zip
powershell [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;iwr 'https://www.7-zip.org/a/7z2201-x64.msi' -OutFile '7z2201-x64.msi'
start /wait .\7z2201-x64.msi /passive /norestart
echo Login to Visual Studio Dev Essentials with a Microsoft Account. Open the downloaded GetLink.json file with notepad. Copy the url without paranthesis. Close Internet Explorer.
"C:\Program Files\Internet Explorer\iexplore.exe" "https://my.visualstudio.com/_apis/Download/GetLink?friendlyFileName=mu_visual_cpp_build_tools_2015_update_3_x64_dvd_dfd9a39c.iso&upn=&productId=2083"
set /p url= "Enter the complete download URL(NO paranthesis):" 
echo "%url%"
REM VS Studio 2015 C++ Build Tools Update 3
powershell -command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;iwr '%url%' -OutFile 'mu_visual_cpp_build_tools_2015_update_3_x64_dvd_dfd9a39c.iso'} "
REM Extract the downloaded .iso
"C:\Program Files\7-Zip\7z.exe" x mu_visual_cpp_build_tools_2015_update_3_x64_dvd_dfd9a39c.iso
start /wait .\VisualCppBuildTools_Full.exe /Passive /NoRestart
REM Build project
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild.exe" Practice-DevOps.sln -p:Configuration=Release
"C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild.exe" Practice-DevOps.sln -p:Configuration=Debug
echo INSTALLATION AND BUILD FINISHED
pause
goto :eof

:resume
REM Check if restart happened
if exist %~dp0current.txt (
    set /p current=<%~dp0current.txt
) else (
    set current=one
)
