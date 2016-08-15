#pragma once

#include "IODevice.h"

/*
 * Structure of the super block
 */
namespace IO
{
struct ext2_super_block {
	int32_t	s_inodes_count;		/* Inodes count */
	int32_t	s_blocks_count;		/* Blocks count */
	int32_t	s_r_blocks_count;	/* Reserved blocks count */
	int32_t	s_free_blocks_count;	/* Free blocks count */
	int32_t	s_free_inodes_count;	/* Free inodes count */
	int32_t	s_first_data_block;	/* First Data Block */
	int32_t	s_log_block_size;	/* Block size */
	int32_t	s_log_frag_size;	/* Fragment size */
	int32_t	s_blocks_per_group;	/* # Blocks per group */
	int32_t	s_frags_per_group;	/* # Fragments per group */
	int32_t	s_inodes_per_group;	/* # Inodes per group */
	int32_t	s_mtime;		/* Mount time */
	int32_t	s_wtime;		/* Write time */
	int16_t	s_mnt_count;		/* Mount count */
	int16_t	s_max_mnt_count;	/* Maximal mount count */
	int16_t	s_magic;		/* Magic signature */
	int16_t	s_state;		/* File system state */
	int16_t	s_errors;		/* Behaviour when detecting errors */
	int16_t	s_minor_rev_level; 	/* minor revision level */
	int32_t	s_lastcheck;		/* time of last check */
	int32_t	s_checkinterval;	/* max. time between checks */
	int32_t	s_creator_os;		/* OS */
	int32_t	s_rev_level;		/* Revision level */
	int16_t	s_def_resuid;		/* Default uid for reserved blocks */
	int16_t	s_def_resgid;		/* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 * 
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	int32_t	s_first_ino; 		/* First non-reserved inode */
	int16_t   s_inode_size; 		/* size of inode structure */
	int16_t	s_block_group_nr; 	/* block group # of this superblock */
	int32_t	s_feature_compat; 	/* compatible feature set */
	int32_t	s_feature_incompat; 	/* incompatible feature set */
	int32_t	s_feature_ro_compat; 	/* readonly-compatible feature set */
	uint8_t	s_uuid[16];		/* 128-bit uuid for volume */
	char	s_volume_name[16]; 	/* volume name */
	char	s_last_mounted[64]; 	/* directory where last mounted */
	int32_t	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	uint8_t	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
	uint8_t	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
	uint16_t	s_padding1;
	/*
	 * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
	uint8_t	s_journal_uuid[16];	/* uuid of journal superblock */
	uint32_t	s_journal_inum;		/* inode number of journal file */
	uint32_t	s_journal_dev;		/* device number of journal file */
	uint32_t	s_last_orphan;		/* start of list of inodes to delete */
	uint32_t	s_hash_seed[4];		/* HTREE hash seed */
	uint8_t	s_def_hash_version;	/* Default hash version to use */
	uint8_t	s_reserved_char_pad;
	uint16_t	s_reserved_word_pad;
	int32_t	s_default_mount_opts;
 	int32_t	s_first_meta_bg; 	/* First metablock block group */
	uint32_t	s_reserved[190];	/* Padding to the end of the block */
};

const int default_linux_block = 4096;
const int superblock_offset = 1024;
const uint16_t EXT2_SUPER_MAGIC = 0xEF53;

struct ext2_struct_t
{
	uint32_t block_size;
	uint32_t inode_size;
};

struct HeaderInfo_t
{
	const uint8_t * header;
	const uint32_t header_size;
	path_string ext;
};

#include <map>
#include <utility>


	class ext2_raw
	{
	private:
		IODevice *device_;
		std::vector<HeaderInfo_t> headers_;
	public:
		ext2_raw(IODevice * device)
			: device_(device)
		{

		}
		void addHeaderInfo(const HeaderInfo_t & new_header)
		{
			headers_.push_back(new_header);
		}

		bool read_superblock(ext2_super_block * superblock, uint64_t offset)
		{
			if (!device_->isOpen())
			{
				device_->setPosition(offset);
				Buffer buffer(default_linux_block);
				if (device_->ReadData(buffer.data, buffer.data_size))
				{
					memcpy(superblock, buffer.data + superblock_offset, sizeof(ext2_super_block));
					return true;
				}
			}
			else
				wprintf_s(L"Error. Device wasn't open.\n");

			return true;
		}

		bool isSuperblock(ext2_super_block * pSuperblock)
		{
			if (pSuperblock)
			{
				if (pSuperblock->s_magic == EXT2_SUPER_MAGIC)
					return true;
			}
			return false;
		}

		bool isTable(uint8_t * data, uint32_t data_size , uint32_t max_blocks , bool &bFullTable )
		{
			if (!data)
				return false;

			uint32_t * pValue = (uint32_t *)data;
			uint32_t * pLast = (uint32_t *)(data + data_size);
			uint32_t NullPos = 0;
			bool bFoundNull = false;
			
			if (!isLessThanValue(pValue, pLast, max_blocks, NullPos))
				return false;

			if (NullPos == 0)
				return false;

			bFullTable = isFullTable(NullPos, data_size);
			if ( !bFullTable )
				if (!isOnlyNulls(pValue, pLast))
					return false;

			pValue = (uint32_t *)data;
			if (hasDuplicates(pValue, pValue + NullPos))
				return false;

			return true;
		}

		bool isFullTable(uint32_t null_pos, uint32_t block_size)
		{
			return null_pos == block_size;
		}

		bool isLessThanValue(uint32_t *pStart, uint32_t * pLast, uint32_t value , uint32_t & null_pos)
		{
			while (pStart != pLast)
			{
				if (*pStart == 0)
					return true;

				if (*pStart > value)
					return false;

				++null_pos;
				++pStart;
			}
			return true;

		}

		bool hasDuplicates(uint32_t *pStart, uint32_t * pLast)
		{
			std::map<uint32_t, uint32_t> mapValues;
			while(pStart != pLast)
			{
				auto findIter = mapValues.find(*pStart);
				if (findIter != mapValues.end())
					return true;

				mapValues.insert(std::make_pair(*pStart, *pStart));

				++pStart;
			}
			return false;
		}

		bool isOnlyNulls(uint32_t * pStart , uint32_t * pLast)
		{
			while (pStart != pLast)
			{
				if (*pStart != 0)
					return false;
				++pStart;
			}
			return true;
		}

		bool isHeader(const uint8_t * data)
		{
			//for ()
			return false;
		}

		void execute()
		{
			ext2_super_block super_block = { 0 };
			if (read_superblock(&super_block, 0))
				return;

			if (isSuperblock(&super_block))
			{
				wprintf_s(L"Error super_block\n");
				return;
			}
			uint64_t offset = 0;

			//while(offset )
		}
		


	};
};