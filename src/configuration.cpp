#include "configuration.hpp"

Configuration::Configuration ():
    m_logStream(LogStream::getLogStream()),
    m_valid(true),
    m_databaseIP(M_DATABASE_IP_DEFAULT),
    m_databasePort(M_DATABASE_PORT_DEFAULT),
    m_databaseProtocol(M_DATABASE_PROTOCOL_DEFAULT)
{
    fstream configurationFile("automaton2000.conf", ios::in);

    try {

        if (configurationFile.is_open()) {

            string line;

            while (getline(configurationFile, line)) {

                int commentPosition = line.find("#");

                if (commentPosition != string::npos) line.erase(commentPosition);

                if (!regex_match(line, regex("^\\s*$"))) {

                    stringstream lineStream(line);

                    string parameter;
                    string value;

                    lineStream >> parameter >> value;

                    if (!value.empty()) {

                        if (parameter == "dbip") m_databaseIP = value;
                        else if (parameter == "dbpassword") m_databasePassword = value;
                        else if (parameter == "dbport") m_databasePort = value;
                        else if (parameter == "dbprotocol") m_databaseProtocol = value;
                        else if (parameter == "dbuser") m_databaseUser = value;
                        else throw ConfigurationException(ConfigurationException::PARAMETER, parameter);
                    }
                    else throw ConfigurationException(ConfigurationException::VALUE, parameter);

                }
            }

            configurationFile.close();
        }
        else throw ConfigurationException(ConfigurationException::FILE, "automaton2000.conf");
    }
    catch (const ConfigurationException& exception) {

        m_valid = false;

        error(exception);
    }
}

const bool& Configuration::isValid () const
{
    return m_valid;
}

const string& Configuration::getDatabaseIP () const
{
    return m_databaseIP;
}

const string& Configuration::getDatabasePassword () const
{
    return m_databasePassword;
}

const string& Configuration::getDatabasePort () const
{
    return m_databasePort;
}

const string& Configuration::getDatabaseProtocol () const
{
    return m_databaseProtocol;
}

const string& Configuration::getDatabaseUser () const
{
    return m_databaseUser;
}

shared_ptr<Configuration> Configuration::getConfiguration ()
{
    if (!m_configuration) {

        m_configuration.reset(new Configuration);
    }

    return m_configuration;
}

void Configuration::error (const ConfigurationException& _exception)
{
    m_logStream->log(_exception.what());
}

const string Configuration::M_DATABASE_IP_DEFAULT = "127.0.0.1";
const string Configuration::M_DATABASE_PORT_DEFAULT = "3306";
const string Configuration::M_DATABASE_PROTOCOL_DEFAULT = "tcp";

shared_ptr<Configuration> Configuration::m_configuration(nullptr);

ConfigurationException::ConfigurationException (const ErrorType _type, const string& _value)
{
    m_what = "CONFIGURATION ERROR: ";

    switch (_type)
    {
        case FILE: m_what += "Unable to open '" + _value + "'.";
        break;
        case PARAMETER: m_what += "Unknown parameter '" + _value + "'.";
        break;
        case VALUE: m_what += "No value provided for '" + _value +"'.";
        break;
        default: m_what += "Unknown error.";
        break;
    }
}

const char* ConfigurationException::what () const noexcept
{
     return m_what.c_str();
}