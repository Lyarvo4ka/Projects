#pragma once

#include "resource.h"



//#include "IOLibrary/iofunctions.h"
#include "IOLibrary/Finder.h"
#include <iostream>


void identify_files(const std::string & source_dir, const std::string & target_dir);
bool identify_pdf(const std::string & file_name, std::string & new_filename, int counter);
bool open_pdf_file(const std::string & file_name);
void verify_pdf_files(const IO::path_string & folder);

