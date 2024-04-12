#include <gtkmm.h>

class MyWindow : public Gtk::Window
{
public:
    MyWindow() {
        set_title("window");
        set_default_size(200, 200);
    }
};

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<MyWindow>(argc, argv);
}
