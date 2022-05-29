#ifndef DEFINES_H
#define DEFINES_H

//#define POSTGRESQL
//#define MYSQL

#ifdef MYSQL
    #define FILENAME "./config/mysql.cfg"
    #define USER_REP UsersRepositoryMySQL
    #define CANVAS_REP CanvasRepositoryMySQL
#else
    #define FILENAME "./config/default.cfg"
    #define USER_REP UsersRepository
    #define CANVAS_REP CanvasRepository
#endif

#endif // DEFINES_H
