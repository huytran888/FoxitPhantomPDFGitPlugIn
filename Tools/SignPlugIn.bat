IF NOT EXIST "C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\PISignatureGen.exe" COPY "%~dp0PISignatureGen.exe" "C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\PISignatureGen.exe"
REM SET PISignatureGenPath="%~dp0PISignatureGen.exe"
SET PISignatureGenPath="C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\PISignatureGen.exe"
SET PluginPath="C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\%1.fpi"
IF NOT "%2"=="" SET PluginPath="C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\%1 %2.fpi"
IF NOT "%3"=="" SET PluginPath="C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\%1 %2 %3.fpi"
SET frdpisdkeyPath="%~dp0frdpisdkey.txt"
%PISignatureGenPath% /sign %PluginPath% %frdpisdkeyPath%