#ifndef MAIN_H
#define MAIN_H

#include <iostream>
using namespace std;
#include <math.h>

#include <gtkmm.h>
#include <cairomm/cairomm.h>

#include "graph.h"

class MyArea : public Gtk::DrawingArea
{
	public:
		MyArea();
		virtual ~MyArea();
		Graph graph;

	protected:
		Cairo::RefPtr<Cairo::ToyFontFace> font;
		//Override default signal handler:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
		void line(const Cairo::RefPtr<Cairo::Context>& cr,
				double x1, double y1, double x2, double y2, double weight);
		void drawGraph(const Cairo::RefPtr<Cairo::Context>& cr, Graph g);
};


#endif

