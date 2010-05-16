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

#include <KAboutData>

#include "ursusapp.h"

int main(int argc, char *argv[]){
	KAboutData aboutData("ursus",
						 0,
						 ki18n("Ursus"),
						 "0.001",
						 ki18n("Music player similar to foobar2000 and Amarok 1.4"),
						 KAboutData::License_GPL,
						 ki18n("2008"),
						 ki18n("Music player"),
						 "http://", // TODO
						 "mpilhoo@gmail.com");

	aboutData.addAuthor(ki18n("Michał Pilch (8siem)"), ki18n("Main Developer"), "mpilhoo@gmail.com");

	KCmdLineArgs::init(argc, argv, &aboutData);

	if (!UrsusApp::start()) {
       fprintf(stderr, "Ursus is already running!\n");
       return 0;
    }
	UrsusApp app;
	return app.exec();
}
