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

#ifndef URSUS_PLUGIN_PANEL_H
#define URSUS_PLUGIN_PANEL_H

#include <QWidget>
#include <KDebug>
#include <QSplitter>
#include <KVBOX>
#include <KHBox>
#include <QSpacer>
#include <QList>
#include <QPushButton>

class UrsusPluginPanel : public QWidget{
	Q_OBJECT
public:
	UrsusPluginPanel();
	~UrsusPluginPanel();

public slots:
signals:
private:
	QSplitter *splitter;
};
#endif