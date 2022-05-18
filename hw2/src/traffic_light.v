module traffic_light (
    input  clk,
    input  rst,
    input  pass,
    output reg R,
    output reg G,
    output reg Y
);

//write your code here
    reg [34:0]counter;
    always @(posedge clk or posedge rst)begin
        counter = counter + 1;
        if(rst)begin
            R <= 0;
            G <= 1;
            Y <= 0;
            counter <= 0;
        end
        else if(pass && counter > 511)begin
            counter <= 0;
            R <= 0;
            G <= 1;
            Y <= 0;
        end
        else begin
            if(counter < 512)begin
                R <= 0;
                G <= 1;
                Y <= 0;
            end
            else if(counter >= 512 && counter <= 575)begin
                R <= 0;
                G <= 0;
                Y <= 0;
            end
            else if(counter >= 576 && counter <= 639)begin
                R <= 0;
                G <= 1;
                Y <= 0;
            end
            else if(counter >= 640 && counter <= 703)begin
                R <= 0;
                G <= 0;
                Y <= 0;
            end
            else if(counter >= 704 && counter <= 767)begin
                R <= 0;
                G <= 1;
                Y <= 0;
            end
            else if(counter >= 768 && counter <= 1023)begin
                R <= 0;
                G <= 0;
                Y <= 1;
            end
            else if(counter >= 1024 && counter <= 1535)begin
                R <= 1;
                G <= 0;
                Y <= 0;
            end
            else begin
                R <= 0;
                G <= 1;
                Y <= 0;
                counter <= 0;
            end
        end
    end
endmodule
