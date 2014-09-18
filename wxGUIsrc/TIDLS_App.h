// Main app and window classes

#pragma once

// wx Headers
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

// App class
class TIDLS_App : public wxApp {
public: 
	virtual bool OnInit();
};

// Main frame class
class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	/* Layout methods */

	wxSizer* createLayout();

	/* Event Handlers */

	// Generic
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	// Buttons
	void OnLoadConstants(wxCommandEvent& event);
	void OnLoadData(wxCommandEvent& event);
	void OnGenerate(wxCommandEvent& event);
	void OnAnalyze(wxCommandEvent& event);

	/* Member Variables */

	// Buttons
	wxButton *loadConstantsButton;
	wxButton *loadDataButton;
	wxButton *generateButton;
	wxButton *analyzeButton;

	// Operation text log
	wxTextCtrl *operationLog;

	// Place holders for what will be graphs
	wxTextCtrl *tauGraph;
	wxTextCtrl *crossGraph;
	wxTextCtrl *lifetimeGraph;

	// wxWidgets macro for event table creation
	wxDECLARE_EVENT_TABLE();
};

// event ID's
enum {
	 BUTTON_LoadConstants = wxID_HIGHEST + 1,
	 BUTTON_LoadData,
	 BUTTON_Generate,
	 BUTTON_Analyze,
};

// wxWidgets app macro
DECLARE_APP(TIDLS_App);