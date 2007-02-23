// (c) 2004 Max Howell (max.howell@methylblue.com)
// See COPYING file for licensing information

#include "codeine.h"
#include "mainWindow.h"

#include <kaboutdata.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <klocalizedstring.h>

#include <X11/Xlib.h>


static KAboutData aboutData( APP_NAME,
        I18N_NOOP(PRETTY_NAME), APP_VERSION,
        I18N_NOOP("A video player that has a usability focus"), KAboutData::License_GPL_V2,
        I18N_NOOP("Copyright 2006, Max Howell\nCopyright 2007, Ian Monroe"), 0,
        "http://www.methylblue.com/codeine/",
        "codeine@monroe.nu" );

static const KCmdLineOptions options[] = {
    { "+[URL]", I18N_NOOP( "Play 'URL'" ), 0 },
    { "play-dvd", I18N_NOOP( "Play DVD Video" ), 0 },
    { 0, 0, 0 } };

int
main( int argc, char **argv )
{
    //we need to do this, says adrianS from SuSE
//    if( !XInitThreads() )
//        return 1;

    aboutData.addCredit( "Mike Diehl", I18N_NOOP("Handbook") );
    aboutData.addCredit( "The Kaffeine Developers", I18N_NOOP("Great reference code") );
    aboutData.addCredit( "Greenleaf", I18N_NOOP("Yatta happened to be the only video on my laptop to test with. :)") );
    aboutData.addCredit( "David Vignoni", I18N_NOOP("The current Codeine icon") );


    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineArgs::addCmdLineOptions( options );

    KApplication application;
    int returnValue;

    {
        Codeine::MainWindow mainWindow;
        mainWindow.show();

        returnValue = application.exec();
    }

    return returnValue;
}
