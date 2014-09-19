#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include "GraphingPane.h"

// Event and handler connection table
wxBEGIN_EVENT_TABLE(GraphingPane, wxPanel)
	EVT_PAINT(GraphingPane::paintEvent)
wxEND_EVENT_TABLE()

GraphingPane::GraphingPane(wxFrame* parent, const wxSize& size, const wxPoint& pos) : wxPanel(parent, wxID_ANY, pos, size) {

}

// Paint event handler
void GraphingPane::paintEvent(wxPaintEvent& event) {

}

void GraphingPane::paintNow() {

}

void GraphingPane::render(wxDC& dc) {
	
}