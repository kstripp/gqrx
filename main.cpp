/* -*- c++ -*- */
/*
 * Copyright 2011 Alexandru Csete OZ9AEC.
 *
 * Gqrx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Gqrx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gqrx; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#include <QtGui/QApplication>
#include <QSettings>
#include <QDebug>
#include "qtgui/ioconfig.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("OZ9AEC");
    QCoreApplication::setOrganizationDomain("oz9aec.net");
    QCoreApplication::setApplicationName("GQRX");
    QCoreApplication::setApplicationVersion("2.0");

    // we need at least an input device configured for FCD
    QSettings settings;

    if (!settings.contains("input")) {

        CIoConfig *ioconf = new CIoConfig();
        int confres = ioconf->exec();

        delete ioconf;

        if (confres == QDialog::Rejected) {
            qDebug() << "I/O device configuration cancelled.";
            return 0;
        }
    }

    // We should now have at least an input device configured
    // and MainWindow will pick that up.
    MainWindow w;
    w.show();

    return a.exec();
}
