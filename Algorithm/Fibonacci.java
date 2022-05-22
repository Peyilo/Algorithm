package Algorithm;

import java.awt.*;
import java.math.BigInteger;
import java.util.Scanner;
//Fibonacci series问题 --- 递归
public class Fibonacci {
    public static void main(String[] args) throws Exception{
        java.util.Scanner input = new Scanner(System.in);
        System.out.print("Enter an integer : ");
        int num = input.nextInt();
        for (int i = 0; i < num; i++){
            long time1 = getTime(i,1);
            long time2 =getTime(i,2);
            BigInteger fibNum = fibonacciNumOptimize(i);
            System.out.print("\nbeforeOptimize : "+time1+"ms\tafterOptimize : "+time2+"ms\tFibonacci("+i+") = "+fibNum+"\n");
        }
    }
    //求解斐波那契数列
    public static BigInteger fibonacciNum(int index){
        if (index == 0)
            return new BigInteger("0");
        else if (index == 1)
            return new BigInteger("1");
        else
            return fibonacciNum(index-1).add(fibonacciNum(index-2));
    }
    //斐波那契数列算法优化
    public static BigInteger fibonacciNumOptimize(int index){
        BigInteger f0 = new BigInteger("0");
        BigInteger f1 = new BigInteger("1");
        BigInteger f2 = new BigInteger("1");
        if (index == 0)
            return f0;
        else if (index == 1)
            return f1;
        else if (index == 2)
            return f2;
        for (int i = 3; i <= index; i++){
            f0= f1;
            f1 = f2;
            f2 = f1.add(f2);
        }
        return f2;
    }
    public static long getTime(int index, int selectNum){
        long start_time,end_time,run_time;
        if (selectNum == 1){
            start_time = System.currentTimeMillis();
            fibonacciNum(index);
            end_time = System.currentTimeMillis();
        }else{
            start_time = System.currentTimeMillis();
            fibonacciNumOptimize(index);
            end_time = System.currentTimeMillis();
        }
        run_time = end_time - start_time;
        return run_time;
    }
}
