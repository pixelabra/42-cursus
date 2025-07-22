#ifndef FILETRANSFER_HPP
#define FILETRANSFER_HPP

#include <string>
#include <map>
#include <fstream>

class Server;
class Client;

struct FileTransferSession {
    std::string filename;
    std::string sender;
    std::string receiver;
    size_t fileSize;
    size_t bytesTransferred;
    std::ofstream* outputFile;
    bool active;
    
    FileTransferSession() : fileSize(0), bytesTransferred(0), outputFile(NULL), active(false) {}
};

class FileTransfer {
private:
    Server* _server;
    std::map<std::string, FileTransferSession> _sessions;
    
    std::string generateSessionId();
    void sendDCCMessage(Client* client, const std::string& message);
    
public:
    FileTransfer(Server* server);
    ~FileTransfer();
    
    // DCC SEND/ACCEPT handling
    void handleDCCSend(Client* sender, const std::string& target, const std::string& filename, size_t fileSize);
    void handleDCCAccept(Client* receiver, const std::string& sender, const std::string& filename);
    void handleFileData(const std::string& sessionId, const char* data, size_t size);
    void handleFileTransferComplete(const std::string& sessionId);
    
    // CTCP DCC message parsing
    bool isDCCMessage(const std::string& message);
    void processDCCMessage(Client* client, const std::string& target, const std::string& message);
};

#endif
