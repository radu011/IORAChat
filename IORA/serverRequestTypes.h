#ifndef SERVERREQUESTTYPES_H
#define SERVERREQUESTTYPES_H

enum serverRequestTypes {
    verifyCredentials = 0,
    signIn = 1,
    resetPassword = 2,
    notifications = 3,
    createChannel = 4,
    belongsChannels = 5,
    channelPosts = 6,
    channelDetails = 7,
    channelFiles = 8,
    chatMembers = 9,
    chatConversation = 10,
    calendarDetails = 11,
    channelAddNewMember = 12,
    channelNewPost = 13,
    channelNewFile = 14,
    channelDownloadFile = 15,
    chatSendMessage = 16,
    newLiveNotification = 101,
    newChannelLivePost = 102,
    newChatLiveMessage = 103,
    newChannelLive = 104
};

#endif // SERVERREQUESTTYPES_H
