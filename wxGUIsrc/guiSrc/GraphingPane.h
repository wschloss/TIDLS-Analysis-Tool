// Grapher window pane class
// Author: Walter Schlosser


#pragma once
// wx Headers
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class GraphingPane : wxPanel {
public:
	GraphingPane(wxFrame* parent, const wxSize& size, const wxPoint& pos);

	// Catches a paint event
	void paintEvent(wxPaintEvent& event);
	// Allows paint at any time
	void paintNow();
	void render(wxDC& dc);
private:

	wxDECLARE_EVENT_TABLE();
};