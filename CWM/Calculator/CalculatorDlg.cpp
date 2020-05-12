
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, DecQInt(_T(""))
	, DecQFloat(_T(""))
	, Bit(_T(""))
	, Hex(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDecQint, DecQInt);
	DDX_Text(pDX, IDC_EDecQfloat, DecQFloat);
	DDX_Text(pDX, IDC_EBit, Bit);
	DDX_Text(pDX, IDC_EHex, Hex);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BRESULT, &CCalculatorDlg::OnBnClickedBresult)
	ON_BN_CLICKED(IDC_BPLUS, &CCalculatorDlg::OnBnClickedBplus)
	ON_BN_CLICKED(IDC_BSUB, &CCalculatorDlg::OnBnClickedBsub)
	ON_BN_CLICKED(IDC_BMULTI, &CCalculatorDlg::OnBnClickedBmulti)
	ON_BN_CLICKED(IDC_BDIV, &CCalculatorDlg::OnBnClickedBdiv)
	ON_BN_CLICKED(IDC_BAC, &CCalculatorDlg::OnBnClickedBac)
	ON_BN_CLICKED(IDC_BAND, &CCalculatorDlg::OnBnClickedBand)
	ON_BN_CLICKED(IDC_BOR, &CCalculatorDlg::OnBnClickedBor)
	ON_BN_CLICKED(IDC_BXOR, &CCalculatorDlg::OnBnClickedBxor)
	ON_BN_CLICKED(IDC_BNOT, &CCalculatorDlg::OnBnClickedBnot)
	ON_BN_CLICKED(IDC_BLEFT, &CCalculatorDlg::OnBnClickedBleft)
	ON_BN_CLICKED(IDC_BRIGHT, &CCalculatorDlg::OnBnClickedBright)
	ON_BN_CLICKED(IDC_BROL, &CCalculatorDlg::OnBnClickedBrol)
	ON_BN_CLICKED(IDC_BROR, &CCalculatorDlg::OnBnClickedBror)
	ON_BN_CLICKED(IDC_BCONVERT, &CCalculatorDlg::OnBnClickedBconvert)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedBresult()
{
	SetDlgItemText(IDC_ValResult, L"");
	switch (ID_Button)
	{
		case 0:
		{
			QInt obj;
			obj.resetQInt();
			CString temp;
			GetDlgItemText(IDC_EDecQint, temp);
			if (checkTH(temp,1))
			{
				//nhap Qint thi chuyen sang kieu bit va hex. qfloat bo trong
				string val(CW2A(temp.GetString()));
				if (obj.overflow(val))
				{
					SetDlgItemText(IDC_ValResult, L"OVERFLOW!");
					return;
				}
				this->DecQInt = temp;				//---Qint
				obj.ScanQInt(val);
				string s;
				//Chuyen nhi phan
				s = this->convert.DecToBin(obj);
				CString csbit(s.c_str());
				this->Bit = csbit;					//---Bin
				SetDlgItemText(IDC_EBit, csbit);
				//chuyen he 16
				s = this->convert.DecToHex(obj);
				CString cshex(s.c_str());
				this->Hex = cshex;					//---hex
				SetDlgItemText(IDC_EHex, cshex);
			}
			else
			{
				GetDlgItemText(IDC_EDecQfloat, temp);
				if (checkTH(temp, 2))
				{
					Qfloat objf;
					string val(CW2A(temp.GetString()));
					this->DecQFloat = temp;			//---Qfloat
					objf.ScanQfloat(val);
					string s;
					//Chuyen nhi phan
					s = objf.DectoBin();
					CString csbit(s.c_str());
					this->Bit = csbit;				//---Bin
					SetDlgItemText(IDC_EBit, csbit);
				}
				else
				{
					GetDlgItemText(IDC_EBit, temp);
					if (checkTH(temp, 3))
					{
						//chuyen bit sang QInt
						string val(CW2A(temp.GetString()));
						string s;
						if (ConvertFI)
						{
							if (val.length() != 128)
							{
								SetDlgItemText(IDC_ValResult, L"OVERFLOW! You must fill in enough 128 bits. Try again !");
								return;
							}
							this->Bit = temp;				//---bin
							//xuat he DecQfloat
							Qfloat objf;
							objf = objf.Qfloat::BinToDec(val);
							s = objf.PrintQfloat();
							CString csQfloat(s.c_str());
							this->DecQFloat = csQfloat;		//--Qfloat
							SetDlgItemText(IDC_EDecQfloat, csQfloat);
						}
						else
						{
							//xuat he DecQint
							if (val.length() > 128)
							{
								SetDlgItemText(IDC_ValResult, L"OVERFLOW! Number of bits must not exceed 128. Try again !");
								return;
							}
							this->Bit = temp;				//---bin
							obj = this->convert.BinToDec(val);
							s = obj.PrintQInt();
							CString csQint(s.c_str());
							this->DecQInt = csQint;			//--Qint
							SetDlgItemText(IDC_EDecQint, csQint);

							//xuat he 16
							s = this->convert.DecToHex(obj);
							CString cshex(s.c_str());
							this->Hex = cshex;				//---hex
							this->Hex = cshex;
							SetDlgItemText(IDC_EHex, this->Hex);
						}
					}
					else
					{
						GetDlgItemText(IDC_EHex, temp);
						if (checkTH(temp, 4))
						{
							//chuyen hex sang Qint
							string val(CW2A(temp.GetString()));
							if (val.length() > 32)
							{
								SetDlgItemText(IDC_ValResult, L"OVERFLOW!");
								return;
							}
							obj = this->convert.HexToDec(val);
							//xuat he DecQint
							string s = obj.PrintQInt();
							CString csQint(s.c_str());
							this->DecQInt = csQint;				//---Qint
							SetDlgItemText(IDC_EDecQint, this->DecQInt);

							//xuat bit
							s = this->convert.DecToBin(obj);
							CString csbit(s.c_str());
							this->Bit = csbit;					//---bin
							SetDlgItemText(IDC_EBit, this->Bit);

						}
						else
						{
							SetDlgItemText(IDC_ValResult,L"Data is null, please fill in !");
						}
					}
				}
			}
			/*SetDlgItemText(IDC_ValResult, L"");*/
		}break;
		case 1:
		case 2:
		case 3:
		case 4:
		{
			//mở hết textbox 
			/*GetDlgItem(IDC_EDecQint)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDecQfloat)->EnableWindow(TRUE);
			GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
			GetDlgItem(IDC_EHex)->EnableWindow(TRUE);*/
			CString temp;
			GetDlgItemText(IDC_EDecQint, temp);
			if (temp != "")
			{
				string val1(CW2A(temp.GetString()));
				y.ScanQInt(val1);
				switch (ID_Button)
				{
				case 1:
					x = x + y;
					break;
				case 2:
					x = x - y;
					break;
				case 3:
					x = x * y;
					break;
				case 4:
				{
					if (val1 == "0")
					{
						SetDlgItemText(IDC_ValResult, L"ERORR ! Dividend can't be 0. Try again !");
						SetDlgItemText(IDC_EDecQint, L"");
						this->ID_Button = 0;
						return;
					}
					else
						x = x / y;
				}
				break;
				default:
					break;
				}
				string s = x.PrintQInt();
				Expression = Expression + val1 + " = " + s;
				CString csQint(s.c_str());
				SetDlgItemText(IDC_EDecQint, csQint);
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
			}
			else
			{
				GetDlgItemText(IDC_EDecQfloat, temp);
				if (temp != "")
				{
					//lam sau
				}
				else
				{
					GetDlgItemText(IDC_EBit, temp);
					if (temp != "")
					{
						string val1(CW2A(temp.GetString()));
						y = convert.BinToDec(val1);
						switch (ID_Button)
						{
						case 1:
							x = x + y;
							break;
						case 2:
							x = x - y;
							break;
						case 3:
							x = x * y;
							break;
						case 4:
						{
							if (val1 == "0")
							{
								SetDlgItemText(IDC_ValResult, L"ERORR ! Dividend can't be 0. Try again !");
								SetDlgItemText(IDC_EBit, L"");
								this->ID_Button = 0;
								return;
							}
							else
								x = x / y;
						}break;
						default:
							break;
						}
						string s = convert.DecToBin(x);
						Expression = Expression + val1 + " = " + s;
						CString csBit(s.c_str());
						SetDlgItemText(IDC_EBit, csBit);
						CString css(Expression.c_str());
						SetDlgItemText(IDC_ValResult, css);
					}
					else
					{
						GetDlgItemText(IDC_EHex, temp);
						if (temp != "")
						{
							string val1(CW2A(temp.GetString()));
							y = convert.HexToDec(val1);
							switch (ID_Button)
							{
							case 1:
								x = x + y;
								break;
							case 2:
								x = x - y;
								break;
							case 3:
								x = x * y;
								break;
							case 4:
							{
								if (val1 == "0")
								{
									SetDlgItemText(IDC_ValResult, L"ERORR ! Dividend can't be 0. Try again !");
									SetDlgItemText(IDC_EHex, L"");
									this->ID_Button = 0;
									return;
								}
								else
									x = x / y;
							}break;
							default:
								break;
							}
							string s = convert.DecToHex(x);
							Expression = Expression + val1 + " = " + s;
							CString csHex(s.c_str());
							SetDlgItemText(IDC_EHex, csHex);
							CString css(Expression.c_str());
							SetDlgItemText(IDC_ValResult, css);
						}
						else
						{
							SetDlgItemText(IDC_ValResult,L"Can't calculate! Data is null, please fill in!");
						}
					}
				}
			}
			GetDlgItem(IDC_EDecQint)->EnableWindow(TRUE);
			GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
			GetDlgItem(IDC_EHex)->EnableWindow(TRUE);
			GetDlgItem(IDC_DecQint)->EnableWindow(TRUE);
			GetDlgItem(IDC_BIT)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEX)->EnableWindow(TRUE);
			this->ID_Button = 0;
		}break;
		case 5:
		case 6:
		case 7:
		{
			//mở hết textbox 
			GetDlgItem(IDC_EDecQint)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDecQfloat)->EnableWindow(TRUE);
			GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
			GetDlgItem(IDC_EHex)->EnableWindow(TRUE);
			GetDlgItem(IDC_DecQint)->EnableWindow(TRUE);
			GetDlgItem(IDC_DecQfloat)->EnableWindow(TRUE);
			GetDlgItem(IDC_BIT)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEX)->EnableWindow(TRUE);
			CString temp;
			GetDlgItemText(IDC_EDecQint, temp);
			if (temp != "")
			{
				string val1(CW2A(temp.GetString()));
				y.ScanQInt(val1);
				switch (ID_Button)
				{
				case 5:
					x = x & y;
					break;
				case 6:
					x = x | y;
					break;
				case 7:
					x = x ^ y;
					break;
				default:
					break;
				}
				string s = x.PrintQInt();
				CString csQint(s.c_str());
				SetDlgItemText(IDC_EDecQint, csQint);
				Expression = Expression + val1 + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
			}
			else
			{
				GetDlgItemText(IDC_EDecQfloat, temp);
				if (temp != "")
				{
					//lam sau
				}
				else
				{
					GetDlgItemText(IDC_EBit, temp);
					if (temp != "")
					{
						string val1(CW2A(temp.GetString()));
						y = convert.BinToDec(val1);
						switch (ID_Button)
						{
						case 5:
							x = x & y;
							break;
						case 6:
							x = x | y;
							break;
						case 7:
							x = x ^ y;
							break;
						default:
							break;
						}
						string s = convert.DecToBin(x);
						CString csBit(s.c_str());
						SetDlgItemText(IDC_EBit, csBit);
						Expression = Expression + val1 + " = " + s;
						CString css(Expression.c_str());
						SetDlgItemText(IDC_ValResult, css);
					}
					else
					{
						GetDlgItemText(IDC_EHex, temp);
						if (temp != "")
						{
							string val1(CW2A(temp.GetString()));
							y = convert.HexToDec(val1);
							switch (ID_Button)
							{
							case 5:
								x = x & y;
								break;
							case 6:
								x = x | y;
								break;
							case 7:
								x = x ^ y;
								break;
							default:
								break;
							}
							string s = convert.DecToHex(x);
							CString csHex(s.c_str());
							SetDlgItemText(IDC_EHex, csHex);
							Expression = Expression + val1 + " = " + s;
							CString css(Expression.c_str());
							SetDlgItemText(IDC_ValResult, css);
						}
						else
						{
							SetDlgItemText(IDC_ValResult, L"Can't calculate! Data is null, please fill in!");
						}
					}
				}
			}
			this->ID_Button = 0;
		}break;
		case 9:
		case 10:
		{
			CString temp;
			GetDlgItemText(IDC_EDecQint, temp);
			SetDlgItemText(IDC_EDecQint, L"");
			string sint(CW2A(temp.GetString()));
			if (sint == "") sint = "0";
			int k = _wtoi(temp);
			if (ID_Button == 9)
				x = x << k;
			else
				x = x >> k;

			switch (this->d)
			{
			case 1:
			{
				string s = x.PrintQInt();
				CString cs(s.c_str());

				Expression = Expression + sint + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
				SetDlgItemText(IDC_EDecQint, cs);
			}break;
			case 2:
			{
				string s = convert.DecToBin(x);
				CString cs(s.c_str());

				Expression = Expression + sint + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
				SetDlgItemText(IDC_EBit, cs);

			}break;
			case 3:
			{
				string s = convert.DecToHex(x);
				CString cs(s.c_str());

				Expression = Expression + sint + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
				SetDlgItemText(IDC_EHex, cs);

			}break;
			default:
				break;
			}
			GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
			GetDlgItem(IDC_EHex)->EnableWindow(TRUE);
			GetDlgItem(IDC_BIT)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEX)->EnableWindow(TRUE);
			ID_Button = 0;
		}break;
		case 11:
		case 12:
		{
			CString temp;
			GetDlgItemText(IDC_EDecQint, temp);
			SetDlgItemText(IDC_EDecQint, L"");
			string sint(CW2A(temp.GetString()));
			if (sint == "") sint = "0";
			int k = _wtoi(temp);
			if (ID_Button == 11)
				x = x.rol(k);
			else
				x = x.ror(k);
			switch (this->d)
			{
			case 1:
			{
				string s = x.PrintQInt();
				CString cs(s.c_str());

				Expression = Expression + sint + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
				SetDlgItemText(IDC_EDecQint, cs);
			}break;
			case 2:
			{
				string s = convert.DecToBin(x);
				CString cs(s.c_str());

				Expression = Expression + sint + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
				SetDlgItemText(IDC_EBit, cs);

			}break;
			case 3:
			{
				string s = convert.DecToHex(x);
				CString cs(s.c_str());

				Expression = Expression + sint + " = " + s;
				CString css(Expression.c_str());
				SetDlgItemText(IDC_ValResult, css);
				SetDlgItemText(IDC_EHex, cs);

			}break;
			default:
				break;
			}
			GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
			GetDlgItem(IDC_EHex)->EnableWindow(TRUE);
			GetDlgItem(IDC_BIT)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEX)->EnableWindow(TRUE);
			ID_Button = 0;
		}break;
	default:
		break;
	}
	x.resetQInt();
	y.resetQInt();	//cho QInt bằng 0
}


void CCalculatorDlg::OnBnClickedBplus()
{
	ID_Button = 1;
	TinhToanQInt();
	Expression = Expression + " + ";
}

void CCalculatorDlg::OnBnClickedBsub()
{
	ID_Button = 2;
	TinhToanQInt();
	Expression = Expression + " - ";
}

void CCalculatorDlg::OnBnClickedBmulti()
{
	ID_Button = 3;
	TinhToanQInt();
	Expression = Expression + " x ";
}

void CCalculatorDlg::OnBnClickedBdiv()
{
	ID_Button = 4;
	TinhToanQInt();
	Expression = Expression + " / ";
}

void CCalculatorDlg::TinhToanQInt()
{
	Expression = "";
	x.resetQInt();
	//Xử lí xem người dùng nhập ở đâu trong 4 text box
	//người dùng sẽ nhập vào ô x, sau đó nhấn "+", thì phải xóa đi nd trong text box
	//sau đó người dùng sẽ nhập tiếp sô thứ hai, sau đó nhấn result để cho ra kết quả.
	CString temp;
	GetDlgItemText(IDC_EDecQint, temp);	//kiểm tra thử người dùng có nhập ở DecQInt không?
	if (temp != "")	//đúng nè
	{
		//Thực hiện xử lí cho dữ liệu vào QInt
		string val(CW2A(temp.GetString()));
		Expression = Expression + val;
		x.ScanQInt(val);
		SetDlgItemText(IDC_EDecQint, L"");

		//sau đó cho người dùng nhập tiếp vào vị trí đó khi nhập xong thì họ nhấn result

		if (ID_Button == 8)
		{
			x = ~x;
			string s = x.PrintQInt();
			CString csQInt(s.c_str());
			SetDlgItemText(IDC_EDecQint, csQInt);
			Expression = "(NOT) " + Expression + " = " + s;
			CString css(Expression.c_str());
			SetDlgItemText(IDC_ValResult, css);
			ID_Button = 0;
		}
		else
		{
			//khoa lai textbox khong xài
			GetDlgItem(IDC_EDecQfloat)->EnableWindow(FALSE);
			GetDlgItem(IDC_EBit)->EnableWindow(FALSE);
			GetDlgItem(IDC_EHex)->EnableWindow(FALSE);
			GetDlgItem(IDC_DecQfloat)->EnableWindow(FALSE);
			GetDlgItem(IDC_BIT)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEX)->EnableWindow(FALSE);

			SetDlgItemText(IDC_EDecQfloat, L"");
			SetDlgItemText(IDC_EBit, L"");
			SetDlgItemText(IDC_EHex, L"");
		}
	}
	else
	{
		//Qfloat
		GetDlgItemText(IDC_EDecQfloat, temp);
		if (temp != "")
		{
			SetDlgItemText(IDC_ValResult,L"Khong ho tro cho Dec(QFloat)");
			SetDlgItemText(IDC_EDecQfloat, L"");
		}
		else
		{
			//bit
			GetDlgItemText(IDC_EBit, temp);
			if (temp != "")
			{
				string val(CW2A(temp.GetString()));
				Expression = Expression + val;
				x = convert.BinToDec(val);
				SetDlgItemText(IDC_EBit, L"");

				if (ID_Button == 8)
				{
					x = ~x;
					string s = convert.DecToBin(x);
					CString csBit(s.c_str());
					SetDlgItemText(IDC_EBit, csBit);
					Expression = "(NOT) " + Expression + " = " + s;
					CString css(Expression.c_str());
					SetDlgItemText(IDC_ValResult, css);
					ID_Button = 0;
				}
				else
				{
					//khoa lai textbox khong xài
					GetDlgItem(IDC_EDecQfloat)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDecQint)->EnableWindow(FALSE);
					GetDlgItem(IDC_EHex)->EnableWindow(FALSE);
					GetDlgItem(IDC_DecQfloat)->EnableWindow(FALSE);
					GetDlgItem(IDC_DecQint)->EnableWindow(FALSE);
					GetDlgItem(IDC_HEX)->EnableWindow(FALSE);

					SetDlgItemText(IDC_EDecQfloat, L"");
					SetDlgItemText(IDC_EDecQint, L"");
					SetDlgItemText(IDC_EHex, L"");
				}
			}
			else
			{
				//hex
				GetDlgItemText(IDC_EHex, temp);
				if (temp != "")
				{
					string val(CW2A(temp.GetString()));
					Expression = Expression + val;
					x = convert.HexToDec(val);
					SetDlgItemText(IDC_EHex, L"");

					if (ID_Button == 8)
					{
						x = ~x;
						string s = convert.DecToHex(x);
						CString csHex(s.c_str());
						SetDlgItemText(IDC_EHex, csHex);
						Expression = "(NOT) " + Expression + " = " + s;
						CString css(Expression.c_str());
						SetDlgItemText(IDC_ValResult, css);
						ID_Button = 0;
					}
					else
					{
						//khoa lai textbox khong xài
						GetDlgItem(IDC_EDecQfloat)->EnableWindow(FALSE);
						GetDlgItem(IDC_EBit)->EnableWindow(FALSE);
						GetDlgItem(IDC_EDecQint)->EnableWindow(FALSE);
						GetDlgItem(IDC_DecQfloat)->EnableWindow(FALSE);
						GetDlgItem(IDC_BIT)->EnableWindow(FALSE);
						GetDlgItem(IDC_DecQint)->EnableWindow(FALSE);

						SetDlgItemText(IDC_EDecQfloat, L"");
						SetDlgItemText(IDC_EDecQint, L"");
						SetDlgItemText(IDC_EBit, L"");
					}
				}
				else
				{
					SetDlgItemText(IDC_ValResult, L"Can't calculate! Data is null, please fill in!");
				}
			}
		}
	}
}


void CCalculatorDlg::OnBnClickedBac()
{
	this->Expression = "";
	this->x.resetQInt();
	this->y.resetQInt();
	this->ID_Button = 0;
	this->d = 0;
	this->DecQFloat = L"";
	this->DecQInt = L"";
	this->Bit = L"";
	this->Hex = L"";
	SetDlgItemText(IDC_EDecQint, L"");
	SetDlgItemText(IDC_EDecQfloat, L"");
	SetDlgItemText(IDC_EBit, L"");
	SetDlgItemText(IDC_EHex, L"");


	GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
	GetDlgItem(IDC_BIT)->EnableWindow(TRUE);


	SetDlgItemText(IDC_ValResult, L"");

	if (this->ConvertFI)
	{
		SetDlgItemTextW(IDC_BCONVERT, L"QFloat");
		GetDlgItem(IDC_EDecQint)->EnableWindow(FALSE);
		GetDlgItem(IDC_DecQint)->EnableWindow(FALSE);
		GetDlgItem(IDC_EHex)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDecQfloat)->EnableWindow(TRUE);
		GetDlgItem(IDC_DecQfloat)->EnableWindow(TRUE);

		//tat button
		GetDlgItem(IDC_BPLUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BSUB)->EnableWindow(FALSE);
		GetDlgItem(IDC_BMULTI)->EnableWindow(FALSE);
		GetDlgItem(IDC_BDIV)->EnableWindow(FALSE);
		GetDlgItem(IDC_BLEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BRIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BROR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BROL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BAND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BXOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BNOT)->EnableWindow(FALSE);
	}
	else
	{
		SetDlgItemTextW(IDC_BCONVERT, L"QInt");
		GetDlgItem(IDC_EDecQfloat)->EnableWindow(FALSE);
		GetDlgItem(IDC_DecQfloat)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDecQint)->EnableWindow(TRUE);
		GetDlgItem(IDC_DecQint)->EnableWindow(TRUE);
		GetDlgItem(IDC_EHex)->EnableWindow(TRUE);
		GetDlgItem(IDC_HEX)->EnableWindow(TRUE);

		GetDlgItem(IDC_BPLUS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BSUB)->EnableWindow(TRUE);
		GetDlgItem(IDC_BMULTI)->EnableWindow(TRUE);
		GetDlgItem(IDC_BDIV)->EnableWindow(TRUE);
		GetDlgItem(IDC_BLEFT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BRIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BROR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BROL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BAND)->EnableWindow(TRUE);
		GetDlgItem(IDC_BOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BXOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_BNOT)->EnableWindow(TRUE);
	}
}

void CCalculatorDlg::OnBnClickedBand()
{
	ID_Button = 5;
	TinhToanQInt();
	Expression = Expression + " (AND) ";
}


void CCalculatorDlg::OnBnClickedBor()
{
	ID_Button = 6;
	TinhToanQInt();
	Expression = Expression + " (OR) ";
}


void CCalculatorDlg::OnBnClickedBxor()
{
	ID_Button = 7;
	TinhToanQInt();
	Expression = Expression + " (XOR) ";
}


void CCalculatorDlg::OnBnClickedBnot()
{
	ID_Button = 8;
	TinhToanQInt();
}



void CCalculatorDlg::OnBnClickedBleft()
{
	ID_Button = 9;
	DichTraiPhai();
	Expression = Expression + " << ";
}

void CCalculatorDlg::OnBnClickedBright()
{
	ID_Button = 10;
	DichTraiPhai();
	Expression = Expression + " >> ";
}

void CCalculatorDlg::DichTraiPhai()
{
	Expression = "";
	CString temp;
	GetDlgItemText(IDC_EDecQint, temp);
	GetDlgItem(IDC_EDecQfloat)->EnableWindow(FALSE);
	GetDlgItem(IDC_EBit)->EnableWindow(FALSE);
	GetDlgItem(IDC_EHex)->EnableWindow(FALSE);
	GetDlgItem(IDC_DecQfloat)->EnableWindow(FALSE);
	GetDlgItem(IDC_BIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX)->EnableWindow(FALSE);
	if (temp != "")
	{
		this->d = 1;
		string val(CW2A(temp.GetString()));
		Expression = Expression + val;
		x.ScanQInt(val);
	}
	else
	{
		GetDlgItemText(IDC_EDecQfloat, temp);
		if (temp != "")
		{
			SetDlgItemText(IDC_ValResult, L"Khong ho tro cho DecQFloat!");
			SetDlgItemText(IDC_EDecQfloat, L"");

			GetDlgItem(IDC_EDecQfloat)->EnableWindow(TRUE);
			GetDlgItem(IDC_EBit)->EnableWindow(TRUE);
			GetDlgItem(IDC_EHex)->EnableWindow(TRUE);
			GetDlgItem(IDC_DecQfloat)->EnableWindow(TRUE);
			GetDlgItem(IDC_BIT)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEX)->EnableWindow(TRUE);

			ID_Button = 0;
		}
		else
		{
			GetDlgItemText(IDC_EBit, temp);
			if (temp != "")
			{
				this->d = 2;
				SetDlgItemText(IDC_EBit, L"");
				string val(CW2A(temp.GetString()));
				Expression = Expression + val;
				x = convert.BinToDec(val);
			}
			else
			{
				GetDlgItemText(IDC_EHex, temp);
				if (temp != "")
				{
					this->d = 3;
					SetDlgItemText(IDC_EHex, L"");
					string val(CW2A(temp.GetString()));
					Expression = Expression + val;
					x = convert.HexToDec(val);
				}
				else
				{
					SetDlgItemText(IDC_ValResult, L"Can't calculate! Data is null, please fill in!");
				}
			}
		}
	}
	SetDlgItemText(IDC_EDecQint, L"");
	SetDlgItemText(IDC_EDecQfloat, L"");
	SetDlgItemText(IDC_EBit, L"");
	SetDlgItemText(IDC_EHex, L"");
}

void CCalculatorDlg::OnBnClickedBrol()
{
	ID_Button = 11;
	roLR();
	Expression = Expression + " (ROL) ";
}

void CCalculatorDlg::OnBnClickedBror()
{
	ID_Button = 12;
	roLR();
	Expression = Expression + " (ROR) ";
}

void CCalculatorDlg::roLR()
{
	Expression = "";
	CString temp;
	GetDlgItemText(IDC_EDecQint, temp);
	GetDlgItem(IDC_EDecQfloat)->EnableWindow(FALSE);
	GetDlgItem(IDC_EBit)->EnableWindow(FALSE);
	GetDlgItem(IDC_EHex)->EnableWindow(FALSE);
	GetDlgItem(IDC_DecQfloat)->EnableWindow(FALSE);
	GetDlgItem(IDC_BIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX)->EnableWindow(FALSE);
	if (temp != "")
	{
		this->d = 1;
		string val(CW2A(temp.GetString()));
		Expression = Expression + val;
		x.ScanQInt(val);
	}
	else
	{
		GetDlgItemText(IDC_EDecQfloat, temp);
		if (temp != "")
		{
			SetDlgItemText(IDC_ValResult, L"Xin loi, roL va roR khong ho tro cho DecQFloat!");
		}
		else
		{
			GetDlgItemText(IDC_EBit, temp);
			if (temp != "")
			{
				this->d = 2;
				SetDlgItemText(IDC_EBit, L"");
				string val(CW2A(temp.GetString()));
				Expression = Expression + val;
				x = convert.BinToDec(val);
			}
			else
			{
				GetDlgItemText(IDC_EHex, temp);
				if (temp != "")
				{
					this->d = 3;
					SetDlgItemText(IDC_EHex, L"");
					string val(CW2A(temp.GetString()));
					Expression = Expression + val;
					x = convert.HexToDec(val);
				}
				else
				{
					SetDlgItemText(IDC_ValResult, L"Can't calculate! Data is null, please fill in!");
				}
			}
		}
	}
	SetDlgItemText(IDC_EDecQint, L"");
	SetDlgItemText(IDC_EDecQfloat, L"");
	SetDlgItemText(IDC_EBit, L"");
	SetDlgItemText(IDC_EHex, L"");
}

void CCalculatorDlg::OnBnClickedBconvert()
{
	this->ConvertFI = !this->ConvertFI;
	OnBnClickedBac();
}

bool CCalculatorDlg::checkTH(CString cs, int k)
{
	switch (k)
	{
	case 1:
		if (this->DecQInt == cs || cs == "")
			return false;
	case 2:
		if (this->DecQFloat == cs || cs == "")
			return false;
	case 3:
		if (this->Bit == cs || cs == "")
			return false;
	case 4:
		if (this->Hex == cs || cs == "")
			return false;
	default:
		break;
	}
	return true;
}
