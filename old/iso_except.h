#ifndef _ISO_EXCEPTION_H
#define _ISO_EXCEPTION_H

#include <exception>

class ISOOpenException : public std::exception
{
public:
  virtual const char * what() const throw()
  {
    return "Could not open image.";
  }
};

#endif
