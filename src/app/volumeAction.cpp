// (C) 2005 Max Howell (max.howell@methylblue.com)
// See COPYING file for licensing information

#include <kactioncollection.h>
#include <klocale.h>
#include <ktoolbar.h>
#include <qevent.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qslider.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3Frame>

#include "debug.h"
#include "volumeAction.h"
#include "volumeAction.moc"
#include "xineEngine.h"


class VolumeSlider : public Q3Frame
{
public:
    VolumeSlider( QWidget *parent )
            : Q3Frame( parent )
    {
        slider = new QSlider( Qt::Vertical, this, "volume" );
        label = new QLabel( this );

        Q3BoxLayout *lay = new Q3VBoxLayout( this );
        lay->addWidget( slider, 0, Qt::AlignHCenter );
        lay->addWidget( label, 0, Qt::AlignHCenter );
        lay->setMargin( 4 );

        slider->setRange( 0, 100 );

        setFrameStyle( Q3Frame::Plain | Q3Frame::Box );
        setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );

        hide();
    }

    QLabel *label;
    QSlider *slider;
};


VolumeAction::VolumeAction( KToolBar *bar, KActionCollection *ac )
        : KToggleAction( i18n("Volume"), ac )
        , m_anchor( 0 )
{
//KToggleAction( i18n("Volume"), "volume", Qt::Key_1, 0, 0, ac, "volume" )
    setObjectName( "volume" );
    setShortcut( Qt::Key_1 );
    m_widget = new VolumeSlider( bar->topLevelWidget() );
    ac->addAction( objectName(), this );
    connect( this, SIGNAL(toggled( bool )), SLOT(toggled( bool )) );
    connect( m_widget->slider, SIGNAL(sliderMoved( int )), SLOT(sliderMoved( int )) );
    connect( m_widget->slider, SIGNAL(sliderMoved( int )), Codeine::engine(), SLOT(setStreamParameter( int )) );
    connect( m_widget->slider, SIGNAL(sliderReleased()), SLOT(sliderReleased()) );
}

QWidget*
VolumeAction::createWidget( QWidget *parent )
{
     DEBUG_BLOCK
     QWidget* ret = KToggleAction::createWidget( parent );
     m_anchor = qobject_cast<QWidget*>(parent->child( "toolbutton_volume" )); //KAction creates it with this name
     if( m_anchor )
          m_anchor->installEventFilter( this ); //so we can keep m_widget anchored
     else
          warning() << "there is no spoon! or toolbutton_volume." << endl;

    return ret;
}

void
VolumeAction::toggled( bool const b )
{
    DEBUG_BLOCK

    m_widget->raise();
    m_widget->setShown( b );
}

void
VolumeAction::sliderMoved( int v )
{
    v = 100 - v; //Qt sliders are wrong way round when vertical

    QString const t = QString::number( v ) + '%';

    setToolTip( i18n( "Volume: %1" ).arg( t ) );
    m_widget->label->setText( t );
}

bool
VolumeAction::eventFilter( QObject *o, QEvent *e )
{
    switch (e->type()) {
        case QEvent::Move:
        case QEvent::Resize: {
            QWidget const * const &a = m_anchor;

            m_widget->move( a->mapTo( m_widget->parentWidget(), QPoint( 0, a->height() ) ) );
            m_widget->resize( a->width(), m_widget->sizeHint().height() );
            return false;
        }

        //TODO one click method, flawed currently in fullscreen mode by palette change in mainwindow.cpp
/*        case QEvent::MouseButtonPress:
            m_widget->show();
            break;

        case QEvent::MouseButtonRelease:
            m_widget->hide();
            break;*/

        default:
            return false;
    }
}
//#include "volumeAction.moc"