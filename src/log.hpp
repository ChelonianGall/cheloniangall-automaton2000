#include <fstream>
#include <iostream>
#include <memory>

using namespace std;

class LogStream {

    public:

    static shared_ptr<LogStream> getLogStream ();

    LogStream (const LogStream&) = delete;

    ~LogStream ();

    void log (const string);

    private:

    static const string M_LOGS_FILE_PATH;

    static shared_ptr<LogStream> m_logStream;

    LogStream ();
    
    ofstream m_ofstream;
};