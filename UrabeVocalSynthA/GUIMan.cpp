#include "GUIMan.h"

using namespace GUIMan;

GUIManager::GUIManager(GLCDManager *glcd_manager, JpSynthManager *jp_synth_manager)
{
  this->current_window = MAIN;
  this->mode = MENU;
  this->glcd_man = glcd_manager;
  this->jps_man = jp_synth_manager;
}

SystemMode GUIManager::get_system_mode() { return this->mode; }

void GUIManager::draw()
{
  this->glcd_man->u8g.firstPage();
  do {
    do_draw();
  } while(this->glcd_man->u8g.nextPage());
}

void GUIManager::do_draw()
{
  this->mode = MENU;
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
//      glcd_man->draw_option(this->display_options[this->current_option]);
      break;
    case JP_SETTINGS:
      this->glcd_man->draw_title("Vocal S");
      this->glcd_man->draw_buttons_upper("Back", "");
//      this->glcd_man->draw_buttons_lower("Sys. Rst.", "Default"); //TODO: After implementing EEPROM value saving
      glcd_man->draw_option(this->jps_man->options[this->current_option]);
      break;
    case SYNTH_RUN:
      this->mode = WAVEFORM;
      this->glcd_man->draw_title("Synth");
      this->glcd_man->draw_buttons_upper("Back", "");
      this->glcd_man->draw_buttons_lower("Panic", "");
      break;
    case JP_RUN:
      this->mode = VOCAL;
      this->glcd_man->draw_title("Vocal");
      this->glcd_man->draw_buttons_upper("Back", "");
      this->glcd_man->draw_buttons_lower("Panic", "Clr Buf");
      KanaTable::Kana disp_kana[9];
      int offset = 0;
      if(this->jps_man->get_notes_on())
        offset = -1;
      for(int i=0; i<9; i++)
      {
        int position = i + this->jps_man->get_buffer_position() + offset;
        disp_kana[i] = this->jps_man->kana_buffer[position];
      }
      this->glcd_man->draw_kana_buffer(disp_kana, this->jps_man->get_notes_on());
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
        case _F3: //Synth
          this->current_window = SYNTH_MENU;
          break;
        case _F4: //Vocal
          this->current_window = JP_MENU;
          break;
      }
      break;
    case SYNTH_MENU:
      switch(b_val)
      {
        case _F1: //Back
          this->current_window = MAIN;
          break;
        case _F2: //Run
          this->current_window = SYNTH_RUN;
          break;
        case _F3: //Settings
          this->current_option = 0;
          this->current_window = SYNTH_SETTINGS;
          break;
      }
      break;
    case JP_MENU:
      switch(b_val)
      {
        case _F1: //Back
          this->current_window = MAIN;
          break;
        case _F2: //Run
          this->current_window = JP_RUN;
          break;
        case _F3: //Settings
          this->current_option = 0;
          this->current_window = JP_SETTINGS;
          break;
      }
      break;
    case SYNTH_SETTINGS:
      switch(b_val)
      {
        case _F1: //Back
          this->current_window = SYNTH_MENU;
          break;
      }
      break;
    case JP_SETTINGS:
      switch(b_val)
      {
        case _F1: //Back
          this->current_window = JP_MENU;
          break;
        case _UP:
          this->change_option(&this->jps_man->options[this->current_option], 1);
          break;
        case _DOWN:
          this->change_option(&this->jps_man->options[this->current_option], -1);
          break;
        case _LEFT:
          this->current_option--;
          if(this->current_option < 0)
            this->current_option = this->jps_man->get_option_count() - 1;
          break;
        case _RIGHT:
          this->current_option++;
          if(this->current_option >= this->jps_man->get_option_count())
            this->current_option = 0;
          break;
      }
      break;
    case SYNTH_RUN:
      switch(b_val)
      {
        case _F1: //Exit
          this->current_window = SYNTH_MENU;
          break;
        case _F3: //Panic
          //TODO: All notes off (after implement waveform synth manager)
          break;
      }
      break;
    case JP_RUN:
      switch(b_val)
      {
        case _F1: //Exit
          this->current_window = JP_MENU;
          break;
        case _F3: //Panic
          this->jps_man->end_speak();
          //TODO: Fix GLCD issue
          break;
        case _F4: //Clear Buffer
          this->jps_man->kana_buffer_clear();
          //TODO: FIx GLCD issue
          break;
      }
      break;
  }
  this->draw();
}

void GUIManager::change_option(ConfigData::ConfigOption *option, int direction)
{
  int precision = 1;
  if(direction < 0)
    precision = -1;
  switch(option->type)
  {
    case ConfigData::INT:
      if(option->value_count != -1)
        precision *= option->value_count;
      if(abs(precision) == 1)
        precision *= 5; //Default Precision
      option->value += precision;
      int min;
      int max;
      sscanf(option->values[0], "%d", &min);
      sscanf(option->values[1], "%d", &max);
      if(option->value < min)
        option->value = min;
      if(option->value > max)
        option->value = max;
      break;
    case ConfigData::ENUM:
      option->value += precision;
      if(option->value < 0)
        option->value = option->value_count - 1;
      if(option->value >= option->value_count)
        option->value = 0;
      break;
  }
}
