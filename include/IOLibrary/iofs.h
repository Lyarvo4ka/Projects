#ifndef IOFS_H
#define IOFS_H

#include "iolibrary_global.h"
#include "constants.h"
#include <memory>
#include <list>

#include <boost/filesystem.hpp>

#pragma warning(disable:4251)

namespace IO
{

	class DirectoryNode;
	//using ListDirectories = std::list<DirectoryNode::Ptr>;
	//using ListFiles = std::list<DirectoryNode::Ptr>;

	class IOLIBRARY_EXPORT Node
	{
	private:
		DirectoryNode * parent_;
		path_string name_;
	public:
		Node(const path_string &name, DirectoryNode * parent = nullptr)
			:parent_(parent)
			,name_(name)
		{
		}
		~Node()
		{
			parent_ = nullptr;
		}

		void setName(const path_string &name)
		{
			this->name_ = name;
		}
		path_string getName() const
		{
			return name_;
		}

		void setParent(DirectoryNode * parent)
		{
			this->parent_ = parent;
		}

		DirectoryNode * getParent() const;
		path_string getFullPath();
	};

	class FileNode
		: public Node
	{
	public:
		typedef std::shared_ptr<FileNode> Ptr;
		static FileNode::Ptr CreateFileNode(const path_string & file_name)
		{
			return std::make_shared<FileNode>(FileNode(file_name));
		}
	private:

	public:
		FileNode(const path_string & file_name)
			: Node(file_name)
		{

		}

		path_string getExtension() const
		{
			boost::filesystem::path file_path(this->getName());
			return file_path.extension().generic_wstring();
		}
	};

	class DirectoryNode
		: public Node
	{
	public:
		typedef std::shared_ptr<DirectoryNode> Ptr;
		static DirectoryNode::Ptr CreateDirectoryNode(const path_string & folder_name)
		{
			return std::make_shared<DirectoryNode>(DirectoryNode(folder_name));
		}
	private:
		std::list<DirectoryNode::Ptr> directories_;
		std::list<FileNode::Ptr> files_;
	public:
		DirectoryNode(const path_string & directory_name)
			: Node(directory_name)
		{

		}

		void AddDirectory(const path_string & directory_name)
		{
			auto new_folder = CreateDirectoryNode(directory_name);
			new_folder->setParent(this);
			directories_.push_back(new_folder);
		}

		// tmp function

		void AddDirectory(DirectoryNode::Ptr directory_node)
		{
			directory_node->setParent(this);
			directories_.push_back(directory_node);
		}

		void AddFile(const path_string & file_name)
		{
			auto new_file = FileNode::CreateFileNode(file_name);
			new_file->setParent(this);
			files_.push_back(new_file);
		}

		//FileNode::Ptr getFirstFile() const
		//{
		//	auto fileIter = files_.begin();
		//	if (fileIter != files_.end())
		//		return *fileIter;

		//	return nullptr;
		//}
		//FileNode::Ptr getNextFile() const 
		//{

		//}

		//bool hasNext() const
		//{

		//}
	};





}
#endif
