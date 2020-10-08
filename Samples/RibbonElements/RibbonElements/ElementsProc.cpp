#include "StdAfx.h"
#include "ElementsProc.h"
#include "resource.h"
#include <iostream>

#include <codecvt>
#include <locale>
#include "GitPrompt.h"
#include "git2/clone.h"
#include "git2/transport.h"
#include "git2/sys/transport.h"
#include "git2/global.h"
#include "git2/errors.h"


CElementsProc::CElementsProc(void)
{
}


CElementsProc::~CElementsProc(void)
{
}


static int ssl_cert(git_cert *cert, int valid, const char *host, void *payload)
{
	//Huy: I don't understand how to use ssl certs yet.  This needs to be completed if we wish to handle authentication.
/*	GIT_UNUSED(cert);
	GIT_UNUSED(host);
	GIT_UNUSED(payload);

	if (_remote_sslnoverify != NULL)
		valid = 1;
		*/
	//return valid ? 0 : GIT_ECERTIFICATE;
	//printf("callback from ssl_cert\n");
	return true;
}

static int succeed_certificate_check(git_cert *cert, int valid, const char *host, void *payload)
{
	//Huy: I don't understand how to use ssl certs yet.  This needs to be completed if we wish to handle authentication.
/*	GIT_UNUSED(cert);
	GIT_UNUSED(valid);
	GIT_UNUSED(payload);

	cl_assert_equal_s("github.com", host);*/
	printf("callback from succeed_certificate_check\n");
	return 0;
}


void CElementsProc::OnButtonCloneProc(void* clientDate)
{
	GitPrompt myDlg;
	myDlg.DoModal(); //Shows the Clone DialogBox

	CString gitaddress = myDlg.gitresource;
	CString outputpath = myDlg.localpath;
	git_libgit2_init();
	static git_clone_options g_options;
	static git_repository *g_repo;
	git_checkout_options dummy_opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_fetch_options dummy_fetch = GIT_FETCH_OPTIONS_INIT;

	memset(&g_options, 0, sizeof(git_clone_options));
	g_options.version = GIT_CLONE_OPTIONS_VERSION;
	g_options.checkout_opts = dummy_opts;
	g_options.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	g_options.fetch_opts = dummy_fetch;
	g_options.fetch_opts.callbacks.certificate_check = ssl_cert;
	g_options.fetch_opts.callbacks.certificate_check = succeed_certificate_check;
	char urlcp[256];
	char pathscp[256];
	sprintf(urlcp, "%ws", gitaddress.GetString());
	sprintf(pathscp, "%ws", outputpath.GetString());


	std::wstring wspath(outputpath);
	const char* path =  (char*)wspath.c_str();
	int error = git_clone(&g_repo,urlcp, pathscp, &g_options);

	std::wstring search_directory =std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(pathscp);
	const unsigned short* pdfExten = L"*.pdf";
	const wchar_t* search_path_expression = search_directory.append(pdfExten).c_str(); //Expression using for finding .pdf files absolute path.
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path_expression, &fd); 
	//search_path_expression points to search_directory.  We have to reset what was changed in order to get just the directory again.
	search_directory.erase(search_directory.size() - sizeof(pdfExten)-1, search_directory.size());
	if(hFind != INVALID_HANDLE_VALUE) {
        do { 
            // read all (real) files in current folder
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
              WCHAR* abc = fd.cFileName;
			  FS_LPCWSTR inputfile = (FS_LPCWSTR)(search_directory.append(fd.cFileName).c_str()); //inputfile has the full pdf path
			  FR_Document frDocument= FRDocOpenFromFile (inputfile,(FS_LPCSTR)L"",true,true); //This opens the PDF file in PhantomPDF
			  //this reset the search directory again by removing the pdf file name
			  search_directory.erase(search_directory.size() - (int)wcslen(fd.cFileName), search_directory.size()); 
			  inputfile = L"";
            }
        }while(::FindNextFile(hFind, &fd)); //repeat search for all of the PDF file.
        ::FindClose(hFind); 

    } 
}

void CElementsProc::OnButtonPullProc(void* clientDate)
{
	FS_LPCWSTR pullmsg= L"Pull request has not been implimented.  Please go to ElementsProc.cpp->CElementsProc::OnButtonPullProc";
	FRSysShowMessageBox(pullmsg, MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}

void CElementsProc::OnButtonCommitProc(void* clientDate)
{
	FS_LPCWSTR commitmsg= L"Commit request has not been implimented.  Please go to ElementsProc.cpp->CElementsProc::OnButtonCommitProc";
	FRSysShowMessageBox(commitmsg, MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}

void CElementsProc::OnButtonPushProc(void* clientDate)
{
	FS_LPCWSTR pushmsg= L"Push request has not been implimented.  Please go to ElementsProc.cpp->CElementsProc::OnButtonPushProc";
	FRSysShowMessageBox(pushmsg, MB_OK | MB_ICONINFORMATION, NULL, NULL, FRAppGetMainFrameWnd());
}