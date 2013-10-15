#ifndef CONFIGDATADEF_H
#define CONFIGDATADEF_H

#define MAX_OPTION_VALUES 32

namespace ConfigData
{
  enum DataType
  {
    INT,
    ENUM
  };
  
  typedef struct _ConfigOption
  {
    char *name;
    DataType type;
    int value; //Actual value for INT, position in value array for ENUM
    char *values[MAX_OPTION_VALUES]; //For INT values[0] is min values[1] is max, for ENUM values[n] is string for Nth option
    int value_count; //Number of options, -1 for INT (>0 can be used to set precision), number of options for ENUM
  } ConfigOption;
};

#endif
