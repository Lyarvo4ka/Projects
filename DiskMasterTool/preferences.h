
#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QObject>

class Preferences : public QObject
{
	Q_OBJECT

public:
	Preferences(QObject *parent);
	~Preferences();

private:
	
};

//class PreferenceManager
//{
//	typedef std::unique_ptr< Preferences > PreferencesPtr;
//public: 
//	static PreferenceManager * getManager() 
//	{
//		if ( !instance_ )
//			instance_ = new PreferenceManager;
//		return instance_;
//	}
//
//
//protected:
//	PreferenceManager()
//	{
//
//	}
//	PreferenceManager( const PreferenceManager & );
//	~PreferenceManager()
//	{
//
//	}
//
//	void operator = ( const PreferenceManager & );
//
//private:
//	static PreferenceManager * instance_;
//	std::vector < PreferencesPtr> preferences_;
//}

#endif // PREFERENCES_H
