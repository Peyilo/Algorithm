package Algorithm;

import java.util.Scanner;

public class Queen {
    static int[] q = new int[40];           //稀疏数组
    static int count = 0;

    public static void n_queens(int k, int n) {
        int j;
        //递归结束条件
        if (k > n)
            print(n);
        else {
            for (j = 1; j <= n; j++) // 试探第k行的每一列，找到符合要求的列
            {
                //如果不安全就回溯(不保存列标到数组中),安全就继续下一层递归
                if (isSafe(k, j)) {
                    q[k] = j;
                    n_queens(k + 1, n); // 在确认第 k 行皇后位置的前提下，继续测试下一行皇后的位置
                }
            }
        }
    }

    public static boolean isSafe(int k, int j) {
        int i;
        for (i = 1; i < k; i++) {
            // 如果有其它皇后位置同一列上，或者位于该位置的斜线位置上，则该位置无法使用
            if (q[i] == j || Math.abs(i - k) == Math.abs(q[i] - j))
                return false;
        }
        return true;
    }

    // 输出 N 皇后问题的解决方案
    public static void print(int n) {
        int i, j;
        count++;
        System.out.println("第 " + count + " 个解: ");

        for (i = 1; i <= n; i++) // 行
        {
            for (j = 1; j <= n; j++) // 列
            {
                if (q[i] != j)
                    System.out.print("x  ");
                else
                    System.out.print("Q  ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void main(String[] args) {
        System.out.println("请输入有几个皇后 : ");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        n_queens(1, n);
        System.out.println("共有 " + count + " 种摆放方式");
    }
}