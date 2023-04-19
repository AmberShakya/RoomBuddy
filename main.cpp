#include <iostream>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;

int main() {
    // Initialize MySQL Connector/C++
    sql::Driver* driver;
    sql::Connection* conn;
    sql::Statement* stmt;
    sql::ResultSet* res;

    try {
        driver = get_driver_instance();
        conn = driver->connect("tcp://localhost:3306", "username", "password");
        conn->setSchema("databasename");

        // Execute a SQL query
        stmt = conn->createStatement();
        res = stmt->executeQuery("SELECT * FROM tablename");

        // Process the result set
        while (res->next()) {
            int id = res->getInt("id");
            string name = res->getString("name");
            double price = res->getDouble("price");

            cout << "Product: " << name << " (ID: " << id << ") - Price: " << price << endl;
        }

        delete res;
        delete stmt;
        delete conn;
    }catch(sql::SQLException& e) {
        cout << "MySQL error: " << e.what() << endl;
    }

    return 0;
}
