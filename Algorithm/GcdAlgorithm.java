package Algorithm;
//欧几里得最大公约数算法
public class GcdAlgorithm {
    //GCD 穷举法,时间复杂度O(n)
    public static int gcd1(int num1, int num2){
        int gcd = 1;
        for (int i = 2; i < num1 && i < num2; i++){
            if(num1 % i == 0 && num2 % i == 0)
                gcd = i;
        }
        return gcd;
    }
    //对穷举法优化，时间复杂度O(n)
    public static int gcd2(int num1, int num2){
        int gcd = 1;
        if (num1 % num2 == 0)return num2;//可以不用判断num1,num2谁大
        for (int i = num2/2; i >=1; i--){
            if(num1 % i == 0 && num2 % i == 0){
                gcd = i;
                break;
            }
        }
        return gcd;
    }
    //Euclid最大公约数算法,时间复杂度O(logn)
    public static int EuclidGCD(int num1, int num2){
        if (num1 % num2 == 0)
            return num2;
        else
            return EuclidGCD(num2,num1 % num2);
    }
    //测试
    public static void main(String[] args){
        System.out.println("gcd1 : "+gcd1(34,16));
        System.out.println("gcd2 : "+gcd2(32,24));
        System.out.println("gcd2 : "+gcd2(24,32));
        System.out.println("gcd2 : "+gcd2(8,32));
        System.out.println("EuclidGCD : "+EuclidGCD(32,24));
        System.out.println("EuclidGCD : "+EuclidGCD(24,32));
    }
}
