package Algorithm;

/* 模式串匹配的暴力匹配解法和KMP解法实现 */
public class StringMatch {

    public static void main(String[] args) {
        System.out.println("Hello world!");
        System.out.println("The index of the string match: " + matchByKMP("abababababc", "ababc", 0));
        System.out.println("The index of the string match: " + matchByBrute("abababababc", "ababc", 0));
    }

    public static int[] getNext(String pattern) {
        int[] next = new int[pattern.length()]; // 创建一个next数组
        next[0] = 0;
        int i = 1, j = 0; // 实质上是模式串子串的尾部和模式串的头部的互相匹配
        while(i < pattern.length()) {
            if(pattern.charAt(i) == pattern.charAt(j)) {
                next[i++] = ++j;
            }else if(j == 0) {
                next[i++] = 0;
            }else {
                j = next[j - 1];
            }
        }
        return next;
    }

    public static int matchByKMP(String string, String pattern, int pos) {
        int[] next = getNext(pattern);
        int i = pos, j = 0; // i是指向主串的指针，j是指向模式串的指针
        while(i < string.length() && j < pattern.length()) {
            if(string.charAt(i) == pattern.charAt(j)) {
                i++; j++;
            }else if(j == 0){ // 模式串的首字母匹配失败
                i++;
            }else{
                j = next[j - 1];
            }
        }
        if(j == pattern.length()) return i - j; // 匹配成功，返回匹配的子串的首字母下标
        return -1; // 匹配失败
    }

    public static int matchByBrute(String string, String pattern, int pos) {
        int i = pos, j = 0;
        while(i < string.length() && j < pattern.length()) {
            if(string.charAt(i) == pattern.charAt(j)) {
                i++; j++;
            }else {
                i = i - j + 1; // 在主串上匹配的子串位置基点前进一位
                j = 0; // 模式串重新开始匹配
            }
        }
        if(j == pattern.length()) return i - j;
        return -1;
    }
}
