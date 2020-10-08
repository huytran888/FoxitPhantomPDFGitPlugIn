#pragma once


// GitPrompt dialog

class GitPrompt : public CDialogEx
{
	DECLARE_DYNAMIC(GitPrompt)

public:
	GitPrompt(CWnd* pParent = NULL);   // standard constructor
	virtual ~GitPrompt();
	//afx_msg void OnBnClickedOk();
// Dialog Data
	enum { IDD = IDD_DIALOG1 };
	CString gitresource;
	CString localpath;
	CString selectedlocalpath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
};
