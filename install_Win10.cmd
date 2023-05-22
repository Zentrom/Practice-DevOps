REM VS Build Tools 2022 C++
powershell iwr 'https://aka.ms/vs/17/release/vs_BuildTools.exe' -OutFile 'vs_BuildTools.exe'
start /wait .\vs_BuildTools.exe --add Microsoft.VisualStudio.Component.VC.140 --add Microsoft.VisualStudio.Component.Windows10SDK.19041 --add Microsoft.VisualStudio.Component.VC.Redist.14.Latest --passive --norestart --wait --nocache
REM Build Project with 2015 Toolset
"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe" /p:Configuration=Release;Platform=x64;WindowsTargetPlatformVersion=10.0.19041.0;PlatformToolset=v140;VCTargetsPath="C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\v140" /t:build
"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe" /p:Configuration=Debug;Platform=x64;WindowsTargetPlatformVersion=10.0.19041.0;PlatformToolset=v140;VCTargetsPath="C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\v140" /t:build
