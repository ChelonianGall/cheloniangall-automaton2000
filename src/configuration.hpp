#pragma once

#include "log.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

class ConfigurationException: public exception {

    public:

    enum ErrorType {

        FILE = 0,
        PARAMETER = 1,
        VALUE = 2
    };

    ConfigurationException () = delete;

    ConfigurationException (const ErrorType _type, const string& _details);

    const char* what () const noexcept;

    private:

    string m_what;
};

class Configuration {

    public:

    Configuration (const Configuration&) = delete;

    static shared_ptr<Configuration> getConfiguration ();

    const bool& isValid () const;

    const string& getDatabaseIP () const;
    const string& getDatabasePassword () const;
    const string& getDatabasePort () const;
    const string& getDatabaseProtocol () const;
    const string& getDatabaseUser () const;

    private:

    Configuration ();

    void error (const ConfigurationException&);

    static const string M_DATABASE_IP_DEFAULT;
    static const string M_DATABASE_PORT_DEFAULT;
    static const string M_DATABASE_PROTOCOL_DEFAULT;

    static shared_ptr<Configuration> m_configuration;

    shared_ptr<LogStream> m_logStream;

    bool m_valid;
    string m_databaseIP;
    string m_databasePassword;
    string m_databasePort;
    string m_databaseProtocol;
    string m_databaseUser;
};