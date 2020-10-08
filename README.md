# FoxitPhantomPDFGitPlugIn
This plug-in adds Git features to Foxit PhantomPDF (PDF Editor).  The idea is to help with keeping revision of PDFs that exist in git repositories.  

# Prerequisites
1. Install Foxit PhantomPDF 10.x (Windows) or higher.  You can download the trial here: https://www.foxitsoftware.com/downloads/#Foxit-PhantomPDF-Business/.
1. The project will output files to "C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF" and "C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins". You will need to grant permissions to allow this to occur.  Using "Windows Explorer", got to both directory directory, right click and choose "Properties," select the "Security", select "User (XXXX\Users)", select "Edit", and set "Full control" to allow.
1. Install Visual Studio 2010 to 2017

# Building
1. Open Samples\RibbonElements\RibbonElements.sln with Visual Studio
1. Build and Run

# Test
1. In Visual Studio select Debug
1. Start Debugging or Start without Debugging
1. Foxit PhantomPDF will start, Select the "Git" Menu
1. Select the Clone Button in the "Git Panel"
1. Input the git repository in the first text field
1. Select the "Choose Path" to choose the path you want to clone too
1. Select the "Clone" Button in the dailog windows
1. See that it has cloned

# To-do
- [ ] Impliment Pull button
- [ ] Impliment Commit button
- [ ] Impliment Push button

# Credit
This project uses library from https://github.com/libgit2/libgit2

# Foxit Student Bounty Project
Are you a student who is interested in this project?  This project is a part of the Foxit Student Bounty Project.   Complete this project or create any other educational Plug-in for Foxit PhantomPDF and get some incentive for doing it.  Check out [Foxit Student Bounty Project Details](http://sync-us.foxitsoftware.com/se/Huy/ED/BountyProgram/FoxitBountyDetails.pdf) for more details.
