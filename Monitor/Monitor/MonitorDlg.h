
// MonitorDlg.h : ͷ�ļ�
//

#pragma once

#include "TitleRoom.h"
#include "ScreenMgr.h"
#include "Screen.h"
#include "Config.h"
#include "Com.h"

// CMonitorDlg �Ի���
class CMonitorDlg : public CDialogEx
{
// ����
public:
	CMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void    OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnChangeLayout(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLinkScreenUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWatchRoomUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUnlinkScreenUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLinkRoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUnlinkRoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDisconnectAllProxys(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCleanScreens(WPARAM wParam, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	pj_status_t Prepare();
	pj_status_t Launch();
	static void event_func_proxy(evutil_socket_t fd, short event, void *arg);
	void EventOnPipe(evutil_socket_t fd, short event, void *arg);
	void EventThread();

private:
	thread event_thread_;
	struct event *event_;
	struct event_base *event_base_;
	pj_bool_t is_draging_;
	User      *draging_user_;
};
