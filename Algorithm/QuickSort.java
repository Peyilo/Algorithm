package Algorithm;
//快速排序算法的java实现
public class QuickSort {
    //快速排序算法对list[]数组的java实现
    public static int partition(int[] list, int p, int q){
        int temp = 0;
        int lowIndex = p;
        int highIndex = q-1;
        int pivot = list[q];
        while(true){
            while(list[lowIndex] < pivot){
                lowIndex++;
            }
            while(highIndex > 0 && list[highIndex] > pivot){
                highIndex--;
            }
            if(lowIndex >= highIndex){
                break;
            }else{
                temp = list[highIndex];
                list[highIndex] = list[lowIndex];
                list[lowIndex] = temp;
                highIndex--;
                lowIndex++;
            }
        }
        list[q] = list[lowIndex];
        list[lowIndex] = pivot;
        return lowIndex;
    }
    public static void quickSort(int[] list, int p, int q){
        int par;
        if((q-p) <= 0){
            return;
        }
        else{
            par = partition(list,p,q);
            quickSort(list,p,par - 1);
            quickSort(list,par+1,q);
        }
    }
    public static void quickSort(int[] list){
        quickSort(list,0,list.length-1);
    }

    //快速排序算法对泛型数组的java实现
    public static <E extends Comparable<E>> int genericPartition(E[] list, int p, int q){
        E temp;
        int lowIndex = p + 1;
        int highIndex = q;
        E pivot = list[p];
        while(true){
            while(list[highIndex].compareTo(pivot) > 0){
                highIndex--;
            }
            while(lowIndex < list.length-1 && list[lowIndex].compareTo(pivot) < 0){
                lowIndex++;
            }
            if(lowIndex >= highIndex){
                break;
            }else{
                temp = list[highIndex];
                list[highIndex] = list[lowIndex];
                list[lowIndex] = temp;
                highIndex--;
                lowIndex++;
            }
        }
        list[p] = list[highIndex];
        list[highIndex] = pivot;
        return highIndex;
    }
    public static <E extends Comparable<E>> void genericQuickSort(E[] list){
        genericQuickSort(list,0,list.length-1);
    }
    public static <E extends Comparable<E>> void genericQuickSort(E[] list, int p, int q){
        int partIndex;
        if(p >= q){
            return;
        }else{
            partIndex = genericPartition(list,p,q);
            genericQuickSort(list,p,partIndex-1);
            genericQuickSort(list,partIndex+1,q);
        }
    }
    public static void main(String[] args){
        Double[] list1 = {1.2,3.2,0.1,-1.3,4.5,4.3,3.4,6.8,5.1};
        int[] list2 = {3,4,6,1,7,32,65,32,7,3,52,1,2};
        quickSort(list2);
        genericQuickSort(list1);
        for(int element: list2){
            System.out.print(element+" ");
        }
        System.out.println();
        for (Double element: list1){
            System.out.print(element+" ");
        }
        System.out.println();
    }
}
