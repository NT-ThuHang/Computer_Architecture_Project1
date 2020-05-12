
// CalculatorDlg.h : header file
//

#pragma once
#include"QInt.h"
#include"Conversion.h"
#include"Qfloat.h"
#include"BasicOperation.h"

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CString DecQInt = L"";
	CString DecQFloat = L"";
	CString Bit =L"";
	CString Hex = L"";
	Conversion convert;
	int ID_Button = 0;
	bool ConvertFI = 0;
	QInt x, y;
	string Expression;
	int d = 0;
public:
	afx_msg void OnBnClickedBresult();
	afx_msg void OnBnClickedBplus();
	void TinhToanQInt();
	afx_msg void OnBnClickedBsub();
	afx_msg void OnBnClickedBmulti();
	afx_msg void OnBnClickedBdiv();
	afx_msg void OnBnClickedBac();
	afx_msg void OnBnClickedBand();
	afx_msg void OnBnClickedBor();
	afx_msg void OnBnClickedBxor();
	afx_msg void OnBnClickedBnot();
	afx_msg void OnBnClickedBleft();
	void DichTraiPhai();
	afx_msg void OnBnClickedBright();
	afx_msg void OnBnClickedBrol();
	void roLR();
	afx_msg void OnBnClickedBror();
	afx_msg void OnBnClickedBconvert();

	bool checkTH(CString, int);
};