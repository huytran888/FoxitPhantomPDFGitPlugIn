# FoxitPhantomPDFGitPlugIn
This plug-in adds Git features to Foxit PhantomPDF (PDF Editor).  The idea is to help with keeping revision of PDFs that exist in git repositories.  

# Prerequisites
Install Foxit PhantomPDF 10.x (Windows) or higher.  You can download the trial here: https://www.foxitsoftware.com/downloads/#Foxit-PhantomPDF-Business/.
The project will output files to "C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF" and "C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins". You will need to grant permissions to allow this to occur.  Using "Windows Explorer", got to both directory directory, right click and choose "Properties," select the "Security", select "User (XXXX\Users)", select "Edit", and set "Full control" to allow.
Install Visual Studio 2010 to 2017

# Building
* Open Samples\RibbonElements\RibbonElements.sln with Visual Studio
* Build and Run

# Test
* In Visual Studio select Debug
* Start Debugging or Start without Debugging
* Foxit PhantomPDF will start, Select the "Git" Menu
* Select the Clone Button in the "Git Panel"
* Input the git repository in the first text field
* Select the "Choose Path" to choose the path you want to clone too
* Select the "Clone" Button in the dailog windows
* See that it has cloned

# To-do
- [ ] Impliment Pull button
- [ ] Impliment Commit button
- [ ] Impliment Push button

# Credit
This project uses library from https://github.com/libgit2/libgit2
