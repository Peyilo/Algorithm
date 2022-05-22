package Algorithm;
//希尔排序算法的java实现
public class ShellSort {
    public static void main(String[] args){
        Double[] list1 = {1.2,3.2,0.1,-1.3,4.5,4.3,3.4,6.8,5.1};
        int[] list2 = {3,4,6,1,7,32,65,32,7,3,52,1,2};
        genericShellSort(list1);
        shellSort(list2);
        //shell_sort(list2);
        for(int element: list2){
            System.out.print(element+" ");
        }
        System.out.println();
        for(Double element : list1){
            System.out.print(element+" ");
        }
        System.out.println();
    }
    //希尔排序算法对int[]数组的java实现
    public static void shellSort(int[] list) {
        int interval = 1;
        while (interval < list.length / 3) {
            interval = interval * 3 + 1;
        }
        while (interval > 0) {
            for (int i = interval; i < list.length; i++) {
                int position = i;
                int shell_ele = list[i];
                while (position > interval - 1 && list[position - interval] > shell_ele) {
                    list[position] = list[position - interval];
                    position -= interval;
                }
                if (position != i)
                    list[position] = shell_ele;
            }
            interval = (interval - 1) / 3;
        }
    }
    //希尔排序算法对泛型数组的java实现
    public static <E extends Comparable<E>> void genericShellSort(E[] list){
        int interval = 1;
        while(interval < list.length / 3)
            interval = interval * 3 + 1;
        while(interval > 0){
            for (int i = interval; i < list.length; i++){
                int position = i;
                E shell_ele = list[i];
                while(position > interval - 1 && list[position - interval].compareTo(shell_ele) >= 0){
                    list[position] = list[position - interval];
                    position -= interval;
                }
                if(position != i)
                    list[position] = shell_ele;
            }
            interval = (interval - 1) / 3;
        }
    }
}
