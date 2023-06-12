#ifndef MESSAGE_PREPROCESSOR_H
#define MESSAGE_PREPROCESSOR_H

#include "MessageHandler.h"
#include <string>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

#include<unistd.h>               // for linux


class MessagePreprocessor {
public:
    MessagePreprocessor();
    void addData(std::string data);
    void processData();
    std::string separateMessage();

private:
    std::unique_ptr<std::thread> mThread;
    std::string mRawData = "";
    std::mutex mMutex;
    std::string MESSAGE_DELIMITER = "|";
    MessageHandler mHandler;
};

#endif // MESSAGE_PREPROCESSOR_H