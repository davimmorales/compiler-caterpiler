module simpleInstructionsRam(clock, address, iRAMOutput);
	 input [9:0] address;
	 input clock;
	 output [31:0] iRAMOutput;
	 integer firstClock = 0;
	 reg [31:0] instructionsRAM[26:0];

	 always @ ( posedge clock ) begin
	 	 if (firstClock==0) begin
 
	 	 instructionsRAM[0] = 32'b01101100000000000000000000000000;//Nop
	 	 instructionsRAM[1] = 32'b01010100000000000000000000001011;//Jump to #11
	 	 instructionsRAM[2] = 32'b01101000001000000000000000000101;//Loadi #5 to r[1]
	 	 instructionsRAM[3] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[4] = 32'b01100100111000000000000000000001;//Store r[7] in m[#1]
	 	 instructionsRAM[5] = 32'b01100000001000000000000000000001;//Load m[#1] to r[1]
	 	 instructionsRAM[6] = 32'b00000111110000010000000000000000;//ADDi r[1], #0 to r[30]
	 	 instructionsRAM[7] = 32'b10000100001111110000000000000000;//Loadr m[r[31]] to r[1]
	 	 instructionsRAM[8] = 32'b10001100000000010000000000000000;//Jump to r[1]
	 	 instructionsRAM[9] = 32'b10000100001111110000000000000000;//Loadr m[r[31]] to r[1]
	 	 instructionsRAM[10] = 32'b10001100000000010000000000000000;//Jump to r[1]
	 	 instructionsRAM[11] = 32'b01101000001000000000000000000010;//Loadi #2 to r[1]
	 	 instructionsRAM[12] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[13] = 32'b01100100111000000000000000000101;//Store r[7] in m[#5]
	 	 instructionsRAM[14] = 32'b01100000001000000000000000000101;//Load m[#5] to r[1]
	 	 instructionsRAM[15] = 32'b01100100001000000000000000000010;//Store r[1] in m[#2]
	 	 instructionsRAM[16] = 32'b01101011111000000000000000000111;//Loadi #7 to r[31]
	 	 instructionsRAM[17] = 32'b00000111111111110000000000000001;//ADDi r[31], #1 to r[31]
	 	 instructionsRAM[18] = 32'b01101000001000000000000000010101;//Loadi #21 to r[1]
	 	 instructionsRAM[19] = 32'b10001000001111110000000000000000;//rStore to r[1] in m[r[31]] 
	 	 instructionsRAM[20] = 32'b01010100000000000000000000000010;//Jump to #2
	 	 instructionsRAM[21] = 32'b00001111111111110000000000000001;//SUBi r[31], #1 to r[31]
	 	 instructionsRAM[22] = 32'b00000100111111100000000000000000;//ADDi r[30], #0 to r[7]
	 	 instructionsRAM[23] = 32'b00000100001001110000000000000000;//ADDi r[7], #0 to r[1]
	 	 instructionsRAM[24] = 32'b01111000001000000000000000000000;//Pre Output r[1]
	 	 instructionsRAM[25] = 32'b10000000001000000000000000000000;//Output r[1]

	 	 firstClock <= 0;
	 	 end
	 end

	 assign iRAMOutput = instructionsRAM[address];
endmodule // simpleInstructionsRAM
