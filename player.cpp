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

#include "player.h"
// #include <QDebug>
using namespace Phonon;

UrsusPlayer::UrsusPlayer(){
// 	qDebug() << this << "constructor()";
	audioOutput=new AudioOutput(MusicCategory, this);
	mediaObject=new MediaObject(this);

	mediaObject->setTickInterval(1000);
	audioOutput->setVolume(1.);

	createPath(mediaObject, audioOutput);
	start=false;
}

UrsusPlayer::~UrsusPlayer(){
// 	qDebug() << this << "destructor";
	delete audioOutput;
	delete mediaObject;
}

AudioOutput* UrsusPlayer::Output(){
// 	qDebug() << this << "Output()";
	return audioOutput;
}

MediaObject* UrsusPlayer::Object(){
// 	qDebug() << this << "Object()";
	return mediaObject;
}

void UrsusPlayer::play(){
// 	qDebug() << this << "play()";
	bool stopped=false;
	if(mediaObject->state()==PlayingState){
		mediaObject->stop();
		stopped=true;
	}
	if(mediaObject->state()==PausedState || stopped){
		mediaObject->play();
		return;
	}
	if(mediaObject->queue().isEmpty()){
		emit(needActualSource());
		start=true;
	}else{
		mediaObject->setCurrentSource(mediaObject->queue().takeFirst());
		startPlaying();
	}
}

void UrsusPlayer::play(MediaSource& mediaSource){
// 	qDebug() << this << "play(MediaSource)";
// 	mediaObject->stop();
	mediaObject->clearQueue();
	mediaObject->setCurrentSource(mediaSource);
	startPlaying();
}

void UrsusPlayer::pause(){
// 	qDebug() << this << "pause()";
	mediaObject->pause();
}

void UrsusPlayer::stop(){
// 	qDebug() << this << "stop()";
	mediaObject->stop();
}

void UrsusPlayer::previous(){
// 	qDebug() << this << "previous()";
	mediaObject->stop();
	start=true;
	mediaObject->clearQueue();
	emit(needPreviousSource());
}

void UrsusPlayer::next(){
// 	qDebug() << this << "next()";
	mediaObject->stop();
	if(mediaObject->queue().isEmpty()){
		start=true;
		emit(needNextSource());
	}else{
		mediaObject->setCurrentSource(mediaObject->queue().takeFirst());
		startPlaying();
	}
}

void UrsusPlayer::enqueue(MediaSource& source){
// 	qDebug() << this << "enqueue()";
	mediaObject->enqueue(source);
	if(start){
		mediaObject->setCurrentSource(mediaObject->queue().takeFirst());
		start=false;
		startPlaying();
	}
}
void UrsusPlayer::startPlaying(){
// 	qDebug() << this << "startPlaying()";
	mediaObject->play();
}
