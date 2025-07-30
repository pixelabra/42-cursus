#ifndef FILETRANSFER_HPP
#define FILETRANSFER_HPP

#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

class Server;
class Client;

struct DCCSession {
    std::string filename;
    std::string filepath;
    std::string senderNick;
    std::string receiverNick;
    uint32_t ip;
    uint16_t port;
    uint32_t fileSize;
    uint32_t bytesTransferred;
    int serverSocket;
    int clientSocket;
    bool active;
    bool isReceiver;
    std::ifstream* inputFile;
    std::ofstream* outputFile;
    
    DCCSession() : ip(0), port(0), fileSize(0), bytesTransferred(0), 
                   serverSocket(-1), clientSocket(-1), active(false), 
                   isReceiver(false), inputFile(NULL), outputFile(NULL) {}
};

class FileTransfer {
private:
    Server* _server;
    std::map<std::string, DCCSession> _activeSessions;
    static uint16_t _nextPort;
    
    std::string getSessionKey(const std::string& sender, const std::string& receiver, const std::string& filename);
    uint32_t ipStringToLong(const std::string& ip);
    std::string ipLongToString(uint32_t ip);
    uint16_t getNextAvailablePort();
    
public:
    FileTransfer(Server* server);
    ~FileTransfer();
    
    // CTCP DCC message detection and parsing
    bool isDCCMessage(const std::string& message);
    void processDCCMessage(Client* client, const std::string& target, const std::string& message);
    
    // DCC SEND command handling
    void handleDCCSend(Client* sender, const std::string& target, const std::string& filename, const std::string& filepath = "");
    
    // DCC protocol message parsing
    void parseDCCSend(Client* client, const std::string& target, const std::vector<std::string>& params);
    void parseDCCAccept(Client* client, const std::vector<std::string>& params);
    void parseDCCResume(Client* client, const std::vector<std::string>& params);
    void parseDCCChat(Client* client, const std::string& target, const std::vector<std::string>& params);
    
    // Real file transfer implementation
    int createDCCServer(uint16_t port);
    bool connectDCCClient(uint32_t ip, uint16_t port, const std::string& sessionKey);
    void handleDCCConnection(const std::string& sessionKey);
    void transferFileData(const std::string& sessionKey);
    void closeDCCSession(const std::string& sessionKey);
    
    // File operations
    uint32_t getFileSize(const std::string& filepath);
    bool fileExists(const std::string& filepath);
};

#endif
