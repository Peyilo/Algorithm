package Algorithm;
//插入排序算法的java实现
public class InsertSort {
    public static void main(String[] args){
        Double[] list1 = {1.2,3.2,0.1,-1.3,4.5,4.3,3.4,6.8,5.1};
        int[] list2 = {3,4,6,1,7,32,65,32,7,3,52,1,2};
        Double[] testList = list1;
        insertSort(list2);
        long insert_startTime = System.currentTimeMillis();
        genericInsertSort(list1);
        long insert_endTime = System.currentTimeMillis();
        long selection_startTime = System.currentTimeMillis();
        SelectionSort.genericSelectionSort(testList);
        long selection_endTime = System.currentTimeMillis();
        for(int element: list2){
            System.out.print(element+" ");
        }
        System.out.println();
        for(Double element: list1){
            System.out.print(element+" ");
        }
        System.out.println();
        System.out.println("insertSort : "+(insert_endTime-insert_startTime)+"\nselectionSort : "+(selection_endTime-selection_startTime));
    }
    //插入排序算法对int[]数组的java实现
    public static void insertSort(int[] list){
        int n = list.length;
        for (int i =1; i < n; i++){
            int insert_ele = list[i];
            int position = i;
            while(position > 0 && insert_ele < list[position-1]){
                list[position] = list[position-1];
                position--;
            }
            if(position != i)
                list[position] = insert_ele;
        }
    }
    //插入排序对泛型数组的java实现
    public static <E extends Comparable<E>> void genericInsertSort(E[] list){
        int n = list.length;
        for (int i = 1; i < n; i++){
            E insert_ele = list[i];
            int position = i;
            while(position > 0 && insert_ele.compareTo(list[position-1]) < 0){
                list[position] = list[position-1];
                position--;
            }
            if(position!=i)
                list[position] = insert_ele;
        }
    }
}
