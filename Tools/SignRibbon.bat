SET PISignatureGenPath=C:\Products\Plug-inSDK\95\Plugin_SDK_9_5_0_0\Tools\PISignatureGen.exe
SET PluginPath="C:\Program Files (x86)\Foxit Software\Foxit PhantomPDF\plugins\Ribbon.fpi"
SET frdpisdkeyPath="C:\Products\Plug-inSDK\95\Plugin_SDK_9_5_0_0\Tools\frdpisdkey.txt"
%PISignatureGenPath% /sign %PluginPath% %frdpisdkeyPath%