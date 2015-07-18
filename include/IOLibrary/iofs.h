#ifndef IOFS_H
#define IOFS_H

#include "iolibrary_global.h"
#include <string>


namespace IO
{

	class AbstractNode
	{
	public:
		virtual AbstractNode * parent() const = 0;

	};

	class Folder
	{
	private:
		std::string name_;
		AbstractNode * parent_;
	public:
		Folder(const std::string & folder_name)
			: name_(folder_name)
		{

		}
		std::string name() const{
			return name_;
		}
		void set_parent(AbstractNode * parent)
		{
			parent_ = parent;
		}
	};

	class File
	{
	private:
		std::string name_;
	public:
		File(const std::string & file_name)
			:name_(file_name)
		{

		}
	};

}
#endif
