#include <mysql/mysql.h>
#include <iostream>

int main()
{
    MYSQL *conn; // 连接句柄
    MYSQL_RES *res; // 结果集句柄
    MYSQL_ROW row; // 表示结果集的一行数据

    // 初始化
    conn = mysql_init(NULL); // 初始化连接句柄

    // 连接数据库
    if (!mysql_real_connect(conn, // 连接数据库
                            "localhost",   // host
                            "root",        // user
                            "",            // password
                            "testdb",      // database
                            3306,          // port
                            NULL,
                            0))
    {
        std::cerr << "connect failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    std::cout << "MySQL connected!" << std::endl;

    // ===== 插入数据 =====
    const char *insert_sql = "INSERT INTO user(name, age) VALUES('Tom', 20)";

    if (mysql_query(conn, insert_sql)) // 执行插入语句
    {
        std::cerr << "insert failed: " << mysql_error(conn) << std::endl;
    }
    else
    {
        std::cout << "Insert success!" << std::endl;
    }

    // ===== 查询数据 =====
    const char *select_sql = "SELECT id, name, age FROM user";

    if (mysql_query(conn, select_sql)) // 执行查询语句
    {
        std::cerr << "select failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    res = mysql_store_result(conn); // 获取结果集  把服务器结果拉到客户端内存

    std::cout << "\nQuery result:\n";

    while ((row = mysql_fetch_row(res))) // 遍历结果集
    {
        std::cout
            << "id=" << row[0]
            << " name=" << row[1]
            << " age=" << row[2]
            << std::endl;
    }

    mysql_free_result(res); // 释放结果集
    mysql_close(conn); // 关闭连接句柄

    return 0;
}

/*
-bash-4.2# ./mysql_demo
MySQL connected!
Insert success!

Query result:
id=1 name=Tom age=20
*/