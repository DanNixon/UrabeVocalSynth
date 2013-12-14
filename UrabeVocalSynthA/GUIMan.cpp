#include "GUIMan.h"

extern char *VERSION_STRING;
using namespace GUIMan;

GUIManager::GUIManager(GLCDManager *glcd_manager, JpSynthManager *jp_synth_manager, SynthManager *synth_manager)
{
  this->current_window = MAIN;
  this->mode = MENU;
  this->glcd_man = glcd_manager;
  this->jps_man = jp_synth_manager;
  this->synth_man = synth_manager;
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
      this->current_option = 0;
      this->glcd_man->draw_title_large("UrabeVocalSynth");
      this->glcd_man->draw_buttons_lower("Synth", "Vocal");
      this->glcd_man->u8g.setFont(u8g_font_helvR08);
      this->glcd_man->u8g.drawStr(0, 24, VERSION_STRING);
      this->glcd_man->u8g.drawStr(0, 34, "dan-nixon.com");
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
      glcd_man->draw_option(this->synth_man->options[this->current_option]);
      break;
    case JP_SETTINGS:
      this->glcd_man->draw_title("Vocal S");
      this->glcd_man->draw_buttons_upper("Back", "");
      glcd_man->draw_option(this->jps_man->options[this->current_option]);
      break;
    case SYNTH_RUN:
      this->mode = WAVEFORM;
      this->glcd_man->draw_title("Synth");
      this->glcd_man->draw_buttons_upper("Back", "");
      this->glcd_man->draw_buttons_lower("Panic", "");
      this->glcd_man->u8g.setFont(u8g_font_5x7);
      //Print some general info
      this->glcd_man->u8g.drawStr(0, 22, this->synth_man->get_waveform_name());
      char vol_buf[10];
      sprintf(vol_buf, "Vol: %d", this->synth_man->get_volume());
      this->glcd_man->u8g.drawStr(0, 30, vol_buf);
      char dist_buf[10];
      sprintf(dist_buf, "Dist: %d", this->synth_man->get_freq_distortion());
      this->glcd_man->u8g.drawStr(0, 38, dist_buf);
      char poly_buf[10];
      sprintf(poly_buf, "Poly: %d", this->synth_man->get_notes_on());
      this->glcd_man->u8g.drawStr(0, 46, poly_buf);
      //Print the envelope stage labels
      this->glcd_man->u8g.drawStr(55, 30, "A");
      this->glcd_man->u8g.drawStr(55, 38, "D");
      this->glcd_man->u8g.drawStr(55, 46, "R");
      //Print envelope durations
      this->glcd_man->u8g.drawStr(65, 22, "Dur.");
      this->glcd_man->u8g.drawStr(65, 30, this->synth_man->get_attack_duration());
      this->glcd_man->u8g.drawStr(65, 38, this->synth_man->get_decay_duration());
      this->glcd_man->u8g.drawStr(65, 46, this->synth_man->get_release_duration());
      //print envelope amplitudes
      this->glcd_man->u8g.drawStr(95, 22, "Amp.");
      char atk_buf[10];
      sprintf(atk_buf, "%d", this->synth_man->get_attack_amp());
      this->glcd_man->u8g.drawStr(95, 30, atk_buf);
      char dec_buf[10];
      sprintf(dec_buf, "%d", this->synth_man->get_decay_amp());
      this->glcd_man->u8g.drawStr(95, 38, dec_buf);
      char rel_buf[10];
      sprintf(rel_buf, "%d", this->synth_man->get_release_amp());
      this->glcd_man->u8g.drawStr(95, 46, rel_buf);
      break;
    case JP_RUN:
      this->mode = VOCAL;
      this->glcd_man->draw_title("Vocal");
      this->glcd_man->draw_buttons_upper("Back", "");
      this->glcd_man->draw_buttons_lower("Panic", "Clr Buf");
      this->glcd_man->u8g.setFont(u8g_font_5x7);
      //Print kana buffer pointer values
      char read_counter_buf[10];
      char write_counter_buf[10];
      sprintf(read_counter_buf, "R:%d", this->jps_man->get_buffer_position());
      sprintf(write_counter_buf, "W:%d", this->jps_man->get_buffer_add_position());
      this->glcd_man->u8g.drawStr(88, 22, read_counter_buf);
      this->glcd_man->u8g.drawStr(88, 30, write_counter_buf);
      //Print kana buffer
      KanaTable::Kana disp_kana[9];
      int offset = 0;
      if(this->jps_man->get_notes_on())
        offset = -1;
      for(int i=0; i<9; i++)
      {
        int position = i + this->jps_man->get_buffer_position() + offset;
        if(position >= KANA_BUFFER_SIZE)
          position = position % KANA_BUFFER_SIZE;
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
          this->synth_man->update_config();
          break;
        case _UP:
          this->change_option(&this->synth_man->options[this->current_option], 1);
          break;
        case _DOWN:
          this->change_option(&this->synth_man->options[this->current_option], -1);
          break;
        case _LEFT:
          this->current_option--;
          if(this->current_option < 0)
            this->current_option = this->synth_man->get_option_count() - 1;
          break;
        case _RIGHT:
          this->current_option++;
          if(this->current_option >= this->synth_man->get_option_count())
            this->current_option = 0;
          break;
      }
      break;
    case JP_SETTINGS:
      switch(b_val)
      {
        case _F1: //Back
          this->current_window = JP_MENU;
          this->jps_man->update_config();
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
          this->synth_man->panic();
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
          this->jps_man->panic();
          break;
        case _F4: //Clear Buffer
          this->jps_man->kana_buffer_clear();
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
