#ifndef INC_05_GUESS_NUMBER_FILE_TO_STRING_H
#define INC_05_GUESS_NUMBER_FILE_TO_STRING_H

#include "utils/terminal.h"
#include <fstream>
#include <iostream>
#include <sstream>


inline std::string FileToString(const std::string& filename)
{
  std::stringstream ss;
  std::ifstream     file;

  try
  {
    file.open(filename, std::ios::in);

    if (!file.fail())
    {
      ss << file.rdbuf();
    }

    file.close();
  }
  catch (std::exception ex)
  {
    Terminal::ReportErr("Error reading file: ");
    Terminal::ReportErr(ex.what());
  }

  return ss.str();
}

#endif //INC_05_GUESS_NUMBER_FILE_TO_STRING_H
