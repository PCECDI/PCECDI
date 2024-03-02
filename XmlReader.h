#ifndef XMLREADER_H
#define XMLREADER_H

#include <QtXml>
#include <QFile>
#include <QCoreApplication>
#include <fcntl.h>

class XmlReader
{
public:
    XmlReader(const QString& filePath) : m_filePath(filePath)
    {
        QFile file(m_filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            file.close();
            m_xmlDocument.setContent("<?xml version='1.0' encoding='UTF-8'?><!DOCTYPE xcdi><xcdi version=\"1.0\"><info><progName>PCECDI</progName><progAuthor>TheGordonFreeman42</progAuthor></info><settings><language>fr</language></settings><choices><text>Travailler sur les postes</text><text>Dessiner</text><text>Apprendre</text><text>Lire</text><text>Faire un exposé</text><text>Voir des exposés</text><text>Jouer au jeux de sociétés</text><text>Jouer de la musique</text><text>Faire ses devoirs</text><text>Se connecter à l'ENT</text><text>Jouer à des escape games</text><text>Faire des recherches</text><text>Aider des élèves</text><text>Venir en tant que délégué CDI</text><text>Faire du théâtre</text><text>Aider Mme Noiret</text><text>Exclusion</text><text>Dormir</text><text>S'informer</text><text>Club</text><text>Retard</text><text>Professeur absent</text><text>Rendez-vous médical</text><text>Heure de colle</text></choices></xcdi>");
            saveToFile();
        }
        else
        {
            QByteArray data = file.readAll();
            m_xmlDocument.setContent(data);
            file.close();
        }
        getVersionAttribute();
    }

    void getVersionAttribute()
    {
        QDomElement xcdi = m_xmlDocument.documentElement();

        if(!xcdi.isNull()) {
            QString version = xcdi.attribute("version");
        }
    }

    void ajouterBaliseText(const QString& texte) {
        QDomNodeList nodeList = m_xmlDocument.elementsByTagName("choices");

        if (!nodeList.isEmpty()) {
            QDomElement parentElement = nodeList.at(0).toElement();

            QDomElement ElementDom = m_xmlDocument.createElement("text");
            QDomText newTextNode = m_xmlDocument.createTextNode(texte);
            parentElement.appendChild(ElementDom);
            ElementDom.appendChild(newTextNode);
        }
    }

    QStringList getTextFromChoices()
    {
        QStringList texts;

        QDomNodeList choicesList = m_xmlDocument.elementsByTagName("choices");

        for (int i = 0; i < choicesList.size(); ++i) {
            QDomElement choices = choicesList.at(i).toElement();

            QDomNodeList textList = choices.elementsByTagName("text");

            for (int j = 0; j < textList.size(); ++j) {
                QDomElement text = textList.at(j).toElement();
                texts << text.text();
            }
        }

        return texts;
    }


    QString lireContenuBalise(const QString baliseParent, const QString balise) {
        QDomElement root = m_xmlDocument.documentElement();
        QDomNodeList nodeList = root.elementsByTagName(baliseParent);
        for (int i = 0; i < nodeList.count(); i++) {
            QDomNode node = nodeList.at(i);
            QDomElement infoElement = node.toElement();
            if (infoElement.isNull()) {
                continue;
            }

            QDomElement languageElement = infoElement.firstChildElement(balise);
            if (!languageElement.isNull()) {
                return languageElement.text();
            }
        }

        return "";
    }

    void changeLanguageInSettings(const QString newLanguage) {
        QDomElement root = m_xmlDocument.documentElement();
        QDomNodeList settingsList = root.elementsByTagName("settings");

        for (int i = 0; i < settingsList.size(); i++) {
            QDomElement settings = settingsList.at(i).toElement();
            QDomNodeList languageList = settings.elementsByTagName("language");

            for (int j = 0; j < languageList.size(); j++) {
                QDomElement language = languageList.at(j).toElement();
                language.firstChild().setNodeValue(newLanguage);
            }
        }
    }

    ~XmlReader() {
        saveToFile();
    }

    void saveToFile() {
        QFile file(m_filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            m_xmlDocument.save(stream, 4);
            file.close();
        }
        else
        {
            if(!QDir("Settings").exists()) mkdir("Settings");
            creat(m_filePath.toLatin1(), 0777);
            file.open(QIODevice::WriteOnly);
            QTextStream stream(&file);
            m_xmlDocument.save(stream, 4);
            file.close();
        }
    }

private:
    QDomDocument m_xmlDocument;
    QString m_filePath;
};

#endif
