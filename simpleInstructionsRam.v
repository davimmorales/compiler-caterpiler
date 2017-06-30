module simpleInstructionsRam(clock, address, iRAMOutput);
	 input [9:0] address;
	 input clock;
	 output [31:0] iRAMOutput;
	 integer firstClock = 0;
	 reg [31:0] instructionsRAM[69:0];

	 always @ ( posedge clock ) begin
	 	 if (firstClock==0) begin
 
	 	 instructionsRAM[0] = 32'b01001000000000000000000000000110;//Jump to #6
	 	 instructionsRAM[1] = 32'b01010000011000000000000000010010;//Load m[#18] to r[3]
	 	 instructionsRAM[2] = 32'b00000100011001110000000000000000;//ADDi r[3], #0 to r[7]
	 	 instructionsRAM[3] = 32'b01010100111000000000000000001111;//Store r[7] in m[#15]
	 	 instructionsRAM[4] = 32'b01110011111000010000000000000000;//Loadr m[r[31]] to r[1]
	 	 instructionsRAM[5] = 32'b01111000001000000000000000000000;//Jump to r[1]
	 	 instructionsRAM[6] = 32'b01011000001000000000000000000000;//Loadi #0 to r[1]
	 	 instructionsRAM[7] = 32'b00000100001001110000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[8] = 32'b01010100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[9] = 32'b01010000001000000000000000010100;//Load m[#20] to r[1]
	 	 instructionsRAM[10] = 32'b01010000001000000000000000010100;//Load m[#20] to r[1]
	 	 instructionsRAM[11] = 32'b01010100001000000000000000000100;//Store r[1] in m[#4]
	 	 instructionsRAM[12] = 32'b01010000001000000000000000010101;//Load m[#21] to r[1]
	 	 instructionsRAM[13] = 32'b01010100001000000000000000000101;//Store r[1] in m[#5]
	 	 instructionsRAM[14] = 32'b01010000001000000000000000010110;//Load m[#22] to r[1]
	 	 instructionsRAM[15] = 32'b01010100001000000000000000000110;//Store r[1] in m[#6]
	 	 instructionsRAM[16] = 32'b01010000001000000000000000010111;//Load m[#23] to r[1]
	 	 instructionsRAM[17] = 32'b01010100001000000000000000000111;//Store r[1] in m[#7]
	 	 instructionsRAM[18] = 32'b01010000001000000000000000011000;//Load m[#24] to r[1]
	 	 instructionsRAM[19] = 32'b01010100001000000000000000001000;//Store r[1] in m[#8]
	 	 instructionsRAM[20] = 32'b01010000001000000000000000011001;//Load m[#25] to r[1]
	 	 instructionsRAM[21] = 32'b01010100001000000000000000001001;//Store r[1] in m[#9]
	 	 instructionsRAM[22] = 32'b01010000001000000000000000011010;//Load m[#26] to r[1]
	 	 instructionsRAM[23] = 32'b01010100001000000000000000001010;//Store r[1] in m[#10]
	 	 instructionsRAM[24] = 32'b01010000001000000000000000011011;//Load m[#27] to r[1]
	 	 instructionsRAM[25] = 32'b01010100001000000000000000001011;//Store r[1] in m[#11]
	 	 instructionsRAM[26] = 32'b01010000001000000000000000011100;//Load m[#28] to r[1]
	 	 instructionsRAM[27] = 32'b01010100001000000000000000001100;//Store r[1] in m[#12]
	 	 instructionsRAM[28] = 32'b01010000001000000000000000011101;//Load m[#29] to r[1]
	 	 instructionsRAM[29] = 32'b01010100001000000000000000001101;//Store r[1] in m[#13]
	 	 instructionsRAM[30] = 32'b01010000001000000000000000011110;//Load m[#30] to r[1]
	 	 instructionsRAM[31] = 32'b01010100001000000000000000001110;//Store r[1] in m[#14]
	 	 instructionsRAM[32] = 32'b01011000001000000000000000000000;//Loadi #0 to r[1]
	 	 instructionsRAM[33] = 32'b01010100001000000000000000010010;//Store r[1] in m[#18]
	 	 instructionsRAM[34] = 32'b01011000001000000000000000001010;//Loadi #10 to r[1]
	 	 instructionsRAM[35] = 32'b01010100001000000000000000010001;//Store r[1] in m[#17]
	 	 instructionsRAM[36] = 32'b01011011111000000000000000011111;//Loadi #31 to r[31]
	 	 instructionsRAM[37] = 32'b00000111111111110000000000000001;//ADDi r[31], #1 to r[31]
	 	 instructionsRAM[38] = 32'b01011000001000000000000000101001;//Loadi #41 to r[1]
	 	 instructionsRAM[39] = 32'b01110111111000010000000000000000;//Storer to r[1] in m[r[31]] 
	 	 instructionsRAM[40] = 32'b01001000000000000000000000000001;//Jump to #1
	 	 instructionsRAM[41] = 32'b00001111111111110000000000000001;//SUBi r[31], #1 to r[31]
	 	 instructionsRAM[42] = 32'b01010000001000000000000000000100;//Load m[#4] to r[1]
	 	 instructionsRAM[43] = 32'b01010100001000000000000000010100;//Store r[1] in m[#20]
	 	 instructionsRAM[44] = 32'b01010000001000000000000000000101;//Load m[#5] to r[1]
	 	 instructionsRAM[45] = 32'b01010100001000000000000000010101;//Store r[1] in m[#21]
	 	 instructionsRAM[46] = 32'b01010000001000000000000000000110;//Load m[#6] to r[1]
	 	 instructionsRAM[47] = 32'b01010100001000000000000000010110;//Store r[1] in m[#22]
	 	 instructionsRAM[48] = 32'b01010000001000000000000000000111;//Load m[#7] to r[1]
	 	 instructionsRAM[49] = 32'b01010100001000000000000000010111;//Store r[1] in m[#23]
	 	 instructionsRAM[50] = 32'b01010000001000000000000000001000;//Load m[#8] to r[1]
	 	 instructionsRAM[51] = 32'b01010100001000000000000000011000;//Store r[1] in m[#24]
	 	 instructionsRAM[52] = 32'b01010000001000000000000000001001;//Load m[#9] to r[1]
	 	 instructionsRAM[53] = 32'b01010100001000000000000000011001;//Store r[1] in m[#25]
	 	 instructionsRAM[54] = 32'b01010000001000000000000000001010;//Load m[#10] to r[1]
	 	 instructionsRAM[55] = 32'b01010100001000000000000000011010;//Store r[1] in m[#26]
	 	 instructionsRAM[56] = 32'b01010000001000000000000000001011;//Load m[#11] to r[1]
	 	 instructionsRAM[57] = 32'b01010100001000000000000000011011;//Store r[1] in m[#27]
	 	 instructionsRAM[58] = 32'b01010000001000000000000000001100;//Load m[#12] to r[1]
	 	 instructionsRAM[59] = 32'b01010100001000000000000000011100;//Store r[1] in m[#28]
	 	 instructionsRAM[60] = 32'b01010000001000000000000000001101;//Load m[#13] to r[1]
	 	 instructionsRAM[61] = 32'b01010100001000000000000000011101;//Store r[1] in m[#29]
	 	 instructionsRAM[62] = 32'b01010000001000000000000000001110;//Load m[#14] to r[1]
	 	 instructionsRAM[63] = 32'b01010100001000000000000000011110;//Store r[1] in m[#30]
	 	 instructionsRAM[64] = 32'b01010000001000000000000000010111;//Load m[#23] to r[1]
	 	 instructionsRAM[65] = 32'b00000100001001110000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[66] = 32'b00000100111000010000000000000000;//ADDi r[7], #0 to r[1]
	 	 instructionsRAM[67] = 32'b01101000001000000000000000000000;//Pre Output r[1]
	 	 instructionsRAM[68] = 32'b01101100001000000000000000000000;//Output r[1]

	 	 firstClock <= 0;
	 	 end
	 end

	 assign iRAMOutput = instructionsRAM[address];
endmodule // simpleInstructionsRAM
