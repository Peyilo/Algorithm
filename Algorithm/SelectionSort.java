package Algorithm;
//选择排序算法的java实现
public class SelectionSort {
    public static void main(String[] args){
        int[] list = {12,3,1,3,412,4,2,5,243,5,3,2,76};
        selectionSort(list);
        Double[] listDouble = {1.2,32.4,3.2,2.3,4.3,4.5,6.5,3.2,45.2,1.2};
        genericSelectionSort(listDouble);
        for(int element : list)
            System.out.print(element+" ");
        System.out.println();
        for (Double element: listDouble)
            System.out.print(element+" ");
    }
    //int[]数组的选择排序的java实现
    public static void selectionSort(int[] list){
        for(int i = 0; i < list.length - 1; i++){
            int minIndex = i;
            int minNum = list[i];
            for (int j = i + 1; j < list.length; j++){
                if (list[j] < minNum){
                    minIndex = j;
                    minNum = list[j];
                }
            }
            list[minIndex] = list[i];
            list[i] = minNum;
        }
    }
    //泛型选择排序算法的实现
    public static <E extends Comparable<E>> void genericSelectionSort(E[] list){
        for (int i = 0; i < list.length - 1; i++){
            int minIndex = i;
            E minNum = list[i];
            for (int j = i + 1; j < list.length; j++){
                if (minNum.compareTo(list[j]) > 0){
                    minNum = list[j];
                    minIndex = j;
                }
            }
            list[minIndex] = list[i];
            list[i] = minNum;
        }
    }
}
