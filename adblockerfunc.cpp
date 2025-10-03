#include "adblockerfunc.h"

AdBlockerFunc::AdBlockerFunc() : adBlockingEnabled(false) {}

void AdBlockerFunc::enableAdBlocking() {
    adBlockingEnabled = true;
}

void AdBlockerFunc::disableAdBlocking() {
    adBlockingEnabled = false;
}

bool AdBlockerFunc::isAdBlockingEnabled() const {
    return adBlockingEnabled;
}

void AdBlockerFunc::loadAdDomainList(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty() && !line.startsWith("#")) {
            adDomainList.append(line);
        }
    }

    file.close();
}

bool AdBlockerFunc::isAdDomain(const QString& domain) {
    for (const QString& pattern : adDomainList) {
        QRegularExpression regex(pattern, QRegularExpression::CaseInsensitiveOption);
        if (regex.match(domain).hasMatch()) {
            return adBlockingEnabled;
        }
    }
    return false;
}

void AdBlockerFunc::blockDNSRequest(const QString& domain) {
    if (isAdDomain(domain)) {
        logBlockedRequest(domain);
    }
}

void AdBlockerFunc::logBlockedRequest(const QString& domain) {
    blockedLog[domain] = QDateTime::currentDateTime();

    QJsonObject logEntry;
    logEntry["domain"] = domain;
    logEntry["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QFile file("blocked_log.json");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        file.write(QJsonDocument(logEntry).toJson());
        file.close();
    }
}

QStringList AdBlockerFunc::getBlockedDomains() const {
    return blockedLog.keys();
}

int AdBlockerFunc::getBlockCount() const {
    return blockedLog.size();
}
