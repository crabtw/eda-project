module testcase2(I1,I2,I3,I4,I5,I6,I7,O1,O2,O3);
input I1;
input I2;
input I3;
input I4;
input I5;
input I6;
input I7;

output O1;
output O2;
output O3;

wire W1;
wire W2;
wire W3;
wire W4;
wire W5;
wire W6;
wire W7;
wire W8;
wire W9;

not G1 (W1, I1);
not G2 (W2, I2);
and G3 (W3, W2, W1);
not G4 (W4, I3);
nor G5 (W5, I4, W4);
or G6 (W6, W5, W3);
or G7 (W7, I5, W3);
nand G8 (W8, W7, W6);
not G9 (W9, I6);
nor G10 (O1, W9, W8);
nor G11 (O2, W2, O1);
nor G12 (O3, I7, W5);
endmodule
