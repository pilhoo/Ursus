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

#ifndef URSUS_MAIN_WIN_H
#define URSUS_MAIN_WIN_H
#include <KXmlGuiWindow>
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KGlobalAccel>
#include <KStandardAction>
#include <KVBox>
#include <KIcon>
#include <KTreeWidgetSearchLineWidget>
#include <QStringList>
#include <QLabel>
#include <Phonon/VolumeSlider>
#include <Phonon/SeekSlider>
#include <QDesktopServices>
#include <QSplitter>
#include <QComboBox>
// #include <KIO/NetAccess>
// #include <KSaveFile>
// #include <KMessageBox>
#include "player.h"
#include "playlisttabs.h"
#include "trayicon.h"

#include <KDebug>

class UrsusMainWin : public KXmlGuiWindow {
	Q_OBJECT
public:
	UrsusMainWin(UrsusPlayer *player_);
	~UrsusMainWin();
	inline PlayListTabs* plTabs(){ return playListTabs; }
	void setTrayIcon(UrsusTrayIcon *_trayIcon);
public slots:
	void tick(qint64 time);
	void stateChanged(Phonon::State newState, Phonon::State /*oldState*/);
	void enableRemoveAction(bool enable);
	void volumeChanged(qreal vol);
	void mute();
	void setTrackString(QString trackString);
	void setActionsEnabled(bool);
private:
	KAction	*actionPrevious,
 			*actionPlay,
			*actionPause,
			*actionStop,
			*actionNext,
			*actionSearchInPlaylist,
			*actionClearPlaylist,
			*actionClosePlaylist,
			*actionNewPlaylist,
   			*actionOpenPlaylist,
   			*actionSavePlaylist,
			*actionAddToPlaylist,
			*actionRemoveFromPlaylist,
			*actionPlayingMode,
// 			*actionUndo,
// 			*actionRedo,
			*actionJump,
			*actionVolumeSlider,
			*actionVolumeLabel,
			*actionMute,
			*actionSeek;
	bool m_actionsDisabled;

	PlayListTabs *playListTabs;
	KTreeWidgetSearchLineWidget *playListSearchLine;
	QSplitter *splitter;

	QComboBox *playingModeCombo;

	Phonon::VolumeSlider *volumeSlider;
	QLabel *volumeLabel;
	Phonon::SeekSlider	*seekSlider;

	UrsusPlayer *player;
	UrsusTrayIcon *trayIcon;

	qreal volume;
	QString m_trackString;

  	void setupActions();
	void addFilesToPlayList(QStringList &files);
	void savePlayLists();
	void loadPlayLists();
};

#endif