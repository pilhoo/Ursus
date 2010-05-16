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

#ifndef URSUS_PLAYLISTAGENT_H
#define URSUS_PLAYLISTAGENT_H
#include <QObject>

class UrsusPlayListAgent : public QObject{
	Q_OBJECT
public:
	UrsusPlayListAgent();
	~UrsusPlayListAgent();
public slots:
	void addFile(QString &file, QStringList &metaInfo);
	void addFiles(QStringList &files);
	void removeSelected();
	void save(QString &path);
	void load(QString &path);
	void setActive(QTreeWidgetItem *item, int /*column*/);
	void setState(Phonon::State newState, Phonon::State);
	void scrollToActive();
	void metaInfoResolving(Phonon::State newState, Phonon::State oldState);
	void deselect(QTreeWidgetItem* item,int);
	void clearPlayList();
	void setPlayingMode(int m);
};

#endif