#include "WavGraph.h"

BEGIN_EVENT_TABLE(WavGraph, wxPanel)
    EVT_PAINT(WavGraph::OnPaint)
END_EVENT_TABLE()


WavGraph::WavGraph(wxWindow *parent,
                   wxWindowID id,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style,
                   const wxString& name):wxPanel(parent, id, pos, size, style,name)
{
    //ctor
}

WavGraph::~WavGraph()
{
    //dtor
}
