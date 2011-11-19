/*
WASTE - listview.hpp (Class for management of Windows listviews)
Copyright (C) 2003 Nullsoft, Inc.
Copyright (C) 2004 WASTE Development Team

WASTE is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

WASTE  is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with WASTE; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _LISTVIEW_H_
#define _LISTVIEW_H_

#ifndef _DEFINE_WXUI

//#include <commctrl.h>

class W_ListView
{
public:
	W_ListView() { m_hwnd=NULL; m_sort_type=0; m_sort_col=0; m_sort_dir=1; m_col=0; }
	W_ListView(HWND hwnd) { m_hwnd=hwnd; m_col=0; }
	~W_ListView() { };

	void setwnd(HWND hwnd)
	{
		m_hwnd=hwnd;
		ListView_SetExtendedListViewStyle(m_hwnd,LVS_EX_FULLROWSELECT);
	};

	void AddCol(char *text, int w);
	int GetCount() { return ListView_GetItemCount(m_hwnd); }
	int GetParam(int p);
	void DeleteItem(int n) { ListView_DeleteItem(m_hwnd,n); }
	void Clear() { ListView_DeleteAllItems(m_hwnd); }
	int GetSelected(int x) { return (ListView_GetItemState(m_hwnd, x, LVIS_SELECTED) & LVIS_SELECTED)?1:0; }
	void SetSelected(int x) { ListView_SetItemState(m_hwnd,x,LVIS_SELECTED,LVIS_SELECTED); }
	int InsertItem(int p, const char *text, int param);
	int InsertItemSorted(const char *text, int param, const char *sorttext);
	void SetItemText(int p, int si, const char *text);
	void SetItemParam(int p, int param);

	void GetText(int p, int si, char *text, int maxlen) { ListView_GetItemText(m_hwnd, p, si, text, maxlen); }
	int FindItemByParam(int param)
	{
		LVFINDINFO fi={LVFI_PARAM,0,param};
		return ListView_FindItem(m_hwnd,-1,&fi);
	};
	void SetSortColumn(int col, int bNumeric=0)
	{
		if (col == m_sort_col) m_sort_dir=-m_sort_dir;
		else m_sort_dir=1;
		m_sort_col=col;
		m_sort_type=bNumeric;
	};
	void SetSortDir(int dir) { m_sort_dir=dir; }
	int GetSortColumn() { return m_sort_col; }
	int GetSortDir() { return m_sort_dir; }
	int GetColumnWidth(int col);
	void Resort();
	HWND getwnd() { return m_hwnd; }

protected:
	HWND m_hwnd;
	int m_col;
	int m_sort_col;
	int m_sort_dir;
	int m_sort_type;
	static int CALLBACK sortfunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	int _docompare(const char *s1, const char *s2);
};

#else /* _DEFINE_WXUI */
/* wxWindows version */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/listctrl.h>

class W_ListView
{
public:
	W_ListView() { m_hwnd=NULL; m_sort_type=0; m_sort_col=0; m_sort_dir=1; m_col=0; }
	W_ListView(wxListCtrl* hwnd) { m_hwnd=hwnd; m_col=0; }
	~W_ListView() { };

	void setwnd(wxListCtrl* hwnd)
	{
		m_hwnd=hwnd;
	};

	void AddCol(char *text, int w);
	int GetCount() { return m_hwnd->GetItemCount(); }
	int GetParam(int p);
	void DeleteItem(int n) { m_hwnd->DeleteItem((long) n); }
	void Clear() { m_hwnd->DeleteAllItems(); }
	int GetSelected(int x) { return (m_hwnd->GetItemState((long) x, wxLIST_STATE_SELECTED))?1:0; }
	void SetSelected(int x) { m_hwnd->SetItemState((long) x,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED); }
	int InsertItem(int p, const char *text, int param);
	int InsertItemSorted(const char *text, int param, const char *sorttext);
	void SetItemText(int p, int si, const char *text);
	void SetItemParam(int p, int param);

	void GetText(int p, int si, char *text, int maxlen) {
				wxListItem item;
				item.m_itemId = p;
				item.m_col = si;
				item.m_mask = wxLIST_MASK_TEXT;
				if (m_hwnd->GetItem(item)) {
				wxstr_to_cstr (text, item.GetText().c_str(), maxlen);
				} else {
				printf("oops! GetItem false for %d/%d\n", p, si);
				*text = '\0';
				}
		}
	int FindItemByParam(int param)
	{
		return m_hwnd->FindItem(-1,(long) param);
	};
	void SetSortColumn(int col, int bNumeric=0)
	{
		if (col == m_sort_col) m_sort_dir=-m_sort_dir;
		else m_sort_dir=1;
		m_sort_col=col;
		m_sort_type=bNumeric;
	};
	void SetSortDir(int dir) { m_sort_dir=dir; }
	int GetSortColumn() { return m_sort_col; }
	int GetSortDir() { return m_sort_dir; }
	int GetColumnWidth(int col);
	void Resort();
	wxListCtrl* getwnd() { return m_hwnd; }

protected:
	wxListCtrl *m_hwnd;
	int m_col;
	int m_sort_col;
	int m_sort_dir;
	int m_sort_type;
	static int wxCALLBACK sortfunc(long lParam1, long lParam2, long lParamSort);
	int _docompare(const char *s1, const char *s2);
};
#endif /* _DEFINE_WXUI */

#endif//_LISTVIEW_H_
