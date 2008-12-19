module testcase1(I1, I2, I3, I4, I5, O1, O2);
input I1;
input I2;
input I3;
input I4;
input I5;

output O1;
output O2;

wire W1;
wire W2;
wire W3;
wire W4;

nand G1 (W1, I1, I3);
nand G2 (W2, I3, I4);
nand G3 (W3, I2, W2);
nand G4 (W4, W2, I5);
nand G5 (O1, W1, W3);
nand G6 (O2, W3, W4);
 
endmodule
