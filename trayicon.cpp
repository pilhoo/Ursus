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

#include "trayicon.h"
// #include <QDebug>

UrsusTrayIcon::UrsusTrayIcon(const QString &icon, KXmlGuiWindow *parent, UrsusPlayer *player_) : KSystemTrayIcon(icon, parent){
// 	qDebug() << this << "constructor()";
	player=player_;

	QMenu *cm=contextMenu();
	cm->addAction(parent->actionCollection()->action("mute"));
	cm->addSeparator();
	cm->addAction(parent->actionCollection()->action("previous"));
	cm->addAction(parent->actionCollection()->action("play"));
	cm->addAction(parent->actionCollection()->action("pause"));
	cm->addAction(parent->actionCollection()->action("stop"));
	cm->addAction(parent->actionCollection()->action("next"));

	setToolTip("Ursus Music Player");

	connect(
		player->Object(),	SIGNAL(stateChanged(Phonon::State, Phonon::State)),
		this,				SLOT(setStateIcon(Phonon::State, Phonon::State))
	);
}

UrsusTrayIcon::~UrsusTrayIcon() {
// 	qDebug() << this << "destructor()";
	disconnect(
		player->Object(),	SIGNAL(stateChanged(Phonon::State, Phonon::State)),
		this,				SLOT(setStateIcon(Phonon::State, Phonon::State))
	);
}

void UrsusTrayIcon::setStateIcon(Phonon::State newState, Phonon::State /*oldState*/){
// 	qDebug() << this << "setStateIcon()";
	switch(actualState=newState){
	case Phonon::PlayingState:
		setIcon(KIcon("ursusplaying"));
		setToolTip(m_trackString);
		break;
	case Phonon::PausedState:
		setIcon(KIcon("ursuspaused"));
		setToolTip(m_trackString);
		break;
	default:
		setIcon(KIcon("ursus"));
		setToolTip("Ursus Music Player");
		break;
	}
}

void UrsusTrayIcon::setTrackString(QString trackString){
// 	qDebug() << this << "setTrackString()";
	m_trackString=trackString;
	if(actualState==Phonon::PlayingState)
		setToolTip(m_trackString);
}
