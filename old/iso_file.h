#ifndef _ISO_FILE_H
#define _ISO_FILE_H

#include "iso.h"

namespace FileFlag
{
  enum
  {
    Hidden = 1,       //  Hidden from the user
    Directory = 2,    //  Directory
    Associated = 4,   //  Normal file
    Extended = 8,     //  Extended information
    Permission = 16,  //  
    Incomplete = 32   //  Incomplete listing
  };
};

struct ISOFile
{

};

#endif
