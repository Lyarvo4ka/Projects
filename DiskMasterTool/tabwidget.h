#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QVector>

class DMItemIdex;

class BaseTabWidget;
class MainTaskWidget;
class CopyTabWidget;


#include "DiskMasterLib\dm_device.h"

class TabWidget : public QTabWidget
{
	Q_OBJECT

public:
	TabWidget(QWidget *parent);
	~TabWidget();


	void addMainTask(MainTaskWidget * mainWidget);
	void addToTab(BaseTabWidget * baseTabWidget);

	void hideTabBar();
	void appearTabBar();
	void UpdateTab();
	void RemoveTabs();
	
	BaseTabWidget * findWidget(const DMItemIdex * dm_index , int itemStatus );
	void UpdateAllView(const DMItemIdex * );
	void showWidget(const DMItemIdex * dm_index , int itemStatus);
	void removeWidgets( const DMItemIdex * );

	public slots:
		void ShowTabWidget(const DMItemIdex * dm_index, int itemStatus);
		void task_load( const DMItemIdex * , const QString & );
		void RemoveTab( QWidget * widget );
		void RemoveTabs(const DMItemIdex * dm_index);
		void CloseTabWidget(int iTabNumber);
		void CloseTab( QWidget *);
		void TabChanged( int nIndex );
		void startTask() ;
		void cancelTask() ;
		void Preferences_clicked();
		void ChangeItemStatus( DWORD id , DWORD state, DWORD status );
		void ChangeProgress( DWORD id , int position );


	signals:
		void setEnabledTasks( bool );
		void setEnabledStart( bool );
		void setEnabledCancel( bool );	
protected:
	void tabRemoved ( int index ) override;
private:
	MainTaskWidget * MainWidget_;
	QVector<QWidget *> widgetHolder_;
};


#endif // TABWIDGET_H
