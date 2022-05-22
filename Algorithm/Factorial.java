package Algorithm;

import java.util.Scanner;
//计算阶乘 --- 递归
public class Factorial {
    public static void main(String[] args){
        java.util.Scanner input = new Scanner(System.in);
        System.out.print("Enter an integer : ");
        int number = input.nextInt();
        System.out.println("Start--->>>");
        System.out.println("result : " + factorialNum(number));
        System.out.println("End!");
    }
    public static int factorialNum(int num){
        if (num == 0)
            return 1;
        else
            return factorialNum(num-1) * num;
    }
}
