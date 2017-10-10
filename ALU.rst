*******************
CPUsim - ALU Module
*******************

.. contents::


Introduction
************

The ALU portion of the lab is to model the ALU unit in a processor. We will only address the math portion of the ALU not and further just ``addition`` and ``subtraction`` operations.  We will only address 8-bit and 16-bit data (ignoring 32-bit and 64-bit) and will not consider mixed operations where one operand is 8 bits, and the other is 16 bits. Both operands are the same size.


Constructors and Destructors
****************************

The constructor needed is very simple, just initialize our variables. We will let the system take care of the destructor, since we are not creating anythin dynamic. ::

	// constructor
	ALU::ALU() {
		result = 0;
		carry = false;
		overflow = false;
	}


Accessors
*********

The accessors again are very simple, just returning the results of our calculations. ::

	// acessors
	int16_t ALU::get_result() {
		return result;
	}

	bool ALU::get_carry() {
		return carry;
	}

	bool ALU::get_overflow() {
		return overflow;
	}


Mutators
********

The parameters passed in are two 16-bit operands and the size of the size used in these operands (in bytes, 1 for 8-bit and 2 for 16-bit).  The result is calculated. 

``add`` Carry Flag: If result (or two operands, in the case of 16-bit), exceeds the maximum allowed for and 8-bit or 16-bit variable or is less than the minimum allowed, the carry flag is set to true. The two operands are used in the case of 16-bit because adding two 16-bit operands in 16-bit variables will not specify whether a carry is created so, using the rule "if second operand is positive (possibly creating a variable to exceed maximum) and the first operand is larger than the maximum minus the second operand, it will exceed the maximum" or "if second operand is negative (possibly creating a variable to be less than minimum) and the first operand is less than the minimum minus a negative (plus) second operand, it will be less than the minimum".

``add`` Overflow Flag: If result (moved to a 32-bit variable, in the case of 16-bit, so you can see the last bit to see if it is a 1), exceeds the maximum allowed for and 7-bit or 15-bit variable or is less than the minimum allowed, the overflow flag is set to true. This is done using the same rule as carry but with a 7-bit and 15-bit minimum and maximum. ::

	// mutators
	void ALU::add(uint16_t op1, uint16_t op2, int size) {
		result = 0;
		carry = false;
		overflow = false;
		if (size > 1) {
			int int_min = -65536;
			result = op1 + op2;
			if (((op2 > 0) and (op1 > (((-int_min) - 1) - op2))) or ((op2 < 0) and (op1 < (int_min - op2)))) {
				carry = true;
			}
			int32_t op1_32 = (op1 & 0x0000ffff);
			int32_t op2_32 = (op2 & 0x0000ffff);
			int32_t result_32 = op1_32 + op2_32;
			if ((result_32 > (((-int_min) / 2) - 1)) or (result_32 < (int_min  / 2))) {
				overflow = true;
			}
		} else {
			int int_min = -256;
			result = op1 + op2;
			if ((result > (((-int_min) / 2) - 1)) or (result < (int_min / 2))) {
				overflow = true;
			}
			if ((result > ((-int_min) - 1)) or (result < int_min)) {
				result = (int8_t)(result & 0x00ff);
				carry = true;
			}
		}
	}

The parameters passed in are two 16-bit operands and the size of the size used in these operands (in bytes, 1 for 8-bit and 2 for 16-bit).  The result is calculated. 

``sub`` Carry Flag: If result (or two operands, in the case of 16-bit), exceeds the maximum allowed for and 8-bit or 16-bit variable or is less than the minimum allowed, the carry flag is set to true. The two operands are used in the case of 16-bit because subtracting two 16-bit operands in 16-bit variables will not specify whether a carry is created so, using the rule "if second operand is negative (possibly creating a variable to exceed maximum) and the first operand is larger than the maximum plus the second operand, it will exceed the maximum" or "if second operand is psoitive (possibly creating a variable to be less than minimum) and the first operand is less than the minimum plus a negative second operand, it will be less than the minimum".

``sub`` Overflow Flag: If result (moved to a 32-bit variable, in the case of 16-bit, so you can see the last bit to see if it is a 1), exceeds the maximum allowed for and 7-bit or 15-bit variable or is less than the minimum allowed, the overflow flag is set to true. This is done using the same rule as carry but with a 7-bit and 15-bit minimum and maximum. ::

	void ALU::sub(uint16_t op1, uint16_t op2, int size) {
		result = 0;
		carry = false;
		overflow = false;
		if (size > 1) {
			int int_min = -65536;
			result = op1 - op2;
			if (((op2 < 0) and (op1 > (((-int_min) - 1) + op2))) or ((op2 > 0) and (op1 < (int_min + op2)))) {
				carry = true;
			}
			int32_t op1_32 = (op1 & 0x0000ffff);
			int32_t op2_32 = (op2 & 0x0000ffff);
			int32_t result_32 = op1_32 - op2_32;
			if ((result_32 > (((-int_min) / 2) - 1)) or (result_32 < (int_min  / 2))) {
				overflow = true;
			}
		} else {
			int int_min = -256;
			result = op1 - op2;
			if ((result > (((-int_min) / 2) - 1)) or (result < (int_min / 2))) {
				overflow = true;
			}
			if ((result > ((-int_min) - 1)) or (result < int_min)) {
				result = (int8_t)(result & 0x00ff);
				carry = true;
			}
		}
	}

