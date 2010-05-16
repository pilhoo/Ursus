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

#include "playlistitem.h"
// #include <QDebug>

PlayListItem::PlayListItem(QTreeWidget *parent, QString path): QTreeWidgetItem(parent){
// 	qDebug() << this << "constructor()";
	setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
	setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
	setTextAlignment(7,Qt::AlignRight); // Length column
	setSource(path);
	m_path=path;
	setText(3,path);
}

PlayListItem::~PlayListItem(){
// 	qDebug() << this << "destructor()";
}

Phonon::MediaSource& PlayListItem::Source(){
	return source;
}

void PlayListItem::setSource(QString path){
// 	qDebug() << this << "setSource()";
	m_path=path;
	source=Phonon::MediaSource(path);

// 	qDebug() << path;
	if(source.type()==Phonon::MediaSource::Invalid){
		valid=false;
		setIcon(0, KIcon("dialog-error"));
		setText(1, "Invalid Source");
	}else{
		valid=true;
		setIcon(0, KIcon());
	}
}

void PlayListItem::setAppearance(bool active, KIcon icon){
// 	qDebug() << this << "setAppearance()";
	setIcon(0,icon);
	QFont font;
	// TODO make configuration for this
	if(active){
		font.setBold(true);
	}
	for(int i=0;i<columnCount();++i){
		setFont(i, font);
	}
}

void PlayListItem::setMetaInfo(QMap<QString, QString> info){
// 	qDebug() << this << "setMetaInfo()";
	metaInfo=info;
	setText(1, metaInfo["ARTIST"].isEmpty() ? "?":metaInfo["ARTIST"]);
	setText(2, metaInfo["ALBUM"].isEmpty() ? "?":metaInfo["ALBUM"]);
	setText(3, metaInfo["TITLE"].isEmpty() ? "?":metaInfo["TITLE"]);
	setText(4, metaInfo["DATE"].isEmpty() ? "?":metaInfo["DATE"]);
	setText(5, metaInfo["GENRE"].isEmpty() ? "?":metaInfo["GENRE"]);
	setText(6, metaInfo["TRACKNUMBER"].isEmpty() ? "?":metaInfo["TRACKNUMBER"]);
	setText(7, metaInfo["LENGTH"].isEmpty() ? "0:00":metaInfo["LENGTH"]);
}

void PlayListItem::checkEmptyInfo(){
	qDebug() << this << "checkEmptyInfo()";
	if(metaInfo["ARTIST"].isEmpty()) setText(1, "?");
	if(metaInfo["ALBUM"].isEmpty()) setText(2, "?");
	if(metaInfo["TITLE"].isEmpty()) setText(3, "?");
	if(metaInfo["DATE"].isEmpty()) setText(4, "?");
	if(metaInfo["GENRE"].isEmpty()) setText(5, "?");
	if(metaInfo["TRACKNUMBER"].isEmpty()) setText(6, "?");
	if(metaInfo["LENGTH"].isEmpty()) setText(7, "0:00");
}

QString PlayListItem::Path(){
// 	qDebug() << this << "ath()";
	return m_path;
}

QString PlayListItem::getTrackString(){
// 	qDebug() << this << "getTrackString()";
	return QString("%1 - %2").arg(Artist()).arg(Title());
}

QString PlayListItem::Artist(){
	return metaInfo["ARTIST"];
}

QString PlayListItem::Title(){
	return metaInfo["TITLE"];
}

QString PlayListItem::Album(){
	return metaInfo["ALBUM"];
}

QString PlayListItem::Date(){
	return metaInfo["DATE"];
}

QString PlayListItem::Genre(){
	return metaInfo["GENRE"];
}

QString PlayListItem::TrackNo(){
	return metaInfo["TRACKNUMBER"];
}

QString PlayListItem::Length(){
	return metaInfo["LENGTH"];
}

QDataStream& operator<< (QDataStream &out, PlayListItem &item){
	out << item.Path() << item.Artist() << item.Album() << item.Title() << item.Date() << item.Genre() << item.TrackNo() << item.Length();
	return out;
}

QDataStream& operator>> (QDataStream &in, PlayListItem &item){
	QString path;
	in >> path;
	item.setSource(path);

	QMap<QString, QString> metaInfo;
	QString info;

	in >> info;
	metaInfo["ARTIST"]=info;
	in >> info;
	metaInfo["ALBUM"]=info;
	in >> info;
	metaInfo["TITLE"]=info;
	in >> info;
	metaInfo["DATE"]=info;
	in >> info;
	metaInfo["GENRE"]=info;
	in >> info;
	metaInfo["TRACKNUMBER"]=info;
	in >> info;
	metaInfo["LENGTH"]=info;

	item.setMetaInfo(metaInfo);

	return in;
}
