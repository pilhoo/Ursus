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

#include "playlistdroppointer.h"

DropPointer::DropPointer(QWidget* parent): QWidget(parent){
	setWidth(200);
	setAcceptDrops(true);
}

DropPointer::~DropPointer(){
}

void DropPointer::setWidth(unsigned int w){
	setGeometry(5,0,w-5,3);
}

void DropPointer::moveTo(unsigned int y){
	pos=y;
	setGeometry(0,y+1, width(), height());
}

void DropPointer::paintEvent(QPaintEvent *e){
	QPainter *p=new QPainter(this);
	QPen pen;
	pen.setWidth(2);
	pen.setCapStyle(Qt::RoundCap);
	pen.setColor(Qt::black);
	pen.setStyle(Qt::DotLine);
	p->setPen(pen);
	p->setOpacity(.4);
	p->setRenderHint(QPainter::Antialiasing, true);
	p->drawLine(0,2,width(),2);
	p->end();
}


void DropPointer::dragEnterEvent(QDragEnterEvent *event){
	event->acceptProposedAction();
	show();
}

void DropPointer::dragMoveEvent(QDragMoveEvent *event){
}

void DropPointer::dragLeaveEvent(QDragLeaveEvent *event){
	hide();
}

void DropPointer::dropEvent(QDropEvent *event){
	((PlayListWidget*)parentWidget())->dropEvent(event);
}
