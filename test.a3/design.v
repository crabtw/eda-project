module DUT (O1, O2, O3, I1, I2, I3, I4);
input I1;
input I2;
input I3;
input I4;
output O1;
output O2;
output O3;
wire n1;
wire n2;
wire n3;
wire n4;
not G1 (n1, I1);
not G2 (n2, I2);
not G3 (n3, I3);
or G4 (O1, n1, n2);
nor G5 (n4, n2, n3);
and G6 (O2, n4, I4);
not G7 (O3, I4);
endmodule
