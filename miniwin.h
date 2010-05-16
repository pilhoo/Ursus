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

#ifndef URSUS_MINI_WIN
#define URSUS_MINI_WIN

#include <QToolButton>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KGlobalAccel>
#include <KStandardAction>
#include <KVBox>
#include <QStringList>
#include <QLabel>
#include <Phonon/VolumeSlider>
#include <Phonon/SeekSlider>
#include "player.h"

class UrsusMiniWin : public QWidget {
	Q_OBJECT
public:
	UrsusMiniWin(QWidget *parent=0, UrsusPlayer *player_=0);
	~UrsusMiniWin();
private:
	UrsusPlayer *player;
};

#endif