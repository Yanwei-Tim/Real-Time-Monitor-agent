
// MonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "afxdialogex.h"

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


// CMonitorDlg �Ի���



CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMonitorDlg ��Ϣ�������
static ScreenMgr *g_screen_mgr = NULL;
BOOL CMonitorDlg::OnInitDialog()
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
	CRect rect;
	GetClientRect(&rect);

	pj_int32_t width = abs(rect.bottom - rect.top);
	pj_int32_t height = abs(rect.right - rect.left);

	SDL_Init( SDL_INIT_VIDEO );
	av_register_all();
	pj_init();

	pj_str_t avsproxy_ip = pj_str("192.168.6.54");
	pj_str_t local_ip = pj_str("192.168.6.54");
	g_screen_mgr = new ScreenMgr(this, 1, avsproxy_ip, 12000, 10, local_ip, 15000);

	pj_status_t status;
	pj_str_t log_file_name = pj_str("avs_proxy_client.log");

	status = g_screen_mgr->Prepare(log_file_name);
	pj_assert(status == PJ_SUCCESS);

	status = g_screen_mgr->Launch();
	pj_assert(status == PJ_SUCCESS);

	g_screen_mgr->Adjest(width, height);
	
	this->MoveWindow(CRect(0, 0, width, height));
	this->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMonitorDlg::OnPaint()
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
HCURSOR CMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMonitorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	pj_assert(lpMMI != NULL);
	lpMMI->ptMinTrackSize.x = g_screen_mgr->GetDefaultResolution().x;
	lpMMI->ptMinTrackSize.y = g_screen_mgr->GetDefaultResolution().y;

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CMonitorDlg::OnSizing(UINT nSide, LPRECT lpRect)
{
	g_screen_mgr->GetSuitedSize(lpRect);

	CDialogEx::OnSizing(nSide, lpRect);
}

void CMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	g_screen_mgr->Adjest( cx, cy );

	CDialogEx::OnSize(nType, cx, cy);
}

void CMonitorDlg::OnBnClickedButton1()
{
	struct resolution
	{
		pj_uint32_t width;
		pj_uint32_t height;
		enum_screen_mgr_resolution_t res;
	} ress[4] = 
	{
		{ 400, 400, SCREEN_RES_1x1 },
		{ 200, 200, SCREEN_RES_2x2 },
		{ 100, 100, SCREEN_RES_1x5 },
		{ 100, 100, SCREEN_RES_3x3 },
	};

	static enum_screen_mgr_resolution_t g_res_type = SCREEN_RES_1x1;

	g_screen_mgr->ChangeLayout(ress[g_res_type].res);

	g_res_type = (enum_screen_mgr_resolution_t)(( g_res_type + 1 ) % 4);
}
