#pragma once

#include "resource.h"



#include "IOLibrary/iofunctions.h"
#include "IOLibrary/FileFinder.h"
#include <iostream>




//void identify_files(const std::string & source_dir, const std::string & target_dir);

void identify_files(const std::string & source_dir, const std::string & target_dir);
bool identify_office2003(const std::string & file_name, std::string & new_filename, int counter);
bool identify_pdf(const std::string & file_name, std::string & new_filename, int counter);

