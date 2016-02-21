#pragma once

#include <string>
#include <cstdint>
#include "common/file_scanner.h"

#include "common/communication_manager.h"

class ClientLogic {
public:
    ClientLogic(CommunicationManager& cm, const std::string& rootFolder);

private:
    enum class Error {
        NoError,
        TimeDiffError,
        Timeout,
    };

    bool checkTimeDiff();

    uint32_t nextID() { return ++mMessageID; }
    uint32_t currentID() { return mMessageID; }

    Error loop();
    Error onIncomingFileList(FileScanner remoteFiles);
    Error deleteFiles(const std::vector<FileInfo>& toDelete);
    Error requestAndSaveNewFiles(const std::vector<FileInfo>& toAdd);

    CommunicationManager& mCM;
    std::string mRoot;
    uint32_t mMessageID = 0;
    time_t mTimeOffset = 0;
};

