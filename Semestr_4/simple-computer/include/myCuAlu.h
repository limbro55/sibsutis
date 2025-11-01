#ifndef MYCLUALU_H
#define MYCLUALU_H

// Операции ввода/вывода
#define READ 0x0a
#define WRITE 0x0b

// Операции загрузки/выгрузки в аккумулятор
#define LOAD 0x14
#define STORE 0x15

// Арифметические операции
#define ADD 0x1e
#define SUB 0x1f
#define DIVIDE 0x20
#define MUL 0x21

// Операции передачи управления
#define JUMP 0x28
#define JNEG 0x29
#define JZ 0x2a
#define HALT 0x2b

// Пользовательские функции

// Акуско
#define NOT 0x33
#define AND 0x34

// Рыбкин
#define LOGRC 0x44
#define RCCL 0x45

// Сафонов
#define RCCR 0x46
#define MOVA 0x47

void CU (void);
int ALU (int command, int operand);
void IRC (int signum);
void isig_generator_start (void);
void isig_generator_stop (void);

#endif // MYCLUALU_H
