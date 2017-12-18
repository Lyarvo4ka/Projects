#pragma once
#include <system_error>
#include <windows.h>
#include "constants.h"

namespace IO
{

	template <class S>
	class SingletonHolder
		/// This is a helper template class for managing
		/// singleton objects allocated on the heap.
		/// The class ensures proper deletion (including
		/// calling of the destructor) of singleton objects
		/// when the application that created them terminates.
	{
	public:
		SingletonHolder() :
			_pS(0)
			/// Creates the SingletonHolder.
		{
		}

		~SingletonHolder()
			/// Destroys the SingletonHolder and the singleton
			/// object that it holds.
		{
			delete _pS;
		}

		S* get()
			/// Returns a pointer to the singleton object
			/// hold by the SingletonHolder. The first call
			/// to get will create the singleton.
		{
			//FastMutex::ScopedLock lock(_m);
			if (!_pS) _pS = new S;
			return _pS;
		}

	private:
		S* _pS;
		//FastMutex _m;
	};

	enum class ErrorLevel
	{
		none, // (turns off logging)
 	    fatal,
	    critical,
	    error,
	    warning,
	    notice,
	    information,
	    debug,
	    trace
	};
	class Error 
	{
	public:
		DWORD last() const
		{
			return ::GetLastError();
		}
		std::wstring Error::getMessage(DWORD errorCode)
		{
			std::wstring errMsg;
			DWORD dwFlg = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;

			LPWSTR lpMsgBuf = 0;
			if (FormatMessageW(dwFlg, 0, errorCode, 0, (LPWSTR)& lpMsgBuf, 0, NULL))
				errMsg = lpMsgBuf;

//				UnicodeConverter::toUTF8(lpMsgBuf, errMsg);
//#else
//			LPTSTR lpMsgBuf = 0;
//			if (FormatMessageA(dwFlg, 0, errorCode, 0, (LPTSTR)& lpMsgBuf, 0, NULL))
//				errMsg = lpMsgBuf;
//#endif
			LocalFree(lpMsgBuf);
			return errMsg;
		}
	};

	class ErrorHandler
	{
	private: 
		static ErrorHandler * error_handler_;
	protected:
		static ErrorHandler* defaultHandler();
	public:
		static ErrorHandler * get()
		{
			return error_handler_;
		}
		void showMessage(const std::wstring & messageText)
		{
			wprintf(messageText.c_str());
			wprintf(L"\n");
		}
		//void showMessage(DWORD error_code , const std::wstring error_type, const std::wstring & sourceOfError)
		//{
		//	std::wstring output_text;

		//	if (!error_type.empty())
		//	{
		//		output_text += error_type;
		//		output_text += L" ";
		//	}

		//	if (!sourceOfError.empty())
		//	{
		//		output_text += sourceOfError;
		//		output_text += L" ";

		//	}

		//	Error error;
		//	auto lastError_string = error.getMessage(error_code);
		//	if (!lastError_string.empty())
		//		output_text += lastError_string;

		//	wprintf(L"%s (code #%d)\n", lastError_string , error_code);
		//}
		//void showMessage(std::error_condition err_cond, const std::wstring & sourceOfError)
		//{
		//	auto err_msg = err_cond.message();
		//	std::wstring output_text(err_msg.begin(), err_msg.end());

		//	if (!sourceOfError.empty())
		//	{
		//		output_text += sourceOfError;
		//		output_text += L" ";

		//	}

		//	Error error;
		//	auto lastError_string = error.getMessage(error.last());
		//		if (!lastError_string.empty())
		//		output_text += lastError_string;

		//	wprintf(L"%s (code #%d)\n", lastError_string, error.last());
		//}

	};



	//inline std::wstring ioDeviceErrorToString(const iodevice_error iodev_error)
	//{
	//	switch (iodev_error)
	//	{
	//	case iodevice_error::openRead_err:
	//		return L"open read";
	//	case iodevice_error::openWrite_err:
	//		return L"open write";
	//	case iodevice_error::create_err:
	//		return L"create";
	//	case iodevice_error::read_err:
	//		return L"read";
	//	case iodevice_error::write_err:
	//		return L"write";

	//	}
	//	return L"Unknown error";

	//}

	enum class iodevice_error
	{
		openRead_err = 1,
		openWrite_err,
		create_err,
		read_err,
		write_err,
		unknown_err

	};

	inline iodevice_error openModeToIOError(OpenMode open_mode)
	{
		switch (open_mode)
		{
		case IO::OpenMode::OpenRead:
			return iodevice_error::openRead_err;
		case IO::OpenMode::OpenWrite:
			return iodevice_error::openWrite_err;
		case IO::OpenMode::Create:
			return iodevice_error::create_err;
		default:
			return iodevice_error::unknown_err;
		}

	}

	//class DeviceErrorCategory :
	//	public std::error_category
	//{
	//public:
	//	virtual const char * name() const override
	//	{
	//		return "device error";
	//	}
	//	virtual std::string message(int ev) const override
	//	{
	//		switch (static_cast<iodevice_error>(ev))
	//		{
	//		case iodevice_error::openRead_err:
	//			return "Error open read";
	//		case iodevice_error::openWrite_err:
	//			return "Error open write";
	//		case iodevice_error::create_err:
	//			return "Error create";
	//		case iodevice_error::read_err:
	//			return "Error read";
	//		case iodevice_error::write_err:
	//			return "Error write";
	//		default:
	//			return "(unrecognized error)";

	//		}

	//	}
	//};

	//const std::error_category & device_error_category()
	//{
	//	static DeviceErrorCategory instance;
	//	return instance;
	//}

	//std::error_condition make_error_condition(iodevice_error e)
	//{
	//	return std::error_condition
	//	(
	//		static_cast<int>(e),
	//		device_error_category()
	//	);
	//}
	//std::error_category
}