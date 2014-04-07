#include "main.h"

class MyArea : public Gtk::DrawingArea
{
	public:
		MyArea();
		virtual ~MyArea();

	protected:
		Cairo::RefPtr<Cairo::ToyFontFace> font;
		//Override default signal handler:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
		void line(const Cairo::RefPtr<Cairo::Context>& cr,
				double x1, double y1, double x2, double y2, double weight);
};

MyArea::MyArea()
{
	font = Cairo::ToyFontFace::create("Bitstream Charter",
									  Cairo::FONT_SLANT_NORMAL,
									  Cairo::FONT_WEIGHT_BOLD);

}

MyArea::~MyArea()
{
}

void MyArea::line(const Cairo::RefPtr<Cairo::Context>& cr, double x1, double y1, double x2, double y2, double weight) {
	// Draw a line.
	cr->set_line_width(8.0);
	cr->set_source_rgba(1.0, 1.0, 1.0, 0.3);
	cr->move_to(x1, y1);
	cr->line_to(x2, y2);
	cr->stroke();

	double x3 = (x1+x2)/2;
	double y3 = (y1+y2)/2;

	cr->move_to(x3, y3);
	cr->set_source_rgb(1,1,1);
	cr->set_font_face(font);
	cr->set_font_size(16);
	std::ostringstream strs;
	double l1 = x1-x2;
	double l2 = y1-y2;
	weight = sqrt(l1*l1 + l2*l2);
	strs << weight;
	cr->show_text(strs.str());
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	const int grid_size = 20;

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);

	// Clear the background
    cr->set_source_rgb(0.5, 0.5, 0.5);
    cr->paint();

	// Paint a grid.
	cr->set_line_width(1.0);
	cr->set_source_rgb(0.6, 0.6, 0.6);
	for (int i=0; i<width; i=i+grid_size) {
		cr->move_to(i, 0);
		cr->line_to(i, height);
	}
	for (int i=0; i<height; i=i+grid_size) {
		cr->move_to(0, i);
		cr->line_to(width, i);
	}
	cr->stroke();

	// Draw some lines.
	line(cr, 100, 100, 300, 300, 15);
	line(cr, 400, 150, 200, 100, 99);
	line(cr, 10, 10, 10, 110, 99);

	cr->get_target()->write_to_png("output.png");

	return true;
}

int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.prog.graph");

	Gtk::Window win;
	win.set_default_size(640, 480);
	win.set_position(Gtk::WIN_POS_CENTER);
	win.set_title("Graph");

	MyArea area;
	win.add(area);
	area.show();

	Graph graph;
	graph.add(Node(1), Node(2));
	graph.add(Node(2), Node(2));
	graph.add(Node(2), Node(1));
	graph.add(Node(2), Node(3));
	graph.add(Node(4), Node(2));

	graph.print();

	return app->run(win);
}

