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

#include "ursusapp.h"
#include <QDebug>

UrsusApp::UrsusApp() : KUniqueApplication(){
// 	qDebug() << this << "constructor()";
	player=NULL;
}

UrsusApp::~UrsusApp() {
// 	qDebug() << this << "destructor()";
	delete player;
}

int UrsusApp::newInstance(){
// 	qDebug() << this << "newInstance()";
	KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

	if(!player){
		player=new UrsusPlayer();
		winMain=new UrsusMainWin(player);
		trayIcon=new UrsusTrayIcon(QString("ursus"),winMain,player);
// 		winMini=NULL/*new UrsusMiniWin(0, player)*/;

		winMain->setTrayIcon(trayIcon);
		trayIcon->show();


		winMain->setObjectName("Main Window");

		qDebug() << "loadPlayLists";
		winMain->plTabs()->loadPlayLists();

		// TODO not works :/
		if(winMain->plTabs()->ActiveItem())
			player->Object()->setCurrentSource(winMain->plTabs()->ActiveItem()->Source());

		qDebug() << "show";
		winMain->show();
		winMain->plTabs()->VisiblePlayList()->resetFirstShow();
		winMain->plTabs()->VisiblePlayList()->setScroll();
	}else
		KWindowSystem::activateWindow(winMain->winId());

	return 0;
}