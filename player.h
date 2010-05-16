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

#ifndef URSUS_PLAYER_H
#define URSUS_PLAYER_H

#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#include <cstdio>

using namespace Phonon;

class UrsusPlayer : public QObject{
	Q_OBJECT
public:
	UrsusPlayer();
	~UrsusPlayer();

	AudioOutput* Output();
	MediaObject* Object();
public slots:
	void play();
	void play(Phonon::MediaSource &mediaSource);
	void pause();
	void stop();
	void previous();
	void next();

	void enqueue(Phonon::MediaSource &source);
signals:
	void needActualSource();
	void needNextSource();
	void needPreviousSource();
private:
	void startPlaying();
	MediaObject *mediaObject;
	AudioOutput *audioOutput;

	bool start;
};
#endif