/***********************************************************************
 * Copyright 2005  Max Howell <max.howell@methylblue.com>
 *           2007  Ian Monroe <ian@monroe.nu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy 
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#ifndef CODEINEPLAYDIALOG_H
#define CODEINEPLAYDIALOG_H

#include <KUrl>
#include <QDialog>

class K3ListView;
class Q3ListViewItem;
class QBoxLayout;

namespace Codeine
{
   class PlayDialog : public QDialog
   {
   Q_OBJECT
   public:
      PlayDialog( QWidget*, bool show_welcome_dialog = false );

      const KUrl &url() const { return m_url; }

      enum DialogCode { FILE = QDialog::Accepted + 2, VCD, CDDA, DVD, RECENT_FILE };

   private slots:
      void done( Q3ListViewItem* );

   private:
      void createRecentFileWidget( QBoxLayout* );

      KUrl m_url;
   };
}

#endif
