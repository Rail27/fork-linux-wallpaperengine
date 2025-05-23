#include <csignal>
#include <iostream>

#include "WallpaperEngine/Application/CApplicationContext.h"
#include "WallpaperEngine/Application/CWallpaperApplication.h"
#include "WallpaperEngine/Logging/CLog.h"

WallpaperEngine::Application::CWallpaperApplication* app;

void signalhandler(int sig) {
    if (app == nullptr)
        return;

    app->signal (sig);
}

void initLogging () {
    sLog.addOutput (new std::ostream (std::cout.rdbuf ()));
    sLog.addError (new std::ostream (std::cerr.rdbuf ()));
}

int main (int argc, char* argv[]) {
    try {
        // if type parameter is specified, this is a subprocess, so no logging should be enabled from our side
        bool enableLogging = true;
        std::string typeZygote = "--type=zygote";
        std::string typeUtility = "--type=utility";

        for (int i = 1; i < argc; i ++) {
            if (strncmp (typeZygote.c_str(), argv[i], typeZygote.size()) == 0) {
                enableLogging = false;
                break;
            } else if (strncmp (typeUtility.c_str(), argv[i], typeUtility.size()) == 0) {
                enableLogging = false;
                break;
            }
        }

        if (enableLogging) {
            initLogging ();
        }

        WallpaperEngine::Application::CApplicationContext appContext (argc, argv);

        // halt if the list-properties option was specified
        if (appContext.settings.general.onlyListProperties)
            return 0;

        app = new WallpaperEngine::Application::CWallpaperApplication (appContext);

        // attach signals to gracefully stop
        std::signal (SIGINT, signalhandler);
        std::signal (SIGTERM, signalhandler);
        std::signal (SIGKILL, signalhandler);

        // show the wallpaper application
        app->show ();

        // remove signal handlers before destroying app
        std::signal (SIGINT, SIG_DFL);
        std::signal (SIGTERM, SIG_DFL);
        std::signal (SIGKILL, SIG_DFL);

        delete app;

        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what () << std::endl;
        return 1;
    }
}