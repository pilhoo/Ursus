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

#ifndef URSUSPLAYLISTITEM_H
#define URSUSPLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <Phonon/MediaSource>
#include <KIcon>
#include <QTextCodec>
#include <KColorScheme>

class PlayListItem : public QTreeWidgetItem{
public:
	PlayListItem(QTreeWidget *parent=0, QString path="");
	~PlayListItem();

	Phonon::MediaSource& Source();
	void setSource(QString path);
	void setAppearance(bool, KIcon icon);
	void setMetaInfo(QMap<QString, QString> info);
	void checkEmptyInfo();
	inline bool isValid() { return valid; }
	QString Path();
	QString getTrackString();
	QString Artist();
	QString Title();
	QString Album();
	QString Date();
	QString Genre();
	QString TrackNo();
	QString Length();
private:
	Phonon::MediaSource source;
	QString m_path;
	QMap<QString, QString> metaInfo;
	bool valid;
};

QDataStream& operator<< (QDataStream &out, PlayListItem &item);
QDataStream& operator>> (QDataStream &in, PlayListItem &item);

#endif