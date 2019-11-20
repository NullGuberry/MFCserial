
// MFCserialportDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCserialport.h"
#include "MFCserialportDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCserialportDlg 대화 상자



CMFCserialportDlg::CMFCserialportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERIALPORT_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_str_baudrate(_T(""))
	, m_str_databit(_T(""))
	, m_str_stopbit(_T(""))
	, m_str_parity(_T(""))
	, m_str_handshake(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCserialportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_str_baudrate);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_combo_databit_list);
	DDX_CBString(pDX, IDC_COMBO_DATABIT, m_str_databit);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_combo_stopbit_list);
	DDX_CBString(pDX, IDC_COMBO_STOPBIT, m_str_stopbit);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_combo_parity_list);
	DDX_CBString(pDX, IDC_COMBO_PARITY, m_str_parity);
	DDX_Control(pDX, IDC_COMBO_HANDSHAKE, m_combo_handshake_list);
	DDX_CBString(pDX, IDC_COMBO_HANDSHAKE, m_str_handshake);
	DDX_Control(pDX, IDC_EDIT_RCV_VIEW, m_edit_rcv_view);
	DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_edit_send_data);
}

BEGIN_MESSAGE_MAP(CMFCserialportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MYCLOSE, &CMFCserialportDlg::OnThreadClosed)
	ON_MESSAGE(WM_MYRECEIVE, &CMFCserialportDlg::OnReceive)
	ON_BN_CLICKED(IDC_BT_CONNECT, &CMFCserialportDlg::OnBnClickedBtConnect)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CMFCserialportDlg::OnCbnSelchangeComboComport)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CMFCserialportDlg::OnCbnSelchangeComboBaudrate)
	ON_CBN_SELCHANGE(IDC_COMBO_DATABIT, &CMFCserialportDlg::OnCbnSelchangeComboDatabit)
	ON_CBN_SELCHANGE(IDC_COMBO_STOPBIT, &CMFCserialportDlg::OnCbnSelchangeComboStopbit)
	ON_CBN_SELCHANGE(IDC_COMBO_PARITY, &CMFCserialportDlg::OnCbnSelchangeComboParity)
	ON_CBN_SELCHANGE(IDC_COMBO_HANDSHAKE, &CMFCserialportDlg::OnCbnSelchangeComboHandshake)
	ON_BN_CLICKED(IDC_BT_CLOSE, &CMFCserialportDlg::OnBnClickedBtClose)
	ON_BN_CLICKED(IDC_BT_SEND, &CMFCserialportDlg::OnBnClickedBtSend)
	ON_EN_CHANGE(IDC_EDIT_RCV_VIEW, &CMFCserialportDlg::OnEnChangeEditRcvView)
	ON_EN_CHANGE(IDC_EDIT_SEND_DATA, &CMFCserialportDlg::OnEnChangeEditSendData)
END_MESSAGE_MAP()


// CMFCserialportDlg 메시지 처리기

BOOL CMFCserialportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));

	m_combo_baudrate_list.AddString(_T("300"));
	m_combo_baudrate_list.AddString(_T("600"));
	m_combo_baudrate_list.AddString(_T("1200"));
	m_combo_baudrate_list.AddString(_T("2400"));
	m_combo_baudrate_list.AddString(_T("4800"));
	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("14400"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("28800"));
	m_combo_baudrate_list.AddString(_T("33600"));
	m_combo_baudrate_list.AddString(_T("38400"));
	m_combo_baudrate_list.AddString(_T("56000"));
	m_combo_baudrate_list.AddString(_T("57600"));
	m_combo_baudrate_list.AddString(_T("115200"));
	m_combo_baudrate_list.AddString(_T("128000"));
	m_combo_baudrate_list.AddString(_T("256000"));

	m_combo_databit_list.AddString(_T("7 Bit"));
	m_combo_databit_list.AddString(_T("8 Bit"));

	m_combo_stopbit_list.AddString(_T("1 Bit"));
	m_combo_stopbit_list.AddString(_T("1.5 Bit"));
	m_combo_stopbit_list.AddString(_T("2 Bit"));

	m_combo_parity_list.AddString(_T("None"));
	m_combo_parity_list.AddString(_T("Even"));
	m_combo_parity_list.AddString(_T("Odd"));

	m_combo_handshake_list.AddString(_T("None"));
	m_combo_handshake_list.AddString(_T("RTS"));
	m_combo_handshake_list.AddString(_T("DTR"));

	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM5");
	m_str_baudrate = _T("9600");
	m_str_databit = _T("8 Bit");
	m_str_stopbit = _T("1 Bit");
	m_str_parity = _T("None");
	m_str_handshake = _T("None");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCserialportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCserialportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCserialportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMFCserialportDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o 핸들을닫는다.
	((CMycomm*)lpara)->HandleClose();
	delete ((CMycomm*)lpara);

	return 0;
}
LRESULT CMFCserialportDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char data[20000];
	if (m_comm)
	{
		m_comm->Receive(data, length); //length 길이만큼데이터를받는다.
		data[length] = _T('\0');
		str += _T("\r\n");
		for (int i = 0; i < length; i++)
		{
			str += data[i];
		}
		m_edit_rcv_view.ReplaceSel(str); //에디트박스에표시하기위함
		str = "";
		//UpdateData(FALSE);
		m_edit_rcv_view.LineScroll(m_edit_rcv_view.GetLineCount());
	}
	return 0;
}

void CMFCserialportDlg::OnBnClickedBtConnect()
{
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("Disconnect!"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_BT_SEND)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CMycomm(_T("\\\\.\\") + m_str_comport, m_str_baudrate, _T("8 Bit"), _T("1 Bit"), _T("None"), _T("None"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("Connect!"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			GetDlgItem(IDC_BT_SEND)->EnableWindow(true);
		}
		else
		{
			AfxMessageBox(_T("USB 연결하세요!"));
		}

	}
}


void CMFCserialportDlg::OnCbnSelchangeComboComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCserialportDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCserialportDlg::OnCbnSelchangeComboDatabit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCserialportDlg::OnCbnSelchangeComboStopbit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCserialportDlg::OnCbnSelchangeComboParity()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCserialportDlg::OnCbnSelchangeComboHandshake()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CMFCserialportDlg::OnBnClickedBtClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_EDIT_RCV_VIEW)->SetWindowText(_T(" "));
}


void CMFCserialportDlg::OnBnClickedBtSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItem(IDC_EDIT_SEND_DATA)->GetWindowText(str);
	str += "\r\n";
	m_comm->Send(str, str.GetLength());
	m_edit_rcv_view.SetWindowText(str);
}



void CMFCserialportDlg::OnEnChangeEditRcvView()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCserialportDlg::OnEnChangeEditSendData()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
