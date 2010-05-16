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

#include "playlisttabs.h"
#include <KAction>
// #include <QDebug>

PlayListTabs::PlayListTabs(QWidget *parent, KTreeWidgetSearchLine *line) : QTabWidget(parent){
// 	qDebug() << this << "constructor()";
	setMovable(true);
	setTabBar(new PlayListTabBar(this));
	connect(
		tabBar(),	SIGNAL(newPlayList()),
		this,		SLOT(newPlayList())
	);
	connect(
		tabBar(),	SIGNAL(closePlayListNr(int)),
		this,		SLOT(closePlayList(int))
	);
	connect(
		tabBar(),	SIGNAL(clearPlayListNr(int)),
		this,		SLOT(clearPlayList(int))
	);

	active=visible=0;

	searchLine=line;

	progressBar=new QProgressBar(this);
	progressBar->hide();
	progressBar->setMinimum(0);
	progressBar->setGeometry(0,this->height()-22,120,22);

	metaResolver=new MetaInfoResolver(this, progressBar);

	setMovable(true);
	setDocumentMode(true);

// 	loadPlayLists();
}

PlayListTabs::~PlayListTabs(){
// 	qDebug() << this << "destructor()";
	disconnect( // I don't know why it isn't working without this
		this,	SIGNAL(currentChanged(int)),
		this,	SLOT(tabChanged(int))
	);

	savePlayLists();

	while(count()){
		QWidget *hlp=widget(0);
		removeTab(0);
		delete hlp;
	}

	delete progressBar;
	delete metaResolver;
}

PlayListWidget* PlayListTabs::ActivePlayList(){
	return active;
}

PlayListWidget* PlayListTabs::VisiblePlayList(){
	return visible;
}

PlayListWidget* PlayListTabs::PlayList(int nr){
	return (PlayListWidget*)widget(nr);
}

PlayListItem* PlayListTabs::ActiveItem(){
	return activeItem;
}

void PlayListTabs::newPlayList(){
// 	qDebug() << this << "newPlayList()";
	PlayListWidget *hlp=newNamedPlayList(QString("Playlist %1").arg(count()+1));
	setCurrentIndex(count()-1);
}

void PlayListTabs::openPlayListFile(){
// 	qDebug() << this << "openPlayListFile()";
	QString playListFilePath=KFileDialog::getOpenFileName(QDesktopServices::storageLocation(QDesktopServices::MusicLocation), i18n("*.m3u *.pls|All Formats(*.m3u, *.pls)\n*.m3u|Winamp playlist (*.m3u)\n*.pls|PLS format (*.pls)"));
	if(!playListFilePath.isEmpty()){
		visible->clear();

		if(playListFilePath.endsWith(".pls"))
			visible->loadPLSPlayList(playListFilePath);

		if(playListFilePath.endsWith(".m3u"))
			visible->loadM3UPlayList(playListFilePath);
	}
}

void PlayListTabs::savePlayListFile(){
// 	qDebug() << this << "savePlayListFile()";
	QString playListFilePath=KFileDialog::getSaveFileName();

	if(!playListFilePath.isEmpty()){
		if(playListFilePath.endsWith(".pls"))
			visible->savePLSPlayList(playListFilePath);
		if(playListFilePath.endsWith(".m3u"))
			visible->saveM3UPlayList(playListFilePath);
	}
}

void PlayListTabs::clearActivePlayList(){
// 	qDebug() << this << "clearActivePlayList()";
	visible->clearPlayList();
}

void PlayListTabs::clearPlayList(int index){
// 	qDebug() << this << "clearPlayList(int index)";
	PlayList(index)->clearPlayList();
}

void PlayListTabs::closeActivePlayList(){
// 	qDebug() << this << "closeActivePlayList()";
	closePlayList(currentIndex());
}

void PlayListTabs::closePlayList(int index){
// 	qDebug() << this << "closePlayList(int index)";
	PlayListWidget *hlp=PlayList(index);

	if(active==PlayList(index)){
		active=0;
		activeItem=0;
	}
	if(visible==PlayList(index)){
		visible=0;
	}

	searchLine->removeTreeWidget(hlp);

	removeTab(index);
	delete hlp;

	if(!count())
		newNamedPlayList(QString("default"));

	if(!visible)
		visible=PlayList(currentIndex());
	if(!active){
		active=visible;
		if(visible->topLevelItemCount())
			activeItem=visible->itemAt(0);
		else
			emit(activeItemExists(false));
	}
}

void PlayListTabs::addFiles(){
// 	qDebug() << this << "addFiles()";
	QStringList files=KFileDialog::getOpenFileNames(QDesktopServices::storageLocation(QDesktopServices::MusicLocation), i18n("*.ogg *.mp3 *.wma|All Formats (*.mp3, *.ogg *.wma)\n*.ogg|Ogg Vorbis (*.ogg)\n*.mp3|MPEG-1 Audio Layer 3 (*.mp3)\n*.wma|Windows Media Audio (*.wma)"));
	if(!files.isEmpty()){
		foreach(QString file, files)
			visible->addFile(file);
	}
}

void PlayListTabs::removeSelected(){
// 	qDebug() << this << "removeSelected()";
	if(visible->selectedItems().contains(activeItem)){
		activeItem=0;
		emit(activeItemExists(false));
	}
	visible->removeSelected();
}

void PlayListTabs::jumpToActive(){
// 	qDebug() << this << "jumpToActive()";
	if(activeItem){
		setCurrentIndex(activeIndex());
		active->scrollToActive();
	}
}

void PlayListTabs::setState(Phonon::State newState, Phonon::State){
// 	qDebug() << this << "setState()";
	if(active){
		switch(newState){
		case Phonon::PlayingState:
			setTabIcon(activeIndex(), KIcon("media-playback-start"));
			if(activeItem) activeItem->setAppearance(true, KIcon("media-playback-start"));
			break;
		case Phonon::PausedState:
			setTabIcon(activeIndex(), KIcon("media-playback-pause"));
			if(activeItem) activeItem->setAppearance(true, KIcon("media-playback-pause"));
			break;
		case Phonon::StoppedState:
			setTabIcon(activeIndex(), KIcon());
			if(activeItem) activeItem->setAppearance(true, KIcon());
			break;
		default:;
		}
	}
}

void PlayListTabs::selectionChanged(){
// 	qDebug() << this << "selectionChanged()";
	emit(enableRemoveAction(!(visible->selectedItems().isEmpty())));
}

void PlayListTabs::playItem(PlayListItem* item){
// 	qDebug() << this << "playItem()";
	setActive(qobject_cast<PlayListWidget*>(sender()), item);
	emit(playSource(item->Source()));
}

void PlayListTabs::getNextSource(){
// 	qDebug() << this << "getNextSource()";
	PlayListItem *givenItem=0;
	PlayListWidget *givenList=0;
	/*switch(playingOrder)*/{
		if(active && activeItem){
			givenItem=active->itemBelow(activeItem);
			givenList=active;
		}
	}

	if(givenItem){
		setActive(givenList, givenItem);
		emit(giveSource(activeItem->Source()));
	}
}

void PlayListTabs::getPreviousSource(){
// 	qDebug() << this << "getPreviousSource()";
	PlayListItem *givenItem=0;
	PlayListWidget *givenList=0;
	/*switch(playingOrder)*/{
		if(active && activeItem){
			givenItem=active->itemAbove(activeItem);
			givenList=active;
		}
	}

	if(givenItem){
		setActive(givenList, givenItem);
		emit(giveSource(activeItem->Source()));
	}
}

void PlayListTabs::getActualSource(){
// 	qDebug() << this << "getActualSource()";
	if(activeItem)
		emit(giveSource(activeItem->Source()));
}

void PlayListTabs::loadPlayLists(){
// 	qDebug() << this << "loadingPlayLists()";
	KConfigGroup playlists(KGlobal::config(), "playlists");

	columnsVisibility << true << true << true << true << false << false << false << true;
	columnsVisibility=playlists.readEntry("columnsVisibility", QList<bool>(columnsVisibility));

	columnsWidth << .03 << .3 << .25 << .3 << .07 << .1 << .05 << 0.03;
	columnsWidth=playlists.readEntry("columnsWidth", QList<float>(columnsWidth));

	for(unsigned int i=0;i<8;++i)
		columnsPosition << i;
	columnsPosition=playlists.readEntry("columnsPosition", QList<unsigned int>(columnsPosition));

	QStringList names=playlists.readEntry("names", QStringList("default"));

	foreach(QString name, names){
		QStringList playlist;
		PlayListWidget *act;
		playlist=playlists.readEntry(name, QStringList());
		act=newNamedPlayList(name);
		act->load();
	}
	setCurrentIndex(playlists.readEntry("lastVisible",0));
	connect(
		this,	SIGNAL(currentChanged(int)),
		this,	SLOT(tabChanged(int))
	);
	tabChanged(currentIndex());

	visible=VisiblePlayList();

	active=PlayList(playlists.readEntry("lastActive",0));
	if(activeItem=active->itemAt(playlists.readEntry("lastPlayed",0)))
		activeItem->setAppearance(true, KIcon());
}

void PlayListTabs::savePlayLists(){
// 	qDebug() << this << "saving PlayLists()";
	KConfigGroup playlists(KGlobal::config(), "playlists");

	playlists.writeEntry("columnsWidth", columnsWidth);
	playlists.writeEntry("columnsVisibility", columnsVisibility);
	playlists.writeEntry("columnsPosition", columnsPosition);

	QStringList names;

	for(int i=0;i<count();++i){
		PlayListWidget *act=(PlayListWidget*)widget(i);
		names.append(act->name());
		act->save();
	}
	playlists.writeEntry("names", names);

	playlists.writeEntry("lastVisible", currentIndex());
	playlists.writeEntry("lastActive", activeIndex());
	if(activeItem)
		playlists.writeEntry("lastPlayed", active->indexOfTopLevelItem(activeItem));
}

void PlayListTabs::setActive(PlayListWidget *widget, PlayListItem *item){
// 	qDebug() << this << "setActive()";
	if(active)
		setTabIcon(activeIndex(), KIcon());
	active=widget;
	setTabIcon(activeIndex(), KIcon("media-playback-start"));

	if(activeItem)
		activeItem->setAppearance(false, KIcon());
	activeItem=item;
	activeItem->setAppearance(true, KIcon("media-playback-start"));

	emit(activeItemExists(true));
	emit(trackStringChanged(activeItem->getTrackString()));
}

void PlayListTabs::tabChanged(int nr){
// 	qDebug() << this << "tabChanged()";
	if(count()){
		if(visible){
			disconnect(
				visible,	SIGNAL(itemSelectionChanged()),
				this,		SLOT(selectionChanged())
			);
		}
		visible=PlayList(nr);
		connect(
			visible,	SIGNAL(itemSelectionChanged()),
			this,		SLOT(selectionChanged())
		);
		visible->refreshConfig();
		visible->setScroll();
		emit(enableRemoveAction(!(visible->selectedItems().isEmpty())));
	}
}

PlayListWidget* PlayListTabs::newNamedPlayList(QString name){
// 	qDebug() << this << "newNamedPlayList()";
	PlayListWidget *hlp=new PlayListWidget(this);
	hlp->setName(name);
	addTab(hlp, name);
	searchLine->addTreeWidget(hlp);
	return hlp;
}

void PlayListTabs::resizeEvent(QResizeEvent *event){
// 	qDebug() << this << "resizeEvent()";
	progressBar->setGeometry(0, this->height()-progressBar->height(), 120, 22);
// 	qDebug() << this << geometry();
	currentWidget()->updateGeometry();
}