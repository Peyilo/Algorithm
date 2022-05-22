package Algorithm;

public class SortAlgorithm {
    //一、选择排序算法的java实现
    public static <E extends Comparable<E>> void select_sort(E[] list){
        int length = list.length;
        for (int i = 0; i < length - 1; i++){
            int minIndex = i;
            E minData = list[i];
            for (int j = i + 1; j < length; j++){
                if(minData.compareTo(list[j]) > 0){
                    minIndex = j;
                    minData = list[j];
                }
            }
            if (minIndex != i){
                list[minIndex] = list[i];
                list[i] = minData;
            }
        }
    }
    //二、插入排序算法的java实现
    public static <E extends Comparable<E>> void insert_sort(E[] list){
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
    //三、冒泡排序算法的java实现
    public static <E extends Comparable<E>> void bubble_sort(E[] list){
        int length = list.length;
        for (int i = 0; i < length - 1; i++){
            for (int j = 0; j < length-i-1; j++){
                if (list[j].compareTo(list[j+1]) > 0){
                    E temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] = temp;
                }
            }
        }
    }
    //四、快速排序算法的java实现
    public static <E extends Comparable<E>> void quick_sort(E[] list){
        quick_sort(list,0,list.length);
    }
    public static <E extends Comparable<E>> void quick_sort(E[] list, int lowIndex, int highIndex){
        if(lowIndex >= highIndex){
            return;
        }else{
            int partIndex = partition(list,lowIndex,highIndex);
            quick_sort(list,lowIndex,partIndex-1);
            quick_sort(list,partIndex+1,highIndex);
        }
    }
    public static <E extends Comparable<E>> int partition(E[] list,int lowIndex,int highIndex){
        E temp;
        E pivot = list[0];
        while(true){
            while(list[highIndex].compareTo(pivot) > 0){
                highIndex--;
            }
            while(lowIndex < list.length - 1 && list[lowIndex].compareTo(pivot) < 0){
                lowIndex++;
            }
            if (lowIndex >= highIndex){
                break;
            }else{
                temp = list[highIndex];
                list[highIndex] = list[lowIndex];
                list[lowIndex] = temp;
                highIndex--;
                lowIndex++;
            }
        }
        list[0] = list[highIndex];
        list[highIndex] = pivot;
        return highIndex;
    }
    //五、希尔排序算法的java实现
    public static <E extends Comparable<E>> void shell_sort(E[] list){
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
    //六、归并排序算法的java实现
    public static <E extends Comparable<E>> void merge_sort(E[] list){
        int length = list.length;
        if (length > 1){
            int length1 = length / 2, length2 = length - length / 2;
            E[] list1 = (E[])new Object[length1];
            E[] list2 = (E[])new Object[length2];
            System.arraycopy(list,0,list1,0,length1);
            System.arraycopy(list,length1,list2,0,length2);
            merge_sort(list1);
            merge_sort(list2);
            merge(list1,list2,list);
        }
    }
    public static <E extends Comparable<E>> void merge(E[] list1, E[] list2, E[] list){
        int length1 =list1.length, length2 = list2.length;
        int index = 0, index1 = 0, index2 = 0;
        while(index1 < length1 && index2 < length2){
            if (list1[index1].compareTo(list2[index2]) < 0)
                list[index++] = list1[index1++];
            else if (list1[index].compareTo(list2[index2]) > 0)
                list[index++] = list2[index2++];
            else{
                list[index++] = list1[index1++];
                list[index++] = list2[index2++];
            }
        }
        while (index1 < length1){
            list[index++] = list1[index1++];
        }
        while (index2 < length2){
            list[index++] = list2[index2++];
        }
    }
    //七、堆排序算法的java实现
    public static void heap_sort(int[] list){

    }
    //八、桶排序算法的java实现
    public static void bucket_sort(int[] list){

    }
    //九、基数排序算法的java实现
    public static void radix_sort(int[] list){

    }
}