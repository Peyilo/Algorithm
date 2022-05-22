package Algorithm;

import java.util.Arrays;

public class MergeSort {
    //MergeSort Algorithm Test
    public static void main(String[] args){
        int[] list = new int[100];
        for (int i =0; i < 100; i++){
            list[i] = (int)(Math.random() * 10000);
        }
        mergeSort(list);

        int count = 0;
        while(count < 100){
            if (count % 10 == 0)
                System.out.print("\n"+list[count++]+" ");
            else
                System.out.print(list[count++]+" ");
        }
    }
    public static void mergeSort(int[] list){
        int length = list.length;
        if(length > 1){
            int firstLength = length/2;
            int secondLength = length - firstLength;
            int[] list1 = new int[firstLength], list2 = new int[secondLength];
            System.arraycopy(list,0,list1,0,firstLength);
            mergeSort(list1);
            System.arraycopy(list,firstLength,list2,0,secondLength);
            mergeSort(list2);
            merge(list1,list2,list);
        }
    }
    public static void merge(int[] list1, int[] list2, int[] temp){
        int index1 = 0,index2 = 0, index3 =0;
        int length1 = list1.length,length2 = list2.length;
        while(index1 < length1 && index2 < length2){
            if (list1[index1] < list2[index2])
                temp[index3++] = list1[index1++];
            else
                temp[index3++] = list2[index2++];
            }
        while(index1 < length1){
            temp[index3++] = list1[index1++];
        }
        while(index2 < length2){
            temp[index3++] = list2[index2++];
        }
    }
}
