/*********************************************************************

 Copyright (C) 2010 Foxit Corporation
 All rights reserved.

 NOTICE: Foxit permits you to use, modify, and distribute this file
 in accordance with the terms of the Foxit license agreement
 accompanying it. If you have received this file from a source other
 than Foxit, then your use, modification, or distribution of it
 requires the prior written permission of Foxit.

 ---------------------------------------------------------------------

RibbonElements.cpp

 - Defines the entry point for the DLL application, the entry point is PlugInMain.

*********************************************************************/

#include "stdafx.h"
#include "RibbonElements.h"
#include "ElementsProc.h"
/**added by Huy***/
#include <string>
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "GitPrompt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CRibbonElementsApp

BEGIN_MESSAGE_MAP(CRibbonElementsApp, CWinApp)
END_MESSAGE_MAP()


// CRibbonElementsApp construction

CRibbonElementsApp::CRibbonElementsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

// The one and only CRibbonElementsApp object

CRibbonElementsApp theApp;

/** 
	This sample gives an explanation about how to use the ribbon element.
*/

//Reads a PDF stored in the project resources directory and output as a bitmap to used for buttons icons.
FS_DIBitmap CRibbonElementsApp::GetBmpFromRes(UINT uID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HRSRC hRes = ::FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(uID), _T("PDF"));//RT_RCDATA);
	if (hRes == NULL) return NULL;
	DWORD dwLength = ::SizeofResource(AfxGetInstanceHandle(), hRes);
	HGLOBAL hGlobal = ::LoadResource(AfxGetInstanceHandle(), hRes);
	if (hGlobal == NULL) return NULL;
	LPVOID pData = ::LockResource(hGlobal);
	if (pData == NULL) return NULL;


	//create bmp
	FS_DIBitmap pBmp = FSDIBitmapNew();
	FSDIBitmapCreate(pBmp, 32, 32, FS_DIB_Argb, NULL, 0);
	FSDIBitmapClear(pBmp, 0xffffff);
	FPD_RenderDevice pDC = FPDFxgeDeviceNew();
	FPDFxgeDeviceAttach(pDC, pBmp, 0);
	FPD_Document pPDFDoc = FPDDocOpenMemDocument(pData, dwLength, NULL);
	FPD_Object pDict = FPDDocGetPage(pPDFDoc, 0);
	FPD_Page pPage = FPDPageNew();
	FPDPageLoad(pPage, pPDFDoc, pDict, TRUE);
	FPDPageParseContent(pPage, NULL);
	FS_AffineMatrix matrix = FPDPageGetDisplayMatrix(pPage, 0, 0, 32, 32, 0);
	FPD_RenderContext pContext = FPDRenderContextNew(pPage, TRUE);
	FPDRenderContextAppendPage(pContext, pPage, matrix);
	FPDRenderContextRender(pContext, pDC, NULL, NULL);
	FPDRenderContextDestroy(pContext);
	FPDPageDestroy(pPage);
	FPDDocClose(pPDFDoc);
	FPDFxgeDeviceDestroy(pDC);

	return pBmp;
}

//This is where the buttons for the ribbons are created and set to a action found in ElementsProc.
void CRibbonElementsApp::CreateElementsToNewCategory()
{
	FS_DIBitmap fs_bitmap = CRibbonElementsApp::GetBmpFromRes(IDR_PDF1);

	FR_RibbonBar fr_Bar = FRAppGetRibbonBar(NULL); //The RibbonBar will free by Foixt Reader or Phantom.

	//**Git Ribbon and buttons added here
	FR_RibbonCategory gitcategory = FRRibbonBarAddCategory(fr_Bar, "Git", (FS_LPCWSTR)L"Git");
	FR_RibbonPanel getpanel = FRRibbonCategoryAddPanel(gitcategory, "Git Panel", (FS_LPCWSTR)L"Git Panel", NULL);

	//Adding Clone button
	FR_RibbonButton gitbutton = (FR_RibbonButton)FRRibbonPanelAddElement(getpanel, FR_RIBBON_BUTTON,
		"Git Clone", (FS_LPCWSTR)L"Clone", FRRibbonPanelGetElementCount(getpanel));
	//FS_DIBitmap bitmapClone = CRibbonElementsApp::GetBmpFromRes(IDR_PDF1);
	FR_RibbonElement gitelment = FRRibbonPanelGetElementByName(getpanel, "Git Clone");
	if(gitelment!=NULL){
		FRRibbonElementSetImage(gitelment, fs_bitmap, fs_bitmap);
		FRRibbonElementSetTooltip(gitelment, (FS_LPCWSTR)L"Git Clone");
		//This set the callback that handles the action
		FRRibbonElementSetExecuteProc(gitelment, CElementsProc::OnButtonCloneProc); //sets action
	}

	//Added Pull button
	FR_RibbonButton Pullbutton = (FR_RibbonButton)FRRibbonPanelAddElement(getpanel, FR_RIBBON_BUTTON,
	"Git Pull", (FS_LPCWSTR)L"Pull", FRRibbonPanelGetElementCount(getpanel));
	FR_RibbonElement Pullelment = FRRibbonPanelGetElementByName(getpanel, "Git Pull");
	if(Pullelment!=NULL){
		FRRibbonElementSetImage(Pullelment, fs_bitmap, fs_bitmap);
		FRRibbonElementSetTooltip(Pullelment, (FS_LPCWSTR)L"Git Pull");
		FRRibbonElementSetExecuteProc(Pullelment, CElementsProc::OnButtonPullProc); //sets action
	}

	//Added Commit button
	FR_RibbonButton commitbutton = (FR_RibbonButton)FRRibbonPanelAddElement(getpanel, FR_RIBBON_BUTTON,
	"Git Commit", (FS_LPCWSTR)L"Commit", FRRibbonPanelGetElementCount(getpanel));
	FR_RibbonElement commitelment = FRRibbonPanelGetElementByName(getpanel, "Git Commit");
	if(commitelment!=NULL){
		FRRibbonElementSetImage(commitelment, fs_bitmap, fs_bitmap);
		FRRibbonElementSetTooltip(commitelment, (FS_LPCWSTR)L"Git Commit");
		FRRibbonElementSetExecuteProc(commitelment, CElementsProc::OnButtonCommitProc); //sets action
	}

	//add Push button
	FR_RibbonButton pushbutton = (FR_RibbonButton)FRRibbonPanelAddElement(getpanel, FR_RIBBON_BUTTON,
	"Git Push", (FS_LPCWSTR)L"Push", FRRibbonPanelGetElementCount(getpanel));
	FR_RibbonElement pushelment = FRRibbonPanelGetElementByName(getpanel, "Git Push");
	if(pushelment!=NULL){
		FRRibbonElementSetImage(pushelment, fs_bitmap, fs_bitmap);
		FRRibbonElementSetTooltip(pushelment, (FS_LPCWSTR)L"Git Push");
		FRRibbonElementSetExecuteProc(pushelment, CElementsProc::OnButtonPushProc); //sets action
	}

	FSDIBitmapDestroy(fs_bitmap); //Note: Datatypes are not automatically manage.
}

//////////////////////////////////////////////////////////////////////////
/* PIExportHFTs
** ------------------------------------------------------
**/
/** 
** Create and Add the extension HFT's
**
** @return true to continue loading plug-in,
** false to cause plug-in loading to stop.
*/
FS_BOOL PIExportHFTs(void)
{
	return TRUE;
}

/** 
The application calls this function to allow it to
<ul>
<li> Import HFTs supplied by other plug-ins.
<li> Replace functions in the HFTs you're using (where allowed).
<li> Register to receive notification events.
</ul>
*/
FS_BOOL PIImportReplaceAndRegister(void)
{
	return TRUE;
}

/* Plug-ins can use their Initialization procedures to hook into Foxit Reader's 
	 * user interface by adding menu items, toolbar buttons, windows, and so on.
	 * It is also acceptable to modify Foxit Reader's user interface later when the plug-in is running.
	 */	
void PILoadMenuBarUI(void* pParentWnd)
{
	//This interface has been depreicated. Please use PILoadRibbonUI
}

void PIReleaseMenuBarUI(void* pParentWnd)
{
	//This interface has been depreicated. Please use PILoadRibbonUI
}

void PILoadToolBarUI(void* pParentWnd)
{
	//This interface has been depreicated. Please use PILoadRibbonUI
}

void PIReleaseToolBarUI(void* pParentWnd)
{
	//This interface has been depreicated. Please use PILoadRibbonUI
}

void PILoadRibbonUI(void* pParentWnd)
{
	theApp.CreateElementsToNewCategory();
	
}


void PILoadStatusBarUI(void* pParentWnd)
{
	//This callback is a good place if you want to test your code without having to press any button.
	//This will trigger when the status of the UI has changed.
	//FRSysShowMessageBox((FS_LPCWSTR)L"Hello World", MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}
/* PIInit
** ------------------------------------------------------
**/
/** 
	The main initialization routine.
	
	@return true to continue loading the plug-in, 
	false to cause plug-in loading to stop.
*/
FS_BOOL PIInit(void)
{
	return TRUE;
}

/* PIUnload
** ------------------------------------------------------
**/
/** 
	The unload routine.
	Called when your plug-in is being unloaded when the application quits.
	Use this routine to release any system resources you may have
	allocated.

	Returning false will cause an alert to display that unloading failed.
	@return true to indicate the plug-in unloaded.
*/
FS_BOOL PIUnload(void)
{	
	return TRUE;
}

/** PIHandshake
	function provides the initial interface between your plug-in and the application.
	This function provides the callback functions to the application that allow it to 
	register the plug-in with the application environment.

	Required Plug-in handshaking routine:
	
	@param handshakeVersion the version this plug-in works with. 
	@param handshakeData OUT the data structure used to provide the primary entry points for the plug-in. These
	entry points are used in registering the plug-in with the application and allowing the plug-in to register for 
	other plug-in services and offer its own.
	@return true to indicate success, false otherwise (the plug-in will not load).
*/

FS_BOOL PIHandshake(FS_INT32 handshakeVersion, void *handshakeData)
{
	if(handshakeVersion != HANDSHAKE_V0100)
		return FALSE;
	
	/* Cast handshakeData to the appropriate type */
	PIHandshakeData_V0100* pData = (PIHandshakeData_V0100*)handshakeData;
	
	/* Set the name we want to go by */
	pData->PIHDRegisterPlugin(pData, "RibbonElements", (FS_LPCWSTR)L"RibbonElements");

	/* If you export your own HFT, do so in here */
	pData->PIHDSetExportHFTsCallback(pData, &PIExportHFTs);
		
	/*
	** If you import plug-in HFTs, replace functionality, and/or want to register for notifications before
	** the user has a chance to do anything, do so in here.
	*/
	pData->PIHDSetImportReplaceAndRegisterCallback(pData, &PIImportReplaceAndRegister);

	/* Perform your plug-in's initialization in here */
	pData->PIHDSetInitDataCallback(pData, &PIInit);
	PIInitUIProcs initUIProcs;
	INIT_CALLBACK_STRUCT(&initUIProcs, sizeof(PIInitUIProcs));
	initUIProcs.lStructSize = sizeof(PIInitUIProcs);
	initUIProcs.PILoadMenuBarUI = PILoadMenuBarUI;
	initUIProcs.PIReleaseMenuBarUI = PIReleaseMenuBarUI;
	initUIProcs.PILoadToolBarUI = PILoadToolBarUI;
	initUIProcs.PIReleaseToolBarUI = PIReleaseToolBarUI;
	initUIProcs.PILoadRibbonUI = PILoadRibbonUI;
	initUIProcs.PILoadStatusBarUI = PILoadStatusBarUI;
	pData->PIHDSetInitUICallbacks(pData, &initUIProcs);	
	/* Perform any memory freeing or state saving on "quit" in here */
	pData->PIHDSetUnloadCallback(pData, &PIUnload);
	return TRUE;
}
