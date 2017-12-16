#pragma once
#include <system_error>
#include <windows.h>

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
		void showMessage(DWORD error_code , const std::wstring & sourceOfError)
		{
			Error error;
			std::wstring error_string = L"Error: ";
			error.getMessage(error.last());
			//wprintf(messageText.c_str());
			wprintf(L"\n");
		}
	};

	enum class device_error
	{
		openRead_err = 1,
		openWrite_err,
		create_err,
		read_err,
		write_err

	};

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
	//		switch (static_cast<device_error>(ev))
	//		{
	//		case device_error::openRead_err:
	//			return "Error open device";
	//		}

	//	}
	//};
	//std::error_category
}