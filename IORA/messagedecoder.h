#ifndef MESSAGEDECODER_H
#define MESSAGEDECODER_H

#include "QStringList"
#include "serverRequestTypes.h"
#include "QDebug"

struct SmessageData
{
    bool approval;
    int size;
    QStringList elements;
    QString wrong;
    QString description;
    QString source;
    QString destination;
};

class messageDecoder
{
public:
    static SmessageData decode(QString message)
    {
        QStringList tokens = message.split("|");

        int code;
        code = tokens[0].toInt();
        SmessageData data;

        switch(code)
        {
        case serverRequestTypes::verifyCredentials:
        {
            data.approval = tokens[1].toInt();
            break;
        }
        case serverRequestTypes::signIn:
        {
            data.approval = tokens[1].toInt();
            if(data.approval == false)
            {
                data.wrong = tokens[2];
            }
            break;
        }
        case serverRequestTypes::resetPassword:
        {
            data.approval = tokens[1].toInt();
            break;
        }
        case serverRequestTypes::notifications:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::createChannel:
        {
            data.approval = tokens[1].toInt();
            break;
        }
        case serverRequestTypes::belongsChannels:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::channelPosts:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::channelDetails:
        {
            data.description = tokens[1];
            data.size = tokens[2].toInt();
            for( int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+3]);
            }
            break;
        }
        case serverRequestTypes::channelFiles:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::chatMembers:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::chatConversation:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::calendarDetails:
        {
            data.size = tokens[1].toInt();
            for(int i = 0 ; i < data.size ; i++)
            {
                data.elements.push_back(tokens[i+2]);
            }
            break;
        }
        case serverRequestTypes::channelNewPost:
        {
            data.approval = tokens[1].toInt();
            data.description = tokens[2];
            break;
        }
        case serverRequestTypes::channelDownloadFile:
        {
            data.approval = tokens[1].toInt();
            break;
        }
        case serverRequestTypes::chatSendMessage:
        {
            data.approval = tokens[1].toInt();
            data.description = tokens[2];
            break;
        }
        case serverRequestTypes::newChatLiveMessage:
        {
            data.source = tokens[1];
            data.destination = tokens[2];
            data.description = tokens[3];
            break;
        }
        default:
            break;
        }
        return data;
    }

private:
    explicit messageDecoder() { }

};


#endif // MESSAGEDECODER_H
