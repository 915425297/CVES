module power1(
input [3: 0] power,
output [15: 0] led) {
led[0] = !power[0] & !power[1] !power[2] & !power[3];
led[1] = power[0] & !power[1] !power[2] & !power[3];
led[2] = !power[0] & power[1] !power[2] & !power[3];
led[3] = power[0] & power[1] !power[2] & !power[3];
led[4] = !power[0] & !power[1] power[2] & !power[3];
led[5] = power[0] & !power[1] power[2] & !power[3];
led[6] = !power[0] & power[1] power[2] & !power[3];
led[7] = power[0] & power[1] power[2] & !power[3];
led[8] = !power[0] & !power[1] !power[2] & power[3];
led[9] = power[0] & !power[1] !power[2] & power[3];
led[10] = !power[0] & power[1] !power[2] & power[3];
led[11] = power[0] & power[1] !power[2] & power[3];
led[12] = !power[0] & !power[1] power[2] & power[3];
led[13] = power[0] & !power[1] power[2] & power[3];
led[14] = !power[0] & power[1] power[2] & power[3];
led[15] = 0;
}

module top_level(
input [15:0] sw,
input btnC,
input btnU,
input btnD,
input clk,
output [6:0] seg,
output [3:0] an,
output [15:0] led
);

wire clk3, clk4, clk5, clk6, clk7, clk8, clk9, clk2;
wire [3:0] data1, data2, data3, data4;
wire [32:0] score, time, timeN, scoreN;
wire [3:0] firstDigit, secondDigit, thirdDigit, fourthDigit;
wire startN, start, setT1, setT2, setT3, setT1N, setT2N, setT3N, onN, on, endN, end;
wire setD1, setD2, setD3, setD1N, setD2N, setD3N, clock;
wire [32:0] timeLevel, nextTime, nextTime2, nextTime1, diffLevel, nextdiff1, nextdiff2, nextdiff;
wire [32:0] addT, subT, curT, addD, subD, curD;
wire [3:0] target;

assign startN = (setT1 & sw[15]) | (setT2 & sw[15]) | (setT3 & sw[15])
| (setD2 & sw[15]) | (setD3 & sw[15]) | (setD1 & sw[15]) | (on & sw[15]) | (end & sw[15]);
dffe star(start, startN, clock, 1'b1, 1'b0);
assign setT1N = ((startN & !sw[15]) | ((setT1 | setT2 | setT3) & !btnU & !btnD)) & !btcC & !sw[15];
dffe se1(setT1, setT1N, clock, 1'b1, 1'b0);
assign setT2N = setT1 & (btnU | btnD) & !btcC & !sw[15];
dffe se2(setT2, setT2N, clock, 1'b1, 1'b0);
assign setT3N = (setT2 | setT3) & (btnU | btnD) & !btcC & !sw[15];
dffe se3(setT3, setT3N, clock, 1'b1, 1'b0);
alu32 s1(nextTime1, , , , timeLevel, 1, 3'b010);
alu32 s2(nextTime2, , , , timeLevel, 1, 3'b011);
register #(32, 0) r3(timeLevel, nextTime, clock, 1'b1, 1'b0);
assign addT = {32{setT2 == 1 & btnU == 1 & timeLevel != 3}};
assign subT = {32{setT2 == 1 & btnD == 1 & timeLevel != 0}};
assign curT = {!addT & !subT};
assign nextTime = ((curT & timeLevel) | (subT & nextTime2) | (addT & nextTime1)) & {32{!sw[15]}};

assign setD1N = ((setT1 | setT2 | setT3) & btcC) | ((setD1 | setD2 | setD3) & !btnU & !btnD) & !btcC) & !sw[15];
dffe st1(setD1, setD1N, clock, 1'b1, 1'b0);
assign setD2N = setD1 & (btnU | btnD) & !btcC & !sw[15];
dffe st2(setD2, setD2N, clock, 1'b1, 1'b0);
assign setD3N = (setD2 | setD3) & !btcC & (btnU | btnD) & !sw[15];
dffe st3(setD3, setD3N, clock, 1'b1, 1'b0);
alu32 s1(nextdiff1, , , , timeLevel, 1, 3'b010);
alu32 s2(nextdiff2, , , , timeLevel, 1, 3'b011);
register #(32) r9(diffLevel, nextdiff, clock, 1'b1, 1'b0);
assign addD = {32{setD2 == 1 & btnU == 1 & diffLevel != 3}};
assign subD = {32{setD2 == 1 & btnD == 1 & diffLevel != 0}};
assign curD = {!addT & !subT};
assign nextdiff = ((curD & timeLevel) | (subD & nextdiff2) | (addD & nextdiff1)) & {32{!sw[15]}};

assign onN = ((setD1 | setD2 | setD3) & btcC & (time != 0) | on) & !sw[15];
assign endN = (end | on)& time == 0 & !sw[15];

dffe on1(on, onN, clock, 1'b1, 1'b0);
dffe end1(end, endN, clock, 1'b1, 1'b0);

DecimalDigitDecoder timeC(time[7: 0], , thirdDigit, fourthDigit);
DecimalDigitDecoder scoreC(score[7: 0], , firstDigit, secondDigit);
assign data1 = ({4{(setT1 | setT2 | setT3)}} & timeLevel[3:0]) | 
({4{(setD1 | setD2 | setD3)}} & diffLevel[3:0]) |
{4{!sw[5]}} | {4{on | end}} & firstDigit;
assign data2 = {4{on | end}} & secondDigit | 15 & !on;
assign data3 = {4{on | end}} & thirdDigit | 15 & !on;
assign data4 = {4{on | end}} & fourthDigit | 15 & !on;
BCDToLED4 k(data1, data2, data3, data4, seg, an, clk);

//game stage
wire [32: 0] next_time, time, next_score, score, expected_time;
wire clk2, clk3, clockformouse;
mux4 #(32) t1(expected_time, 15, 30, 45, 60, timeLevel[1:0]);
register #(32, expected_time) timecontrol(time, next_time, clk2, on, setT1);
alu32 subtract(next_time, , time, 1, 3'b011);
register #(32, 0) scorecontrol(score, next_score, clockformouse, on & (led == sw), setT1);


mux4 #(1) clockcontroler(clockformouse, clk2, clk3, clk4, clk5, diffLevel);
alu32 addscore(next_score, , score, 1, 3'b010);
power1 r(target, led);
register #(4, 15) targetControl(target, {clk6, clk7, clk8, clk9},  clockformouse, on, !on);


clock_divider #(1) (clk, clock); // main clock
clock_divider #(5000000) (clk, clk2); // clock for 1 sec
clock_divider #(2500000) (clk, clk3); // clock for 0.5 sec
clock_divider #(7500000) (clk, clk4); // clock for 1.5 sec
clock_divider #(10000000) (clk, clk5); // clock for 2 sec
clock_divider #(57) (clk, clk6); # clock sybolize four digit
clock_divider #(1013) (clk, clk7);
clock_divider #(2243) (clk, clk8);
clock_divider #(5449) (clk, clk9);

endmodule
