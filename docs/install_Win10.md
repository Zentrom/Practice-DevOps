## Windows 10 install & build
You can use this script to install and build the project and all it needs on a virtual Windows 10 OS, with no additional interaction needed.  
If you have VS Studio 2015 or newer already, then you don't need this.  
This installs **VS Studio 2022 Build Tools** with **MSVC v140**, **Windows 10 SDK** and **C++ Runtime 2022**.  
Further details in [install_Win10.cmd](https://github.com/Zentrom/Practice-DevOps/blob/dev2/install_Win10.cmd)  
**The script should work on Windows 11 aswell**.  
The download link this script uses might become dead in the future.

### Prerequisites
1. Windows 10.
2. [Git](https://git-scm.com/downloads)
3. ~10GB free space on C: drive.

### Usage
1. Start ``cmd`` with admin rights. Navigate inside the ``Practice-DevOps`` repository.
2. Launch the script: ``.\install_Win10.cmd``
3. When it's done, you can find the completed builds inside the ``Build\`` directory.