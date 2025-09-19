#include <QApplication>
#include <components/settings/settings.hpp>
#include <components/files/configurationmanager.hpp>
#include <apps/browser/netutils/QueryClient.hpp>
#include "MainWindow.hpp"

std::string loadSettings (Settings::Manager & settings)
{
    Files::ConfigurationManager mCfgMgr;
    // Create the settings manager and load default settings file
    const std::string localdefault = (mCfgMgr.getLocalPath() / "tes3mp-client-default.cfg").string();
    const std::string globaldefault = (mCfgMgr.getGlobalPath() / "tes3mp-client-default.cfg").string();

    // prefer local
    if (boost::filesystem::exists(localdefault))
        settings.loadDefault(localdefault, false);
    else if (boost::filesystem::exists(globaldefault))
        settings.loadDefault(globaldefault, false);
    else
        throw std::runtime_error ("No default settings file found! Make sure the file \"tes3mp-client-default.cfg\" was properly installed.");

    // load user settings if they exist
    const std::string settingspath = (mCfgMgr.getUserConfigPath() / "tes3mp-client.cfg").string();
    if (boost::filesystem::exists(settingspath))
        settings.loadUser(settingspath);

    return settingspath;
}

int main(int argc, char *argv[])
{
    Settings::Manager mgr;

    loadSettings(mgr);

    std::string addr = mgr.getString("address", "Master");
    int port = mgr.getInt("port", "Master");

    // Is this an attempt to connect to the official master server at the old port? If so,
    // redirect it to the correct port for the currently used fork of RakNet
    if (Misc::StringUtils::ciEqual(addr, "master.tes3mp.com") && port == 25560)
        port = 25561;

    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QueryClient::Get().SetServer(addr, port);
    QApplication app(argc, argv);
    MainWindow d;

    d.show();
    return app.exec();
}
