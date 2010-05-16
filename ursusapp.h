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

#include <KUniqueApplication>
#include <KConfig>
#include <KCmdLineArgs>
#include <KWindowSystem>

#include "mainwin.h"
#include "trayicon.h"
// #include "playlisttabs.h"

class UrsusApp : public KUniqueApplication {
public:
	UrsusApp();
	~UrsusApp();

	int newInstance();
private:
	UrsusPlayer *player;
	UrsusMainWin *winMain;
	UrsusTrayIcon *trayIcon;
};
