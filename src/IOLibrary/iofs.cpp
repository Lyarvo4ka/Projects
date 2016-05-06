#include "iofs.h"
namespace IO
{
	DirectoryNode * Node::getParent() const
	{
		return parent_;
	}

	path_string Node::getFullPath()
	{
		path_string full_path = name_;
		auto  pParent = parent_;
		while (pParent)
		{
			full_path.insert(0, pParent->getName() + back_slash);
			pParent = pParent->getParent();
		}
		return full_path;
	}

}