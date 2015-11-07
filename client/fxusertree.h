/***************************************************************************
 *   Copyright (C) 2008 by DDD                                             *
 *   dedodong@163.com                                                      *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef FXUSERTREE_H_
#define FXUSERTREE_H_

#include <QTreeWidget>
#include "fxdebug.h"

namespace fxgui
{

class FxUserTree: public QTreeWidget
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER

    public:
        FxUserTree(QWidget *parent = 0) :
            QTreeWidget(parent)
        {
            normalSize = QSize(30, 16);
            clickedSize = QSize(70, 40);
        }

    private:
        QSize clickedSize;
        QSize normalSize;

    private slots:
        void onCurrentItemChanged(QTreeWidgetItem* current,
                QTreeWidgetItem * previous)
        {
            if (previous)
            {
                if (previous->parent())
                {
                    previous->setSizeHint(0, normalSize);
                }
            }
            if (current)
            {
                if (current->parent())
                {
                    current->setSizeHint(0, clickedSize);
                }
            }
            updateGeometries();
        }

        void onItemClicked(QTreeWidgetItem * /*item*/, int /*column*/)
        {
        }
};

}
#endif

