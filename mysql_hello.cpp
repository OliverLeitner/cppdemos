// Includes
#include <iostream>
#include <cstring>
#include <mariadb/conncpp.hpp>

// Main Process
int main(int argc, char **argv)
{
   try
   {
      // Instantiate Driver
      sql::Driver* driver = sql::mariadb::get_driver_instance();

      // Configure Connection
      // The URL or TCP connection string format is
      // ``jdbc:mariadb://host:port/database``.
      sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/classicmodels");

      // Use a properties map for the user name and password
      sql::Properties properties({
            {"user", "demo"},
            {"password", "123"}
         });

      // Establish Connection
      // Use a smart pointer for extra safety
      std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

      // Use Connection
      // ...

      // Close Connection
      conn->close();
   }

   // Catch Exceptions
   catch (sql::SQLException& e)
   {
      std::cerr << "Error Connecting to MariaDB Platform: "
         << e.what() << std::endl;

      // Exit (Failed)
      return 1;
   }

   // Exit (Success)
   std::cout << "everything working just fine" << std::endl;
   return 0;
}
