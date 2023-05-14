## Windows 7 install
You can use this script to install and build the project and all it needs on a virtual Windows 7 OS, with minimal interaction.  
If you have VS Studio 2015 already, then you don't need this.  
This installs **VS Studio 2015 C++ Build Tools(MSBuild)** and everything that's needed to get there. You can always check the comments of [install_Win7.cmd](https://github.com/Zentrom/Practice-DevOps/blob/dev2/docs/install_Win7.cmd) (_lines starting with REM_) to see what gets installed. 

### Warnings:
- Don't use this script on a native OS, unless you know what you're doing!
- The download links might become dead. If that's the case, you need to continue manually where you left off.
- Be aware that this script will auto-restart your computer when it needs to apply the Powershell V3 update.

### Prerequisites
1. Windows 7 with important Windows updates already installed.
2. [Git](https://git-scm.com/downloads)
3. A Microsoft account.

### Usage
1. Start ``cmd`` with admin rights. Navigate inside the ``Practice-DevOps`` repository.
2. Launch the script: ``.\install_Win7.cmd``
3. The script will need to restart the PC at some point, and will give you 3 minutes to close things if needed. (You don't have to wait for the auto-restart)
4. After the restart, the script will continue the installation, but it'll start to ask for admin rights.
5. When Internet Explorer opens, you need to authenticate with your Microsoft account. Then, open the ``GetLink.json`` and copy the **url** without paranthesis inside the **cmd**.
6. When everything is done, you can find the completed builds in the ``Build\`` directory.