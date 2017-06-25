module simpleInstructionsRam(clock, address, iRAMOutput);
	 input [9:0] address;
	 input clock;
	 output [31:0] iRAMOutput;
	 integer firstClock = 0;
	 reg [31:0] instructionsRAM[55:0];

	 always @ ( posedge clock ) begin
	 	 if (firstClock==0) begin
 
	 	 instructionsRAM[0] = 32'b01001000000000000000000000001000;//Jump to #8
	 	 instructionsRAM[1] = 32'b01010000011000000000000000010010;//Load m[#18] to r[3]
	 	 instructionsRAM[2] = 32'b00000100011001110000000000000000;//ADDi r[3], #0 to r[7]
	 	 instructionsRAM[3] = 32'b01010100111000000000000000001111;//Store r[7] in m[#15]
	 	 instructionsRAM[4] = 32'b01010000001000000000000000001111;//Load m[#15] to r[1]
	 	 instructionsRAM[5] = 32'b00000100001111100000000000000000;//ADDi r[1], #0 to r[30]
	 	 instructionsRAM[6] = 32'b01001000000000000000000000101010;//Jump to #42
	 	 instructionsRAM[7] = 32'b01001000000000000000000000101010;//Jump to #42
	 	 instructionsRAM[8] = 32'b01011000001000000000000000000000;//Loadi #0 to r[1]
	 	 instructionsRAM[9] = 32'b00000100001001110000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[10] = 32'b01010100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[11] = 32'b01100000001000000000000000000000;//Input to r[1]
	 	 instructionsRAM[12] = 32'b00000100001001110000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[13] = 32'b01010100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[14] = 32'b01010000001000000000000000010100;//Load m[#20] to r[1]
	 	 instructionsRAM[15] = 32'b01010000001000000000000000010100;//Load m[#20] to r[1]
	 	 instructionsRAM[16] = 32'b01010100001000000000000000000100;//Store r[1] in m[#4]
	 	 instructionsRAM[17] = 32'b01010000001000000000000000010101;//Load m[#21] to r[1]
	 	 instructionsRAM[18] = 32'b01010100001000000000000000000101;//Store r[1] in m[#5]
	 	 instructionsRAM[19] = 32'b01010000001000000000000000010110;//Load m[#22] to r[1]
	 	 instructionsRAM[20] = 32'b01010100001000000000000000000110;//Store r[1] in m[#6]
	 	 instructionsRAM[21] = 32'b01010000001000000000000000010111;//Load m[#23] to r[1]
	 	 instructionsRAM[22] = 32'b01010100001000000000000000000111;//Store r[1] in m[#7]
	 	 instructionsRAM[23] = 32'b01010000001000000000000000011000;//Load m[#24] to r[1]
	 	 instructionsRAM[24] = 32'b01010100001000000000000000001000;//Store r[1] in m[#8]
	 	 instructionsRAM[25] = 32'b01010000001000000000000000011001;//Load m[#25] to r[1]
	 	 instructionsRAM[26] = 32'b01010100001000000000000000001001;//Store r[1] in m[#9]
	 	 instructionsRAM[27] = 32'b01010000001000000000000000011010;//Load m[#26] to r[1]
	 	 instructionsRAM[28] = 32'b01010100001000000000000000001010;//Store r[1] in m[#10]
	 	 instructionsRAM[29] = 32'b01010000001000000000000000011011;//Load m[#27] to r[1]
	 	 instructionsRAM[30] = 32'b01010100001000000000000000001011;//Store r[1] in m[#11]
	 	 instructionsRAM[31] = 32'b01010000001000000000000000011100;//Load m[#28] to r[1]
	 	 instructionsRAM[32] = 32'b01010100001000000000000000001100;//Store r[1] in m[#12]
	 	 instructionsRAM[33] = 32'b01010000001000000000000000011101;//Load m[#29] to r[1]
	 	 instructionsRAM[34] = 32'b01010100001000000000000000001101;//Store r[1] in m[#13]
	 	 instructionsRAM[35] = 32'b01010000001000000000000000011110;//Load m[#30] to r[1]
	 	 instructionsRAM[36] = 32'b01010100001000000000000000001110;//Store r[1] in m[#14]
	 	 instructionsRAM[37] = 32'b01010000001000000000000000000010;//Load m[#2] to r[1]
	 	 instructionsRAM[38] = 32'b01010100001000000000000000010010;//Store r[1] in m[#18]
	 	 instructionsRAM[39] = 32'b01011000001000000000000000000100;//Loadi #4 to r[1]
	 	 instructionsRAM[40] = 32'b01010100001000000000000000010001;//Store r[1] in m[#17]
	 	 instructionsRAM[41] = 32'b01001000000000000000000000000001;//Jump to #1
	 	 instructionsRAM[42] = 32'b00000111110001110000000000000000;//ADDi r[30], #0 to r[7]
	 	 instructionsRAM[43] = 32'b01010100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[44] = 32'b01010000011000000000000000000010;//Load m[#2] to r[3]
	 	 instructionsRAM[45] = 32'b01011000100000000000000000001010;//Loadi #10 to r[4]
	 	 instructionsRAM[46] = 32'b01001100011001000000100000000000;//SLT if r[3] < r[4], r[1] = 1 else r[1] = 0
	 	 instructionsRAM[47] = 32'b00000100001001110000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[48] = 32'b00111100111000000000000000000000;//Pre Branch r[7]
	 	 instructionsRAM[49] = 32'b01000000000000000000000000000110;//Branch on Zero #6
	 	 instructionsRAM[50] = 32'b01010000011000000000000000000010;//Load m[#2] to r[3]
	 	 instructionsRAM[51] = 32'b00000100011000010000000000000001;//ADDi r[3], #1 to r[1]
	 	 instructionsRAM[52] = 32'b00000100001001110000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[53] = 32'b01010100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[54] = 32'b01001000000000000000000000101100;//Jump to #44

	 	 firstClock <= 0;
	 	 end
	 end

	 assign iRAMOutput = instructionsRAM[address];
endmodule // simpleInstructionsRAM
