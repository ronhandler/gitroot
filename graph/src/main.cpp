#include "main.h"

class MyArea : public Gtk::DrawingArea
{
	public:
		MyArea();
		virtual ~MyArea();

	protected:
		//Override default signal handler:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
};

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// Set a line width.
	cr->set_line_width(10.0);

	// draw red lines out from the center of the window
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->move_to(0, 0);
	cr->line_to(width, height);
	cr->move_to(width, 0);
	cr->line_to(0, height);
	cr->stroke();

	return true;
}

int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.prog.graph");

	Gtk::Window win;
	win.set_default_size(640, 480);
	win.set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	win.set_title("DrawingArea");

	MyArea area;
	win.add(area);
	area.show();

	return app->run(win);
}

