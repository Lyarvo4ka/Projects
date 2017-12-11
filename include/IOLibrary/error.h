#pragma once
#include <system_error>

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
		void showMessage()
	};

	enum class device_error
	{
		open ,
		create,
		read,
		write
	};

	class DeviceErrorCategory :
		public std::error_category
	{
	public:
		virtual const char * name() const override
		{
			return "device error";
		}
		virtual std::string message(int ev) const override
		{
			switch (static_cast<device_error>(ev))
			{
			case device_error::open:
				return "Error open device";
			}

		}
	};
	//std::error_category
}