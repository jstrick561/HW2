**********************
CPUsim - Memory Module
**********************

.. contents::


Introduction
************

The memory portion of the lab is to model the memory in a processor. We will only address memory sizes of 8-bit and 16-bit (ignoring 32-bit and 64-bit). To do this we set up dynamic array of 8-bit fields and will need two fields to represent a 16-bit chunk of memory. We will use the little endian method to store 16-bit chunks. 


Constructors and Destructors
****************************

A default contstructor is created with 1 field and 0 read/write access time create, which could be used as the program counter register (register have 0 read/write time). The main contructor takes in parameters of the size of the array (items to be processed, each process may use multiple fields) and simulated read time and write time, to simulate the time to access RAM to retreive or write data. And because we are creating a dynamic array (using new), we must have a deconstructor to release this memory for reuse. ::

	// constructors
	Memory::Memory() {
		mSize = 1;
		mem = new uint8_t[mSize];
		read_access_time = 0;
		write_access_time = 0;
	}

	Memory::Memory(int size, int read_time, int write_time) {
		delay = 0;
		if (size >= 0) {
			mSize = size;
			mem = new uint8_t[mSize];		
		}

		if (read_time >= 0) {
			read_access_time = read_time;
		}

		if (write_time >= 0) {
			write_access_time = write_time;
		}
	}

	// deconstructor
	Memory::~Memory() {
		delete[] mem;
	}


Accessors
*********

The process here is to read data in the array (memory), which takes time, and only return the data when the time has expired. So in the program that calls these functions, would call ``read``, ``ready``, ``ready``, ``ready`` (until ready comes back true) and then ``read_valid`` to get the data.

The parameters passed in are a  16-bit variable containing the address in the array where the data resides and the size of that data (in bytes, 1 for 8-bit and 2 for 16-bit). Remember actions can only take place is no other actions are in progress (``delay`` = 0). ``rdata`` is used to pass the data from ``read`` to ``read_valid``. ``delay`` is set to the ``read_access_time`` passed in the constructor to represent the time it take to access the register or RAM. Then depending on whether the call was to return a 8-bit or 16-bit field, will determine how to fill ``rdata`` (zero filling the upper 8-bits if only a 8-bit field was requested). ::

	// accessors
	void Memory::read(uint16_t address, int size) {
		if (delay == 0) {
			rdata = 0;
			delay = read_access_time;
			if (size > 1) {
				rdata = ((uint16_t)mem[address + 1] << 8) | mem[address];
			} else {
				rdata = ((uint16_t)0U << 8) | mem[address];
			}
		}
	}


``read_valid`` will return the results, if the memory is in a finished stable state (``delay`` equals zero). ::

	uint16_t Memory::read_valid(void) {
		if (delay == 0) {
			return rdata;
		} else {
			return (uint16_t)0;
		}
	}

``ready`` is the count down of delay. Each time ready is called ``delay`` is decremented by 1 until it reaches zero and then ``ready`` returns ``true``. ::

	bool Memory::ready(void) {
		if (delay == 0) {
			return true;
		} else {
			--delay;
			return false;
		}
	}

``get_size`` will return the size of the array constructed. :: 

	int Memory::get_size() {
		return mSize;
	}


Mutators
********

The process here is to write data in the array (memory), which again, takes time. So in the program that calls these functions, would call ``write``, ``ready``, ``ready``, ``ready`` (until ready comes back true) and then and only then can processing continue.

The parameters passed in are a  16-bit variable containing the address in the array where the data is to reside, the size of that data (in bytes, 1 for 8-bit and 2 for 16-bit) and a 16-bit variable that is the data itself. Remember actions can only take place is no other actions are in progress (``delay`` = 0). ``delay`` is set to the ``write_access_time`` passed in the constructor to represent the time it take to access the register or RAM. The first thing that happens it the 16-bit variable is separated into 2 8-bit variables and then depending on whether the data to store is a 8-bit or 16-bit field, will determine how to fill populalte the array (again using little endian and only populating one address if only a 8-bit field was sent). ::

	// mutators
	void Memory::write(uint16_t address, int size, uint16_t data) {
		if (delay == 0) {
			delay = write_access_time;
			uint8_t left_part = (uint8_t)((data & 0xFF00) >> 8);
			uint8_t right_part = (uint8_t)(data & 0x00FF);
			if (size > 1) {
				mem[address + 1] = left_part;
				mem[address] = right_part;
			} else {
				mem[address] = right_part;
			}
		}
	}
