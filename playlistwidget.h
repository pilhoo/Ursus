/***************************************************************************
 *   Copyright (C) 2008 by Michał Pilch  <mpilhoo@gmail.com>               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef URSUS_PLAYLISTWIDGET_H
#define URSUS_PLAYLISTWIDGET_H
#include <QTreeWidget>
#include <QStringList>
#include <KConfigGroup>
#include <KIO/NetAccess>
#include <KMessageBox>
#include <KSaveFile>
#include <QTextStream>
#include <QTextCodec>
#include <Phonon/MediaSource>
#include <Phonon/MediaObject>
#include <KIcon>
#include <QTime>
#include <QMultiMap>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QHeaderView>
#include <QMenu>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QScrollBar>
#include <QList>
#include "playlistitem.h"
#include "metainforesolver.h"
#include "playlisttabs.h"
#include "playlistdroppointer.h"

class PlayListTabs;
class DropPointer;

class PlayListWidget : public QTreeWidget{
	friend class DropPointer;
	Q_OBJECT
public:
	PlayListWidget(QWidget *parent=0);
	~PlayListWidget();

	PlayListItem* itemAbove(const QTreeWidgetItem *item);
	PlayListItem* itemBelow(const QTreeWidgetItem *item);
	PlayListItem* itemAt(int index);
	PlayListItem* itemAt(const QPoint &pos);

	QString name();
	void setName(QString name);
	void load();
	void save();
	void refreshConfig();
	void resetFirstShow();
	inline unsigned int visibleWidth();
public slots:
	void addFile(QString file, int pos=-1);
	void addFile(QString file, QMap< QString, QString >& metaInfo, int pos=-1);
    int addDir(QString &path, int pos=-1);
	void removeSelected();
	void doubleClicked(QTreeWidgetItem *item, int /*column*/);
	void scrollToActive();
	void deselect(QTreeWidgetItem* item,int);
	void clearPlayList();

	int loadM3UPlayList(QString &path, int pos=-1);
	int loadPLSPlayList(QString &path, int pos=-1);

	void saveM3UPlayList(QString &path);
	void savePLSPlayList(QString &path);

	void updateColumnWidth(int nr, int /*oldSize*/, int newSize);
	void updateColumnPosition(int, int, int);
	void headerContextMenu(const QPoint& point);
    void setScroll();
signals:
	void playListEmpty();
	void playItem(PlayListItem*);
private:
	PlayListItem* createNewItem(QString file, int pos = -1);
	void disconnectConfigUpdate();
	void connectConfigUpdate();
	QString msecToTimeString(int sec);
	int timeStringToSec(QString timeString);
	void updateDropPointer(const QPoint& pos);
	int addPath(QString path, bool addPlayLists=false, int pos=-1);
	void correctColumnsSizes();

	QString m_name;
	PlayListTabs *tabs;
	DropPointer *dropPointer;
	int dropIndex, scrollPosition;
	bool firstShow;
private slots:
	void hideSection();
	void showSection();

	void printPos(int pos) { qDebug() << this << "slider moved to:" << pos << "max is:" << verticalScrollBar()->maximum(); }
protected:
	void startDrag(Qt::DropActions supportedActions);
	void resizeEvent(QResizeEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);
};

#endif