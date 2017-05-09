
// 7BotSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "7BotSystemDlg.h"
#include "afxdialogex.h"

#include <math.h>

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

	arm.theta[6] = 45.0;
	center.x = 0.0;
	center.y = 265.0;
	center.z = 200.0;
	radius = 65.0;
	angle = 0.0;
	delta = 5.0;

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


void CMy7BotSystemDlg::OnBnClickedButtonOpenCom3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[0] = new CComRcvThread(_T("Com3"), 0);
	if (m_thCom[0]->CreateThread())
	{
		GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(TRUE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonOpenCom4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[1] = new CComRcvThread(_T("Com4"), 1);
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

	KillTimer(0);

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

	KillTimer(1);

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
			SetTimer(i, 200, NULL);

			// �򿪴������������Ϣ
			if (m_dlgCom[i] == NULL)
			{
				m_dlgCom[i] = new CSerialDlg(_T("Serial Monitor : ") + m_thCom[i]->m_sCom, (CWnd *)this);
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


void CMy7BotSystemDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (calculate())
	{
		angle = - angle;
		while (calculate())
		{
			angle += delta;
		}
	}
	angle += delta;

	for (int i = 0; i < 2; i++)
	{
		m_thCom[i]->PostThreadMessage(WM_MOVEANGLE, (WPARAM)arm.theta, NULL);
	}
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
}


// CMy7BotSystemDlg �������


int CMy7BotSystemDlg::calculate()
{
	PVector j6(center);
	PVector vec56;
	PVector vec67(0.0, 0.0, 1.0);

	j6.x += radius * sin(angle / 180 * PI);
	j6.y -= radius * cos(angle / 180 * PI);
	vec56.x = - sin(angle / 180 * PI);
	vec56.y = cos(angle / 180 * PI);

	return arm.IK6(j6, vec56, vec67);
}