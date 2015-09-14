#ifndef IOFS_H
#define IOFS_H

#include "iolibrary_global.h"
#include <string>
#include <memory>
#include <map>


namespace IO
{

	class Node;
	typedef std::shared_ptr<Node> AbstractNode;

	class Directory;
	typedef std::shared_ptr<Directory> DirectoryNode;

	class File;
	typedef std::shared_ptr<File> FileNode;


	typedef std::map<std::string, AbstractNode> Nodes;

	class Node
	{
	public:
		virtual std::string name() const = 0;
		virtual Directory * parent() const = 0;


	};

	class Directory
		: public Node
	{
	private:
		std::string name_;
		Directory * parent_;
		Nodes nodes_;
	public:
		Directory(const std::string & folder_name)
			: name_(folder_name)
			, parent_(nullptr)
		{

		}
		std::string name() const override
		{
			return name_;
		}
		Directory * parent() const override
		{
			return parent_;
		}
		void set_parent(Directory * parent)
		{
			parent_ = parent;
		}
		void add_folder(Nodes new_folder)
		{

		}
		void add_file(const std::string & file_name)
		{

		}
	};

	class File
		: public Node
	{
	private:
		std::string name_;
		Directory* parent_;
	public:
		File(const std::string & file_name)
			: name_(file_name)
			, parent_(nullptr)
		{

		}
		std::string name() const override
		{
			return name_;
		}
		void set_parent(Directory * parent)
		{
			parent_ = parent;
		}
		Directory * parent() const
		{
			return parent_;
		}
	};

}
#endif
