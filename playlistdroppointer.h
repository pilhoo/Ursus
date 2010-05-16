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

#ifndef URSUS_PLAYLISTDROPPOINTER_H
#define URSUS_PLAYLISTDROPPOINTER_H
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPaintEvent>
#include "playlistwidget.h"

class DropPointer : public QWidget{
	Q_OBJECT
public:
	DropPointer(QWidget* parent=0);
	~DropPointer();

	void setWidth(unsigned int w);
	void moveTo(unsigned int y);
	inline int position() { return pos; }
private:
	int pos;

	void paintEvent(QPaintEvent*);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);
};

#endif