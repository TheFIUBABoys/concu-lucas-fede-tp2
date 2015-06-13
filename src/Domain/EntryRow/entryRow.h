//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_ENTRYROW_H
#define CONCU_LUCAS_FEDE_TP2_ENTRYROW_H

#define DB_QUERY    1
#define DB_RESPONSE 2

#define SAVE    0
#define UPDATE  1
#define RETRIEVE    2
#define DELETE  3

typedef struct entryRow {
    char nombre[61];
    char direccion[120];
    char telefono[13];
} entryRow_t;

typedef struct dbAction {
    long mtype;
    int action;
    char nombre[61];
    entryRow_t entryRow;
} dbAction_t;

#endif //CONCU_LUCAS_FEDE_TP2_ENTRYROW_H
