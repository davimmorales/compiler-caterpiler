module simpleInstructionsRam(clock, address, iRAMOutput);
	 input [9:0] address;
	 input clock;
	 output [31:0] iRAMOutput;
	 integer firstClock = 0;
	 reg [31:0] instructionsRAM[128:0];

	 always @ ( posedge clock ) begin
	 	 if (firstClock==0) begin
 
	 	 instructionsRAM[0] = 32'b01101100000000000000000000000000;//Nop
	 	 instructionsRAM[1] = 32'b01010100000000000000000001010000;//Jump to #80
	 	 instructionsRAM[2] = 32'b01101000001000000000000000000000;//Loadi #0 to r[1]
	 	 instructionsRAM[3] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[4] = 32'b01100100111000000000000000001001;//Store r[7] in m[#9]
	 	 instructionsRAM[5] = 32'b01100000011000000000000000001100;//Load m[#12] to r[3]
	 	 instructionsRAM[6] = 32'b00001100001000110000000000000001;//SUBi r[3], #1 to r[1]
	 	 instructionsRAM[7] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[8] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[9] = 32'b00000100100001110000000000000000;//ADDi r[7], #0 to r[4]
	 	 instructionsRAM[10] = 32'b01011100001000110010000000000000;//SLT if r[3] < r[4], r[1] = 1 else r[1] = 0
	 	 instructionsRAM[11] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[12] = 32'b01111100000001110000000000000000;//Pre Branch r[7]
	 	 instructionsRAM[13] = 32'b01001100000000000000000001000001;//Branch on Zero #65
	 	 instructionsRAM[14] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[15] = 32'b00000100111000110000000000000000;//ADDi r[3], #0 to r[7]
	 	 instructionsRAM[16] = 32'b01100100111000000000000000001101;//Store r[7] in m[#13]
	 	 instructionsRAM[17] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[18] = 32'b00000100001000110000000000000001;//ADDi r[3], #1 to r[1]
	 	 instructionsRAM[19] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[20] = 32'b01100100111000000000000000001010;//Store r[7] in m[#10]
	 	 instructionsRAM[21] = 32'b01100000011000000000000000001010;//Load m[#10] to r[3]
	 	 instructionsRAM[22] = 32'b01100000100000000000000000001100;//Load m[#12] to r[4]
	 	 instructionsRAM[23] = 32'b01011100001000110010000000000000;//SLT if r[3] < r[4], r[1] = 1 else r[1] = 0
	 	 instructionsRAM[24] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[25] = 32'b01111100000001110000000000000000;//Pre Branch r[7]
	 	 instructionsRAM[26] = 32'b01001100000000000000000000010110;//Branch on Zero #22
	 	 instructionsRAM[27] = 32'b01100000011000000000000000001010;//Load m[#10] to r[3]
	 	 instructionsRAM[28] = 32'b00000100100000110000000000001110;//ADDi r[3], #14 to r[4]
	 	 instructionsRAM[29] = 32'b10000100001001000000000000000000;//Loadr m[r[4]] to r[1]
	 	 instructionsRAM[30] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[31] = 32'b01100000011000000000000000001101;//Load m[#13] to r[3]
	 	 instructionsRAM[32] = 32'b00000100100000110000000000001110;//ADDi r[3], #14 to r[4]
	 	 instructionsRAM[33] = 32'b10000100001001000000000000000000;//Loadr m[r[4]] to r[1]
	 	 instructionsRAM[34] = 32'b00000101000000010000000000000000;//ADDi r[1], #0 to r[8]
	 	 instructionsRAM[35] = 32'b00000100011001110000000000000000;//ADDi r[7], #0 to r[3]
	 	 instructionsRAM[36] = 32'b00000100100010000000000000000000;//ADDi r[8], #0 to r[4]
	 	 instructionsRAM[37] = 32'b01011100001000110010000000000000;//SLT if r[3] < r[4], r[1] = 1 else r[1] = 0
	 	 instructionsRAM[38] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[39] = 32'b01111100000001110000000000000000;//Pre Branch r[7]
	 	 instructionsRAM[40] = 32'b01001100000000000000000000000011;//Branch on Zero #3
	 	 instructionsRAM[41] = 32'b01100000011000000000000000001010;//Load m[#10] to r[3]
	 	 instructionsRAM[42] = 32'b00000100111000110000000000000000;//ADDi r[3], #0 to r[7]
	 	 instructionsRAM[43] = 32'b01100100111000000000000000001101;//Store r[7] in m[#13]
	 	 instructionsRAM[44] = 32'b01100000011000000000000000001010;//Load m[#10] to r[3]
	 	 instructionsRAM[45] = 32'b00000100001000110000000000000001;//ADDi r[3], #1 to r[1]
	 	 instructionsRAM[46] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[47] = 32'b01100100111000000000000000001010;//Store r[7] in m[#10]
	 	 instructionsRAM[48] = 32'b01010100000000000000000000010101;//Jump to #21
	 	 instructionsRAM[49] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[50] = 32'b01100000100000000000000000001101;//Load m[#13] to r[4]
	 	 instructionsRAM[51] = 32'b01011100001000110010000000000000;//SLT if r[3] < r[4], r[1] = 1 else r[1] = 0
	 	 instructionsRAM[52] = 32'b01011100011001000001100000000000;//SLT if r[4] < r[3], r[3] = 1 else r[3] = 0
	 	 instructionsRAM[53] = 32'b00100100001000010001100000000000;//OR r[1],r[3] to r[1]
	 	 instructionsRAM[54] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[55] = 32'b01111100000001110000000000000000;//Pre Branch r[7]
	 	 instructionsRAM[56] = 32'b01001100000000000000000000010001;//Branch on Zero #17
	 	 instructionsRAM[57] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[58] = 32'b00000100100000110000000000001110;//ADDi r[3], #14 to r[4]
	 	 instructionsRAM[59] = 32'b10000100001001000000000000000000;//Loadr m[r[4]] to r[1]
	 	 instructionsRAM[60] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[61] = 32'b01100100111000000000000000001011;//Store r[7] in m[#11]
	 	 instructionsRAM[62] = 32'b01100000011000000000000000001101;//Load m[#13] to r[3]
	 	 instructionsRAM[63] = 32'b00000100100000110000000000001110;//ADDi r[3], #14 to r[4]
	 	 instructionsRAM[64] = 32'b10000100001001000000000000000000;//Loadr m[r[4]] to r[1]
	 	 instructionsRAM[65] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[66] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[67] = 32'b00000100100000110000000000001110;//ADDi r[3], #14 to r[4]
	 	 instructionsRAM[68] = 32'b10001000111001000000000000000000;//rStore to r[7] in m[r[4]] 
	 	 instructionsRAM[69] = 32'b01100000011000000000000000001011;//Load m[#11] to r[3]
	 	 instructionsRAM[70] = 32'b00000100111000110000000000000000;//ADDi r[3], #0 to r[7]
	 	 instructionsRAM[71] = 32'b01100000011000000000000000001101;//Load m[#13] to r[3]
	 	 instructionsRAM[72] = 32'b00000100100000110000000000001110;//ADDi r[3], #14 to r[4]
	 	 instructionsRAM[73] = 32'b10001000111001000000000000000000;//rStore to r[7] in m[r[4]] 
	 	 instructionsRAM[74] = 32'b01100000011000000000000000001001;//Load m[#9] to r[3]
	 	 instructionsRAM[75] = 32'b00000100001000110000000000000001;//ADDi r[3], #1 to r[1]
	 	 instructionsRAM[76] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[77] = 32'b01100100111000000000000000001001;//Store r[7] in m[#9]
	 	 instructionsRAM[78] = 32'b01010100000000000000000000000101;//Jump to #5
	 	 instructionsRAM[79] = 32'b01010100000000000000000001101011;//Jump to #107
	 	 instructionsRAM[80] = 32'b01101000001000000000000000001001;//Loadi #9 to r[1]
	 	 instructionsRAM[81] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[82] = 32'b01100100111000000000000000000010;//Store r[7] in m[#2]
	 	 instructionsRAM[83] = 32'b01101000001000000000000000000110;//Loadi #6 to r[1]
	 	 instructionsRAM[84] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[85] = 32'b01100100111000000000000000000011;//Store r[7] in m[#3]
	 	 instructionsRAM[86] = 32'b01101000001000000000000000001000;//Loadi #8 to r[1]
	 	 instructionsRAM[87] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[88] = 32'b01100100111000000000000000000100;//Store r[7] in m[#4]
	 	 instructionsRAM[89] = 32'b01101000001000000000000000000111;//Loadi #7 to r[1]
	 	 instructionsRAM[90] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[91] = 32'b01100100111000000000000000000101;//Store r[7] in m[#5]
	 	 instructionsRAM[92] = 32'b01100000001000000000000000000010;//Load m[#2] to r[1]
	 	 instructionsRAM[93] = 32'b01100000001000000000000000000010;//Load m[#2] to r[1]
	 	 instructionsRAM[94] = 32'b01100100001000000000000000001110;//Store r[1] in m[#14]
	 	 instructionsRAM[95] = 32'b01100000001000000000000000000011;//Load m[#3] to r[1]
	 	 instructionsRAM[96] = 32'b01100100001000000000000000001111;//Store r[1] in m[#15]
	 	 instructionsRAM[97] = 32'b01100000001000000000000000000100;//Load m[#4] to r[1]
	 	 instructionsRAM[98] = 32'b01100100001000000000000000010000;//Store r[1] in m[#16]
	 	 instructionsRAM[99] = 32'b01100000001000000000000000000101;//Load m[#5] to r[1]
	 	 instructionsRAM[100] = 32'b01100100001000000000000000010001;//Store r[1] in m[#17]
	 	 instructionsRAM[101] = 32'b01100000001000000000000000000110;//Load m[#6] to r[1]
	 	 instructionsRAM[102] = 32'b01100100001000000000000000010010;//Store r[1] in m[#18]
	 	 instructionsRAM[103] = 32'b01101000001000000000000000000100;//Loadi #4 to r[1]
	 	 instructionsRAM[104] = 32'b01100100001000000000000000001100;//Store r[1] in m[#12]
	 	 instructionsRAM[105] = 32'b01101011111000000000000000010100;//Loadi #20 to r[31]
	 	 instructionsRAM[106] = 32'b01010100000000000000000000000010;//Jump to #2
	 	 instructionsRAM[107] = 32'b01100000001000000000000000001110;//Load m[#14] to r[1]
	 	 instructionsRAM[108] = 32'b01100100001000000000000000000010;//Store r[1] in m[#2]
	 	 instructionsRAM[109] = 32'b01100000001000000000000000001111;//Load m[#15] to r[1]
	 	 instructionsRAM[110] = 32'b01100100001000000000000000000011;//Store r[1] in m[#3]
	 	 instructionsRAM[111] = 32'b01100000001000000000000000010000;//Load m[#16] to r[1]
	 	 instructionsRAM[112] = 32'b01100100001000000000000000000100;//Store r[1] in m[#4]
	 	 instructionsRAM[113] = 32'b01100000001000000000000000010001;//Load m[#17] to r[1]
	 	 instructionsRAM[114] = 32'b01100100001000000000000000000101;//Store r[1] in m[#5]
	 	 instructionsRAM[115] = 32'b01100000001000000000000000010010;//Load m[#18] to r[1]
	 	 instructionsRAM[116] = 32'b01100100001000000000000000000110;//Store r[1] in m[#6]
	 	 instructionsRAM[117] = 32'b01110100001000000000000000000000;//Input to r[1]
	 	 instructionsRAM[118] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[119] = 32'b01100100111000000000000000000111;//Store r[7] in m[#7]
	 	 instructionsRAM[120] = 32'b01100000011000000000000000000111;//Load m[#7] to r[3]
	 	 instructionsRAM[121] = 32'b00000100100000110000000000000010;//ADDi r[3], #2 to r[4]
	 	 instructionsRAM[122] = 32'b10000100001001000000000000000000;//Loadr m[r[4]] to r[1]
	 	 instructionsRAM[123] = 32'b00000100111000010000000000000000;//ADDi r[1], #0 to r[7]
	 	 instructionsRAM[124] = 32'b00000100001001110000000000000000;//ADDi r[7], #0 to r[1]
	 	 instructionsRAM[125] = 32'b01111000001000000000000000000000;//Pre Output r[1]
	 	 instructionsRAM[126] = 32'b10000000001000000000000000000000;//Output r[1]
	 	 instructionsRAM[127] = 32'b01110000000000000000000000000000;//Hlt

	 	 firstClock <= 0;
	 	 end
	 end

	 assign iRAMOutput = instructionsRAM[address];
endmodule // simpleInstructionsRAM
