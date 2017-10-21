**************************
CPUsim - Controller Module
**************************

.. contents::


Introduction
************





#include <iostream>
#include "Controller.h"
#include "mnemonics.h"

// Constructor
Controller::Controller(void) {
    PC = 0;
    IR = 0;
}
 
   
// accessors
int Controller::get_IR(void) {
    return IR;
}

int Controller::get_PC(void) {
    return PC;
}

// mutators

void Controller::reset(void) {
    PC = 0;
    IR = 0;
}

int Controller::fetch(Memory *mem) {
    unsigned int ticks = 0;
    mem->read(PC,1);
    while (!mem->ready()) { ticks++; }
    IR = mem->read_valid();
    return ticks;
}

int Controller::decode(Memory *mem) {
    unsigned int ticks = 0;
    mem->read((2 * PC), 1);
    while(!mem->ready()) { ticks++; }
    int oper1 = mem->read_valid();
    mem->read(((2 * PC) + 1), 1);
    while(!mem->ready()) { ticks++; }
    int oper2 = mem->read_valid();
    int result = 0;
 
    switch(IR) {
        case 0 :        // UNDEF
            // nothing to be done
            break;
        case 1 :        // MOVRR
            // move memory address in oper1 and oper2 from rMem to rMem
            PC += 2;
            break;
        case 2 :        // MOVRM
            // move memory address in oper1 and oper2 from rMem to dMem
            PC += 3;
            break;
        case 3 :        // MOVMR
            // move memory address in oper1 and oper2 from dMem to rMem
            PC+= 3;
            break;
        case 4 :        // ADD
            // call ALU with memory addresses in oper1 and oper2
            break;
        case 5 :        // SUB
            // call ALU with memory addresses in oper1 and oper2
            break;
        case 6 :        // IADD
            // call ALU with memory addresses in oper1 and oper2
            break;
        case 7 :        // ISUB
            // call ALU with memory addresses in oper1 and oper2
            break;
        case 8 :        //HLT
            // nothing to be done
            break;
        default :       // OOPS!! NOT VALID
            // nothing to be done
            ;
    }
    PC++;
    return ticks;
}

int Controller::execute(void) {
    unsigned int ticks = 0;
    return ticks;
}

int Controller::retire(void) {
    unsigned int ticks = 0;
    return ticks;
}

