#!/bin/bash
g++  main.cpp "FileSystem/Block.cpp" "FileSystem/Block.h" "FileSystem/FileStream.h" "FileSystem/FileStream.cpp" "Config.h" "FileSystem/FileStreamRead.cpp" "FileSystem/FileStreamRead.h" "FileSystem/FileStreamWrite.cpp" "FileSystem/FileStreamWrite.h" "Exception/ExceptionFileNotOpened.h" "Exception/ExceptionFileNotOpened.cpp" "DataBase/SingletoneConn.h" "DataBase/SingletoneConn.cpp" "DataBase/Tables/ServerFiles.h" "DataBase/Tables/ServerFiles.cpp"  -lmysqlcppconn -o testProgect 2>out.log
echo "compile complited"
