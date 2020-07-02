#include <gtest/gtest.h>
#include "../src/cpu/sm83_state.hpp"
#include "../src/cpu/sm83_op_codes.hpp"

namespace {

/**
 * @brief
 *
 */
class OpCodesTest : public ::testing::Test {
protected:

    uint8_t* memory_;
    SM83State* state_;
    uint16_t program_counter_ = 0x100;


    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        this->memory_ = new uint8_t[65536];
        this->state_ = new SM83State(this->memory_);
        this->state_->setProgramCounter(this->program_counter_);
    }

    void TearDown() override {
        delete this->state_;
        delete this->memory_;
    }
};

TEST_F(OpCodesTest, TestExecute00) {
    // Ensure that the operation takes 4 cycles
    ASSERT_EQ(Execute00(this->state_), 4);
    // And that the
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 1);
}

TEST_F(OpCodesTest, TestExecute01) {
    this->state_->SetMemoryAt(this->program_counter_ + 1, 0x04);
    this->state_->SetMemoryAt(this->program_counter_ + 2, 0x02);

    // Ensure that the
    ASSERT_EQ(Execute01(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 3);

    ASSERT_EQ(this->state_->b(), 0x04);
    ASSERT_EQ(this->state_->c(), 0x02);
    ASSERT_EQ(this->state_->bc(), 0x0402);
}

TEST_F(OpCodesTest, TestExecute02) {
    uint8_t a = 0x42;
    uint8_t b = 0x02;
    uint8_t c = 0x00;

    this->state_->setA(a);
    this->state_->setB(b);
    this->state_->setC(c);

    // Ensure that the
    ASSERT_EQ(Execute02(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt((uint16_t)b << 8 | c), a);
}

TEST_F(OpCodesTest, TestExecute03) {
    uint16_t bc = 0x1987;

    this->state_->setB(0x19);
    this->state_->setC(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute03(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->bc(), bc + 1);
}

TEST_F(OpCodesTest, TestExecute04) {
    uint8_t b = 0x19;
    this->state_->setB(b);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute04(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->b(), b + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute04_Z1C0H1) {
    uint8_t b = 0xFF;
    this->state_->setB(b);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute04(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->b(), 0);
    // Z should equal 0 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}