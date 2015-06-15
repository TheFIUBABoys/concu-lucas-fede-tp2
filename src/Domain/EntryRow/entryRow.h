//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_ENTRYROW_H
#define CONCU_LUCAS_FEDE_TP2_ENTRYROW_H

#define SAVE    0
#define RETRIEVE    1
#define UPDATE  2
#define DELETE  3

#define NOMBRE_SIZE 61
#define DIRECCION_SIZE 120
#define TELEFONO_SIZE 13

typedef struct entryRow {
    char nombre[NOMBRE_SIZE];
    char direccion[DIRECCION_SIZE];
    char telefono[TELEFONO_SIZE];
} entryRow_t;

typedef struct dbQuery {
    long mtype;
    int action;
    char nombre[61];
    entryRow_t entryRow;
} dbQuery_t;

typedef struct dbResponse {
    long mtype;
    char value[NOMBRE_SIZE + DIRECCION_SIZE + TELEFONO_SIZE];
    int result;
} dbResponse_t;

#endif //CONCU_LUCAS_FEDE_TP2_ENTRYROW_H
