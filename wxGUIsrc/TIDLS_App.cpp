#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include "TIDLS_App.h"

// wxWidgets begin app macro
IMPLEMENT_APP(TIDLS_App);

// Initialization function
bool TIDLS_App::OnInit() {
	// Create a frame
	MainFrame *frame = new MainFrame("TIDLS Analyzer", wxDefaultPosition, wxSize(900,600) );
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

// Event and handler connection table
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	EVT_BUTTON(BUTTON_LoadConstants, MainFrame::OnLoadConstants)
	EVT_BUTTON(BUTTON_LoadData, MainFrame::OnLoadData)
	EVT_BUTTON(BUTTON_Generate, MainFrame::OnGenerate)
	EVT_BUTTON(BUTTON_Analyze, MainFrame::OnAnalyze)
wxEND_EVENT_TABLE()

// Main frame construction
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size) {

	//Init and add buttons
	loadConstantsButton = new wxButton(this, BUTTON_LoadConstants, "Load Constants", wxDefaultPosition, wxDefaultSize, 0);
	loadDataButton = new wxButton(this, BUTTON_LoadData, "Load Data", wxDefaultPosition, wxDefaultSize, 0);
	generateButton = new wxButton(this, BUTTON_Generate, "Generate Data", wxDefaultPosition, wxDefaultSize, 0);
	analyzeButton = new wxButton(this, BUTTON_Analyze, "Analyze Data", wxDefaultPosition, wxDefaultSize, 0);

	//Init and add the operation log
	operationLog = new wxTextCtrl(this, wxID_ANY, "TIDLS Analyzer Initialized\n", wxDefaultPosition, wxSize(200,450), wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);

	//Init and add the place holders for what will be graphs
	tauGraph = new wxTextCtrl(this, wxID_ANY, "This will be a graph of tau0 vs Et", wxDefaultPosition, wxSize(250,250), wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);
	crossGraph = new wxTextCtrl(this, wxID_ANY, "This will be a graph of k vs Et", wxDefaultPosition, wxSize(250,250), wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);
	lifetimeGraph = new wxTextCtrl(this, wxID_ANY, "This will be a graph of the lifetime vs injection for different temperatures", wxDefaultPosition, wxSize(500,250), wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);

	//Create layout with sizers
	SetSizer(MainFrame::createLayout());

	//Create Menu Bar
	wxMenu *menuFile = new wxMenu;
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar( menuBar );

	//Create status bar
	CreateStatusBar();
	SetStatusText("TIDLS data analyzing tool");
}

//Layout creation
wxSizer* MainFrame::createLayout() {
	// buttons area
	wxBoxSizer* buttons = new wxBoxSizer(wxVERTICAL);

	buttons->Add(loadConstantsButton,0,wxEXPAND,0);
	buttons->Add(loadDataButton,0,wxEXPAND,0);
	buttons->Add(generateButton,0,wxEXPAND,0);
	buttons->Add(analyzeButton,0,wxEXPAND,0);

	// tau and k graphs area
	wxBoxSizer* analysisGraphs = new wxBoxSizer(wxHORIZONTAL);

	analysisGraphs->Add(tauGraph,0,0,0);
	analysisGraphs->Add(crossGraph,0,0,0);

	// lifetime graph area
	wxBoxSizer* dataGraph = new wxBoxSizer(wxVERTICAL);

	dataGraph->Add(lifetimeGraph,0,0,0);

	// Link graph areas into one
	wxBoxSizer* graphArea = new wxBoxSizer(wxVERTICAL);

	graphArea->Add(analysisGraphs,0,0,0);
	graphArea->Add(dataGraph,0,0,0);

	// link three aread horizontally
	wxBoxSizer* windowSizer = new wxBoxSizer(wxHORIZONTAL);

	windowSizer->Add(buttons,0,wxEXPAND | wxALL,20);
	windowSizer->Add(graphArea,0,wxEXPAND | wxALL,10);
	windowSizer->Add(operationLog,0,wxEXPAND | wxALL,20);

	// Access window size
	windowSizer->SetSizeHints(this);

	return windowSizer;

}

// Main frame event handlers
void MainFrame::OnExit(wxCommandEvent& event) {
	Close( true );
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("TIDLS Analyzer is used for extracting possible defects from lifetime data");
}

void MainFrame::OnLoadConstants(wxCommandEvent& event) {
	operationLog->AppendText("Loading constants...\n");
	wxMessageBox("Loading Constants has not been linked");
}

void MainFrame::OnLoadData(wxCommandEvent& event) {
	operationLog->AppendText("Loading data...\n");
	wxMessageBox("Loading Data has not been linked");
}

void MainFrame::OnGenerate(wxCommandEvent& event) {
	operationLog->AppendText("Generating data...\n");
	wxMessageBox("Generate has not been linked");
}

void MainFrame::OnAnalyze(wxCommandEvent& event) {
	operationLog->AppendText("Analyzing data...\n");
	wxMessageBox("Analyze has not been linked");
}

