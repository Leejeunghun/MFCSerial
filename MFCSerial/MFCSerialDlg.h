
// MFCSerialDlg.h: 헤더 파일
//

#pragma once
#include "SerialClass.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>

using std::cout; using std::endl;
using std::string; using std::hex;
using std::stringstream;
// CMFCSerialDlg 대화 상자
class CMFCSerialDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCSerialDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERIAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ConnectSerial();
	void ConnectSerial(const char* portName, unsigned long porSpeed);


	void SendSerial();

	void SendSerial_Device();
	void SendSerial_DGUS();


	int splitString(CString str, CString var, CStringArray& strs);
	void ReadSerial(char c_message[]);
	bool b_SendCheck = false; // false = 보낼 것 없음 // true = 보낼 필요 있음

	char c_message[255] = {};
	int c_message_length = 0;
	string str_message;

	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnDgus();
	afx_msg void OnBnClickedBtnSend2();
	afx_msg void OnBnClickedButton1();
};
