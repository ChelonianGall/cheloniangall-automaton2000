#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class DataBase {

	public:

	DataBase () = delete;
	DataBase (const DataBase&) = delete;
    
    DataBase (const string);
    ~DataBase ();

    void clearResults ();
    bool nextResult ();
    int executeQuery (const string);

    int getColumnAsInt (const string) const;
    string getColumnAsString (const string) const;

	private:

	void error (const sql::SQLException&) const;

	static const string M_ADDRESS;
	static const string M_USERNAME;
	static const string M_PASSWORD;

	string m_baseName;
	sql::Driver* m_driver;
	sql::Connection* m_connection;
	sql::Statement* m_statement;
	sql::ResultSet* m_results;
};