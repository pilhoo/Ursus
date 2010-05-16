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

#ifndef URSUS_METAINFORESOLVER_H
#define URSUS_METAINFORESOLVER_H
#include <QProgressBar>
#include <QQueue>
#include <Phonon/MediaObject>
#include <QTime>
#include "playlistitem.h"

class MetaInfoResolver : public QObject{
	Q_OBJECT
public:
	MetaInfoResolver(QWidget *parent=0, QProgressBar *bar=0);
	~MetaInfoResolver();
public slots:
	void Enqueue(PlayListItem *item);
	void infoResolving(Phonon::State newState, Phonon::State /* oldState */);
	void resolveNextItem();
private:
	QProgressBar *progressBar;
	Phonon::MediaObject *mediaObject;
	QQueue<PlayListItem*> queue;
	PlayListItem *actualItem;

	QString msecToTimeString(int msec);
signals:
	void readyToResolveNext();
};

#endif