/***************************************************************************
 *   Copyright (C) 2010 by Michał Pilch  <mpilhoo@gmail.com>               *
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

#ifndef URSUS_PLAYLISTTABBAR_H
#define URSUS_PLAYLISTTABBAR_H
#include <QTabWidget>
#include <KIcon>
#include <KLocale>
#include <KMenu>
#include <QAction>
#include <QTabBar>
#include <QLineEdit>
#include <QMouseEvent>
#include "playlisttabs.h"
#include "playlistwidget.h"

class PlayListTabs;

class PlayListTabBar : public QTabBar{
	Q_OBJECT
public:
	PlayListTabBar(QWidget *parent=0);
	~PlayListTabBar();
private slots:
	void openPlayList();
	void savePlayList();
	void clearPlayList();
	void closePlayList(/* pointer to tab or it's number*/);
	void contextMenu(const QPoint& point);
	void setPlayListName();
	void renamePlayList();
protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
private:
	void createRenameLine(int index);
	QLineEdit *renameLine;
	int edited;
	PlayListTabs *parentPLTab;
signals:
	void newPlayList();
	void closePlayListNr(int);
	void clearPlayListNr(int);
};

#endif
