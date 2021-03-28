// Includes
#include <iostream>
#include <sstream>
#include <iterator>
#include <mariadb/conncpp.hpp>
#include <nlohmann/json.hpp>
using nlohmann::json;

struct Customer {
 int customerNumber;
 std::string customerName;
 std::string contactFirstName;
 std::string contactLastName;
 std::string phone;
};

int numberOfRowsInTable() {
   int numRows = 0;
   try
   {
      sql::Driver* driver = sql::mariadb::get_driver_instance();
      sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/classicmodels?characterEncoding=latin1");
      sql::Properties properties({
            {"user", "demo"},
            {"password", "123"}
         });
      std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
      std::shared_ptr<sql::Statement> stmnt(conn->createStatement());

      std::unique_ptr<sql::ResultSet> res(
           stmnt->executeQuery("SELECT count(*) FROM customers")
      );

      while (res->next())
      {
          numRows = res->getInt("count(*)");
      }

      conn->close();
   }
   catch (sql::SQLException &e)
   {
       std::cerr << "Error Connecting to MariaDB Platform: "
         << e.what() << std::endl;
      return 1;
   }
   return numRows;
}

// Function to print Contacts
std::string printCustomers(std::shared_ptr<sql::Statement> &stmnt)
{
   std::string str = "[";
   Customer customers[numberOfRowsInTable()];
   int i = 0;
   try
   {
      // Execute SELECT Statement
      std::unique_ptr<sql::ResultSet> res(
           stmnt->executeQuery("SELECT customerNumber,customerName,contactFirstName,contactLastName,phone FROM customers")
      );

      json j;

      // Loop over Result-set
      while (res->next())
      {
          if (i > 0) str = str + ",";
          str = str + "{";
          str = str + "\"customerNumber\": \"" + res->getString("customerNumber") + "\",";
          str = str + "\"customerName\": \"" + res->getString("customerName") + "\",";
          str = str + "\"phone\": \"" + res->getString("phone") + "\",";
          str = str + "\"contactFirstName\": \"" + res->getString("contactFirstName") + "\",";
          str = str + "\"contactLastName\": \"" + res->getString("contactLastName") + "\"";
          str = str + "}";
          /*Customer scustomer;
          scustomer.customerNumber = res->getInt("customerNumber");
          scustomer.customerName = res->getString("customerName");
          scustomer.contactFirstName = res->getString("contactFirstName");
          scustomer.contactLastName = res->getString("contactLastName");
          scustomer.phone = res->getString("phone");
          customers[i] = scustomer;*/
          // str = str + "{\"customerName\": \"" + res->getString("customerName") + "\", \"phone\": \"" + res->getString("phone") + "\"}";
          // str = str + customers[i].customerName + "\n";
          i++;
      }
   }

   // Catch Exception
   catch (sql::SQLException& e)
   {
       std::cerr << "Error printing customers: "
         << e.what() << std::endl;
   }

   return str + "]"; // customers;
}

// can be called from outside
std::string getCustomerData() {
   std::string data = "";
   try
   {
      sql::Driver* driver = sql::mariadb::get_driver_instance();
      sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/classicmodels");
      sql::Properties properties({
            {"user", "demo"},
            {"password", "123"}
         });
      std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
      std::shared_ptr<sql::Statement> stmnt(conn->createStatement());

      std::cout << "connection established" << std::endl;
      data = printCustomers(stmnt);
      conn->close();
   }
   catch (sql::SQLException &e)
   {
       std::cerr << "Error Connecting to MariaDB Platform: "
         << e.what() << std::endl;
      return "1";
   }

   if(data != "") return data;
   else return 0;
}
