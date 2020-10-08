// GitPrompt.cpp : implementation file
//

#include "stdafx.h"
#include "RibbonElements.h"
#include "GitPrompt.h"
#include "afxdialogex.h"
#include "git2/clone.h"
#include "git2/transport.h"
#include "git2/sys/transport.h"
#include "git2/global.h"
#include "git2/errors.h"
// GitPrompt dialog

IMPLEMENT_DYNAMIC(GitPrompt, CDialogEx)

GitPrompt::GitPrompt(CWnd* pParent /*=NULL*/)
	: CDialogEx(GitPrompt::IDD, pParent)
{

}

GitPrompt::~GitPrompt()
{
}

void GitPrompt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString (pDX, IDC_EDIT1, gitresource);
	DDX_CBString (pDX, IDC_EDIT2, localpath);
}


BEGIN_MESSAGE_MAP(GitPrompt, CDialogEx)
	ON_BN_CLICKED(IDOK, &GitPrompt::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GitPrompt::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &GitPrompt::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &GitPrompt::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &GitPrompt::OnBnClickedButton1)
END_MESSAGE_MAP()


// GitPrompt message handlers

static int ssl_cert(git_cert *cert, int valid, const char *host, void *payload)
{
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
/*	GIT_UNUSED(cert);
	GIT_UNUSED(valid);
	GIT_UNUSED(payload);

	cl_assert_equal_s("github.com", host);*/
	printf("callback from succeed_certificate_check\n");
	return 0;
}
void GitPrompt::OnBnClickedOk()
{
	CString cs1;
	GetDlgItemText(IDC_EDIT1, cs1);
	CDialogEx::OnOK();
}


void GitPrompt::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void GitPrompt::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void GitPrompt::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void GitPrompt::OnBnClickedButton1()
{
	//This code adds the folder selection dialog box
	LPWSTR szTitle = L"Choose PDF directory";
	LPWSTR szPath;  //resulting choosen path is provided here
	szPath=(wchar_t *) malloc(sizeof(WCHAR) * 100); 
	BOOL         retCode;
	LPMALLOC	   pMalloc;
	BROWSEINFO   nBI;
	LPITEMIDLIST pidl;
	memset(&nBI,0,sizeof(nBI));
	nBI.hwndOwner      = GetSafeHwnd(); //Set parent handle
	nBI.pszDisplayName = szPath;
	nBI.lpszTitle      = szTitle;
	nBI.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_BROWSEFORCOMPUTER;
	if (NULL != (pidl=SHBrowseForFolder(&nBI))){
		retCode = SHGetPathFromIDList(pidl,szPath);
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pidl);
		pMalloc->Release();
	}
	wcscat(szPath, L"\\");
	SetDlgItemText(IDC_EDIT2,szPath);
}
