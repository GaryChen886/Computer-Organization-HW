`timescale 1ns/10ps
`define abs(a,b) ((a>b)? a-b : b-a )
module CS(Y, X, reset, clk);
	input clk, reset;
	input 	[7:0] X;
	output reg [9:0] Y;
//--------------------------------------
//  \^o^/   Write your code here~  \^o^/
//--------------------------------------
    reg [7:0] XS [8:0]; //XSay of 8-bit number with length 9
	reg [13:0] sum; //sum of XSay
	reg [7:0] avg; //average of sum
	reg [7:0] appr; //approximate average
	integer i,j,k;
	always @(posedge clk or posedge reset) begin
		if(reset)begin
			for(i=0;i<9;i=i+1)begin
				XS[i] <= 0;
			end
			sum <= 0;
			i <= 0;
		end
		else begin
			sum <= sum - XS[0] + X;

			for(j=0;j<8;j=j+1)begin
				XS[j] <= XS[j+1];
			end
			XS[8] = X;
		end
	end
	always @(*) begin
		appr = 0;
		avg = sum/9;
		for(k=0;k<9;k=k+1)begin
			if((avg >= XS[k]) && (`abs(avg,XS[k]) < `abs(appr,avg)))begin
				appr = XS[k];
			end
		end
		Y = {sum + {appr,3'b0} + appr}>>3;
	end

endmodule
