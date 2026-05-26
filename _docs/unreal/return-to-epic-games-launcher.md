---
title: Return to Epic Games Launcher
---
This file covers the return from the github download engine to the epic games launcher engine

Version: 5.6.1
OS: Windows

### Overview
Goal  
Process Overview  
Log  

### Goal
No longer require using the github unreal engine download, which takes a long time to install and fix (more than 3 hours for me), takes up approximately 250 GB, and requires an Epic Games account.  
Switching (back) to the Epic Games Launcher version, which is approximately 10GB, last I checked. Compiling significantly less necessary (and not measured in hours).

### Process Overview

Sentry disabled for this.

Only one major bug found: an error with SolverBody.h  
  
put paratheses around a line in SolverBody.h (part of the engine); frequent error, does not actually make sense (operator precedence should make paratheses unnecessary).  
Info:  
File address: `\UE_Folder\Engine\Source\Runtime\Experimental\Chaos\Public\Chaos\Evolution\SolverBody.h`  
Line: 101  
Change: `std::numeric_limits<FSolverReal>::min` -> `(std::numeric_limits<FSolverReal>::min)` : after `return `, followed by `()`  
Note: Files were read-only b/c git, had to be set to writable (prompted on attempting change)  

Error was discovered after attempting to open project by building it in Visual Studio. Unreal simply gave "failed to compile" and said to use an IDE. 

### Log
This log was created and made over the problem solving process.
<hr>
Installed 5.6 and 5.7  

launched 5.6  
attempted to open project  
stated version change, prompt  
 
hit "open a copy"  
failed: no write access?  

Duplicated project manually. (file explorer)  
Success.  
   
Used "switch engine version" option  
selected "5.6" (not a file path)  
generating files bar  
left, unable to verify if any errors, but none clear.  

opened up .uproject  
prompted to rebuild list of things, including sentry  

chose yes  
loading bar  
failed, modules and stuff out of date  

attempted to open .sln  
failed, crash  

generating v.s. project files  
success   

opening VS  
launching from VS  
error: SolverBody.h line; scope resolution operator :: versus function call operator ()  

attempting to fix line 101 in file  
`C:\Program Files\Epic Games\UE_5.6\Engine\Source\Runtime\Experimental\Chaos\Public\Chaos\Evolution\SolverBody.h`  
warning:   
From; source control, git  
"You are trying to edit read only files. Do you want to mark these files as writable?"  
Options: ok or cancel  

Selected ok  
fix was putting paratheses around   
`std::numeric_limits<FSolverReal>::min`  
success.

Attempting build from VS
