#ifndef ADBLOCKERFUNC_H
#define ADBLOCKERFUNC_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QDateTime>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>

class AdBlockerFunc {
public:
    AdBlockerFunc();

    void enableAdBlocking();
    void disableAdBlocking();
    bool isAdBlockingEnabled() const;

    void loadAdDomainList(const QString& filePath);
    bool isAdDomain(const QString& domain);
    void blockDNSRequest(const QString& domain);
    void logBlockedRequest(const QString& domain);
    QStringList getBlockedDomains() const;
    int getBlockCount() const;

private:
    bool adBlockingEnabled;
    QStringList adDomainList;
    QMap<QString, QDateTime> blockedLog;
};

#endif // ADBLOCKERFUNC_H
