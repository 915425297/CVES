module BCDToLED(
input [3:0] x, // binary input
output [6:0] seg
 // segments
);
assign seg[ 0 ] = (x[2] & !x[1] & !x[0]) | (!x[3] & !x[2] & !x[1] & x[0]);
assign seg[ 1 ] = (x[2] & !x[1] & x[0]) | (x[2] & x[1] & !x[0]);
assign seg[ 2 ] = (!x[2] & x[1] & !x[0]);
assign seg[ 3 ] = (x[2] & !x[1] & !x[0]) | (x[2] & x[1] & x[0]) | (!x[3] & !x[2] & !x[1] & x[0]);
assign seg[ 4 ] = (x[2] & !x[1]) | x[0];
assign seg[ 5 ] = (x[1] & x[0]) | (!x[2] & x[1]) | (!x[3] & !x[2] & x[0]);
assign seg[ 6 ] = (x[2] & x[1] & x[0]) | (!x[3] & !x[2] & !x[1]);
endmodule

module BCDToLED4(
input [3:0] data1, data2, data3, data4,
output [6:0] seg,
output [3:0] an,
clk
);
wire [3:0] p;
wire [1:0] clkout;
wire clk1;
clock_divider it(clk1, clkout[0]);
clk_wiz_1 ih(clk, clk1);
clock_divider #(2500) iti(clk1, clkout[1]);
mux4v #(4) shitr(p, data4, data3, data2, data1, clkout);
BCDToLED pj(p, seg);
assign an[3] = clkout[1] | clkout[0];
assign an[2] = clkout[1] | !clkout[0];
assign an[1] = !clkout[1] | clkout[0];
assign an[0] = !clkout[1] | !clkout[0];
endmodule
