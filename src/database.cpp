#include "database.hpp"

DataBase::DataBase (const string _baseName): m_baseName(_baseName), m_results(0)
{
    try {

        m_driver = get_driver_instance();

        m_connection = m_driver->connect(M_ADDRESS, M_USERNAME, M_PASSWORD);

        m_connection->setSchema(m_baseName);

        m_statement = m_connection->createStatement();
    }
    catch (sql::SQLException& exception) {
        
        error(exception);
    }
}

DataBase::~DataBase ()
{
    clearResults();

    delete m_statement;
    delete m_connection;
}

void DataBase::clearResults ()
{
    if (m_results) {

        delete m_results;
        m_results = 0;
    }
}

bool DataBase::nextResult ()
{
    return m_results->next();
}

int DataBase::executeQuery (const string _query)
{
    try {

        clearResults();
        
        m_results = m_statement->executeQuery(_query);
        
        return m_results->rowsCount();
    }
    catch (sql::SQLException& exception) {

        error(exception);

        return -1;
    }
}

int DataBase::getColumnAsInt (const string _column) const
{
    return m_results->getInt(_column);
}

string DataBase::getColumnAsString (const string _column) const
{
    return m_results->getString(_column);
}

void DataBase::error (const sql::SQLException& _exception) const
{
    cout << "ERROR: " << _exception.what() << " (MySQL error code: "
        << _exception.getErrorCode() << ", SQL state: "
        << _exception.getSQLState() << " )" << endl;
}

const string DataBase::M_ADDRESS = "tcp://127.0.0.1:3306";
const string DataBase::M_USERNAME = "automaton2000";
const string DataBase::M_PASSWORD = "Automaton2000";