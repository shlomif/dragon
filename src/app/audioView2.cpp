#include "audioView2.h"
#include "ui_audioView2.h"

#include <KFontSizeAction>

#include "theStream.h"
#include "videoWindow.h"

namespace Dragon {

AudioView2::AudioView2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioView2)
{
    ui->setupUi(this);
    engine()->setupAnalyzer(ui->m_analyzer);
    connect(engine(), SIGNAL(metaDataChanged()), this, SLOT(update()));
}

AudioView2::~AudioView2()
{
    delete ui;
}

void AudioView2::enableDemo(bool enable)
{
    ui->m_analyzer->enableDemo(enable);
}

void AudioView2::update()
{
    ui->m_artist->setText( TheStream::metaData( Phonon::ArtistMetaData ) );
    ui->m_album->setText( TheStream::metaData( Phonon::AlbumMetaData ) );
    QString trackString;
    {
        QString trackName = TheStream::metaData( Phonon::TitleMetaData );
        QString trackNumber = TheStream::metaData( Phonon::TracknumberMetaData );
        bool okInt = false;
        if ( trackNumber.toInt(&okInt) > 0 && okInt)
        {
            trackString =  QString( trackNumber + QLatin1String(" - ") + trackName );
        }
        else
            trackString = trackName;
    }
    ui->m_track->setText( trackString );
//    { //somewhat of a longshot: try to find Amarok cover for the music
//        QString imagePath = checkForAmarokImage( artist, album );
//        if(imagePath.isNull())
//        {
//            delete m_image;
//            m_image = 0;
//            m_layout->setColumnFixedWidth(0, 0.0);
//        }
//        else
//        {
//            m_layout->setColumnFixedWidth(0, COVER_COLUMN_WIDTH);
//            if(!m_image)
//            {
//                m_image = new QGraphicsPixmapItem();
//                scene()->addItem( m_image );
//                m_image->setPos( 3.0, 3.0 );
//            }
//            QPixmap cover( imagePath );
//            m_image->setPixmap( cover );
//            qreal width = static_cast<qreal>( cover.width() );
//            qreal scale = COVER_WIDTH / width;
//            m_image->setScale( scale );
//        }
//    }
}


void AudioView2::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

} // namespace Dragon