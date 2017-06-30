module simpleInstructionsRam(clock, address, iRAMOutput);
	 input [9:0] address;
	 input clock;
	 output [31:0] iRAMOutput;
	 integer firstClock = 0;
	 reg [31:0] instructionsRAM[12:0];

	 always @ ( posedge clock ) begin
	 	 if (firstClock==0) begin
 
	 	 instructionsRAM[0] = 32'b01101100000000000000000000000000;//Nop
	 	 instructionsRAM[1] = 32'b01010100000000000000000000000010;//Jump to #2
	 	 instructionsRAM[2] = 32'b01110100001000000000000000000000;//Input to r[1]
	 	 instructionsRAM[3] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[4] = 32'b01100100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[5] = 32'b01100000011000000000000000000010;//Load m[#2] to r[3]
	 	 instructionsRAM[6] = 32'b00001100001000110000000000000001;//SUBi r[3], #1 to r[1]
	 	 instructionsRAM[7] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[8] = 32'b01100100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[9] = 32'b01100000001000000000000000000010;//Load m[#2] to r[1]
	 	 instructionsRAM[10] = 32'b01111000001000000000000000000000;//Pre Output r[1]
	 	 instructionsRAM[11] = 32'b10000000001000000000000000000000;//Output r[1]

	 	 firstClock <= 0;
	 	 end
	 end

	 assign iRAMOutput = instructionsRAM[address];
endmodule // simpleInstructionsRAM
