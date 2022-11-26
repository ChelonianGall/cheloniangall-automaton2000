#include "log.hpp"

shared_ptr<LogStream> LogStream::getLogStream ()
{
    if (!m_logStream) {
        
        m_logStream.reset(new LogStream);
    }

    return m_logStream;
}

LogStream::LogStream ()
{
    m_ofstream.open(M_LOGS_FILE_PATH, ios::app);

    if (!m_ofstream.is_open()) {

        cout << "WARNING: Unable to open or create '" << M_LOGS_FILE_PATH
            << "'. The logs will be displayed but not saved." << endl;
    }
}

LogStream::~LogStream ()
{
    m_ofstream.close();
}

void LogStream::log (const string _message)
{
    if (m_ofstream.is_open()) {

        m_ofstream << _message << endl;
    }

    cout << _message << endl;
}

const string LogStream::M_LOGS_FILE_PATH = "automaton2000.log";

shared_ptr<LogStream> LogStream::m_logStream(nullptr);