/**
 * @file sm83_state.cpp
 * @author Joel Hill (@joelghill)
 * @brief
 * @version 0.1
 * @date 2020-06-26
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include "./sm83_state.hpp"

using namespace std;

SM83State::SM83State(uint8_t* memory_bus_ptr) {
    // Sets the pointer to the memory bus array
    this->memory_bus_ = memory_bus_ptr;
}

bool SM83State::zFlag() {
    return (this->f_register_ & Z_FLAG) > 0;
}

bool SM83State::nFlag() {
    return (this->f_register_ & N_FLAG) > 0;
}

bool SM83State::hFlag() {
    return (this->f_register_ & H_FLAG) > 0;
}

bool SM83State::cFlag() {
    return (this->f_register_ & C_FLAG) > 0;
}

uint16_t SM83State::stackPointer() {
    return this->stack_pointer_;
}

void SM83State::setStackPointer(uint16_t value) {
    this->stack_pointer_ = value;
}

uint16_t SM83State::programCounter() {
    return this->program_counter_;
}

void SM83State::setProgramCounter(uint16_t value) {
    this->program_counter_ = value;
}

void SM83State::IncrementProgramCounter(uint8_t num_bytes) {
    this->program_counter_ = this->program_counter_ + num_bytes;
}

uint8_t SM83State::MemoryAt(int16_t address) {
    return this->memory_bus_[address];
}

void SM83State::SetMemoryAt(int16_t address, uint8_t value) {
    this->memory_bus_[address] = value;
}

uint8_t SM83State::a() {
    return this->a_register_;
}

void SM83State::setA(uint8_t value) {
    this->a_register_ = value;
}

uint8_t SM83State::b() {
    return this->b_register_;
}

void SM83State::setB(uint8_t value) {
    this->b_register_ = value;
}

uint8_t SM83State::c() {
    return this->c_register_;
}

void SM83State::setC(uint8_t value) {
    this->c_register_ = value;
}

uint16_t SM83State::bc() {
    return ((uint16_t)(this->b_register_ << 8) | this->c_register_);
}

void SM83State::setBC(uint16_t value) {
    this->b_register_ = (uint8_t)((value & 0xff00) >> 8);
    this->c_register_ = (uint8_t)(value & 0x00ff);
}

uint8_t SM83State::d() {
    return this->d_register_;
}

void SM83State::setD(uint8_t value) {
    this->d_register_ = value;
}

uint8_t SM83State::e() {
    return this->e_register_;
}

void SM83State::setE(uint8_t value) {
    this->e_register_ = value;
}

uint16_t SM83State::de() {
    return ((uint16_t)(this->d_register_ << 8) | this->e_register_);
}

void SM83State::setDE(uint16_t value) {
    this->d_register_ = (uint8_t)((value & 0xff00) >> 8);
    this->e_register_ = (uint8_t)(value & 0x00ff);
}

uint8_t SM83State::h() {
    return this->h_register_;
}

void SM83State::setH(uint8_t value) {
    this->h_register_ = value;
}

uint8_t SM83State::l() {
    return this->l_register_;
}

void SM83State::setL(uint8_t value) {
    this->l_register_ = value;
}

uint16_t SM83State::hl() {
    return ((uint16_t)(this->h_register_ << 8) | this->l_register_);
}

void SM83State::setHL(uint16_t value) {
    this->h_register_ = (uint8_t)((value & 0xff00) >> 8);
    this->l_register_ = (uint8_t)(value & 0x00ff);
}

uint8_t SM83State::f() {
    return this->f_register_;
}

void SM83State::setF(uint8_t value) {
    this->f_register_ = value;
}

uint16_t SM83State::af() {
    return ((uint16_t)(this->a_register_ << 8) | this->f_register_);
}

void SM83State::setAF(uint16_t value) {
    this->a_register_ = (uint8_t)((value & 0xff00) >> 8);
    this->f_register_ = (uint8_t)(value & 0x00ff);
}