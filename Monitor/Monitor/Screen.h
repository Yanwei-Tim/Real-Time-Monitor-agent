#ifndef __MONITOR_SCREEN__
#define __MONITOR_SCREEN__

#include "common.h"

class Screen
	: public CWnd
{
public:
	Screen();
	virtual ~Screen();
	void Prepare(const CRect &, const CWnd *, pj_uint32_t);
	void Refresh(const CRect &);
	void Hide();
	void Painting();

protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

private:
	CRect         screen_rect;
	const CWnd   *wrapper;
	pj_uint32_t   index;
	SDL_Window   *window;       // SDL����
	SDL_Renderer *render;       // ��Ⱦ��
	SDL_Texture  *texture;      // ����
};

#endif
