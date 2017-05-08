
// 7BotSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "7BotSystemDlg.h"
#include "afxdialogex.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy7BotSystemDlg �Ի���



CMy7BotSystemDlg::CMy7BotSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy7BotSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy7BotSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy7BotSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMy7BotSystemDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM3, &CMy7BotSystemDlg::OnBnClickedButtonOpenCom3)
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM4, &CMy7BotSystemDlg::OnBnClickedButtonOpenCom4)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECOM3, &CMy7BotSystemDlg::OnBnClickedButtonCloseCom3)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECOM4, &CMy7BotSystemDlg::OnBnClickedButtonCloseCom4)
	ON_MESSAGE(WM_COMERROR, &CMy7BotSystemDlg::OnComError)
	ON_MESSAGE(WM_COMSUCCESS, &CMy7BotSystemDlg::OnComSuccess)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMy7BotSystemDlg ��Ϣ�������

BOOL CMy7BotSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for (int i = 0; i < 2; i++)
	{
		m_thCom[i] = NULL;
		m_dlgCom[i] = NULL;
	}
	GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(FALSE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy7BotSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy7BotSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy7BotSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy7BotSystemDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMy7BotSystemDlg::OnBnClickedButtonOpenCom3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[0] = new CComRcvThread(_T("Com3"));
	if (m_thCom[0]->CreateThread())
	{
		GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(TRUE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonOpenCom4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[1] = new CComRcvThread(_T("Com4"));
	if (m_thCom[1]->CreateThread())
	{
		GetDlgItem(IDC_BUTTON_OPENCOM4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(TRUE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonCloseCom3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[0]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
	GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(FALSE);

	// �رմ���
	if (m_dlgCom[0] != NULL)
	{
		delete m_dlgCom[0];
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonCloseCom4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[1]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
	GetDlgItem(IDC_BUTTON_OPENCOM4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(FALSE);

	// �رմ���
	if (m_dlgCom[1] != NULL)
	{
		delete m_dlgCom[1];
	}
}


LRESULT CMy7BotSystemDlg::OnComError(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < 2; i++)
	{
		if (wParam == (int)(void *)m_thCom[i])
		{
			AfxMessageBox(m_thCom[i]->m_sCom + _T("�޷��򿪣�"));

			m_thCom[i]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
			m_thCom[i] = NULL;
			GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(FALSE);

			break;
		}
	}
	return 0;
}


LRESULT CMy7BotSystemDlg::OnComSuccess(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < 2; i++)
	{
		if (wParam == (int)(void *)m_thCom[i])
		{
			SetTimer(i, 100, NULL);

			// �򿪴������������Ϣ
			if (m_dlgCom[i] == NULL)
			{
				m_dlgCom[i] = new CSerialDlg();
				m_dlgCom[i]->Create(IDD_SERIAL_DIALOG);
			}
  			m_dlgCom[i]->ShowWindow(SW_SHOW);

			break;
		}
	}
	return 0;
}


void CMy7BotSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for (int i = 0; i < 2; i++)
	{	
		if (nIDEvent == i)
		{
			m_thCom[i]->PostThreadMessage(WM_RECEIVE, NULL, NULL);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
