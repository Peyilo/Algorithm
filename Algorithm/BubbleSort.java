package Algorithm;
//冒泡排序算法的java实现
public class BubbleSort {
    public static void main(String[] args){
        Double[] list1 = {1.2,3.2,0.1,-1.3,4.5,4.3,3.4,6.8,5.1};
        int[] list2 = {3,4,6,1,7,32,65,32,7,3,52,1,2};
        genericBubbleSort(list1);
        bubbleSort(list2);
        for(int element: list2){
            System.out.print(element+" ");
        }
        System.out.println();
        for(Double element: list1){
            System.out.print(element+" ");
        }
        System.out.println();
    }
    //冒泡排序算法对int[]数组的java实现
    public static void bubbleSort(int[] list){
        int length = list.length;
        for (int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - 1 -i; j ++){
                if (list[j] > list[j + 1]){
                    int temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] = temp;
                }
            }
        }
    }
    //冒泡排序算法对泛型数组的java实现
    public static <E extends Comparable<E>> void genericBubbleSort(E[] list){
        int length = list.length;
        for(int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - 1 -i; j++){
                if(list[j].compareTo(list[j+1]) > 0){
                    E temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] = temp;
                }
            }
        }
    }
}
