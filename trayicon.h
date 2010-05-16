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

#ifndef URSUS_TRAY_ICON
#define URSUS_TRAY_ICON

#include <KSystemTrayIcon>
#include <KXmlGuiWindow>
#include <KMenu>
#include <KActionCollection>
#include <KIcon>
#include "player.h"
#include "miniwin.h"

class UrsusTrayIcon : public KSystemTrayIcon {
	Q_OBJECT
public:
	UrsusTrayIcon(const QString &icon, KXmlGuiWindow *parent=0, UrsusPlayer *player_=0);
	~UrsusTrayIcon();

public slots:
	void setStateIcon(Phonon::State newState, Phonon::State /*oldState*/);
	void setTrackString(QString trackString);
private:
	void createIcons();

	UrsusMiniWin *winMini;
	UrsusPlayer *player;
	Phonon::State actualState;
	QString m_trackString;
	KIcon playingIcon, pausedIcon;
};

#endif