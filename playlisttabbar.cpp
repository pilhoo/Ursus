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

#include "playlisttabbar.h"
// #include <QDebug>

PlayListTabBar::PlayListTabBar(QWidget* parent): QTabBar(parent){
// 	qDebug() << this << "constructor()";
	setContextMenuPolicy(Qt::CustomContextMenu);
	parentPLTab=(PlayListTabs*)parent;
	connect(
		this,	SIGNAL(customContextMenuRequested(const QPoint&)),
		this,	SLOT(contextMenu(const QPoint&))
	);
	renameLine=0;
	edited=-1;
}

PlayListTabBar::~PlayListTabBar(){
}

void PlayListTabBar::openPlayList(){
	// TODO
}

void PlayListTabBar::savePlayList(){
	// TODO
}

void PlayListTabBar::clearPlayList(){
// 	qDebug() << this << "clearPlayList()";
	if(QAction *action=qobject_cast<QAction*>(sender()) ){
		int nr=action->data().toInt();
		emit(clearPlayListNr(nr));
	}
}

void PlayListTabBar::closePlayList(){
// 	qDebug() << this << "closePlayList()";
	if(QAction *action=qobject_cast<QAction*>(sender()) ){
		int nr=action->data().toInt();
		emit(closePlayListNr(nr));
	}
}

void PlayListTabBar::contextMenu(const QPoint& point){
// 	qDebug() << this << "contextMenu()";
	int index=tabAt(point);
	KMenu menu;
	QAction *action;

	if(index!=-1){
		action=menu.addAction(KIcon("edit-rename"), tr("Rename Playlist"), this, SLOT(renamePlayList()));
		action->setData(index);

		action=menu.addAction(KIcon("edit-clear-list"), tr("Clear Playlist"), this, SLOT(clearPlayList()));
		action->setData(index);

		action=menu.addAction(KIcon("dialog-close"), tr("Close Playlist"), this, SLOT(closePlayList()));
		action->setData(index);
	}else{

	}

	menu.exec(QCursor::pos());
}

void PlayListTabBar::renamePlayList(){
// 	qDebug() << this << "renamePlayList()";
	if(QAction *action=qobject_cast<QAction*>(sender()) ){
		int nr=action->data().toInt();
		createRenameLine(nr);
	}
}

void PlayListTabBar::createRenameLine(int index){
// 	qDebug() << this << "createRenameLine()";
	if(renameLine)
		setPlayListName();

	renameLine=new QLineEdit(this);
	renameLine->setGeometry(tabRect(index));
	renameLine->setText(parentPLTab->PlayList(index)->name());
	renameLine->show();
	renameLine->selectAll();
	renameLine->setFocus();
	edited=index;
	connect(
		renameLine,	SIGNAL(editingFinished()),
		this,		SLOT(setPlayListName())
	);
}

void PlayListTabBar::setPlayListName(){
// 	qDebug() << this << "setPlayListName()";
	QString listName=renameLine->text();
	parentPLTab->PlayList(edited)->setName(renameLine->text());
	listName.replace('&', "&&");
	setTabText(edited, listName);
	disconnect(
		renameLine,	SIGNAL(editingFinished()),
		this,		SLOT(setPlayListName())
	);
	renameLine->hide();
	delete renameLine;
	renameLine=0;
	edited=-1;
}


void PlayListTabBar::mouseDoubleClickEvent(QMouseEvent *event){
// 	qDebug() << this << "mouseDoubleClickEvent()";
	int index=tabAt(event->pos());
	if(index!=-1)
		createRenameLine(index);
	else
		emit(newPlayList());
}

