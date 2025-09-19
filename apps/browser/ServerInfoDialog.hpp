#ifndef NEWLAUNCHER_SERVERINFODIALOG_HPP
#define NEWLAUNCHER_SERVERINFODIALOG_HPP

#include "ui_ServerInfo.h"
#include <apps/browser/netutils/Utils.hpp>
#include <RakNetTypes.h>
#include <components/openmw-mp/Master/MasterData.hpp>

class ThrWorker;

class ServerInfoDialog : public QDialog,  public Ui::Dialog
{
    Q_OBJECT
public:
    explicit ServerInfoDialog(const QString &addr, QWidget *parent = nullptr);
    ~ServerInfoDialog() override;
    bool isUpdated();
    void setData(std::pair<RakNet::SystemAddress, QueryData> &newSD);
public slots:
    void refresh();
    int exec() Q_DECL_OVERRIDE;
private:
    QThread *refreshThread;
    ThrWorker* worker;
    std::pair<RakNet::SystemAddress, QueryData> sd;
};

class ThrWorker: public QObject
{
    friend class ServerInfoDialog;
Q_OBJECT
public:
    ThrWorker(ServerInfoDialog *dialog, QString addr, unsigned short port);

public slots:
    void process();
signals:
    void finished();
private:
    QString addr;
    unsigned short port;
    bool stopped;
    ServerInfoDialog *dialog;
};


#endif //NEWLAUNCHER_SERVERINFODIALOG_HPP
