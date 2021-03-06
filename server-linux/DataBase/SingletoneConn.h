#pragma once
/* MySQL Connector/C++ specific headers */
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include <boost/thread/lock_guard.hpp> 
#include <boost/thread/recursive_mutex.hpp>

#include "../Config.h"
using namespace sql;

namespace Database{
	class SingletoneConn
	{
	public:
		static SingletoneConn& Instance();
		
		/**
		 * Return obj for query
		 */
		Statement* getStatementObj(void);
                
                /**
                 * Return Connection obj
                 * @return 
                 */
                Connection* getConnection();
                
                
                //for critical sections
                boost::recursive_mutex  m_guard;
                
	private:
		Driver *driver;
		Connection *con;
		Statement *stmt;
                
        
		SingletoneConn();
		SingletoneConn(const SingletoneConn&);
		SingletoneConn& operator=(const SingletoneConn&);
	};
}
