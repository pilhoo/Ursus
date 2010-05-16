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

#ifndef URSUS_PLAYLISTTABS_H
#define URSUS_PLAYLISTTABS_H
#include <QTabWidget>
#include <KIcon>
#include <QProgressBar>
#include <QQueue>
#include <QList>
#include <KTreeWidgetSearchLine>
#include <KFileDialog>
#include <QDesktopServices>
#include <KLocale>
#include <KMenu>
#include <KAction>
#include <Phonon/MediaSource>
#include <QRect>
#include "playlisttabbar.h"
#include "playlistwidget.h"
#include "playlistitem.h"
#include "metainforesolver.h"
// #include <QLabel>

class PlayListWidget;

class PlayListTabs : public QTabWidget{
	friend class PlayListWidget;
	Q_OBJECT
public:
	PlayListTabs(QWidget *parent=0, KTreeWidgetSearchLine *line=0);
	~PlayListTabs();

	PlayListWidget* ActivePlayList();
	PlayListWidget* VisiblePlayList();
	PlayListWidget* PlayList(int nr);
	PlayListItem* ActiveItem();

public slots:
	void loadPlayLists();
	void savePlayLists();
	void newPlayList();
	void openPlayListFile();
	void savePlayListFile();
	void clearActivePlayList();
	void clearPlayList(int index);
	void closeActivePlayList();
	void closePlayList(int index);
	void addFiles();
	void removeSelected();
	void jumpToActive();
	void setState(Phonon::State newState, Phonon::State);
	void selectionChanged();

	void playItem(PlayListItem* item);
	void getNextSource();
	void getPreviousSource();
	void getActualSource();
private:
	PlayListWidget* newNamedPlayList(QString name);
	void setActive(PlayListWidget *widget, PlayListItem *item);
	int activeIndex() { return (active) ? indexOf((QWidget*)active):-1; }

	QProgressBar *progressBar;
	Phonon::State actualState;
	MetaInfoResolver *metaResolver;
	KTreeWidgetSearchLine *searchLine;

	QList<bool> columnsVisibility;
	QList<float> columnsWidth;
	QList<unsigned int> columnsPosition;

	PlayListWidget *active,*visible;
	PlayListItem *activeItem;
private slots:
	void tabChanged(int nr);
signals:
	void visibleChanged(PlayListWidget *shown);
	void enableRemoveAction(bool);
	void playSource(Phonon::MediaSource&);
	void trackStringChanged(QString);
	void giveSource(Phonon::MediaSource&);
	void activeItemExists(bool);
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif
