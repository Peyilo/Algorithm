package Algorithm;
import java.util.Scanner;
public class Prime {
    //穷举法，时间复杂度O(n)
    public static boolean isPrimeBruteForce(int n){
        if (n == 1)return false;
        for (int i = 2; i < n; i++){
            if(n % i == 0)return false;
        }
        return true;
    }
    //对穷举法进行优化，时间复杂度为O(n^(1/2))
    public static boolean isPrime(int n){
        if (n == 1)return false;
        int sqrNum = (int)Math.sqrt(n);
        for (int i = 2; i <= sqrNum; i++){
            if (n % i == 0)return false;
        }
        return true;
    }
    //Algorithm Test
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        System.out.print("Enter a integer : ");
        int n = input.nextInt();
        System.out.println("\nstart~");
        long time1_start = System.currentTimeMillis();
        for (int i = 2; i <= n; i++){
            if(isPrimeBruteForce(i))System.out.print(i+" ");
        }
        long time1_end = System.currentTimeMillis();
        System.out.println("\nend~");
        System.out.println("start~");
        long time2_start = System.currentTimeMillis();
        for (int i = 2; i <= n; i++){
            if(isPrime(i))System.out.print(i+" ");
        }
        long time2_end = System.currentTimeMillis();
        System.out.println("\nend~");
        System.out.println("time1 : "+(time1_end - time1_start)+"\ttime2 : "+(time2_end-time2_start));
    }
}
