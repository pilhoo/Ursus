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

#include "metainforesolver.h"
// #include <QDebug>

MetaInfoResolver::MetaInfoResolver(QWidget *parent, QProgressBar *bar){
// 	qDebug() << this << "constructor()";
	progressBar=bar;
	mediaObject=new Phonon::MediaObject(this);

	actualItem=0;
	connect(
		mediaObject,	SIGNAL(stateChanged(Phonon::State,Phonon::State)),
		this,			SLOT(infoResolving(Phonon::State, Phonon::State))
	);
	connect(
		this,	SIGNAL(readyToResolveNext()),
		this,	SLOT(resolveNextItem())
	);
}

MetaInfoResolver::~MetaInfoResolver(){
// 	qDebug() << this << "destructor()";
	delete mediaObject;
}

void MetaInfoResolver::Enqueue(PlayListItem *item){
// 	qDebug() << this << "Enqueue()";
	bool wasEmpty=queue.isEmpty();
	queue.enqueue(item);
	progressBar->setRange(0,progressBar->maximum()+1);
	if(wasEmpty && !actualItem){
		progressBar->setVisible(true);
		emit(readyToResolveNext());
	}
}

void MetaInfoResolver::infoResolving(Phonon::State newState, Phonon::State /* oldState */){
// 	qDebug() << this << "infoResolving()";
	if(newState!=Phonon::StoppedState && newState!=Phonon::PausedState)
		return;

	if(newState==Phonon::ErrorState || mediaObject->currentSource().type() == Phonon::MediaSource::Invalid){
		actualItem->setIcon(0, KIcon("dialog-error"));
	}else{
		QMap<QString,QString> metaData=mediaObject->metaData();
		metaData["LENGTH"]=msecToTimeString(mediaObject->totalTime());

		actualItem->setMetaInfo(metaData);
	}

	progressBar->setValue(progressBar->value()+1);
	actualItem=NULL;

	emit(readyToResolveNext());
}

void MetaInfoResolver::resolveNextItem(){
// 	qDebug() << this << "resolveNextItem()";
	if(!queue.isEmpty()){
		actualItem=queue.dequeue();
		mediaObject->setCurrentSource(actualItem->Source());
	}else{
		progressBar->setVisible(false);
		progressBar->setRange(0,0);
	}
}

QString MetaInfoResolver::msecToTimeString(int msec){
// 	qDebug() << this << "msecToTimeString()";
	QString timeString;
	QTime length((msec/3600000), (msec/60000)%60, (msec/1000)%60);
	if(length.hour()>9)
		timeString=length.toString("hh:mm:ss");
	else if(length.hour()>0)
		timeString=length.toString("h:mm:ss");
	else if(length.minute()>9)
		timeString=length.toString("mm:ss");
	else
		timeString=length.toString("m:ss");

	return timeString;
}
