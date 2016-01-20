#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>
#include <string>
#include <stdint.h>

#define SIZEOF_ARRAY( a ) (sizeof( a ) / sizeof( a[ 0 ] ))

//typedef unsigned char		uint8_t;
//typedef unsigned long		uint32_t;
//typedef unsigned long long  uint64_t;

const uint64_t ERROR_RESULT = _UI64_MAX;


#include <array>
#include <vector>

namespace MLVKeywords
{

	static const char *mlv_array[] =	{ "MLVI", "VIDF", "AUDF", "RAWI", "WAVI", "EXPO", "LENS", "RTCI", 
										  "IDNT", "XREF", "INFO", "DISO", "NULL", "ELVL", "WBAL", "STYL", 
										  "MARK", "SUBC", "SUBI", "COLP", "DARK", "VIGN", "VERS", "DEBG" };
	const int mlv_array_size = SIZEOF_ARRAY(mlv_array);
};

namespace QTKeyword
{
	static const char * qt_array[] = { "ftyp", "moov", "mdat", "free", "skip", "wide", "pnot", "prfl", 
									   "mvhd", "clip", "trak", "udta", "ctab", "cmov", "rmra" };
	const int qt_array_size = SIZEOF_ARRAY(qt_array);
	//const int 
}

namespace Signatures
{

	const BYTE qt_header[] =  { 0x00 , 0x00 , 0x00 , 0x18 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x20 , 0x07 , 0x09 , 0x00 };
	const BYTE qt_header2[] = { 0x00 , 0x00 , 0x00 , 0x20 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x20 , 0x05 , 0x03 , 0x00 };
	const BYTE qt_header3[] = { 0x00 , 0x00 , 0x00 , 0x14 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x00 , 0x00 , 0x00 , 0x00 };
	const BYTE qt_header4[] = { 0x00 , 0x00 , 0x00 , 0x20 , 0x66 , 0x74 , 0x79 , 0x70 , 0x61 , 0x76 , 0x63 , 0x31 , 0x00 , 0x00 , 0x00 , 0x00 };
	const BYTE qt_header5[] = { 0x00 , 0x00 , 0x00 , 0x1C , 0x66 , 0x74 , 0x79 , 0x70 , 0x6D , 0x70 , 0x34 , 0x32 , 0x00 , 0x00 , 0x00 , 0x01 };
	const BYTE qt_header_def[] = { 0x00 , 0x00 , 0x00 , 0x20 , 0x66 , 0x74 , 0x79 , 0x70 };

	const BYTE qt_header_hts[] = { 0x00 , 0x00 , 0x00 , 0x18 , 0x66 , 0x74 , 0x79 , 0x70 , 0x69 , 0x73 , 0x6F , 0x6D , 0x00 , 0x00 , 0x00 , 0x00 };
	const int qt_header_size = SIZEOF_ARRAY( qt_header );
	const std::string moov = "mdat";
	const BYTE mdat[] = { 0x6D , 0x64 , 0x61 , 0x74 };
	const int mdat_size = SIZEOF_ARRAY( mdat );
	const BYTE dvr_header[] = { 0x22 , 0x00 , 0x00 , 0x00 , 0x03 , 0x00 , 0x00 , 0x00 , 0x07 , 0x02 , 0x03 , 0x16 , 0x02 , 0x01 , 0x14 , 0x90 };
	const int dvr_header_size  = SIZEOF_ARRAY( dvr_header );
	const BYTE mxf_header[] = { 0x06 , 0x0E , 0x2B , 0x34 , 0x02 , 0x05 , 0x01 , 0x01 , 0x0D , 0x01 , 0x02 , 0x01 , 0x01 , 0x02 , 0x04 , 0x00};
	const int mxf_header_size = SIZEOF_ARRAY( mxf_header );
	const BYTE mxf_footer[] = { 0x06 , 0x0E , 0x2B , 0x34 , 0x02 , 0x05 , 0x01 , 0x01 , 0x0D , 0x01 , 0x02 , 0x01 , 0x01 , 0x04 , 0x04 , 0x00 };
	const int mxf_footer_size = SIZEOF_ARRAY( mxf_header );

	const BYTE at_t_header[] = {0x41 , 0x54 , 0x26 , 0x54 , 0x46 , 0x4F , 0x52 , 0x4D};
	const int at_t_header_size = SIZEOF_ARRAY( at_t_header );
	const BYTE djvu_header[] = {0x44 , 0x4A , 0x56 , 0x4D , 0x44 , 0x49 , 0x52 , 0x4D};
	const int djvu_header_size = SIZEOF_ARRAY( djvu_header );

	const BYTE r3d_header[] = { 0x00 , 0x00 , 0x03 , 0x72 , 0x52 , 0x45 , 0x44 , 0x32 };
	const int r3d_header_size = SIZEOF_ARRAY( r3d_header);
	const BYTE r3d_footer[] = { 0x00 , 0x00 , 0x03 , 0x92 , 0x52 , 0x45 , 0x4F };
	const int r3d_footer_size = SIZEOF_ARRAY( r3d_footer);

	const BYTE mts_header[] = { 0x47, 0x40, 0x00, 0x10, 0x00, 0x00, 0xB0, 0x11, 0x00, 0x00, 0xC1, 0x00 };
	const int mts_header_size = SIZEOF_ARRAY(mts_header);
	const int mts_header_offset = 4;

	const BYTE mts_header2[] = { 0x47, 0x40, 0x00, 0x10, 0x00, 0x00, 0xB0, 0x11, 0x00, 0x01, 0xC1, 0x00 };


	const BYTE bad_sector_header[] = { 0x62, 0x61, 0x64, 0x20, 0x73, 0x65, 0x63, 0x74, 0x6F, 0x72 };

	const BYTE marker_0x27[] = { 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27 };
	const int marker_0x27_size = SIZEOF_ARRAY(marker_0x27);


};

const int SECTOR_SIZE = 512;
const int default_sector_size = 512;
const int defalut_number_sectors = 128;
const int default_block_size = defalut_number_sectors * default_sector_size;
const int SECTOR_COUNT = 64;
const int BLOCK_SIZE = SECTOR_SIZE * SECTOR_COUNT;

namespace BS
{
const int KB = 1024;
const int MB = KB*KB;
const int GB = MB*KB;
};

#endif