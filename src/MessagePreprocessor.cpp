#include "MessagePreprocessor.h"

MessagePreprocessor::MessagePreprocessor() {
    mThread = std::make_unique<std::thread>(&MessagePreprocessor::processData, this);
}

void MessagePreprocessor::addData(std::string data) {
    mMutex.lock();
    mRawData += data;
    mMutex.unlock();
}

void MessagePreprocessor::processData() {
    std::string msg = "";
    while (true)
    {
        mMutex.lock();
        if (!mRawData.empty()) {
            msg = separateMessage();
            if(!msg.empty())
                mHandler.handleMessage(msg);
        }
        mMutex.unlock();
    }
}

std::string MessagePreprocessor::separateMessage() {
    const unsigned int nearestDelimiter = mRawData.find(MESSAGE_DELIMITER);
    if (nearestDelimiter == std::string::npos) return "";

    std::string msg = mRawData.substr(0, nearestDelimiter);
    // std::cout << "RawData: " + mRawData << std::endl;
    mRawData.erase(mRawData.find(msg), msg.length());
    if (mRawData.length() > 0 || mRawData.find(MESSAGE_DELIMITER) == 0) mRawData.erase(0, 1);
    mRawData.erase(mRawData.find_last_not_of(" ") + 1);

    msg.erase(0, msg.find(" "));
    // std::cout << "Message separated: " +  msg << std::endl;
    return msg;
}