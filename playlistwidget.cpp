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

#include "playlistwidget.h"
#include <QDebug>

PlayListWidget::PlayListWidget(QWidget* parent) : QTreeWidget(parent){
// 	qDebug() << this << "constructor()";
	setRootIsDecorated(false);
	setSortingEnabled(false);
	setAcceptDrops(true);
	setDragEnabled(true);
	setItemsExpandable(false);
	setTabKeyNavigation(false);
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setAlternatingRowColors(true);
	setAllColumnsShowFocus(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	header()->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(
		header(),	SIGNAL(customContextMenuRequested(const QPoint&)),
		this,		SLOT(headerContextMenu(const QPoint&))
	);

	QStringList headerLabels;
	headerLabels << "*" << "Artist" << "Album" << "Title"  << "Date" << "Genre"<< "Track No." << "Length";
	setHeaderLabels(headerLabels);

	tabs=(PlayListTabs*) parentWidget();

	dropPointer=new DropPointer(this);
	dropPointer->hide();
	dropPointer->setWidth(visibleWidth());
	dropPointer->moveTo(0);

	refreshConfig();

	connectConfigUpdate();

	connect(
		this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
		this, SLOT(doubleClicked(QTreeWidgetItem*,int))
	);
	connect(
		this,	SIGNAL(playItem(PlayListItem*)),
		tabs,	SLOT(playItem(PlayListItem*))
	);
	connect(
		this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
		this, SLOT(deselect(QTreeWidgetItem*,int))
	);

	connect(
		verticalScrollBar(),	SIGNAL(valueChanged(int)),
		this,					SLOT(printPos(int))
	);

	firstShow=true;
	scrollPosition=0;
}

PlayListWidget::~PlayListWidget(){
}

void PlayListWidget::refreshConfig(){
// 	qDebug() << this << "refreshConfig()";
	disconnectConfigUpdate();
	for(int i=0; i<columnCount(); ++i){
		setColumnHidden(i,!tabs->columnsVisibility[i]);
		setColumnWidth(i, (int)((double)visibleWidth() * tabs->columnsWidth[i]));
		header()->moveSection(header()->visualIndex(i), tabs->columnsPosition[i]);
	}
	connectConfigUpdate();
}

unsigned int PlayListWidget::visibleWidth(){
	return width() - verticalScrollBar()->width();
}

PlayListItem* PlayListWidget::itemAbove(const QTreeWidgetItem *item){
	return (PlayListItem*) QTreeWidget::itemAbove(item);
}

PlayListItem* PlayListWidget::itemBelow(const QTreeWidgetItem *item){
	return (PlayListItem*) QTreeWidget::itemBelow(item);
}

PlayListItem* PlayListWidget::itemAt(int index){
	return (PlayListItem*) QTreeWidget::topLevelItem(index);
}

PlayListItem* PlayListWidget::itemAt(const QPoint &pos){
	return (PlayListItem*) QTreeWidget::itemAt(pos);
}

QString PlayListWidget::name(){
	return m_name;
}

void PlayListWidget::setName(QString name){
	m_name=name;
}

void PlayListWidget::load(){
// 	qDebug() << this << "load()";
	KConfigGroup cfg(KGlobal::config(), QString("playlist-%1").arg(m_name));
	QStringList playlist=cfg.readEntry("list", QStringList());

	foreach(QString entry, playlist){
		QMultiMap<QString, QString> info;
		QStringList infoList=entry.split('\n'); // TODO this sux a little
		info.replace("ARTIST", infoList.at(1));
		info.replace("ALBUM", infoList.at(2));
		info.replace("TITLE", infoList.at(3));
		info.replace("DATE", infoList.at(4));
		info.replace("GENRE", infoList.at(5));
		info.replace("TRACKNUMBER", infoList.at(6));
		info.replace("LENGTH", infoList.at(7));
		QString filename=infoList.at(0);
		addFile(filename, info);
	}
	scrollPosition=cfg.readEntry(QString("ScrollVal"), 0);
}

void PlayListWidget::save(){
// 	qDebug() << this << "save()";
	KConfigGroup cfg(KGlobal::config(), QString("playlist-%1").arg(m_name));
	QStringList playlist;

	cfg.writeEntry(QString("ScrollVal"), verticalScrollBar()->value());

	for(int j=0;j<topLevelItemCount();++j){
		PlayListItem *item=itemAt(j);
		QString info;

		info=QString("%1\n%2\n%3\n%4\n%5\n%6\n%7\n%8").arg(item->Path()).arg(item->Artist()).arg(item->Album()).arg(item->Title()).arg(item->Date()).arg(item->Genre()).arg(item->TrackNo()).arg(item->Length());

		playlist.append(info);
	}
	cfg.writeEntry("list", playlist);
}

void PlayListWidget::addFile(QString file, int pos){
// 	qDebug() << this << "addFile(QString)";
	PlayListItem *newItem=createNewItem(file, pos);
	if(newItem->isValid())
		tabs->metaResolver->Enqueue(newItem);
}

void PlayListWidget::addFile(QString file, QMap<QString, QString> &metaInfo, int pos){
// 	qDebug() << this << "addFile(string, map)";
	PlayListItem *newItem=createNewItem(file, pos);
	newItem->setMetaInfo(metaInfo);
}

int PlayListWidget::addDir(QString &path, int pos){
// 	qDebug() << this << "addDir( ,"<< pos << ")";
	QDir dir(path);
	QStringList entries=dir.entryList();

	int added=0;

	foreach(QString filename, entries)
		if(filename!=QString("..") && filename!=QString(".")){// TODO maybe there is some better way to to that
			added+=addPath(dir.filePath(filename), false, (pos==-1) ? pos:pos+added);
		}

	return added;
}

void PlayListWidget::removeSelected(){
// 	qDebug() << this << "removeSelected()";
	while(!selectedItems().isEmpty()){
		if(selectedItems().front()==tabs->activeItem)
			tabs->activeItem=NULL;
		delete selectedItems().front();
	}
	if(!topLevelItemCount())
		emit(playListEmpty());
}

void PlayListWidget::deselect(QTreeWidgetItem* item,int /*column*/){
	item->setSelected(false);
}

void PlayListWidget::clearPlayList(){
	clear();
}

void PlayListWidget::doubleClicked(QTreeWidgetItem *item, int /*column*/){
// 	qDebug() << this << "doubleClicked()";
	PlayListItem *plItem=(PlayListItem*)item;
	if(plItem->isValid())
		emit(playItem(plItem));
// 	else
// 		plItem->setAppearance(false, KIcon("dialog-error"));
}

void PlayListWidget::scrollToActive(){
// 	qDebug() << this << "scrollToActive()";
	scrollToItem(tabs->activeItem);
}

int PlayListWidget::loadM3UPlayList(QString &path, int pos){
// 	qDebug() << this << "loadM3UPlayList()";
	int added=0;
	QString dirPath=path.section('/', 0,-2)+"/";

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return 0;

	QTextStream in(&file);

	QString line;
	while (!in.atEnd()){
		line=in.readLine();
		if(line=="#EXTM3U")
			continue;
		if(line.startsWith("#EXTINF:")){
			line.remove(0,8);
			line=in.readLine();
		}
		QString filePath=(line.startsWith("/")) ? line:dirPath+line;
		addFile(filePath,pos+added++);
	}
	return added;
}

int PlayListWidget::loadPLSPlayList(QString &path, int pos){
// 	qDebug() << this << "loadPLSPlayList()";
	// TODO load pls
	return 0;
}

void PlayListWidget::saveM3UPlayList(QString &path){
// 	qDebug() << this << "saveM3UPlayList()";
	QFile file(path);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	QTextStream out(&file);
	out << "#EXTM3U\n";
	for(int i=0;i<topLevelItemCount();++i){
		PlayListItem *hlp=itemAt(i);
		out << "#EXTINF:" << timeStringToSec(hlp->Length()) << "," << hlp->Title() << "\n" << hlp->Path() << "\n";
	}
}

void PlayListWidget::savePLSPlayList(QString &path){
// 	qDebug() << this << "savePLSPlayList()";
	// TODO save pls
}

void PlayListWidget::updateColumnWidth(int nr, int /*oldSize*/, int newSize){
// 	qDebug() << this << "updateColumnWidth()";
	tabs->columnsWidth[nr]=(float)newSize/(float)visibleWidth();
}

void PlayListWidget::updateColumnPosition(int /*nr*/, int /*oldVisualIndex*/,  int /*newVisualIndex*/){
// 	qDebug() << this << "updateColumnPosition()";
	for(int i=0;i<columnCount();++i)
		tabs->columnsPosition[i]=header()->visualIndex(i);
}

void PlayListWidget::headerContextMenu(const QPoint& point){
// 	qDebug() << this << "headerContextMenu()";
	QMenu menu;
	QAction *action;
	int index=header()->logicalIndexAt(point);
	action=menu.addAction(tr("hide section ")+headerItem()->text(index), this, SLOT(hideSection()));
	action->setData(index);
	menu.addSeparator();

	for(int i=0;i<columnCount();++i){
		if(!tabs->columnsVisibility[i]){
			action=menu.addAction(tr("show section ")+headerItem()->text(i), this, SLOT(showSection()));
			action->setData(i);
		}
	}

	menu.exec(QCursor::pos());
}

void PlayListWidget::resetFirstShow(){
	firstShow=true;
}

void PlayListWidget::setScroll(){
	if(firstShow){
		qDebug() << "scrollpos=" << scrollPosition << "max=" << verticalScrollBar()->maximum();
		verticalScrollBar()->setValue(scrollPosition);
		firstShow=false;
	}
}

void PlayListWidget::hideSection(){
// 	qDebug() << this << "hideSection()";
	if(QAction *action=qobject_cast<QAction*>(sender()) ){
		int nr=action->data().toInt();
		tabs->columnsVisibility[nr]=false;
// 		hideColumn(nr);
		correctColumnsSizes();
	}
}

void PlayListWidget::showSection(){
// 	qDebug() << this << "showSection()";
	if(QAction *action=qobject_cast<QAction*>(sender()) ){
		int nr=action->data().toInt();
		tabs->columnsVisibility[nr]=true;
// 		showColumn(nr);
		correctColumnsSizes();
	}
}

void PlayListWidget::correctColumnsSizes(){
	double sum=0.;
	for(int i=0;i<columnCount();++i)
		if(tabs->columnsVisibility[i])
			sum+=tabs->columnsWidth[i];

	int sizeSum=0, lv;
	for(int i=0;i<columnCount();++i){
		if(tabs->columnsVisibility[i]){
			tabs->columnsWidth[i]/=sum;
			lv=i;
			sizeSum+=tabs->columnsWidth[i]*visibleWidth();
		}
	}
	refreshConfig();
}

QString PlayListWidget::msecToTimeString(int msec){
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

PlayListItem* PlayListWidget::createNewItem(QString file, int pos){
// 	qDebug() << this << "createNewItem()";
	PlayListItem *newItem=new PlayListItem(0, file);
	if(pos!=-1)
		insertTopLevelItem(pos, newItem);
	else
		addTopLevelItem(newItem);
	return newItem;
}

void PlayListWidget::disconnectConfigUpdate(){
// 	qDebug() << this << "disconnectConfigUpdate()";
	disconnect(
		header(),	SIGNAL(sectionResized(int,int,int)),
		this,		SLOT(updateColumnWidth(int,int,int))
	);
	disconnect(
		header(),	SIGNAL(sectionMoved(int,int,int)),
		this,		SLOT(updateColumnPosition(int,int,int))
	);
}

void PlayListWidget::connectConfigUpdate(){
// 	qDebug() << this << "connectConfigUpdate()";
	connect(
		header(),	SIGNAL(sectionResized(int,int,int)),
		this,		SLOT(updateColumnWidth(int,int,int))
	);
	connect(
		header(),	SIGNAL(sectionMoved(int,int,int)),
		this,		SLOT(updateColumnPosition(int,int,int))
	);
}

int PlayListWidget::timeStringToSec(QString timeString){
// 	qDebug() << this << "timeStringToSec()";
	int sec=timeString.section(':',-1).toInt();
	sec+=timeString.section(':',-2).toInt()*60;
	if(timeString.length()>6)
		sec+=timeString.section(':',-3).toInt()*3600;
	return sec;
}

void PlayListWidget::resizeEvent(QResizeEvent *event){
// 	qDebug() << this << "resizeEvent()";
	disconnect(
		header(),	SIGNAL(sectionResized(int,int,int)),
		this,		SLOT(updateColumnWidth(int,int,int))
	);

	float sum=0.;
	for(int i=0;i<columnCount()-1; ++i){
		setColumnWidth(i, (int)((float)visibleWidth() * tabs->columnsWidth[i]));
		sum+=tabs->columnsWidth[i];
	}
	setColumnWidth(columnCount()-1, visibleWidth() * (1.-sum));

	connect(
		header(),	SIGNAL(sectionResized(int,int,int)),
		this,		SLOT(updateColumnWidth(int,int,int))
	);
	dropPointer->setWidth(visibleWidth());

// 	qDebug() << "geom=" << geometry();
// 	qDebug() << "ScrollVal=" << verticalScrollBar()->value();
}

void PlayListWidget::updateDropPointer(const QPoint &pos){
// 	qDebug() << this << "updateDropPointer()";
	PlayListItem *item=itemAt(pos);

	// TODO this suck a 'little' :/
	QPoint p=pos,d(p),u(p);
	int hy;


	if(item){
		while(itemAt(u) == item) u.ry()--;
		while(itemAt(d) == item) d.ry()++;

		if(d.ry()-p.ry() < p.ry()-u.ry()){
			hy=d.ry();
			dropIndex=indexOfTopLevelItem(item)+1;
		}else{
			hy=u.ry();
			dropIndex=indexOfTopLevelItem(item);
		}
	}else{
		while(u.ry()>0 && !itemAt(u)) u.ry()--;
		hy=u.ry();
		dropIndex=-1;
	}
	hy+=header()->height();

	if(dropPointer->position()!=hy)
		dropPointer->moveTo(hy);
}

int PlayListWidget::addPath(QString path, bool addPlayLists, int pos){
// 	qDebug() << this << "addPath(,"<< addPlayLists <<","<< pos <<")";
	if(path.endsWith(".mp3") || path.endsWith(".ogg") || path.endsWith(".wma")){
		addFile(path, pos);
		return 1;
	}else if(QDir(path).exists()){
		return addDir(path, pos);
	}else if(addPlayLists){
		if(path.endsWith(".pls"))
			return loadM3UPlayList(path);
		else if(path.endsWith(".m3u"))
			return loadPLSPlayList(path);
	}
	return 0;
}

void PlayListWidget::startDrag(Qt::DropActions supportedActions){
//     QTreeWidget::startDrag(supportedActions);

	QList<QUrl> urls;
	QByteArray byteArray;
	QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
	foreach(QTreeWidgetItem *item, selectedItems()){
		PlayListItem *plItem=(PlayListItem*)item;
		urls.append(QUrl(plItem->Path()));
		dataStream << indexOfTopLevelItem(item) << *plItem;
	}

	QMimeData *data=new QMimeData;
	data->setUrls(urls);
	data->setData("application/x-ursus-playlistitemlist", byteArray);

	QDrag *drag=new QDrag(this);
	drag->setPixmap(KIcon("audio-x-flac").pixmap(16)); // TODO maybe some better icons
	drag->setMimeData(data);

	drag->exec(Qt::MoveAction);
}

void PlayListWidget::dragEnterEvent(QDragEnterEvent *event){
	event->acceptProposedAction();
	dropPointer->show();
	updateDropPointer(event->pos());
}

void PlayListWidget::dragMoveEvent(QDragMoveEvent *event){
	int y=event->pos().y();
	// TODO scrolling when cursor is near up and bottom
	updateDropPointer(event->pos());
}

void PlayListWidget::dragLeaveEvent(QDragLeaveEvent *event){
	dropPointer->hide();
}

void PlayListWidget::dropEvent(QDropEvent *event){
	const QMimeData *mimeData=event->mimeData();
	if(mimeData->hasFormat("application/x-ursus-playlistitemlist")){
		QByteArray byteArray(mimeData->data("application/x-ursus-playlistitemlist"));
		QDataStream stream(&byteArray, QIODevice::ReadOnly);
		QList<PlayListItem*> toDel;
		QList<QTreeWidgetItem*> toInsert;
		while(!stream.atEnd()){
			int index;
			PlayListItem *item, *hlp;

			item=new PlayListItem(0, QString());
			stream >> index >> *item;
			hlp=(PlayListItem*)topLevelItem(index);
			if(hlp == tabs->ActiveItem())
				tabs->setActive(this, item);
			toDel.append(hlp);
			toInsert.append(item);
		}
		insertTopLevelItems(dropIndex, toInsert);
		foreach(QTreeWidgetItem *item, toInsert)
			item->setSelected(true);
		foreach(PlayListItem *item, toDel)
			delete item;
	}else if(mimeData->hasUrls()){
		int added=0;
		foreach(QUrl url, mimeData->urls()){
			added+=addPath(url.path(), true, (dropIndex==-1) ? -1:dropIndex+added);
		}
	}
	dropIndex=-1;
	dropPointer->hide();
}
