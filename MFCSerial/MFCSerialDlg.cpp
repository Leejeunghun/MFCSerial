
// MFCSerialDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCSerial.h"
#include "MFCSerialDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include <vector>
#include <sstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define _CRT_SECURE_NO_WARNINGS
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


// CMFCSerialDlg 대화 상자

UINT Thread_Reive(LPVOID param)
{
	CMFCSerialDlg* pDlg = (CMFCSerialDlg*)param;

	pDlg->ConnectSerial();

	return true;
}

UINT Thread_Reive_DGUS(LPVOID param)
{
	CMFCSerialDlg* pDlg = (CMFCSerialDlg*)param;

	pDlg->ConnectSerial("\\\\\.\\\\\COM3",115200);

	return true;
}

CMFCSerialDlg::CMFCSerialDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERIAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCSerialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CMFCSerialDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_SEND, &CMFCSerialDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_DGUS, &CMFCSerialDlg::OnBnClickedBtnDgus)
	ON_BN_CLICKED(IDC_BTN_SEND2, &CMFCSerialDlg::OnBnClickedBtnSend2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCSerialDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCSerialDlg 메시지 처리기

BOOL CMFCSerialDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCSerialDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCSerialDlg::OnPaint()
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
HCURSOR CMFCSerialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSerialDlg::ConnectSerial()
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("\\\\.\\COM9");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	char result[255] = {};
	unsigned char* bytearray = NULL;
	//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;

	int i = 0;
	int j = 0;

	while (SP->IsConnected())
	{
		if (b_SendCheck == true)
		{
			SP->WriteData(c_message, str_message.length() + 3);
			b_SendCheck = false;
		}

		readResult = SP->ReadData(incomingData, dataLength);
		if (readResult == 0)//명령어가 없으므로 쉰다/
		{
			Sleep(500);
			continue;
		}
		printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;
		for (i = 0; i < 10; ++i)
		{
			result[i * 2] = incomingData[i * 2];
			result[i * 2+1] = incomingData[i * 2 + 1];

		}
		//명령어 만 확인
		for (i = 0; i < 20; i++)
		{
			if (result[i] == -1 && result[i + 1] == -1 && result[i + 2] == -1)
			{
				printf("명령 길이[%d] ",i);
				for (j = 0; j < i; j++)
				{
					printf(" %x",  result[j]);
				}
				printf("\n");
				break;
			}
			ReadSerial(result);
		}

		Sleep(500);
	}
	return ;
}

void CMFCSerialDlg::ConnectSerial(const char* portName, unsigned long porSpeed)
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial(portName, porSpeed);    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	char result[255] = {};
	unsigned char* bytearray = NULL;
	//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;

	int i = 0;
	int j = 0;

	while (SP->IsConnected())
	{
		if (b_SendCheck == true)
		{
			SP->WriteData(c_message, str_message.length());
			b_SendCheck = false;
		}

		readResult = SP->ReadData(incomingData, dataLength);
		if (readResult == 0)//명령어가 없으므로 쉰다/
		{
			Sleep(500);
			continue;
		}
		printf("Bytes read: (0 means no data available) %i\n", readResult);
		incomingData[readResult] = 0;
		for (i = 0; i < 10; ++i)
		{
			result[i * 2] = incomingData[i * 2];
			result[i * 2 + 1] = incomingData[i * 2 + 1];

		}
		//명령어 만 확인
		for (i = 0; i < 20; i++)
		{
			if (result[i] == -1 && result[i + 1] == -1 && result[i + 2] == -1)
			{
				printf("명령 길이[%d] ", i);
				for (j = 0; j < i; j++)
				{
					printf(" %x", result[j]);
				}
				printf("\n");
				break;
			}
			ReadSerial(result);
		}

		Sleep(500);
	}
	return;
}

void CMFCSerialDlg::SendSerial()
{
	b_SendCheck = true;
	CString test;
	GetDlgItem(IDC_ED_MESSAGE)->GetWindowTextW(test);

	str_message = std::string(CT2CA(test));

	for (int i = 0; i < str_message.length(); ++i)
		c_message[i] = (char)str_message[i];
	c_message[str_message.length()] = 255;
	c_message[str_message.length() + 1] = 255;
	c_message[str_message.length() + 2] = 255;

	return;
}

void CMFCSerialDlg::ReadSerial(char c_message[])
{
	if (c_message[0] == 0)
	{
		printf("명령어 무효 \n");
	}
	else if (c_message[0] == 26)
	{
		printf("유효하지 않는 변수 명 사용\n");
	}
	else if (c_message[0] == 101)
	{
		printf("버튼 입력");
	}
}



void CMFCSerialDlg::SendSerial_Device()
{
	b_SendCheck = true;
	CString test;
	GetDlgItem(IDC_ED_MESSAGE)->GetWindowTextW(test);

	CStringArray str;

	str_message = std::string(CT2CA(test));

	c_message[0] = 2;
	for (int i = 1; i < str_message.length(); ++i)
		c_message[i] = (char)str_message[i];
	c_message[str_message.length()] = 3;
}

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}

void CMFCSerialDlg::SendSerial_DGUS()
{
	b_SendCheck = true;
	CString test;
	GetDlgItem(IDC_ED_MESSAGE)->GetWindowTextW(test);

	CStringArray str;
	CString var;
	var = " ";
	
	str_message = std::string(CT2CA(test));

	unsigned int nHexValue = 0;
	vector<string> result = split(str_message, ' ');
	for (int i = 0; i < result.size(); i++) {
		stringstream convert(result[i]);
		convert >> std::hex >> nHexValue;
		cout << std::hex << nHexValue << endl;

		c_message[i] = nHexValue;
	}
	c_message_length = result.size();

	printf("send");
}

void CMFCSerialDlg::OnBnClickedBtnConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	AfxBeginThread(Thread_Reive, this);
}


void CMFCSerialDlg::OnBnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

//	SendSerial();
	SendSerial_Device();
}

int CMFCSerialDlg::splitString(CString str, CString var, CStringArray& strs)
{
	int count = 0;

	CString tempStr = str;

	int length = str.GetLength();

	while (length)
	{
		int find = tempStr.Find(var);
		if (find != -1)
		{
			CString temp = tempStr.Left(find);
			strs.Add(temp);
			int varLen = _tcslen(var);
			tempStr = tempStr.Mid(find + varLen);
		}
		else
		{
			strs.Add(tempStr);
			length = 0;
		}
		count++;

	}
	return count;
}



void CMFCSerialDlg::OnBnClickedBtnDgus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxBeginThread(Thread_Reive_DGUS, this);
}


void CMFCSerialDlg::OnBnClickedBtnSend2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SendSerial_DGUS();
}


void CMFCSerialDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	string test = "5a 59";

	unsigned int nHexValue = 0;

	vector<string> result = split(test, ' ');
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";

		stringstream convert(result[i]);
		convert >> std::hex >> nHexValue;
		cout << std::hex << nHexValue << endl;

		c_message[i] = nHexValue;
	}

}
