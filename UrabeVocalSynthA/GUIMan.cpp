#include "GUIMan.h"

using namespace GUIMan;

GUIManager::GUIManager(GLCDManager *glcd_manager, JpSynthManager *jp_synth_manager)
{
  this->current_window = W_NULL;
  this->glcd_man = glcd_manager;
  this->jps_man = jp_synth_manager;
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
//      this->glcd_man->draw_buttons_lower("Sys. Rst.", "Default"); //TODO: After implementing EEPROM value saving
//      for(int i=0; i<this->synth_man->option_count; i++) //TODO: Re-add after implementation of waveform synth manager
//      {
//        this->display_options[i] = this->synth_man->options[i];
//      }
//      glcd_man->draw_option(this->display_options[this->current_option]);
      break;
    case JP_SETTINGS:
      this->glcd_man->draw_title("Vocal S");
      this->glcd_man->draw_buttons_upper("Back", "");
//      this->glcd_man->draw_buttons_lower("Sys. Rst.", "Default"); //TODO: After implementing EEPROM value saving
      for(int i=0; i<this->jps_man->option_count; i++)
      {
        this->display_options[i] = this->jps_man->options[i];
      }
      glcd_man->draw_option(this->display_options[this->current_option]);
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
  switch(this->current_window)
  {
    case MAIN:
      switch(b_val)
      {
        case F3: //Synth
          this->current_window = SYNTH_MENU;
          break;
        case F4: //Vocal
          this->current_window = JP_MENU;
          break;
      }
      break;
    case SYNTH_MENU:
      switch(b_val)
      {
        case F1: //Back
          this->current_window = MAIN;
          break;
        case F2: //Run
          this->current_window = SYNTH_RUN;
          break;
        case F3: //Settings
          this->current_window = SYNTH_SETTINGS;
          break;
      }
      break;
    case JP_MENU:
      switch(b_val)
      {
        case F1: //Back
          this->current_window = MAIN;
          break;
        case F2: //Run
          this->current_window = JP_RUN;
          break;
        case F3: //Settings
          this->current_window = JP_SETTINGS;
          break;
      }
      break;
    case SYNTH_SETTINGS:
      switch(b_val)
      {
        case F1: //Back
          this->current_window = SYNTH_MENU;
          break;
      }
      break;
    case JP_SETTINGS:
      switch(b_val)
      {
        case F1: //Back
          this->current_window = JP_MENU;
          break;
      }
      break;
    case SYNTH_RUN:
      switch(b_val)
      {
        case F1: //Exit
          this->current_window = SYNTH_MENU;
          break;
        case F3: //Panic
          //TODO: All notes off (after implement waveform synth manager)
          break;
      }
      break;
    case JP_RUN:
      switch(b_val)
      {
        case F1: //Exit
          this->current_window = JP_MENU;
          break;
        case F3: //Panic
          this->jps_man->end_speak();
          break;
        case F4: //Clear Buffer
          this->jps_man->kana_buffer_clear();
          break;
      }
      break;
  }
  this->do_draw();
}
