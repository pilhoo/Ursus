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

#include "mainwin.h"
// #include <QDebug>

UrsusMainWin::UrsusMainWin(UrsusPlayer *player_){
// 	qDebug() << this << "constructor()";
	KConfigGroup config(KGlobal::config(), "player");
	// Ui
	playListSearchLine=new KTreeWidgetSearchLineWidget();
	playListSearchLine->setMinimumWidth(120);

	splitter=new QSplitter(this);
	playListTabs=new PlayListTabs(this, playListSearchLine->searchLine());
	splitter->addWidget(playListTabs);

	player=player_;
	trayIcon=NULL;

	// Volume
	volumeSlider=new Phonon::VolumeSlider();
	volumeSlider->setAudioOutput(player->Output());
	volumeSlider->setMinimumWidth(80);
	volumeSlider->setMuteVisible(false);

	volumeLabel=new QLabel();
	volumeLabel->setText("100%");
	volumeLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	volume=config.readEntry("volume", 1.);

	// Seek
	seekSlider=new Phonon::SeekSlider();
	seekSlider->setMinimumWidth(120);
	seekSlider->setIconVisible(false);
	seekSlider->setMediaObject(player->Object());
	seekSlider->setTracking(false);

	playingModeCombo=new QComboBox(this);
	playingModeCombo->addItem(KIcon("view-media-playlist"), QString("Normal"));
// 	playingModeCombo->addItem(KIcon("shuffle-track"), QString("Shuffle Track"));
// 	playingModeCombo->addItem(KIcon("shuffle-album"), QString("Shuffle Album"));
// 	playingModeCombo->addItem(KIcon("repeat-list"), QString("Repeat List"));
// 	playingModeCombo->addItem(KIcon("repeat-album"), QString("Repeat Album"));
// 	playingModeCombo->addItem(KIcon("repeat-track"), QString("Repeat Track"));
	playingModeCombo->setCurrentIndex(config.readEntry("playingMode", 0));

	setCentralWidget(splitter);

	setupActions();
	setupGUI();
	setStatusBar(NULL);

	m_trackString="";
// 	disableActions();

	connect(
		player->Object(),	SIGNAL(stateChanged(Phonon::State, Phonon::State)),
		this,				SLOT(stateChanged(Phonon::State, Phonon::State))
	);
	connect(
		player->Object(),	SIGNAL(stateChanged(Phonon::State, Phonon::State)),
		playListTabs,		SLOT(setState(Phonon::State, Phonon::State))
	);
	connect(
		player->Object(),	SIGNAL(aboutToFinish()),
		playListTabs,		SLOT(getNextSource())
	);
	connect(
		player,			SIGNAL(needNextSource()),
		playListTabs,	SLOT(getNextSource())
	);
	connect(
		player,			SIGNAL(needPreviousSource()),
		playListTabs,	SLOT(getPreviousSource())
	);
	connect(
		player,			SIGNAL(needActualSource()),
		playListTabs,	SLOT(getActualSource())
	);
	connect(
		playListTabs,	SIGNAL(playSource(Phonon::MediaSource&)),
		player,			SLOT(play(Phonon::MediaSource&))
	);
	connect(
		playListTabs,	SIGNAL(giveSource(Phonon::MediaSource&)),
		player,			SLOT(enqueue(Phonon::MediaSource&))
	);
	connect(
		playListTabs,	SIGNAL(enableRemoveAction(bool)),
		this,			SLOT(enableRemoveAction(bool))
	);
	connect(
		playListTabs,	SIGNAL(trackStringChanged(QString)),
		this,			SLOT(setTrackString(QString))
	);
	connect(
		playListTabs,	SIGNAL(activeItemExists(bool)),
		this,			SLOT(setActionsEnabled(bool))
	);
	connect(
		player->Output(),	SIGNAL(volumeChanged(qreal)),
		this,				SLOT(volumeChanged(qreal))
	);

	player->Output()->setVolume(volume);
}

UrsusMainWin::~UrsusMainWin(){
// 	qDebug() << this << "destructor()";
	KConfigGroup config(KGlobal::config(), "player");
	config.writeEntry("volume", volume);
	config.writeEntry("playingMode", playingModeCombo->currentIndex());

	if(trayIcon){
		disconnect(
			playListTabs,	SIGNAL(trackStringChanged(QString)),
			trayIcon,		SLOT(setTrackString(QString))
		);
	}

	delete playListSearchLine;
	delete playListTabs;
	delete volumeSlider;
	delete volumeLabel;
}

void UrsusMainWin::setTrayIcon(UrsusTrayIcon *_trayIcon){
// 	qDebug() << this << "setTrayIcon()";
	trayIcon=_trayIcon;
	connect(
		playListTabs,	SIGNAL(trackStringChanged(QString)),
		trayIcon,		SLOT(setTrackString(QString))
	);
}

void UrsusMainWin::setupActions(){
// 	qDebug() << this << "setupActions()";
	// Actions
	actionPrevious=new KAction(this);
	actionPrevious->setText(i18n("Previous"));
	actionPrevious->setIcon(KIcon("media-skip-backward"));
	actionCollection()->addAction("previous", actionPrevious);
	connect(
		actionPrevious,	SIGNAL(triggered(bool)),
		player,			SLOT(previous())
	);
	actionPrevious->setGlobalShortcut(KShortcut(Qt::META+Qt::Key_Z));

	actionPlay=new KAction(this);
	actionPlay->setText(i18n("Play"));
	actionPlay->setIcon(KIcon("media-playback-start"));
	actionCollection()->addAction("play", actionPlay);
	connect(
		actionPlay,	SIGNAL(triggered(bool)),
		player,		SLOT(play())
	);
	actionPlay->setGlobalShortcut(KShortcut(Qt::META+Qt::Key_X));

	actionPause=new KAction(this);
	actionPause->setText(i18n("Pause"));
	actionPause->setIcon(KIcon("media-playback-pause"));
	actionCollection()->addAction("pause", actionPause);
	actionPause->setEnabled(false);
	connect(
		actionPause,	SIGNAL(triggered(bool)),
		player,			SLOT(pause())
	);
	actionPause->setGlobalShortcut(KShortcut(Qt::META+Qt::Key_C));

	actionStop=new KAction(this);
	actionStop->setText(i18n("Stop"));
	actionStop->setIcon(KIcon("media-playback-stop"));
	actionStop->setEnabled(false);
	actionCollection()->addAction("stop", actionStop);
	connect(
		actionStop,	SIGNAL(triggered(bool)),
		player,		SLOT(stop())
	);
	actionStop->setGlobalShortcut(KShortcut(Qt::META+Qt::Key_V));

	actionNext=new KAction(this);
	actionNext->setText(i18n("Next"));
	actionNext->setIcon(KIcon("media-skip-forward"));
	actionCollection()->addAction("next", actionNext);
	connect(
		actionNext,	SIGNAL(triggered(bool)),
		player,		SLOT(next())
	);
	actionNext->setGlobalShortcut(KShortcut(Qt::META+Qt::Key_B));

	// Playlist
	actionSearchInPlaylist=new KAction(this);
	actionSearchInPlaylist->setText(i18n("Search"));
	actionCollection()->addAction("playlist search", actionSearchInPlaylist);
	actionSearchInPlaylist->setDefaultWidget(playListSearchLine);

	actionClearPlaylist=new KAction(this);
	actionClearPlaylist->setText(i18n("Clear Playlist"));
	actionClearPlaylist->setIcon(KIcon("edit-clear-list"));
	actionCollection()->addAction("clearplaylist", actionClearPlaylist);
	connect(
		actionClearPlaylist,	SIGNAL(triggered(bool)),
		playListTabs,			SLOT(clearActivePlayList())
	);

	actionClosePlaylist=new KAction(this);
	actionClosePlaylist->setText(i18n("Close Playlist"));
	actionClosePlaylist->setIcon(KIcon("tab-close"));
// 	actionNewPlaylist->setShortcut(Qt::CTRL+Qt::Key_W);
	actionCollection()->addAction("closeplaylist", actionClosePlaylist);
	connect(
		actionClosePlaylist,	SIGNAL(triggered(bool)),
		playListTabs,			SLOT(closeActivePlayList())
	);

	actionNewPlaylist=new KAction(this);
	actionNewPlaylist->setText(i18n("New Playlist"));
	actionNewPlaylist->setIcon(KIcon("tab-new"));
	actionNewPlaylist->setShortcut(Qt::CTRL+Qt::Key_N);
	actionCollection()->addAction("newplaylist", actionNewPlaylist);
	connect(
		actionNewPlaylist,	SIGNAL(triggered(bool)),
		playListTabs,		SLOT(newPlayList())
	);

	actionOpenPlaylist=new KAction(this);
	actionOpenPlaylist->setText(i18n("Open Playlist"));
	actionOpenPlaylist->setIcon(KIcon("document-open"));
	actionOpenPlaylist->setShortcut(Qt::CTRL+Qt::Key_O);
	actionCollection()->addAction("openplaylist", actionOpenPlaylist);
	connect(
		actionOpenPlaylist,	SIGNAL(triggered(bool)),
		playListTabs,		SLOT(openPlayListFile())
	);

	actionSavePlaylist=new KAction(this);
	actionSavePlaylist->setText(i18n("Save Playlist"));
	actionSavePlaylist->setIcon(KIcon("document-save"));
	actionSavePlaylist->setShortcut(Qt::CTRL+Qt::Key_S);
	actionCollection()->addAction("saveplaylist", actionSavePlaylist);
	connect(
		actionSavePlaylist,	SIGNAL(triggered(bool)),
		playListTabs,		SLOT(savePlayListFile())
	);

	KAction *actionAddToPlaylist=new KAction(this);
	actionAddToPlaylist->setText(i18n("Add Multimedia"));
	actionAddToPlaylist->setIcon(KIcon("list-add"));
// 	actionAddToPlaylist->setShortcut(Qt::META+Qt::Key_A);
	actionCollection()->addAction("addtoplaylist", actionAddToPlaylist);
	connect(
		actionAddToPlaylist,	SIGNAL(triggered(bool)),
		playListTabs,			SLOT(addFiles())
	);

	actionRemoveFromPlaylist=new KAction(this);
	actionRemoveFromPlaylist->setText(i18n("Remove from Playlist"));
	actionRemoveFromPlaylist->setIcon(KIcon("list-remove"));
	actionRemoveFromPlaylist->setShortcut(Qt::Key_Delete);
	actionRemoveFromPlaylist->setEnabled(false);
	actionCollection()->addAction("removefromplaylist", actionRemoveFromPlaylist);
	connect(
		actionRemoveFromPlaylist,	SIGNAL(triggered(bool)),
		playListTabs,				SLOT(removeSelected())
	);

// 	actionUndo=new KAction(this);
// 	actionUndo->setText(i18n("Undo"));
// 	actionUndo->setIcon(KIcon("edit-undo"));
// 	actionUndo->setShortcut(Qt::CTRL+Qt::Key_Z);
// 	actionCollection()->addAction("undo", actionUndo);
// 	// TODO connect actionUndo
//
// 	actionRedo=new KAction(this);
// 	actionRedo->setText(i18n("Redo"));
// 	actionRedo->setIcon(KIcon("edit-redo"));
// 	actionRedo->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_Z);
// 	actionCollection()->addAction("redo", actionRedo);
// 	// TODO connect actionRedo

	actionJump=new KAction(this);
	actionJump->setText(i18n("Jump to Actual"));
	actionJump->setIcon(KIcon("go-jump"));
	actionJump->setShortcut(Qt::ALT+Qt::Key_A);
	actionCollection()->addAction("jump", actionJump);
	connect(actionJump, SIGNAL(triggered(bool)), playListTabs, SLOT(jumpToActive()));

	// Volume
	actionVolumeSlider=new KAction(this);
	actionVolumeSlider->setText(i18n("Volume Control"));
	actionCollection()->addAction("volume slider", actionVolumeSlider);
	actionVolumeSlider->setDefaultWidget(volumeSlider);

	actionMute=new KAction(this);
	actionMute->setText(i18n("Mute"));
	actionMute->setIcon(KIcon("audio-volume-high"));
	actionMute->setShortcut(Qt::Key_VolumeMute);
	actionCollection()->addAction("mute", actionMute);
	connect(actionMute, SIGNAL(triggered(bool)), this, SLOT(mute()));

	actionVolumeLabel=new KAction(this);
	actionVolumeLabel->setText(i18n("Volume Label"));
	actionCollection()->addAction("volume label", actionVolumeLabel);
	actionVolumeLabel->setDefaultWidget(volumeLabel);
	// Seek
	actionSeek=new KAction(this);
	actionSeek->setText(i18n("Seek Slider"));
	actionCollection()->addAction("seekslider", actionSeek);
	actionSeek->setDefaultWidget(seekSlider);

	// Playing Mode
	actionPlayingMode=new KAction(this);
	actionPlayingMode->setText(i18n("Playing Mode"));
	actionCollection()->addAction("playingmode", actionPlayingMode);
	actionPlayingMode->setDefaultWidget(playingModeCombo);
	playingModeCombo->setMaximumHeight(24);
// 	connect(playingModeCombo, SIGNAL(activated(int)), playListWidget, SLOT(setPlayingMode(int)));
}

void UrsusMainWin::tick(qint64 time){
// 	qDebug() << this << "tick()";
	kDebug() << time;
	// TODO some time label
}

void UrsusMainWin::stateChanged(Phonon::State newState, Phonon::State /*oldState*/){
// 	qDebug() << this << "stateChanged()";
	kDebug() << "State Changed";
	switch (newState) {
		case Phonon::ErrorState:
			if (player->Object()->errorType() == Phonon::FatalError) {
				kDebug() << "FATAL ERROR!!!";
			} else {
				kDebug() << "ERROR";
			}
			break;
		case Phonon::PlayingState:
			actionPlay->setEnabled(true);
			actionPause->setEnabled(true);
			actionStop->setEnabled(true);
			if(trayIcon){

			}
			setWindowTitle(QString("Ursus: ")+m_trackString);
			break;
		case Phonon::StoppedState:
			actionStop->setEnabled(false);
			actionPause->setEnabled(false);
			actionPlay->setEnabled(true);
			setWindowTitle(QString("Ursus"));
			break;
		case Phonon::PausedState:
			actionPause->setEnabled(false);
			actionStop->setEnabled(true);
			actionPlay->setEnabled(true);
			break;
		case Phonon::BufferingState:
			kDebug() << "Buffering";
			break;
		default:;
	}
}

void UrsusMainWin::enableRemoveAction(bool enable){
// 	qDebug() << this << "enableRemoveAction()";
	actionRemoveFromPlaylist->setEnabled(enable);
}

void UrsusMainWin::volumeChanged(qreal vol){
// 	qDebug() << this << "volumeChanged()";
	volumeLabel->setText(QString("%1").arg(vol*100)+"%");
	if(!player->Output()->isMuted()){
		if(vol>0.6)
			actionMute->setIcon(KIcon("audio-volume-high"));
		else if(vol>0.3)
			actionMute->setIcon(KIcon("audio-volume-medium"));
		else if(vol>0.)
			actionMute->setIcon(KIcon("audio-volume-low"));
		else
			actionMute->setIcon(KIcon("audio-volume-muted"));
	}
	volume=vol;
}

void UrsusMainWin::mute(){
// 	qDebug() << this << "mute()";
	if(player->Output()->isMuted()){
		player->Output()->setMuted(false);
		volumeChanged(volume);
	}else{
		player->Output()->setMuted(true);
		actionMute->setIcon(KIcon("audio-volume-muted"));
	}
}

void UrsusMainWin::setTrackString(QString trackString){
// 	qDebug() << this << "setTrackString()";
	m_trackString=trackString;

	if(actionStop->isEnabled())
		setWindowTitle(QString("Ursus: ")+m_trackString);
}

void UrsusMainWin::setActionsEnabled(bool enabled){
// 	qDebug() << this << "setActionsEnabled()";
	m_actionsDisabled=!enabled;
	actionStop->setEnabled(enabled);
	actionPause->setEnabled(enabled);
	actionPlay->setEnabled(enabled);
	actionPrevious->setEnabled(enabled);
	actionNext->setEnabled(enabled);
}
