#pragma once

#include "jpeglib.h"
#include "AbstractRaw.h"
#include <exception>
#include <Wingdi.h>

namespace IO
{
	class my_exception
		: public std::exception
	{
	public:
		my_exception(std::string && expection_text) noexcept
			: text_(std::move(expection_text))
		{}
		my_exception(const std::string & expection_text) noexcept
			: text_(expection_text)
		{}
		~my_exception() {}
	private:
		std::string text_;
	};

	class ImageData
	{
	private:
		int width_ = 0;
		int height_= 0;
		int numComponets_ = 0;
		IO::DataArray::Ptr pixelsArray_;
		int scanline_count_ = 0;
	public:
		ImageData(int width, int height, int output_components)
			: width_(width)
			, height_(height)
			, numComponets_(output_components)
		{
			int pixels_size = width * height * output_components;
			pixelsArray_ = std::move(IO::makeDataArray(pixels_size));
		}
		ImageData()	{}

		IO::ByteArray getData()
		{
			return pixelsArray_->data();
		}

		uint32_t getSize() const
		{
			return pixelsArray_->size();
		}
		void setScanlineCount(const int scanline_count)
		{
			scanline_count_ = scanline_count;
		}
		int getScanlineCount() const
		{
			return scanline_count_;
		}
		int getWidth() const
		{
			return width_;
		}
		int getHeight() const
		{
			return height_;
		}
		int getOutputComponents() const
		{
			return numComponets_;
		}

	};

	double calcPercentages(int val, int max)
	{
		if (max == 0)
			return 0.0;
		double percent = (double)val / (double)max;
		return percent * 100.00;
	}

	void jpegErrorExit(j_common_ptr cinfo)
	{
		char jpegLastErrorMsg[JMSG_LENGTH_MAX];
		/* Create the message */
		(*(cinfo->err->format_message)) (cinfo, jpegLastErrorMsg);

		/* Jump to the setjmp point */
		//throw std::runtime_error(jpegLastErrorMsg); // or your preffered exception ...
		throw my_exception(jpegLastErrorMsg);
	}

	bool isVaidMSGCode(const int msg_code)
	{
		if (msg_code >= 73/*JMSG_COPYRIGHT*/
			&& msg_code <= 113/*JTRC_XMS_OPEN*/)
			return true;
		return false;
	}
	void jpegOutputMessage(j_common_ptr cinfo)
	{
		char jpegLastErrorMsg[JMSG_LENGTH_MAX];
		/* Create the message */
		(*(cinfo->err->format_message)) (cinfo, jpegLastErrorMsg);
		printf("%s (error_code [%d])\n", jpegLastErrorMsg, cinfo->err->msg_code);
		//printf("Error code [%d]\n", cinfo->err->msg_code);
		if (!isVaidMSGCode(cinfo->err->msg_code))
			printf("Not Valid error code");


		/* Jump to the setjmp point */
		//if (!isVaidMSGCode(cinfo->err->msg_code))
		//	throw std::runtime_error(jpegLastErrorMsg); // or your preffered exception ...
	}

	void saveBMP_file(const IO::path_string & path , const ImageData & image_data)
	{
		IO::File bmp_file(path);
		bmp_file.Open(IO::OpenMode::Create);

		
		ImageData img_new(image_data.getWidth(), image_data.getHeight(), image_data.getOutputComponents());
		for (auto i = 0; i < image_data.getSize(); i = i + image_data.getOutputComponents())
		{
			for (auto j = 0; j < image_data.getOutputComponents(); ++j)
				img_new.getData()[i + j] = image_data.getData()[image_data.getSize() - 1 - i - j];
		}


		BITMAPINFOHEADER bfh = BITMAPINFOHEADER();
		//BITMAPINFO bi;
		bfh.biSize = sizeof(BITMAPINFOHEADER);
		bfh.biHeight = cinfo.output_height;
		bfh.biWidth = cinfo.output_width;
		bfh.biBitCount = 24;
		bfh.biPlanes = 1;
		bfh.biCompression = BI_RGB;

		const char BM_TEXT[] = "BM";

		BITMAPFILEHEADER bm_header = BITMAPFILEHEADER();
		memcpy(&bm_header.bfType, BM_TEXT, 2);
		bm_header.bfSize = sizeof(BITMAPFILEHEADER) + bfh.biSize + image_data.getSize();


		auto bytes_written = bmp_file.WriteData((ByteArray)&bm_header, sizeof(BITMAPFILEHEADER));
		bytes_written += bmp_file.WriteData((ByteArray)&bfh, bfh.biSize);
		bytes_written += bmp_file.WriteData(img_new.getData(), img_new.getSize());
		//bytes_written += bmp_file.WriteData(image_data.getData(), image_data.getSize());

		bmp_file.Close();


	}

	class JpegDecoder
	{
	private:

		jpeg_error_mgr err = jpeg_error_mgr();
		jpeg_decompress_struct cinfo = jpeg_decompress_struct();
	public:
		//JpegDecoder(const IO::path_string & jpeg_filename)
		//	: jpeg_filename_(jpeg_filename)
		//{

		//}
		void Init()
		{
			ZeroMemory(&err, sizeof(jpeg_error_mgr));
			ZeroMemory(&cinfo, sizeof(jpeg_decompress_struct));
		}
		void createDecompressor()
		{
			Init();
			jpeg_create_decompress(&cinfo);
			cinfo.err = jpeg_std_error(&err);
			cinfo.do_fancy_upsampling = FALSE;
			err.error_exit = jpegErrorExit;
			err.output_message = jpegOutputMessage;
			//err.trace_level = 1;
		}
		void destroyDecompressor()
		{
			jpeg_finish_decompress(&cinfo);
			jpeg_destroy_decompress(&cinfo);
		}

		IO::DataArray ReadJpegFile(const IO::path_string & jpeg_filename)
		{
			IO::File jpg_file(jpeg_filename);
			if (!jpg_file.Open(IO::OpenMode::OpenRead))
				return IO::DataArray(0);

			IO::DataArray data_array(jpg_file.Size());
			if (data_array.size() == 0)
				return data_array;

			auto bytes_read = jpg_file.ReadData(data_array);
			if (bytes_read != data_array.size())
				return IO::DataArray(0);

			return data_array;
		}

		ImageData decompress(const IO::path_string & jpeg_filename)
		{
			createDecompressor();

			auto data_array = ReadJpegFile(jpeg_filename);
			if (data_array.size() == 0)
				return ImageData();

			/* set source buffer */
			jpeg_mem_src(&cinfo, data_array.data(), data_array.size());

			/* read jpeg header */
			jpeg_read_header(&cinfo, 1);


			auto bRes = jpeg_start_decompress(&cinfo);
			if (err.num_warnings > 0)
			{
				return ImageData();
			}


			JSAMPROW output_data;
			auto scanline_len = cinfo.output_width * cinfo.output_components;

			auto scanline_count = 0;
			ImageData image_data(cinfo.output_width, cinfo.output_height, cinfo.output_components);



			while (cinfo.output_scanline < cinfo.output_height)
			{
				output_data = (image_data.getData() + (scanline_count * scanline_len));
				jpeg_read_scanlines(&cinfo, &output_data, 1);

				if (err.num_warnings > 0)
					break;

				if (!isVaidMSGCode(err.msg_code))
				{
					//int k = cinfo.next_scanline;
					//cinfo.output_scanline = cinfo.output_height;
					break;
				}

				scanline_count++;
			}

			cinfo.output_scanline = cinfo.output_height;
			destroyDecompressor();
			image_data.setScanlineCount(scanline_count);

			//saveBMP_file(L"d:\\Photo\\jpg_test\\bad_file\\bitmap.bmp" , image_data);

 			return image_data;
		}

	};
}