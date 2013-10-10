#include "GUIMan.h"

using namespace GUIMan;

GUIManager::GUIManager(GLCDManager *glcd_manager)
{
  this->current_window = W_NULL;
  this->glcd_man = glcd_manager;
}

void GUIManager::draw()
{
  this->glcd_man->u8g.firstPage();
  do {
    do_draw();
  } while(this->glcd_man->u8g.nextPage());
}

void GUIManager::do_draw()
{
  this->glcd_man->draw_base();
  switch(this->current_window)
  {
    case MAIN:
      this->glcd_man->draw_title_large("Main Title");
      this->glcd_man->draw_buttons_lower("Synth", "Vocal");
      break;
    case SYNTH_MENU:
      this->glcd_man->draw_title("Synth");
      this->glcd_man->draw_buttons_upper("Back", "Run");
      this->glcd_man->draw_buttons_lower("Settings", "");
      break;
    case JP_MENU:
      this->glcd_man->draw_title("Vocal");
      this->glcd_man->draw_buttons_upper("Back", "Run");
      this->glcd_man->draw_buttons_lower("Settings", "");
      break;
    case SYNTH_SETTINGS:
      this->glcd_man->draw_title("Synth S");
      this->glcd_man->draw_buttons_upper("Back", "");
      this->glcd_man->draw_buttons_lower("Sys. Rst.", "Default");
      break;
    case JP_SETTINGS:
      this->glcd_man->draw_title("Vocal S");
      this->glcd_man->draw_buttons_upper("Back", "");
      this->glcd_man->draw_buttons_lower("Sys. Rst.", "Default");
      break;
    case SYNTH_RUN:
      this->glcd_man->draw_title("Synth");
      this->glcd_man->draw_buttons_upper("Exit", "");
      this->glcd_man->draw_buttons_lower("Panic", "");
      break;
    case JP_RUN:
      this->glcd_man->draw_title("Vocal");
      this->glcd_man->draw_buttons_upper("Exit", "");
      this->glcd_man->draw_buttons_lower("Panic", "Clr Buf");
      this->glcd_man->draw_kana_buffer(this->display_kana, this->notes_on);
      break;
  }
}

void GUIManager::handle_menu_input(ButtonValue b_val)
{
  //todo
}
