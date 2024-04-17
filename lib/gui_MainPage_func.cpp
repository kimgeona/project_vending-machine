#include <gui_MainPage.hpp>

namespace gui
{


void MyButtonMenu::set_name_and_price(Glib::ustring name, Glib::ustring price)
{
    labelName.set_text(name);
    labelPrice.set_text(price);
}


}
